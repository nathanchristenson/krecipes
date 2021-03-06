/***************************************************************************
*   Copyright © 2003-2005 Unai Garro <ugarro@gmail.com>                   *
*   Copyright © 2003-2005 Cyril Bosselut <bosselut@b1project.com>         *
*   Copyright © 2003-2005 Jason Kivlighn <jkivlighn@gmail.com>            *
*   Copyright © 2016 José Manuel Santamaría Lema <panfaust@gmail.com>     *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/

#include "ratingdisplaywidget.h"

#include "datablocks/rating.h"

RatingDisplayWidget::RatingDisplayWidget( QWidget *parent ) 
	: QWidget( parent )
{
	ui = new Ui::RatingDisplayWidget;
	ui->setupUi( this );
	connect( ui->buttonEdit, SIGNAL(clicked()),
		this, SIGNAL(editButtonClicked()) );
	connect( ui->buttonRemove, SIGNAL(clicked()),
		this, SIGNAL(removeButtonClicked()) );
}

void RatingDisplayWidget::displayRating( const Rating & rating )
{
	//Set the icon
	int average = qRound(rating.average());
	if ( average >= 0 )
		ui->iconLabel->setPixmap( UserIcon(QString("rating%1").arg(average) ) );
	else //no rating criteria, therefore no average (we don't want to automatically assume a zero average)
		ui->iconLabel->clear();

	//Set the name and comment texts
	ui->raterName->setText(rating.rater());
	ui->comment->setText(rating.comment());

	//Set the list of criteria, stars
	ui->criteriaTreeWidget->clear();
	foreach ( RatingCriteria rc, rating.ratingCriterias() ) {
		QTreeWidgetItem * item = new QTreeWidgetItem;
		item->setData( 0, Qt::DisplayRole, rc.name() );
		item->setData( 1, Qt::DecorationRole, Rating::starsPixmap(rc.stars()) );
		ui->criteriaTreeWidget->addTopLevelItem( item );
	}

}
