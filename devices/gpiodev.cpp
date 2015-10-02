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

#include "gpiodev.h"

#include <QDebug>

GpioDev::GpioDev(QObject *parent) :
    Device(parent)
{
}

#define GPIO_CNF_OFFSET 0x0
union gpio_cnf_u {
    struct {
        unsigned int bit_0:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_1:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_2:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_3:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_4:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_5:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_6:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int bit_7:1;               /* Configures each pin to be in either GPIO or SFIO mode; 0 = SPIO; 1 = GPIO */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_cnf_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_cnf_u old_value_t = { .reg32 = value };
    const gpio_cnf_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "Configures each pin to be in either GPIO or SFIO mode;\n0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_OE_OFFSET 0x10
union gpio_oe_u {
    struct {
        unsigned int bit_0:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_1:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_2:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_3:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_4:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_5:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_6:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_7:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_oe_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_oe_u old_value_t = { .reg32 = value };
    const gpio_oe_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_OUT_OFFSET 0x20
union gpio_out_u {
    struct {
        unsigned int bit_0:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_1:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_2:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_3:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_4:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_5:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_6:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int bit_7:1;               /* GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state; 0 = LOW; 1 = HIGH */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_out_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_out_u old_value_t = { .reg32 = value };
    const gpio_out_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "GPIO_CNF.x=1 (in GPIO mode) AND GPIO_OE.x=1 (GPIO output enabled) mxst be true for this to be a valid state;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_IN_OFFSET 0x30
union gpio_in_u {
    struct {
        unsigned int bit_0:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_1:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_2:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_3:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_4:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_5:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_6:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int bit_7:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = LOW; 1 = HIGH */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_in_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_in_u old_value_t = { .reg32 = value };
    const gpio_in_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_INT_STA_OFFSET 0x40
union gpio_int_sta_u {
    struct {
        unsigned int bit_0:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_1:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_2:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_3:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_4:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_5:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_6:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_7:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_int_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_int_sta_u old_value_t = { .reg32 = value };
    const gpio_int_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_INT_ENB_OFFSET 0x50
union gpio_int_enb_u {
    struct {
        unsigned int bit_0:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_1:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_2:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_3:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_4:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_5:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_6:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_7:1;               /* GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_int_enb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_int_enb_u old_value_t = { .reg32 = value };
    const gpio_int_enb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "GPIO mode (GPIO_CNF.x=1) must be true for this condition to be valid;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_INT_LVL_OFFSET 0x60
union gpio_int_lvl_u {
    struct {
        unsigned int bit_0:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_1:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_2:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_3:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_4:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_5:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_6:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int bit_7:1;               /* Interrupt Activation Level or Edge (HIGH for High level or Rising Edge); 0 = LOW; 1 = HIGH */
        unsigned int edge_0:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_1:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_2:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_3:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_4:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_5:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_6:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int edge_7:1;              /* 1 means Configure as Edge-Triggered Interrupt */
        unsigned int delta_0:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_1:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_2:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_3:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_4:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_5:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_6:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int delta_7:1;             /* 1 means Trigger Interrupt on ANY change of input if EDGE is TRUE */
        unsigned int undefined_bits_24_31:8;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_int_lvl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_int_lvl_u old_value_t = { .reg32 = value };
    const gpio_int_lvl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "Interrupt Activation Level or Edge (HIGH for High level or Rising Edge);\n0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: edge_0:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_0, new_value_t.edge_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: edge_1:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_1, new_value_t.edge_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: edge_2:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_2, new_value_t.edge_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: edge_3:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_3, new_value_t.edge_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: edge_4:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_4, new_value_t.edge_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: edge_5:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_5, new_value_t.edge_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: edge_6:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_6, new_value_t.edge_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: edge_7:1",
              "1 means Configure as Edge-Triggered Interrupt",
              1, old_value_t.edge_7, new_value_t.edge_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: delta_0:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_0, new_value_t.delta_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: delta_1:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_1, new_value_t.delta_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: delta_2:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_2, new_value_t.delta_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: delta_3:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_3, new_value_t.delta_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: delta_4:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_4, new_value_t.delta_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: delta_5:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_5, new_value_t.delta_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: delta_6:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_6, new_value_t.delta_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: delta_7:1",
              "1 means Trigger Interrupt on ANY change of input if EDGE is TRUE",
              1, old_value_t.delta_7, new_value_t.delta_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_INT_CLR_OFFSET 0x70
union gpio_int_clr_u {
    struct {
        unsigned int bit_0:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_1:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_2:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_3:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_4:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_5:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_6:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int bit_7:1;               /* GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid; 0 = SET; 1 = CLEAR */
        unsigned int undefined_bits_8_31:24;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_int_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_int_clr_u old_value_t = { .reg32 = value };
    const gpio_int_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "GPIO mode (GPIO_CNF.x=1) and GPIO_INT.ENB.x=1 must be true for this condition to be valid;\n0 = SET;\n1 = CLEAR",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_MSK_CNF_OFFSET 0x800
union gpio_msk_cnf_u {
    struct {
        unsigned int bit_0:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int bit_1:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int bit_2:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int bit_3:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int bit_4:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int bit_5:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int bit_6:1;               /* 0 = SPIO; 1= GPIO */
        unsigned int bit_7:1;               /* 0 = SPIO; 1 = GPIO */
        unsigned int msk0:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk1:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk2:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk3:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk4:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk5:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk6:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk7:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_msk_cnf_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_msk_cnf_u old_value_t = { .reg32 = value };
    const gpio_msk_cnf_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "0 = SPIO;\n1= GPIO",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "0 = SPIO;\n1 = GPIO",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: msk0:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk0, new_value_t.msk0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: msk1:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk1, new_value_t.msk1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: msk2:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk2, new_value_t.msk2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: msk3:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk3, new_value_t.msk3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: msk4:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk4, new_value_t.msk4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: msk5:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk5, new_value_t.msk5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: msk6:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk6, new_value_t.msk6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: msk7:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk7, new_value_t.msk7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_MSK_OE_OFFSET 0x810
union gpio_msk_oe_u {
    struct {
        unsigned int bit_0:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_1:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_2:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_3:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_4:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_5:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_6:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int bit_7:1;               /* 0 = TRI_STATE; 1 = DRIVEN */
        unsigned int msk0:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk1:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk2:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk3:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk4:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk5:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk6:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk7:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_msk_oe_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_msk_oe_u old_value_t = { .reg32 = value };
    const gpio_msk_oe_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "0 = TRI_STATE;\n1 = DRIVEN",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: msk0:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk0, new_value_t.msk0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: msk1:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk1, new_value_t.msk1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: msk2:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk2, new_value_t.msk2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: msk3:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk3, new_value_t.msk3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: msk4:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk4, new_value_t.msk4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: msk5:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk5, new_value_t.msk5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: msk6:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk6, new_value_t.msk6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: msk7:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk7, new_value_t.msk7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_MSK_OUT_OFFSET 0x820
union gpio_msk_out_u {
    struct {
        unsigned int bit_0:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_1:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_2:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_3:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_4:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_5:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_6:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_7:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int msk0:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk1:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk2:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk3:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk4:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk5:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk6:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk7:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_msk_out_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_msk_out_u old_value_t = { .reg32 = value };
    const gpio_msk_out_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: msk0:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk0, new_value_t.msk0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: msk1:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk1, new_value_t.msk1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: msk2:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk2, new_value_t.msk2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: msk3:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk3, new_value_t.msk3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: msk4:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk4, new_value_t.msk4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: msk5:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk5, new_value_t.msk5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: msk6:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk6, new_value_t.msk6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: msk7:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk7, new_value_t.msk7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_MSK_INT_STA_OFFSET 0x840
union gpio_msk_int_sta_u {
    struct {
        unsigned int bit_0:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_1:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_2:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_3:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_4:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_5:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_6:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int bit_7:1;               /* 0 = IN_ACTIVE; 1 = ACTIVE */
        unsigned int msk0:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk1:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk2:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk3:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk4:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk5:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk6:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk7:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_msk_int_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_msk_int_sta_u old_value_t = { .reg32 = value };
    const gpio_msk_int_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "0 = IN_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: msk0:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk0, new_value_t.msk0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: msk1:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk1, new_value_t.msk1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: msk2:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk2, new_value_t.msk2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: msk3:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk3, new_value_t.msk3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: msk4:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk4, new_value_t.msk4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: msk5:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk5, new_value_t.msk5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: msk6:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk6, new_value_t.msk6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: msk7:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk7, new_value_t.msk7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_MSK_INT_ENB_OFFSET 0x850
union gpio_msk_int_enb_u {
    struct {
        unsigned int bit_0:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_1:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_2:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_3:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_4:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_5:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_6:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int bit_7:1;               /* 0 = DISABLE; 1 = ENABLE */
        unsigned int msk0:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk1:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk2:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk3:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk4:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk5:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk6:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int msk7:1;                /* 0=Disable bit for write; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_msk_int_enb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_msk_int_enb_u old_value_t = { .reg32 = value };
    const gpio_msk_int_enb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: msk0:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk0, new_value_t.msk0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: msk1:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk1, new_value_t.msk1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: msk2:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk2, new_value_t.msk2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: msk3:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk3, new_value_t.msk3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: msk4:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk4, new_value_t.msk4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: msk5:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk5, new_value_t.msk5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: msk6:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk6, new_value_t.msk6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: msk7:1",
              "0=Disable bit for write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.msk7, new_value_t.msk7 };
    m_bit_details_model.bits.append(entry);
}

#define GPIO_MSK_INT_LVL_OFFSET 0x860
union gpio_msk_int_lvl_u {
    struct {
        unsigned int bit_0:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_1:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_2:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_3:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_4:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_5:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_6:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int bit_7:1;               /* 0 = LOW; 1 = HIGH */
        unsigned int msk0:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk1:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk2:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk3:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk4:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk5:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk6:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int msk7:1;                /* 0=Disable bit for write; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;

    };

    u_int32_t reg32;
};

void GpioDev::fill_gpio_msk_int_lvl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gpio_msk_int_lvl_u old_value_t = { .reg32 = value };
    const gpio_msk_int_lvl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.bits.clear();
    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bit_0:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_0, new_value_t.bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bit_1:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_1, new_value_t.bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bit_2:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_2, new_value_t.bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bit_3:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_3, new_value_t.bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bit_4:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_4, new_value_t.bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: bit_5:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_5, new_value_t.bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: bit_6:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_6, new_value_t.bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: bit_7:1",
              "0 = LOW;\n1 = HIGH",
              1, old_value_t.bit_7, new_value_t.bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: msk0:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk0, new_value_t.msk0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: msk1:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk1, new_value_t.msk1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: msk2:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk2, new_value_t.msk2 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: msk3:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk3, new_value_t.msk3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: msk4:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk4, new_value_t.msk4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: msk5:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk5, new_value_t.msk5 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: msk6:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk6, new_value_t.msk6 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: msk7:1",
              "0=Disable bit for write;\n1 = ENABLE",
              1, old_value_t.msk7, new_value_t.msk7 };
    m_bit_details_model.bits.append(entry);
}

bool GpioDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset & 0x870) {
    case GPIO_CNF_OFFSET:
    case GPIO_OE_OFFSET:
    case GPIO_OUT_OFFSET:
    case GPIO_IN_OFFSET:
    case GPIO_INT_STA_OFFSET:
    case GPIO_INT_ENB_OFFSET:
    case GPIO_INT_LVL_OFFSET:
    case GPIO_INT_CLR_OFFSET:
    case GPIO_MSK_CNF_OFFSET:
    case GPIO_MSK_OE_OFFSET:
    case GPIO_MSK_OUT_OFFSET:
    case GPIO_MSK_INT_STA_OFFSET:
    case GPIO_MSK_INT_ENB_OFFSET:
    case GPIO_MSK_INT_LVL_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

QString GpioDev::get_register_name(const log_entry &entry) const
{
    int bank = (entry.offset >> 7) & 0x7;
    int port = (entry.offset & 0xf) >> 2;
    int port_nb = bank * 4 + port;
    QString port_name;

    switch (port_nb) {
    case 0 ... 25:
        port_name = QString().sprintf(" (PORT '%c')", port_nb + 65);
        break;
    case 26:
        port_name = " (PORT 'AA')";
        break;
    case 27:
        port_name = " (PORT 'BB')";
        break;
    default:
        Q_ASSERT(false);
        break;
    }

    switch (entry.offset & 0x870) {
    case GPIO_CNF_OFFSET:
        return QString("GPIO_CNF") + port_name;
    case GPIO_OE_OFFSET:
        return QString("GPIO_OE") + port_name;
    case GPIO_OUT_OFFSET:
        return QString("GPIO_OUT") + port_name;
    case GPIO_IN_OFFSET:
        return QString("GPIO_IN") + port_name;
    case GPIO_INT_STA_OFFSET:
        return QString("GPIO_INT_STA") + port_name;
    case GPIO_INT_ENB_OFFSET:
        return QString("GPIO_INT_ENB") + port_name;
    case GPIO_INT_LVL_OFFSET:
        return QString("GPIO_INT_LVL") + port_name;
    case GPIO_INT_CLR_OFFSET:
        return QString("GPIO_INT_CLR") + port_name;
    case GPIO_MSK_CNF_OFFSET:
        return QString("GPIO_MSK_CNF") + port_name;
    case GPIO_MSK_OE_OFFSET:
        return QString("GPIO_MSK_OE") + port_name;
    case GPIO_MSK_OUT_OFFSET:
        return QString("GPIO_MSK_OUT") + port_name;
    case GPIO_MSK_INT_STA_OFFSET:
        return QString("GPIO_MSK_INT_STA") + port_name;
    case GPIO_MSK_INT_ENB_OFFSET:
        return QString("GPIO_MSK_INT_ENB") + port_name;
    case GPIO_MSK_INT_LVL_OFFSET:
        return QString("GPIO_MSK_INT_LVL") + port_name;

    default:
        break;
    }

    qDebug() << QString().sprintf("GPIO: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... 0x%X", entry.offset);
}

void GpioDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset & 0x870) {
    case GPIO_CNF_OFFSET:
        fill_gpio_cnf_details(value, new_value);
        break;
    case GPIO_OE_OFFSET:
        fill_gpio_oe_details(value, new_value);
        break;
    case GPIO_OUT_OFFSET:
        fill_gpio_out_details(value, new_value);
        break;
    case GPIO_IN_OFFSET:
        fill_gpio_in_details(value, new_value);
        break;
    case GPIO_INT_STA_OFFSET:
        fill_gpio_int_sta_details(value, new_value);
        break;
    case GPIO_INT_ENB_OFFSET:
        fill_gpio_int_enb_details(value, new_value);
        break;
    case GPIO_INT_LVL_OFFSET:
        fill_gpio_int_lvl_details(value, new_value);
        break;
    case GPIO_INT_CLR_OFFSET:
        fill_gpio_int_clr_details(value, new_value);
        break;
    case GPIO_MSK_CNF_OFFSET:
        fill_gpio_msk_cnf_details(value, new_value);
        break;
    case GPIO_MSK_OE_OFFSET:
        fill_gpio_msk_oe_details(value, new_value);
        break;
    case GPIO_MSK_OUT_OFFSET:
        fill_gpio_msk_out_details(value, new_value);
        break;
    case GPIO_MSK_INT_STA_OFFSET:
        fill_gpio_msk_int_sta_details(value, new_value);
        break;
    case GPIO_MSK_INT_ENB_OFFSET:
        fill_gpio_msk_int_enb_details(value, new_value);
        break;
    case GPIO_MSK_INT_LVL_OFFSET:
        fill_gpio_msk_int_lvl_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
