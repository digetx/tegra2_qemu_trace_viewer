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

#ifndef BSEDEV_H
#define BSEDEV_H

#include "device.h"

class BseDev : public Device
{
    Q_OBJECT

public:
    explicit BseDev(QObject *parent = 0);

    BseDev(const QString name, u_int32_t base) :
        Device(name, base), m_state(BseDev::IDLE) {}

signals:

public slots:

private:
    void fill_icmdque_wr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmdque_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intr_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bse_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_dest_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_input_select_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_config_ext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_security_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_hash_result0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_hash_result1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_hash_result2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_hash_result3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_sec_sel7_details(const u_int32_t &value, const u_int32_t &new_value);

    bool is_offset_valid(const u_int32_t &offset) const;

    bool is_undef_changed(const u_int32_t &offset,
                          const u_int32_t &value,
                          const u_int32_t &new_value) const;

    void update_internal(log_entry &entry);

    typedef enum {
        IDLE,
        DMA_SETUP,
        COPY_TO_VRAM
    } bse_state;

    bse_state m_state;

    // Device interface
private:
    QString get_register_name(const log_entry &entry) const;

    void fill_bits_details(const u_int32_t &offset, const u_int32_t &value,
                           const u_int32_t &new_value);

};

#endif // BSEDEV_H
