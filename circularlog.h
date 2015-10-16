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

#ifndef CIRCULARLOG_H
#define CIRCULARLOG_H

#include <QMutex>
#include <QVarLengthArray>

template <class E_Type>
class CircularLog
{
public:
    explicit CircularLog(unsigned max_log_size);

    E_Type read(int index) const;
    E_Type read_last(void) const;
    bool isFull(void) const;
    unsigned size(void) const;
    void write(E_Type entry);
    void clear(void);

private:
    mutable QMutex mutex;
    QVarLengthArray<E_Type> m_log;
    const unsigned m_max_log_size;
    unsigned m_log_pointer_last;
    unsigned m_log_pointer;
    unsigned m_log_size;
};

template <class E_Type>
CircularLog<E_Type>::CircularLog(unsigned max_log_size)
    : m_max_log_size(max_log_size)
{
    m_log_pointer_last = 0;
    m_log_pointer = 0;
    m_log_size = 0;
    m_log.clear();
}

template <class E_Type>
E_Type CircularLog<E_Type>::read(int index) const
{
    E_Type entry;

    mutex.lock();

    if (m_log_size >= m_max_log_size) {
        index += m_log_pointer;

        if (index >= m_log_size)
            index -= m_max_log_size;
    }

    entry = m_log.value(index);

    mutex.unlock();

    return entry;
}

template <class E_Type>
E_Type CircularLog<E_Type>::read_last(void) const
{
    E_Type entry;

    mutex.lock();
    entry = m_log.value(m_log_pointer_last);
    mutex.unlock();

    return entry;
}

template <class E_Type>
void CircularLog<E_Type>::write(E_Type entry)
{
    mutex.lock();

    if (m_log_size < m_max_log_size)
        m_log.append(entry);
    else
        m_log.replace(m_log_pointer, entry);

    m_log_pointer_last = m_log_pointer;
    m_log_pointer = (++m_log_pointer == m_max_log_size) ? 0 : m_log_pointer;

    m_log_size = qMin(m_log_size + 1, m_max_log_size);

    mutex.unlock();
}

template <class E_Type>
bool CircularLog<E_Type>::isFull(void) const
{
    return (m_log_size == m_max_log_size);
}

template <class E_Type>
void CircularLog<E_Type>::clear(void)
{
    mutex.lock();

    m_log.clear();
    m_log_size = 0;

    mutex.unlock();
}

template <class E_Type>
unsigned CircularLog<E_Type>::size(void) const
{
    return m_log_size;
}


#endif // CIRCULARLOG_H
