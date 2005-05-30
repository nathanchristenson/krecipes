/***************************************************************************
*   Copyright (C) 2004 by                                                 *
*   Jason Kivlighn (mizunoami44@users.sourceforge.net)                    *
*   Unai Garro (ugarro@users.sourceforge.net)                             *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/

#include "recipelistview.h"

#include <qintdict.h>
#include <qdatastream.h>

#include <kdebug.h>
#include <kconfig.h>
#include <kglobal.h>
#include <klocale.h>
#include <kiconloader.h>

#include "backends/recipedb.h"


class UncategorizedItem : public QListViewItem
{
public:
	UncategorizedItem( QListView *lv ) : QListViewItem( lv, i18n("Uncategorized") ){}
	int rtti() const { return 1006; }
};

RecipeItemDrag::RecipeItemDrag( RecipeListItem *recipeItem, QWidget *dragSource, const char *name )
		: QStoredDrag( RECIPEITEMMIMETYPE, dragSource, name )
{
	if ( recipeItem ) {
		QByteArray data;
		QDataStream out( data, IO_WriteOnly );
		out << recipeItem->recipeID();
		out << recipeItem->title();
		setEncodedData( data );
	}
}

bool RecipeItemDrag::canDecode( QMimeSource* e )
{
	return e->provides( RECIPEITEMMIMETYPE );
}

bool RecipeItemDrag::decode( const QMimeSource* e, RecipeListItem& item )
{
	if ( !e )
		return false;

	QByteArray data = e->encodedData( RECIPEITEMMIMETYPE );
	if ( data.isEmpty() )
		return false;

	QString title;
	int recipeID;
	QDataStream in( data, IO_ReadOnly );
	in >> recipeID;
	in >> title;

	item.setTitle( title );
	item.setRecipeID( recipeID );

	return true;
}


RecipeListView::RecipeListView( QWidget *parent, RecipeDB *db ) : StdCategoryListView( parent, db ),
		flat_list( false ),
		m_uncat_item(0)
{
	connect( database, SIGNAL( recipeCreated( const Element &, const ElementList & ) ), SLOT( createRecipe( const Element &, const ElementList & ) ) );
	connect( database, SIGNAL( recipeRemoved( int ) ), SLOT( removeRecipe( int ) ) );
	connect( database, SIGNAL( recipeRemoved( int, int ) ), SLOT( removeRecipe( int, int ) ) );
	connect( database, SIGNAL( recipeModified( const Element &, const ElementList & ) ), SLOT( modifyRecipe( const Element &, const ElementList & ) ) );

	setColumnText( 0, i18n( "Recipe" ) );

	KConfig *config = KGlobal::config(); config->setGroup( "Performance" );
	curr_limit = config->readNumEntry("CategoryLimit",-1);

	KIconLoader il;
	setPixmap( il.loadIcon( "categories", KIcon::NoGroup, 16 ) );
}

QDragObject *RecipeListView::dragObject()
{
	RecipeListItem * item = dynamic_cast<RecipeListItem*>( selectedItem() );
	if ( item != 0 ) {
		RecipeItemDrag * obj = new RecipeItemDrag( item, this, "Recipe drag item" );
		/*const QPixmap *pm = item->pixmap(0);
		if( pm )
			obj->setPixmap( *pm );*/ 
		return obj;
	}
	return 0;
}

bool RecipeListView::acceptDrag( QDropEvent *event ) const
{
	return RecipeItemDrag::canDecode( event );
}

void RecipeListView::load(int limit, int offset)
{
	m_uncat_item = 0;

	if ( flat_list ) {
		ElementList recipeList;
		database->loadRecipeList( &recipeList );

		ElementList::const_iterator recipe_it;
		for ( recipe_it = recipeList.begin();recipe_it != recipeList.end();++recipe_it ) {
			Recipe recipe;
			recipe.recipeID = ( *recipe_it ).id;
			recipe.title = ( *recipe_it ).name;
			createRecipe( recipe, -1 );
		}
	}
	else {
		StdCategoryListView::load(limit,offset);

		if ( offset == 0 ) {
			ElementList recipeList;
			database->loadUncategorizedRecipes( &recipeList );

			ElementList::const_iterator recipe_it;
			for ( recipe_it = recipeList.begin();recipe_it != recipeList.end();++recipe_it ) {
				Recipe recipe;
				recipe.recipeID = ( *recipe_it ).id;
				recipe.title = ( *recipe_it ).name;
				createRecipe( recipe, -1 );
			}
		}
	}
}

void RecipeListView::populate( QListViewItem *item )
{
	StdCategoryListView::populate(item);

	if ( !flat_list ) {
		if ( item->firstChild() && item->firstChild()->rtti() == RECIPELISTITEM_RTTI ) return;

		CategoryItemInfo *cat_item; //note: we can't go straight from QListViewItem -> CategoryInfoItem
		if ( item->rtti() == CATEGORYLISTITEM_RTTI )
			cat_item = (CategoryListItem*)item;
		else if ( item->rtti() == CATEGORYCHECKLISTITEM_RTTI )
			cat_item = (CategoryCheckListItem*)item;
		else
			return;
		int id = cat_item->categoryId();

		// Now show the recipes
		ElementList recipeList;
		database->loadRecipeList( &recipeList, id );

		ElementList::const_iterator recipe_it;
		for ( recipe_it = recipeList.begin(); recipe_it != recipeList.end(); ++recipe_it ) {
			Recipe recipe;
			recipe.recipeID = ( *recipe_it ).id;
			recipe.title = ( *recipe_it ).name;
			createRecipe( recipe, id );
		}
	}
}

