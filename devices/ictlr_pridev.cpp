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

#include "ictlr_pridev.h"

#include <QDebug>

#define PRI_ICTLR_VIRQ_CPU_OFFSET 0x0
#define PRI_ICTLR_VIRQ_CPU_UNDEFMASK 0x00000000
union pri_ictlr_virq_cpu_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_virq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_virq_cpu_u old_value_t = { .reg32 = value };
    const pri_ictlr_virq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Valid Interrupt Request Status for CPU Register";
}

#define PRI_ICTLR_VIRQ_COP_OFFSET 0x4
#define PRI_ICTLR_VIRQ_COP_UNDEFMASK 0x00000000
union pri_ictlr_virq_cop_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_virq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_virq_cop_u old_value_t = { .reg32 = value };
    const pri_ictlr_virq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Valid Interrupt Status for AVP (COP) Register";
}

#define PRI_ICTLR_VFIQ_CPU_OFFSET 0x8
#define PRI_ICTLR_VFIQ_CPU_UNDEFMASK 0x00000000
union pri_ictlr_vfiq_cpu_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_vfiq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_vfiq_cpu_u old_value_t = { .reg32 = value };
    const pri_ictlr_vfiq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Valid Interrupt Status for CPU Register";
}

#define PRI_ICTLR_VFIQ_COP_OFFSET 0xC
#define PRI_ICTLR_VFIQ_COP_UNDEFMASK 0x00000000
union pri_ictlr_vfiq_cop_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_vfiq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_vfiq_cop_u old_value_t = { .reg32 = value };
    const pri_ictlr_vfiq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for AVP (COP) Register";
}

#define PRI_ICTLR_ISR_OFFSET 0x10
#define PRI_ICTLR_ISR_UNDEFMASK 0x00000000
union pri_ictlr_isr_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_isr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_isr_u old_value_t = { .reg32 = value };
    const pri_ictlr_isr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Latched Interrupt Status Register (Hardware)";
}

#define PRI_ICTLR_FIR_OFFSET 0x14
#define PRI_ICTLR_FIR_UNDEFMASK 0x00000000
union pri_ictlr_fir_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_fir_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_fir_u old_value_t = { .reg32 = value };
    const pri_ictlr_fir_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Forced Interrupt Status Register (Software)";
}

#define PRI_ICTLR_FIR_SET_OFFSET 0x18
#define PRI_ICTLR_FIR_SET_UNDEFMASK 0x00000000
union pri_ictlr_fir_set_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_fir_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_fir_set_u old_value_t = { .reg32 = value };
    const pri_ictlr_fir_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Set";
}

#define PRI_ICTLR_FIR_CLR_OFFSET 0x1C
#define PRI_ICTLR_FIR_CLR_UNDEFMASK 0x00000000
union pri_ictlr_fir_clr_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_fir_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_fir_clr_u old_value_t = { .reg32 = value };
    const pri_ictlr_fir_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Clear Register";
}

#define PRI_ICTLR_CPU_IER_OFFSET 0x20
#define PRI_ICTLR_CPU_IER_UNDEFMASK 0x00000000
union pri_ictlr_cpu_ier_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cpu_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cpu_ier_u old_value_t = { .reg32 = value };
    const pri_ictlr_cpu_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for CPU Register";
}

#define PRI_ICTLR_CPU_IER_SET_OFFSET 0x24
#define PRI_ICTLR_CPU_IER_SET_UNDEFMASK 0x00000000
union pri_ictlr_cpu_ier_set_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cpu_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cpu_ier_set_u old_value_t = { .reg32 = value };
    const pri_ictlr_cpu_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Enable for CPU Register";
}

#define PRI_ICTLR_CPU_IER_CLR_OFFSET 0x28
#define PRI_ICTLR_CPU_IER_CLR_UNDEFMASK 0x00000000
union pri_ictlr_cpu_ier_clr_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cpu_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cpu_ier_clr_u old_value_t = { .reg32 = value };
    const pri_ictlr_cpu_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Clear Interrupt Enable for CPU";
}

