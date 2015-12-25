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

#include <arpa/inet.h>

#include "traceipc.h"

#define PACKET_TRACE_RW     0x11111111
#define PACKET_TRACE_RW_V2  0x11111112
#define PACKET_TRACE_IRQ    0x22222222
#define PACKET_TRACE_TXT    0x33333333
#define PACKET_TRACE_CDMA   0x44444444

#define MAX_JOBS        1000

TraceIPC::TraceIPC(QObject *parent) :
    QObject(parent), m_reconnect(false)
{
    connect(&m_socket, SIGNAL(connected()), this, SLOT(socket_connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(socket_readReady()));
#ifdef LOCAL_SOCKET
    connect(&m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(socket_error(QLocalSocket::LocalSocketError)));
#else
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socket_error(QAbstractSocket::SocketError)));
#endif

    m_reconnect_timer.setSingleShot(true);
    connect(&m_reconnect_timer, SIGNAL(timeout()), this, SLOT(Reconnect()));
}

void TraceIPC::connectTo(const QString &addr)
{
    m_addr = addr;
#ifdef LOCAL_SOCKET
    m_socket.connectToServer(m_addr);
#else
    m_socket.connectToHost(m_addr, 19191);
#endif
}

void TraceIPC::Reconnect(void)
{
    m_socket.reset();
    connectTo(m_addr);
}

void TraceIPC::socket_connected(void)
{
    qDebug() << "socket_connected";

    emit connected();
}

void TraceIPC::socket_disconnected(void)
{
    qDebug() << "socket_disconnected";

    emit disconnected();
}

void TraceIPC::socket_readReady(void)
{
    TraceIPC::packet_cdma pak_cdma;
    TraceIPC::packet_irq pak_irq;
    TraceIPC::packet_rw pak_rw;
    int i = MAX_JOBS;
    u_int32_t entry;

    while (m_socket.bytesAvailable() >= sizeof(pak_irq) && i--) {
        m_socket.read((char*)&entry, sizeof(entry));

        switch (ntohl(entry)) {
        case PACKET_TRACE_RW:
        case PACKET_TRACE_RW_V2:
            m_socket.read((char*)&pak_rw, sizeof(pak_rw));

            pak_rw.hwaddr           = ntohl(pak_rw.hwaddr);
            pak_rw.offset           = ntohl(pak_rw.offset);
            pak_rw.value            = ntohl(pak_rw.value);
            pak_rw.new_value        = ntohl(pak_rw.new_value);
            pak_rw.__old_is_write   = ntohl(pak_rw.__old_is_write);
            pak_rw.time             = ntohl(pak_rw.time);
            pak_rw.cpu_pc           = ntohl(pak_rw.cpu_pc);
            pak_rw.cpu_id           = ntohl(pak_rw.cpu_id);

            emit regAccess(pak_rw);
            break;
        case PACKET_TRACE_IRQ:
            m_socket.read((char*)&pak_irq, sizeof(pak_irq));

            pak_irq.hwaddr = ntohl(pak_irq.hwaddr);
            pak_irq.hwirq  = ntohl(pak_irq.hwirq);
            pak_irq.status = ntohl(pak_irq.status);
            pak_irq.time   = ntohl(pak_irq.time);
            pak_irq.cpu_pc = ntohl(pak_irq.cpu_pc);
            pak_irq.cpu_id = ntohl(pak_irq.cpu_id);

            emit irqEvent(pak_irq);
            break;
        case PACKET_TRACE_TXT:
        {
            m_socket.read((char*)&entry, sizeof(entry));

            entry = ntohl(entry);

            char *txt = new char[entry];
            m_socket.read(txt, entry);

            emit message(txt);
            break;
        }
        case PACKET_TRACE_CDMA:
            m_socket.read((char*)&pak_cdma, sizeof(pak_cdma));

            pak_cdma.time       = ntohl(pak_cdma.time);
            pak_cdma.data       = ntohl(pak_cdma.data);
            pak_cdma.is_gather  = ntohl(pak_cdma.is_gather);
            pak_cdma.ch_id      = ntohl(pak_cdma.ch_id);

            emit chWrite(ntohl(pak_cdma.ch_id), ntohl(pak_cdma.time),
                         ntohl(pak_cdma.data), ntohl(pak_cdma.is_gather));
            break;
        default:
            Q_ASSERT(0);
            break;
        }
    }
}

#ifdef LOCAL_SOCKET
void TraceIPC::socket_error(QLocalSocket::LocalSocketError)
#else
void TraceIPC::socket_error(QAbstractSocket::SocketError)
#endif
{
    qDebug() << "socket_error" << m_socket.errorString();

    m_reconnect_timer.start(1500);
}

void TraceIPC::changeAddr(const QString &addr)
{
    m_addr = addr;
}

bool TraceIPC::send(void *cmd, qint64 size)
{
    return m_socket.write((char*)cmd, size) == size;
}
