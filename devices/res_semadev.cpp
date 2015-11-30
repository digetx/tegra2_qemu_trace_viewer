/*
 * Copyright (c) 2015 Dmitry Osipenko <digetx@gmail.com>
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

#include "res_semadev.h"

#include <QDebug>

#define RES_SEMA_SHRD_SMP_STA_OFFSET 0x0
#define RES_SEMA_SHRD_SMP_STA_UNDEFMASK 0x00000000
union res_sema_shrd_smp_sta_u {
    struct {
        unsigned int smp_31_smp_0:32;       /* SMP.27:SMP.24: Available in APB_DMA.REQUESTORS  register */
    };

    u_int32_t reg32;
};

void Res_semaDev::fill_res_sema_shrd_smp_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const res_sema_shrd_smp_sta_u old_value_t = { .reg32 = value };
    const res_sema_shrd_smp_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: smp_31_smp_0:32",
              "SMP.27:SMP.24: Available in APB_DMA.REQUESTORS  register",
              32, old_value_t.smp_31_smp_0, new_value_t.smp_31_smp_0 };
    m_bit_details_model.bits.append(entry);
}

#define RES_SEMA_SHRD_SMP_SET_OFFSET 0x4
#define RES_SEMA_SHRD_SMP_SET_UNDEFMASK 0x00000000
union res_sema_shrd_smp_set_u {
    struct {
        unsigned int set_31_set_0:32;       /* Semaphore set register. Writing a one to any bit  will set the corresponding semaphore bit. Shared resource set-bit requests */
    };

    u_int32_t reg32;
};

void Res_semaDev::fill_res_sema_shrd_smp_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const res_sema_shrd_smp_set_u old_value_t = { .reg32 = value };
    const res_sema_shrd_smp_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_31_set_0:32",
              "Semaphore set register. Writing a one to any bit  will set the corresponding semaphore bit. Shared resource set-bit requests",
              32, old_value_t.set_31_set_0, new_value_t.set_31_set_0 };
    m_bit_details_model.bits.append(entry);
}

#define RES_SEMA_SHRD_SMP_CLR_OFFSET 0x8
#define RES_SEMA_SHRD_SMP_CLR_UNDEFMASK 0x00000000
union res_sema_shrd_smp_clr_u {
    struct {
        unsigned int clr_31_clr_0:32;       /* corresponding semaphore bit */
    };

    u_int32_t reg32;
};

void Res_semaDev::fill_res_sema_shrd_smp_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const res_sema_shrd_smp_clr_u old_value_t = { .reg32 = value };
    const res_sema_shrd_smp_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_31_clr_0:32",
              "corresponding semaphore bit",
              32, old_value_t.clr_31_clr_0, new_value_t.clr_31_clr_0 };
    m_bit_details_model.bits.append(entry);
}

#define RES_SEMA_SHRD_INBOX_OFFSET 0x10
#define RES_SEMA_SHRD_INBOX_UNDEFMASK 0x00000000
union res_sema_shrd_inbox_u {
    struct {
        unsigned int in_box_data:17;        /* definition) */
        unsigned int in_box_cmd:7;          /* General purpose data bits, suggested usage is for  INBOX command (SW can change definition) */
        unsigned int in_box_stat:4;         /* definition) */
        unsigned int n_a1:1;                /* Reserved = 0 */
        unsigned int tag:1;                 /* Set when the COP writes this register and cleared when CPU writes this register with this bit set to 1 (write one clear). 0 = INVALID 1 = VALID */
        unsigned int ie_ibe:1;              /* Interrupt COP on INBOX Empty (TAG=0) */
        unsigned int ie_ibf:1;              /* Interrupt CPU on INBOX Full (TAG=1) */
    };

    u_int32_t reg32;
};

void Res_semaDev::fill_res_sema_shrd_inbox_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const res_sema_shrd_inbox_u old_value_t = { .reg32 = value };
    const res_sema_shrd_inbox_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: in_box_data:17",
              "definition)",
              17, old_value_t.in_box_data, new_value_t.in_box_data };
    m_bit_details_model.bits.append(entry);
    entry = { "17: in_box_cmd:7",
              "General purpose data bits, suggested usage is for  INBOX command (SW can change definition)",
              7, old_value_t.in_box_cmd, new_value_t.in_box_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: in_box_stat:4",
              "definition)",
              4, old_value_t.in_box_stat, new_value_t.in_box_stat };
    m_bit_details_model.bits.append(entry);
    entry = { "28: n_a1:1",
              "Reserved = 0",
              1, old_value_t.n_a1, new_value_t.n_a1 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: tag:1",
              "Set when the COP writes this register and cleared when CPU writes this register with this bit set to 1 (write one clear).\n0 = INVALID\n1 = VALID",
              1, old_value_t.tag, new_value_t.tag };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_ibe:1",
              "Interrupt COP on INBOX Empty (TAG=0)",
              1, old_value_t.ie_ibe, new_value_t.ie_ibe };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ie_ibf:1",
              "Interrupt CPU on INBOX Full (TAG=1)",
              1, old_value_t.ie_ibf, new_value_t.ie_ibf };
    m_bit_details_model.bits.append(entry);
}

