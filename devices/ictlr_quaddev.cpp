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

#include "ictlr_quaddev.h"

#include <QDebug>

Ictlr_quadDev::Ictlr_quadDev(QObject *parent) :
    Device(parent)
{
}

#define QUAD_ICTLR_VIRQ_CPU_OFFSET 0x300
#define QUAD_ICTLR_VIRQ_CPU_UNDEFMASK 0xFF0000E0
union quad_ictlr_virq_cpu_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_virq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_virq_cpu_u old_value_t = { .reg32 = value };
    const quad_ictlr_virq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Fourth interrupt controller base registers\nValid Interrupt Request Status for CPU Register";
}

#define QUAD_ICTLR_VIRQ_COP_OFFSET 0x304
#define QUAD_ICTLR_VIRQ_COP_UNDEFMASK 0xFF0000E0
union quad_ictlr_virq_cop_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_virq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_virq_cop_u old_value_t = { .reg32 = value };
    const quad_ictlr_virq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Valid Interrupt Status for COP Register";
}

#define QUAD_ICTLR_VFIQ_CPU_OFFSET 0x308
#define QUAD_ICTLR_VFIQ_CPU_UNDEFMASK 0xFF0000E0
union quad_ictlr_vfiq_cpu_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_vfiq_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_vfiq_cpu_u old_value_t = { .reg32 = value };
    const quad_ictlr_vfiq_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for CPU Register";
}

#define QUAD_ICTLR_VFIQ_COP_OFFSET 0x30C
#define QUAD_ICTLR_VFIQ_COP_UNDEFMASK 0xFF0000E0
union quad_ictlr_vfiq_cop_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_vfiq_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_vfiq_cop_u old_value_t = { .reg32 = value };
    const quad_ictlr_vfiq_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FIQ Valid Interrupt Status for COP Register";
}

#define QUAD_ICTLR_ISR_OFFSET 0x310
#define QUAD_ICTLR_ISR_UNDEFMASK 0xFF0000E0
union quad_ictlr_isr_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_isr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_isr_u old_value_t = { .reg32 = value };
    const quad_ictlr_isr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Latched Interrupt Status Register (HW)";
}

#define QUAD_ICTLR_FIR_OFFSET 0x314
#define QUAD_ICTLR_FIR_UNDEFMASK 0xFF0000E0
union quad_ictlr_fir_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_fir_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_fir_u old_value_t = { .reg32 = value };
    const quad_ictlr_fir_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Forced Interrupt Status Register (SW)";
}

#define QUAD_ICTLR_FIR_SET_OFFSET 0x318
#define QUAD_ICTLR_FIR_SET_UNDEFMASK 0xFF0000E0
union quad_ictlr_fir_set_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_fir_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_fir_set_u old_value_t = { .reg32 = value };
    const quad_ictlr_fir_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Set";
}

#define QUAD_ICTLR_FIR_CLR_OFFSET 0x31C
#define QUAD_ICTLR_FIR_CLR_UNDEFMASK 0xFF0000E0
union quad_ictlr_fir_clr_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_fir_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_fir_clr_u old_value_t = { .reg32 = value };
    const quad_ictlr_fir_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Force Interrupt Register Clear Register";
}

#define QUAD_ICTLR_CPU_IER_OFFSET 0x320
#define QUAD_ICTLR_CPU_IER_UNDEFMASK 0xFF0000E0
union quad_ictlr_cpu_ier_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cpu_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cpu_ier_u old_value_t = { .reg32 = value };
    const quad_ictlr_cpu_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for CPU Register";
}

#define QUAD_ICTLR_CPU_IER_SET_OFFSET 0x324
#define QUAD_ICTLR_CPU_IER_SET_UNDEFMASK 0xFF0000E0
union quad_ictlr_cpu_ier_set_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cpu_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cpu_ier_set_u old_value_t = { .reg32 = value };
    const quad_ictlr_cpu_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Enable for CPU Register";
}

