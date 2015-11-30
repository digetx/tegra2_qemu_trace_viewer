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

#include "ictlr_secdev.h"

#include <QDebug>

#define SEC_ICTLR_VIRQ_CPU_OFFSET 0x100
#define SEC_ICTLR_VIRQ_CPU_UNDEFMASK 0x04000000
union sec_ictlr_virq_cpu_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_virq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_virq_cpu_u old_value_t = { .reg32 = value };
    const sec_ictlr_virq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Second interrupt controller base registers.\nValid Interrupt Request Status for CPU Register";
}

#define SEC_ICTLR_VIRQ_COP_OFFSET 0x104
#define SEC_ICTLR_VIRQ_COP_UNDEFMASK 0x04000000
union sec_ictlr_virq_cop_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_virq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_virq_cop_u old_value_t = { .reg32 = value };
    const sec_ictlr_virq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Valid Interrupt Status for COP Register";
}

#define SEC_ICTLR_VFIQ_CPU_OFFSET 0x108
#define SEC_ICTLR_VFIQ_CPU_UNDEFMASK 0x04000000
union sec_ictlr_vfiq_cpu_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_vfiq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_vfiq_cpu_u old_value_t = { .reg32 = value };
    const sec_ictlr_vfiq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for CPU Register";
}

#define SEC_ICTLR_VFIQ_COP_OFFSET 0x10C
#define SEC_ICTLR_VFIQ_COP_UNDEFMASK 0x04000000
union sec_ictlr_vfiq_cop_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_vfiq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_vfiq_cop_u old_value_t = { .reg32 = value };
    const sec_ictlr_vfiq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for COP Register";
}

#define SEC_ICTLR_ISR_OFFSET 0x110
#define SEC_ICTLR_ISR_UNDEFMASK 0x04000000
union sec_ictlr_isr_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_isr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_isr_u old_value_t = { .reg32 = value };
    const sec_ictlr_isr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Latched Interrupt Status Register (HW)";
}

#define SEC_ICTLR_FIR_OFFSET 0x114
#define SEC_ICTLR_FIR_UNDEFMASK 0x04000000
union sec_ictlr_fir_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_fir_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_fir_u old_value_t = { .reg32 = value };
    const sec_ictlr_fir_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Forced Interrupt Status Register (SW)";
}

#define SEC_ICTLR_FIR_SET_OFFSET 0x118
#define SEC_ICTLR_FIR_SET_UNDEFMASK 0x04000000
union sec_ictlr_fir_set_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_fir_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_fir_set_u old_value_t = { .reg32 = value };
    const sec_ictlr_fir_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Set";
}

#define SEC_ICTLR_FIR_CLR_OFFSET 0x11C
#define SEC_ICTLR_FIR_CLR_UNDEFMASK 0x04000000
union sec_ictlr_fir_clr_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_fir_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_fir_clr_u old_value_t = { .reg32 = value };
    const sec_ictlr_fir_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Clear Register";
}

#define SEC_ICTLR_CPU_IER_OFFSET 0x120
#define SEC_ICTLR_CPU_IER_UNDEFMASK 0x04000000
union sec_ictlr_cpu_ier_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cpu_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cpu_ier_u old_value_t = { .reg32 = value };
    const sec_ictlr_cpu_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for CPU Register";
}

#define SEC_ICTLR_CPU_IER_SET_OFFSET 0x124
#define SEC_ICTLR_CPU_IER_SET_UNDEFMASK 0x04000000
union sec_ictlr_cpu_ier_set_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cpu_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cpu_ier_set_u old_value_t = { .reg32 = value };
    const sec_ictlr_cpu_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Enable for CPU Register";
}

#define SEC_ICTLR_CPU_IER_CLR_OFFSET 0x128
#define SEC_ICTLR_CPU_IER_CLR_UNDEFMASK 0x04000000
union sec_ictlr_cpu_ier_clr_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cpu_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cpu_ier_clr_u old_value_t = { .reg32 = value };
    const sec_ictlr_cpu_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPUs Clear Interrupt Enable for CPU";
}