#define RES_SEMA_SHRD_OUTBOX_OFFSET 0x20
#define RES_SEMA_SHRD_OUTBOX_UNDEFMASK 0x00000000
union res_sema_shrd_outbox_u {
    struct {
        unsigned int out_box_data:17;       /* General purpose Out Box data bits, suggested usage  is for OUTBOX data (SW can change definition) */
        unsigned int out_box_cmd:7;         /* General purpose data bits, suggested usage is for  Out Box OUTBOX command (SW can change definition) */
        unsigned int out_box_stat:4;        /* General purpose data bits, suggested usage is for  Out Box OUTBOX status (SW can change definition) */
        unsigned int n_a1:1;                /* Reserved = 0 */
        unsigned int tag:1;                 /* Set when the CPU writes this register and cleared when the COP writes this register with this bit set to 1 (write one clear). 0 = INVALID 1 = VALID */
        unsigned int ie_obe:1;              /* Interrupt CPU on OUTBOX Empty (TAG=0) */
        unsigned int ie_obf:1;              /* Interrupt COP on OUTBOX Full (TAG=1) */
    };

    u_int32_t reg32;
};

void Res_semaDev::fill_res_sema_shrd_outbox_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const res_sema_shrd_outbox_u old_value_t = { .reg32 = value };
    const res_sema_shrd_outbox_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: out_box_data:17",
              "General purpose Out Box data bits, suggested usage  is for OUTBOX data (SW can change definition)",
              17, old_value_t.out_box_data, new_value_t.out_box_data };
    m_bit_details_model.bits.append(entry);
    entry = { "17: out_box_cmd:7",
              "General purpose data bits, suggested usage is for  Out Box OUTBOX command (SW can change definition)",
              7, old_value_t.out_box_cmd, new_value_t.out_box_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: out_box_stat:4",
              "General purpose data bits, suggested usage is for  Out Box OUTBOX status (SW can change definition)",
              4, old_value_t.out_box_stat, new_value_t.out_box_stat };
    m_bit_details_model.bits.append(entry);
    entry = { "28: n_a1:1",
              "Reserved = 0",
              1, old_value_t.n_a1, new_value_t.n_a1 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: tag:1",
              "Set when the CPU writes this register and cleared when the COP writes this register with this bit set to 1 (write one clear).\n0 = INVALID\n1 = VALID",
              1, old_value_t.tag, new_value_t.tag };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_obe:1",
              "Interrupt CPU on OUTBOX Empty (TAG=0)",
              1, old_value_t.ie_obe, new_value_t.ie_obe };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ie_obf:1",
              "Interrupt COP on OUTBOX Full (TAG=1)",
              1, old_value_t.ie_obf, new_value_t.ie_obf };
    m_bit_details_model.bits.append(entry);
}



bool Res_semaDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case RES_SEMA_SHRD_SMP_STA_OFFSET:
    case RES_SEMA_SHRD_SMP_SET_OFFSET:
    case RES_SEMA_SHRD_SMP_CLR_OFFSET:
    case RES_SEMA_SHRD_INBOX_OFFSET:
    case RES_SEMA_SHRD_OUTBOX_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Res_semaDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case RES_SEMA_SHRD_SMP_STA_OFFSET:
        if ((value ^ new_value) & RES_SEMA_SHRD_SMP_STA_UNDEFMASK)
            return true;
        break;
    case RES_SEMA_SHRD_SMP_SET_OFFSET:
        if ((value ^ new_value) & RES_SEMA_SHRD_SMP_SET_UNDEFMASK)
            return true;
        break;
    case RES_SEMA_SHRD_SMP_CLR_OFFSET:
        if ((value ^ new_value) & RES_SEMA_SHRD_SMP_CLR_UNDEFMASK)
            return true;
        break;
    case RES_SEMA_SHRD_INBOX_OFFSET:
        if ((value ^ new_value) & RES_SEMA_SHRD_INBOX_UNDEFMASK)
            return true;
        break;
    case RES_SEMA_SHRD_OUTBOX_OFFSET:
        if ((value ^ new_value) & RES_SEMA_SHRD_OUTBOX_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Res_semaDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case RES_SEMA_SHRD_SMP_STA_OFFSET:
        return QString("RES_SEMA_SHRD_SMP_STA");
    case RES_SEMA_SHRD_SMP_SET_OFFSET:
        return QString("RES_SEMA_SHRD_SMP_SET");
    case RES_SEMA_SHRD_SMP_CLR_OFFSET:
        return QString("RES_SEMA_SHRD_SMP_CLR");
    case RES_SEMA_SHRD_INBOX_OFFSET:
        return QString("RES_SEMA_SHRD_INBOX");
    case RES_SEMA_SHRD_OUTBOX_OFFSET:
        return QString("RES_SEMA_SHRD_OUTBOX");

    default:
        break;
    }

    qDebug() << QString().sprintf("RES_SEMA: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Res_semaDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case RES_SEMA_SHRD_SMP_STA_OFFSET:
        fill_res_sema_shrd_smp_sta_details(value, new_value);
        break;
    case RES_SEMA_SHRD_SMP_SET_OFFSET:
        fill_res_sema_shrd_smp_set_details(value, new_value);
        break;
    case RES_SEMA_SHRD_SMP_CLR_OFFSET:
        fill_res_sema_shrd_smp_clr_details(value, new_value);
        break;
    case RES_SEMA_SHRD_INBOX_OFFSET:
        fill_res_sema_shrd_inbox_details(value, new_value);
        break;
    case RES_SEMA_SHRD_OUTBOX_OFFSET:
        fill_res_sema_shrd_outbox_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
