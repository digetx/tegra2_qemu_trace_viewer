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

#ifndef MCDEV_H
#define MCDEV_H

#include "device.h"

class McDev : public Device
{
    Q_OBJECT

public:
    explicit McDev(QObject *parent = 0);

    McDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_emem_cfg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_emem_adr_cfg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_emem_arb_cfg0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_emem_arb_cfg1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_emem_arb_cfg2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gart_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gart_entry_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gart_entry_data_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gart_error_req_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gart_error_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_decerr_emem_others_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_decerr_emem_others_adr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_client_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_client_hotresetn_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_lowlatency_rawlogic_write_participants_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_tmval_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_emem_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_emem_ctrl_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_avpc_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dc_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_dcb_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_epp_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_g2_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_hc_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_isp_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mpcore_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mpea_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mpeb_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mpec_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ppcs_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vde_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vi_orrc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_avpc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_dc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_dcb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_epp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_g2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_hc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_isp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_mpcore_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_mpea_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_mpeb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_mpec_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_nv_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_ppcs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_vde_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_fpri_ctrl_vi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_avpc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_dc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_dcb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_epp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_g2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_hc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_isp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_mpcore_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_mpea_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_mpeb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_mpec_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_nv_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_ppcs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_vde_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_vi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_avpc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_dc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout1_rcoal_dc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_dcb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout1_rcoal_dcb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_epp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_g2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_hc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_mpcore_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_mpea_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_mpeb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_mpec_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_nv_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_ppcs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_vde_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_rcoal_vi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rcoal_autodisable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_avpc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_dc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_dcb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_epp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_g2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_hc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_isp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_mpcore_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_mpea_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_mpeb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_mpec_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_nv_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_ppcs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_vde_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bwshare_vi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intstatus_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_intmask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clken_override_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_security_cfg0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_security_cfg1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_security_violation_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_security_violation_adr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_security_cfg2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_addr_low_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_addr_high_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_clock_limit_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_clocks_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_control_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_hist_limit_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_hist_limit_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_count_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_count_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_hist_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_stat_emc_hist_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_axi_decerr_ovr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_lowlatency_config_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ap_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ap_ctrl_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_client_activity_monitor_emem_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_client_activity_monitor_emem_1_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // MCDEV_H