#define SEC_ICTLR_CPU_IEP_CLASS_OFFSET 0x12C
#define SEC_ICTLR_CPU_IEP_CLASS_UNDEFMASK 0x04000000
union sec_ictlr_cpu_iep_class_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cpu_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cpu_iep_class_u old_value_t = { .reg32 = value };
    const sec_ictlr_cpu_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPUs Interrupt Enable Priority Class (FIQ/IRQ)";
}

#define SEC_ICTLR_COP_IER_OFFSET 0x130
#define SEC_ICTLR_COP_IER_UNDEFMASK 0x04000000
union sec_ictlr_cop_ier_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cop_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cop_ier_u old_value_t = { .reg32 = value };
    const sec_ictlr_cop_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for COP Register";
}

#define SEC_ICTLR_COP_IER_SET_OFFSET 0x134
#define SEC_ICTLR_COP_IER_SET_UNDEFMASK 0x04000000
union sec_ictlr_cop_ier_set_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cop_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cop_ier_set_u old_value_t = { .reg32 = value };
    const sec_ictlr_cop_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Source for COP Register";
}

#define SEC_ICTLR_COP_IER_CLR_OFFSET 0x138
#define SEC_ICTLR_COP_IER_CLR_UNDEFMASK 0x04000000
union sec_ictlr_cop_ier_clr_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cop_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cop_ier_clr_u old_value_t = { .reg32 = value };
    const sec_ictlr_cop_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clear Interrupt Source for COP Register";
}

