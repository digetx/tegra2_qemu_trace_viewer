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
#include <QVarLengthArray>

#include "tracedev.h"

#define MAX_LOG_ENTRIES 3000

class CdmaTrace : public TraceDev
{
    Q_OBJECT

public:
    CdmaTrace()
        : TraceDev(),
          m_log_pointer(0),
          m_log_size(0),
          m_class_id(0),
          m_access_nb(0)
    {
    }

    CdmaTrace(int id)
        : TraceDev(),
          m_log_pointer(0),
          m_log_size(0),
          m_class_id(0),
          m_access_nb(0),
          m_ch_id(id)
    {
        m_name = QString().sprintf("host1x cdma%d", m_ch_id);
        setText(m_name);
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

    QString m_name;
    QVarLengthArray<log_entry> m_log;
    int m_log_pointer;
    int m_log_size;
    u_int8_t m_class_id;
    u_int64_t m_access_nb;
    unsigned m_ch_id;

    log_entry read_log_entry(int index) const;
    void write_log(log_entry &entry);
    QString opcodeName(u_int8_t opcode) const;
    QString cmdParams(u_int32_t &data) const;
    void validataEntry(log_entry &entry);

public:
    void trace(u_int32_t &time, u_int32_t &data, bool is_gather);

signals:
    void logItemInserted(bool);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation, int role) const;

    // TraceDev interface
public:
    int deviceType() const;

public slots:
    void ClearLog();

    // TraceDev interface
public:
    bool is_valid(u_int32_t ch_id);

    // QAbstractItemModel interface
public:
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // CDMATRACE_H
