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

#include <QColor>
#include <QTime>
#include <QtCore/qmath.h>

#include "cdmatrace.h"
#include "host1x_cmd_processor.h"
#include "tracecore.h"

#define DMA_START   0xA
#define DMA_STOP    0xB

void CdmaTrace::validateEntry(log_entry &entry)
{
    switch (CMD_OPCODE(entry.data)) {
    case SETCL:
    {
        setcl_op op = { .reg32 = entry.data };

        if (m_class_id != op.class_id)
            emit cdmaStarted(op.class_id);

        m_class_id = op.class_id;
        entry.class_id = 0;

        return;
    }
    case INCR:
    case NONINCR:
    case MASK:
    case IMM:
    case RESTART:
    case GATHER:
    case EXTEND:
    case CHDONE:
        entry.class_id = m_class_id;
        break;
    default:
        entry.invalid = true;
        break;
    }

    entry.class_id = m_class_id;
}

void CdmaTrace::setLogPath(const QString ldir)
{
    m_log.setLogFilePath(ldir + m_name + ".txt");
}

QString CdmaTrace::entryAsString(void *e) const
{
    log_entry *entry = (CdmaTrace::log_entry*) e;
    QTime mstime = QTime(0, 0).addMSecs(entry->time / 1000);
    QString ret;

    ret = mstime.toString("hh:mm:ss.zzz") +
                    QString().sprintf(".%03d\t", entry->time % 1000);

    if (entry->class_id)
        ret += QString().sprintf("Class 0x%02X ",entry-> class_id);

    ret += CdmaTrace::opcodeName(CMD_OPCODE(entry->data)) + ": ";
    ret += CdmaTrace::cmdParams(entry->data);

    return ret;
}

void CdmaTrace::write_log(log_entry &entry)
{
    bool log_is_full = m_log.write(entry);
    emit layoutChanged();

    if (log_is_full) {
        emit itemInserted();
    }
}

void CdmaTrace::trace(const u_int32_t &time, const u_int32_t &data, const bool &is_gather)
{
    log_entry entry = {
        .time = time,
        .data = data,
        .class_id = 0,
        .is_gather = is_gather,
        .invalid = false,
    };

    validateEntry(entry);
    write_log(entry);

    if (!m_update_stats_timer.isActive())
        m_update_stats_timer.start(300);

    m_access_nb++;
}

void CdmaTrace::updateStats(void)
{
    setText(0, m_name + QString().sprintf(" (%lu)", m_access_nb));
    m_log.flush();
}

int CdmaTrace::rowCount(const QModelIndex &) const
{
    return m_log.size();
}

int CdmaTrace::columnCount(const QModelIndex &) const
{
    return CdmaTrace::COLUMNS_NB;
}

QString CdmaTrace::opcodeName(u_int8_t opcode) const
{
    switch (opcode) {
    case SETCL:
        return "SETCL";
    case INCR:
        return "INCR";
    case NONINCR:
        return "NONINCR";
    case MASK:
        return "MASK";
    case IMM:
        return "IMM";
    case RESTART:
        return "RESTART";
    case GATHER:
        return "GATHER";
    case EXTEND:
        return "EXTEND";
    case CHDONE:
        return "CHDONE";
    default:
        return QString().sprintf("0x%02X", opcode);
    }
}

QString CdmaTrace::cmdParams(u_int32_t &data) const
{
    switch ( CMD_OPCODE(data) ) {
    case SETCL:
    {
        setcl_op op = { .reg32 = data };

        return QString().sprintf("mask=0x%X class_id=0x%02X offset=0x%X",
                                 op.mask, op.class_id, op.offset);
    }
    case INCR:
    case NONINCR:
    {
        incr_op op = { .reg32 = data };

        return QString().sprintf("count=%d offset=0x%X",
                                 op.count, op.offset);
    }
    case MASK:
    {
        mask_op op = { .reg32 = data };

        return QString().sprintf("mask=0x%X offset=0x%X",
                                 op.mask, op.offset);
    }
    case IMM:
    {
        imm_op op = { .reg32 = data };

        return QString().sprintf("immdata=0x%X offset=0x%X",
                                 op.immdata, op.offset);
    }
    case GATHER:
    {
        gather_op op = { .reg32 = data };

        return QString().sprintf("incrcount=%d insert=%d incr=%d offset=0x%X",
                                 op.incrcount, op.insert, op.incr, op.offset);
    }
    case EXTEND:
    {
        extend_op op = { .reg32 = data };

        switch (op.subop) {
        case ACQUIRE_MLOCK:
            return QString().sprintf("subop=ACQUIRE_MLOCK id=%d", op.value);
        case RELEASE_MLOCK:
            return QString().sprintf("subop=RELEASE_MLOCK id=%d", op.value);
        default:
            return QString().sprintf("value=0x%X subop=0x%X",
                                     op.value, op.subop);
        }
    }
    case RESTART:
    {
        restart_op op = { .reg32 = data };

        return QString().sprintf("new_get=%d", op.offset);
    }
    case CHDONE:
        return QString();
    case START:
        return "CDMA start";
    case STOP:
        return "CDMA stop";
    default:
        return QString().sprintf("0x%08X", data);
    }
}

QVariant CdmaTrace::data(const QModelIndex &index, int role) const
{
    log_entry entry;
    QTime mstime;

    Q_ASSERT(index.row() < m_log.size());

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
    {
        entry = m_log.read( index.row() );

        switch ( index.column() ) {
        case CdmaTrace::CMD:
            return opcodeName(CMD_OPCODE(entry.data));
        case CdmaTrace::PARAMS:
            return cmdParams(entry.data);
        case CdmaTrace::CLASS_ID:
            if (entry.class_id)
                return QString().sprintf("0x%02X", entry.class_id);
            break;
        case CdmaTrace::TIME:
        {
            mstime = QTime(0, 0).addMSecs(entry.time / 1000);

            return mstime.toString("hh:mm:ss.zzz") +
                            QString().sprintf(".%03d", entry.time % 1000);
        }
        default:
            break;
        }
        break;
    }
    case Qt::BackgroundRole:
    {
        entry = m_log.read( index.row() );

        if (entry.is_gather)
            return QColor(200, 255, 200);

        if ((entry.data >> 28) == DMA_START)
            return QColor(255, 255, 150);

        if ((entry.data >> 28) == DMA_STOP)
            return QColor(150, 150, 255);

        break;
    }
    default:
        break;
    }

    return QVariant();
}

QVariant CdmaTrace::headerData(int section, Qt::Orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch (section) {
        case CdmaTrace::CMD:
            return "Command";
        case CdmaTrace::CLASS_ID:
            return "Class ID";
        case CdmaTrace::PARAMS:
            return "Params";
        case CdmaTrace::TIME:
            return "Time";
        default:
            break;
        }
    default:
        break;
    }

    return QVariant();
}


int CdmaTrace::deviceType() const
{
    return TraceDev::HOST1X_CDMA;
}

void CdmaTrace::ClearLog()
{
    m_class_id = 0;
    m_access_nb = 0;
    m_log.clear();

    updateStats();

    emit layoutChanged();
}

bool CdmaTrace::is_valid(u_int32_t ch_id)
{
    return ch_id == m_ch_id;
}

Qt::ItemFlags CdmaTrace::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
