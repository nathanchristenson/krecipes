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

#include "psqlrecipedb.h"

#include <kmdcodec.h>
#include <kdebug.h>
#include <kstandarddirs.h>
#include <ktempfile.h>
#include <klocale.h>

//Note: PostgreSQL's database names are always lowercase
PSqlRecipeDB::PSqlRecipeDB(QString host, QString user, QString pass, QString DBname):QSqlRecipeDB(host, user,pass,DBname.lower())
{
}

PSqlRecipeDB::~PSqlRecipeDB()
{
}

void PSqlRecipeDB::createDB()
{
QString real_db_name = database->databaseName();

//we have to be connected to some database in order to create the Krecipes database
//so long as the permissions given are allowed access to "template1', this works
database->setDatabaseName("template1");
if ( database->open() ) {
	QSqlQuery query(QString("CREATE DATABASE %1").arg(real_db_name),database);
	if ( !query.isActive() )
		kdDebug()<<"create query failed: "<<database->lastError().databaseText()<<endl;
	
	database->close();
}
else
	kdDebug()<<"create open failed: "<<database->lastError().databaseText()<<endl;

database->setDatabaseName(real_db_name);
}

void PSqlRecipeDB::initializeDB(void)
{
}

void PSqlRecipeDB::initializeData(void)
{
QSqlQuery initializeQuery(QString::null,database);

//

// Populate with data

	QString commands;
	// Read the commands form the data file
	QFile datafile(KGlobal::dirs()->findResource("appdata", "data/mysqldata.sql"));
	if ( datafile.open( IO_ReadOnly ) ) {
	QTextStream stream( &datafile );
     	commands=stream.read();
     	datafile.close();
 	}


	// Split commands
	QStringList commandList;
	splitCommands(commands,commandList);

	// Execute commands
	for ( QStringList::Iterator it = commandList.begin(); it != commandList.end(); ++it )
	 {
	 initializeQuery.exec((*it)+QString(";")); //Split removes the semicolons
	 }

}

void PSqlRecipeDB::createTable(QString tableName)
{

QStringList commands;

if (tableName=="recipes") commands<<"CREATE TABLE recipes (id SERIAL NOT NULL PRIMARY KEY,title CHARACTER VARYING,persons INTEGER,instructions TEXT, photo TEXT, prep_time TIME);";

else if (tableName=="ingredients") commands<<"CREATE TABLE ingredients (id SERIAL NOT NULL PRIMARY KEY, name CHARACTER VARYING);";

else if (tableName=="ingredient_list") { 
commands<<"CREATE TABLE ingredient_list (recipe_id INTEGER, ingredient_id INTEGER, amount FLOAT, unit_id INTEGER, prep_method_id INTEGER, order_index INTEGER);";
commands<<"CREATE INDEX ridil_index ON ingredient_list USING BTREE (recipe_id);";
commands<<"CREATE INDEX iidil_index ON ingredient_list USING BTREE (ingredient_id);";
}

else if (tableName=="unit_list") commands<<"CREATE TABLE unit_list (ingredient_id INTEGER, unit_id INTEGER);";

else if (tableName== "units") commands<<"CREATE TABLE units (id SERIAL NOT NULL PRIMARY KEY, name CHARACTER VARYING);";

else if (tableName== "prep_methods") commands<<"CREATE TABLE prep_methods (id SERIAL NOT NULL PRIMARY KEY, name CHARACTER VARYING);";

else if  (tableName=="ingredient_info") commands<<"CREATE TABLE ingredient_info (ingredient_id INTEGER, property_id INTEGER, amount FLOAT, per_units INTEGER);";

else if (tableName=="ingredient_properties") commands<<"CREATE TABLE ingredient_properties (id SERIAL NOT NULL,name CHARACTER VARYING, units CHARACTER VARYING);";

else if (tableName=="units_conversion") commands<<"CREATE TABLE units_conversion (unit1_id INTEGER, unit2_id INTEGER, ratio FLOAT);";

else if (tableName=="categories") commands<<"CREATE TABLE categories (id SERIAL NOT NULL PRIMARY KEY, name CHARACTER VARYING default NULL, parent_id INTEGER NOT NULL default -1);";

else if (tableName=="category_list") {
commands<<"CREATE TABLE category_list (recipe_id INTEGER NOT NULL,category_id INTEGER NOT NULL);";
commands<<"CREATE INDEX rid_index ON category_list USING BTREE (recipe_id);";
commands<<"CREATE INDEX cid_index ON category_list USING BTREE (category_id);";
}

else if (tableName=="authors") commands<<"CREATE TABLE authors (id SERIAL NOT NULL PRIMARY KEY, name CHARACTER VARYING default NULL);";

else if (tableName=="author_list") commands<<"CREATE TABLE author_list (recipe_id INTEGER NOT NULL,author_id INTEGER NOT NULL);";

else if (tableName=="db_info") {
commands<<"CREATE TABLE db_info (ver FLOAT NOT NULL,generated_by CHARACTER VARYING default NULL);";
commands<<"INSERT INTO db_info VALUES(0.61,'Krecipes 0.6');";
}

else return;

QSqlQuery databaseToCreate(QString::null,database);

 // execute the queries
for ( QStringList::const_iterator it = commands.begin(); it != commands.end(); ++it )
	databaseToCreate.exec(*it);
}

void PSqlRecipeDB::portOldDatabases(float version)
{
kdDebug()<<"Current database version is..."<<version<<"\n";
QString command;

if ( version < 0.7 ) {
	//version added
}

}

int PSqlRecipeDB::lastInsertID()
{
	return last_insert_id;
}

int PSqlRecipeDB::getNextInsertID( const QString &table, const QString &column )
{
	QString command = QString("SELECT nextval('%1_%2_seq');").arg(table).arg(column);
	QSqlQuery getID(command,database);

	if (getID.isActive() && getID.first()) {
		last_insert_id = getID.value(0).toInt();
	}
	else
		last_insert_id = -1;
	
	return last_insert_id;
}

void PSqlRecipeDB::storePhoto(int recipeID, const QByteArray &data )
{
	QSqlQuery query(QString::null,database);
	
	query.prepare("UPDATE recipes SET photo=? WHERE id="+QString::number(recipeID));
	query.addBindValue(KCodecs::base64Encode(data));
	query.exec();
}

void PSqlRecipeDB::loadPhoto(int recipeID, QPixmap &photo)
{
	QString command = QString("SELECT photo FROM recipes WHERE id=%1;").arg(recipeID);
	QSqlQuery query(command,database);

	if ( query.isActive() && query.first() ) {
		QCString decodedPic;
		QPixmap pix;
		KCodecs::base64Decode(QCString(query.value(0).toString().latin1()), decodedPic);
		int len = decodedPic.size();
		QByteArray picData(len);
		memcpy(picData.data(),decodedPic.data(),len);

		bool ok = pix.loadFromData(picData, "JPEG");
		if (ok) photo = pix;
	}
}

#include "psqlrecipedb.moc"
