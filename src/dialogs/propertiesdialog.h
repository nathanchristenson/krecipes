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

#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <qlayout.h>
#include <qpushbutton.h>
#include <qvbox.h>
#include <klistview.h>

class RecipeDB;
class StdPropertyListView;

/**
@author Unai Garro
*/
class PropertiesDialog: public QWidget
{
	Q_OBJECT
public:
	PropertiesDialog( QWidget *parent, RecipeDB *db );
	~PropertiesDialog();
	void reload( void );

private:
	// Variables
	RecipeDB *database;

	// Widgets
	QGridLayout* layout;
	QPushButton* addPropertyButton;
	QPushButton* removePropertyButton;
	StdPropertyListView* propertyListView;

};

#endif
