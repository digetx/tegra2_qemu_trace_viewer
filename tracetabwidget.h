/*
 * Copyright (c) 2014-2015 Dmitry Osipenko <digetx@gmail.com>
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

#ifndef TRACETABWIDGET_H
#define TRACETABWIDGET_H

#include <QTabWidget>

class TraceTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TraceTabWidget(QWidget *parent = 0);

signals:

public slots:
    void OnError(void);
    void ClearErrorState(void);

private:
    enum {
        TRACE_A9_TAB = 0,
        TRACE_AVP_TAB,
        TRACE_HOST1X_CDMA_TAB,
        ERROR_TAB,
        CONSOLE_TAB
    };

    unsigned errors_cnt;

};

#endif // TRACETABWIDGET_H
