/***************************************************************************
*   Copyright © 2015 José Manuel Santamaría Lema <panfaust@gmail.com>      *
*                                                                          *
*   This program is free software; you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by   *
*   the Free Software Foundation; either version 2 of the License, or      *
*   (at your option) any later version.                                    *
****************************************************************************/

#ifndef KREINGREDIENTACTIONSHANDLER_H
#define KREINGREDIENTACTIONSHANDLER_H

#include "actionshandlers/kregenericactionshandler.h"

class KreGenericListWidget;
class RecipeDB;

class KreIngredientActionsHandler : public KreGenericActionsHandler
{
Q_OBJECT

public:
	KreIngredientActionsHandler( KreGenericListWidget * listwidget, RecipeDB *db );
	~KreIngredientActionsHandler() {}

public slots:
	void createNew();
	void remove();

protected slots:
	virtual void saveElement( const QModelIndex & topLeft, 
		const QModelIndex & bottomRight );

private:
	bool checkBounds( const QString &name );

};

#endif //KREINGREDIENTACTIONSHANDLER_H

