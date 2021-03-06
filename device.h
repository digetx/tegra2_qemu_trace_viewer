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

#ifndef DEVICE_H
#define DEVICE_H

#include <QColor>
#include <QFile>
#include <QMetaType>
#include <QTextStream>
#include <QTimer>

#include "circularlog.h"
#include "tracedev.h"
#include "traceipc.h"

#define MAX_LOG_ENTRIES 3000

class BitDetails : public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef struct bit_entry_s {
        QString name;
        QString comment;
        u_int8_t bits;
        u_int32_t value;
        u_int32_t new_value;
    } bit_entry;

    explicit BitDetails(QObject *parent = 0);

    void signalUpdate(void);

    QVarLengthArray<BitDetails::bit_entry> bits;
    QString desc;

    bool has_changed_bits:1;

    enum {
        NAME = 0,
        VALUE,
        NEW_VALUE,
        COMMENT,
        COLUMNS_NB
    };

protected:

private:

signals:

public slots:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

class Device : public TraceDev
{
    Q_OBJECT

public:
    typedef struct log_entry_s {
        u_int32_t offset;
        u_int32_t value;
        u_int32_t new_value;
        u_int32_t time;
        u_int32_t cpu_pc;
        u_int32_t cpu_id;
        bool      is_write:1;
        bool      is_error:1;
        bool      undefined_changed:1;
        bool      is_irq:1;
        bool      clk_disabled:1;
        bool      in_reset:1;
        u_int32_t custom;
        unsigned  rw_size;
    } log_entry;

    Device(QObject    *parent,
           QString     name,
           u_int32_t   base,
           bool        host1x_item = false,
           int         max_log_entries = MAX_LOG_ENTRIES)
        : TraceDev(parent, name + (host1x_item ? "_" + QString::number(base, 16).toUpper() : "")),
          m_bit_details_model(this),
          m_is_host1x_item(host1x_item),
          m_log(this, max_log_entries),
          m_base(base),
          m_dev_writes_nb(0),
          m_dev_reads_nb(0),
          m_dev_irqs_nb(0),
          m_dev_errs_nb(0),
          m_regFilter(""),
          m_stats_changed(false),
          m_irq_act(false),
          m_record_dev(NULL)
    {
        updateName();

        blink_reset_timer.setSingleShot(true);
        connect(&blink_reset_timer, SIGNAL(timeout()),
                this, SLOT(blink_reset()));

        update_dev_stats_timer.setSingleShot(true);
        connect(&update_dev_stats_timer, SIGNAL(timeout()),
                this, SLOT(update_dev_stats()));
    }

    virtual bool is_valid(u_int32_t base) {return m_base == base;}

    void setLogPath(QString ldir);

    void write_log(const TraceIPC::packet_rw &);
    void write_log(const TraceIPC::packet_irq &);
    void write_log(log_entry &);

    QString updateDetails(const int &index);

    QAbstractTableModel* getBitDetailsModel(void);

    QString name(void)   { return m_name; }
    quint32 base(void)   { return m_base; }
    quint64 reads(void)  { return m_dev_reads_nb; }
    quint64 writes(void) { return m_dev_writes_nb; }
    quint64 irqs(void)   { return m_dev_irqs_nb; }
    quint64 errors(void) { return m_dev_errs_nb; }
    bool    nostats(void) { return !m_stats_changed; }
    bool    irq_active(void) { return m_irq_act; }

public slots:
    void ClearLog(void);
    void regFilterChanged(const QString &text);
    virtual void breakRecord(unsigned);

protected:
    virtual bool is_offset_valid(const u_int32_t &offset) const = 0;
    virtual bool is_undef_changed(const u_int32_t &offset,
                                  const u_int32_t &value,
                                  const u_int32_t &new_value) const = 0;
    virtual void update_internal(log_entry &entry);

    BitDetails m_bit_details_model;
    bool m_is_host1x_item;
    CircularLog<Device, Device::log_entry> m_log;
    QTimer update_dev_stats_timer;
    QTimer blink_reset_timer;
    const u_int32_t m_base;
    u_int64_t m_dev_writes_nb;
    bool m_writes_stat_dirty;
    u_int64_t m_dev_reads_nb;
    bool m_reads_stat_dirty;
    u_int64_t m_dev_irqs_nb;
    bool m_irqs_stat_dirty;
    u_int64_t m_dev_errs_nb;
    bool m_errs_stat_dirty;
    QString m_regFilter;
    QBrush m_background;
    bool m_stats_changed;
    bool m_irq_act;
    Device *m_record_dev;

    virtual QString get_register_name(const log_entry &entry) const = 0;

    virtual void fill_bits_details(const u_int32_t &offset,
                                   const u_int32_t &value,
                                   const u_int32_t &new_value) = 0;

    void updateName(void);

    enum {
        TIME = 0,
        REGISTER,
        VALUE,
        CPU_PC,
        COLUMNS_NB
    };

signals:
    void itemInserted();

    void ErrorUnknownReg(const QString dev_name, const Device::log_entry entry);

    void ErrorCustom(const QString dev_name, const QString text,
                     const u_int32_t time);

    void irqStatUpdated(int);
    void readStatUpdated(int);
    void writeStatUpdated(int);
    void errorStatUpdated(int);
    void firstTimeStatUpdated(int);

private slots:
    void update_dev_stats(void);
    void blink_reset(void);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // TraceDev interface
public:
    int deviceType() const;
    bool hasCap(dev_caps cap) const;
    QString entryAsString(void *e) const;
};

Q_DECLARE_METATYPE(Device *)

#endif // DEVICE_H
