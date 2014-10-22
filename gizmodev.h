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

#ifndef GIZMODEV_H
#define GIZMODEV_H

#include "device.h"

class GizmoDev : public Device
{
    Q_OBJECT

public:
    explicit GizmoDev(QObject *parent = 0);

    GizmoDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_ahb_mem_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_apb_dma_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ide_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_usb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_xbar_bridge_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cpu_ahb_bridge_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cop_ahb_bridge_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_xbar_apb_ctlr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vcp_ahb_bridge_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nand_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sdmmc4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_xio_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bsev_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_bsea_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nor_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_usb2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_usb3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sdmmc1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sdmmc2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sdmmc3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mem_prefetch_cfg_x_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_xbar_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mem_prefetch_cfg3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mem_prefetch_cfg4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_avp_ppcs_rd_coh_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mem_prefetch_cfg1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mem_prefetch_cfg2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_ahbslvmem_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_ahb_mem_wrque_mst_id_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_cpu_abort_info_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_cpu_abort_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_cop_abort_info_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_cop_abort_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_avpc_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_timeout_wcoal_avpc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_disable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_priority_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahb_arbitration_usr_protect_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // GIZMODEV_H
