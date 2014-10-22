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

#include "ictlr_tridev.h"

#include <QDebug>

Ictlr_triDev::Ictlr_triDev(QObject *parent) :
    Device(parent)
{
}

#define TRI_ICTLR_VIRQ_CPU_OFFSET 0x200
#define TRI_ICTLR_VIRQ_CPU_UNDEFMASK 0x40008000
union tri_ictlr_virq_cpu_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_virq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_virq_cpu_u old_value_t = { .reg32 = value };
    const tri_ictlr_virq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Third interrupt controller base registers.\n Valid Interrupt Request Status for CPU Register";
}

#define TRI_ICTLR_VIRQ_COP_OFFSET 0x204
#define TRI_ICTLR_VIRQ_COP_UNDEFMASK 0x40008000
union tri_ictlr_virq_cop_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_virq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_virq_cop_u old_value_t = { .reg32 = value };
    const tri_ictlr_virq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Valid Interrupt Status for COP Register";
}

#define TRI_ICTLR_VFIQ_CPU_OFFSET 0x208
#define TRI_ICTLR_VFIQ_CPU_UNDEFMASK 0x40008000
union tri_ictlr_vfiq_cpu_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_vfiq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_vfiq_cpu_u old_value_t = { .reg32 = value };
    const tri_ictlr_vfiq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for CPU Register";
}

#define TRI_ICTLR_VFIQ_COP_OFFSET 0x20C
#define TRI_ICTLR_VFIQ_COP_UNDEFMASK 0x40008000
union tri_ictlr_vfiq_cop_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_vfiq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_vfiq_cop_u old_value_t = { .reg32 = value };
    const tri_ictlr_vfiq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for COP Register";
}

#define TRI_ICTLR_ISR_OFFSET 0x210
#define TRI_ICTLR_ISR_UNDEFMASK 0x40008000
union tri_ictlr_isr_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_isr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_isr_u old_value_t = { .reg32 = value };
    const tri_ictlr_isr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Latched Interrupt Status Register (HW)";
}

#define TRI_ICTLR_FIR_OFFSET 0x214
#define TRI_ICTLR_FIR_UNDEFMASK 0x40008000
union tri_ictlr_fir_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_fir_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_fir_u old_value_t = { .reg32 = value };
    const tri_ictlr_fir_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Forced Interrupt Status Register (SW)";
}

#define TRI_ICTLR_FIR_SET_OFFSET 0x218
#define TRI_ICTLR_FIR_SET_UNDEFMASK 0x40008000
union tri_ictlr_fir_set_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_fir_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_fir_set_u old_value_t = { .reg32 = value };
    const tri_ictlr_fir_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Set";
}

#define TRI_ICTLR_FIR_CLR_OFFSET 0x21C
#define TRI_ICTLR_FIR_CLR_UNDEFMASK 0x40008000
union tri_ictlr_fir_clr_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_fir_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_fir_clr_u old_value_t = { .reg32 = value };
    const tri_ictlr_fir_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Clear Register";
}

#define TRI_ICTLR_CPU_IER_OFFSET 0x220
#define TRI_ICTLR_CPU_IER_UNDEFMASK 0x40008000
union tri_ictlr_cpu_ier_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cpu_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cpu_ier_u old_value_t = { .reg32 = value };
    const tri_ictlr_cpu_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for CPU Register";
}

#define TRI_ICTLR_CPU_IER_SET_OFFSET 0x224
#define TRI_ICTLR_CPU_IER_SET_UNDEFMASK 0x40008000
union tri_ictlr_cpu_ier_set_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cpu_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cpu_ier_set_u old_value_t = { .reg32 = value };
    const tri_ictlr_cpu_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Enable for CPU Register";
}

#define TRI_ICTLR_CPU_IER_CLR_OFFSET 0x228
#define TRI_ICTLR_CPU_IER_CLR_UNDEFMASK 0x40008000
union tri_ictlr_cpu_ier_clr_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cpu_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cpu_ier_clr_u old_value_t = { .reg32 = value };
    const tri_ictlr_cpu_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPUs Clear Interrupt Enable for CPU";
}

