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

#include "apb_dmadev.h"

#include <QDebug>

#define COMMAND_OFFSET 0x0
#define COMMAND_UNDEFMASK 0x7FFFFFFF
union command_u {
    struct {
        unsigned int undefined_bits_0_30:31;
        unsigned int gen:1;                 /* Enables Global APB-DMA; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_command_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const command_u old_value_t = { .reg32 = value };
    const command_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_30:31", "", 31, old_value_t.undefined_bits_0_30, new_value_t.undefined_bits_0_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: gen:1",
              "Enables Global APB-DMA;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.gen, new_value_t.gen };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Global Enable bit in the command register enables the APB DMA. Clearing this bit causes active DMA transfers to be paused. Pending bus transactions (ongoing burst) will be completed and no new transactions will be initiated. Setting this bit again resumes the transfers.\nNote that the power on reset value for the APB DMA Global Enable is 0. This bit must be written to 1 before any APB DMA transactions can begin.\nAPB-DMA Command Register";
}

#define STATUS_OFFSET 0x4
#define STATUS_UNDEFMASK 0x00000000
union status_u {
    struct {
        unsigned int ise_eoc_0:1;           /* DMA channel0 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_1:1;           /* DMA channel1 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_2:1;           /* DMA channel2 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_3:1;           /* DMA channel3 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_4:1;           /* DMA channel4 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_5:1;           /* DMA channel5 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_6:1;           /* DMA channel6 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_7:1;           /* DMA channel7 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_8:1;           /* DMA channel8 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_9:1;           /* DMA channel9 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_10:1;          /* DMA channel10 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_11:1;          /* DMA channel11 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_12:1;          /* DMA channel12 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_13:1;          /* DMA channel13 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_14:1;          /* DMA channel14 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ise_eoc_15:1;          /* DMA channel15 Interrupt Status; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int bsy_0:1;               /* DMA channel0 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_1:1;               /* DMA channel1 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_2:1;               /* DMA channel2 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_3:1;               /* DMA channel3 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_4:1;               /* DMA channel4 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_5:1;               /* DMA channel5 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_6:1;               /* DMA channel6 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_7:1;               /* DMA channel7 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_8:1;               /* DMA channel8 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_9:1;               /* DMA channel9 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_10:1;              /* DMA channel10 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_11:1;              /* DMA channel11 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_12:1;              /* DMA channel12 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_13:1;              /* DMA channel13 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_14:1;              /* DMA channel14 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_15:1;              /* DMA channel15 status; 0 = NOT_BUSY; 1 = BUSY */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const status_u old_value_t = { .reg32 = value };
    const status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ise_eoc_0:1",
              "DMA channel0 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_0, new_value_t.ise_eoc_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ise_eoc_1:1",
              "DMA channel1 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_1, new_value_t.ise_eoc_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ise_eoc_2:1",
              "DMA channel2 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_2, new_value_t.ise_eoc_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ise_eoc_3:1",
              "DMA channel3 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_3, new_value_t.ise_eoc_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ise_eoc_4:1",
              "DMA channel4 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_4, new_value_t.ise_eoc_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ise_eoc_5:1",
              "DMA channel5 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_5, new_value_t.ise_eoc_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ise_eoc_6:1",
              "DMA channel6 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_6, new_value_t.ise_eoc_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ise_eoc_7:1",
              "DMA channel7 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_7, new_value_t.ise_eoc_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ise_eoc_8:1",
              "DMA channel8 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_8, new_value_t.ise_eoc_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: ise_eoc_9:1",
              "DMA channel9 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_9, new_value_t.ise_eoc_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ise_eoc_10:1",
              "DMA channel10 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_10, new_value_t.ise_eoc_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ise_eoc_11:1",
              "DMA channel11 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_11, new_value_t.ise_eoc_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ise_eoc_12:1",
              "DMA channel12 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_12, new_value_t.ise_eoc_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ise_eoc_13:1",
              "DMA channel13 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_13, new_value_t.ise_eoc_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ise_eoc_14:1",
              "DMA channel14 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_14, new_value_t.ise_eoc_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ise_eoc_15:1",
              "DMA channel15 Interrupt Status;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ise_eoc_15, new_value_t.ise_eoc_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: bsy_0:1",
              "DMA channel0 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_0, new_value_t.bsy_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: bsy_1:1",
              "DMA channel1 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_1, new_value_t.bsy_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: bsy_2:1",
              "DMA channel2 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_2, new_value_t.bsy_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: bsy_3:1",
              "DMA channel3 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_3, new_value_t.bsy_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: bsy_4:1",
              "DMA channel4 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_4, new_value_t.bsy_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: bsy_5:1",
              "DMA channel5 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_5, new_value_t.bsy_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: bsy_6:1",
              "DMA channel6 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_6, new_value_t.bsy_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: bsy_7:1",
              "DMA channel7 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_7, new_value_t.bsy_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: bsy_8:1",
              "DMA channel8 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_8, new_value_t.bsy_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: bsy_9:1",
              "DMA channel9 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_9, new_value_t.bsy_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: bsy_10:1",
              "DMA channel10 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_10, new_value_t.bsy_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: bsy_11:1",
              "DMA channel11 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_11, new_value_t.bsy_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: bsy_12:1",
              "DMA channel12 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_12, new_value_t.bsy_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: bsy_13:1",
              "DMA channel13 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_13, new_value_t.bsy_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: bsy_14:1",
              "DMA channel14 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_14, new_value_t.bsy_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy_15:1",
              "DMA channel15 status;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.bsy_15, new_value_t.bsy_15 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Busy bits in the Status Register indicate which (if any) of the APB DMA channels have active pending APB DMA transfers. Note that APB DMA transfers that are started in continuous (repetitive) mode will have their busy bits active until the enable bit for the APB DMA channel is cleared to 0 (by the software).\nRead-only Flags set/cleared by HW.\nAPB-DMA Status Register";
}

#define REQUESTORS_TX_OFFSET 0x8
#define REQUESTORS_TX_UNDEFMASK 0xFC000000
union requestors_tx_u {
    struct {
        unsigned int cntr_req:1;            /* 1 = Enable counter request. 0 = Disable counter request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int i2s_2:1;               /* I2S Tx Output FIFO2 (Play) (Peripheral initiated DMA request) 1 = Activate DMA transfer0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int i2s_1:1;               /* I2S Tx Output FIFO1 (Record) (Peripheral initiated DMA request) 1 = Activate DMA transfer0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int spd_i:1;               /* SPDIF Output FIFO (Rx) (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ui_i:1;                /* EBU USR Output (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int mipi:1;                /* MIPI Rx Input FIFO */
        unsigned int i2s2_2:1;              /* I2S2 Tx Output FIFO2 (Play) (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int i2s2_1:1;              /* I2S2 Tx Output FIFO1 (Play) (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_a:1;              /* UART 1; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_b:1;              /* UART 2 (VFIR); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_c:1;              /* UART 3; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int spi:1;                 /* SPI Controller; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ac97:1;                /* AC97; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ac:1;                  /* 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int rsvd:1;                /* 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int sl2b1:1;               /* SLINK 2B-1 (SPI1); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b2:1;               /* SLINK 2B-2 (SPI2); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b3:1;               /* SLINK 2B-3 (SPI3); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b4:1;               /* SLINK 2B-4 (SPI4) 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int uart_d:1;              /* UART4  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int uart_e:1;              /* UART5  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_1:1;               /* I2C1  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_2:1;               /* I2C2  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_3:1;               /* I2C3  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int dvc_i2c:1;             /* DVC-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int owr:1;                 /* OWR-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_requestors_tx_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const requestors_tx_u old_value_t = { .reg32 = value };
    const requestors_tx_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cntr_req:1",
              "1 = Enable counter request.\n0 = Disable counter request;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.cntr_req, new_value_t.cntr_req };
    m_bit_details_model.bits.append(entry);
    entry = { "01: i2s_2:1",
              "I2S Tx Output FIFO2 (Play) (Peripheral initiated DMA request)\n1 = Activate DMA transfer0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s_2, new_value_t.i2s_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2s_1:1",
              "I2S Tx Output FIFO1 (Record) (Peripheral initiated DMA request)\n1 = Activate DMA transfer0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s_1, new_value_t.i2s_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: spd_i:1",
              "SPDIF Output FIFO (Rx) (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.spd_i, new_value_t.spd_i };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ui_i:1",
              "EBU USR Output (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ui_i, new_value_t.ui_i };
    m_bit_details_model.bits.append(entry);
    entry = { "05: mipi:1",
              "MIPI Rx Input FIFO",
              1, old_value_t.mipi, new_value_t.mipi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2s2_2:1",
              "I2S2 Tx Output FIFO2 (Play) (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s2_2, new_value_t.i2s2_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: i2s2_1:1",
              "I2S2 Tx Output FIFO1 (Play) (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s2_1, new_value_t.i2s2_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uart_a:1",
              "UART 1;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.uart_a, new_value_t.uart_a };
    m_bit_details_model.bits.append(entry);
    entry = { "09: uart_b:1",
              "UART 2 (VFIR);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.uart_b, new_value_t.uart_b };
    m_bit_details_model.bits.append(entry);
    entry = { "10: uart_c:1",
              "UART 3;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.uart_c, new_value_t.uart_c };
    m_bit_details_model.bits.append(entry);
    entry = { "11: spi:1",
              "SPI Controller;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ac97:1",
              "AC97;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ac:1",
              "0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ac, new_value_t.ac };
    m_bit_details_model.bits.append(entry);
    entry = { "14: rsvd:1",
              "0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.rsvd, new_value_t.rsvd };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sl2b1:1",
              "SLINK 2B-1 (SPI1);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.sl2b1, new_value_t.sl2b1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: sl2b2:1",
              "SLINK 2B-2 (SPI2);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.sl2b2, new_value_t.sl2b2 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: sl2b3:1",
              "SLINK 2B-3 (SPI3);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.sl2b3, new_value_t.sl2b3 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sl2b4:1",
              "SLINK 2B-4 (SPI4)\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.sl2b4, new_value_t.sl2b4 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: uart_d:1",
              "UART4 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.uart_d, new_value_t.uart_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: uart_e:1",
              "UART5 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.uart_e, new_value_t.uart_e };
    m_bit_details_model.bits.append(entry);
    entry = { "21: i2c_1:1",
              "I2C1 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.i2c_1, new_value_t.i2c_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: i2c_2:1",
              "I2C2 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.i2c_2, new_value_t.i2c_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: i2c_3:1",
              "I2C3 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.i2c_3, new_value_t.i2c_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dvc_i2c:1",
              "DVC-I2C\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.dvc_i2c, new_value_t.dvc_i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "25: owr:1",
              "OWR-I2C\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Tx Requestors are values used as triggers or flow controls for APB DMA transfers.\nThe Tx requestor register is read only. This register is provided only to give the software the ability to see the state of signals that may affect (trigger-start or flow-control-inhibit) APB DMA processes.\nBit[0] in the Tx Requestor channel is a signal generated from the programmable APB DMA Counter. This bit is active whenever the APB DMA Counter value is 0.\nAPB-DMA Requestor Register (Tx)";
}

#define REQUESTORS_RX_OFFSET 0xC
#define REQUESTORS_RX_UNDEFMASK 0xFC000000
union requestors_rx_u {
    struct {
        unsigned int cntr_req:1;            /* indicates Enabled counter request or not; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int i2s_1:1;               /* I2S Rx Input FIFO1 (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int i2s_2:1;               /* I2S Rx Input FIFO2 (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int spd_i:1;               /* SPDIF Input FIFO (Rx) (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ui_i:1;                /* EBU+SPDIF USR Input (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int mipi:1;                /* MIPI Rx Input FIFO */
        unsigned int i2s2_1:1;              /* I2S2 Rx Input FIFO1 (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int i2s2_2:1;              /* I2S2 Rx Input FIFO2 (Peripheral initiated DMA request) 1 = Activate DMA transfer 0 = NOP; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_a:1;              /* UART 1; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_b:1;              /* UART 2 (VFIR); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_c:1;              /* UART 3; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int spi:1;                 /* SPI Controller; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ac97:1;                /* AC97; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int ac:1;                  /* 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int rsvd:1;
        unsigned int sl2b1:1;               /* SLINK 2B-1 (SPI1); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b2:1;               /* SLINK 2B-2 (SPI2); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b3:1;               /* SLINK 2B-3 (SPI3); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b4:1;               /* SLINK 2B-4 (SPI4) 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int uart_d:1;              /* UART4  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int uart_e:1;              /* UART5 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_1:1;               /* I2C1  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_2:1;               /* I2C2  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_3:1;               /* I2C3  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int dvc_i2c:1;             /* DVC-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int owr:1;                 /* OWR-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_requestors_rx_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const requestors_rx_u old_value_t = { .reg32 = value };
    const requestors_rx_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cntr_req:1",
              "indicates Enabled counter request or not;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.cntr_req, new_value_t.cntr_req };
    m_bit_details_model.bits.append(entry);
    entry = { "01: i2s_1:1",
              "I2S Rx Input FIFO1 (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s_1, new_value_t.i2s_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2s_2:1",
              "I2S Rx Input FIFO2 (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s_2, new_value_t.i2s_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: spd_i:1",
              "SPDIF Input FIFO (Rx) (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.spd_i, new_value_t.spd_i };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ui_i:1",
              "EBU+SPDIF USR Input (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ui_i, new_value_t.ui_i };
    m_bit_details_model.bits.append(entry);
    entry = { "05: mipi:1",
              "MIPI Rx Input FIFO",
              1, old_value_t.mipi, new_value_t.mipi };
    m_bit_details_model.bits.append(entry);
    entry = { "06: i2s2_1:1",
              "I2S2 Rx Input FIFO1 (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s2_1, new_value_t.i2s2_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: i2s2_2:1",
              "I2S2 Rx Input FIFO2 (Peripheral initiated DMA request)\n1 = Activate DMA transfer\n0 = NOP;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.i2s2_2, new_value_t.i2s2_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uart_a:1",
              "UART 1;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.uart_a, new_value_t.uart_a };
    m_bit_details_model.bits.append(entry);
    entry = { "09: uart_b:1",
              "UART 2 (VFIR);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.uart_b, new_value_t.uart_b };
    m_bit_details_model.bits.append(entry);
    entry = { "10: uart_c:1",
              "UART 3;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.uart_c, new_value_t.uart_c };
    m_bit_details_model.bits.append(entry);
    entry = { "11: spi:1",
              "SPI Controller;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.spi, new_value_t.spi };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ac97:1",
              "AC97;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ac97, new_value_t.ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ac:1",
              "0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.ac, new_value_t.ac };
    m_bit_details_model.bits.append(entry);
    entry = { "14: rsvd:1", "", 1, old_value_t.rsvd, new_value_t.rsvd };
    m_bit_details_model.bits.append(entry);
    entry = { "15: sl2b1:1",
              "SLINK 2B-1 (SPI1);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.sl2b1, new_value_t.sl2b1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: sl2b2:1",
              "SLINK 2B-2 (SPI2);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.sl2b2, new_value_t.sl2b2 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: sl2b3:1",
              "SLINK 2B-3 (SPI3);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.sl2b3, new_value_t.sl2b3 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sl2b4:1",
              "SLINK 2B-4 (SPI4)\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.sl2b4, new_value_t.sl2b4 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: uart_d:1",
              "UART4 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.uart_d, new_value_t.uart_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: uart_e:1",
              "UART5\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.uart_e, new_value_t.uart_e };
    m_bit_details_model.bits.append(entry);
    entry = { "21: i2c_1:1",
              "I2C1 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.i2c_1, new_value_t.i2c_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: i2c_2:1",
              "I2C2 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.i2c_2, new_value_t.i2c_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: i2c_3:1",
              "I2C3 \n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.i2c_3, new_value_t.i2c_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dvc_i2c:1",
              "DVC-I2C\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.dvc_i2c, new_value_t.dvc_i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "25: owr:1",
              "OWR-I2C\n0 = NOT_ACTIVE\n1 = ACTIVE",
              1, old_value_t.owr, new_value_t.owr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Rx Requestors are values used as triggers or flow controls for APB DMA transfers.\nThe Rx requestor register is read only. This register is provided only to give the software the ability to see the state of signals that may affect (trigger-start or flow-control-inhibit) APB DMA processes.\nBit[0] in the Rx Requestor channel is a signal generated from the programmable APB DMA Counter. This bit is active whenever the APB DMA Counter value is 0.\nAPB-DMA Requestor Register (RX)";
}

#define CNTRL_REG_OFFSET 0x10
#define CNTRL_REG_UNDEFMASK 0x00000000
union cntrl_reg_u {
    struct {
        unsigned int count_value:16;        /* DMA COUNT Value */
        unsigned int ch0_cnt_en:1;          /* Enable the channel0 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1_cnt_en:1;          /* Enable the channel1 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2_cnt_en:1;          /* Enable the channel2 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3_cnt_en:1;          /* Enable the channel3 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4_cnt_en:1;          /* Enable the channel4 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5_cnt_en:1;          /* Enable the channel5 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6_cnt_en:1;          /* Enable the channel6 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7_cnt_en:1;          /* Enable the channel7 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8_cnt_en:1;          /* Enable the channel8 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9_cnt_en:1;          /* Enable the channel9 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10_cnt_en:1;         /* Enable the channel10 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11_cnt_en:1;         /* Enable the channel11 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12_cnt_en:1;         /* Enable the channel12 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13_cnt_en:1;         /* Enable the channel13 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14_cnt_en:1;         /* Enable the channel14 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15_cnt_en:1;         /* Enable the channel15 count; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_cntrl_reg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cntrl_reg_u old_value_t = { .reg32 = value };
    const cntrl_reg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: count_value:16",
              "DMA COUNT Value",
              16, old_value_t.count_value, new_value_t.count_value };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ch0_cnt_en:1",
              "Enable the channel0 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0_cnt_en, new_value_t.ch0_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ch1_cnt_en:1",
              "Enable the channel1 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1_cnt_en, new_value_t.ch1_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ch2_cnt_en:1",
              "Enable the channel2 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2_cnt_en, new_value_t.ch2_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "19: ch3_cnt_en:1",
              "Enable the channel3 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3_cnt_en, new_value_t.ch3_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "20: ch4_cnt_en:1",
              "Enable the channel4 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch4_cnt_en, new_value_t.ch4_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "21: ch5_cnt_en:1",
              "Enable the channel5 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch5_cnt_en, new_value_t.ch5_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "22: ch6_cnt_en:1",
              "Enable the channel6 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch6_cnt_en, new_value_t.ch6_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "23: ch7_cnt_en:1",
              "Enable the channel7 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch7_cnt_en, new_value_t.ch7_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ch8_cnt_en:1",
              "Enable the channel8 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch8_cnt_en, new_value_t.ch8_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ch9_cnt_en:1",
              "Enable the channel9 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch9_cnt_en, new_value_t.ch9_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ch10_cnt_en:1",
              "Enable the channel10 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch10_cnt_en, new_value_t.ch10_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ch11_cnt_en:1",
              "Enable the channel11 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch11_cnt_en, new_value_t.ch11_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ch12_cnt_en:1",
              "Enable the channel12 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch12_cnt_en, new_value_t.ch12_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ch13_cnt_en:1",
              "Enable the channel13 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch13_cnt_en, new_value_t.ch13_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ch14_cnt_en:1",
              "Enable the channel14 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch14_cnt_en, new_value_t.ch14_cnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ch15_cnt_en:1",
              "Enable the channel15 count;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch15_cnt_en, new_value_t.ch15_cnt_en };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The APB DMA Counter is used to slow down the request rates on some APB DMA channels.\nThe APB DMA Counter register stores bits that configure which (if any) channel(s) should be throttled (bits [31:16]) correspond to APB DMA 16 channels.\nThe APB DMA Counter initial/reload count value is programmed in the APB DMA Counter Register (bits[15:0]).The APB DMA Counter is loaded with this initial/reload count value whenever the APB DMA Counter Register is written, and is re-loaded to this saved initial count value on a burst complete (programmable).\nThe APB DMA Counter value will decrement whenever an APB DMA burst complete, and the current count value is non-zero, and any of the bits [31:16] are set.\nAPB-DMA Counter Register";
}

#define IRQ_STA_CPU_OFFSET 0x14
#define IRQ_STA_CPU_UNDEFMASK 0xFFFF0000
union irq_sta_cpu_u {
    struct {
        unsigned int ch0:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel0 */
        unsigned int ch1:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel3; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel4; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel5; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel6; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel7; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel8; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel9; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel10; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel11; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel12; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel13; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel14; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel15; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_irq_sta_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_sta_cpu_u old_value_t = { .reg32 = value };
    const irq_sta_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel0",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel4;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch4, new_value_t.ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel5;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch5, new_value_t.ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel6;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch6, new_value_t.ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel7;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch7, new_value_t.ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ch8:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel8;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch8, new_value_t.ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: ch9:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel9;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch9, new_value_t.ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ch10:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel10;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch10, new_value_t.ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ch11:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel11;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch11, new_value_t.ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ch12:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel12;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch12, new_value_t.ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ch13:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel13;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch13, new_value_t.ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ch14:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel14;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch14, new_value_t.ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ch15:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel15;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch15, new_value_t.ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Gathers all the after-masking CPU directed IRQ status bits.\nAPB-DMA CPU IRQ Status Register";
}

#define IRQ_STA_COP_OFFSET 0x18
#define IRQ_STA_COP_UNDEFMASK 0xFFFF0000
union irq_sta_cop_u {
    struct {
        unsigned int ch0:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel0 */
        unsigned int ch1:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel3; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel4; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel5; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel6; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel7; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel8; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel9; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel10; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel11; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel12; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel13; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel14; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel15; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_irq_sta_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_sta_cop_u old_value_t = { .reg32 = value };
    const irq_sta_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel0",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel4;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch4, new_value_t.ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel5;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch5, new_value_t.ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel6;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch6, new_value_t.ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel7;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch7, new_value_t.ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ch8:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel8;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch8, new_value_t.ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: ch9:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel9;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch9, new_value_t.ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ch10:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel10;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch10, new_value_t.ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ch11:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel11;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch11, new_value_t.ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ch12:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel12;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch12, new_value_t.ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ch13:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel13;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch13, new_value_t.ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ch14:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel14;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch14, new_value_t.ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ch15:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel15;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch15, new_value_t.ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Gathers all the after-masking COP directed IRQ status bits.\nAPB-DMA COP IRQ Status Register";
}

#define IRQ_MASK_OFFSET 0x1C
#define IRQ_MASK_UNDEFMASK 0xFFFF0000
union irq_mask_u {
    struct {
        unsigned int ch0:1;                 /* Each bit allows the associated channel0 IRQ to propagate when '1' */
        unsigned int ch1:1;                 /* Each bit allows the associated channel1 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Each bit allows the associated channel2 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Each bit allows the associated channel3 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Each bit allows the associated channel4 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Each bit allows the associated channel5 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Each bit allows the associated channel6 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Each bit allows the associated channel7 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Each bit allows the associated channel8 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Each bit allows the associated channel9 IRQ to propagate when '1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Each bit allows the associated channel10 IRQ to propagate when '1' 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Each bit allows the associated channel11 IRQ to propagate when '1' 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Each bit allows the associated channel12 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Each bit allows the associated channel13 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Each bit allows the associated channel14 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Each bit allows the associated channel15 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_irq_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_mask_u old_value_t = { .reg32 = value };
    const irq_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Each bit allows the associated channel0 IRQ to propagate when '1'",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Each bit allows the associated channel1 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Each bit allows the associated channel2 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Each bit allows the associated channel3 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4:1",
              "Each bit allows the associated channel4 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch4, new_value_t.ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5:1",
              "Each bit allows the associated channel5 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch5, new_value_t.ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6:1",
              "Each bit allows the associated channel6 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch6, new_value_t.ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7:1",
              "Each bit allows the associated channel7 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch7, new_value_t.ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ch8:1",
              "Each bit allows the associated channel8 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch8, new_value_t.ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: ch9:1",
              "Each bit allows the associated channel9 IRQ to propagate when '1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch9, new_value_t.ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ch10:1",
              "Each bit allows the associated channel10 IRQ to propagate when '1'\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch10, new_value_t.ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ch11:1",
              "Each bit allows the associated channel11 IRQ to propagate when '1'\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch11, new_value_t.ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ch12:1",
              "Each bit allows the associated channel12 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch12, new_value_t.ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ch13:1",
              "Each bit allows the associated channel13 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch13, new_value_t.ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ch14:1",
              "Each bit allows the associated channel14 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch14, new_value_t.ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ch15:1",
              "Each bit allows the associated channel15 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch15, new_value_t.ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Allows the IRQ to propagate when enabled, this is the ANDed result of set and clear.\nAPB-DMA IRQ Mask Register";
}

#define IRQ_MASK_SET_OFFSET 0x20
#define IRQ_MASK_SET_UNDEFMASK 0xFFFF0000
union irq_mask_set_u {
    struct {
        unsigned int ch0:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_irq_mask_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_mask_set_u old_value_t = { .reg32 = value };
    const irq_mask_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch4, new_value_t.ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch5, new_value_t.ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch6, new_value_t.ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch7, new_value_t.ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ch8:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch8, new_value_t.ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: ch9:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch9, new_value_t.ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ch10:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch10, new_value_t.ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ch11:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch11, new_value_t.ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ch12:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch12, new_value_t.ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ch13:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch13, new_value_t.ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ch14:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch14, new_value_t.ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ch15:1",
              "Sets the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch15, new_value_t.ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA IRQ Mask Set Register";
}

#define IRQ_MASK_CLR_OFFSET 0x24
#define IRQ_MASK_CLR_UNDEFMASK 0xFFFF0000
union irq_mask_clr_u {
    struct {
        unsigned int ch0:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_irq_mask_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_mask_clr_u old_value_t = { .reg32 = value };
    const irq_mask_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch4, new_value_t.ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch5, new_value_t.ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch6, new_value_t.ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch7, new_value_t.ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ch8:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch8, new_value_t.ch8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: ch9:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch9, new_value_t.ch9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ch10:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch10, new_value_t.ch10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ch11:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch11, new_value_t.ch11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ch12:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch12, new_value_t.ch12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ch13:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch13, new_value_t.ch13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ch14:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch14, new_value_t.ch14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ch15:1",
              "Clears the Mask Register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch15, new_value_t.ch15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA IRQ Mask Clear Register";
}

#define TRIG_REG_OFFSET 0x28
#define TRIG_REG_UNDEFMASK 0xFE000001
union trig_reg_u {
    struct {
        unsigned int undefined_bit_0:1;
        unsigned int smp_24:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int smp_25:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int smp_26:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int smp_27:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int xrq_a:1;               /* XRQ.A (GPIOA) (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int xrq_b:1;               /* XRQ.B (GPIOB) (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int tmr1:1;                /* Trigger select from Timer (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int tmr2:1;                /* Trigger select from Timer (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_0:1;               /* EOC-0 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_1:1;               /* EOC-1 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_2:1;               /* EOC-2 Initiated DMA Request after transfer completion); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_3:1;               /* EOC-3 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_4:1;               /* EOC-4 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_5:1;               /* EOC-5 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_6:1;               /* EOC-6 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_7:1;               /* EOC-7 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_8:1;               /* EOC-8 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_9:1;               /* EOC-9 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_10:1;              /* EOC-10 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_11:1;              /* EOC-11 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_12:1;              /* EOC-12 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_13:1;              /* EOC-13 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_14:1;              /* EOC-14 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apb_15:1;              /* EOC-15 Initiated DMA Request after transfer completion; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_trig_reg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const trig_reg_u old_value_t = { .reg32 = value };
    const trig_reg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bit_0:1", "", 1, old_value_t.undefined_bit_0, new_value_t.undefined_bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: smp_24:1",
              "Semaphore requests SW initiated DMA request;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.smp_24, new_value_t.smp_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: smp_25:1",
              "Semaphore requests SW initiated DMA request;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.smp_25, new_value_t.smp_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: smp_26:1",
              "Semaphore requests SW initiated DMA request;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.smp_26, new_value_t.smp_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: smp_27:1",
              "Semaphore requests SW initiated DMA request;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.smp_27, new_value_t.smp_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: xrq_a:1",
              "XRQ.A (GPIOA) (Hardware initiated DMA request);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.xrq_a, new_value_t.xrq_a };
    m_bit_details_model.bits.append(entry);
    entry = { "06: xrq_b:1",
              "XRQ.B (GPIOB) (Hardware initiated DMA request);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.xrq_b, new_value_t.xrq_b };
    m_bit_details_model.bits.append(entry);
    entry = { "07: tmr1:1",
              "Trigger select from Timer (Hardware initiated DMA request);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.tmr1, new_value_t.tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: tmr2:1",
              "Trigger select from Timer (Hardware initiated DMA request);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.tmr2, new_value_t.tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb_0:1",
              "EOC-0 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_0, new_value_t.apb_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: apb_1:1",
              "EOC-1 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_1, new_value_t.apb_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: apb_2:1",
              "EOC-2 Initiated DMA Request after transfer completion);\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_2, new_value_t.apb_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: apb_3:1",
              "EOC-3 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_3, new_value_t.apb_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: apb_4:1",
              "EOC-4 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_4, new_value_t.apb_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: apb_5:1",
              "EOC-5 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_5, new_value_t.apb_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: apb_6:1",
              "EOC-6 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_6, new_value_t.apb_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_7:1",
              "EOC-7 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_7, new_value_t.apb_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: apb_8:1",
              "EOC-8 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_8, new_value_t.apb_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: apb_9:1",
              "EOC-9 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_9, new_value_t.apb_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: apb_10:1",
              "EOC-10 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_10, new_value_t.apb_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: apb_11:1",
              "EOC-11 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_11, new_value_t.apb_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: apb_12:1",
              "EOC-12 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_12, new_value_t.apb_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: apb_13:1",
              "EOC-13 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_13, new_value_t.apb_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: apb_14:1",
              "EOC-14 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_14, new_value_t.apb_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: apb_15:1",
              "EOC-15 Initiated DMA Request after transfer completion;\n0 = NOT_ACTIVE;\n1 = ACTIVE",
              1, old_value_t.apb_15, new_value_t.apb_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA Trigger Register";
}

#define CHANNEL_0_CSR_OFFSET 0x1000
#define CHANNEL_0_CSR_UNDEFMASK 0x00000003
union channel_0_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_0_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_0_csr_u old_value_t = { .reg32 = value };
    const channel_0_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Writing a 1 to bit [31] of an APB DMA Channel Control Register will initiate the APB DMA Transfer. Because this action will depend on some values programmed in the other registers, it is recommended that the registers in the address space in the required APB DMA channel be programmed before writing into control register.\nIn \"Once\" mode, the channel is disabled after the APB DMA Transfer has completed. When the channel's transfer completes, an interrupt will be sent if the IE.EOC bit is set. If the transfer requires a trigger or flow, then the corresponding trigger selected by the \"TRIG_SEL\" or \"REQ_SEL\" field must become active respectively before the channel can starts its transfer. If both Trigger and Flow bits are set, both conditions must be met before the channel starts each DMA Burst.\nAPB-DMA-0 Control Register";
}

#define CHANNEL_0_STA_OFFSET 0x1004
#define CHANNEL_0_STA_UNDEFMASK 0x0FFF0003
union channel_0_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* if dir = AHB_WRITE : 0 - ping buffer transfer completed ; 1 - pong buffer transfer completed if dir = AHB_READ : 1 - ping buffer transfer completed ; 0 - pong buffer transfer completed; 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicates whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_0_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_0_sta_u old_value_t = { .reg32 = value };
    const channel_0_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "if dir = AHB_WRITE : 0 - ping buffer transfer completed ; 1 - pong buffer transfer completed if dir = AHB_READ : 1 - ping buffer transfer completed ; 0 - pong buffer transfer completed;\n0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicates whether DMA Channel Status active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-0 Status Register";
}

#define CHANNEL_0_AHB_PTR_OFFSET 0x1010
#define CHANNEL_0_AHB_PTR_UNDEFMASK 0x00000003
union channel_0_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_0_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_0_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_0_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-0 AHB Starting Address Pointer Register";
}

#define CHANNEL_0_AHB_SEQ_OFFSET 0x1014
#define CHANNEL_0_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_0_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time) 0 = RELOAD_FOR_1X_BLOCKS 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits) else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_0_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_0_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_0_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time)\n0 = RELOAD_FOR_1X_BLOCKS\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits) else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-0 AHB Address Sequencer Register";
}

#define CHANNEL_0_APB_PTR_OFFSET 0x1018
#define CHANNEL_0_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_0_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_0_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_0_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_0_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-0 APB Starting Address Pointer Register";
}

#define CHANNEL_0_APB_SEQ_OFFSET 0x101C
#define CHANNEL_0_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_0_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_0_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_0_apb_seq_u old_value_t = { .reg32 = value };
    const channel_0_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-0 APB Address Sequencer Assignments";
}

#define CHANNEL_1_CSR_OFFSET 0x1020
#define CHANNEL_1_CSR_UNDEFMASK 0x00000003
union channel_1_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SL2B4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_1_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_1_csr_u old_value_t = { .reg32 = value };
    const channel_1_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SL2B4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-1 Control";
}

#define CHANNEL_1_STA_OFFSET 0x1024
#define CHANNEL_1_STA_UNDEFMASK 0x0FFF0003
union channel_1_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicates whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_1_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_1_sta_u old_value_t = { .reg32 = value };
    const channel_1_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicates whether DMA Channel Status active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-1 Status Register";
}

#define CHANNEL_1_AHB_PTR_OFFSET 0x1030
#define CHANNEL_1_AHB_PTR_UNDEFMASK 0x00000003
union channel_1_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_1_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_1_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_1_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-1 AHB Starting Address Pointer Register";
}

#define CHANNEL_1_AHB_SEQ_OFFSET 0x1034
#define CHANNEL_1_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_1_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_1_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_1_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_1_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-1 AHB Address Sequencer Register";
}

#define CHANNEL_1_APB_PTR_OFFSET 0x1038
#define CHANNEL_1_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_1_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_1_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_1_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_1_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-1 APB Starting Address Pointer Register";
}

#define CHANNEL_1_APB_SEQ_OFFSET 0x103C
#define CHANNEL_1_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_1_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_1_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_1_apb_seq_u old_value_t = { .reg32 = value };
    const channel_1_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-1 APB Address Sequencer Assignments";
}

#define CHANNEL_2_CSR_OFFSET 0x1040
#define CHANNEL_2_CSR_UNDEFMASK 0x00000003
union channel_2_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4; 19 = UART4; 20 = UART5; 21 = I2C; 22 = I2C2; 23 = I2C3; 24 = DVC_I2C; 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_2_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_2_csr_u old_value_t = { .reg32 = value };
    const channel_2_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4;\n19 = UART4;\n20 = UART5;\n21 = I2C;\n22 = I2C2;\n23 = I2C3;\n24 = DVC_I2C;\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-2 Control";
}

#define CHANNEL_2_STA_OFFSET 0x1044
#define CHANNEL_2_STA_UNDEFMASK 0x0FFF0003
union channel_2_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicates whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_2_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_2_sta_u old_value_t = { .reg32 = value };
    const channel_2_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicates whether DMA Channel Status active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-2 Status Register";
}

#define CHANNEL_2_AHB_PTR_OFFSET 0x1050
#define CHANNEL_2_AHB_PTR_UNDEFMASK 0x00000003
union channel_2_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_2_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_2_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_2_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-2 AHB Starting Address Pointer Register";
}

#define CHANNEL_2_AHB_SEQ_OFFSET 0x1054
#define CHANNEL_2_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_2_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_2_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_2_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_2_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-2 AHB Address Sequencer Register";
}

#define CHANNEL_2_APB_PTR_OFFSET 0x1058
#define CHANNEL_2_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_2_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_2_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_2_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_2_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-2 APB Starting Address Pointer Register";
}

#define CHANNEL_2_APB_SEQ_OFFSET 0x105C
#define CHANNEL_2_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_2_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_2_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_2_apb_seq_u old_value_t = { .reg32 = value };
    const channel_2_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-2 APB Address Sequencer Assignments";
}

#define CHANNEL_3_CSR_OFFSET 0x1060
#define CHANNEL_3_CSR_UNDEFMASK 0x00000003
union channel_3_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_3_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_3_csr_u old_value_t = { .reg32 = value };
    const channel_3_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-3 Control";
}

#define CHANNEL_3_STA_OFFSET 0x1064
#define CHANNEL_3_STA_UNDEFMASK 0x0FFF0003
union channel_3_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicates whether DMA Channel Status active; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_3_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_3_sta_u old_value_t = { .reg32 = value };
    const channel_3_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicates whether DMA Channel Status active;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-3 Status Register";
}

#define CHANNEL_3_AHB_PTR_OFFSET 0x1070
#define CHANNEL_3_AHB_PTR_UNDEFMASK 0x00000003
union channel_3_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_3_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_3_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_3_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-3 AHB Starting Address Pointer Register";
}

#define CHANNEL_3_AHB_SEQ_OFFSET 0x1074
#define CHANNEL_3_AHB_SEQ_UNDEFMASK 0x00F8FFFF
union channel_3_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int undefined_bits_19_23:5;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_3_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_3_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_3_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-3 AHB Address Sequencer Register";
}

#define CHANNEL_3_APB_PTR_OFFSET 0x1078
#define CHANNEL_3_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_3_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_3_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_3_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_3_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-3 APB Starting Address Pointer Register";
}

#define CHANNEL_3_APB_SEQ_OFFSET 0x107C
#define CHANNEL_3_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_3_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_3_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_3_apb_seq_u old_value_t = { .reg32 = value };
    const channel_3_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-3 APB Address Sequencer Assignments";
}

#define CHANNEL_4_CSR_OFFSET 0x1080
#define CHANNEL_4_CSR_UNDEFMASK 0x00000003
union channel_4_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_4_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_4_csr_u old_value_t = { .reg32 = value };
    const channel_4_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-4 Control";
}

#define CHANNEL_4_STA_OFFSET 0x1084
#define CHANNEL_4_STA_UNDEFMASK 0x0FFF0003
union channel_4_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicates whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_4_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_4_sta_u old_value_t = { .reg32 = value };
    const channel_4_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicates whether DMA Channel Status active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-4 Status Register";
}

#define CHANNEL_4_AHB_PTR_OFFSET 0x1090
#define CHANNEL_4_AHB_PTR_UNDEFMASK 0x00000003
union channel_4_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_4_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_4_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_4_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-4 AHB Starting Address Pointer Register";
}

#define CHANNEL_4_AHB_SEQ_OFFSET 0x1094
#define CHANNEL_4_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_4_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_4_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_4_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_4_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-4 AHB Address Sequencer Register";
}

#define CHANNEL_4_APB_PTR_OFFSET 0x1098
#define CHANNEL_4_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_4_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_4_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_4_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_4_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-4 APB Starting Address Pointer Register";
}

#define CHANNEL_4_APB_SEQ_OFFSET 0x109C
#define CHANNEL_4_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_4_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_4_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_4_apb_seq_u old_value_t = { .reg32 = value };
    const channel_4_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-4 APB Address Sequencer Assignments";
}

#define CHANNEL_5_CSR_OFFSET 0x10A0
#define CHANNEL_5_CSR_UNDEFMASK 0x00000003
union channel_5_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_5_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_5_csr_u old_value_t = { .reg32 = value };
    const channel_5_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-5 Control";
}

#define CHANNEL_5_STA_OFFSET 0x10A4
#define CHANNEL_5_STA_UNDEFMASK 0x0FFF0003
union channel_5_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_5_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_5_sta_u old_value_t = { .reg32 = value };
    const channel_5_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate whether DMA Channel Status active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-5 Status Register";
}

#define CHANNEL_5_AHB_PTR_OFFSET 0x10B0
#define CHANNEL_5_AHB_PTR_UNDEFMASK 0x00000003
union channel_5_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_5_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_5_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_5_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-5 AHB Starting Address Pointer Register";
}

#define CHANNEL_5_AHB_SEQ_OFFSET 0x10B4
#define CHANNEL_5_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_5_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_5_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_5_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_5_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-5 AHB Address Sequencer Register";
}

#define CHANNEL_5_APB_PTR_OFFSET 0x10B8
#define CHANNEL_5_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_5_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_5_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_5_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_5_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-5 APB Starting Address Pointer Register";
}

#define CHANNEL_5_APB_SEQ_OFFSET 0x10BC
#define CHANNEL_5_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_5_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_5_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_5_apb_seq_u old_value_t = { .reg32 = value };
    const channel_5_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-5 APB Address Sequencer Assignments";
}

#define CHANNEL_6_CSR_OFFSET 0x10C0
#define CHANNEL_6_CSR_UNDEFMASK 0x00000003
union channel_6_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_6_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_6_csr_u old_value_t = { .reg32 = value };
    const channel_6_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-6 Control";
}

#define CHANNEL_6_STA_OFFSET 0x10C4
#define CHANNEL_6_STA_UNDEFMASK 0x0FFF0003
union channel_6_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_6_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_6_sta_u old_value_t = { .reg32 = value };
    const channel_6_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate whether DMA Channel Status active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-6 Status Register";
}

#define CHANNEL_6_AHB_PTR_OFFSET 0x10D0
#define CHANNEL_6_AHB_PTR_UNDEFMASK 0x00000003
union channel_6_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_6_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_6_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_6_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-6 AHB Starting Address Pointer Register";
}

#define CHANNEL_6_AHB_SEQ_OFFSET 0x10D4
#define CHANNEL_6_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_6_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_6_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_6_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_6_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-6 AHB Address Sequencer Register";
}

#define CHANNEL_6_APB_PTR_OFFSET 0x10D8
#define CHANNEL_6_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_6_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_6_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_6_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_6_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-6 APB Starting Address Pointer Register";
}

#define CHANNEL_6_APB_SEQ_OFFSET 0x10DC
#define CHANNEL_6_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_6_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_6_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_6_apb_seq_u old_value_t = { .reg32 = value };
    const channel_6_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-6 APB Address Sequencer Assignments";
}

#define CHANNEL_7_CSR_OFFSET 0x10E0
#define CHANNEL_7_CSR_UNDEFMASK 0x00000003
union channel_7_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_7_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_7_csr_u old_value_t = { .reg32 = value };
    const channel_7_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-7 Control";
}

#define CHANNEL_7_STA_OFFSET 0x10E4
#define CHANNEL_7_STA_UNDEFMASK 0x0FFF0003
union channel_7_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag 0 = NO_INTR 1 = INTR */
        unsigned int bsy:1;                 /* indicate whether DMA Channel Status Active or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_7_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_7_sta_u old_value_t = { .reg32 = value };
    const channel_7_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag\n0 = NO_INTR\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate whether DMA Channel Status Active or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-7 Status Register";
}

#define CHANNEL_7_AHB_PTR_OFFSET 0x10F0
#define CHANNEL_7_AHB_PTR_UNDEFMASK 0x00000003
union channel_7_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_7_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_7_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_7_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-7 AHB Starting Address Pointer Register";
}

#define CHANNEL_7_AHB_SEQ_OFFSET 0x10F4
#define CHANNEL_7_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_7_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_7_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_7_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_7_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-7 AHB Address Sequencer Register";
}

#define CHANNEL_7_APB_PTR_OFFSET 0x10F8
#define CHANNEL_7_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_7_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_7_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_7_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_7_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-7 APB Starting Address Pointer Register";
}

#define CHANNEL_7_APB_SEQ_OFFSET 0x10FC
#define CHANNEL_7_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_7_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_7_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_7_apb_seq_u old_value_t = { .reg32 = value };
    const channel_7_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-7 APB Address Sequencer Assignments";
}

#define CHANNEL_8_CSR_OFFSET 0x1100
#define CHANNEL_8_CSR_UNDEFMASK 0x00000003
union channel_8_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_8_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_8_csr_u old_value_t = { .reg32 = value };
    const channel_8_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-8 Control";
}

#define CHANNEL_8_STA_OFFSET 0x1104
#define CHANNEL_8_STA_UNDEFMASK 0x0FFF0003
union channel_8_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_8_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_8_sta_u old_value_t = { .reg32 = value };
    const channel_8_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-8 Status Register";
}

#define CHANNEL_8_AHB_PTR_OFFSET 0x1110
#define CHANNEL_8_AHB_PTR_UNDEFMASK 0x00000003
union channel_8_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_8_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_8_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_8_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-8 AHB Starting Address Pointer Register";
}

#define CHANNEL_8_AHB_SEQ_OFFSET 0x1114
#define CHANNEL_8_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_8_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_8_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_8_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_8_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-8 AHB Address Sequencer Register";
}

#define CHANNEL_8_APB_PTR_OFFSET 0x1118
#define CHANNEL_8_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_8_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_8_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_8_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_8_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-8 APB Starting Address Pointer Register";
}

#define CHANNEL_8_APB_SEQ_OFFSET 0x111C
#define CHANNEL_8_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_8_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_8_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_8_apb_seq_u old_value_t = { .reg32 = value };
    const channel_8_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-8 APB Address Sequencer Assignments";
}

#define CHANNEL_9_CSR_OFFSET 0x1120
#define CHANNEL_9_CSR_UNDEFMASK 0x00000003
union channel_9_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_9_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_9_csr_u old_value_t = { .reg32 = value };
    const channel_9_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-9 Control";
}

#define CHANNEL_9_STA_OFFSET 0x1124
#define CHANNEL_9_STA_UNDEFMASK 0x0FFF0003
union channel_9_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_9_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_9_sta_u old_value_t = { .reg32 = value };
    const channel_9_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-9 Status Register";
}

#define CHANNEL_9_AHB_PTR_OFFSET 0x1130
#define CHANNEL_9_AHB_PTR_UNDEFMASK 0x00000003
union channel_9_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_9_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_9_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_9_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-9 AHB Starting Address Pointer Register";
}

#define CHANNEL_9_AHB_SEQ_OFFSET 0x1134
#define CHANNEL_9_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_9_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_9_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_9_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_9_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-9 AHB Address Sequencer Register";
}

#define CHANNEL_9_APB_PTR_OFFSET 0x1138
#define CHANNEL_9_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_9_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_9_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_9_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_9_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-9 APB Starting Address Pointer Register";
}

#define CHANNEL_9_APB_SEQ_OFFSET 0x113C
#define CHANNEL_9_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_9_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_9_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_9_apb_seq_u old_value_t = { .reg32 = value };
    const channel_9_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-9 APB Address Sequencer Assignments";
}

#define CHANNEL_10_CSR_OFFSET 0x1140
#define CHANNEL_10_CSR_UNDEFMASK 0x00000003
union channel_10_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0= CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes 1 = Enable Hold (wait) 0 = Disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_10_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_10_csr_u old_value_t = { .reg32 = value };
    const channel_10_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0= CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes\n1 = Enable Hold (wait)\n0 = Disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-10 Control";
}

#define CHANNEL_10_STA_OFFSET 0x1144
#define CHANNEL_10_STA_UNDEFMASK 0x0FFF0003
union channel_10_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_10_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_10_sta_u old_value_t = { .reg32 = value };
    const channel_10_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-10 Status Register";
}

#define CHANNEL_10_AHB_PTR_OFFSET 0x1150
#define CHANNEL_10_AHB_PTR_UNDEFMASK 0x00000003
union channel_10_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_10_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_10_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_10_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-10 AHB Starting Address Pointer Register";
}

#define CHANNEL_10_AHB_SEQ_OFFSET 0x1154
#define CHANNEL_10_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_10_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_10_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_10_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_10_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-10 AHB Address Sequencer Register";
}

#define CHANNEL_10_APB_PTR_OFFSET 0x1158
#define CHANNEL_10_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_10_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_10_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_10_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_10_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-10 APB Starting Address Pointer Register";
}

#define CHANNEL_10_APB_SEQ_OFFSET 0x115C
#define CHANNEL_10_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_10_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_10_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_10_apb_seq_u old_value_t = { .reg32 = value };
    const channel_10_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-10 APB Address Sequencer Assignments";
}

#define CHANNEL_11_CSR_OFFSET 0x1160
#define CHANNEL_11_CSR_UNDEFMASK 0x00000003
union channel_11_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_11_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_11_csr_u old_value_t = { .reg32 = value };
    const channel_11_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-11 Control";
}

#define CHANNEL_11_STA_OFFSET 0x1164
#define CHANNEL_11_STA_UNDEFMASK 0x0FFF0003
union channel_11_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or waiting; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_11_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_11_sta_u old_value_t = { .reg32 = value };
    const channel_11_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or waiting;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-11 Status Register";
}

#define CHANNEL_11_AHB_PTR_OFFSET 0x1170
#define CHANNEL_11_AHB_PTR_UNDEFMASK 0x00000003
union channel_11_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_11_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_11_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_11_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-11 AHB Starting Address Pointer Register";
}

#define CHANNEL_11_AHB_SEQ_OFFSET 0x1174
#define CHANNEL_11_AHB_SEQ_UNDEFMASK 0x00F8FFFF
union channel_11_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int undefined_bits_19_23:5;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits) else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_11_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_11_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_11_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits) else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-11 AHB Address Sequencer Register";
}

#define CHANNEL_11_APB_PTR_OFFSET 0x1178
#define CHANNEL_11_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_11_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_11_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_11_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_11_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper 16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-11 APB Starting Address Pointer Register";
}

#define CHANNEL_11_APB_SEQ_OFFSET 0x117C
#define CHANNEL_11_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_11_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_11_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_11_apb_seq_u old_value_t = { .reg32 = value };
    const channel_11_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-11 APB Address Sequencer Assignments";
}

#define CHANNEL_12_CSR_OFFSET 0x1180
#define CHANNEL_12_CSR_UNDEFMASK 0x00000003
union channel_12_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_12_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_12_csr_u old_value_t = { .reg32 = value };
    const channel_12_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-12 Control";
}

#define CHANNEL_12_STA_OFFSET 0x1184
#define CHANNEL_12_STA_UNDEFMASK 0x0FFF0003
union channel_12_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_12_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_12_sta_u old_value_t = { .reg32 = value };
    const channel_12_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-12 Status Register";
}

#define CHANNEL_12_AHB_PTR_OFFSET 0x1190
#define CHANNEL_12_AHB_PTR_UNDEFMASK 0x00000003
union channel_12_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_12_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_12_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_12_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-12 AHB Starting Address Pointer Register";
}

#define CHANNEL_12_AHB_SEQ_OFFSET 0x1194
#define CHANNEL_12_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_12_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_12_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_12_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_12_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-12 AHB Address Sequencer Register";
}

#define CHANNEL_12_APB_PTR_OFFSET 0x1198
#define CHANNEL_12_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_12_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_12_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_12_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_12_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-12 APB Starting Address Pointer Register";
}

#define CHANNEL_12_APB_SEQ_OFFSET 0x119C
#define CHANNEL_12_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_12_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_12_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_12_apb_seq_u old_value_t = { .reg32 = value };
    const channel_12_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-12 APB Address Sequencer Assignments";
}

#define CHANNEL_13_CSR_OFFSET 0x11A0
#define CHANNEL_13_CSR_UNDEFMASK 0x00000003
union channel_13_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0= AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_13_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_13_csr_u old_value_t = { .reg32 = value };
    const channel_13_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0= AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-13 Control";
}

#define CHANNEL_13_STA_OFFSET 0x11A4
#define CHANNEL_13_STA_UNDEFMASK 0x0FFF0003
union channel_13_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_13_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_13_sta_u old_value_t = { .reg32 = value };
    const channel_13_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-13 Status Register";
}

#define CHANNEL_13_AHB_PTR_OFFSET 0x11B0
#define CHANNEL_13_AHB_PTR_UNDEFMASK 0x00000003
union channel_13_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_13_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_13_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_13_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-13 AHB Starting Address Pointer Register";
}

#define CHANNEL_13_AHB_SEQ_OFFSET 0x11B4
#define CHANNEL_13_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_13_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_13_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_13_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_13_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] };\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-13 AHB Address Sequencer Register";
}

#define CHANNEL_13_APB_PTR_OFFSET 0x11B8
#define CHANNEL_13_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_13_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_13_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_13_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_13_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-13 APB Starting Address Pointer Register";
}

#define CHANNEL_13_APB_SEQ_OFFSET 0x11BC
#define CHANNEL_13_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_13_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0= DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_13_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_13_apb_seq_u old_value_t = { .reg32 = value };
    const channel_13_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0= DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-13 APB Address Sequencer Assignments";
}

#define CHANNEL_14_CSR_OFFSET 0x11C0
#define CHANNEL_14_CSR_UNDEFMASK 0x00000003
union channel_14_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_14_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_14_csr_u old_value_t = { .reg32 = value };
    const channel_14_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-14 Control";
}

#define CHANNEL_14_STA_OFFSET 0x11C4
#define CHANNEL_14_STA_UNDEFMASK 0x0FFF0003
union channel_14_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_14_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_14_sta_u old_value_t = { .reg32 = value };
    const channel_14_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-14 Status Register";
}

#define CHANNEL_14_AHB_PTR_OFFSET 0x11D0
#define CHANNEL_14_AHB_PTR_UNDEFMASK 0x00000003
union channel_14_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_14_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_14_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_14_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-14 AHB Starting Address Pointer Register";
}

#define CHANNEL_14_AHB_SEQ_OFFSET 0x11D4
#define CHANNEL_14_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_14_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_14_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_14_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_14_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-14 AHB Address Sequencer Register";
}

#define CHANNEL_14_APB_PTR_OFFSET 0x11D8
#define CHANNEL_14_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_14_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_14_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_14_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_14_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-14 APB Starting Address Pointer Register";
}

#define CHANNEL_14_APB_SEQ_OFFSET 0x11DC
#define CHANNEL_14_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_14_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_14_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_14_apb_seq_u old_value_t = { .reg32 = value };
    const channel_14_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around Window\n0 = No Wrap\n1 = Wrap on 1 Word Window (def)\n2 = Wrap on 2 Word Window\n3 = Wrap on 4 Word Window\n4 = Wrap on 8 Word Window\n5 = Wrap on 16 Word Window\n6 = Wrap on 32 Word Window\n7 = Wrap on 64 Word Window (RSVD);\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISBALE;\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-14 APB Address Sequencer Assignments";
}

#define CHANNEL_15_CSR_OFFSET 0x11E0
#define CHANNEL_15_CSR_UNDEFMASK 0x00000003
union channel_15_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = I2S_2; 2 = I2S_1; 3 = SPD_I; 4 = UI_I; 5 = MIPI; 6 = I2S2_2; 7 = I2S2_1; 8 = UART1; 9 = UART2; 10 = UART3; 11 = SPI; 12 = AC97; 13 = AC Modem; 14 = RSVD; 15 = SPI1; 16 = SPI2; 17 = SPI3; 18 = SPI4 19 = UART4 20 = UART5 21 = I2C 22 = I2C2 23 = I2C3 24 = DVC_I2C 25 = OWR; 26 = NA26; 27 = NA27; 28 = NA28; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_15_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_15_csr_u old_value_t = { .reg32 = value };
    const channel_15_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32bit word cycles",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:5",
              "0 = CNTR_REQ;\n1 = I2S_2;\n2 = I2S_1;\n3 = SPD_I;\n4 = UI_I;\n5 = MIPI;\n6 = I2S2_2;\n7 = I2S2_1;\n8 = UART1;\n9 = UART2;\n10 = UART3;\n11 = SPI;\n12 = AC97;\n13 = AC Modem;\n14 = RSVD;\n15 = SPI1;\n16 = SPI2;\n17 = SPI3;\n18 = SPI4\n19 = UART4\n20 = UART5\n21 = I2C\n22 = I2C2\n23 = I2C3\n24 = DVC_I2C\n25 = OWR;\n26 = NA26;\n27 = NA27;\n28 = NA28;\n29 = NA29;\n30 = NA30;\n31 = NA31",
              5, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: flow:1",
              "Flow Control Enable (Synchronize Burst Transfers)\n1 = Link to DRQ source\n0 = Independent of DRQ request;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "22: trig_sel:5",
              "Enable on Non-Zero Value;\n0 = NA1;\n1 = SMP24;\n2 = SMP25;\n3 = SMP26;\n4 = SMP27;\n5 = XRQ_A;\n6 = XRQ_B;\n7 = TMR1;\n8 = TMR2;\n9 = APB_0;\n10 = APB_1;\n11 = APB_2;\n12 = APB_3;\n13 = APB_4;\n14 = APB_5;\n15 = APB_6;\n16 = APB_7;\n17 = APB_8;\n18 = APB_9;\n19 = APB_10;\n20 = APB_11;\n21 = APB_12;\n22 = APB_13;\n23 = APB_14;\n24 = APB_15",
              5, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "27: once:1",
              "Run Once or Run Multiple Mode (Allow Retriggering of this Channel)\n1 = Run for One Block Transfer\n0 = Run for Multiple Block Transfer;\n0 = MULTIPLE_BLOCK;\n1 = SINGLE_BLOCK",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dir:1",
              "DMA Transfer Direction\n1 = AHB read to APB write\n0 = APB read to AHB write;\n0 = AHB_WRITE;\n1 = AHB_READ",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "29: hold:1",
              "Hold this Processor until DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "Interrupt when DMA Block Transfer Completes;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "Enable DMA channel transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-15 Control";
}

#define CHANNEL_15_STA_OFFSET 0x11E4
#define CHANNEL_15_STA_UNDEFMASK 0x0FFF0003
union channel_15_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicate DMA Channel Status activate or not; 0 = WAIT; 1 = ACTIVE */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_15_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_15_sta_u old_value_t = { .reg32 = value };
    const channel_15_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Current 32bit word cycles Flags set /cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ping_pong_sts:1",
              "0 = PING_INTR_STS;\n1 = PONG_INTR_STS",
              1, old_value_t.ping_pong_sts, new_value_t.ping_pong_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "29: halt:1",
              "Holding Status of Processor;\n0 = NO_HALT;\n1 = HALT",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ise_eoc:1",
              "Write '1' to clear the flag;\n0 = NO_INTR;\n1 = INTR",
              1, old_value_t.ise_eoc, new_value_t.ise_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "indicate DMA Channel Status activate or not;\n0 = WAIT;\n1 = ACTIVE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-15 Status Register";
}

#define CHANNEL_15_AHB_PTR_OFFSET 0x11F0
#define CHANNEL_15_AHB_PTR_UNDEFMASK 0x00000003
union channel_15_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_15_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_15_ahb_ptr_u old_value_t = { .reg32 = value };
    const channel_15_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "APB-DMA Starting Address for AHB Bus: SW writes to modify",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-15 AHB Starting Address Pointer Register";
}

#define CHANNEL_15_AHB_SEQ_OFFSET 0x11F4
#define CHANNEL_15_AHB_SEQ_UNDEFMASK 0x00F0FFFF
union channel_15_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time); 0 = RELOAD_FOR_1X_BLOCKS; 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP; 1 = CPU; 0 = COP */
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_15_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_15_ahb_seq_u old_value_t = { .reg32 = value };
    const channel_15_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: wrap:3",
              "AHB Address Wrap: AHB Address wrap-around window\n0=No Wrap (default)\n5=Wrap on 512 word window\n1=Wrap on 32 word window\n6=Wrap on 1024 word window\n2=Wrap on 64 word window\n7=Wrap on 2048 word window\n3=Wrap on 128 word window\n4=Wrap on 256 word window;\n0 = NO_WRAP;\n1 = WRAP_0N_32WORDS;\n2 = WRAP_ON_64WORDS;\n3 = WRAP_ON_128WORDS;\n4 = WRAP_ON_256WORDS;\n5 = WRAP_ON_512WORDS;\n6 = WRAP_ON_1024WORDS;\n7 = WRAP_ON_2048WORDS",
              3, old_value_t.wrap, new_value_t.wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations)\n1 = Reload Base Address for 2X blocks (reload every other time)\n0 = Reload Base Address for 1X blocks (def) (reload each time);\n0 = RELOAD_FOR_1X_BLOCKS;\n1 = RELOAD_FOR_2X_BLOCKS",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "AHB Burst Size DMA Burst Length (encoded)\n4 = 1 Word (1x32bits)\n5 = 4 Words (4x32bits)else = 8 Words (8x32bits) default;\n4 = DMA_BURST_1WORDS;\n5 = DMA_BURST_4WORDS;\n6 = DMA_BURST_8WORDS",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ahb_bus_width:3",
              "AHB Bus Width\n0 = 8 bit Bus (RSVD)\n1 = 16 bit Bus (RSVD)\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)4 = 128 bit Bus (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.ahb_bus_width, new_value_t.ahb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP;\n1 = CPU;\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-15 AHB Address Sequencer Register";
}

