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

#ifndef CDMATRACE_H
#define CDMATRACE_H

#include <QListWidgetItem>
#include <QTimer>
#include <QVarLengthArray>

#include "circularlog.h"
#include "tracedev.h"

#define MAX_LOG_ENTRIES 3000

#define CHANNELS_NB 8

class CdmaTrace : public TraceDev
{
    Q_OBJECT

public:
    explicit CdmaTrace(QObject *parent, unsigned id)
        : TraceDev(parent, QString().sprintf("host1x_cdma%d", id)),
          m_log(this, MAX_LOG_ENTRIES),
          m_class_id(0),
          m_access_nb(0),
          m_ch_id(id)
    {
        updateStats();

        m_update_stats_timer.setSingleShot(true);
        connect(&m_update_stats_timer, SIGNAL(timeout()), this, SLOT(updateStats()));
    }

private:
    enum {
        TIME = 0,
        CLASS_ID,
        CMD,
        PARAMS,
        COLUMNS_NB
    };

    typedef struct log_entry_s {
        u_int32_t time;
        u_int32_t data;
        u_int8_t class_id;
        bool is_gather;
        bool invalid;
    } log_entry;

    CircularLog<CdmaTrace, log_entry> m_log;
    u_int8_t m_class_id;
    u_int64_t m_access_nb;
    unsigned m_ch_id;
    QTimer m_update_stats_timer;

    void setLogPath(QString ldir);
    void write_log(log_entry &entry);
    QString opcodeName(u_int8_t opcode) const;
    QString cmdParams(u_int32_t &data) const;
    void validateEntry(log_entry &entry);

public:
    void trace(const u_int32_t &time, const u_int32_t &data, const bool &is_gather);

signals:
    void itemInserted(void);

public slots:
    void ClearLog();

private slots:
    void updateStats(void);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // TraceDev interface
public:
    int deviceType() const;
    QString entryAsString(void *e) const;
    bool is_valid(u_int32_t ch_id);
};

#endif // CDMATRACE_H