#define SEC_ICTLR_COP_IEP_CLASS_OFFSET 0x13C
#define SEC_ICTLR_COP_IEP_CLASS_UNDEFMASK 0x04000000
union sec_ictlr_cop_iep_class_u {
    struct {
        unsigned int gpio1:1;
        unsigned int gpio2:1;
        unsigned int gpio3:1;
        unsigned int gpio4:1;
        unsigned int uart1:1;
        unsigned int uart2:1;
        unsigned int i2c:1;
        unsigned int spi:1;
        unsigned int twc:1;
        unsigned int tmr3:1;
        unsigned int tmr4:1;
        unsigned int flow_rsm_cpu:1;
        unsigned int flow_rsm_cop:1;
        unsigned int spdif:1;
        unsigned int uart3:1;
        unsigned int mipi_hs:1;
        unsigned int event_gpio_a:1;
        unsigned int event_gpio_b:1;
        unsigned int event_gpio_c:1;
        unsigned int event_gpio_d:1;
        unsigned int vfir:1;
        unsigned int dvc:1;
        unsigned int stat_mon:1;
        unsigned int gpio5:1;
        unsigned int cpu0_pmu_intr:1;
        unsigned int cpu1_pmu_intr:1;
        unsigned int undefined_bit_26:1;
        unsigned int sbc1:1;
        unsigned int apb_dma_cop:1;
        unsigned int ahb_dma_cop:1;
        unsigned int dma_tx:1;
        unsigned int dma_rx:1;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_cop_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_cop_iep_class_u old_value_t = { .reg32 = value };
    const sec_ictlr_cop_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gpio1:1", "", 1, old_value_t.gpio1, new_value_t.gpio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gpio2:1", "", 1, old_value_t.gpio2, new_value_t.gpio2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpio3:1", "", 1, old_value_t.gpio3, new_value_t.gpio3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: gpio4:1", "", 1, old_value_t.gpio4, new_value_t.gpio4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uart1:1", "", 1, old_value_t.uart1, new_value_t.uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: uart2:1", "", 1, old_value_t.uart2, new_value_t.uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2c:1", "", 1, old_value_t.i2c, new_value_t.i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi:1", "", 1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: twc:1", "", 1, old_value_t.twc, new_value_t.twc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: tmr3:1", "", 1, old_value_t.tmr3, new_value_t.tmr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: tmr4:1", "", 1, old_value_t.tmr4, new_value_t.tmr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: flow_rsm_cpu:1", "", 1, old_value_t.flow_rsm_cpu, new_value_t.flow_rsm_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "12: flow_rsm_cop:1", "", 1, old_value_t.flow_rsm_cop, new_value_t.flow_rsm_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "13: spdif:1", "", 1, old_value_t.spdif, new_value_t.spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart3:1", "", 1, old_value_t.uart3, new_value_t.uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mipi_hs:1", "", 1, old_value_t.mipi_hs, new_value_t.mipi_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "16: event_gpio_a:1", "", 1, old_value_t.event_gpio_a, new_value_t.event_gpio_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: event_gpio_b:1", "", 1, old_value_t.event_gpio_b, new_value_t.event_gpio_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: event_gpio_c:1", "", 1, old_value_t.event_gpio_c, new_value_t.event_gpio_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: event_gpio_d:1", "", 1, old_value_t.event_gpio_d, new_value_t.event_gpio_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vfir:1", "", 1, old_value_t.vfir, new_value_t.vfir };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dvc:1", "", 1, old_value_t.dvc, new_value_t.dvc };
    m_bit_details_model.bits.append(entry);
    entry = { "22: stat_mon:1", "", 1, old_value_t.stat_mon, new_value_t.stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "23: gpio5:1", "", 1, old_value_t.gpio5, new_value_t.gpio5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu0_pmu_intr:1", "", 1, old_value_t.cpu0_pmu_intr, new_value_t.cpu0_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cpu1_pmu_intr:1", "", 1, old_value_t.cpu1_pmu_intr, new_value_t.cpu1_pmu_intr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sbc1:1", "", 1, old_value_t.sbc1, new_value_t.sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_dma_cop:1", "", 1, old_value_t.apb_dma_cop, new_value_t.apb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_dma_cop:1", "", 1, old_value_t.ahb_dma_cop, new_value_t.ahb_dma_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dma_tx:1", "", 1, old_value_t.dma_tx, new_value_t.dma_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dma_rx:1", "", 1, old_value_t.dma_rx, new_value_t.dma_rx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COPs Interrupt Enable Priority Class (FIQ/IRQ) Register";
}

#define SEC_ICTLR_DRQ_TX_STATUS_OFFSET 0x140
#define SEC_ICTLR_DRQ_TX_STATUS_UNDEFMASK 0xFFF80000
union sec_ictlr_drq_tx_status_u {
    struct {
        unsigned int ac97_pb:1;
        unsigned int i2s1_tx_fifo2:1;
        unsigned int i2s1_tx_fifo1:1;
        unsigned int spdif_data_tx:1;
        unsigned int spdif_user_tx:1;
        unsigned int i2s2_tx_fifo2:1;
        unsigned int i2s2_tx_fifo1:1;
        unsigned int spi_tx:1;
        unsigned int uart1_output_fifo:1;
        unsigned int uart2_output_fifo:1;
        unsigned int uart3_output_fifo:1;
        unsigned int twc_tx:1;
        unsigned int i2c_tx:1;
        unsigned int i2c2_tx:1;
        unsigned int uart4_output_fifo:1;
        unsigned int uart5_output_fifo:1;
        unsigned int i2c3_tx:1;
        unsigned int vfir_tx_fifo:1;
        unsigned int ac97_mpb:1;
        unsigned int undefined_bits_19_31:13;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_drq_tx_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_drq_tx_status_u old_value_t = { .reg32 = value };
    const sec_ictlr_drq_tx_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ac97_pb:1", "", 1, old_value_t.ac97_pb, new_value_t.ac97_pb };
    m_bit_details_model.bits.append(entry);
    entry = { "01: i2s1_tx_fifo2:1", "", 1, old_value_t.i2s1_tx_fifo2, new_value_t.i2s1_tx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2s1_tx_fifo1:1", "", 1, old_value_t.i2s1_tx_fifo1, new_value_t.i2s1_tx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: spdif_data_tx:1", "", 1, old_value_t.spdif_data_tx, new_value_t.spdif_data_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "04: spdif_user_tx:1", "", 1, old_value_t.spdif_user_tx, new_value_t.spdif_user_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "05: i2s2_tx_fifo2:1", "", 1, old_value_t.i2s2_tx_fifo2, new_value_t.i2s2_tx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2s2_tx_fifo1:1", "", 1, old_value_t.i2s2_tx_fifo1, new_value_t.i2s2_tx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi_tx:1", "", 1, old_value_t.spi_tx, new_value_t.spi_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uart1_output_fifo:1", "", 1, old_value_t.uart1_output_fifo, new_value_t.uart1_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "09: uart2_output_fifo:1", "", 1, old_value_t.uart2_output_fifo, new_value_t.uart2_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "10: uart3_output_fifo:1", "", 1, old_value_t.uart3_output_fifo, new_value_t.uart3_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "11: twc_tx:1", "", 1, old_value_t.twc_tx, new_value_t.twc_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "12: i2c_tx:1", "", 1, old_value_t.i2c_tx, new_value_t.i2c_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2c2_tx:1", "", 1, old_value_t.i2c2_tx, new_value_t.i2c2_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart4_output_fifo:1", "", 1, old_value_t.uart4_output_fifo, new_value_t.uart4_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "15: uart5_output_fifo:1", "", 1, old_value_t.uart5_output_fifo, new_value_t.uart5_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "16: i2c3_tx:1", "", 1, old_value_t.i2c3_tx, new_value_t.i2c3_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vfir_tx_fifo:1", "", 1, old_value_t.vfir_tx_fifo, new_value_t.vfir_tx_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ac97_mpb:1", "", 1, old_value_t.ac97_mpb, new_value_t.ac97_mpb };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_31:13", "", 13, old_value_t.undefined_bits_19_31, new_value_t.undefined_bits_19_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Second Interrupt Controller DRQ TX Registers.\nDRQ Interrupt Source Status";
}

#define SEC_ICTLR_DRQ_TX_ENABLE_OFFSET 0x144
#define SEC_ICTLR_DRQ_TX_ENABLE_UNDEFMASK 0xFFF80000
union sec_ictlr_drq_tx_enable_u {
    struct {
        unsigned int ac97_pb:1;
        unsigned int i2s1_tx_fifo2:1;
        unsigned int i2s1_tx_fifo1:1;
        unsigned int spdif_data_tx:1;
        unsigned int spdif_user_tx:1;
        unsigned int i2s2_tx_fifo2:1;
        unsigned int i2s2_tx_fifo1:1;
        unsigned int spi_tx:1;
        unsigned int uart1_output_fifo:1;
        unsigned int uart2_output_fifo:1;
        unsigned int uart3_output_fifo:1;
        unsigned int twc_tx:1;
        unsigned int i2c_tx:1;
        unsigned int i2c2_tx:1;
        unsigned int uart4_output_fifo:1;
        unsigned int uart5_output_fifo:1;
        unsigned int i2c3_tx:1;
        unsigned int vfir_tx_fifo:1;
        unsigned int ac97_mpb:1;
        unsigned int undefined_bits_19_31:13;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_drq_tx_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_drq_tx_enable_u old_value_t = { .reg32 = value };
    const sec_ictlr_drq_tx_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ac97_pb:1", "", 1, old_value_t.ac97_pb, new_value_t.ac97_pb };
    m_bit_details_model.bits.append(entry);
    entry = { "01: i2s1_tx_fifo2:1", "", 1, old_value_t.i2s1_tx_fifo2, new_value_t.i2s1_tx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2s1_tx_fifo1:1", "", 1, old_value_t.i2s1_tx_fifo1, new_value_t.i2s1_tx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: spdif_data_tx:1", "", 1, old_value_t.spdif_data_tx, new_value_t.spdif_data_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "04: spdif_user_tx:1", "", 1, old_value_t.spdif_user_tx, new_value_t.spdif_user_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "05: i2s2_tx_fifo2:1", "", 1, old_value_t.i2s2_tx_fifo2, new_value_t.i2s2_tx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2s2_tx_fifo1:1", "", 1, old_value_t.i2s2_tx_fifo1, new_value_t.i2s2_tx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi_tx:1", "", 1, old_value_t.spi_tx, new_value_t.spi_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uart1_output_fifo:1", "", 1, old_value_t.uart1_output_fifo, new_value_t.uart1_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "09: uart2_output_fifo:1", "", 1, old_value_t.uart2_output_fifo, new_value_t.uart2_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "10: uart3_output_fifo:1", "", 1, old_value_t.uart3_output_fifo, new_value_t.uart3_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "11: twc_tx:1", "", 1, old_value_t.twc_tx, new_value_t.twc_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "12: i2c_tx:1", "", 1, old_value_t.i2c_tx, new_value_t.i2c_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2c2_tx:1", "", 1, old_value_t.i2c2_tx, new_value_t.i2c2_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart4_output_fifo:1", "", 1, old_value_t.uart4_output_fifo, new_value_t.uart4_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "15: uart5_output_fifo:1", "", 1, old_value_t.uart5_output_fifo, new_value_t.uart5_output_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "16: i2c3_tx:1", "", 1, old_value_t.i2c3_tx, new_value_t.i2c3_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vfir_tx_fifo:1", "", 1, old_value_t.vfir_tx_fifo, new_value_t.vfir_tx_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ac97_mpb:1", "", 1, old_value_t.ac97_mpb, new_value_t.ac97_mpb };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_31:13", "", 13, old_value_t.undefined_bits_19_31, new_value_t.undefined_bits_19_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DRQ Interrupt Source Enable Gates";
}

#define SEC_ICTLR_DRQ_RX_STATUS_OFFSET 0x148
#define SEC_ICTLR_DRQ_RX_STATUS_UNDEFMASK 0xFFF80000
union sec_ictlr_drq_rx_status_u {
    struct {
        unsigned int ac97_rec:1;
        unsigned int i2s1_rx_fifo1:1;
        unsigned int i2s1_rx_fifo2:1;
        unsigned int spdif_data_rx:1;
        unsigned int spdif_user_rx:1;
        unsigned int i2s2_rx_fifo1:1;
        unsigned int i2s2_rx_fifo2:1;
        unsigned int spi_rx:1;
        unsigned int uart1_input_fifo:1;
        unsigned int uart2_input_fifo:1;
        unsigned int uart3_input_fifo:1;
        unsigned int twc_rx:1;
        unsigned int i2c_rx:1;
        unsigned int i2c2_rx:1;
        unsigned int uart4_input_fifo:1;
        unsigned int uart5_input_fifo:1;
        unsigned int i2c3_rx:1;
        unsigned int vfir_rx_fifo:1;
        unsigned int ac97_mrec:1;
        unsigned int undefined_bits_19_31:13;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_drq_rx_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_drq_rx_status_u old_value_t = { .reg32 = value };
    const sec_ictlr_drq_rx_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ac97_rec:1", "", 1, old_value_t.ac97_rec, new_value_t.ac97_rec };
    m_bit_details_model.bits.append(entry);
    entry = { "01: i2s1_rx_fifo1:1", "", 1, old_value_t.i2s1_rx_fifo1, new_value_t.i2s1_rx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2s1_rx_fifo2:1", "", 1, old_value_t.i2s1_rx_fifo2, new_value_t.i2s1_rx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: spdif_data_rx:1", "", 1, old_value_t.spdif_data_rx, new_value_t.spdif_data_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "04: spdif_user_rx:1", "", 1, old_value_t.spdif_user_rx, new_value_t.spdif_user_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "05: i2s2_rx_fifo1:1", "", 1, old_value_t.i2s2_rx_fifo1, new_value_t.i2s2_rx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2s2_rx_fifo2:1", "", 1, old_value_t.i2s2_rx_fifo2, new_value_t.i2s2_rx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi_rx:1", "", 1, old_value_t.spi_rx, new_value_t.spi_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uart1_input_fifo:1", "", 1, old_value_t.uart1_input_fifo, new_value_t.uart1_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "09: uart2_input_fifo:1", "", 1, old_value_t.uart2_input_fifo, new_value_t.uart2_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "10: uart3_input_fifo:1", "", 1, old_value_t.uart3_input_fifo, new_value_t.uart3_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "11: twc_rx:1", "", 1, old_value_t.twc_rx, new_value_t.twc_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "12: i2c_rx:1", "", 1, old_value_t.i2c_rx, new_value_t.i2c_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2c2_rx:1", "", 1, old_value_t.i2c2_rx, new_value_t.i2c2_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart4_input_fifo:1", "", 1, old_value_t.uart4_input_fifo, new_value_t.uart4_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "15: uart5_input_fifo:1", "", 1, old_value_t.uart5_input_fifo, new_value_t.uart5_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "16: i2c3_rx:1", "", 1, old_value_t.i2c3_rx, new_value_t.i2c3_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vfir_rx_fifo:1", "", 1, old_value_t.vfir_rx_fifo, new_value_t.vfir_rx_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ac97_mrec:1", "", 1, old_value_t.ac97_mrec, new_value_t.ac97_mrec };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_31:13", "", 13, old_value_t.undefined_bits_19_31, new_value_t.undefined_bits_19_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Second interrupt controller DRQ RX registers.\nDRQ Interrupt Source Status por=0x00000000";
}

#define SEC_ICTLR_DRQ_RX_ENABLE_OFFSET 0x14C
#define SEC_ICTLR_DRQ_RX_ENABLE_UNDEFMASK 0xFFF80000
union sec_ictlr_drq_rx_enable_u {
    struct {
        unsigned int ac97_rec:1;
        unsigned int i2s1_rx_fifo1:1;
        unsigned int i2s1_rx_fifo2:1;
        unsigned int spdif_data_rx:1;
        unsigned int spdif_user_rx:1;
        unsigned int i2s2_rx_fifo1:1;
        unsigned int i2s2_rx_fifo2:1;
        unsigned int spi_rx:1;
        unsigned int uart1_input_fifo:1;
        unsigned int uart2_input_fifo:1;
        unsigned int uart3_input_fifo:1;
        unsigned int twc_rx:1;
        unsigned int i2c_rx:1;
        unsigned int i2c2_rx:1;
        unsigned int uart4_input_fifo:1;
        unsigned int uart5_input_fifo:1;
        unsigned int i2c3_rx:1;
        unsigned int vfir_rx_fifo:1;
        unsigned int ac97_mrec:1;
        unsigned int undefined_bits_19_31:13;
    };