#define CHANNEL_15_APB_PTR_OFFSET 0x11F8
#define CHANNEL_15_APB_PTR_UNDEFMASK 0xFFFF0003
union channel_15_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:14;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_15_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_15_apb_ptr_u old_value_t = { .reg32 = value };
    const channel_15_apb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: apb_base:14",
              "APB-DMA Starting address for APB Bus: APB Base address: Upper  16 bits are fixed at 0x7000:XXXX",
              14, old_value_t.apb_base, new_value_t.apb_base };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-15 APB Starting Address Pointer Register";
}

#define CHANNEL_15_APB_SEQ_OFFSET 0x11FC
#define CHANNEL_15_APB_SEQ_UNDEFMASK 0x87F8FFFF
union channel_15_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around; 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISABLE 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_dmaDev::fill_channel_15_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_15_apb_seq_u old_value_t = { .reg32 = value };
    const channel_15_apb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: apb_addr_wrap:3",
              "APB Address Wrap-around;\n0 = NO_WRAP;\n1 = WRAP_0N_1WORDS;\n2 = WRAP_ON_2WORDS;\n3 = WRAP_ON_4WORDS;\n4 = WRAP_ON_8WORDS;\n5 = WRAP_ON_16WORDS;\n6 = WRAP_ON_32WORDS;\n7 = WRAP_ON_64WORDS",
              3, old_value_t.apb_addr_wrap, new_value_t.apb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_26:8", "", 8, old_value_t.undefined_bits_19_26, new_value_t.undefined_bits_19_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: apb_data_swap:1",
              "When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]};\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.apb_data_swap, new_value_t.apb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: apb_bus_width:3",
              "0 = 8 bit Bus\n1 = 16 bit Bus\n2 = 32 bit Bus (Def)\n3 = 64 bit Bus (RSVD)\n4 = 128 bit BUS (RSVD);\n0 = BUS_WIDTH_8;\n1 = BUS_WIDTH_16;\n2 = BUS_WIDTH_32;\n3 = BUS_WIDTH_64;\n4 = BUS_WIDTH_128",
              3, old_value_t.apb_bus_width, new_value_t.apb_bus_width };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "APB-DMA-15 APB Address Sequencer Assignments";
}

