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
//#include "devices/gr3ddev.h"

#include "cdmatrace.h"
#include "tracehost1x.h"

TraceHOST1X::TraceHOST1X(MainWindow *window, QString name, QObject *parent) :
    TraceSRC(window, name, parent)
{
    CdmaTrace *cdma0 = new CdmaTrace(this, 0);
    CdmaTrace *cdma1 = new CdmaTrace(this, 1);
    CdmaTrace *cdma2 = new CdmaTrace(this, 2);
    CdmaTrace *cdma3 = new CdmaTrace(this, 3);
    CdmaTrace *cdma4 = new CdmaTrace(this, 4);
    CdmaTrace *cdma5 = new CdmaTrace(this, 5);
    CdmaTrace *cdma6 = new CdmaTrace(this, 6);
    CdmaTrace *cdma7 = new CdmaTrace(this, 7);

    Host1xDev *host1x         = new Host1xDev(this, "host1x", 0x1, true);
    Gr2dDev   *host1x_gr2d    = new Gr2dDev(this, "host1x_gr2d", 0x51, true);
    Gr2dDev   *host1x_gr2d_sb = new Gr2dDev(this, "host1x_gr2d_sb", 0x52, true);
//    Gr3dDev   *host1x_gr3d    = new Gr3dDev(this, "host1x_gr3d", 0x60, true);

    addDevice( cdma0 );
    addDevice( cdma1 );
    addDevice( cdma2 );
    addDevice( cdma3 );
    addDevice( cdma4 );
    addDevice( cdma5 );
    addDevice( cdma6 );
    addDevice( cdma7 );

    addDevice( host1x );
    addDevice( host1x_gr2d );
    addDevice( host1x_gr2d_sb );
//    addDevice( host1x_gr3d );

//    connect(cdma0, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma1, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma2, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma3, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma4, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma5, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma6, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
//    connect(cdma7, SIGNAL(cdmaStarted(unsigned)),
//            host1x_gr3d, SLOT(breakRecord(unsigned)));
}
