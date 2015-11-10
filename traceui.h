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

#ifndef TRACEUI_H
#define TRACEUI_H

#include <QObject>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>

#include "device.h"
#include "mainwindow.h"
#include "tracedev.h"
#include "tracedevview.h"
#include "traceqtablewidget.h"

class TraceUI : public QObject
{
    Q_OBJECT
public:
    explicit TraceUI(MainWindow *window, QString name, QObject *parent = 0);

    void addDevice(TraceDev *dev);
    void resetUI(void);

private:
    MainWindow      *m_mainwindow;
    TraceDevView    *m_tableViewTrace;
    QTableView      *m_tableViewBitDetails;
    QListWidget     *m_listWidgetDevices;
    QTextEdit       *m_textRegDesc;
    QLineEdit       *m_regFilter;
    TraceDev        *m_activeDevice;

signals:

private slots:
    void ActiveDeviceChanged(QListWidgetItem *, QListWidgetItem *);
    void ActiveRegChanged(const QModelIndex &index);
};

#endif // TRACEUI_H
