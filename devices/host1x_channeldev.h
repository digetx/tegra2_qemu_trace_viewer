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

#ifndef HOST1X_CHANNELDEV_H
#define HOST1X_CHANNELDEV_H

#include "device.h"

class Host1x_channelDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_fifostat_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_indoff_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_indcnt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_inddata_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dmastart_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dmaput_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dmaget_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dmaend_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dmactrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_indoff2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tickcount_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tickcount_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channelctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_raise_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbbufbase_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmdswap_details(const u_int32_t &value, const u_int32_t &new_value);

    bool is_offset_valid(const u_int32_t &offset) const;

    bool is_undef_changed(const u_int32_t &offset,
                          const u_int32_t &value,
                          const u_int32_t &new_value) const;

    // Device interface
private:
    QString get_register_name(const log_entry &entry) const;

    void fill_bits_details(const u_int32_t &offset, const u_int32_t &value,
                           const u_int32_t &new_value);

};

#endif // HOST1X_CHANNELDEV_H
