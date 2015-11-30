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

#ifndef FUSEDEV_H
#define FUSEDEV_H

#include "device.h"

class FuseDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_fuse_fusebypass_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_write_access_sw_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_jtag_secureid_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_jtag_secureid_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_sku_info_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_process_calib_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_io_calib_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_dac_crt_calib_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_dac_hdtv_calib_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_dac_sdtv_calib_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_reserved_production_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_9_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_10_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_11_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_12_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_13_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_14_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_15_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_16_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_17_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_18_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_19_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_20_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_21_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_22_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_23_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_24_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_25_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_26_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_27_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_28_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_29_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_30_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_31_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_32_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_33_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_34_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_35_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_36_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_37_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_38_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_39_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_40_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_41_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_42_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_43_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_44_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_45_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_46_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_47_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_48_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_49_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_50_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_51_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_52_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_53_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_54_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_55_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_56_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_57_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_58_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_59_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_60_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fuse_spare_bit_61_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // FUSEDEV_H
