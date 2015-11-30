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

#include "uartdev.h"

#include <QDebug>

#define THR_DLAB_OFFSET 0x0
#define THR_DLAB_UNDEFMASK 0xFFFFFF00
union thr_dlab_u {
    struct {
        unsigned int thr_rbr_dll:8;         /* Transmit holding register, holds the character to be transmitted by the UART. In FIFO mode, a write to this FIFO places the data at the end of the FIFO; Receive Buffer Register. Rx Data read from here; Divisor Latch LSB (low 8 bits of 16-bit Baud Divisor) */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_thr_dlab_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const thr_dlab_u old_value_t = { .reg32 = value };
    const thr_dlab_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: thr_rbr_dll:8",
              "Transmit holding register, holds the character to be transmitted by the UART. In FIFO mode, a write to this FIFO places the data at the end of the FIFO; Receive Buffer Register. Rx Data read from here; Divisor Latch LSB (low 8 bits of 16-bit Baud Divisor)",
              8, old_value_t.thr_rbr_dll, new_value_t.thr_rbr_dll };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This UART is based on the 16550 industry standard Universal Asynchronous Receiver/Transmitter (UART), with enhancements to support Autobaud detection and End-of-Received Data timeout detection.\nThe UART supports a device clock of up to 72 MHz, for a maximum baud rate of 4.5 Megabits per second.\nThe THR, RBR and DLL registers all occupy the same address space.\n    * The Transmitter Holding Register (THR) is Write-Only, and can be accessed if the LSR.DLAB bit is clear.\n    * The Receiver Buffer Register (RBR) is Read-Only, and can be accessed if the LSR.DLAB bit is clear.\n    * The Divisor Latch LSByte Register (DLL) is Read/Write and can be accessed if the LSR.DLAB bit is set.\nUART Transmit Holding Register";
}

#define IER_DLAB_OFFSET 0x4
#define IER_DLAB_UNDEFMASK 0xFFFFFF00
union ier_dlab_u {
    struct {
        unsigned int ie_rhr:1;              /* Interrupt Enable for Received Data Interrupt; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_thr:1;              /* Interrupt Enable for Transmitter Holding Register Empty interrupt; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_rxs:1;              /* Interrupt Enable for Receiver Line Status Interrupt; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_msi:1;              /* Interrupt Enable for Modem Status Interrupt; 0 = DISABLE; 1 = ENABLE NOTE: Modem Status Interrupt (IE_MSI) should not be enabled when the modem is used in 4-pin or 2-pin configurations. If enabled in these configurations phantom interrupts may be generated. */
        unsigned int ie_rx_timeout:1;       /* Interrupt Enable for Rx FIFO timeout 1 = Enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eord:1;             /* Interrupt Enable for End of Received Data 1 = Enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int n_a:2;                 /* Reserved */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_ier_dlab_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ier_dlab_u old_value_t = { .reg32 = value };
    const ier_dlab_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ie_rhr:1",
              "Interrupt Enable for Received Data Interrupt;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_rhr, new_value_t.ie_rhr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ie_thr:1",
              "Interrupt Enable for Transmitter Holding Register Empty interrupt;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_thr, new_value_t.ie_thr };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ie_rxs:1",
              "Interrupt Enable for Receiver Line Status Interrupt;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_rxs, new_value_t.ie_rxs };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ie_msi:1",
              "Interrupt Enable for Modem Status Interrupt;\n0 = DISABLE;\n1 = ENABLE NOTE: Modem Status Interrupt (IE_MSI) should not be enabled when the modem is used in 4-pin or 2-pin configurations. If enabled in these configurations phantom interrupts may be generated.",
              1, old_value_t.ie_msi, new_value_t.ie_msi };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ie_rx_timeout:1",
              "Interrupt Enable for Rx FIFO timeout\n1 = Enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_rx_timeout, new_value_t.ie_rx_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ie_eord:1",
              "Interrupt Enable for End of Received Data\n1 = Enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eord, new_value_t.ie_eord };
    m_bit_details_model.bits.append(entry);
    entry = { "06: n_a:2",
              "Reserved",
              2, old_value_t.n_a, new_value_t.n_a };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The IER and DLH registers occupy the same address space, selected by the LSR.DLAB bit. The Interrupt Enable Register (IER) is selected if the LSR.DLAB bit is clear. The Divisor Latch MSByte register (DLM) is selected if the LSR.DLAB bit is set. The DLM register holds the upper 8 bits of the 16-bit Baud Divisor (16x).\nUART Interrupt Enable por=0x00000000\nRX_TIMEOUT occurs when data has been sitting in the Rx FIFO for more than 4 character times without being read because there is not enough data to reach the trigger level.  Interrupt needed to handle this case so that all data is received in a timely manner. Note that this normally occurs at the end of an incoming data stream.\nEORD (End of Receive Data) Interrupt occurs when the receiver detects that data stops coming in for more than 4 character times. Useful for determining that the sending device has completed sending all its data. EORD timeout will not occur if the receiving data stream is stopped because of hardware handshaking. To clear the EORD timeout interrupt you must DISABLE the EORD interrupt enable (IE_EORD)\nInterrupt Enable and Divisor Latch MSByte Registers";
}

