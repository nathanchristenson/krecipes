/***************************************************************************
 *   Copyright (C) 2003 by                                                 *
 *   Cyril Bosselut (bosselut@b1project.com)                               *
 *   Jason Kivlighn (mizunoami44@users.sourceforge.net)                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef KREEXPORTER_H
#define KREEXPORTER_H

#include "baseexporter.h"

/**
Export class for Krecipes native file format (.kre, .kreml)

@author Cyril Bosselut and Jason Kivlighn
*/
class KreExporter : public BaseExporter{
public:
    KreExporter( RecipeDB *, const QString&, const QString );

    virtual ~KreExporter();

    virtual QString createContent( const RecipeList & );

protected:
    virtual void saveToFile( const RecipeList & );
    virtual QString extensions() const{ return ".kre,.kreml"; }
};

#endif
