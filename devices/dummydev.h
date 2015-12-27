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

#ifndef DUMMYDEV_H
#define DUMMYDEV_H

#include "device.h"

class DummyDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    bool is_offset_valid(const u_int32_t &) const { return true; }

    bool is_undef_changed(const u_int32_t &,
                          const u_int32_t &,
                          const u_int32_t &) const { return false; }

    // Device interface
private:
    QString get_register_name(const log_entry &entry) const
    {
        return QString().sprintf("0x%08X", entry.offset + m_base);
    }

    void fill_bits_details(const u_int32_t &, const u_int32_t &value,
                           const u_int32_t &new_value)
    {
        BitDetails::bit_entry entry = { "00: data:32", "", 32,
                                        value, new_value };

        m_bit_details_model.bits.append(entry);
        m_bit_details_model.has_changed_bits = (value != new_value);
    }

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const
    {
        log_entry entry;

        switch (role) {
        case Qt::EditRole:
            if (index.column() == Device::REGISTER) {
                entry = m_log.read( index.row() );
                return get_register_name(entry);
            }
        default:
            return Device::data(index, role);
        }
    }
};

#endif // DUMMYDEV_H