#define IIR_FCR_OFFSET 0x8
#define IIR_FCR_UNDEFMASK 0xFFFFFF00
union iir_fcr_u {
    struct {
        unsigned int is_sta_fcr_en_fifo:1;  /* Interrupt Pending if ZERO; 0 = INTR_PEND; 1 = NO_INTR_PEND; 1 = Enable the transmit and receive FIFO. This bit should be enabled; 0 = DISABLE; 1 = ENABLE */
        unsigned int is_pri0_rx_clr:1;      /* Encoded Interrupt ID Refer to IIR[3:0] table above; 0 = DISABLE; 1 = ENABLE; 1 = Clears the contents of the receive FIFO and resets its counter logic to 0 (the receive shift register is not cleared or altered). This bit returns to 0 after clearing the FIFOs; 0 = NO_CLEAR; 1 = CLEAR */
        unsigned int is_pri1_tx_clr:1;      /* Encoded Interrupt ID Refer to IIR[3:0] table above; 0 = DISABLE; 1 = ENABLE; 1 = Clears the contents of the transmit FIFO and resets its counter logic to 0 (the transmit shift register is not cleared or altered). This bit returns to 0 after clearing the FIFOs; 0 = NO_CLEAR; 1 = CLEAR */
        unsigned int is_pri2_dma:1;         /* Encoded Interrupt ID Refer to IIR[3:0] table above; 0 = DISABLE; 1 = ENABLE; 0:DMA_Mode_0 1:DMA_MODE_1; 0 = NO_CHANGE; 1 = CHANGE */
        unsigned int n_a_tx_trig:2;         /* Reserved; FIFO_COUNT_GREATER_12 deprecated 0 = FIFO_COUNT_GREATER_16 1 = FIFO_COUNT_GREATER_8 2 = FIFO_COUNT_GREATER_4 3 = FIFO_COUNT_GREATER_1 0 = FIFO_COUNT_GREATER_12 */
        unsigned int en_fifo_rx_trig:2;     /* FIFO Mode Status 0=16450 mode(no FIFO), 1 = 16550 mode (FIFO); 1 = MODE_16550; 0 = MODE_16450; FIFO_COUNT_GREATER_12 deprecated  0 = FIFO_COUNT_GREATER_1 1 = FIFO_COUNT_GREATER_4 2 = FIFO_COUNT_GREATER_8 3 = FIFO_COUNT_GREATER_16 3 = FIFO_COUNT_GREATER_12 */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_iir_fcr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const iir_fcr_u old_value_t = { .reg32 = value };
    const iir_fcr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: is_sta_fcr_en_fifo:1",
              "Interrupt Pending if ZERO;\n0 = INTR_PEND;\n1 = NO_INTR_PEND;\n1 = Enable the transmit and receive FIFO. This bit should be enabled;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.is_sta_fcr_en_fifo, new_value_t.is_sta_fcr_en_fifo };
    m_bit_details_model.bits.append(entry);
    entry = { "01: is_pri0_rx_clr:1",
              "Encoded Interrupt ID Refer to IIR[3:0] table above;\n0 = DISABLE;\n1 = ENABLE;\n1 = Clears the contents of the receive FIFO and resets its counter logic to 0 (the receive shift register is not cleared or altered). This bit returns to 0 after clearing the FIFOs;\n0 = NO_CLEAR;\n1 = CLEAR",
              1, old_value_t.is_pri0_rx_clr, new_value_t.is_pri0_rx_clr };
    m_bit_details_model.bits.append(entry);
    entry = { "02: is_pri1_tx_clr:1",
              "Encoded Interrupt ID Refer to IIR[3:0] table above;\n0 = DISABLE;\n1 = ENABLE;\n1 = Clears the contents of the transmit FIFO and resets its counter logic to 0 (the transmit shift register is not cleared or altered). This bit returns to 0 after clearing the FIFOs;\n0 = NO_CLEAR;\n1 = CLEAR",
              1, old_value_t.is_pri1_tx_clr, new_value_t.is_pri1_tx_clr };
    m_bit_details_model.bits.append(entry);
    entry = { "03: is_pri2_dma:1",
              "Encoded Interrupt ID Refer to IIR[3:0] table above;\n0 = DISABLE;\n1 = ENABLE; 0:DMA_Mode_0 1:DMA_MODE_1;\n0 = NO_CHANGE;\n1 = CHANGE",
              1, old_value_t.is_pri2_dma, new_value_t.is_pri2_dma };
    m_bit_details_model.bits.append(entry);
    entry = { "04: n_a_tx_trig:2",
              "Reserved; FIFO_COUNT_GREATER_12 deprecated\n0 = FIFO_COUNT_GREATER_16\n1 = FIFO_COUNT_GREATER_8\n2 = FIFO_COUNT_GREATER_4\n3 = FIFO_COUNT_GREATER_1\n0 = FIFO_COUNT_GREATER_12",
              2, old_value_t.n_a_tx_trig, new_value_t.n_a_tx_trig };
    m_bit_details_model.bits.append(entry);
    entry = { "06: en_fifo_rx_trig:2",
              "FIFO Mode Status\n0=16450 mode(no FIFO),\n1 = 16550 mode (FIFO);\n1 = MODE_16550;\n0 = MODE_16450; FIFO_COUNT_GREATER_12 deprecated \n0 = FIFO_COUNT_GREATER_1\n1 = FIFO_COUNT_GREATER_4\n2 = FIFO_COUNT_GREATER_8\n3 = FIFO_COUNT_GREATER_16\n3 = FIFO_COUNT_GREATER_12",
              2, old_value_t.en_fifo_rx_trig, new_value_t.en_fifo_rx_trig };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The FCR and IIR registers occupy the same address space. The FIFO Control Register (FCR) is Write-Only. The Interrupt Identification Register (IIR) is Read-Only\nUART FIFO Control Register por=0x00000000\nThe DMA can run in one of two modes:\n    * If Mode0 is selected (NO_CHANGE) the Rx DMA request will go active whenever the Rx FIFO is not empty.  Only single byte transactions can be performed in this mode.  If the FIFO is not enabled, Mode0 MUST be used.\n    * If Mode1 is selected (CHANGE) the Rx DMA request will go active whenever the Rx FIFO trigger level is reached.\nFor best performance, always enable the FIFO and select DMA Mode 1.\nFor RX_TRIG the FIFO_COUNT references the number of bytes in the receive FIFO\nFor TX_TRIG the FIFO_COUNT references the number of empty bytes in the transmit FIFO. For example, FIFO_COUNT_GREATER_16 means that there are at least 16 empty byte slots in the TX_FIFO\nUART Interrupt ID Register por=0x00000001\nThe Interrupt ID field indicates the current highest priority interrupt. If more than one interrupt is pending the one with the highest priority will be shown.\nThe table below shows the encoding. Priority flows from top (highest) to bottom (lowest).\nTable 72  Interrupt ID encoding\nIIR[3:0]\n Priority Level\n0001\n no interrupt\n0110\n Overrun Error, Parity Error, Framing Error, Break\n0100\n Receiver Data Available\n1100\n rx_timeout_intr\n1000\n eord_timeout_intr\n0010\n transmitter holding register empty\n0000\n modem_status interrupt\nUART FIFO Control and Interrupt Identification Registers";
}

#define LCR_OFFSET 0xC
#define LCR_UNDEFMASK 0xFFFFFF00
union lcr_u {
    struct {
        unsigned int wd_size:2;             /* 3=Word length of 8; 0 = WORD_LENGTH_5; 1 = WORD_LENGTH_6; 2 = WORD_LENGTH_7; 3 = WORD_LENGTH_8 */
        unsigned int stop:1;                /* 0 = Transmit 1 stop bit, 1 = Transmit 2 stop bits (receiver always checks for 1 stop bit); 0 = DISABLE; 1 = ENABLE */
        unsigned int par:1;                 /* 0 = No parity sent; 0 = NO_PARITY; 1 = PARITY */
        unsigned int even:1;                /* Even parity format. There will always be an even number of 1s in the binary representation (PAR = 1); 0 = DISABLE; 1 = ENABLE */
        unsigned int set_p:1;               /* Set (force) parity to value in LCR [4]; 0 = NO_PARITY; 1 = PARITY */
        unsigned int set_b:1;               /* Set BREAK condition -- Transmitter will send all zeroes to indicate BREAK; 0 = NO_BREAK; 1 = BREAK */
        unsigned int dlab:1;                /* Divisor Latch Access Bit (set to allow programming of the DLH, DLM Divisors); 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_lcr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const lcr_u old_value_t = { .reg32 = value };
    const lcr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wd_size:2",
              "3=Word length of 8;\n0 = WORD_LENGTH_5;\n1 = WORD_LENGTH_6;\n2 = WORD_LENGTH_7;\n3 = WORD_LENGTH_8",
              2, old_value_t.wd_size, new_value_t.wd_size };
    m_bit_details_model.bits.append(entry);
    entry = { "02: stop:1",
              "0 = Transmit 1 stop bit,\n1 = Transmit 2 stop bits (receiver always checks for 1 stop bit);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.stop, new_value_t.stop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: par:1",
              "0 = No parity sent;\n0 = NO_PARITY;\n1 = PARITY",
              1, old_value_t.par, new_value_t.par };
    m_bit_details_model.bits.append(entry);
    entry = { "04: even:1",
              "Even parity format. There will always be an even number of 1s in the binary representation (PAR = 1);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.even, new_value_t.even };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_p:1",
              "Set (force) parity to value in LCR [4];\n0 = NO_PARITY;\n1 = PARITY",
              1, old_value_t.set_p, new_value_t.set_p };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_b:1",
              "Set BREAK condition -- Transmitter will send all zeroes to indicate BREAK;\n0 = NO_BREAK;\n1 = BREAK",
              1, old_value_t.set_b, new_value_t.set_b };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dlab:1",
              "Divisor Latch Access Bit (set to allow programming of the DLH, DLM Divisors);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dlab, new_value_t.dlab };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "UART Line Control Register";
}

#define MCR_OFFSET 0x10
#define MCR_UNDEFMASK 0xFFFFFF00
union mcr_u {
    struct {
        unsigned int dtr:1;                 /* 1 = Force DTR to high; 0 = FORCE_DTR_HI; 1 = FORCE_DTR_LOW */
        unsigned int rts:1;                 /* 0 = Force RTS to high if RTS HW flow control not enabled; 0 = FORCE_RTS_HI; 1 = FORCE_RTS_LOW */
        unsigned int out1:1;                /* nOUT1 (Not Used); 0 = DISABLE; 1 = ENABLE */
        unsigned int out2:1;                /* nOUT2 (Not Used); 0 = DISABLE; 1 = ENABLE */
        unsigned int loopbk:1;              /* 1 = enable internal loop back of Serial Out to In; 0 = DISABLE; 1 = ENABLE */
        unsigned int cts_en:1;              /* 1 = Enable CTS Hardware Flow Control; 0 = DISABLE; 1 = ENABLE */
        unsigned int rts_en:1;              /* 1 = Enable RTS Hardware Flow Control; 0 = DISABLE; 1 = ENABLE */
        unsigned int n_a:1;                 /* Reserved */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_mcr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mcr_u old_value_t = { .reg32 = value };
    const mcr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dtr:1",
              "1 = Force DTR to high;\n0 = FORCE_DTR_HI;\n1 = FORCE_DTR_LOW",
              1, old_value_t.dtr, new_value_t.dtr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: rts:1",
              "0 = Force RTS to high if RTS HW flow control not enabled;\n0 = FORCE_RTS_HI;\n1 = FORCE_RTS_LOW",
              1, old_value_t.rts, new_value_t.rts };
    m_bit_details_model.bits.append(entry);
    entry = { "02: out1:1",
              "nOUT1 (Not Used);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.out1, new_value_t.out1 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: out2:1",
              "nOUT2 (Not Used);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.out2, new_value_t.out2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: loopbk:1",
              "1 = enable internal loop back of Serial Out to In;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.loopbk, new_value_t.loopbk };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cts_en:1",
              "1 = Enable CTS Hardware Flow Control;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cts_en, new_value_t.cts_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: rts_en:1",
              "1 = Enable RTS Hardware Flow Control;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.rts_en, new_value_t.rts_en };
    m_bit_details_model.bits.append(entry);
    entry = { "07: n_a:1",
              "Reserved",
              1, old_value_t.n_a, new_value_t.n_a };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The RTS and CTS pins are used for hardware handshaking with and external serial device. RTS (Request-To-Send) informs the device that the UART is ready to accept data. CTS (Clear-To-Send) comes from the RTS of the external device and informs us that it is OK to send data.\nThe RTS pin can be controlled manually with the RTS bit in the MCR, or automatically by setting the RTS_EN bit.\nIf RTS_EN is set, the RTS pin will automatically remove the Request-To-Send when the FIFO reaches the trigger level.\nIf the CTS_EN bit is set, the UART transmitter will stop transmitting when the Clear-To-Send input is taken away.\nUART Modem Control Register";
}

#define LSR_OFFSET 0x14
#define LSR_UNDEFMASK 0xFFFFFF00
union lsr_u {
    struct {
        unsigned int rdr:1;                 /* 1 = Receiver Data Ready (Data available to read); 0 = NO_DATA_IN_FIFO; 1 = DATA_IN_FIFO */
        unsigned int ovrf:1;                /* 1 = Receiver Overrun Error; 0 = NO_OVERRUN_ERROR; 1 = OVERRUN_ERROR */
        unsigned int perr:1;                /* 1 = Parity Error; 0 = NO_PARITY_ERR; 1 = PARITY_ERR */
        unsigned int ferr:1;                /* 1 = Framing Errpr; 0 = NO_FRAME_ERR; 1 = FRAME_ERR */
        unsigned int brk:1;                 /* 1 = BREAK condition detected on line; 0 = NO_BREAK; 1 = BREAK */
        unsigned int thre:1;                /* 1 = Transmit Holding Register is Empty -- OK to write data; 0 = FULL; 1 = EMPTY */
        unsigned int tmty:1;                /* Transmit Shift Reg empty status; 0 = NO_EMPTY; 1 = EMPTY */
        unsigned int fifoe:1;               /* 1 = Receive FIFO Error; 0 = NO_ERR; 1 = ERR */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_lsr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const lsr_u old_value_t = { .reg32 = value };
    const lsr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdr:1",
              "1 = Receiver Data Ready (Data available to read);\n0 = NO_DATA_IN_FIFO;\n1 = DATA_IN_FIFO",
              1, old_value_t.rdr, new_value_t.rdr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ovrf:1",
              "1 = Receiver Overrun Error;\n0 = NO_OVERRUN_ERROR;\n1 = OVERRUN_ERROR",
              1, old_value_t.ovrf, new_value_t.ovrf };
    m_bit_details_model.bits.append(entry);
    entry = { "02: perr:1",
              "1 = Parity Error;\n0 = NO_PARITY_ERR;\n1 = PARITY_ERR",
              1, old_value_t.perr, new_value_t.perr };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ferr:1",
              "1 = Framing Errpr;\n0 = NO_FRAME_ERR;\n1 = FRAME_ERR",
              1, old_value_t.ferr, new_value_t.ferr };
    m_bit_details_model.bits.append(entry);
    entry = { "04: brk:1",
              "1 = BREAK condition detected on line;\n0 = NO_BREAK;\n1 = BREAK",
              1, old_value_t.brk, new_value_t.brk };
    m_bit_details_model.bits.append(entry);
    entry = { "05: thre:1",
              "1 = Transmit Holding Register is Empty -- OK to write data;\n0 = FULL;\n1 = EMPTY",
              1, old_value_t.thre, new_value_t.thre };
    m_bit_details_model.bits.append(entry);
    entry = { "06: tmty:1",
              "Transmit Shift Reg empty status;\n0 = NO_EMPTY;\n1 = EMPTY",
              1, old_value_t.tmty, new_value_t.tmty };
    m_bit_details_model.bits.append(entry);
    entry = { "07: fifoe:1",
              "1 = Receive FIFO Error;\n0 = NO_ERR;\n1 = ERR",
              1, old_value_t.fifoe, new_value_t.fifoe };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "UART Line Status Register";
}

#define MSR_OFFSET 0x18
#define MSR_UNDEFMASK 0xFFFFFF00
union msr_u {
    struct {
        unsigned int dcts:1;                /* Change (Delta) in CTS state detected; 0 = DISABLE; 1 = ENABLE */
        unsigned int ddsr:1;                /* Change (Delta) in DSR state detected; 0 = DISABLE; 1 = ENABLE */
        unsigned int dri:1;                 /* Change (Delta) in RI state detected; 0 = DISABLE; 1 = ENABLE */
        unsigned int dcd:1;                 /* Change (Delta) in CD state detected; 0 = DISABLE; 1 = ENABLE */
        unsigned int cts:1;                 /* State of Clear to send pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int dsr:1;                 /* State of Data set ready pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int ri:1;                  /* State of Ring Indicator pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int cd:1;                  /* State of Carrier detect pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_msr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const msr_u old_value_t = { .reg32 = value };
    const msr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dcts:1",
              "Change (Delta) in CTS state detected;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dcts, new_value_t.dcts };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ddsr:1",
              "Change (Delta) in DSR state detected;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ddsr, new_value_t.ddsr };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dri:1",
              "Change (Delta) in RI state detected;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dri, new_value_t.dri };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dcd:1",
              "Change (Delta) in CD state detected;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dcd, new_value_t.dcd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cts:1",
              "State of Clear to send pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cts, new_value_t.cts };
    m_bit_details_model.bits.append(entry);
    entry = { "05: dsr:1",
              "State of Data set ready pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dsr, new_value_t.dsr };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ri:1",
              "State of Ring Indicator pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ri, new_value_t.ri };
    m_bit_details_model.bits.append(entry);
    entry = { "07: cd:1",
              "State of Carrier detect pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cd, new_value_t.cd };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "UART Modem Status Register";
}

#define SPR_OFFSET 0x1C
#define SPR_UNDEFMASK 0xFFFFFF00
union spr_u {
    struct {
        unsigned int spr_a:8;               /* Scratchpad register (not used internally) */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_spr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const spr_u old_value_t = { .reg32 = value };
    const spr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spr_a:8",
              "Scratchpad register (not used internally)",
              8, old_value_t.spr_a, new_value_t.spr_a };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "UART Scratch Pad Register";
}

#define IRDA_CSR_OFFSET 0x20
#define IRDA_CSR_UNDEFMASK 0xFFFFFF00
union irda_csr_u {
    struct {
        unsigned int invert_rxd:1;          /* Inverts the normally inactive high RXD pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int invert_txd:1;          /* Inverts the normally inactive high TXD pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int invert_cts:1;          /* Inverts the normally inactive high nCTS pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int invert_rts:1;          /* Inverts the normally inactive high nRTS pin; 0 = DISABLE; 1 = ENABLE */
        unsigned int n_a:2;                 /* Reserved = 0 */
        unsigned int pwt_a:1;               /* 0=3/16th Baud Pulse, 1=4/16; 0 = BAUD_PULSE_3_14; 1 = BAUD_PULSE_4_14 */
        unsigned int sir_a:1;               /* 1 = Enable SIR coder 0 = Disable SIR coder; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void UartDev::fill_irda_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irda_csr_u old_value_t = { .reg32 = value };
    const irda_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: invert_rxd:1",
              "Inverts the normally inactive high RXD pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.invert_rxd, new_value_t.invert_rxd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: invert_txd:1",
              "Inverts the normally inactive high TXD pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.invert_txd, new_value_t.invert_txd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: invert_cts:1",
              "Inverts the normally inactive high nCTS pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.invert_cts, new_value_t.invert_cts };
    m_bit_details_model.bits.append(entry);
    entry = { "03: invert_rts:1",
              "Inverts the normally inactive high nRTS pin;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.invert_rts, new_value_t.invert_rts };
    m_bit_details_model.bits.append(entry);
    entry = { "04: n_a:2",
              "Reserved = 0",
              2, old_value_t.n_a, new_value_t.n_a };
    m_bit_details_model.bits.append(entry);
    entry = { "06: pwt_a:1",
              "0=3/16th Baud Pulse,\n1=4/16;\n0 = BAUD_PULSE_3_14;\n1 = BAUD_PULSE_4_14",
              1, old_value_t.pwt_a, new_value_t.pwt_a };
    m_bit_details_model.bits.append(entry);
    entry = { "07: sir_a:1",
              "1 = Enable SIR coder\n0 = Disable SIR coder;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.sir_a, new_value_t.sir_a };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Bits [7:6] control the InfraRed (SIR) encoding. If enabled each zero bit sent will be transmitted as a short IR pulse.  No pulse is sent during idle or '1' data bits. The IR pulse can be either 3/16 or 4/16 of a normal bit time.\nThe low 4 bits control signal polarity and apply whether or not SIR coding is enabled.\nUART IrDA Pulse Coding CSR Register";
}

#define ASR_OFFSET 0x3C
#define ASR_UNDEFMASK 0x00000000
union asr_u {
    struct {
        unsigned int rx_rate_sense_l:8;     /* Shows the bits[7:0] of the count of clock edges between two successive clock edges */
        unsigned int rx_rate_sense_h:8;     /* Shows the bits [15:8] of the count of clock edges between two successive clock edges */
        unsigned int n_a:14;                /* Reserved = 0 */
        unsigned int busy:1;                /* This bit is set when there is a write to ASR and is reset when the controller finishes counting the clock edges between two successive clock edges; 0 = NO_BUSY; 1 = BUSY */
        unsigned int valid:1;               /* This bit is set when the controller finishes counting the clocks between two successive clock edges after there is a write to ASR with dont care data; 0 = UN_SET; 1 = SET */
    };

