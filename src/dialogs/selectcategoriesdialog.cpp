/***************************************************************************
 *   Copyright (C) 2003 by                                                 *
 *   Unai Garro (ugarro@users.sourceforge.net)                             *
 *   Cyril Bosselut (bosselut@b1project.com)                               *
 *   Jason Kivlighn (mizunoami44@users.sourceforge.net)                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "selectcategoriesdialog.h"
#include "createelementdialog.h"

#include <klocale.h>
#include <kdebug.h>

#include "datablocks/categorytree.h"
#include "DBBackend/recipedb.h"

class CategoryListItem:public QCheckListItem{
public:
	CategoryListItem(QListView* qlv, const Element &el ):QCheckListItem(qlv,QString::null,QCheckListItem::CheckBox),elStored(el){}
	CategoryListItem(CategoryListItem* cli, const Element &el ):QCheckListItem(cli,QString::null,QCheckListItem::CheckBox),elStored(el){}
	Element element() const { return elStored; }

private:
	const Element elStored;

public:
	virtual QString text(int column) const
		{
		if (column==1) return(elStored.name);
		else return(QString::null);
		}

protected:
	virtual void stateChange(bool on)
	{
		if ( on )
		{
			CategoryListItem *cat_it;
			for ( cat_it = (CategoryListItem*)parent(); cat_it; cat_it = (CategoryListItem*)cat_it->parent() )
				 cat_it->setOn(false);

			QListViewItemIterator it( firstChild() );
			while ( it.current() ) {
				cat_it = (CategoryListItem*)it.current();
				cat_it->setOn(false);
				++it;
			}
		}
	}
};

SelectCategoriesDialog::SelectCategoriesDialog(QWidget *parent, const CategoryTree *categoryTree,const QMap<Element,bool> &selected, RecipeDB *db):QDialog(parent,0,true)
{

// Store pointer
database = db;

//Design UI

layout = new QGridLayout( this, 1, 1, 0, 0);

	// Border Spacers
	QSpacerItem* spacer_left = new QSpacerItem( 10,10, QSizePolicy::Fixed, QSizePolicy::Minimum );	layout->addItem( spacer_left, 1,0 );
	QSpacerItem* spacer_top = new QSpacerItem( 10,10, QSizePolicy::Minimum, QSizePolicy::Fixed );
	layout->addItem(spacer_top,0,1);

//Category List
categoryListView=new KListView(this);
categoryListView->addColumn("*");
categoryListView->addColumn(i18n("Category"));
categoryListView->setAllColumnsShowFocus(true);
categoryListView->setRootIsDecorated(true);
layout->addMultiCellWidget(categoryListView,1,1,1,3);

//New category button
QSpacerItem* catButtonSpacer=new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Fixed);
layout->addItem(catButtonSpacer,2,1);

QPushButton *newCatButton = new QPushButton(this);
newCatButton->setText(i18n("&New Category..."));
newCatButton->setFlat(true);
layout->addMultiCellWidget(newCatButton,3,3,1,3);

//Ok/Cancel buttons
QSpacerItem* buttonsSpacer=new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Fixed);
layout->addItem(buttonsSpacer,4,1);

okButton=new QPushButton(this);
okButton->setText(i18n("&OK"));
okButton->setFlat(true);
okButton->setDefault(true);
layout->addWidget(okButton,5,1);

QSpacerItem* spacerBetweenButtons=new QSpacerItem(10,10, QSizePolicy::Fixed, QSizePolicy::Minimum);
layout->addItem(spacerBetweenButtons,5,2);

cancelButton=new QPushButton(this);
cancelButton->setText(i18n("&Cancel"));
cancelButton->setFlat(true);
layout->addWidget(cancelButton,5,3);

// Load the list
loadCategories(categoryTree,selected);

// Connect signals & Slots
connect (newCatButton,SIGNAL(clicked()),SLOT(createNewCategory()));
connect (okButton,SIGNAL(clicked()),this,SLOT(accept()));
connect (cancelButton,SIGNAL(clicked()),this,SLOT(reject()));

}

SelectCategoriesDialog::~SelectCategoriesDialog()
{
}

void SelectCategoriesDialog::getSelectedCategories(ElementList *newSelected,CategoryListItem *parent)
{
CategoryListItem *it;
if ( parent == 0 )
	it = (CategoryListItem*)categoryListView->firstChild();
else
	it = (CategoryListItem*)parent->firstChild();

for (;it; it=(CategoryListItem *) it->nextSibling())
	{
	if (it->isOn()) newSelected->append(it->element()); // If checked, add
	
	getSelectedCategories(newSelected,it);
	}
}

void SelectCategoriesDialog::loadCategories(const CategoryTree *categoryTree, const QMap<Element,bool> &selected, CategoryListItem *parent )
{
	const CategoryTreeChildren *children = categoryTree->children();
	for ( CategoryTreeChildren::const_iterator child_it = children->begin(); child_it != children->end(); ++child_it )
	{
		const CategoryTree *node = *child_it;
		
		CategoryListItem *new_item;
		if ( parent == 0 )
			new_item = new CategoryListItem(categoryListView,node->category);
		else
			new_item = new CategoryListItem(parent,node->category);
		
		new_item->setOn(selected[node->category]);
		new_item->setOpen(true);
		loadCategories( node, selected, new_item );
	}
}

void SelectCategoriesDialog::createNewCategory(void)
{
	CreateElementDialog* elementDialog=new CreateElementDialog(this,i18n("New Category"));

	if ( elementDialog->exec() == QDialog::Accepted )
	{
		QString result = elementDialog->newElementName();
		
		int parent_id = -1;
		if ( CategoryListItem *current = (CategoryListItem*)categoryListView->selectedItem() )
			parent_id = current->element().id;
		
		database->createNewCategory(result,parent_id); // Create the new category in the database
		
		Element new_cat(result,database->lastInsertID());
		
		CategoryListItem *it;
		if ( parent_id == -1 )
			it = new CategoryListItem(categoryListView,new_cat);
		else
			it = new CategoryListItem((CategoryListItem*)categoryListView->selectedItem(),new_cat);
		it->setOn(true);
	}
	
	delete elementDialog;
}


#include "selectcategoriesdialog.moc"
