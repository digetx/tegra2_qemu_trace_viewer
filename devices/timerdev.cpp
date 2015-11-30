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

#include "timerdev.h"

#include <QDebug>

#define PTV_OFFSET 0x0
#define PTV_UNDEFMASK 0x20000000
union ptv_u {
    struct {
        unsigned int tmr_ptv:29;            /* Trigger Value: count trigger value (count length). This is in n+1 scheme. If you program the value n, the count trigger value will actually be n+1 */
        unsigned int undefined_bit_29:1;
        unsigned int per:1;                 /* Enable Periodic Interrupt; 0 = DISABLE; 1 = ENABLE */
        unsigned int en:1;                  /* Enable Timer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void TimerDev::fill_ptv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ptv_u old_value_t = { .reg32 = value };
    const ptv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr_ptv:29",
              "Trigger Value: count trigger value (count length). This is in n+1 scheme. If you program the value n, the count trigger value will actually be n+1",
              29, old_value_t.tmr_ptv, new_value_t.tmr_ptv };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: per:1",
              "Enable Periodic Interrupt;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.per, new_value_t.per };
    m_bit_details_model.bits.append(entry);
    entry = { "31: en:1",
              "Enable Timer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.en, new_value_t.en };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Before programming timer:\n    * Input oscillator frequency must be specified in the TIMERUS_USEC_CFG to support multiple frequencies\n    * Program the number of 1us timer counts per \"tick\" in the PTV (Present Trigger Value) register.\n    * Set the PTV EN (enable bit) to start counting down.\n    * When the count reaches zero, interrupt is generated.\n    * To auto-reload the timer counter, set the PTV PER (periodic) bit. Otherwise, leave it clear for a one-shot.\nTimer Present Trigger Value (Set) Register";
}

#define PCR_OFFSET 0x4
#define PCR_UNDEFMASK 0xA0000000
union pcr_u {
    struct {
        unsigned int tmr_pcv:29;            /* Counter value: decrements from PTV */
        unsigned int undefined_bit_29:1;
        unsigned int intr_clr:1;            /* 1 = clears the interrupt, 0 = no affect. Write-1-to-Clear */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void TimerDev::fill_pcr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pcr_u old_value_t = { .reg32 = value };
    const pcr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tmr_pcv:29",
              "Counter value: decrements from PTV",
              29, old_value_t.tmr_pcv, new_value_t.tmr_pcv };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: intr_clr:1",
              "1 = clears the interrupt,\n0 = no affect. Write-1-to-Clear",
              1, old_value_t.intr_clr, new_value_t.intr_clr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "When interrupt is generated, write \"1\" to PCR[30] present count Register) to clear the interrupt.\nTimer interrupt assignments:\n    * Timer 1 = primary interrupt controller bit 0\n    * Timer 2 = primary interrupt controller bit 1\n    * Timer 3 = secondary interrupt controller bit 9\n    * Timer 4 = secondary interrupt controller bit 10\nTimer Present Count Value (Status) Register";
}

bool TimerDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case PTV_OFFSET:
    case PCR_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool TimerDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case PTV_OFFSET:
        if ((value ^ new_value) & PTV_UNDEFMASK)
            return true;
        break;
    case PCR_OFFSET:
        if ((value ^ new_value) & PCR_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString TimerDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case PTV_OFFSET:
        return QString("PTV");
    case PCR_OFFSET:
        return QString("PCR");

    default:
        break;
    }

    qDebug() << QString().sprintf("TIMER: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void TimerDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case PTV_OFFSET:
        fill_ptv_details(value, new_value);
        break;
    case PCR_OFFSET:
        fill_pcr_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