#define TRI_ICTLR_CPU_IEP_CLASS_OFFSET 0x22C
#define TRI_ICTLR_CPU_IEP_CLASS_UNDEFMASK 0x40008000
union tri_ictlr_cpu_iep_class_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cpu_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cpu_iep_class_u old_value_t = { .reg32 = value };
    const tri_ictlr_cpu_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPUs Interrupt Enable Priority Class (FIQ/IRQ)";
}

#define TRI_ICTLR_COP_IER_OFFSET 0x230
#define TRI_ICTLR_COP_IER_UNDEFMASK 0x40008000
union tri_ictlr_cop_ier_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cop_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cop_ier_u old_value_t = { .reg32 = value };
    const tri_ictlr_cop_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for COP Register";
}

#define TRI_ICTLR_COP_IER_SET_OFFSET 0x234
#define TRI_ICTLR_COP_IER_SET_UNDEFMASK 0x40008000
union tri_ictlr_cop_ier_set_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cop_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cop_ier_set_u old_value_t = { .reg32 = value };
    const tri_ictlr_cop_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Source for COP Register";
}

#define TRI_ICTLR_COP_IER_CLR_OFFSET 0x238
#define TRI_ICTLR_COP_IER_CLR_UNDEFMASK 0x40008000
union tri_ictlr_cop_ier_clr_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cop_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cop_ier_clr_u old_value_t = { .reg32 = value };
    const tri_ictlr_cop_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clear Interrupt Source for COP Register";
}

#define TRI_ICTLR_COP_IEP_CLASS_OFFSET 0x23C
#define TRI_ICTLR_COP_IEP_CLASS_UNDEFMASK 0x40008000
union tri_ictlr_cop_iep_class_u {
    struct {
        unsigned int host1x_syncpt_cop:1;
        unsigned int host1x_syncpt_cpu:1;
        unsigned int host1x_gen_cop:1;
        unsigned int host1x_gen_cpu:1;
        unsigned int mpe:1;
        unsigned int vi:1;
        unsigned int epp:1;
        unsigned int isp:1;
        unsigned int gr2d:1;
        unsigned int display:1;
        unsigned int displayb:1;
        unsigned int hdmi:1;
        unsigned int tvo:1;
        unsigned int mc:1;
        unsigned int emc:1;
        unsigned int undefined_bit_15:1;
        unsigned int nor_flash:1;
        unsigned int ac97:1;
        unsigned int sbc2:1;
        unsigned int sbc3:1;
        unsigned int i2c2:1;
        unsigned int kbc:1;
        unsigned int pmu_ext:1;
        unsigned int gpio6:1;
        unsigned int tvdac:1;
        unsigned int gpio7:1;
        unsigned int uart4:1;
        unsigned int uart5:1;
        unsigned int i2c3:1;
        unsigned int sbc4:1;
        unsigned int undefined_bit_30:1;
        unsigned int sw_intr:1;
    };

    u_int32_t reg32;
};

