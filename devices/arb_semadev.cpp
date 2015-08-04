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

#include "arb_semadev.h"

#include <QDebug>

Arb_semaDev::Arb_semaDev(QObject *parent) :
    Device(parent)
{
}

#define ARB_SEMA_SMP_GNT_ST_OFFSET 0x0
#define ARB_SEMA_SMP_GNT_ST_UNDEFMASK 0x00000000
union arb_sema_smp_gnt_st_u {
    struct {
        unsigned int arb_31_arb_0:32;       /* A one in any bit indicates that the processor reading this register as granted status for that bit. A zero indicates semaphore not granted */
    };

    u_int32_t reg32;
};

void Arb_semaDev::fill_arb_sema_smp_gnt_st_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const arb_sema_smp_gnt_st_u old_value_t = { .reg32 = value };
    const arb_sema_smp_gnt_st_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: arb_31_arb_0:32",
              "A one in any bit indicates that the processor reading this register as granted status for that bit. A zero indicates semaphore not granted",
              32, old_value_t.arb_31_arb_0, new_value_t.arb_31_arb_0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Semaphore Granted Status Register";
}

#define ARB_SEMA_SMP_GET_OFFSET 0x4
#define ARB_SEMA_SMP_GET_UNDEFMASK 0x00000000
union arb_sema_smp_get_u {
    struct {
        unsigned int get_31_get_0:32;       /* Writing a one in any bit is a request for that semaphore bit by the processor performing the register write */
    };

    u_int32_t reg32;
};

void Arb_semaDev::fill_arb_sema_smp_get_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const arb_sema_smp_get_u old_value_t = { .reg32 = value };
    const arb_sema_smp_get_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: get_31_get_0:32",
              "Writing a one in any bit is a request for that semaphore bit by the processor performing the register write",
              32, old_value_t.get_31_get_0, new_value_t.get_31_get_0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Request Arbitration Semaphore Register";
}

#define ARB_SEMA_SMP_PUT_OFFSET 0x8
#define ARB_SEMA_SMP_PUT_UNDEFMASK 0x00000000
union arb_sema_smp_put_u {
    struct {
        unsigned int put_31_put_0:32;       /* Writing a one in any bit will clear the corresponding semaphore bit by the processor performing the register write */
    };

    u_int32_t reg32;
};

void Arb_semaDev::fill_arb_sema_smp_put_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const arb_sema_smp_put_u old_value_t = { .reg32 = value };
    const arb_sema_smp_put_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: put_31_put_0:32",
              "Writing a one in any bit will clear the corresponding semaphore bit by the processor performing the register write",
              32, old_value_t.put_31_put_0, new_value_t.put_31_put_0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Arbitration Semaphore Put Request Register";
}

#define ARB_SEMA_SMP_REQ_ST_OFFSET 0xC
#define ARB_SEMA_SMP_REQ_ST_UNDEFMASK 0x00000000
union arb_sema_smp_req_st_u {
    struct {
        unsigned int req_31_req_0:32;       /* A one in any bit indicates a request pending status. The corresponding bits are set when the request for the individual resource is pending. The read by CPU of this register shows the pending status for CPU and a read of this register by AVP (COP) shows the pending status for AVP */
    };

    u_int32_t reg32;
};

void Arb_semaDev::fill_arb_sema_smp_req_st_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const arb_sema_smp_req_st_u old_value_t = { .reg32 = value };
    const arb_sema_smp_req_st_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: req_31_req_0:32",
              "A one in any bit indicates a request pending status. The corresponding bits are set when the request for the individual resource is pending. The read by CPU of this register shows the pending status for CPU and a read of this register by AVP (COP) shows the pending status for AVP",
              32, old_value_t.req_31_req_0, new_value_t.req_31_req_0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Arbitration Request Pending Status (1=PENDING) Register";
}

bool Arb_semaDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case ARB_SEMA_SMP_GNT_ST_OFFSET:
    case ARB_SEMA_SMP_GET_OFFSET:
    case ARB_SEMA_SMP_PUT_OFFSET:
    case ARB_SEMA_SMP_REQ_ST_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Arb_semaDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case ARB_SEMA_SMP_GNT_ST_OFFSET:
        if ((value ^ new_value) & ARB_SEMA_SMP_GNT_ST_UNDEFMASK)
            return true;
        break;
    case ARB_SEMA_SMP_GET_OFFSET:
        if ((value ^ new_value) & ARB_SEMA_SMP_GET_UNDEFMASK)
            return true;
        break;
    case ARB_SEMA_SMP_PUT_OFFSET:
        if ((value ^ new_value) & ARB_SEMA_SMP_PUT_UNDEFMASK)
            return true;
        break;
    case ARB_SEMA_SMP_REQ_ST_OFFSET:
        if ((value ^ new_value) & ARB_SEMA_SMP_REQ_ST_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Arb_semaDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case ARB_SEMA_SMP_GNT_ST_OFFSET:
        return QString("ARB_SEMA_SMP_GNT_ST");
    case ARB_SEMA_SMP_GET_OFFSET:
        return QString("ARB_SEMA_SMP_GET");
    case ARB_SEMA_SMP_PUT_OFFSET:
        return QString("ARB_SEMA_SMP_PUT");
    case ARB_SEMA_SMP_REQ_ST_OFFSET:
        return QString("ARB_SEMA_SMP_REQ_ST");

    default:
        break;
    }

    qDebug() << QString().sprintf("ARB_SEMA: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Arb_semaDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case ARB_SEMA_SMP_GNT_ST_OFFSET:
        fill_arb_sema_smp_gnt_st_details(value, new_value);
        break;
    case ARB_SEMA_SMP_GET_OFFSET:
        fill_arb_sema_smp_get_details(value, new_value);
        break;
    case ARB_SEMA_SMP_PUT_OFFSET:
        fill_arb_sema_smp_put_details(value, new_value);
        break;
    case ARB_SEMA_SMP_REQ_ST_OFFSET:
        fill_arb_sema_smp_req_st_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