#define PRI_ICTLR_CPU_IEP_CLASS_OFFSET 0x2C
#define PRI_ICTLR_CPU_IEP_CLASS_UNDEFMASK 0x00000000
union pri_ictlr_cpu_iep_class_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cpu_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cpu_iep_class_u old_value_t = { .reg32 = value };
    const pri_ictlr_cpu_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Interrupt Enable Priority Class (FIQ/IRQ)";
}

#define PRI_ICTLR_COP_IER_OFFSET 0x30
#define PRI_ICTLR_COP_IER_UNDEFMASK 0x00000000
union pri_ictlr_cop_ier_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cop_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cop_ier_u old_value_t = { .reg32 = value };
    const pri_ictlr_cop_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for AVP (COP) Register";
}

#define PRI_ICTLR_COP_IER_SET_OFFSET 0x34
#define PRI_ICTLR_COP_IER_SET_UNDEFMASK 0x00000000
union pri_ictlr_cop_ier_set_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cop_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cop_ier_set_u old_value_t = { .reg32 = value };
    const pri_ictlr_cop_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Source for COP Register";
}

#define PRI_ICTLR_COP_IER_CLR_OFFSET 0x38
#define PRI_ICTLR_COP_IER_CLR_UNDEFMASK 0x00000000
union pri_ictlr_cop_ier_clr_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cop_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cop_ier_clr_u old_value_t = { .reg32 = value };
    const pri_ictlr_cop_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clear Interrupt Source for COP Register";
}

#define PRI_ICTLR_COP_IEP_CLASS_OFFSET 0x3C
#define PRI_ICTLR_COP_IEP_CLASS_UNDEFMASK 0x00000000
union pri_ictlr_cop_iep_class_u {
    struct {
        unsigned int tmr1:1;
        unsigned int tmr2:1;
        unsigned int rtc:1;
        unsigned int i2s2:1;
        unsigned int shr_sem_inbox_full:1;
        unsigned int shr_sem_inbox_empty:1;
        unsigned int shr_sem_outbox_full:1;
        unsigned int shr_sem_outbox_empty:1;
        unsigned int vde_ucq:1;
        unsigned int vde_sync_token:1;
        unsigned int vde_bsev:1;
        unsigned int vde_bsea:1;
        unsigned int vde_sxe:1;
        unsigned int i2s1:1;
        unsigned int sdmmc1:1;
        unsigned int sdmmc2:1;
        unsigned int xio:1;
        unsigned int vde:1;
        unsigned int avp_ucq:1;
        unsigned int sdmmc3:1;
        unsigned int usb:1;
        unsigned int usb2:1;
        unsigned int reserved:1;
        unsigned int eide:1;
        unsigned int nandctrl:1;
        unsigned int vcp:1;
        unsigned int apb_dma_cpu:1;
        unsigned int ahb_dma_cpu:1;
        unsigned int arb_sem_gnt_cop:1;
        unsigned int arb_sem_gnt_cpu:1;
        unsigned int owr:1;
        unsigned int sdmmc4:1;
    };

    u_int32_t reg32;
};

