/****************************************************************************
*   Copyright © 2016 José Manuel Santamaría Lema <panfaust@gmail.com>       *
*                                                                           *
*   This program is free software; you can redistribute it and/or modify    *
*   it under the terms of the GNU General Public License as published by    *
*   the Free Software Foundation; either version 2 of the License, or       *
*   (at your option) any later version.                                     *
****************************************************************************/

#ifndef NUTRIENTINFOSTATUSWIDGET_H
#define NUTRIENTINFOSTATUSWIDGET_H

#include <QWidget>

namespace Ui {
	class NutrientInfoStatusWidget;
}

namespace NutrientInfo {
	enum Status {
		Complete=0,
		Intermediate=1,
		Incomplete=2,
		Unknown=3
	};
}

class NutrientInfoStatusWidget : public QWidget
{
	Q_OBJECT

public:
	NutrientInfoStatusWidget( QWidget * parent = 0 );

	void setStatus( NutrientInfo::Status status );

signals:
	void detailsButtonClicked();
	void updateButtonClicked();

private:
	Ui::NutrientInfoStatusWidget * ui;

};

#endif