bool Apb_dmaDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case COMMAND_OFFSET:
    case STATUS_OFFSET:
    case REQUESTORS_TX_OFFSET:
    case REQUESTORS_RX_OFFSET:
    case CNTRL_REG_OFFSET:
    case IRQ_STA_CPU_OFFSET:
    case IRQ_STA_COP_OFFSET:
    case IRQ_MASK_OFFSET:
    case IRQ_MASK_SET_OFFSET:
    case IRQ_MASK_CLR_OFFSET:
    case TRIG_REG_OFFSET:
    case CHANNEL_0_CSR_OFFSET:
    case CHANNEL_0_STA_OFFSET:
    case CHANNEL_0_AHB_PTR_OFFSET:
    case CHANNEL_0_AHB_SEQ_OFFSET:
    case CHANNEL_0_APB_PTR_OFFSET:
    case CHANNEL_0_APB_SEQ_OFFSET:
    case CHANNEL_1_CSR_OFFSET:
    case CHANNEL_1_STA_OFFSET:
    case CHANNEL_1_AHB_PTR_OFFSET:
    case CHANNEL_1_AHB_SEQ_OFFSET:
    case CHANNEL_1_APB_PTR_OFFSET:
    case CHANNEL_1_APB_SEQ_OFFSET:
    case CHANNEL_2_CSR_OFFSET:
    case CHANNEL_2_STA_OFFSET:
    case CHANNEL_2_AHB_PTR_OFFSET:
    case CHANNEL_2_AHB_SEQ_OFFSET:
    case CHANNEL_2_APB_PTR_OFFSET:
    case CHANNEL_2_APB_SEQ_OFFSET:
    case CHANNEL_3_CSR_OFFSET:
    case CHANNEL_3_STA_OFFSET:
    case CHANNEL_3_AHB_PTR_OFFSET:
    case CHANNEL_3_AHB_SEQ_OFFSET:
    case CHANNEL_3_APB_PTR_OFFSET:
    case CHANNEL_3_APB_SEQ_OFFSET:
    case CHANNEL_4_CSR_OFFSET:
    case CHANNEL_4_STA_OFFSET:
    case CHANNEL_4_AHB_PTR_OFFSET:
    case CHANNEL_4_AHB_SEQ_OFFSET:
    case CHANNEL_4_APB_PTR_OFFSET:
    case CHANNEL_4_APB_SEQ_OFFSET:
    case CHANNEL_5_CSR_OFFSET:
    case CHANNEL_5_STA_OFFSET:
    case CHANNEL_5_AHB_PTR_OFFSET:
    case CHANNEL_5_AHB_SEQ_OFFSET:
    case CHANNEL_5_APB_PTR_OFFSET:
    case CHANNEL_5_APB_SEQ_OFFSET:
    case CHANNEL_6_CSR_OFFSET:
    case CHANNEL_6_STA_OFFSET:
    case CHANNEL_6_AHB_PTR_OFFSET:
    case CHANNEL_6_AHB_SEQ_OFFSET:
    case CHANNEL_6_APB_PTR_OFFSET:
    case CHANNEL_6_APB_SEQ_OFFSET:
    case CHANNEL_7_CSR_OFFSET:
    case CHANNEL_7_STA_OFFSET:
    case CHANNEL_7_AHB_PTR_OFFSET:
    case CHANNEL_7_AHB_SEQ_OFFSET:
    case CHANNEL_7_APB_PTR_OFFSET:
    case CHANNEL_7_APB_SEQ_OFFSET:
    case CHANNEL_8_CSR_OFFSET:
    case CHANNEL_8_STA_OFFSET:
    case CHANNEL_8_AHB_PTR_OFFSET:
    case CHANNEL_8_AHB_SEQ_OFFSET:
    case CHANNEL_8_APB_PTR_OFFSET:
    case CHANNEL_8_APB_SEQ_OFFSET:
    case CHANNEL_9_CSR_OFFSET:
    case CHANNEL_9_STA_OFFSET:
    case CHANNEL_9_AHB_PTR_OFFSET:
    case CHANNEL_9_AHB_SEQ_OFFSET:
    case CHANNEL_9_APB_PTR_OFFSET:
    case CHANNEL_9_APB_SEQ_OFFSET:
    case CHANNEL_10_CSR_OFFSET:
    case CHANNEL_10_STA_OFFSET:
    case CHANNEL_10_AHB_PTR_OFFSET:
    case CHANNEL_10_AHB_SEQ_OFFSET:
    case CHANNEL_10_APB_PTR_OFFSET:
    case CHANNEL_10_APB_SEQ_OFFSET:
    case CHANNEL_11_CSR_OFFSET:
    case CHANNEL_11_STA_OFFSET:
    case CHANNEL_11_AHB_PTR_OFFSET:
    case CHANNEL_11_AHB_SEQ_OFFSET:
    case CHANNEL_11_APB_PTR_OFFSET:
    case CHANNEL_11_APB_SEQ_OFFSET:
    case CHANNEL_12_CSR_OFFSET:
    case CHANNEL_12_STA_OFFSET:
    case CHANNEL_12_AHB_PTR_OFFSET:
    case CHANNEL_12_AHB_SEQ_OFFSET:
    case CHANNEL_12_APB_PTR_OFFSET:
    case CHANNEL_12_APB_SEQ_OFFSET:
    case CHANNEL_13_CSR_OFFSET:
    case CHANNEL_13_STA_OFFSET:
    case CHANNEL_13_AHB_PTR_OFFSET:
    case CHANNEL_13_AHB_SEQ_OFFSET:
    case CHANNEL_13_APB_PTR_OFFSET:
    case CHANNEL_13_APB_SEQ_OFFSET:
    case CHANNEL_14_CSR_OFFSET:
    case CHANNEL_14_STA_OFFSET:
    case CHANNEL_14_AHB_PTR_OFFSET:
    case CHANNEL_14_AHB_SEQ_OFFSET:
    case CHANNEL_14_APB_PTR_OFFSET:
    case CHANNEL_14_APB_SEQ_OFFSET:
    case CHANNEL_15_CSR_OFFSET:
    case CHANNEL_15_STA_OFFSET:
    case CHANNEL_15_AHB_PTR_OFFSET:
    case CHANNEL_15_AHB_SEQ_OFFSET:
    case CHANNEL_15_APB_PTR_OFFSET:
    case CHANNEL_15_APB_SEQ_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Apb_dmaDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case COMMAND_OFFSET:
        if ((value ^ new_value) & COMMAND_UNDEFMASK)
            return true;
        break;
    case STATUS_OFFSET:
        if ((value ^ new_value) & STATUS_UNDEFMASK)
            return true;
        break;
    case REQUESTORS_TX_OFFSET:
        if ((value ^ new_value) & REQUESTORS_TX_UNDEFMASK)
            return true;
        break;
    case REQUESTORS_RX_OFFSET:
        if ((value ^ new_value) & REQUESTORS_RX_UNDEFMASK)
            return true;
        break;
    case CNTRL_REG_OFFSET:
        if ((value ^ new_value) & CNTRL_REG_UNDEFMASK)
            return true;
        break;
    case IRQ_STA_CPU_OFFSET:
        if ((value ^ new_value) & IRQ_STA_CPU_UNDEFMASK)
            return true;
        break;
    case IRQ_STA_COP_OFFSET:
        if ((value ^ new_value) & IRQ_STA_COP_UNDEFMASK)
            return true;
        break;
    case IRQ_MASK_OFFSET:
        if ((value ^ new_value) & IRQ_MASK_UNDEFMASK)
            return true;
        break;
    case IRQ_MASK_SET_OFFSET:
        if ((value ^ new_value) & IRQ_MASK_SET_UNDEFMASK)
            return true;
        break;
    case IRQ_MASK_CLR_OFFSET:
        if ((value ^ new_value) & IRQ_MASK_CLR_UNDEFMASK)
            return true;
        break;
    case TRIG_REG_OFFSET:
        if ((value ^ new_value) & TRIG_REG_UNDEFMASK)
            return true;
        break;
    case CHANNEL_0_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_0_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_0_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_0_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_0_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_0_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_0_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_0_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_0_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_0_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_0_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_0_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_1_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_1_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_1_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_1_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_1_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_1_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_1_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_1_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_1_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_1_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_1_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_1_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_2_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_2_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_2_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_2_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_2_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_2_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_2_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_2_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_2_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_2_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_2_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_2_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_3_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_3_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_3_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_3_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_3_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_3_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_3_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_3_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_3_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_3_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_3_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_3_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_4_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_4_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_4_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_4_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_4_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_4_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_4_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_4_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_4_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_4_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_4_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_4_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_5_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_5_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_5_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_5_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_5_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_5_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_5_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_5_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_5_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_5_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_5_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_5_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_6_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_6_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_6_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_6_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_6_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_6_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_6_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_6_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_6_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_6_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_6_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_6_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_7_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_7_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_7_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_7_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_7_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_7_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_7_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_7_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_7_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_7_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_7_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_7_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_8_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_8_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_8_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_8_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_8_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_8_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_8_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_8_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_8_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_8_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_8_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_8_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_9_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_9_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_9_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_9_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_9_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_9_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_9_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_9_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_9_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_9_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_9_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_9_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_10_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_10_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_10_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_10_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_10_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_10_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_10_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_10_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_10_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_10_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_10_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_10_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_11_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_11_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_11_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_11_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_11_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_11_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_11_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_11_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_11_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_11_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_11_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_11_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_12_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_12_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_12_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_12_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_12_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_12_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_12_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_12_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_12_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_12_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_12_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_12_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_13_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_13_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_13_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_13_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_13_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_13_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_13_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_13_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_13_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_13_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_13_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_13_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_14_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_14_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_14_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_14_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_14_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_14_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_14_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_14_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_14_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_14_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_14_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_14_APB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_15_CSR_OFFSET:
        if ((value ^ new_value) & CHANNEL_15_CSR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_15_STA_OFFSET:
        if ((value ^ new_value) & CHANNEL_15_STA_UNDEFMASK)
            return true;
        break;
    case CHANNEL_15_AHB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_15_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_15_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_15_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case CHANNEL_15_APB_PTR_OFFSET:
        if ((value ^ new_value) & CHANNEL_15_APB_PTR_UNDEFMASK)
            return true;
        break;
    case CHANNEL_15_APB_SEQ_OFFSET:
        if ((value ^ new_value) & CHANNEL_15_APB_SEQ_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Apb_dmaDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case COMMAND_OFFSET:
        return QString("COMMAND");
    case STATUS_OFFSET:
        return QString("STATUS");
    case REQUESTORS_TX_OFFSET:
        return QString("REQUESTORS_TX");
    case REQUESTORS_RX_OFFSET:
        return QString("REQUESTORS_RX");
    case CNTRL_REG_OFFSET:
        return QString("CNTRL_REG");
    case IRQ_STA_CPU_OFFSET:
        return QString("IRQ_STA_CPU");
    case IRQ_STA_COP_OFFSET:
        return QString("IRQ_STA_COP");
    case IRQ_MASK_OFFSET:
        return QString("IRQ_MASK");
    case IRQ_MASK_SET_OFFSET:
        return QString("IRQ_MASK_SET");
    case IRQ_MASK_CLR_OFFSET:
        return QString("IRQ_MASK_CLR");
    case TRIG_REG_OFFSET:
        return QString("TRIG_REG");
    case CHANNEL_0_CSR_OFFSET:
        return QString("CHANNEL_0_CSR");
    case CHANNEL_0_STA_OFFSET:
        return QString("CHANNEL_0_STA");
    case CHANNEL_0_AHB_PTR_OFFSET:
        return QString("CHANNEL_0_AHB_PTR");
    case CHANNEL_0_AHB_SEQ_OFFSET:
        return QString("CHANNEL_0_AHB_SEQ");
    case CHANNEL_0_APB_PTR_OFFSET:
        return QString("CHANNEL_0_APB_PTR");
    case CHANNEL_0_APB_SEQ_OFFSET:
        return QString("CHANNEL_0_APB_SEQ");
    case CHANNEL_1_CSR_OFFSET:
        return QString("CHANNEL_1_CSR");
    case CHANNEL_1_STA_OFFSET:
        return QString("CHANNEL_1_STA");
    case CHANNEL_1_AHB_PTR_OFFSET:
        return QString("CHANNEL_1_AHB_PTR");
    case CHANNEL_1_AHB_SEQ_OFFSET:
        return QString("CHANNEL_1_AHB_SEQ");
    case CHANNEL_1_APB_PTR_OFFSET:
        return QString("CHANNEL_1_APB_PTR");
    case CHANNEL_1_APB_SEQ_OFFSET:
        return QString("CHANNEL_1_APB_SEQ");
    case CHANNEL_2_CSR_OFFSET:
        return QString("CHANNEL_2_CSR");
    case CHANNEL_2_STA_OFFSET:
        return QString("CHANNEL_2_STA");
    case CHANNEL_2_AHB_PTR_OFFSET:
        return QString("CHANNEL_2_AHB_PTR");
    case CHANNEL_2_AHB_SEQ_OFFSET:
        return QString("CHANNEL_2_AHB_SEQ");
    case CHANNEL_2_APB_PTR_OFFSET:
        return QString("CHANNEL_2_APB_PTR");
    case CHANNEL_2_APB_SEQ_OFFSET:
        return QString("CHANNEL_2_APB_SEQ");
    case CHANNEL_3_CSR_OFFSET:
        return QString("CHANNEL_3_CSR");
    case CHANNEL_3_STA_OFFSET:
        return QString("CHANNEL_3_STA");
    case CHANNEL_3_AHB_PTR_OFFSET:
        return QString("CHANNEL_3_AHB_PTR");
    case CHANNEL_3_AHB_SEQ_OFFSET:
        return QString("CHANNEL_3_AHB_SEQ");
    case CHANNEL_3_APB_PTR_OFFSET:
        return QString("CHANNEL_3_APB_PTR");
    case CHANNEL_3_APB_SEQ_OFFSET:
        return QString("CHANNEL_3_APB_SEQ");
    case CHANNEL_4_CSR_OFFSET:
        return QString("CHANNEL_4_CSR");
    case CHANNEL_4_STA_OFFSET:
        return QString("CHANNEL_4_STA");
    case CHANNEL_4_AHB_PTR_OFFSET:
        return QString("CHANNEL_4_AHB_PTR");
    case CHANNEL_4_AHB_SEQ_OFFSET:
        return QString("CHANNEL_4_AHB_SEQ");
    case CHANNEL_4_APB_PTR_OFFSET:
        return QString("CHANNEL_4_APB_PTR");
    case CHANNEL_4_APB_SEQ_OFFSET:
        return QString("CHANNEL_4_APB_SEQ");
    case CHANNEL_5_CSR_OFFSET:
        return QString("CHANNEL_5_CSR");
    case CHANNEL_5_STA_OFFSET:
        return QString("CHANNEL_5_STA");
    case CHANNEL_5_AHB_PTR_OFFSET:
        return QString("CHANNEL_5_AHB_PTR");
    case CHANNEL_5_AHB_SEQ_OFFSET:
        return QString("CHANNEL_5_AHB_SEQ");
    case CHANNEL_5_APB_PTR_OFFSET:
        return QString("CHANNEL_5_APB_PTR");
    case CHANNEL_5_APB_SEQ_OFFSET:
        return QString("CHANNEL_5_APB_SEQ");
    case CHANNEL_6_CSR_OFFSET:
        return QString("CHANNEL_6_CSR");
    case CHANNEL_6_STA_OFFSET:
        return QString("CHANNEL_6_STA");
    case CHANNEL_6_AHB_PTR_OFFSET:
        return QString("CHANNEL_6_AHB_PTR");
    case CHANNEL_6_AHB_SEQ_OFFSET:
        return QString("CHANNEL_6_AHB_SEQ");
    case CHANNEL_6_APB_PTR_OFFSET:
        return QString("CHANNEL_6_APB_PTR");
    case CHANNEL_6_APB_SEQ_OFFSET:
        return QString("CHANNEL_6_APB_SEQ");
    case CHANNEL_7_CSR_OFFSET:
        return QString("CHANNEL_7_CSR");
    case CHANNEL_7_STA_OFFSET:
        return QString("CHANNEL_7_STA");
    case CHANNEL_7_AHB_PTR_OFFSET:
        return QString("CHANNEL_7_AHB_PTR");
    case CHANNEL_7_AHB_SEQ_OFFSET:
        return QString("CHANNEL_7_AHB_SEQ");
    case CHANNEL_7_APB_PTR_OFFSET:
        return QString("CHANNEL_7_APB_PTR");
    case CHANNEL_7_APB_SEQ_OFFSET:
        return QString("CHANNEL_7_APB_SEQ");
    case CHANNEL_8_CSR_OFFSET:
        return QString("CHANNEL_8_CSR");
    case CHANNEL_8_STA_OFFSET:
        return QString("CHANNEL_8_STA");
    case CHANNEL_8_AHB_PTR_OFFSET:
        return QString("CHANNEL_8_AHB_PTR");
    case CHANNEL_8_AHB_SEQ_OFFSET:
        return QString("CHANNEL_8_AHB_SEQ");
    case CHANNEL_8_APB_PTR_OFFSET:
        return QString("CHANNEL_8_APB_PTR");
    case CHANNEL_8_APB_SEQ_OFFSET:
        return QString("CHANNEL_8_APB_SEQ");
    case CHANNEL_9_CSR_OFFSET:
        return QString("CHANNEL_9_CSR");
    case CHANNEL_9_STA_OFFSET:
        return QString("CHANNEL_9_STA");
    case CHANNEL_9_AHB_PTR_OFFSET:
        return QString("CHANNEL_9_AHB_PTR");
    case CHANNEL_9_AHB_SEQ_OFFSET:
        return QString("CHANNEL_9_AHB_SEQ");
    case CHANNEL_9_APB_PTR_OFFSET:
        return QString("CHANNEL_9_APB_PTR");
    case CHANNEL_9_APB_SEQ_OFFSET:
        return QString("CHANNEL_9_APB_SEQ");
    case CHANNEL_10_CSR_OFFSET:
        return QString("CHANNEL_10_CSR");
    case CHANNEL_10_STA_OFFSET:
        return QString("CHANNEL_10_STA");
    case CHANNEL_10_AHB_PTR_OFFSET:
        return QString("CHANNEL_10_AHB_PTR");
    case CHANNEL_10_AHB_SEQ_OFFSET:
        return QString("CHANNEL_10_AHB_SEQ");
    case CHANNEL_10_APB_PTR_OFFSET:
        return QString("CHANNEL_10_APB_PTR");
    case CHANNEL_10_APB_SEQ_OFFSET:
        return QString("CHANNEL_10_APB_SEQ");
    case CHANNEL_11_CSR_OFFSET:
        return QString("CHANNEL_11_CSR");
    case CHANNEL_11_STA_OFFSET:
        return QString("CHANNEL_11_STA");
    case CHANNEL_11_AHB_PTR_OFFSET:
        return QString("CHANNEL_11_AHB_PTR");
    case CHANNEL_11_AHB_SEQ_OFFSET:
        return QString("CHANNEL_11_AHB_SEQ");
    case CHANNEL_11_APB_PTR_OFFSET:
        return QString("CHANNEL_11_APB_PTR");
    case CHANNEL_11_APB_SEQ_OFFSET:
        return QString("CHANNEL_11_APB_SEQ");
    case CHANNEL_12_CSR_OFFSET:
        return QString("CHANNEL_12_CSR");
    case CHANNEL_12_STA_OFFSET:
        return QString("CHANNEL_12_STA");
    case CHANNEL_12_AHB_PTR_OFFSET:
        return QString("CHANNEL_12_AHB_PTR");
    case CHANNEL_12_AHB_SEQ_OFFSET:
        return QString("CHANNEL_12_AHB_SEQ");
    case CHANNEL_12_APB_PTR_OFFSET:
        return QString("CHANNEL_12_APB_PTR");
    case CHANNEL_12_APB_SEQ_OFFSET:
        return QString("CHANNEL_12_APB_SEQ");
    case CHANNEL_13_CSR_OFFSET:
        return QString("CHANNEL_13_CSR");
    case CHANNEL_13_STA_OFFSET:
        return QString("CHANNEL_13_STA");
    case CHANNEL_13_AHB_PTR_OFFSET:
        return QString("CHANNEL_13_AHB_PTR");
    case CHANNEL_13_AHB_SEQ_OFFSET:
        return QString("CHANNEL_13_AHB_SEQ");
    case CHANNEL_13_APB_PTR_OFFSET:
        return QString("CHANNEL_13_APB_PTR");
    case CHANNEL_13_APB_SEQ_OFFSET:
        return QString("CHANNEL_13_APB_SEQ");
    case CHANNEL_14_CSR_OFFSET:
        return QString("CHANNEL_14_CSR");
    case CHANNEL_14_STA_OFFSET:
        return QString("CHANNEL_14_STA");
    case CHANNEL_14_AHB_PTR_OFFSET:
        return QString("CHANNEL_14_AHB_PTR");
    case CHANNEL_14_AHB_SEQ_OFFSET:
        return QString("CHANNEL_14_AHB_SEQ");
    case CHANNEL_14_APB_PTR_OFFSET:
        return QString("CHANNEL_14_APB_PTR");
    case CHANNEL_14_APB_SEQ_OFFSET:
        return QString("CHANNEL_14_APB_SEQ");
    case CHANNEL_15_CSR_OFFSET:
        return QString("CHANNEL_15_CSR");
    case CHANNEL_15_STA_OFFSET:
        return QString("CHANNEL_15_STA");
    case CHANNEL_15_AHB_PTR_OFFSET:
        return QString("CHANNEL_15_AHB_PTR");
    case CHANNEL_15_AHB_SEQ_OFFSET:
        return QString("CHANNEL_15_AHB_SEQ");
    case CHANNEL_15_APB_PTR_OFFSET:
        return QString("CHANNEL_15_APB_PTR");
    case CHANNEL_15_APB_SEQ_OFFSET:
        return QString("CHANNEL_15_APB_SEQ");

    default:
        break;
    }

    qDebug() << QString().sprintf("APB_DMA: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Apb_dmaDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case COMMAND_OFFSET:
        fill_command_details(value, new_value);
        break;
    case STATUS_OFFSET:
        fill_status_details(value, new_value);
        break;
    case REQUESTORS_TX_OFFSET:
        fill_requestors_tx_details(value, new_value);
        break;
    case REQUESTORS_RX_OFFSET:
        fill_requestors_rx_details(value, new_value);
        break;
    case CNTRL_REG_OFFSET:
        fill_cntrl_reg_details(value, new_value);
        break;
    case IRQ_STA_CPU_OFFSET:
        fill_irq_sta_cpu_details(value, new_value);
        break;
    case IRQ_STA_COP_OFFSET:
        fill_irq_sta_cop_details(value, new_value);
        break;
    case IRQ_MASK_OFFSET:
        fill_irq_mask_details(value, new_value);
        break;
    case IRQ_MASK_SET_OFFSET:
        fill_irq_mask_set_details(value, new_value);
        break;
    case IRQ_MASK_CLR_OFFSET:
        fill_irq_mask_clr_details(value, new_value);
        break;
    case TRIG_REG_OFFSET:
        fill_trig_reg_details(value, new_value);
        break;
    case CHANNEL_0_CSR_OFFSET:
        fill_channel_0_csr_details(value, new_value);
        break;
    case CHANNEL_0_STA_OFFSET:
        fill_channel_0_sta_details(value, new_value);
        break;
    case CHANNEL_0_AHB_PTR_OFFSET:
        fill_channel_0_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_0_AHB_SEQ_OFFSET:
        fill_channel_0_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_0_APB_PTR_OFFSET:
        fill_channel_0_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_0_APB_SEQ_OFFSET:
        fill_channel_0_apb_seq_details(value, new_value);
        break;
    case CHANNEL_1_CSR_OFFSET:
        fill_channel_1_csr_details(value, new_value);
        break;
    case CHANNEL_1_STA_OFFSET:
        fill_channel_1_sta_details(value, new_value);
        break;
    case CHANNEL_1_AHB_PTR_OFFSET:
        fill_channel_1_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_1_AHB_SEQ_OFFSET:
        fill_channel_1_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_1_APB_PTR_OFFSET:
        fill_channel_1_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_1_APB_SEQ_OFFSET:
        fill_channel_1_apb_seq_details(value, new_value);
        break;
    case CHANNEL_2_CSR_OFFSET:
        fill_channel_2_csr_details(value, new_value);
        break;
    case CHANNEL_2_STA_OFFSET:
        fill_channel_2_sta_details(value, new_value);
        break;
    case CHANNEL_2_AHB_PTR_OFFSET:
        fill_channel_2_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_2_AHB_SEQ_OFFSET:
        fill_channel_2_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_2_APB_PTR_OFFSET:
        fill_channel_2_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_2_APB_SEQ_OFFSET:
        fill_channel_2_apb_seq_details(value, new_value);
        break;
    case CHANNEL_3_CSR_OFFSET:
        fill_channel_3_csr_details(value, new_value);
        break;
    case CHANNEL_3_STA_OFFSET:
        fill_channel_3_sta_details(value, new_value);
        break;
    case CHANNEL_3_AHB_PTR_OFFSET:
        fill_channel_3_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_3_AHB_SEQ_OFFSET:
        fill_channel_3_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_3_APB_PTR_OFFSET:
        fill_channel_3_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_3_APB_SEQ_OFFSET:
        fill_channel_3_apb_seq_details(value, new_value);
        break;
    case CHANNEL_4_CSR_OFFSET:
        fill_channel_4_csr_details(value, new_value);
        break;
    case CHANNEL_4_STA_OFFSET:
        fill_channel_4_sta_details(value, new_value);
        break;
    case CHANNEL_4_AHB_PTR_OFFSET:
        fill_channel_4_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_4_AHB_SEQ_OFFSET:
        fill_channel_4_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_4_APB_PTR_OFFSET:
        fill_channel_4_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_4_APB_SEQ_OFFSET:
        fill_channel_4_apb_seq_details(value, new_value);
        break;
    case CHANNEL_5_CSR_OFFSET:
        fill_channel_5_csr_details(value, new_value);
        break;
    case CHANNEL_5_STA_OFFSET:
        fill_channel_5_sta_details(value, new_value);
        break;
    case CHANNEL_5_AHB_PTR_OFFSET:
        fill_channel_5_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_5_AHB_SEQ_OFFSET:
        fill_channel_5_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_5_APB_PTR_OFFSET:
        fill_channel_5_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_5_APB_SEQ_OFFSET:
        fill_channel_5_apb_seq_details(value, new_value);
        break;
    case CHANNEL_6_CSR_OFFSET:
        fill_channel_6_csr_details(value, new_value);
        break;
    case CHANNEL_6_STA_OFFSET:
        fill_channel_6_sta_details(value, new_value);
        break;
    case CHANNEL_6_AHB_PTR_OFFSET:
        fill_channel_6_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_6_AHB_SEQ_OFFSET:
        fill_channel_6_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_6_APB_PTR_OFFSET:
        fill_channel_6_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_6_APB_SEQ_OFFSET:
        fill_channel_6_apb_seq_details(value, new_value);
        break;
    case CHANNEL_7_CSR_OFFSET:
        fill_channel_7_csr_details(value, new_value);
        break;
    case CHANNEL_7_STA_OFFSET:
        fill_channel_7_sta_details(value, new_value);
        break;
    case CHANNEL_7_AHB_PTR_OFFSET:
        fill_channel_7_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_7_AHB_SEQ_OFFSET:
        fill_channel_7_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_7_APB_PTR_OFFSET:
        fill_channel_7_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_7_APB_SEQ_OFFSET:
        fill_channel_7_apb_seq_details(value, new_value);
        break;
    case CHANNEL_8_CSR_OFFSET:
        fill_channel_8_csr_details(value, new_value);
        break;
    case CHANNEL_8_STA_OFFSET:
        fill_channel_8_sta_details(value, new_value);
        break;
    case CHANNEL_8_AHB_PTR_OFFSET:
        fill_channel_8_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_8_AHB_SEQ_OFFSET:
        fill_channel_8_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_8_APB_PTR_OFFSET:
        fill_channel_8_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_8_APB_SEQ_OFFSET:
        fill_channel_8_apb_seq_details(value, new_value);
        break;
    case CHANNEL_9_CSR_OFFSET:
        fill_channel_9_csr_details(value, new_value);
        break;
    case CHANNEL_9_STA_OFFSET:
        fill_channel_9_sta_details(value, new_value);
        break;
    case CHANNEL_9_AHB_PTR_OFFSET:
        fill_channel_9_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_9_AHB_SEQ_OFFSET:
        fill_channel_9_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_9_APB_PTR_OFFSET:
        fill_channel_9_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_9_APB_SEQ_OFFSET:
        fill_channel_9_apb_seq_details(value, new_value);
        break;
    case CHANNEL_10_CSR_OFFSET:
        fill_channel_10_csr_details(value, new_value);
        break;
    case CHANNEL_10_STA_OFFSET:
        fill_channel_10_sta_details(value, new_value);
        break;
    case CHANNEL_10_AHB_PTR_OFFSET:
        fill_channel_10_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_10_AHB_SEQ_OFFSET:
        fill_channel_10_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_10_APB_PTR_OFFSET:
        fill_channel_10_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_10_APB_SEQ_OFFSET:
        fill_channel_10_apb_seq_details(value, new_value);
        break;
    case CHANNEL_11_CSR_OFFSET:
        fill_channel_11_csr_details(value, new_value);
        break;
    case CHANNEL_11_STA_OFFSET:
        fill_channel_11_sta_details(value, new_value);
        break;
    case CHANNEL_11_AHB_PTR_OFFSET:
        fill_channel_11_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_11_AHB_SEQ_OFFSET:
        fill_channel_11_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_11_APB_PTR_OFFSET:
        fill_channel_11_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_11_APB_SEQ_OFFSET:
        fill_channel_11_apb_seq_details(value, new_value);
        break;
    case CHANNEL_12_CSR_OFFSET:
        fill_channel_12_csr_details(value, new_value);
        break;
    case CHANNEL_12_STA_OFFSET:
        fill_channel_12_sta_details(value, new_value);
        break;
    case CHANNEL_12_AHB_PTR_OFFSET:
        fill_channel_12_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_12_AHB_SEQ_OFFSET:
        fill_channel_12_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_12_APB_PTR_OFFSET:
        fill_channel_12_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_12_APB_SEQ_OFFSET:
        fill_channel_12_apb_seq_details(value, new_value);
        break;
    case CHANNEL_13_CSR_OFFSET:
        fill_channel_13_csr_details(value, new_value);
        break;
    case CHANNEL_13_STA_OFFSET:
        fill_channel_13_sta_details(value, new_value);
        break;
    case CHANNEL_13_AHB_PTR_OFFSET:
        fill_channel_13_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_13_AHB_SEQ_OFFSET:
        fill_channel_13_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_13_APB_PTR_OFFSET:
        fill_channel_13_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_13_APB_SEQ_OFFSET:
        fill_channel_13_apb_seq_details(value, new_value);
        break;
    case CHANNEL_14_CSR_OFFSET:
        fill_channel_14_csr_details(value, new_value);
        break;
    case CHANNEL_14_STA_OFFSET:
        fill_channel_14_sta_details(value, new_value);
        break;
    case CHANNEL_14_AHB_PTR_OFFSET:
        fill_channel_14_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_14_AHB_SEQ_OFFSET:
        fill_channel_14_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_14_APB_PTR_OFFSET:
        fill_channel_14_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_14_APB_SEQ_OFFSET:
        fill_channel_14_apb_seq_details(value, new_value);
        break;
    case CHANNEL_15_CSR_OFFSET:
        fill_channel_15_csr_details(value, new_value);
        break;
    case CHANNEL_15_STA_OFFSET:
        fill_channel_15_sta_details(value, new_value);
        break;
    case CHANNEL_15_AHB_PTR_OFFSET:
        fill_channel_15_ahb_ptr_details(value, new_value);
        break;
    case CHANNEL_15_AHB_SEQ_OFFSET:
        fill_channel_15_ahb_seq_details(value, new_value);
        break;
    case CHANNEL_15_APB_PTR_OFFSET:
        fill_channel_15_apb_ptr_details(value, new_value);
        break;
    case CHANNEL_15_APB_SEQ_OFFSET:
        fill_channel_15_apb_seq_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