void Ictlr_priDev::fill_pri_ictlr_cop_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_cop_iep_class_u old_value_t = { .reg32 = value };
    const pri_ictlr_cop_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr1:1", "", 1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: tmr2:1", "", 1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc:1", "", 1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: i2s2:1", "", 1, old_value_t.i2s2, new_value_t.i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: shr_sem_inbox_full:1", "", 1, old_value_t.shr_sem_inbox_full, new_value_t.shr_sem_inbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "05: shr_sem_inbox_empty:1", "", 1, old_value_t.shr_sem_inbox_empty, new_value_t.shr_sem_inbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "06: shr_sem_outbox_full:1", "", 1, old_value_t.shr_sem_outbox_full, new_value_t.shr_sem_outbox_full };
    m_bit_details_model.bits.append(entry);
    entry = { "07: shr_sem_outbox_empty:1", "", 1, old_value_t.shr_sem_outbox_empty, new_value_t.shr_sem_outbox_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vde_ucq:1", "", 1, old_value_t.vde_ucq, new_value_t.vde_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vde_sync_token:1", "", 1, old_value_t.vde_sync_token, new_value_t.vde_sync_token };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vde_bsev:1", "", 1, old_value_t.vde_bsev, new_value_t.vde_bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bsea:1", "", 1, old_value_t.vde_bsea, new_value_t.vde_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vde_sxe:1", "", 1, old_value_t.vde_sxe, new_value_t.vde_sxe };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2s1:1", "", 1, old_value_t.i2s1, new_value_t.i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdmmc1:1", "", 1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sdmmc2:1", "", 1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xio:1", "", 1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vde:1", "", 1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "18: avp_ucq:1", "", 1, old_value_t.avp_ucq, new_value_t.avp_ucq };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc3:1", "", 1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: usb:1", "", 1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "21: usb2:1", "", 1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: reserved:1", "", 1, old_value_t.reserved, new_value_t.reserved };
    m_bit_details_model.bits.append(entry);
    entry = { "23: eide:1", "", 1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "24: nandctrl:1", "", 1, old_value_t.nandctrl, new_value_t.nandctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "25: vcp:1", "", 1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: apb_dma_cpu:1", "", 1, old_value_t.apb_dma_cpu, new_value_t.apb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_dma_cpu:1", "", 1, old_value_t.ahb_dma_cpu, new_value_t.ahb_dma_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "28: arb_sem_gnt_cop:1", "", 1, old_value_t.arb_sem_gnt_cop, new_value_t.arb_sem_gnt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: arb_sem_gnt_cpu:1", "", 1, old_value_t.arb_sem_gnt_cpu, new_value_t.arb_sem_gnt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr:1", "", 1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sdmmc4:1", "", 1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Interrupt Enable Priority Class (FIQ/IRQ) Register";
}



