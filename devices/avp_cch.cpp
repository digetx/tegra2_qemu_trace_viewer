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

#include "avp_cch.h"

#include <QDebug>

#define PTE0_COMPARE    0xF000
union pte_compare_u {
    struct {
        unsigned int translate_mask:16;
        unsigned int translate_virt_base:16;
    };

    u_int32_t reg32;
};

void AVP_CchDev::fill_pte_compare_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pte_compare_u old_value_t = { .reg32 = value };
    const pte_compare_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: translate_mask:16", "",
              16, old_value_t.translate_mask, new_value_t.translate_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "16: translate_virt_base:16", "",
              16, old_value_t.translate_virt_base, new_value_t.translate_virt_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "";
}

#define PTE0_TRANSLATE  0xF004
#define PTE0_TRANSLATE_UNDEFMASK 0x0000F000
union pte_translate_u {
    struct {
        unsigned int translate_flags:12;
        unsigned int undefined_bits:4;
        unsigned int translate_phys_base:16;
    };

    u_int32_t reg32;
};

void AVP_CchDev::fill_pte_translate_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pte_translate_u old_value_t = { .reg32 = value };
    const pte_translate_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: translate_flags:12", "",
              12, old_value_t.translate_flags, new_value_t.translate_flags };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits:4", "",
              4, old_value_t.undefined_bits, new_value_t.undefined_bits };
    m_bit_details_model.bits.append(entry);
    entry = { "16: translate_phys_base:16", "",
              16, old_value_t.translate_phys_base, new_value_t.translate_phys_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "";
}

bool AVP_CchDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case PTE0_COMPARE:
    case PTE0_TRANSLATE:
        return true;
    default:
        break;
    }

    return false;
}

bool AVP_CchDev::is_undef_changed(const u_int32_t &offset, const u_int32_t &value,
                                  const u_int32_t &new_value) const
{
    switch (offset) {
    case PTE0_TRANSLATE:
        if ((value ^ new_value) & PTE0_TRANSLATE_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString AVP_CchDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case PTE0_COMPARE:
        return QString("PTE0_COMPARE");
    case PTE0_TRANSLATE:
        return QString("PTE0_TRANSLATE");

    default:
        break;
    }

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void AVP_CchDev::fill_bits_details(const u_int32_t &offset,
                                   const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case PTE0_COMPARE:
        fill_pte_compare_details(value, new_value);
        break;
    case PTE0_TRANSLATE:
        fill_pte_translate_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
