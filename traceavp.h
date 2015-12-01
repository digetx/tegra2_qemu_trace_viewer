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

#include <QPushButton>

#ifndef TraceAVP_H
#define TraceAVP_H

#include "tracesrc.h"

class TraceAVP : public TraceSRC
{
    Q_OBJECT
public:
    explicit TraceAVP(MainWindow *window, QString name, QObject *parent = 0);

    void stopRecording(void);
    void restartRecording(void);

    enum {
        BASE,
        NAME,
        READS,
        WRITES,
        IRQ_ACTIONS,
        ERRORS,
        RECORDING_EN,
        COLUMS_NB,
    };

private slots:
    void recordingToggle(void);
    void firstTimeStatUpdated(int);
    void readStatUpdated(int);
    void writeStatUpdated(int);
    void irqStatUpdated(int);
    void errorStatUpdated(int);

private:
    QFile m_recordfile;
    QDataStream m_recordstream;
    QPushButton *m_rec_button;
    QString m_log_path;
    bool m_record_en;

    void recordingSet(bool en);
    bool openRecordFile(void);
    void flushRecordFile(void);

    // TraceSRC interface
public:
    void regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                   const u_int32_t &value, const u_int32_t &new_value,
                   const u_int32_t &time, const bool &is_write,
                   const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                   const bool &is_irq);

    void addDevice(TraceDev *dev);
    void reset(QString log_path);

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &, int) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // TraceAVP_H
