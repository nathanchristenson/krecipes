/***************************************************************************
 *   Copyright (C) 2003 by Unai Garro                                      *
 *   uga@ee.ed.ac.uk                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "recipeviewdialog.h"

RecipeViewDialog::RecipeViewDialog(QWidget *parent, RecipeDB *db, int recipeID):QVBox(parent)
{

// Initialize UI Elements
recipeView=new KHTMLPart(this);

// Store/Initialize local variables
database=db; // Store the database pointer.
loadedRecipe=new Recipe();

//------------------ Show the recipe --------
QString recipeHTML;



// Create HTML Code
if (recipeID<0)
{
// Show default (empty) recipe
recipeHTML="<html><head><title>Title of the Recipe</title></head><body>";
recipeHTML+="<div STYLE=\"position: absolute; top: 30px; left:1%; width: 22%\"> <li>Ingredient 1</li>";
recipeHTML+="<li>Ingredient 2</li> <li>Ingredient 3</li> </div>";
recipeHTML+="<div STYLE=\"position: absolute; top: 30px; left:25%; width: 74%\">";
recipeHTML+="<center><h1>Title of the Recipe</h1></center>";
recipeHTML+="<p>Recipe Instructions </p></div></body></html>";
}
else
{
// Load the recipe and format as HTML code
loadRecipe (recipeID);
// title (not shown)
recipeHTML= QString("<html><head><title>%1</title></head><body>").arg( loadedRecipe->title);
// Ingredient Block
recipeHTML+="<div STYLE=\"position: absolute; top: 250px; left:1%; width: 220px; background-color: #D4A143\">";
    //Ingredients
    Ingredient * ing;
    for ( ing = loadedRecipe->ingList.getFirst(); ing; ing = loadedRecipe->ingList.getNext() )
       {
       recipeHTML+=QString("<li>%2 %3  %1</li>")
			    .arg(ing->name)
			    .arg(ing->amount)
			    .arg(ing->units);
       }
recipeHTML+="</div>";


// Instructions Block
recipeHTML+="<div STYLE=\"margin-left: 240px;margin-right: 1%;margin-top: 80px\">";
recipeHTML+=QString("<center><h1>%1</h1></center>").arg(loadedRecipe->title);
recipeHTML+=QString("<p>%1</p></div>").arg(loadedRecipe->instructions);

// Photo Block

recipeHTML+="<div STYLE=\"position: absolute; top: 50px; left:1%; width: 220px; height: 165px; border: solid #000000 1px \">";
recipeHTML+=QString("<img src=\"/tmp/krecipes_photo.png\" width=220px height=165px> </div>");

// Header

recipeHTML+="<div STYLE=\"position: absolute; top: 5px; left:1%; width: 98%; height:30px; background-color: #EDD89E\">";
recipeHTML+=QString("<p align=right >Recipe: #%1</p></div>").arg(recipeID);

// Close HTML
recipeHTML+="</body></html>";

// Store Photo
loadedRecipe->photo.save("/tmp/krecipes_photo.png","PNG");
}

recipeView->begin(KURL("file:/tmp/" )); // Initialize to /tmp, where the photo was stored
recipeView->write(recipeHTML);
recipeView->end();

 }

RecipeViewDialog::~RecipeViewDialog()
{
}

void RecipeViewDialog::loadRecipe(int recipeID)
{

// Load specified Recipe ID

database->loadRecipe(loadedRecipe,recipeID);

}