    u_int32_t reg32;
};

void Ictlr_secDev::fill_sec_ictlr_drq_rx_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_ictlr_drq_rx_enable_u old_value_t = { .reg32 = value };
    const sec_ictlr_drq_rx_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ac97_rec:1", "", 1, old_value_t.ac97_rec, new_value_t.ac97_rec };
    m_bit_details_model.bits.append(entry);
    entry = { "01: i2s1_rx_fifo1:1", "", 1, old_value_t.i2s1_rx_fifo1, new_value_t.i2s1_rx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2s1_rx_fifo2:1", "", 1, old_value_t.i2s1_rx_fifo2, new_value_t.i2s1_rx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: spdif_data_rx:1", "", 1, old_value_t.spdif_data_rx, new_value_t.spdif_data_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "04: spdif_user_rx:1", "", 1, old_value_t.spdif_user_rx, new_value_t.spdif_user_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "05: i2s2_rx_fifo1:1", "", 1, old_value_t.i2s2_rx_fifo1, new_value_t.i2s2_rx_fifo1 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2s2_rx_fifo2:1", "", 1, old_value_t.i2s2_rx_fifo2, new_value_t.i2s2_rx_fifo2 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi_rx:1", "", 1, old_value_t.spi_rx, new_value_t.spi_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uart1_input_fifo:1", "", 1, old_value_t.uart1_input_fifo, new_value_t.uart1_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "09: uart2_input_fifo:1", "", 1, old_value_t.uart2_input_fifo, new_value_t.uart2_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "10: uart3_input_fifo:1", "", 1, old_value_t.uart3_input_fifo, new_value_t.uart3_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "11: twc_rx:1", "", 1, old_value_t.twc_rx, new_value_t.twc_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "12: i2c_rx:1", "", 1, old_value_t.i2c_rx, new_value_t.i2c_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "13: i2c2_rx:1", "", 1, old_value_t.i2c2_rx, new_value_t.i2c2_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "14: uart4_input_fifo:1", "", 1, old_value_t.uart4_input_fifo, new_value_t.uart4_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "15: uart5_input_fifo:1", "", 1, old_value_t.uart5_input_fifo, new_value_t.uart5_input_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "16: i2c3_rx:1", "", 1, old_value_t.i2c3_rx, new_value_t.i2c3_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vfir_rx_fifo:1", "", 1, old_value_t.vfir_rx_fifo, new_value_t.vfir_rx_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ac97_mrec:1", "", 1, old_value_t.ac97_mrec, new_value_t.ac97_mrec };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_31:13", "", 13, old_value_t.undefined_bits_19_31, new_value_t.undefined_bits_19_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DRQ Interrupt Source Enable Gates";
}



bool Ictlr_secDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case SEC_ICTLR_VIRQ_CPU_OFFSET:
    case SEC_ICTLR_VIRQ_COP_OFFSET:
    case SEC_ICTLR_VFIQ_CPU_OFFSET:
    case SEC_ICTLR_VFIQ_COP_OFFSET:
    case SEC_ICTLR_ISR_OFFSET:
    case SEC_ICTLR_FIR_OFFSET:
    case SEC_ICTLR_FIR_SET_OFFSET:
    case SEC_ICTLR_FIR_CLR_OFFSET:
    case SEC_ICTLR_CPU_IER_OFFSET:
    case SEC_ICTLR_CPU_IER_SET_OFFSET:
    case SEC_ICTLR_CPU_IER_CLR_OFFSET:
    case SEC_ICTLR_CPU_IEP_CLASS_OFFSET:
    case SEC_ICTLR_COP_IER_OFFSET:
    case SEC_ICTLR_COP_IER_SET_OFFSET:
    case SEC_ICTLR_COP_IER_CLR_OFFSET:
    case SEC_ICTLR_COP_IEP_CLASS_OFFSET:
    case SEC_ICTLR_DRQ_TX_STATUS_OFFSET:
    case SEC_ICTLR_DRQ_TX_ENABLE_OFFSET:
    case SEC_ICTLR_DRQ_RX_STATUS_OFFSET:
    case SEC_ICTLR_DRQ_RX_ENABLE_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Ictlr_secDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case SEC_ICTLR_VIRQ_CPU_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_VIRQ_CPU_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_VIRQ_COP_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_VIRQ_COP_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_VFIQ_CPU_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_VFIQ_CPU_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_VFIQ_COP_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_VFIQ_COP_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_ISR_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_ISR_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_FIR_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_FIR_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_FIR_SET_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_FIR_SET_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_FIR_CLR_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_FIR_CLR_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_CPU_IER_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_CPU_IER_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_CPU_IER_SET_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_CPU_IER_SET_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_CPU_IER_CLR_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_CPU_IER_CLR_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_CPU_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_CPU_IEP_CLASS_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_COP_IER_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_COP_IER_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_COP_IER_SET_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_COP_IER_SET_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_COP_IER_CLR_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_COP_IER_CLR_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_COP_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_COP_IEP_CLASS_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_DRQ_TX_STATUS_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_DRQ_TX_STATUS_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_DRQ_TX_ENABLE_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_DRQ_TX_ENABLE_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_DRQ_RX_STATUS_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_DRQ_RX_STATUS_UNDEFMASK)
            return true;
        break;
    case SEC_ICTLR_DRQ_RX_ENABLE_OFFSET:
        if ((value ^ new_value) & SEC_ICTLR_DRQ_RX_ENABLE_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Ictlr_secDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case SEC_ICTLR_VIRQ_CPU_OFFSET:
        return QString("SEC_ICTLR_VIRQ_CPU");
    case SEC_ICTLR_VIRQ_COP_OFFSET:
        return QString("SEC_ICTLR_VIRQ_COP");
    case SEC_ICTLR_VFIQ_CPU_OFFSET:
        return QString("SEC_ICTLR_VFIQ_CPU");
    case SEC_ICTLR_VFIQ_COP_OFFSET:
        return QString("SEC_ICTLR_VFIQ_COP");
    case SEC_ICTLR_ISR_OFFSET:
        return QString("SEC_ICTLR_ISR");
    case SEC_ICTLR_FIR_OFFSET:
        return QString("SEC_ICTLR_FIR");
    case SEC_ICTLR_FIR_SET_OFFSET:
        return QString("SEC_ICTLR_FIR_SET");
    case SEC_ICTLR_FIR_CLR_OFFSET:
        return QString("SEC_ICTLR_FIR_CLR");
    case SEC_ICTLR_CPU_IER_OFFSET:
        return QString("SEC_ICTLR_CPU_IER");
    case SEC_ICTLR_CPU_IER_SET_OFFSET:
        return QString("SEC_ICTLR_CPU_IER_SET");
    case SEC_ICTLR_CPU_IER_CLR_OFFSET:
        return QString("SEC_ICTLR_CPU_IER_CLR");
    case SEC_ICTLR_CPU_IEP_CLASS_OFFSET:
        return QString("SEC_ICTLR_CPU_IEP_CLASS");
    case SEC_ICTLR_COP_IER_OFFSET:
        return QString("SEC_ICTLR_COP_IER");
    case SEC_ICTLR_COP_IER_SET_OFFSET:
        return QString("SEC_ICTLR_COP_IER_SET");
    case SEC_ICTLR_COP_IER_CLR_OFFSET:
        return QString("SEC_ICTLR_COP_IER_CLR");
    case SEC_ICTLR_COP_IEP_CLASS_OFFSET:
        return QString("SEC_ICTLR_COP_IEP_CLASS");
    case SEC_ICTLR_DRQ_TX_STATUS_OFFSET:
        return QString("SEC_ICTLR_DRQ_TX_STATUS");
    case SEC_ICTLR_DRQ_TX_ENABLE_OFFSET:
        return QString("SEC_ICTLR_DRQ_TX_ENABLE");
    case SEC_ICTLR_DRQ_RX_STATUS_OFFSET:
        return QString("SEC_ICTLR_DRQ_RX_STATUS");
    case SEC_ICTLR_DRQ_RX_ENABLE_OFFSET:
        return QString("SEC_ICTLR_DRQ_RX_ENABLE");

    default:
        break;
    }

