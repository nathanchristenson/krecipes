/*
 * Copyright (C) 2003 Unai Garro <uga@ee.ed.ac.uk>
 */

#ifndef _KRECIPESPREF_H_
#define _KRECIPESPREF_H_

#include <kdialogbase.h>
#include <qframe.h>

class KrecipesPrefPageOne;
class KrecipesPrefPageTwo;

class KrecipesPreferences : public KDialogBase
{
    Q_OBJECT
public:
    KrecipesPreferences();

private:
    KrecipesPrefPageOne *m_pageOne;
    KrecipesPrefPageTwo *m_pageTwo;
};

class KrecipesPrefPageOne : public QFrame
{
    Q_OBJECT
public:
    KrecipesPrefPageOne(QWidget *parent = 0);
};

class KrecipesPrefPageTwo : public QFrame
{
    Q_OBJECT
public:
    KrecipesPrefPageTwo(QWidget *parent = 0);
};

#endif // _KRECIPESPREF_H_