void Ictlr_triDev::fill_tri_ictlr_cop_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tri_ictlr_cop_iep_class_u old_value_t = { .reg32 = value };
    const tri_ictlr_cop_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_syncpt_cop:1", "", 1, old_value_t.host1x_syncpt_cop, new_value_t.host1x_syncpt_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: host1x_syncpt_cpu:1", "", 1, old_value_t.host1x_syncpt_cpu, new_value_t.host1x_syncpt_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1x_gen_cop:1", "", 1, old_value_t.host1x_gen_cop, new_value_t.host1x_gen_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: host1x_gen_cpu:1", "", 1, old_value_t.host1x_gen_cpu, new_value_t.host1x_gen_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe:1", "", 1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "05: vi:1", "", 1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: epp:1", "", 1, old_value_t.epp, new_value_t.epp };
    m_bit_details_model.bits.append(entry);
    entry = { "07: isp:1", "", 1, old_value_t.isp, new_value_t.isp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: gr2d:1", "", 1, old_value_t.gr2d, new_value_t.gr2d };
    m_bit_details_model.bits.append(entry);
    entry = { "09: display:1", "", 1, old_value_t.display, new_value_t.display };
    m_bit_details_model.bits.append(entry);
    entry = { "10: displayb:1", "", 1, old_value_t.displayb, new_value_t.displayb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hdmi:1", "", 1, old_value_t.hdmi, new_value_t.hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: tvo:1", "", 1, old_value_t.tvo, new_value_t.tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mc:1", "", 1, old_value_t.mc, new_value_t.mc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emc:1", "", 1, old_value_t.emc, new_value_t.emc };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: nor_flash:1", "", 1, old_value_t.nor_flash, new_value_t.nor_flash };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ac97:1", "", 1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sbc2:1", "", 1, old_value_t.sbc2, new_value_t.sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sbc3:1", "", 1, old_value_t.sbc3, new_value_t.sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: i2c2:1", "", 1, old_value_t.i2c2, new_value_t.i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: kbc:1", "", 1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pmu_ext:1", "", 1, old_value_t.pmu_ext, new_value_t.pmu_ext };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio6:1", "", 1, old_value_t.gpio6, new_value_t.gpio6 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: tvdac:1", "", 1, old_value_t.tvdac, new_value_t.tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "25: gpio7:1", "", 1, old_value_t.gpio7, new_value_t.gpio7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: uart4:1", "", 1, old_value_t.uart4, new_value_t.uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: uart5:1", "", 1, old_value_t.uart5, new_value_t.uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2c3:1", "", 1, old_value_t.i2c3, new_value_t.i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: sbc4:1", "", 1, old_value_t.sbc4, new_value_t.sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: sw_intr:1", "", 1, old_value_t.sw_intr, new_value_t.sw_intr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COPs Interrupt Enable Priority Class (FIQ/IRQ) Register";
}