    qDebug() << QString().sprintf("ICTLR_SEC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Ictlr_secDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case SEC_ICTLR_VIRQ_CPU_OFFSET:
        fill_sec_ictlr_virq_cpu_details(value, new_value);
        break;
    case SEC_ICTLR_VIRQ_COP_OFFSET:
        fill_sec_ictlr_virq_cop_details(value, new_value);
        break;
    case SEC_ICTLR_VFIQ_CPU_OFFSET:
        fill_sec_ictlr_vfiq_cpu_details(value, new_value);
        break;
    case SEC_ICTLR_VFIQ_COP_OFFSET:
        fill_sec_ictlr_vfiq_cop_details(value, new_value);
        break;
    case SEC_ICTLR_ISR_OFFSET:
        fill_sec_ictlr_isr_details(value, new_value);
        break;
    case SEC_ICTLR_FIR_OFFSET:
        fill_sec_ictlr_fir_details(value, new_value);
        break;
    case SEC_ICTLR_FIR_SET_OFFSET:
        fill_sec_ictlr_fir_set_details(value, new_value);
        break;
    case SEC_ICTLR_FIR_CLR_OFFSET:
        fill_sec_ictlr_fir_clr_details(value, new_value);
        break;
    case SEC_ICTLR_CPU_IER_OFFSET:
        fill_sec_ictlr_cpu_ier_details(value, new_value);
        break;
    case SEC_ICTLR_CPU_IER_SET_OFFSET:
        fill_sec_ictlr_cpu_ier_set_details(value, new_value);
        break;
    case SEC_ICTLR_CPU_IER_CLR_OFFSET:
        fill_sec_ictlr_cpu_ier_clr_details(value, new_value);
        break;
    case SEC_ICTLR_CPU_IEP_CLASS_OFFSET:
        fill_sec_ictlr_cpu_iep_class_details(value, new_value);
        break;
    case SEC_ICTLR_COP_IER_OFFSET:
        fill_sec_ictlr_cop_ier_details(value, new_value);
        break;
    case SEC_ICTLR_COP_IER_SET_OFFSET:
        fill_sec_ictlr_cop_ier_set_details(value, new_value);
        break;
    case SEC_ICTLR_COP_IER_CLR_OFFSET:
        fill_sec_ictlr_cop_ier_clr_details(value, new_value);
        break;
    case SEC_ICTLR_COP_IEP_CLASS_OFFSET:
        fill_sec_ictlr_cop_iep_class_details(value, new_value);
        break;
    case SEC_ICTLR_DRQ_TX_STATUS_OFFSET:
        fill_sec_ictlr_drq_tx_status_details(value, new_value);
        break;
    case SEC_ICTLR_DRQ_TX_ENABLE_OFFSET:
        fill_sec_ictlr_drq_tx_enable_details(value, new_value);
        break;
    case SEC_ICTLR_DRQ_RX_STATUS_OFFSET:
        fill_sec_ictlr_drq_rx_status_details(value, new_value);
        break;
    case SEC_ICTLR_DRQ_RX_ENABLE_OFFSET:
        fill_sec_ictlr_drq_rx_enable_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