bool Ictlr_priDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case PRI_ICTLR_VIRQ_CPU_OFFSET:
    case PRI_ICTLR_VIRQ_COP_OFFSET:
    case PRI_ICTLR_VFIQ_CPU_OFFSET:
    case PRI_ICTLR_VFIQ_COP_OFFSET:
    case PRI_ICTLR_ISR_OFFSET:
    case PRI_ICTLR_FIR_OFFSET:
    case PRI_ICTLR_FIR_SET_OFFSET:
    case PRI_ICTLR_FIR_CLR_OFFSET:
    case PRI_ICTLR_CPU_IER_OFFSET:
    case PRI_ICTLR_CPU_IER_SET_OFFSET:
    case PRI_ICTLR_CPU_IER_CLR_OFFSET:
    case PRI_ICTLR_CPU_IEP_CLASS_OFFSET:
    case PRI_ICTLR_COP_IER_OFFSET:
    case PRI_ICTLR_COP_IER_SET_OFFSET:
    case PRI_ICTLR_COP_IER_CLR_OFFSET:
    case PRI_ICTLR_COP_IEP_CLASS_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Ictlr_priDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case PRI_ICTLR_VIRQ_CPU_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_VIRQ_CPU_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_VIRQ_COP_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_VIRQ_COP_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_VFIQ_CPU_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_VFIQ_CPU_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_VFIQ_COP_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_VFIQ_COP_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_ISR_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_ISR_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_FIR_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_FIR_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_FIR_SET_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_FIR_SET_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_FIR_CLR_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_FIR_CLR_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_CPU_IER_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_CPU_IER_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_CPU_IER_SET_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_CPU_IER_SET_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_CPU_IER_CLR_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_CPU_IER_CLR_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_CPU_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_CPU_IEP_CLASS_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_COP_IER_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_COP_IER_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_COP_IER_SET_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_COP_IER_SET_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_COP_IER_CLR_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_COP_IER_CLR_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_COP_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_COP_IEP_CLASS_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Ictlr_priDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case PRI_ICTLR_VIRQ_CPU_OFFSET:
        return QString("PRI_ICTLR_VIRQ_CPU");
    case PRI_ICTLR_VIRQ_COP_OFFSET:
        return QString("PRI_ICTLR_VIRQ_COP");
    case PRI_ICTLR_VFIQ_CPU_OFFSET:
        return QString("PRI_ICTLR_VFIQ_CPU");
    case PRI_ICTLR_VFIQ_COP_OFFSET:
        return QString("PRI_ICTLR_VFIQ_COP");
    case PRI_ICTLR_ISR_OFFSET:
        return QString("PRI_ICTLR_ISR");
    case PRI_ICTLR_FIR_OFFSET:
        return QString("PRI_ICTLR_FIR");
    case PRI_ICTLR_FIR_SET_OFFSET:
        return QString("PRI_ICTLR_FIR_SET");
    case PRI_ICTLR_FIR_CLR_OFFSET:
        return QString("PRI_ICTLR_FIR_CLR");
    case PRI_ICTLR_CPU_IER_OFFSET:
        return QString("PRI_ICTLR_CPU_IER");
    case PRI_ICTLR_CPU_IER_SET_OFFSET:
        return QString("PRI_ICTLR_CPU_IER_SET");
    case PRI_ICTLR_CPU_IER_CLR_OFFSET:
        return QString("PRI_ICTLR_CPU_IER_CLR");
    case PRI_ICTLR_CPU_IEP_CLASS_OFFSET:
        return QString("PRI_ICTLR_CPU_IEP_CLASS");
    case PRI_ICTLR_COP_IER_OFFSET:
        return QString("PRI_ICTLR_COP_IER");
    case PRI_ICTLR_COP_IER_SET_OFFSET:
        return QString("PRI_ICTLR_COP_IER_SET");
    case PRI_ICTLR_COP_IER_CLR_OFFSET:
        return QString("PRI_ICTLR_COP_IER_CLR");
    case PRI_ICTLR_COP_IEP_CLASS_OFFSET:
        return QString("PRI_ICTLR_COP_IEP_CLASS");

    default:
        break;
    }

    qDebug() << QString().sprintf("ICTLR_PRI: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Ictlr_priDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case PRI_ICTLR_VIRQ_CPU_OFFSET:
        fill_pri_ictlr_virq_cpu_details(value, new_value);
        break;
    case PRI_ICTLR_VIRQ_COP_OFFSET:
        fill_pri_ictlr_virq_cop_details(value, new_value);
        break;
    case PRI_ICTLR_VFIQ_CPU_OFFSET:
        fill_pri_ictlr_vfiq_cpu_details(value, new_value);
        break;
    case PRI_ICTLR_VFIQ_COP_OFFSET:
        fill_pri_ictlr_vfiq_cop_details(value, new_value);
        break;
    case PRI_ICTLR_ISR_OFFSET:
        fill_pri_ictlr_isr_details(value, new_value);
        break;
    case PRI_ICTLR_FIR_OFFSET:
        fill_pri_ictlr_fir_details(value, new_value);
        break;
    case PRI_ICTLR_FIR_SET_OFFSET:
        fill_pri_ictlr_fir_set_details(value, new_value);
        break;
    case PRI_ICTLR_FIR_CLR_OFFSET:
        fill_pri_ictlr_fir_clr_details(value, new_value);
        break;
    case PRI_ICTLR_CPU_IER_OFFSET:
        fill_pri_ictlr_cpu_ier_details(value, new_value);
        break;
    case PRI_ICTLR_CPU_IER_SET_OFFSET:
        fill_pri_ictlr_cpu_ier_set_details(value, new_value);
        break;
    case PRI_ICTLR_CPU_IER_CLR_OFFSET:
        fill_pri_ictlr_cpu_ier_clr_details(value, new_value);
        break;
    case PRI_ICTLR_CPU_IEP_CLASS_OFFSET:
        fill_pri_ictlr_cpu_iep_class_details(value, new_value);
        break;
    case PRI_ICTLR_COP_IER_OFFSET:
        fill_pri_ictlr_cop_ier_details(value, new_value);
        break;
    case PRI_ICTLR_COP_IER_SET_OFFSET:
        fill_pri_ictlr_cop_ier_set_details(value, new_value);
        break;
    case PRI_ICTLR_COP_IER_CLR_OFFSET:
        fill_pri_ictlr_cop_ier_clr_details(value, new_value);
        break;
    case PRI_ICTLR_COP_IEP_CLASS_OFFSET:
        fill_pri_ictlr_cop_iep_class_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
