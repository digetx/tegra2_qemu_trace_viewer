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

#ifndef TRACEIPC_H
#define TRACEIPC_H

#include <QMutex>
#include <QLocalSocket>
#include <QTcpSocket>
#include <QTimer>

#ifndef Q_OS_ANDROID
#define LOCAL_SOCKET
#endif

class TraceIPC : public QObject
{
    Q_OBJECT

public:
    TraceIPC(QObject *parent = 0);

    void connectTo(const QString &addr);

    bool send(void *cmd, qint64 size);

    typedef struct trace_pkt_rw_s {
//        u_int32_t magic;
        u_int32_t hwaddr;
        u_int32_t offset;
        u_int32_t value;
        u_int32_t new_value;
        union {
            struct {
                unsigned is_write:1;
                unsigned clk_disabled:1;
                unsigned in_reset:1;
                unsigned size:3;
            };

            uint32_t __old_is_write;
        };
        u_int32_t time;
        u_int32_t cpu_pc;
        u_int32_t cpu_id;
    } __attribute__((packed, aligned(1))) packet_rw;

    typedef struct trace_pkt_irq_s {
//        u_int32_t magic;
        u_int32_t hwaddr;
        u_int32_t hwirq;
        u_int32_t status;
        u_int32_t time;
        u_int32_t cpu_pc;
        u_int32_t cpu_id;
        u_int64_t __pad;
    } __attribute__((packed, aligned(1))) packet_irq;

    typedef struct trace_pkt_cdma_s {
//        u_int32_t magic;
        u_int32_t time;
        u_int32_t data;
        u_int32_t is_gather;
        u_int32_t ch_id;
        u_int64_t __pad0;
        u_int64_t __pad1;
    } __attribute__((packed, aligned(1))) packet_cdma;

    typedef struct trace_pkt_txt_s {
//        u_int32_t magic;
        u_int32_t text_sz;
        u_int64_t __pad0;
        u_int64_t __pad1;
        u_int64_t __pad2;
        u_int32_t __pad4;
    } __attribute__((packed, aligned(1))) packet_txt;

signals:
    void regAccess(TraceIPC::packet_rw pak_rw);
    void irqEvent(TraceIPC::packet_irq pak_irq);
    void chWrite(u_int32_t ch_id, u_int32_t time,
                 u_int32_t data, u_int32_t is_gather);
    void connected(void);
    void disconnected(void);
    void message(char *txt);

public slots:
    void socket_connected(void);
    void socket_disconnected(void);
    void socket_readReady(void);
    void socket_error(void);

private slots:
    void Reconnect(void);
    void changeAddr(const QString &addr);

private:
#ifdef LOCAL_SOCKET
    QLocalSocket m_socket;
#else
    QTcpSocket m_socket;
#endif
    QTimer m_reconnect_timer;
    QString m_addr;
    bool m_reconnect;
};

#endif // TRACEIPC_H
