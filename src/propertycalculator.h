/***************************************************************************
 *   Copyright (C) 2003 by Unai Garro                                      *
 *   ugarro@users.sourceforge.net                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/


 #include <qptrlist.h>
 #include <DBBackend/recipedb.h>
 #include "elementlist.h"
 #include "ingredientpropertylist.h"
 #include "recipe.h"

int autoConvert(RecipeDB *database,double amount1,int unit1,double amount2,int unit2, double &newAmount, int &newID);
void calculateProperties(Recipe* recipe,RecipeDB* database,IngredientPropertyList *recipePropertyList);
void addPropertyToList(RecipeDB *database,IngredientPropertyList *recipePropertyList,IngredientPropertyList &ingPropertyList,Ingredient &ing);
