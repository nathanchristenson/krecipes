/***************************************************************************
 *   Copyright (C) 2003 by Unai Garro                                      *
 *   ugarro@users.sourceforge.net                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef UNITRATIO_H
#define UNITRATIO_H

/**
@author Unai Garro
*/
class UnitRatio{
public:

    UnitRatio();
    UnitRatio(UnitRatio *ur);
    ~UnitRatio();
    int ingID1,ingID2;
    double ratio;
};

#endif