bool Ictlr_triDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case TRI_ICTLR_VIRQ_CPU_OFFSET:
    case TRI_ICTLR_VIRQ_COP_OFFSET:
    case TRI_ICTLR_VFIQ_CPU_OFFSET:
    case TRI_ICTLR_VFIQ_COP_OFFSET:
    case TRI_ICTLR_ISR_OFFSET:
    case TRI_ICTLR_FIR_OFFSET:
    case TRI_ICTLR_FIR_SET_OFFSET:
    case TRI_ICTLR_FIR_CLR_OFFSET:
    case TRI_ICTLR_CPU_IER_OFFSET:
    case TRI_ICTLR_CPU_IER_SET_OFFSET:
    case TRI_ICTLR_CPU_IER_CLR_OFFSET:
    case TRI_ICTLR_CPU_IEP_CLASS_OFFSET:
    case TRI_ICTLR_COP_IER_OFFSET:
    case TRI_ICTLR_COP_IER_SET_OFFSET:
    case TRI_ICTLR_COP_IER_CLR_OFFSET:
    case TRI_ICTLR_COP_IEP_CLASS_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Ictlr_triDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case TRI_ICTLR_VIRQ_CPU_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_VIRQ_CPU_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_VIRQ_COP_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_VIRQ_COP_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_VFIQ_CPU_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_VFIQ_CPU_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_VFIQ_COP_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_VFIQ_COP_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_ISR_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_ISR_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_FIR_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_FIR_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_FIR_SET_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_FIR_SET_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_FIR_CLR_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_FIR_CLR_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_CPU_IER_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_CPU_IER_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_CPU_IER_SET_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_CPU_IER_SET_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_CPU_IER_CLR_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_CPU_IER_CLR_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_CPU_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_CPU_IEP_CLASS_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_COP_IER_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_COP_IER_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_COP_IER_SET_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_COP_IER_SET_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_COP_IER_CLR_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_COP_IER_CLR_UNDEFMASK)
            return true;
        break;
    case TRI_ICTLR_COP_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & TRI_ICTLR_COP_IEP_CLASS_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Ictlr_triDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case TRI_ICTLR_VIRQ_CPU_OFFSET:
        return QString("TRI_ICTLR_VIRQ_CPU");
    case TRI_ICTLR_VIRQ_COP_OFFSET:
        return QString("TRI_ICTLR_VIRQ_COP");
    case TRI_ICTLR_VFIQ_CPU_OFFSET:
        return QString("TRI_ICTLR_VFIQ_CPU");
    case TRI_ICTLR_VFIQ_COP_OFFSET:
        return QString("TRI_ICTLR_VFIQ_COP");
    case TRI_ICTLR_ISR_OFFSET:
        return QString("TRI_ICTLR_ISR");
    case TRI_ICTLR_FIR_OFFSET:
        return QString("TRI_ICTLR_FIR");
    case TRI_ICTLR_FIR_SET_OFFSET:
        return QString("TRI_ICTLR_FIR_SET");
    case TRI_ICTLR_FIR_CLR_OFFSET:
        return QString("TRI_ICTLR_FIR_CLR");
    case TRI_ICTLR_CPU_IER_OFFSET:
        return QString("TRI_ICTLR_CPU_IER");
    case TRI_ICTLR_CPU_IER_SET_OFFSET:
        return QString("TRI_ICTLR_CPU_IER_SET");
    case TRI_ICTLR_CPU_IER_CLR_OFFSET:
        return QString("TRI_ICTLR_CPU_IER_CLR");
    case TRI_ICTLR_CPU_IEP_CLASS_OFFSET:
        return QString("TRI_ICTLR_CPU_IEP_CLASS");
    case TRI_ICTLR_COP_IER_OFFSET:
        return QString("TRI_ICTLR_COP_IER");
    case TRI_ICTLR_COP_IER_SET_OFFSET:
        return QString("TRI_ICTLR_COP_IER_SET");
    case TRI_ICTLR_COP_IER_CLR_OFFSET:
        return QString("TRI_ICTLR_COP_IER_CLR");
    case TRI_ICTLR_COP_IEP_CLASS_OFFSET:
        return QString("TRI_ICTLR_COP_IEP_CLASS");

    default:
        break;
    }

    qDebug() << QString().sprintf("ICTLR_TRI: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Ictlr_triDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case TRI_ICTLR_VIRQ_CPU_OFFSET:
        fill_tri_ictlr_virq_cpu_details(value, new_value);
        break;
    case TRI_ICTLR_VIRQ_COP_OFFSET:
        fill_tri_ictlr_virq_cop_details(value, new_value);
        break;
    case TRI_ICTLR_VFIQ_CPU_OFFSET:
        fill_tri_ictlr_vfiq_cpu_details(value, new_value);
        break;
    case TRI_ICTLR_VFIQ_COP_OFFSET:
        fill_tri_ictlr_vfiq_cop_details(value, new_value);
        break;
    case TRI_ICTLR_ISR_OFFSET:
        fill_tri_ictlr_isr_details(value, new_value);
        break;
    case TRI_ICTLR_FIR_OFFSET:
        fill_tri_ictlr_fir_details(value, new_value);
        break;
    case TRI_ICTLR_FIR_SET_OFFSET:
        fill_tri_ictlr_fir_set_details(value, new_value);
        break;
    case TRI_ICTLR_FIR_CLR_OFFSET:
        fill_tri_ictlr_fir_clr_details(value, new_value);
        break;
    case TRI_ICTLR_CPU_IER_OFFSET:
        fill_tri_ictlr_cpu_ier_details(value, new_value);
        break;
    case TRI_ICTLR_CPU_IER_SET_OFFSET:
        fill_tri_ictlr_cpu_ier_set_details(value, new_value);
        break;
    case TRI_ICTLR_CPU_IER_CLR_OFFSET:
        fill_tri_ictlr_cpu_ier_clr_details(value, new_value);
        break;
    case TRI_ICTLR_CPU_IEP_CLASS_OFFSET:
        fill_tri_ictlr_cpu_iep_class_details(value, new_value);
        break;
    case TRI_ICTLR_COP_IER_OFFSET:
        fill_tri_ictlr_cop_ier_details(value, new_value);
        break;
    case TRI_ICTLR_COP_IER_SET_OFFSET:
        fill_tri_ictlr_cop_ier_set_details(value, new_value);
        break;
    case TRI_ICTLR_COP_IER_CLR_OFFSET:
        fill_tri_ictlr_cop_ier_clr_details(value, new_value);
        break;
    case TRI_ICTLR_COP_IEP_CLASS_OFFSET:
        fill_tri_ictlr_cop_iep_class_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