void RecipeListView::populateAll( QListViewItem *parent )
{
	if ( !parent )
		parent = firstChild();
	else {
		populate( parent );
		parent = parent->firstChild();
	}

	for ( QListViewItem *item = parent; item; item = item->nextSibling() ) {
		populateAll( item );
	}
}

void RecipeListView::createRecipe( const Recipe &recipe, int parent_id )
{
	if ( parent_id == -1 ) {
		if ( !m_uncat_item && curr_offset == 0 )
			m_uncat_item = new UncategorizedItem(this);

		if ( m_uncat_item )
			( void ) new RecipeListItem( m_uncat_item, recipe );
	}
	else {
		CategoryListItem *parent = items_map[ parent_id ];
		if ( parent && parent->isPopulated() )
			( void ) new RecipeListItem( parent, recipe );
	}
}

void RecipeListView::createRecipe( const Element &recipe_el, const ElementList &categories )
{
	Recipe recipe;
	recipe.recipeID = recipe_el.id;
	recipe.title = recipe_el.name;

	if ( categories.count() == 0 ) {
		createRecipe( recipe, -1 );
	}
	else {
		for ( ElementList::const_iterator cat_it = categories.begin(); cat_it != categories.end(); ++cat_it ) {
			int cur_cat_id = ( *cat_it ).id;

			QListViewItemIterator iterator( this );
			while ( iterator.current() ) {
				if ( iterator.current() ->rtti() == 1001 ) {
					CategoryListItem * cat_item = ( CategoryListItem* ) iterator.current();
					if ( cat_item->categoryId() == cur_cat_id ) {
						createRecipe( recipe, cur_cat_id );
					}
				}
				++iterator;
			}
		}
	}
}

void RecipeListView::modifyRecipe( const Element &recipe, const ElementList &categories )
{
	removeRecipe( recipe.id );
	createRecipe( recipe, categories );
}

void RecipeListView::removeRecipe( int id )
{
	QListViewItemIterator iterator( this );
	while ( iterator.current() ) {
		if ( iterator.current() ->rtti() == 1000 ) {
			RecipeListItem * recipe_it = ( RecipeListItem* ) iterator.current();
			if ( recipe_it->recipeID() == id )
				delete recipe_it;
		}
		++iterator;
	}
}

void RecipeListView::removeRecipe( int recipe_id, int cat_id )
{
	QListViewItem * item = items_map[ cat_id ];

	//find out if this is the only category the recipe belongs to
	int finds = 0;
	QListViewItemIterator iterator( this );
	while ( iterator.current() ) {
		if ( iterator.current() ->rtti() == 1000 ) {
			RecipeListItem * recipe_it = ( RecipeListItem* ) iterator.current();

			if ( recipe_it->recipeID() == recipe_id ) {
				if ( finds > 1 )
					break;
				finds++;
			}
		}
		++iterator;
	}

	//do this to only iterate over children of 'item'
	QListViewItem *pEndItem = NULL;
	QListViewItem *pStartItem = item;
	do {
		if ( pStartItem->nextSibling() )
			pEndItem = pStartItem->nextSibling();
		else
			pStartItem = pStartItem->parent();
	}
	while ( pStartItem && !pEndItem );

	iterator = QListViewItemIterator( item );
	while ( iterator.current() != pEndItem ) {
		if ( iterator.current() ->rtti() == 1000 ) {
			RecipeListItem * recipe_it = ( RecipeListItem* ) iterator.current();

			if ( recipe_it->recipeID() == recipe_id ) {
				if ( finds > 1 ) {
					delete recipe_it;
				}
				else {
					//the item is now uncategorized
					recipe_it->parent() ->takeItem( recipe_it );
					if ( !m_uncat_item && curr_offset == 0 )
						m_uncat_item = new UncategorizedItem(this);
					if ( m_uncat_item )
						m_uncat_item->insertItem( recipe_it );
				}
				break;
			}
		}
		++iterator;
	}
}

void RecipeListView::removeCategory( int id )
{
	QListViewItem * item = items_map[ id ];
	if ( !item )
		return ; //this may have been deleted already by its parent being deleted

	moveChildrenToRoot( item );

	StdCategoryListView::removeCategory( id );
}

void RecipeListView::moveChildrenToRoot( QListViewItem *item )
{
	QListViewItem * next_sibling;
	for ( QListViewItem * it = item->firstChild(); it; it = next_sibling ) {
		next_sibling = it->nextSibling();
		if ( it->rtti() == 1000 ) {
			//the item is now uncategorized
			it->parent() ->takeItem( it );
			if ( !m_uncat_item && curr_offset == 0 )
				m_uncat_item = new UncategorizedItem(this);
			if ( m_uncat_item )
				m_uncat_item->insertItem( it );
		}
		moveChildrenToRoot( it );
	}
}

#include "recipelistview.moc"
