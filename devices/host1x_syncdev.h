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

#ifndef HOST1X_SYNCDEV_H
#define HOST1X_SYNCDEV_H

#include "device.h"

class Host1x_syncDev : public Device
{
    Q_OBJECT

public:
    explicit Host1x_syncDev(QObject *parent = 0);

    Host1x_syncDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_intstatus_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intmask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intc0mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intc1mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hintstatus_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hintmask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hintstatus_ext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hintmask_ext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_cpu0_int_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_cpu1_int_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_int_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_int_mask_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_int_disable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_int_enable_cpu0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_thresh_int_enable_cpu1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf0_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf1_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf2_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf3_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf4_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf5_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf6_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf7_setup_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cf_setupdone_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmdproc_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmdproc_stat_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmdproc_stop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch_teardown_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mod_teardown_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch0_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch1_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch2_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch3_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch4_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch5_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch6_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ch7_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_display_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_displayb_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_epp_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gr3d_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_isp_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mpe_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tvo_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dsi_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hdmi_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vi_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gr2d_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_direct_module_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_usec_clk_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ctxsw_timeout_cfg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_indreg_dma_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_priority_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cdma_asm_timeout_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cdma_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ip_busy_timeout_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ip_read_timeout_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ip_write_timeout_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mccif_thctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hc_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_wcoal_hc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hwlock7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_9_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_10_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_11_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_12_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_13_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_14_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_15_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_9_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_10_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_11_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_12_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_13_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_14_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_owner_15_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mlock_error_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_9_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_10_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_11_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_12_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_13_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_14_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_15_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_16_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_17_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_18_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_19_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_20_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_21_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_22_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_23_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_24_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_25_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_26_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_27_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_28_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_29_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_30_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_31_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_9_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_10_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_11_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_12_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_13_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_14_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_15_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_16_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_17_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_18_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_19_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_20_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_21_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_22_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_23_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_24_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_25_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_26_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_27_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_28_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_29_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_30_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_int_thresh_31_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_base_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_syncpt_cpu_incr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbread7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_regf_data_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_regf_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_waitovr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfpeek_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfpeek_read_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfpeek_ptrs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cbstat7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cdma_stats_words_fetched_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cdma_stats_words_discarded_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cfg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_arb_count_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_wrap_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_status0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_buffer_threshold0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_conf0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_swap0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_line0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_clid0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_baddr0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdma_dmatrigger0_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // HOST1X_SYNCDEV_H
