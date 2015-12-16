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

#ifndef TRACECPU_H
#define TRACECPU_H

#include <QAbstractTableModel>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVarLengthArray>

#include "mainwindow.h"

#include "device.h"
#include "tracedev.h"
#include "tracedevview.h"
#include "traceqtablewidget.h"

class TraceSRC;

class TraceUI : public QObject
{
    Q_OBJECT
public:
    explicit TraceUI(MainWindow *window, QString name, TraceSRC *parent);

    void addDevice(TraceDev *dev);
    void resetUI(void);

    QPushButton     *m_rec_button;

private:
    MainWindow      *m_mainwindow;
    QTableView      *m_tableViewDevices;
    TraceDevView    *m_tableViewTrace;
    QTableView      *m_tableViewBitDetails;
    QListWidget     *m_listWidgetDevices;
    QTextEdit       *m_textRegDesc;
    QLineEdit       *m_regFilter;
    TraceDev        *m_activeDevice;
    TraceSRC        *m_tracesrc;

    void ActiveDeviceChanged(TraceDev *dev);

signals:

private slots:
    void ActiveDeviceChanged(QListWidgetItem *item, QListWidgetItem *);
    void ActiveDeviceChanged(const QModelIndex &, const QModelIndex &);
    void ActiveRegChanged(const QModelIndex &);
};

class TraceSRC : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TraceSRC(MainWindow *window, QString name, QObject *parent = 0);

    virtual void regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                   const u_int32_t &value, const u_int32_t &new_value,
                   const u_int32_t &time, const u_int32_t &is_write,
                   const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                   const bool &is_irq);

    virtual void chWrite(const u_int32_t &ch_id, const u_int32_t &time,
                 const u_int32_t &data, const u_int32_t &is_gather);

    virtual void reset(QString log_path);

    TraceDev * getDevByAddr(const u_int32_t &, const TraceDev::dev_type &);
    TraceDev * getDevAt(int idx) const;

protected:
    TraceUI *m_tui;
    QString m_name;
    QVarLengthArray<TraceDev*> m_devices;

    void addDevice(TraceDev *dev);

private:
    u_int32_t m_prev_addr;
    TraceDev *m_prev_dev;
    QMutex m_mutex;

signals:
    void ErrUnkDev(const QString, const Device::log_entry);

public slots:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const
    {
        return m_devices.size();
    }

    int columnCount(const QModelIndex &) const
    {
        return 0;
    }

    QVariant data(const QModelIndex &, int) const
    {
        return QVariant();
    }
};

#endif // TRACECPU_H
