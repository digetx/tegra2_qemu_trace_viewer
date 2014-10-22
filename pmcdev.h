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

#ifndef PMCDEV_H
#define PMCDEV_H

#include "device.h"

class PmcDev : public Device
{
    Q_OBJECT

public:
    explicit PmcDev(QObject *parent = 0);

    PmcDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sec_disable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pmc_swrst_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_wake_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_wake_lvl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_wake_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sw_wake_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dpd_pads_oride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dpd_sample_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dpd_enable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwrgate_timer_off_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwrgate_timer_on_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwrgate_toggle_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_remove_clamping_cmd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwrgate_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwrgood_timer_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_blink_timer_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_no_iopower_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwr_det_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwr_det_latch_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch9_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch10_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch11_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch12_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch13_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch14_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch15_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch16_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch17_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch18_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch19_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch20_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch21_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch22_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch23_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_scratch0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_scratch1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_scratch2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_scratch3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_scratch4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_secure_scratch5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cpupwrgood_timer_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cpupwroff_timer_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pg_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pg_mask_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_auto_wake_lvl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_auto_wake_lvl_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_wake_delay_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pwr_det_val_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ddr_pwr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_usb_debounce_del_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_usb_ao_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_crypto_op_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllp_wb0_override_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch24_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch25_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch26_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch27_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch28_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch29_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch30_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch31_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch32_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch33_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch34_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch35_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch36_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch37_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch38_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch39_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch40_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch41_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_scratch42_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bondout_mirror0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bondout_mirror1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bondout_mirror2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sys_33v_en_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bondout_mirror_access_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gate_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // PMCDEV_H
