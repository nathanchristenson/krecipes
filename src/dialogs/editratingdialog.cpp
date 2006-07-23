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
#include <knuminput.h>
#include <qheader.h>
#include <klistview.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qpainter.h>

#include <kpopupmenu.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kdebug.h>

#include "datablocks/rating.h"
#include "datablocks/elementlist.h"
#include "datablocks/mixednumber.h"

#include "widgets/ratingwidget.h"

class RatingCriteriaListView : public KListView
{
public:
	RatingCriteriaListView( QWidget *parent = 0, const char *name = 0 ) : KListView(parent,name){}

	void rename( QListViewItem *it, int c )
	{
		if ( c == 1 )
			it->setPixmap(c,QPixmap());

		KListView::rename(it,c);
	}
};


EditRatingDialog::EditRatingDialog( const ElementList &criteriaList, const Rating &rating, QWidget* parent, const char* name ) : KDialog(parent,name)
{
	if ( !name )
		setName( "EditRatingDialog" );

	init(criteriaList);
	loadRating(rating);
}

/*
 *  Constructs a EditRatingDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
EditRatingDialog::EditRatingDialog( const ElementList &criteriaList, QWidget* parent, const char* name )
    : KDialog( parent, name )
{
	if ( !name )
		setName( "EditRatingDialog" );

	init(criteriaList);
}

void EditRatingDialog::init( const ElementList &criteriaList )
{
	EditRatingDialogLayout = new QVBoxLayout( this, 11, 6, "EditRatingDialogLayout"); 
	
	layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 
	
	raterLabel = new QLabel( this, "raterLabel" );
	layout2->addWidget( raterLabel );
	
	raterEdit = new QLineEdit( this, "raterEdit" );
	layout2->addWidget( raterEdit );
	EditRatingDialogLayout->addLayout( layout2 );
	
	layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 
	
	criteriaLabel = new QLabel( this, "criteriaLabel" );
	layout8->addWidget( criteriaLabel );
	
	criteriaComboBox = new QComboBox( FALSE, this, "criteriaComboBox" );
	criteriaComboBox->setSizePolicy( QSizePolicy( QSizePolicy::MinimumExpanding, (QSizePolicy::SizeType)0, 0, 0, criteriaComboBox->sizePolicy().hasHeightForWidth() ) );
	criteriaComboBox->setEditable( TRUE );
	criteriaComboBox->lineEdit()->disconnect( criteriaComboBox ); //so hitting enter doesn't enter the item into the box
	layout8->addWidget( criteriaComboBox );
	
	starsLabel = new QLabel( this, "starsLabel" );
	layout8->addWidget( starsLabel );
	/*
	starsSpinBox = new KDoubleSpinBox( this, "starsSpinBox" );
	starsSpinBox->setMaxValue( 5 );
	starsSpinBox->setLineStep( 0.5 );
	layout8->addWidget( starsSpinBox );
*/
	starsWidget = new RatingWidget( 5, this, "starsWidget" );
	//starsWidget->setMaxValue( 5 );
	layout8->addWidget( starsWidget );
	
	addButton = new QPushButton( this, "addButton" );
	layout8->addWidget( addButton );

	removeButton = new QPushButton( this, "removeButton" );
	layout8->addWidget( removeButton );

	EditRatingDialogLayout->addLayout( layout8 );
	
	criteriaListView = new RatingCriteriaListView( this, "criteriaListView" );
	criteriaListView->addColumn( i18n( "Criteria" ) );
	criteriaListView->addColumn( i18n( "Stars" ) );
	criteriaListView->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, criteriaListView->sizePolicy().hasHeightForWidth() ) );
	criteriaListView->setSorting(-1);
	criteriaListView->setItemsRenameable( true );
	criteriaListView->setRenameable( 0, true );
	criteriaListView->setRenameable( 1, true );
	EditRatingDialogLayout->addWidget( criteriaListView );
	
	commentsLabel = new QLabel( this, "commentsLabel" );
	EditRatingDialogLayout->addWidget( commentsLabel );
	
	commentsEdit = new QTextEdit( this, "commentsEdit" );
	EditRatingDialogLayout->addWidget( commentsEdit );
	
	layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 
	
	okButton = new QPushButton( this, "okButton" );
	layout7->addWidget( okButton );
	
	cancelButton = new QPushButton( this, "cancelButton" );
	layout7->addWidget( cancelButton );
	buttonsSpacer = new QSpacerItem( 240, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
	layout7->addItem( buttonsSpacer );
	EditRatingDialogLayout->addLayout( layout7 );
	languageChange();
	resize( QSize(358, 331).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );

	connect( criteriaListView, SIGNAL(itemRenamed(QListViewItem*,const QString &,int)), this, SLOT(itemRenamed(QListViewItem*,const QString &,int)) );
	connect( addButton, SIGNAL(clicked()), this, SLOT(slotAddRatingCriteria()) );
	connect( removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveRatingCriteria()) );
	connect( okButton, SIGNAL(clicked()), this, SLOT(accept()) );
	connect( cancelButton, SIGNAL(clicked()), this, SLOT(reject()) );

	KIconLoader il;
	KPopupMenu *kpop = new KPopupMenu( criteriaListView );
	kpop->insertItem( il.loadIcon( "editshred", KIcon::NoGroup, 16 ), i18n( "&Delete" ), this, SLOT( slotRemoveRatingCriteria() ), Key_Delete );

	for ( ElementList::const_iterator criteria_it = criteriaList.begin(); criteria_it != criteriaList.end(); ++criteria_it ) {
		criteriaComboBox->insertItem( ( *criteria_it ).name );
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
	setCaption( i18n( "Rating" ) );
	criteriaLabel->setText( i18n( "Criteria:" ) );
	starsLabel->setText( i18n( "Stars:" ) );
	addButton->setText( i18n( "Add" ) );
	removeButton->setText( i18n( "&Delete" ) );
	criteriaListView->header()->setLabel( 0, i18n( "Criteria" ) );
	criteriaListView->header()->setLabel( 1, i18n( "Stars" ) );
	commentsLabel->setText( i18n( "Comments:" ) );
	raterLabel->setText( i18n( "Rater:" ) );
	okButton->setText( i18n( "&OK" ) );
	okButton->setAccel( QKeySequence( i18n( "Alt+O" ) ) );
	cancelButton->setText( i18n( "&Cancel" ) );
	cancelButton->setAccel( QKeySequence( i18n( "Alt+C" ) ) );
}

void EditRatingDialog::itemRenamed(QListViewItem* it, const QString &, int c)
{
	if ( c == 1 ) {
		bool ok = false;
		MixedNumber stars_mn = MixedNumber::fromString(it->text(c),&ok);
		if ( ok && !it->text(c).isEmpty() ) {
			double stars = QMAX(0,QMIN(stars_mn.toDouble(),5)); //force to between 0 and 5
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

	for ( QListViewItem *it = criteriaListView->firstChild(); it; it = it->nextSibling() ) {
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
	r.name = criteriaComboBox->lineEdit()->text().stripWhiteSpace();
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
	QListViewItem * it = new QListViewItem(criteriaListView,rc.name);

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