#define QUAD_ICTLR_CPU_IER_CLR_OFFSET 0x328
#define QUAD_ICTLR_CPU_IER_CLR_UNDEFMASK 0xFF0000E0
union quad_ictlr_cpu_ier_clr_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cpu_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cpu_ier_clr_u old_value_t = { .reg32 = value };
    const quad_ictlr_cpu_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPUs Clear Interrupt Enable for CPU";
}

#define QUAD_ICTLR_CPU_IEP_CLASS_OFFSET 0x32C
#define QUAD_ICTLR_CPU_IEP_CLASS_UNDEFMASK 0xFF0000E0
union quad_ictlr_cpu_iep_class_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cpu_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cpu_iep_class_u old_value_t = { .reg32 = value };
    const quad_ictlr_cpu_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPUs Interrupt Enable Priority Class (FIQ/IRQ)";
}

#define QUAD_ICTLR_COP_IER_OFFSET 0x330
#define QUAD_ICTLR_COP_IER_UNDEFMASK 0xFF0000E0
union quad_ictlr_cop_ier_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cop_ier_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cop_ier_u old_value_t = { .reg32 = value };
    const quad_ictlr_cop_ier_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enabled Interrupt Source for COP Register";
}

#define QUAD_ICTLR_COP_IER_SET_OFFSET 0x334
#define QUAD_ICTLR_COP_IER_SET_UNDEFMASK 0xFF0000E0
union quad_ictlr_cop_ier_set_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cop_ier_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cop_ier_set_u old_value_t = { .reg32 = value };
    const quad_ictlr_cop_ier_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set Interrupt Source for COP Register";
}

#define QUAD_ICTLR_COP_IER_CLR_OFFSET 0x338
#define QUAD_ICTLR_COP_IER_CLR_UNDEFMASK 0xFF0000E0
union quad_ictlr_cop_ier_clr_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cop_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cop_ier_clr_u old_value_t = { .reg32 = value };
    const quad_ictlr_cop_ier_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clear Interrupt Source for COP Register";
}

