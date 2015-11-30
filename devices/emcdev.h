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

#ifndef EMCDEV_H
#define EMCDEV_H

#include "device.h"

class EmcDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_intstatus_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intmask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dbg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_adr_cfg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_adr_cfg_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_refctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pin_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timing_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rfc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ras_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_r2w_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_w2r_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_r2p_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_w2p_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rd_rcd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_wr_rcd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rrd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_wdv_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_quse_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_qrst_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_qsafe_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdv_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_refresh_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_burst_refresh_num_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pdex2wr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pdex2rd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pchg2pden_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_act2pden_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ar2pden_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rw2pden_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_txsr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tcke_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tfaw_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_trpab_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tclkstable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tclkstop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_trefbw_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_quse_extra_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_odt_write_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_odt_read_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mrs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_emrs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ref_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pre_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_self_ref_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dpd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mrw_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mrr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_cfg1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_dqsib_dly_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_dqsib_dly_msb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_cfg5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_quse_dly_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_quse_dly_msb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_cfg6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dqs_trimmer_rd0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dqs_trimmer_rd1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dqs_trimmer_rd2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dqs_trimmer_rd3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ll_arb_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_t_min_critical_hp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_t_min_critical_timeout_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_t_min_load_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_t_max_critical_hp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_t_max_critical_timeout_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_t_max_load_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_auto_cal_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_auto_cal_interval_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_auto_cal_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_req_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_emc_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_dig_dll_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dll_xform_dqs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dll_xform_quse_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dig_dll_upper_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dig_dll_lower_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ctt_term_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_zcal_ref_cnt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_zcal_wait_cnt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_zcal_mrw_cmd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmdq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_spare_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fbio_wrptr_eq_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clken_override_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_addr_low_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_addr_high_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_clock_limit_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_clocks_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_hist_limit_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_count_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_llmc_hist_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_pwr_clock_limit_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_pwr_clocks_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_pwr_count_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_clock_limit_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_clock_limit_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_clocks_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_clocks_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_activate_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_activate_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_read_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_read_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_write_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_write_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_ref_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_ref_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_cumm_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_cumm_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_cumm_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_cumm_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_cke_eq1_clks_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_cke_eq1_clks_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_extclks_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_extclks_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_extclks_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_extclks_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_activate_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_activate_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_read_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_read_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_write_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_write_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_ref_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_ref_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_cumm_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_cumm_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_cumm_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_cumm_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_cke_eq1_clks_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_cke_eq1_clks_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_extclks_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_extclks_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_extclks_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_extclks_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_no_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_no_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_no_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev0_no_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_no_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_no_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_no_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_dram_dev1_no_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_clktrim_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_clktrim_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_clktrim_2_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // EMCDEV_H
