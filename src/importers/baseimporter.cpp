/***************************************************************************
*   Copyright (C) 2003 by                                                 *
*   Jason Kivlighn (mizunoami44@users.sourceforge.net)                    *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/

#include "baseimporter.h"

#include <kapplication.h>
#include <kconfig.h>
#include <kdebug.h>
#include <klocale.h>
#include <kprogress.h>
#include <kmessagebox.h>

#include <qvaluevector.h>

#include "datablocks/recipe.h"
#include "backends/recipedb.h"
#include "datablocks/categorytree.h"
#include "datablocks/unit.h"

BaseImporter::BaseImporter() :
		m_recipe_list( new RecipeList ),
		m_cat_structure( 0 ),
		file_recipe_count( 0 )
{
	KConfig * config = kapp->config();
	config->setGroup( "Import" );

	direct = config->readBoolEntry( "DirectImport", false );
}

BaseImporter::~BaseImporter()
{
	delete m_recipe_list;
	delete m_cat_structure;
}

void BaseImporter::add( const RecipeList &recipe_list )
{
	file_recipe_count += recipe_list.count();

	for ( RecipeList::const_iterator it = recipe_list.begin(); it != recipe_list.end(); ++it ) {
		Recipe copy = *it;
		copy.recipeID = -1; //make sure an importer didn't give this a value
		m_recipe_list->append( copy );
	}
}

void BaseImporter::add( const Recipe &recipe )
{
	file_recipe_count++;
	Recipe copy = recipe;
	copy.recipeID = -1; //make sure an importer didn't give this a value

	if ( direct ) {
		if ( !m_progress_dialog->wasCancelled() ) {
			RecipeList list;
			list.append( recipe );
			importRecipes( list, m_database, m_progress_dialog );
		}
	}
	else
		m_recipe_list->append( copy );
}

void BaseImporter::parseFiles( const QStringList &filenames )
{
	if ( direct )
		m_filenames = filenames;
	else {
		for ( QStringList::const_iterator file_it = filenames.begin(); file_it != filenames.end(); ++file_it ) {
			file_recipe_count = 0;
			parseFile( *file_it );
			processMessages( *file_it );
		}
	}
}

void BaseImporter::import( RecipeDB *db, bool automatic )
{
	if ( direct ) {
		m_database = db;

		m_progress_dialog = new KProgressDialog( kapp->mainWidget(), 0,
			i18n( "Importing selected recipes" ), QString::null, true );
		KProgress *progress = m_progress_dialog->progressBar();
		progress->setPercentageVisible(false);
		progress->setTotalSteps( 0 );
	
		for ( QStringList::const_iterator file_it = m_filenames.begin(); file_it != m_filenames.end(); ++file_it ) {
			file_recipe_count = 0;
			parseFile( *file_it );
			processMessages( *file_it );
	
			if ( m_progress_dialog->wasCancelled() )
				break;
		}
		
		importUnitRatios( db );
		delete m_progress_dialog;
	}
	else {
		if ( m_recipe_list->count() == 0 )
			return;
	
		m_recipe_list->empty();
		//db->blockSignals(true);

		m_progress_dialog = new KProgressDialog( kapp->mainWidget(), 0,
			i18n( "Importing selected recipes" ), QString::null, true );
		KProgress *progress = m_progress_dialog->progressBar();
		progress->setTotalSteps( m_recipe_list->count() );
		progress->setFormat( i18n( "%v/%m Recipes" ) );

		if ( m_cat_structure ) {
			importCategoryStructure( db, m_cat_structure );
			delete m_cat_structure;
			m_cat_structure = 0;
		}
		importRecipes( *m_recipe_list, db, m_progress_dialog );
		importUnitRatios( db );
	
		//db->blockSignals(false);
		delete m_progress_dialog; m_progress_dialog = 0;
	}
}

void BaseImporter::importRecipes( RecipeList &selected_recipes, RecipeDB *db, KProgressDialog *progress_dialog )
{
	// Load Current Settings
	KConfig *config = kapp->config();
	config->setGroup( "Import" );
	bool overwrite = config->readBoolEntry( "OverwriteExisting", false );

	//cache some data we'll need
	int max_units_length = db->maxUnitNameLength();
	int max_group_length = db->maxIngGroupNameLength();

	RecipeList::iterator recipe_it; RecipeList::iterator recipe_list_end( selected_recipes.end() );
	RecipeList::iterator recipe_it_old = selected_recipes.end();
	for ( recipe_it = selected_recipes.begin(); recipe_it != recipe_list_end; ++recipe_it ) {
		if ( !direct ) {
			if ( progress_dialog->wasCancelled() ) {
				KMessageBox::information( kapp->mainWidget(), i18n( "All recipes up unto this point have been successfully imported." ) );
				//db->blockSignals(false);
				return ;
			}
		}

		if ( recipe_it_old != selected_recipes.end() )
			selected_recipes.remove( recipe_it_old );

		progress_dialog->setLabel( QString( i18n( "Importing recipe: %1" ) ).arg( ( *recipe_it ).title ) );
		progress_dialog->progressBar()->advance( 1 );
		kapp->processEvents();

		//add all recipe items (authors, ingredients, etc. to the database if they aren't already
		IngredientList::iterator ing_list_end( ( *recipe_it ).ingList.end() );
		for ( IngredientList::iterator ing_it = ( *recipe_it ).ingList.begin(); ing_it != ing_list_end; ++ing_it ) {
			if ( direct ) {
				progress_dialog->progressBar()->advance( 1 );
				kapp->processEvents();
			}

			//create ingredient groups
			QString real_group_name = ( *ing_it ).group.left( max_group_length );
			int new_group_id = db->findExistingIngredientGroupByName(real_group_name);
			if ( new_group_id == -1 ) {
				db->createNewIngGroup( real_group_name );
				new_group_id = db->lastInsertID();
			}
			( *ing_it ).groupID = new_group_id;

			int new_ing_id = db->findExistingIngredientByName((*ing_it).name);
			if ( new_ing_id == -1 && !(*ing_it).name.isEmpty() )
			{
				db->createNewIngredient( (*ing_it).name );
				new_ing_id = db->lastInsertID();
			}

			if ( direct ) {
				progress_dialog->progressBar()->advance( 1 );
				kapp->processEvents();
			}

			Unit real_unit( ( *ing_it ).units.name.left( max_units_length ), ( *ing_it ).units.plural.left( max_units_length ) );
			if ( real_unit.name.isEmpty() )
				real_unit.name = real_unit.plural;
			else if ( real_unit.plural.isEmpty() )
				real_unit.plural = real_unit.name;

			int new_unit_id = db->findExistingUnitByName(real_unit.name);
			if ( new_unit_id == -1 ) {
				db->createNewUnit( real_unit.name, real_unit.plural );
				new_unit_id = db->lastInsertID();
			}

			if ( direct ) {
				progress_dialog->progressBar()->advance( 1 );
				kapp->processEvents();
			}

			if ( ( *ing_it ).prepMethodList.count() > 0 ) {
				for ( ElementList::iterator prep_it = ( *ing_it ).prepMethodList.begin(); prep_it != ( *ing_it ).prepMethodList.end(); ++prep_it ) {
					int new_prep_id = db->findExistingPrepByName((*prep_it).name);
					if ( new_prep_id == -1 ) {
						db->createNewPrepMethod((*prep_it).name);
						new_prep_id = db->lastInsertID();
					}
					(*prep_it).id = new_prep_id;
				}
			}

			( *ing_it ).unitID = new_unit_id;
			( *ing_it ).ingredientID = new_ing_id;

			ElementList unitsWithIng;
			db->findExistingUnitsByName( ( *ing_it ).units.name, new_ing_id, &unitsWithIng );
			db->findExistingUnitsByName( ( *ing_it ).units.plural, new_ing_id, &unitsWithIng );

			if ( !unitsWithIng.containsId( new_unit_id ) )
				db->addUnitToIngredient( new_ing_id, new_unit_id );
		}

		ElementList::iterator author_list_end( ( *recipe_it ).authorList.end() );
		for ( ElementList::iterator author_it = ( *recipe_it ).authorList.begin(); author_it != author_list_end; ++author_it ) {
			if ( direct ) {
				progress_dialog->progressBar()->advance( 1 );
				kapp->processEvents();
			}

			int new_author_id = db->findExistingAuthorByName(( *author_it ).name);
			if ( new_author_id == -1 && !( *author_it ).name.isEmpty() ) {
				db->createNewAuthor( ( *author_it ).name );
				new_author_id = db->lastInsertID();
			}

			( *author_it ).id = new_author_id;
		}

		ElementList::iterator cat_list_end( ( *recipe_it ).categoryList.end() );
		for ( ElementList::iterator cat_it = ( *recipe_it ).categoryList.begin(); cat_it != cat_list_end; ++cat_it ) {
			if ( direct ) {
				progress_dialog->progressBar()->advance( 1 );
				kapp->processEvents();
			}

			int new_cat_id = db->findExistingCategoryByName(( *cat_it ).name);
			if ( new_cat_id == -1 && !( *cat_it ).name.isEmpty() ) {
				db->createNewCategory( ( *cat_it ).name );
				new_cat_id = db->lastInsertID();
			}

			( *cat_it ).id = new_cat_id;
		}

		if ( !(*recipe_it).yield.type.isEmpty() ) {
			int new_id = db->findExistingYieldTypeByName((*recipe_it).yield.type);
			if ( new_id == -1 ) {
				db->createNewYieldType( (*recipe_it).yield.type );
				new_id = db->lastInsertID();
			}
			(*recipe_it).yield.type_id = new_id;
		}

		RatingList::iterator rating_list_end( ( *recipe_it ).ratingList.end() );
		for ( RatingList::iterator rating_it = ( *recipe_it ).ratingList.begin(); rating_it != rating_list_end; ++rating_it ) {
			if ( direct ) {
				progress_dialog->progressBar()->advance( 1 );
				kapp->processEvents();
			}

			for ( RatingCriteriaList::iterator rc_it = (*rating_it).ratingCriteriaList.begin(); rc_it != (*rating_it).ratingCriteriaList.end(); ++rc_it ) {
				int new_criteria_id = db->findExistingRatingByName(( *rc_it ).name);
				if ( new_criteria_id == -1 && !( *rc_it ).name.isEmpty() ) {
					db->createNewRating( ( *rc_it ).name );
					new_criteria_id = db->lastInsertID();
				}
	
				( *rc_it ).id = new_criteria_id;
			}
		}

		if ( overwrite )  //overwrite existing
			( *recipe_it ).recipeID = db->findExistingRecipeByName( ( *recipe_it ).title );
		else //rename
			( *recipe_it ).title = db->getUniqueRecipeTitle( ( *recipe_it ).title );

		if ( direct ) {
			progress_dialog->progressBar()->advance( 1 );
			kapp->processEvents();
		}

		//save into the database
		db->saveRecipe( &( *recipe_it ) );

		recipe_it_old = recipe_it; //store to delete once we've got the next recipe
	}
}

void BaseImporter::setCategoryStructure( CategoryTree *cat_structure )
{
	if ( direct ) {
		importCategoryStructure( m_database, cat_structure );
	}
	else {
		delete m_cat_structure;
		m_cat_structure = cat_structure;
	}
}

void BaseImporter::importCategoryStructure( RecipeDB *db, const CategoryTree *categoryTree )
{
	for ( CategoryTree * child_it = categoryTree->firstChild(); child_it; child_it = child_it->nextSibling() ) {
		int new_cat_id = db->findExistingCategoryByName( child_it->category.name );
		if ( new_cat_id == -1 ) {
			db->createNewCategory( child_it->category.name, categoryTree->category.id );
			new_cat_id = db->lastInsertID();
		}

		child_it->category.id = new_cat_id;

		importCategoryStructure( db, child_it );
	}
}

void BaseImporter::setUnitRatioInfo( UnitRatioList &ratioList, UnitList &unitList )
{
	m_ratioList = ratioList;
	m_unitList = unitList;
}

void BaseImporter::importUnitRatios( RecipeDB *db )
{
	for ( UnitRatioList::const_iterator it = m_ratioList.begin(); it != m_ratioList.end(); ++it ) {
		QString unitName1, unitName2;
		for ( UnitList::const_iterator unit_it = m_unitList.begin(); unit_it != m_unitList.end(); ++unit_it ) {
			if ( ( *it ).uID1 == ( *unit_it ).id ) {
				unitName1 = ( *unit_it ).name;
				if ( !unitName2.isNull() )
					break;
			}
			else if ( ( *it ).uID2 == ( *unit_it ).id ) {
				unitName2 = ( *unit_it ).name;
				if ( !unitName1.isNull() )
					break;
			}
		}

		int unitId1 = db->findExistingUnitByName( unitName1 );
		int unitId2 = db->findExistingUnitByName( unitName2 );

		//the unit needed for the ratio may not have been added, because the
		//recipes chosen did not include the unit
		if ( unitId1 != -1 && unitId2 != -1 ) {
			UnitRatio ratio;
			ratio.uID1 = unitId1;
			ratio.uID2 = unitId2;
			ratio.ratio = ( *it ).ratio;
			db->saveUnitRatio( &ratio );
		}
	}
}

void BaseImporter::processMessages( const QString &file )
{
	if ( m_error_msgs.count() > 0 ) {
		//<!doc> ensures it is detected as RichText
		m_master_error += QString( i18n( "<!doc>Import of recipes from the file <b>\"%1\"</b> <b>failed</b> due to the following error(s):" ) ).arg( file );
		m_master_error += "<ul><li>" + m_error_msgs.join( "</li><li>" ) + "</li></ul>";

		m_error_msgs.clear();
	}
	else if ( m_warning_msgs.count() > 0 ) {
		m_master_warning += QString( i18n( "The file <b>%1</b> generated the following warning(s):" ) ).arg( file );
		m_master_warning += "<ul><li>" + m_warning_msgs.join( "</li><li>" ) + "</li></ul>";

		m_warning_msgs.clear();
	}
}
