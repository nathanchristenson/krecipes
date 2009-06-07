/***************************************************************************
*   Copyright (C) 2005 by Jason Kivlighn                                  *
*   jkivlighn@gmail.com                                                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/

#include "editratingdialog.h"

#include <klocale.h>

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
//Added by qt3to4:
#include <QPixmap>
#include <knuminput.h>
#include <q3header.h>
#include <k3listview.h>
#include <q3textedit.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qpainter.h>

#include <KVBox>
#include <kmenu.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kdebug.h>
#include <kvbox.h>

#include "datablocks/rating.h"
#include "datablocks/elementlist.h"
#include "datablocks/mixednumber.h"

#include "widgets/ratingwidget.h"

class RatingCriteriaListView : public K3ListView
{
public:
	RatingCriteriaListView( QWidget *parent = 0, const char *name = 0 ) : K3ListView(parent){ setObjectName( name ); }

	void rename( Q3ListViewItem *it, int c )
	{
		if ( c == 1 )
			it->setPixmap(c,QPixmap());

		K3ListView::rename(it,c);
	}
};


EditRatingDialog::EditRatingDialog( const ElementList &criteriaList, const Rating &rating, QWidget* parent, const char* name )
		: KDialog( parent )
{
   setObjectName( name );
   setCaption( i18n( "Rating" ) );
	init(criteriaList);
	loadRating(rating);
}

/*
 *  Constructs a EditRatingDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
EditRatingDialog::EditRatingDialog( const ElementList &criteriaList, QWidget* parent, const char* name )
		: KDialog( parent )
{
   setObjectName( name );
   	setCaption( i18n( "Rating" ) );
	init(criteriaList);
}

void EditRatingDialog::init( const ElementList &criteriaList )
{
    setButtons(KDialog::Ok | KDialog::Cancel);
    setDefaultButton(KDialog::Ok);
    setModal( true );

    KVBox *page = new KVBox( this );
    setMainWidget( page );
	layout2 = new KHBox( page );

	raterLabel = new QLabel( layout2 );
   raterLabel->setObjectName( "raterLabel" );
	raterEdit = new QLineEdit( layout2 );
   raterEdit->setObjectName( "raterEdit" );

	layout8 = new KHBox( page );

	criteriaLabel = new QLabel( layout8 );
   criteriaLabel->setObjectName( "criteriaLabel" );

	criteriaComboBox = new QComboBox( layout8 );
   criteriaComboBox->setEditable( false );
   criteriaComboBox->setObjectName( "criteriaComboBox" );
	criteriaComboBox->setSizePolicy( QSizePolicy( QSizePolicy::MinimumExpanding, (QSizePolicy::SizeType)0, 0, 0, criteriaComboBox->sizePolicy().hasHeightForWidth() ) );
	criteriaComboBox->setEditable( true );
	criteriaComboBox->lineEdit()->disconnect( criteriaComboBox ); //so hitting enter doesn't enter the item into the box

	starsLabel = new QLabel( layout8 );
   starsLabel->setObjectName( "starsLabel" );

	starsWidget = new RatingWidget( 5, layout8, "starsWidget" );

	addButton = new QPushButton( layout8 );
   addButton->setObjectName( "addButton" );

	removeButton = new QPushButton( layout8 );
   removeButton->setObjectName( "removeButton" );

	criteriaListView = new RatingCriteriaListView( page, "criteriaListView" );
	criteriaListView->addColumn( i18n( "Criteria" ) );
	criteriaListView->addColumn( i18n( "Stars" ) );
	criteriaListView->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, criteriaListView->sizePolicy().hasHeightForWidth() ) );
	criteriaListView->setSorting(-1);
	criteriaListView->setItemsRenameable( true );
	criteriaListView->setRenameable( 0, true );
	criteriaListView->setRenameable( 1, true );

	commentsLabel = new QLabel( page );
   commentsLabel->setObjectName( "commentsLabel" );

	commentsEdit = new Q3TextEdit( page, "commentsEdit" );

	languageChange();
	resize( QSize(358, 331).expandedTo(minimumSizeHint()) );
	//clearWState( WState_Polished );

	connect( criteriaListView, SIGNAL(itemRenamed(Q3ListViewItem*,const QString &,int)), this, SLOT(itemRenamed(Q3ListViewItem*,const QString &,int)) );
	connect( addButton, SIGNAL(clicked()), this, SLOT(slotAddRatingCriteria()) );
	connect( removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveRatingCriteria()) );

	KIconLoader *il = KIconLoader::global();
	KMenu *kpop = new KMenu( criteriaListView );
	kpop->addAction( il->loadIcon( "edit-delete-shred", KIconLoader::NoGroup, 16 ), i18n( "&Delete" ), this, SLOT( slotRemoveRatingCriteria() ), Qt::Key_Delete );

	for ( ElementList::const_iterator criteria_it = criteriaList.begin(); criteria_it != criteriaList.end(); ++criteria_it ) {
		criteriaComboBox->insertItem( criteriaComboBox->count(), ( *criteria_it ).name );
		//criteriaComboBox->completionObject()->addItem( ( *criteria_it ).name );
	}

	ratingID = -1;
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditRatingDialog::~EditRatingDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void EditRatingDialog::languageChange()
{
	criteriaLabel->setText( i18n( "Criteria:" ) );
	starsLabel->setText( i18n( "Stars:" ) );
	addButton->setText( i18n( "Add" ) );
	removeButton->setText( i18n( "&Delete" ) );
	criteriaListView->header()->setLabel( 0, i18n( "Criteria" ) );
	criteriaListView->header()->setLabel( 1, i18n( "Stars" ) );
	commentsLabel->setText( i18n( "Comments:" ) );
	raterLabel->setText( i18n( "Rater:" ) );
}

void EditRatingDialog::itemRenamed(Q3ListViewItem* it, const QString &, int c)
{
	if ( c == 1 ) {
		bool ok = false;
		MixedNumber stars_mn = MixedNumber::fromString(it->text(c),&ok);
		if ( ok && !it->text(c).isEmpty() ) {
			double stars = qMax(0.0,qMin(stars_mn.toDouble(),5.0)); //force to between 0 and 5
			QPixmap starsPic = Rating::starsPixmap( stars );
			it->setPixmap(c,starsPic);
			it->setText(2,QString::number(stars));
		}
		else {
			double stars = it->text(2).toDouble(); //col 2 holds the old value, which we'll set it back to
			QPixmap starsPic = Rating::starsPixmap( stars );
			it->setPixmap(c,starsPic);
		}

		it->setText(c,QString::null);
	}
}

Rating EditRatingDialog::rating() const
{
	Rating r;

	for ( Q3ListViewItem *it = criteriaListView->firstChild(); it; it = it->nextSibling() ) {
		RatingCriteria rc;
		rc.name = it->text(0);
		rc.stars = it->text(2).toDouble();
		r.append( rc );
	}

	r.comment = commentsEdit->text();
	r.rater = raterEdit->text();

	r.id = ratingID;

	return r;
}

void EditRatingDialog::loadRating( const Rating &rating )
{
	for ( RatingCriteriaList::const_iterator rc_it = rating.ratingCriteriaList.begin(); rc_it != rating.ratingCriteriaList.end(); ++rc_it ) {
		addRatingCriteria(*rc_it);
	}

	raterEdit->setText(rating.rater);
	commentsEdit->setText(rating.comment);

	ratingID = rating.id;
}

void EditRatingDialog::slotAddRatingCriteria()
{
	RatingCriteria r;
	r.name = criteriaComboBox->lineEdit()->text().trimmed();
	if ( r.name.isEmpty() )
		return;

	r.stars = starsWidget->text().toDouble();

	addRatingCriteria(r);

	criteriaComboBox->lineEdit()->clear();
	starsWidget->clear();

	criteriaComboBox->lineEdit()->setFocus();
}

void EditRatingDialog::addRatingCriteria( const RatingCriteria &rc )
{
	Q3ListViewItem * it = new Q3ListViewItem(criteriaListView,rc.name);

	QPixmap stars = Rating::starsPixmap(rc.stars);
	if ( !stars.isNull() ) //there aren't zero stars
		it->setPixmap(1,stars);

	it->setText(2,QString::number(rc.stars));
}

void EditRatingDialog::slotRemoveRatingCriteria()
{
	delete criteriaListView->selectedItem();
}

#include "editratingdialog.moc"
