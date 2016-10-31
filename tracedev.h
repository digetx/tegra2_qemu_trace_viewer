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

#ifndef TRACEDEV_H
#define TRACEDEV_H

#include <QAbstractTableModel>
#include <QTreeWidgetItem>

class TraceDev : public QAbstractTableModel, public QTreeWidgetItem
{
    Q_OBJECT

public:
    TraceDev(QObject *parent, QString name = "")
        : QAbstractTableModel(parent),
          id(0),
          m_name(name),
          m_rec_enb(false)
    {
    }

    enum dev_type {
        MMIO,
        HOST1X_CDMA,
        HOST1X_MODULE,
    };

    enum dev_caps {
        REG_DESC,
        BITS_DESC,
    };

    virtual int deviceType(void) const = 0;
    virtual bool hasCap(dev_caps) const { return false; }
    virtual bool is_valid(u_int32_t) { return false; }
    virtual void setLogPath(QString) {}
    virtual QString updateDetails(const int &) { return QString(); }
    virtual QAbstractTableModel* getBitDetailsModel(void) { return NULL; }
    virtual QString entryAsString(void *) const { return ""; }

    int id;

    QString name(void)
    {
        return m_name;
    }

    bool recEnabled(void)
    {
        return m_rec_enb;
    }

protected:
    QString m_name;
    bool m_rec_enb;

signals:
    void recStateUpdated(int);

public slots:
    virtual void ClearLog(void) = 0;
    virtual void regFilterChanged(const QString &) {}

    void setRecording(bool enable)
    {
        m_rec_enb = enable;
        emit recStateUpdated(id);
    }
};

#endif // TRACEDEV_H
