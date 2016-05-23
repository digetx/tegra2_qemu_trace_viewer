/*
 * Copyright (c) 2015 Dmitry Osipenko <digetx@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "devices/host1x_dev.h"
#include "devices/gr2ddev.h"

#include "cdmatrace.h"
#include "tracehost1x.h"

TraceHOST1X::TraceHOST1X(MainWindow *window, QString name, QObject *parent) :
    TraceSRC(window, name, parent)
{
    addDevice( new CdmaTrace(this, 0) );
    addDevice( new CdmaTrace(this, 1) );
    addDevice( new CdmaTrace(this, 2) );
    addDevice( new CdmaTrace(this, 3) );
    addDevice( new CdmaTrace(this, 4) );
    addDevice( new CdmaTrace(this, 5) );
    addDevice( new CdmaTrace(this, 6) );
    addDevice( new CdmaTrace(this, 7) );

    addDevice( new Host1xDev(this, "host1x", 0x1, true) );
    addDevice( new Gr2dDev(this, "host1x_gr2d", 0x51, true) );
    addDevice( new Gr2dDev(this, "host1x_gr2d_sb", 0x52, true) );
    addDevice( new Gr2dDev(this, "host1x_gr3d", 0x60, true) );
}