    u_int32_t reg32;
};

void UartDev::fill_asr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const asr_u old_value_t = { .reg32 = value };
    const asr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rx_rate_sense_l:8",
              "Shows the bits[7:0] of the count of clock edges between two successive clock edges",
              8, old_value_t.rx_rate_sense_l, new_value_t.rx_rate_sense_l };
    m_bit_details_model.bits.append(entry);
    entry = { "08: rx_rate_sense_h:8",
              "Shows the bits [15:8] of the count of clock edges between two successive clock edges",
              8, old_value_t.rx_rate_sense_h, new_value_t.rx_rate_sense_h };
    m_bit_details_model.bits.append(entry);
    entry = { "16: n_a:14",
              "Reserved = 0",
              14, old_value_t.n_a, new_value_t.n_a };
    m_bit_details_model.bits.append(entry);
    entry = { "30: busy:1",
              "This bit is set when there is a write to ASR and is reset when the controller finishes counting the clock edges between two successive clock edges;\n0 = NO_BUSY;\n1 = BUSY",
              1, old_value_t.busy, new_value_t.busy };
    m_bit_details_model.bits.append(entry);
    entry = { "31: valid:1",
              "This bit is set when the controller finishes counting the clocks between two successive clock edges after there is a write to ASR with dont care data;\n0 = UN_SET;\n1 = SET",
              1, old_value_t.valid, new_value_t.valid };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The UART has auto-Baud sensing logic which can measure the width of the start bit of incoming data to determine baud rate. For this to work the incoming character must have it's LSB set.   A <cr> works well (0x0d). The logic will use the UART device clock to count how wide the start pulse is and the BUSY bit will be set when the sensing is complete.  The value in {RX_RATE_SENSE_H,RX_RATE_SENSE_L} should be divided by 16 with Round-to-Nearest, and the resulting value loaded into the DLM,DLL register pair to set the Baud Clock to 16X the Baud Rate.\nUART Auto Sense Baud Register";
}

