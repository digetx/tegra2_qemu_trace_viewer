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

#ifndef RTCDEV_H
#define RTCDEV_H

#include "device.h"

class RtcDev : public Device
{
    Q_OBJECT

public:
    explicit RtcDev(QObject *parent = 0);

    RtcDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_busy_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_seconds_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_shadow_seconds_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_milli_seconds_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_seconds_alarm0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_seconds_alarm1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_milli_seconds_alarm_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_seconds_countdown_alarm_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_milli_seconds_countdown_alarm_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intr_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intr_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intr_source_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intr_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_correction_factor_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // RTCDEV_H
