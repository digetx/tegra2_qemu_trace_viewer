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

#include "arb_gnt_ictlrdev.h"

#include <QDebug>

Arb_gnt_ictlrDev::Arb_gnt_ictlrDev(QObject *parent) :
    Device(parent)
{
}

#define PRI_ICTLR_ARBGNT_CPU_STATUS_OFFSET 0x0
#define PRI_ICTLR_ARBGNT_CPU_STATUS_UNDEFMASK 0x00000000
union pri_ictlr_arbgnt_cpu_status_u {
    struct {
        unsigned int gnt31_gng0:32;         /* Each bit is set by hardware when the corresponding arbitration semaphore ownership is granted to CPU. Interrupt is cleared when the CPU writes the ARB_SMP.PUT register with the corresponding bit set */
    };

    u_int32_t reg32;
};

void Arb_gnt_ictlrDev::fill_pri_ictlr_arbgnt_cpu_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_arbgnt_cpu_status_u old_value_t = { .reg32 = value };
    const pri_ictlr_arbgnt_cpu_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gnt31_gng0:32",
              "Each bit is set by hardware when the corresponding arbitration semaphore ownership is granted to CPU. Interrupt is cleared when the CPU writes the ARB_SMP.PUT register with the corresponding bit set",
              32, old_value_t.gnt31_gng0, new_value_t.gnt31_gng0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Arbitration semaphores provide a mechanism by which the two processors can arbitrate for the use of various resources. These semaphores provide a hardware locking mechanism, so that when a processor is already using a resource, the second processor is not granted that resource. There are 32 bits of Arbitration semaphores provided in the system. The hardware does not enforce any resource association to these bits. It is left to the firmware to assign and use these bits.\nThe Arbitration Semaphores can also generate an interrupt when a hardware resource becomes available. The registers in this module configure these interrupts.\nWhen a 1 is set in the corresponding bit position of the Arbitration Semaphore Interrupt Source Register (CPU_enable or COP_enable), an interrupt will be generated when the processor achieves Grant Status for that resource.\nThe current Grant status can be viewed in the CPU_STATUS or COP_STATUS registers.\nCPU Arbitration Semaphore Interrupt Status Register";
}

#define PRI_ICTLR_ARBGNT_CPU_ENABLE_OFFSET 0x4
#define PRI_ICTLR_ARBGNT_CPU_ENABLE_UNDEFMASK 0x00000000
union pri_ictlr_arbgnt_cpu_enable_u {
    struct {
        unsigned int ger31_ger0:32;         /* Writing a 1 in any bit position will enable the corresponding arbitration semaphore interrupt */
    };

    u_int32_t reg32;
};

void Arb_gnt_ictlrDev::fill_pri_ictlr_arbgnt_cpu_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_arbgnt_cpu_enable_u old_value_t = { .reg32 = value };
    const pri_ictlr_arbgnt_cpu_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ger31_ger0:32",
              "Writing a 1 in any bit position will enable the corresponding arbitration semaphore interrupt",
              32, old_value_t.ger31_ger0, new_value_t.ger31_ger0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Arbitration Semaphore Interrupt Enable Register";
}

#define PRI_ICTLR_ARBGNT_COP_STATUS_OFFSET 0x8
#define PRI_ICTLR_ARBGNT_COP_STATUS_UNDEFMASK 0x00000000
union pri_ictlr_arbgnt_cop_status_u {
    struct {
        unsigned int gnt31_gng0:32;         /* Each bit is set by hardware when the corresponding arbitration semaphore ownership is granted to AVP (COP). Interrupt is cleared when the AVP (COP) writes the ARB_SMP.PUT register with the corresponding bit set */
    };

    u_int32_t reg32;
};

void Arb_gnt_ictlrDev::fill_pri_ictlr_arbgnt_cop_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_arbgnt_cop_status_u old_value_t = { .reg32 = value };
    const pri_ictlr_arbgnt_cop_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gnt31_gng0:32",
              "Each bit is set by hardware when the corresponding arbitration semaphore ownership is granted to AVP (COP). Interrupt is cleared when the AVP (COP) writes the ARB_SMP.PUT register with the corresponding bit set",
              32, old_value_t.gnt31_gng0, new_value_t.gnt31_gng0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Arbitration Semaphore Interrupt Status Register";
}

#define PRI_ICTLR_ARBGNT_COP_ENABLE_OFFSET 0xC
#define PRI_ICTLR_ARBGNT_COP_ENABLE_UNDEFMASK 0x00000000
union pri_ictlr_arbgnt_cop_enable_u {
    struct {
        unsigned int ger31_ger0:32;         /* Writing a 1 in any bit position will enable the corresponding arbitration semaphore interrupt */
    };

    u_int32_t reg32;
};

void Arb_gnt_ictlrDev::fill_pri_ictlr_arbgnt_cop_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pri_ictlr_arbgnt_cop_enable_u old_value_t = { .reg32 = value };
    const pri_ictlr_arbgnt_cop_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ger31_ger0:32",
              "Writing a 1 in any bit position will enable the corresponding arbitration semaphore interrupt",
              32, old_value_t.ger31_ger0, new_value_t.ger31_ger0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Arbitration Semaphore Interrupt Enable Register";
}

bool Arb_gnt_ictlrDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case PRI_ICTLR_ARBGNT_CPU_STATUS_OFFSET:
    case PRI_ICTLR_ARBGNT_CPU_ENABLE_OFFSET:
    case PRI_ICTLR_ARBGNT_COP_STATUS_OFFSET:
    case PRI_ICTLR_ARBGNT_COP_ENABLE_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Arb_gnt_ictlrDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case PRI_ICTLR_ARBGNT_CPU_STATUS_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_ARBGNT_CPU_STATUS_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_ARBGNT_CPU_ENABLE_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_ARBGNT_CPU_ENABLE_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_ARBGNT_COP_STATUS_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_ARBGNT_COP_STATUS_UNDEFMASK)
            return true;
        break;
    case PRI_ICTLR_ARBGNT_COP_ENABLE_OFFSET:
        if ((value ^ new_value) & PRI_ICTLR_ARBGNT_COP_ENABLE_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Arb_gnt_ictlrDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case PRI_ICTLR_ARBGNT_CPU_STATUS_OFFSET:
        return QString("PRI_ICTLR_ARBGNT_CPU_STATUS");
    case PRI_ICTLR_ARBGNT_CPU_ENABLE_OFFSET:
        return QString("PRI_ICTLR_ARBGNT_CPU_ENABLE");
    case PRI_ICTLR_ARBGNT_COP_STATUS_OFFSET:
        return QString("PRI_ICTLR_ARBGNT_COP_STATUS");
    case PRI_ICTLR_ARBGNT_COP_ENABLE_OFFSET:
        return QString("PRI_ICTLR_ARBGNT_COP_ENABLE");

    default:
        break;
    }

    qDebug() << QString().sprintf("ARB_GNT_ICTLR: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Arb_gnt_ictlrDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case PRI_ICTLR_ARBGNT_CPU_STATUS_OFFSET:
        fill_pri_ictlr_arbgnt_cpu_status_details(value, new_value);
        break;
    case PRI_ICTLR_ARBGNT_CPU_ENABLE_OFFSET:
        fill_pri_ictlr_arbgnt_cpu_enable_details(value, new_value);
        break;
    case PRI_ICTLR_ARBGNT_COP_STATUS_OFFSET:
        fill_pri_ictlr_arbgnt_cop_status_details(value, new_value);
        break;
    case PRI_ICTLR_ARBGNT_COP_ENABLE_OFFSET:
        fill_pri_ictlr_arbgnt_cop_enable_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