#define QUAD_ICTLR_COP_IEP_CLASS_OFFSET 0x33C
#define QUAD_ICTLR_COP_IEP_CLASS_UNDEFMASK 0xFF0000E0
union quad_ictlr_cop_iep_class_u {
    struct {
        unsigned int snor:1;
        unsigned int usb3:1;
        unsigned int pcie_int:1;
        unsigned int pcie_msi:1;
        unsigned int pcie_wake:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int apb_dma_ch0:1;
        unsigned int apb_dma_ch1:1;
        unsigned int apb_dma_ch2:1;
        unsigned int apb_dma_ch3:1;
        unsigned int apb_dma_ch4:1;
        unsigned int apb_dma_ch5:1;
        unsigned int apb_dma_ch6:1;
        unsigned int apb_dma_ch7:1;
        unsigned int apb_dma_ch8:1;
        unsigned int apb_dma_ch9:1;
        unsigned int apb_dma_ch10:1;
        unsigned int apb_dma_ch11:1;
        unsigned int apb_dma_ch12:1;
        unsigned int apb_dma_ch13:1;
        unsigned int apb_dma_ch14:1;
        unsigned int apb_dma_ch15:1;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void Ictlr_quadDev::fill_quad_ictlr_cop_iep_class_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quad_ictlr_cop_iep_class_u old_value_t = { .reg32 = value };
    const quad_ictlr_cop_iep_class_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor:1", "", 1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "01: usb3:1", "", 1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pcie_int:1", "", 1, old_value_t.pcie_int, new_value_t.pcie_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcie_msi:1", "", 1, old_value_t.pcie_msi, new_value_t.pcie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcie_wake:1", "", 1, old_value_t.pcie_wake, new_value_t.pcie_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: apb_dma_ch0:1", "", 1, old_value_t.apb_dma_ch0, new_value_t.apb_dma_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_dma_ch1:1", "", 1, old_value_t.apb_dma_ch1, new_value_t.apb_dma_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_dma_ch2:1", "", 1, old_value_t.apb_dma_ch2, new_value_t.apb_dma_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_dma_ch3:1", "", 1, old_value_t.apb_dma_ch3, new_value_t.apb_dma_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_dma_ch4:1", "", 1, old_value_t.apb_dma_ch4, new_value_t.apb_dma_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_dma_ch5:1", "", 1, old_value_t.apb_dma_ch5, new_value_t.apb_dma_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_dma_ch6:1", "", 1, old_value_t.apb_dma_ch6, new_value_t.apb_dma_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_dma_ch7:1", "", 1, old_value_t.apb_dma_ch7, new_value_t.apb_dma_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_dma_ch8:1", "", 1, old_value_t.apb_dma_ch8, new_value_t.apb_dma_ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_dma_ch9:1", "", 1, old_value_t.apb_dma_ch9, new_value_t.apb_dma_ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_dma_ch10:1", "", 1, old_value_t.apb_dma_ch10, new_value_t.apb_dma_ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_dma_ch11:1", "", 1, old_value_t.apb_dma_ch11, new_value_t.apb_dma_ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_dma_ch12:1", "", 1, old_value_t.apb_dma_ch12, new_value_t.apb_dma_ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_dma_ch13:1", "", 1, old_value_t.apb_dma_ch13, new_value_t.apb_dma_ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_dma_ch14:1", "", 1, old_value_t.apb_dma_ch14, new_value_t.apb_dma_ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_dma_ch15:1", "", 1, old_value_t.apb_dma_ch15, new_value_t.apb_dma_ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COPs Interrupt Enable Priority Class (FIQ/IRQ) Register";
}



bool Ictlr_quadDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case QUAD_ICTLR_VIRQ_CPU_OFFSET:
    case QUAD_ICTLR_VIRQ_COP_OFFSET:
    case QUAD_ICTLR_VFIQ_CPU_OFFSET:
    case QUAD_ICTLR_VFIQ_COP_OFFSET:
    case QUAD_ICTLR_ISR_OFFSET:
    case QUAD_ICTLR_FIR_OFFSET:
    case QUAD_ICTLR_FIR_SET_OFFSET:
    case QUAD_ICTLR_FIR_CLR_OFFSET:
    case QUAD_ICTLR_CPU_IER_OFFSET:
    case QUAD_ICTLR_CPU_IER_SET_OFFSET:
    case QUAD_ICTLR_CPU_IER_CLR_OFFSET:
    case QUAD_ICTLR_CPU_IEP_CLASS_OFFSET:
    case QUAD_ICTLR_COP_IER_OFFSET:
    case QUAD_ICTLR_COP_IER_SET_OFFSET:
    case QUAD_ICTLR_COP_IER_CLR_OFFSET:
    case QUAD_ICTLR_COP_IEP_CLASS_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Ictlr_quadDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case QUAD_ICTLR_VIRQ_CPU_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_VIRQ_CPU_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_VIRQ_COP_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_VIRQ_COP_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_VFIQ_CPU_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_VFIQ_CPU_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_VFIQ_COP_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_VFIQ_COP_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_ISR_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_ISR_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_FIR_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_FIR_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_FIR_SET_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_FIR_SET_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_FIR_CLR_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_FIR_CLR_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_CPU_IER_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_CPU_IER_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_CPU_IER_SET_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_CPU_IER_SET_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_CPU_IER_CLR_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_CPU_IER_CLR_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_CPU_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_CPU_IEP_CLASS_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_COP_IER_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_COP_IER_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_COP_IER_SET_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_COP_IER_SET_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_COP_IER_CLR_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_COP_IER_CLR_UNDEFMASK)
            return true;
        break;
    case QUAD_ICTLR_COP_IEP_CLASS_OFFSET:
        if ((value ^ new_value) & QUAD_ICTLR_COP_IEP_CLASS_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Ictlr_quadDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case QUAD_ICTLR_VIRQ_CPU_OFFSET:
        return QString("QUAD_ICTLR_VIRQ_CPU");
    case QUAD_ICTLR_VIRQ_COP_OFFSET:
        return QString("QUAD_ICTLR_VIRQ_COP");
    case QUAD_ICTLR_VFIQ_CPU_OFFSET:
        return QString("QUAD_ICTLR_VFIQ_CPU");
    case QUAD_ICTLR_VFIQ_COP_OFFSET:
        return QString("QUAD_ICTLR_VFIQ_COP");
    case QUAD_ICTLR_ISR_OFFSET:
        return QString("QUAD_ICTLR_ISR");
    case QUAD_ICTLR_FIR_OFFSET:
        return QString("QUAD_ICTLR_FIR");
    case QUAD_ICTLR_FIR_SET_OFFSET:
        return QString("QUAD_ICTLR_FIR_SET");
    case QUAD_ICTLR_FIR_CLR_OFFSET:
        return QString("QUAD_ICTLR_FIR_CLR");
    case QUAD_ICTLR_CPU_IER_OFFSET:
        return QString("QUAD_ICTLR_CPU_IER");
    case QUAD_ICTLR_CPU_IER_SET_OFFSET:
        return QString("QUAD_ICTLR_CPU_IER_SET");
    case QUAD_ICTLR_CPU_IER_CLR_OFFSET:
        return QString("QUAD_ICTLR_CPU_IER_CLR");
    case QUAD_ICTLR_CPU_IEP_CLASS_OFFSET:
        return QString("QUAD_ICTLR_CPU_IEP_CLASS");
    case QUAD_ICTLR_COP_IER_OFFSET:
        return QString("QUAD_ICTLR_COP_IER");
    case QUAD_ICTLR_COP_IER_SET_OFFSET:
        return QString("QUAD_ICTLR_COP_IER_SET");
    case QUAD_ICTLR_COP_IER_CLR_OFFSET:
        return QString("QUAD_ICTLR_COP_IER_CLR");
    case QUAD_ICTLR_COP_IEP_CLASS_OFFSET:
        return QString("QUAD_ICTLR_COP_IEP_CLASS");

    default:
        break;
    }

    qDebug() << QString().sprintf("ICTLR_QUAD: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Ictlr_quadDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case QUAD_ICTLR_VIRQ_CPU_OFFSET:
        fill_quad_ictlr_virq_cpu_details(value, new_value);
        break;
    case QUAD_ICTLR_VIRQ_COP_OFFSET:
        fill_quad_ictlr_virq_cop_details(value, new_value);
        break;
    case QUAD_ICTLR_VFIQ_CPU_OFFSET:
        fill_quad_ictlr_vfiq_cpu_details(value, new_value);
        break;
    case QUAD_ICTLR_VFIQ_COP_OFFSET:
        fill_quad_ictlr_vfiq_cop_details(value, new_value);
        break;
    case QUAD_ICTLR_ISR_OFFSET:
        fill_quad_ictlr_isr_details(value, new_value);
        break;
    case QUAD_ICTLR_FIR_OFFSET:
        fill_quad_ictlr_fir_details(value, new_value);
        break;
    case QUAD_ICTLR_FIR_SET_OFFSET:
        fill_quad_ictlr_fir_set_details(value, new_value);
        break;
    case QUAD_ICTLR_FIR_CLR_OFFSET:
        fill_quad_ictlr_fir_clr_details(value, new_value);
        break;
    case QUAD_ICTLR_CPU_IER_OFFSET:
        fill_quad_ictlr_cpu_ier_details(value, new_value);
        break;
    case QUAD_ICTLR_CPU_IER_SET_OFFSET:
        fill_quad_ictlr_cpu_ier_set_details(value, new_value);
        break;
    case QUAD_ICTLR_CPU_IER_CLR_OFFSET:
        fill_quad_ictlr_cpu_ier_clr_details(value, new_value);
        break;
    case QUAD_ICTLR_CPU_IEP_CLASS_OFFSET:
        fill_quad_ictlr_cpu_iep_class_details(value, new_value);
        break;
    case QUAD_ICTLR_COP_IER_OFFSET:
        fill_quad_ictlr_cop_ier_details(value, new_value);
        break;
    case QUAD_ICTLR_COP_IER_SET_OFFSET:
        fill_quad_ictlr_cop_ier_set_details(value, new_value);
        break;
    case QUAD_ICTLR_COP_IER_CLR_OFFSET:
        fill_quad_ictlr_cop_ier_clr_details(value, new_value);
        break;
    case QUAD_ICTLR_COP_IEP_CLASS_OFFSET:
        fill_quad_ictlr_cop_iep_class_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