bool UartDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case THR_DLAB_OFFSET:
    case IER_DLAB_OFFSET:
    case IIR_FCR_OFFSET:
    case LCR_OFFSET:
    case MCR_OFFSET:
    case LSR_OFFSET:
    case MSR_OFFSET:
    case SPR_OFFSET:
    case IRDA_CSR_OFFSET:
    case ASR_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool UartDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case THR_DLAB_OFFSET:
        if ((value ^ new_value) & THR_DLAB_UNDEFMASK)
            return true;
        break;
    case IER_DLAB_OFFSET:
        if ((value ^ new_value) & IER_DLAB_UNDEFMASK)
            return true;
        break;
    case IIR_FCR_OFFSET:
        if ((value ^ new_value) & IIR_FCR_UNDEFMASK)
            return true;
        break;
    case LCR_OFFSET:
        if ((value ^ new_value) & LCR_UNDEFMASK)
            return true;
        break;
    case MCR_OFFSET:
        if ((value ^ new_value) & MCR_UNDEFMASK)
            return true;
        break;
    case LSR_OFFSET:
        if ((value ^ new_value) & LSR_UNDEFMASK)
            return true;
        break;
    case MSR_OFFSET:
        if ((value ^ new_value) & MSR_UNDEFMASK)
            return true;
        break;
    case SPR_OFFSET:
        if ((value ^ new_value) & SPR_UNDEFMASK)
            return true;
        break;
    case IRDA_CSR_OFFSET:
        if ((value ^ new_value) & IRDA_CSR_UNDEFMASK)
            return true;
        break;
    case ASR_OFFSET:
        if ((value ^ new_value) & ASR_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString UartDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case THR_DLAB_OFFSET:
        return QString("THR_DLAB");
    case IER_DLAB_OFFSET:
        return QString("IER_DLAB");
    case IIR_FCR_OFFSET:
        return QString("IIR_FCR");
    case LCR_OFFSET:
        return QString("LCR");
    case MCR_OFFSET:
        return QString("MCR");
    case LSR_OFFSET:
        return QString("LSR");
    case MSR_OFFSET:
        return QString("MSR");
    case SPR_OFFSET:
        return QString("SPR");
    case IRDA_CSR_OFFSET:
        return QString("IRDA_CSR");
    case ASR_OFFSET:
        return QString("ASR");

    default:
        break;
    }

    qDebug() << QString().sprintf("UART: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void UartDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case THR_DLAB_OFFSET:
        fill_thr_dlab_details(value, new_value);
        break;
    case IER_DLAB_OFFSET:
        fill_ier_dlab_details(value, new_value);
        break;
    case IIR_FCR_OFFSET:
        fill_iir_fcr_details(value, new_value);
        break;
    case LCR_OFFSET:
        fill_lcr_details(value, new_value);
        break;
    case MCR_OFFSET:
        fill_mcr_details(value, new_value);
        break;
    case LSR_OFFSET:
        fill_lsr_details(value, new_value);
        break;
    case MSR_OFFSET:
        fill_msr_details(value, new_value);
        break;
    case SPR_OFFSET:
        fill_spr_details(value, new_value);
        break;
    case IRDA_CSR_OFFSET:
        fill_irda_csr_details(value, new_value);
        break;
    case ASR_OFFSET:
        fill_asr_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
