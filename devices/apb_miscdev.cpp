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

#include "apb_miscdev.h"

#include <QDebug>

Apb_miscDev::Apb_miscDev(QObject *parent) :
    Device(parent)
{
}

#define PP_STRAPPING_OPT_A_OFFSET 0x8
#define PP_STRAPPING_OPT_A_UNDEFMASK 0xC03FFE0E
union pp_strapping_opt_a_u {
    struct {
        unsigned int nor_width:1;           /* 0 = IS16BIT; 1 = IS8BIT */
        unsigned int undefined_bits_1_3:3;
        unsigned int ram_code:4;            /* read at power-on reset time from GMI_AD[7:4] strap pads. In emulation (HIDREV_MAJORREV==0), this field indicates the RAM type connected. For QT (HIDREV_MINORREV==0): 0=SIM, 1=DDR, 2=DDR2, 3=LPDDR2 For FPGA (HIDREV_MINORREV==1): 0=SIM, 1=DDR, 2=DDR2, 3=LPDDR2 */
        unsigned int mio_width:1;           /* 0 = RSVD1 1 = RSVD2 */
        unsigned int undefined_bits_9_21:13;
        unsigned int arm_jtag:2;            /* read at power-on reset time from {GMI_CLK, GMI_ADV_N} strap pads 00=Serial_JTAG, 01=CPU_only, 10=COP_only, 11=Serial_JTAG (same as 00 case); 0 = SERIAL; 1 = CPU; 2 = COP; 3 = SERIAL_ALT */
        unsigned int boot_src_nor_boot:1;   /* read at power-on reset time from GMI_HIOW strap pad; 0 = IROM; 1 = NOR */
        unsigned int boot_src_usb_recovery_mode:1;/* read at power-on reset time from GMI_HIOR strap pad 0 = DISABLED 1 = ENABLED */
        unsigned int boot_select:4;         /* read at power-on reset time from GMI_AD[15:12] strap pads */
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_strapping_opt_a_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_strapping_opt_a_u old_value_t = { .reg32 = value };
    const pp_strapping_opt_a_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: nor_width:1",
              "0 = IS16BIT;\n1 = IS8BIT",
              1, old_value_t.nor_width, new_value_t.nor_width };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_3:3", "", 3, old_value_t.undefined_bits_1_3, new_value_t.undefined_bits_1_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ram_code:4",
              "read at power-on reset time from GMI_AD[7:4] strap pads. In emulation (HIDREV_MAJORREV==0), this field indicates the RAM type connected. For QT (HIDREV_MINORREV==0):\n0=SIM,\n1=DDR,\n2=DDR2,\n3=LPDDR2 For FPGA (HIDREV_MINORREV==1):\n0=SIM,\n1=DDR,\n2=DDR2,\n3=LPDDR2",
              4, old_value_t.ram_code, new_value_t.ram_code };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mio_width:1",
              "0 = RSVD1\n1 = RSVD2",
              1, old_value_t.mio_width, new_value_t.mio_width };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_21:13", "", 13, old_value_t.undefined_bits_9_21, new_value_t.undefined_bits_9_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: arm_jtag:2",
              "read at power-on reset time from {GMI_CLK, GMI_ADV_N} strap pads\n00=Serial_JTAG,\n01=CPU_only,\n10=COP_only,\n11=Serial_JTAG (same as 00 case);\n0 = SERIAL;\n1 = CPU;\n2 = COP;\n3 = SERIAL_ALT",
              2, old_value_t.arm_jtag, new_value_t.arm_jtag };
    m_bit_details_model.bits.append(entry);
    entry = { "24: boot_src_nor_boot:1",
              "read at power-on reset time from GMI_HIOW strap pad;\n0 = IROM;\n1 = NOR",
              1, old_value_t.boot_src_nor_boot, new_value_t.boot_src_nor_boot };
    m_bit_details_model.bits.append(entry);
    entry = { "25: boot_src_usb_recovery_mode:1",
              "read at power-on reset time from GMI_HIOR strap pad\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.boot_src_usb_recovery_mode, new_value_t.boot_src_usb_recovery_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "26: boot_select:4",
              "read at power-on reset time from GMI_AD[15:12] strap pads",
              4, old_value_t.boot_select, new_value_t.boot_select };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Strapping Options Register";
}

#define PP_TRISTATE_REG_A_OFFSET 0x14
#define PP_TRISTATE_REG_A_UNDEFMASK 0x00000000
union pp_tristate_reg_a_u {
    struct {
        unsigned int z_ata:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_atb:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_atc:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_atd:1;               /* 0 = NORMAL; 1 = TRI TATE */
        unsigned int z_cdev1:1;             /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_cdev2:1;             /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_csus:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dap1:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dap2:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dap3:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dap4:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dta:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dtb:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dtc:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dtd:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dte:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_gpu:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_gpv:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_i2cp:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_irtx:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_irrx:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_kbcb:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_kbca:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_pmc:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_pta:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_rm:1;                /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_kbce:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_kbcf:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_gma:1;               /* 0 = NORMAL 1 = TRISTATE */
        unsigned int z_gmc:1;               /* 0 = NORMAL 1 = TRISTATE */
        unsigned int z_sdio1:1;             /* 0 = NORMAL 1 = TRISTATE */
        unsigned int z_owc:1;               /* 0 = NORMAL 1 = TRISTATE */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_tristate_reg_a_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_tristate_reg_a_u old_value_t = { .reg32 = value };
    const pp_tristate_reg_a_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: z_ata:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ata, new_value_t.z_ata };
    m_bit_details_model.bits.append(entry);
    entry = { "01: z_atb:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_atb, new_value_t.z_atb };
    m_bit_details_model.bits.append(entry);
    entry = { "02: z_atc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_atc, new_value_t.z_atc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: z_atd:1",
              "0 = NORMAL;\n1 = TRI TATE",
              1, old_value_t.z_atd, new_value_t.z_atd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: z_cdev1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_cdev1, new_value_t.z_cdev1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: z_cdev2:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_cdev2, new_value_t.z_cdev2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: z_csus:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_csus, new_value_t.z_csus };
    m_bit_details_model.bits.append(entry);
    entry = { "07: z_dap1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dap1, new_value_t.z_dap1 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: z_dap2:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dap2, new_value_t.z_dap2 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: z_dap3:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dap3, new_value_t.z_dap3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: z_dap4:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dap4, new_value_t.z_dap4 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: z_dta:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dta, new_value_t.z_dta };
    m_bit_details_model.bits.append(entry);
    entry = { "12: z_dtb:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dtb, new_value_t.z_dtb };
    m_bit_details_model.bits.append(entry);
    entry = { "13: z_dtc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dtc, new_value_t.z_dtc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: z_dtd:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dtd, new_value_t.z_dtd };
    m_bit_details_model.bits.append(entry);
    entry = { "15: z_dte:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dte, new_value_t.z_dte };
    m_bit_details_model.bits.append(entry);
    entry = { "16: z_gpu:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_gpu, new_value_t.z_gpu };
    m_bit_details_model.bits.append(entry);
    entry = { "17: z_gpv:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_gpv, new_value_t.z_gpv };
    m_bit_details_model.bits.append(entry);
    entry = { "18: z_i2cp:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_i2cp, new_value_t.z_i2cp };
    m_bit_details_model.bits.append(entry);
    entry = { "19: z_irtx:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_irtx, new_value_t.z_irtx };
    m_bit_details_model.bits.append(entry);
    entry = { "20: z_irrx:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_irrx, new_value_t.z_irrx };
    m_bit_details_model.bits.append(entry);
    entry = { "21: z_kbcb:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_kbcb, new_value_t.z_kbcb };
    m_bit_details_model.bits.append(entry);
    entry = { "22: z_kbca:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_kbca, new_value_t.z_kbca };
    m_bit_details_model.bits.append(entry);
    entry = { "23: z_pmc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_pmc, new_value_t.z_pmc };
    m_bit_details_model.bits.append(entry);
    entry = { "24: z_pta:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_pta, new_value_t.z_pta };
    m_bit_details_model.bits.append(entry);
    entry = { "25: z_rm:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_rm, new_value_t.z_rm };
    m_bit_details_model.bits.append(entry);
    entry = { "26: z_kbce:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_kbce, new_value_t.z_kbce };
    m_bit_details_model.bits.append(entry);
    entry = { "27: z_kbcf:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_kbcf, new_value_t.z_kbcf };
    m_bit_details_model.bits.append(entry);
    entry = { "28: z_gma:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_gma, new_value_t.z_gma };
    m_bit_details_model.bits.append(entry);
    entry = { "29: z_gmc:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_gmc, new_value_t.z_gmc };
    m_bit_details_model.bits.append(entry);
    entry = { "30: z_sdio1:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_sdio1, new_value_t.z_sdio1 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: z_owc:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_owc, new_value_t.z_owc };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "These registers are used to control the PAD behavior.  The TRISTATE registers should be programmed before tri-state pads which are not used for Power consumptions.  Z_ indicates the enable for TRISTATING the pads, Enum TRISTATE indicates Outputs are Tristate, and NORMAL indicates they are Not Tristated.\n TRI STATES THE Output Pads when the Tristate Bit is enabled. This is used by SW for Power Consumption.\n 0 = Normal; 1 = tristate Output.\nTRI_STATE Configuration Register";
}

#define PP_TRISTATE_REG_B_OFFSET 0x18
#define PP_TRISTATE_REG_B_UNDEFMASK 0x19000010
union pp_tristate_reg_b_u {
    struct {
        unsigned int z_gme:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_sdc:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_sdd:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_slxa:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int undefined_bit_4:1;
        unsigned int z_slxc:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_slxd:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_slxk:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spdi:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spdo:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spia:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spib:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spic:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spid:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spie:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spif:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spig:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_spih:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_uaa:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_uab:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_uac:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_uad:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_uca:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ucb:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int undefined_bit_24:1;
        unsigned int z_ate:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_kbcc:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int undefined_bits_27_28:2;
        unsigned int z_gmb:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_gmd:1;               /* 0 = NORMAL 1 = TRISTATE */
        unsigned int z_ddc:1;               /* 0 = NORMAL 1 = TRISTATE */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_tristate_reg_b_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_tristate_reg_b_u old_value_t = { .reg32 = value };
    const pp_tristate_reg_b_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: z_gme:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_gme, new_value_t.z_gme };
    m_bit_details_model.bits.append(entry);
    entry = { "01: z_sdc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_sdc, new_value_t.z_sdc };
    m_bit_details_model.bits.append(entry);
    entry = { "02: z_sdd:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_sdd, new_value_t.z_sdd };
    m_bit_details_model.bits.append(entry);
    entry = { "03: z_slxa:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_slxa, new_value_t.z_slxa };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bit_4:1", "", 1, old_value_t.undefined_bit_4, new_value_t.undefined_bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: z_slxc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_slxc, new_value_t.z_slxc };
    m_bit_details_model.bits.append(entry);
    entry = { "06: z_slxd:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_slxd, new_value_t.z_slxd };
    m_bit_details_model.bits.append(entry);
    entry = { "07: z_slxk:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_slxk, new_value_t.z_slxk };
    m_bit_details_model.bits.append(entry);
    entry = { "08: z_spdi:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spdi, new_value_t.z_spdi };
    m_bit_details_model.bits.append(entry);
    entry = { "09: z_spdo:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spdo, new_value_t.z_spdo };
    m_bit_details_model.bits.append(entry);
    entry = { "10: z_spia:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spia, new_value_t.z_spia };
    m_bit_details_model.bits.append(entry);
    entry = { "11: z_spib:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spib, new_value_t.z_spib };
    m_bit_details_model.bits.append(entry);
    entry = { "12: z_spic:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spic, new_value_t.z_spic };
    m_bit_details_model.bits.append(entry);
    entry = { "13: z_spid:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spid, new_value_t.z_spid };
    m_bit_details_model.bits.append(entry);
    entry = { "14: z_spie:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spie, new_value_t.z_spie };
    m_bit_details_model.bits.append(entry);
    entry = { "15: z_spif:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spif, new_value_t.z_spif };
    m_bit_details_model.bits.append(entry);
    entry = { "16: z_spig:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spig, new_value_t.z_spig };
    m_bit_details_model.bits.append(entry);
    entry = { "17: z_spih:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_spih, new_value_t.z_spih };
    m_bit_details_model.bits.append(entry);
    entry = { "18: z_uaa:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_uaa, new_value_t.z_uaa };
    m_bit_details_model.bits.append(entry);
    entry = { "19: z_uab:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_uab, new_value_t.z_uab };
    m_bit_details_model.bits.append(entry);
    entry = { "20: z_uac:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_uac, new_value_t.z_uac };
    m_bit_details_model.bits.append(entry);
    entry = { "21: z_uad:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_uad, new_value_t.z_uad };
    m_bit_details_model.bits.append(entry);
    entry = { "22: z_uca:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_uca, new_value_t.z_uca };
    m_bit_details_model.bits.append(entry);
    entry = { "23: z_ucb:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ucb, new_value_t.z_ucb };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: z_ate:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ate, new_value_t.z_ate };
    m_bit_details_model.bits.append(entry);
    entry = { "26: z_kbcc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_kbcc, new_value_t.z_kbcc };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bits_27_28:2", "", 2, old_value_t.undefined_bits_27_28, new_value_t.undefined_bits_27_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: z_gmb:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_gmb, new_value_t.z_gmb };
    m_bit_details_model.bits.append(entry);
    entry = { "30: z_gmd:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_gmd, new_value_t.z_gmd };
    m_bit_details_model.bits.append(entry);
    entry = { "31: z_ddc:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_ddc, new_value_t.z_ddc };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "These registers are used to control the PAD behavior.  The TRISTATE registers should be programmed before tri-state pads which are not used for Power consumptions.  Z_ indicates the enable for TRISTATING the pads, Enum TRISTATE indicates Outputs are Tristate, and NORMAL indicates they are Not Tristated.\nTRI STATES THE Output Pads when the Tristate Bit is enabled. This is used by SW for Power Consumption.\nTRI_STATE Configuration Register";
}

#define PP_TRISTATE_REG_C_OFFSET 0x1C
#define PP_TRISTATE_REG_C_UNDEFMASK 0x00000000
union pp_tristate_reg_c_u {
    struct {
        unsigned int z_ld0:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld1:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld2:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld3:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld4:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld5:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld6:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld7:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld8:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld9:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld10:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld11:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld12:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld13:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld14:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld15:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld16:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ld17:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lhp0:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lhp1:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lhp2:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lvp0:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lvp1:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_hdint:1;             /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lm0:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lm1:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lvs:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lsc0:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lsc1:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lsck:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ldc:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lcsn:1;              /* 0 = NORMAL; 1 = TRISTATE */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_tristate_reg_c_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_tristate_reg_c_u old_value_t = { .reg32 = value };
    const pp_tristate_reg_c_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: z_ld0:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld0, new_value_t.z_ld0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: z_ld1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld1, new_value_t.z_ld1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: z_ld2:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld2, new_value_t.z_ld2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: z_ld3:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld3, new_value_t.z_ld3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: z_ld4:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld4, new_value_t.z_ld4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: z_ld5:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld5, new_value_t.z_ld5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: z_ld6:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld6, new_value_t.z_ld6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: z_ld7:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld7, new_value_t.z_ld7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: z_ld8:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld8, new_value_t.z_ld8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: z_ld9:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld9, new_value_t.z_ld9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: z_ld10:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld10, new_value_t.z_ld10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: z_ld11:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld11, new_value_t.z_ld11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: z_ld12:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld12, new_value_t.z_ld12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: z_ld13:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld13, new_value_t.z_ld13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: z_ld14:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld14, new_value_t.z_ld14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: z_ld15:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld15, new_value_t.z_ld15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: z_ld16:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld16, new_value_t.z_ld16 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: z_ld17:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ld17, new_value_t.z_ld17 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: z_lhp0:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lhp0, new_value_t.z_lhp0 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: z_lhp1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lhp1, new_value_t.z_lhp1 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: z_lhp2:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lhp2, new_value_t.z_lhp2 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: z_lvp0:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lvp0, new_value_t.z_lvp0 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: z_lvp1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lvp1, new_value_t.z_lvp1 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: z_hdint:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_hdint, new_value_t.z_hdint };
    m_bit_details_model.bits.append(entry);
    entry = { "24: z_lm0:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lm0, new_value_t.z_lm0 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: z_lm1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lm1, new_value_t.z_lm1 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: z_lvs:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lvs, new_value_t.z_lvs };
    m_bit_details_model.bits.append(entry);
    entry = { "27: z_lsc0:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lsc0, new_value_t.z_lsc0 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: z_lsc1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lsc1, new_value_t.z_lsc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: z_lsck:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lsck, new_value_t.z_lsck };
    m_bit_details_model.bits.append(entry);
    entry = { "30: z_ldc:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ldc, new_value_t.z_ldc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: z_lcsn:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lcsn, new_value_t.z_lcsn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "These registers are used to control the PAD behavior.  The TRISTATE registers should be programmed before tri-state pads which are not used for Power consumptions.  Z_ indicates the enable for TRISTATING the pads, Enum TRISTATE indicates Outputs are Tristate, and NORMAL indicates they are Not Tristated.\nTRI STATES THE Output Pads when the Tristate Bit is enabled. This is used by SW for Power Consumption.\nTRI_STATE Configuration Register";
}

#define PP_TRISTATE_REG_D_OFFSET 0x20
#define PP_TRISTATE_REG_D_UNDEFMASK 0xFFFF0200
union pp_tristate_reg_d_u {
    struct {
        unsigned int z_lspi:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lsda:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lsdi:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lpw0:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lpw1:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lpw2:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_ldi:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lhs:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_lpp:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int undefined_bit_9:1;
        unsigned int z_kbcd:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_gpu7:1;              /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_dtf:1;               /* 0 = NORMAL; 1 = TRISTATE */
        unsigned int z_uda:1;               /* 0 = NORMAL 1 = TRISTATE */
        unsigned int z_crtp:1;              /* 0 = NORMAL 1 = TRISTATE */
        unsigned int z_sdb:1;               /* 0 = NORMAL 1 = TRISTATE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_tristate_reg_d_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_tristate_reg_d_u old_value_t = { .reg32 = value };
    const pp_tristate_reg_d_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: z_lspi:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lspi, new_value_t.z_lspi };
    m_bit_details_model.bits.append(entry);
    entry = { "01: z_lsda:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lsda, new_value_t.z_lsda };
    m_bit_details_model.bits.append(entry);
    entry = { "02: z_lsdi:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lsdi, new_value_t.z_lsdi };
    m_bit_details_model.bits.append(entry);
    entry = { "03: z_lpw0:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lpw0, new_value_t.z_lpw0 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: z_lpw1:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lpw1, new_value_t.z_lpw1 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: z_lpw2:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lpw2, new_value_t.z_lpw2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: z_ldi:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_ldi, new_value_t.z_ldi };
    m_bit_details_model.bits.append(entry);
    entry = { "07: z_lhs:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lhs, new_value_t.z_lhs };
    m_bit_details_model.bits.append(entry);
    entry = { "08: z_lpp:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_lpp, new_value_t.z_lpp };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bit_9:1", "", 1, old_value_t.undefined_bit_9, new_value_t.undefined_bit_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: z_kbcd:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_kbcd, new_value_t.z_kbcd };
    m_bit_details_model.bits.append(entry);
    entry = { "11: z_gpu7:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_gpu7, new_value_t.z_gpu7 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: z_dtf:1",
              "0 = NORMAL;\n1 = TRISTATE",
              1, old_value_t.z_dtf, new_value_t.z_dtf };
    m_bit_details_model.bits.append(entry);
    entry = { "13: z_uda:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_uda, new_value_t.z_uda };
    m_bit_details_model.bits.append(entry);
    entry = { "14: z_crtp:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_crtp, new_value_t.z_crtp };
    m_bit_details_model.bits.append(entry);
    entry = { "15: z_sdb:1",
              "0 = NORMAL\n1 = TRISTATE",
              1, old_value_t.z_sdb, new_value_t.z_sdb };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "These registers are used to control the PAD behavior.  The TRISTATE registers should be programmed before tri-state pads which are not used for Power consumptions.\nZ_ indicates the enable for TRISTATING the pads, Enum TRISTATE indicates Outputs are Tristate, and NORMAL indicates they are Not Tristated.\nTRI STATES THE Output Pads when the Tristate Bit is enabled. This is used by SW for Power Consumption.\nTRI_STATE Configuration Register";
}

#define PP_CONFIG_CTL_OFFSET 0x24
#define PP_CONFIG_CTL_UNDEFMASK 0xFFFFFF3F
union pp_config_ctl_u {
    struct {
        unsigned int undefined_bits_0_5:6;
        unsigned int jtag:1;                /* 0 = Disable Debug ; 1 = Enable JTAG DBGEN; 0 = DISABLE; 1 = ENABLE */
        unsigned int tbe:1;                 /* 0 = Disable ; 1 = Enable RTCK Daisy chaining; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_config_ctl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_config_ctl_u old_value_t = { .reg32 = value };
    const pp_config_ctl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_5:6", "", 6, old_value_t.undefined_bits_0_5, new_value_t.undefined_bits_0_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: jtag:1",
              "0 = Disable Debug ;\n1 = Enable JTAG DBGEN;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.jtag, new_value_t.jtag };
    m_bit_details_model.bits.append(entry);
    entry = { "07: tbe:1",
              "0 = Disable ;\n1 = Enable RTCK Daisy chaining;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.tbe, new_value_t.tbe };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Configuration Control Register";
}

#define PP_MISC_USB_OTG_OFFSET 0x28
#define PP_MISC_USB_OTG_UNDEFMASK 0x3C000000
union pp_misc_usb_otg_u {
    struct {
        unsigned int sus_pol:1;             /* Polarity of the suspend signal going to USB PHY Software should not change this. 0 = ACTIVE_LOW 1 = ACTIVE_HIGH */
        unsigned int staticgpi:1;           /* Static General purpose input coming from ID pin 0 = UNSET 1 = SET */
        unsigned int suspended:1;           /* USB PHY suspend status This bit is set to 1 whenever USB is suspended and the PHY clock isn’t available. NOTE: Software should not access any registers in USB controller when this bit is set. 0 = UNSET 1 = SET */
        unsigned int sw_otg_id_en:1;        /* Enable Software Controlled OTG_ID If using a GPIO for OTG_ID signal, then software can set this to 1 and write the value from the GPIO to the SW_OTG_ID bit in this register. This field is the same as the field ID_SW_EN in register USB_PHY_VBUS_WAKEUP_ID. 0 = DISABLE 1 = ENABLE */
        unsigned int otg_id:1;              /* Real OTG_ID status from the USB PHY. This field is the same as the field ID_STS in register USB_PHY_VBUS_WAKEUP_ID. 0 = UNSET 1 = SET */
        unsigned int lpbk_en:1;             /* Loopback enable Not for normal software use 0 = DISABLE 1 = ENABLE */
        unsigned int vbus_chg_det:1;        /* VBUS change detect. This bit is set whenever a change in A_SESS_VLD is detected. Software can read the status of A_SESS_VLD from A_SESS_VLD_STS2 bit. This field is the same as the field A_SESS_VLD_CHG_DET in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int pclkvld:1;             /* PHY clock valid status. This bit is set whenever PHY clock becomes valid. It is cleared whenever PHY clock stops. 0 = UNSET 1 = SET */
        unsigned int wk_rsm_en:1;           /* Wake on resume enable. If this bit is enabled, USB PHY will wake up from suspend whenever resume/reset signaling is detected on USB. 0 = DISABLE 1 = ENABLE */
        unsigned int rsm_ie:1;              /* Resume/Clock valid interrupt enable. If this bit is enabled, interrupt is generated whenever PHY clock becomes valid. 0 = DISABLE 1 = ENABLE */
        unsigned int rsm_vbus_chg:1;        /* Wake/resume on VBUS change detect. If enabled, the USB PHY will wake up whenever a change in A_SESS_VLD is detected. This should be set only when USB PHY is already suspended. 0 = DISABLE 1 = ENABLE */
        unsigned int susp_clr:1;            /* Suspend Clear Software must write a 1 to this bit to bring the PHY out of suspend mode. This is used when the software stops the PHY clock during suspend and then wants to initiate a resume. Software should also write 0 to clear it. NOTE: It is required that software generate a positive pulse on this bit to */
        unsigned int id_pu:1;               /* ID pullup enable. This field controls the internal pull-up to OTG_ID pin. Software should set this to 1 if using internal OTG_ID. If software is using a GPIO for OTG_ID, then it can write this to 0. 0 = DISABLE 1 = ENABLE */
        unsigned int rsvd13:1;              /* Reserved */
        unsigned int sw_otg_id:1;           /* Software controlled OTG_ID. If SW_OTG_ID_EN = 1, then software needs to monitor actual OTG_ID bit used as a GPIO and based on the value of OTG_ID, it can set this bit. This field is the same as the field ID_SW_VALUE in register USB_PHY_VBUS_WAKEUP_ID. 0 = UNSET 1 = SET */
        unsigned int vbus_chg_int_en:1;     /* VBUS Change Interrupt Enable If set, an interrupt will be generated whenever A_SESS_VLD changes value. Software can read the value of A_SESS_VLD from A_SESS_VLD_STS2 bit. This field is the same as the field A_SESS_VLD_INT_EN in register USB_PHY_VBUS_SENSORS. 0 = DISABLE 1 = ENABLE */
        unsigned int susp_set:1;            /* Suspend Set Software must write a 1 to this bit to put the USB PHY in suspend mode. Software should do this only after making sure that the USB is indeed in suspend mode. Setting this bit will stop the PHY clock. Software should write a 0 to clear it. NOTE: It is required that software generate a positive pulse on this bit to guarantee proper operation. 0 = UNSET 1 = SET */
        unsigned int sw_a_sess_vld_en:1;    /* Enable Software Controlled A_SESS_VLD. Software sets this bit to drive the value in SW_A_SESS_VLD to the USB controller. This field is the same as the field A_SESS_VLD_SW_EN in register USB_PHY_VBUS_SENSORS. 0 = DISABLE 1 = ENABLE */
        unsigned int sw_a_sess_vld:1;       /* Software_A_SESS_VLD status. Software should write the appropriate value (1/0) to set/unset the A_SESS_VLD status. This field is the same as the field A_SESS_VLD_SW_VALUE in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int sw_a_vbus_vld_en:1;    /* Enable Software Controlled A_VBUS_VLD. Software sets this bit to drive the value in SW_A_VBUS_VLD to the USB controller. This field is the same as the field A_VBUS_VLD_SW_EN in register USB_PHY_VBUS_SENSORS. 0 = DISABLE 1 = ENABLE */
        unsigned int sw_a_vbus_vld:1;       /* Software_A_VBUS_VLD status. Software should write the appropriate value (1/0) to set/unset the A_VBUS_VLD status. This field is the same as the field A_VBUS_VLD_SW_VALUE in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int sw_b_sess_end_en:1;    /* Enable Software Controlled B_SESS_END. Software sets this bit to drive the value in SW_B_SESS_END to the USB controller This field is the same as the field B_SESS_END_SW_EN in register USB_PHY_VBUS_SENSORS. 0 = DISABLE 1 = ENABLE */
        unsigned int sw_b_sess_end:1;       /* Software_B_SESS_END status. Software should write the appropriate value (1/0) to set/unset the B_SESS_END status. This field is the same as the field B_SESS_END_SW_VALUE in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int a_sess_vld_sts2:1;     /* A_SESS_VLD status from USB PHY. This field is the same as the field A_SESS_VLD_STS in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int a_vbus_vld_sts2:1;     /* A_VBUS_VLD status from USB PHY. This field is the same as the field A_VBUS_VLD_STS in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int b_sess_end_sts2:1;     /* B_SESS_END status from USB PHY. This field is the same as the field B_SESS_END_STS in register USB_PHY_VBUS_SENSORS. 0 = UNSET 1 = SET */
        unsigned int undefined_bits_26_29:4;
        unsigned int wake_on_cnnt_en:1;     /* Wake on Connect Enable (device mode) When enabled (1), USB PHY will wake up from suspend on a connect event. 0 = DISABLE 1 = ENABLE */
        unsigned int wake_on_discon_en:1;   /* Wake on Disconnect Enable (device mode). When enabled (1), USB PHY will wake up from suspend on a disconnect event. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_misc_usb_otg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_misc_usb_otg_u old_value_t = { .reg32 = value };
    const pp_misc_usb_otg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sus_pol:1",
              "Polarity of the suspend signal going to USB PHY Software should not change this.\n0 = ACTIVE_LOW\n1 = ACTIVE_HIGH",
              1, old_value_t.sus_pol, new_value_t.sus_pol };
    m_bit_details_model.bits.append(entry);
    entry = { "01: staticgpi:1",
              "Static General purpose input coming from ID pin\n0 = UNSET\n1 = SET",
              1, old_value_t.staticgpi, new_value_t.staticgpi };
    m_bit_details_model.bits.append(entry);
    entry = { "02: suspended:1",
              "USB PHY suspend status This bit is set to 1 whenever USB is suspended and the PHY clock isn’t available. NOTE: Software should not access any registers in USB controller when this bit is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.suspended, new_value_t.suspended };
    m_bit_details_model.bits.append(entry);
    entry = { "03: sw_otg_id_en:1",
              "Enable Software Controlled OTG_ID If using a GPIO for OTG_ID signal, then software can set this to 1 and write the value from the GPIO to the SW_OTG_ID bit in this register. This field is the same as the field ID_SW_EN in register USB_PHY_VBUS_WAKEUP_ID.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sw_otg_id_en, new_value_t.sw_otg_id_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: otg_id:1",
              "Real OTG_ID status from the USB PHY. This field is the same as the field ID_STS in register USB_PHY_VBUS_WAKEUP_ID.\n0 = UNSET\n1 = SET",
              1, old_value_t.otg_id, new_value_t.otg_id };
    m_bit_details_model.bits.append(entry);
    entry = { "05: lpbk_en:1",
              "Loopback enable Not for normal software use\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.lpbk_en, new_value_t.lpbk_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: vbus_chg_det:1",
              "VBUS change detect. This bit is set whenever a change in A_SESS_VLD is detected. Software can read the status of A_SESS_VLD from A_SESS_VLD_STS2 bit. This field is the same as the field A_SESS_VLD_CHG_DET in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.vbus_chg_det, new_value_t.vbus_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "07: pclkvld:1",
              "PHY clock valid status. This bit is set whenever PHY clock becomes valid. It is cleared whenever PHY clock stops.\n0 = UNSET\n1 = SET",
              1, old_value_t.pclkvld, new_value_t.pclkvld };
    m_bit_details_model.bits.append(entry);
    entry = { "08: wk_rsm_en:1",
              "Wake on resume enable. If this bit is enabled, USB PHY will wake up from suspend whenever resume/reset signaling is detected on USB.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wk_rsm_en, new_value_t.wk_rsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "09: rsm_ie:1",
              "Resume/Clock valid interrupt enable. If this bit is enabled, interrupt is generated whenever PHY clock becomes valid.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.rsm_ie, new_value_t.rsm_ie };
    m_bit_details_model.bits.append(entry);
    entry = { "10: rsm_vbus_chg:1",
              "Wake/resume on VBUS change detect. If enabled, the USB PHY will wake up whenever a change in A_SESS_VLD is detected. This should be set only when USB PHY is already suspended.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.rsm_vbus_chg, new_value_t.rsm_vbus_chg };
    m_bit_details_model.bits.append(entry);
    entry = { "11: susp_clr:1",
              "Suspend Clear Software must write a 1 to this bit to bring the PHY out of suspend mode. This is used when the software stops the PHY clock during suspend and then wants to initiate a resume. Software should also write 0 to clear it. NOTE: It is required that software generate a positive pulse on this bit to",
              1, old_value_t.susp_clr, new_value_t.susp_clr };
    m_bit_details_model.bits.append(entry);
    entry = { "12: id_pu:1",
              "ID pullup enable. This field controls the internal pull-up to OTG_ID pin. Software should set this to 1 if using internal OTG_ID. If software is using a GPIO for OTG_ID, then it can write this to 0.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.id_pu, new_value_t.id_pu };
    m_bit_details_model.bits.append(entry);
    entry = { "13: rsvd13:1",
              "Reserved",
              1, old_value_t.rsvd13, new_value_t.rsvd13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sw_otg_id:1",
              "Software controlled OTG_ID. If SW_OTG_ID_EN = 1, then software needs to monitor actual OTG_ID bit used as a GPIO and based on the value of OTG_ID, it can set this bit. This field is the same as the field ID_SW_VALUE in register USB_PHY_VBUS_WAKEUP_ID.\n0 = UNSET\n1 = SET",
              1, old_value_t.sw_otg_id, new_value_t.sw_otg_id };
    m_bit_details_model.bits.append(entry);
    entry = { "15: vbus_chg_int_en:1",
              "VBUS Change Interrupt Enable If set, an interrupt will be generated whenever A_SESS_VLD changes value. Software can read the value of A_SESS_VLD from A_SESS_VLD_STS2 bit. This field is the same as the field A_SESS_VLD_INT_EN in register USB_PHY_VBUS_SENSORS.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vbus_chg_int_en, new_value_t.vbus_chg_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "16: susp_set:1",
              "Suspend Set Software must write a 1 to this bit to put the USB PHY in suspend mode. Software should do this only after making sure that the USB is indeed in suspend mode. Setting this bit will stop the PHY clock. Software should write a 0 to clear it. NOTE: It is required that software generate a positive pulse on this bit to guarantee proper operation.\n0 = UNSET\n1 = SET",
              1, old_value_t.susp_set, new_value_t.susp_set };
    m_bit_details_model.bits.append(entry);
    entry = { "17: sw_a_sess_vld_en:1",
              "Enable Software Controlled A_SESS_VLD. Software sets this bit to drive the value in SW_A_SESS_VLD to the USB controller. This field is the same as the field A_SESS_VLD_SW_EN in register USB_PHY_VBUS_SENSORS.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sw_a_sess_vld_en, new_value_t.sw_a_sess_vld_en };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sw_a_sess_vld:1",
              "Software_A_SESS_VLD status. Software should write the appropriate value (1/0) to set/unset the A_SESS_VLD status. This field is the same as the field A_SESS_VLD_SW_VALUE in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.sw_a_sess_vld, new_value_t.sw_a_sess_vld };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sw_a_vbus_vld_en:1",
              "Enable Software Controlled A_VBUS_VLD. Software sets this bit to drive the value in SW_A_VBUS_VLD to the USB controller. This field is the same as the field A_VBUS_VLD_SW_EN in register USB_PHY_VBUS_SENSORS.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sw_a_vbus_vld_en, new_value_t.sw_a_vbus_vld_en };
    m_bit_details_model.bits.append(entry);
    entry = { "20: sw_a_vbus_vld:1",
              "Software_A_VBUS_VLD status. Software should write the appropriate value (1/0) to set/unset the A_VBUS_VLD status. This field is the same as the field A_VBUS_VLD_SW_VALUE in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.sw_a_vbus_vld, new_value_t.sw_a_vbus_vld };
    m_bit_details_model.bits.append(entry);
    entry = { "21: sw_b_sess_end_en:1",
              "Enable Software Controlled B_SESS_END. Software sets this bit to drive the value in SW_B_SESS_END to the USB controller This field is the same as the field B_SESS_END_SW_EN in register USB_PHY_VBUS_SENSORS.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sw_b_sess_end_en, new_value_t.sw_b_sess_end_en };
    m_bit_details_model.bits.append(entry);
    entry = { "22: sw_b_sess_end:1",
              "Software_B_SESS_END status. Software should write the appropriate value (1/0) to set/unset the B_SESS_END status. This field is the same as the field B_SESS_END_SW_VALUE in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.sw_b_sess_end, new_value_t.sw_b_sess_end };
    m_bit_details_model.bits.append(entry);
    entry = { "23: a_sess_vld_sts2:1",
              "A_SESS_VLD status from USB PHY. This field is the same as the field A_SESS_VLD_STS in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.a_sess_vld_sts2, new_value_t.a_sess_vld_sts2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: a_vbus_vld_sts2:1",
              "A_VBUS_VLD status from USB PHY. This field is the same as the field A_VBUS_VLD_STS in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.a_vbus_vld_sts2, new_value_t.a_vbus_vld_sts2 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: b_sess_end_sts2:1",
              "B_SESS_END status from USB PHY. This field is the same as the field B_SESS_END_STS in register USB_PHY_VBUS_SENSORS.\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_end_sts2, new_value_t.b_sess_end_sts2 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_29:4", "", 4, old_value_t.undefined_bits_26_29, new_value_t.undefined_bits_26_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: wake_on_cnnt_en:1",
              "Wake on Connect Enable (device mode) When enabled (1), USB PHY will wake up from suspend on a connect event.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wake_on_cnnt_en, new_value_t.wake_on_cnnt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "31: wake_on_discon_en:1",
              "Wake on Disconnect Enable (device mode). When enabled (1), USB PHY will wake up from suspend on a disconnect event.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wake_on_discon_en, new_value_t.wake_on_discon_en };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is used to control suspend/resume status of USB PHY, and VBUS and ID sensor status and control. Some of the bits in this register also appear in the registers USB_PHY_VBUS_SENSORS and  USB_PHY_VBUS_WAKEUP_ID.\nMiscellaneous Control Register for OTG Controller";
}

#define PP_USB_PHY_PARAM_OFFSET 0x64
#define PP_USB_PHY_PARAM_UNDEFMASK 0xFFFFFFE7
union pp_usb_phy_param_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int vs_ctl:2;              /* Vbus_sense control Controls which VBUS sensor input is driven to the controller. 00: Use VBUS_WAKEUP. 01: Use (A_SESS_VLD || B_SESS_VLD) output from the PHY if the PHY clock is available. Otherwise, use VBUS_WAKEUP. 10: Use (A_SESS_VLD || B_SESS_VLD) output from the PHY 11: Use A_SESS_VLD output from the PHY 0 = VBUS_WAKEUP 1 = AB_SESS_VLD_OR_VBUS_WAKEUP 2 = AB_SESS_VLD 3 = A_SESS_VLD */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_usb_phy_param_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_usb_phy_param_u old_value_t = { .reg32 = value };
    const pp_usb_phy_param_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: vs_ctl:2",
              "Vbus_sense control Controls which VBUS sensor input is driven to the controller. 00: Use VBUS_WAKEUP. 01: Use (A_SESS_VLD || B_SESS_VLD) output from the PHY if the PHY clock is available. Otherwise, use VBUS_WAKEUP. 10: Use (A_SESS_VLD || B_SESS_VLD) output from the PHY 11: Use A_SESS_VLD output from the PHY\n0 = VBUS_WAKEUP\n1 = AB_SESS_VLD_OR_VBUS_WAKEUP\n2 = AB_SESS_VLD\n3 = A_SESS_VLD",
              2, old_value_t.vs_ctl, new_value_t.vs_ctl };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register controls the parameters for USB PHY.\nUSB PHY Parameters";
}

#define PP_USB_PHY_VBUS_SENSORS_OFFSET 0x70
#define PP_USB_PHY_VBUS_SENSORS_UNDEFMASK 0xC0C0C0C0
union pp_usb_phy_vbus_sensors_u {
    struct {
        unsigned int b_sess_end_int_en:1;   /* B_SESS_END interrupt enable If this field is set to 1, an interrupt is generated whenever B_SESS_END_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int b_sess_end_chg_det:1;  /* B_SESS_END change detect. This field is set by hardware whenever a change is detected in the value of B_SESS_END. software writes a 1 to clear it 0 = UNSET 1 = SET */
        unsigned int b_sess_end_sts:1;      /* B_SESS_END status. This is set to 1 whenever B_SESS_END sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int b_sess_end_sw_en:1;    /* B_SESS_END software enable. Enable Software Controlled B_SESS_END Software sets this bit to drive the value in B_SESS_END_SW_VALUE to the USB controller. 0 = DISABLE 1 = ENABLE */
        unsigned int b_sess_end_sw_value:1; /* B_SESS_END software value Software should write the appropriate value (1/0) to set/unset the B_SESS_END status. This is only valid when B_SESS_END_SW_EN is set. 0 = UNSET 1 = SET */
        unsigned int b_sess_end_deb_sel_b:1;/* B_SESS_END debounce A/B select Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A 1 = SEL_B */
        unsigned int undefined_bits_6_7:2;
        unsigned int b_sess_vld_int_en:1;   /* B_SESS_VLD interrupt enable. If this field is set to 1, an interrupt is generated whenever B_SESS_VLD_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int b_sess_vld_chg_det:1;  /* B_SESS_VLD change detect. This field is set by hardware whenever a change is detected in the value of B_SESS_VLD. software writes a 1 to clear it 0 = UNSET 1 = SET */
        unsigned int b_sess_vld_sts:1;      /* B_SESS_VLD status. This is set to 1 whenever B_SESS_VLD sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int b_sess_vld_sw_en:1;    /* B_SESS_VLD software enable. Enable Software Controlled B_SESS_VLD. Software sets this bit to drive the value in B_SESS_VLD_SW_VALUE to the USB controller. 0 = DISABLE 1 = ENABLE */
        unsigned int b_sess_vld_sw_value:1; /* B_SESS_VLD software value. Software should write the appropriate value (1/0) to set/unset the B_SESS_VLD status. This is only valid when B_SESS_VLD_SW_EN is set. 0 = UNSET 1 = SET */
        unsigned int b_sess_vld_deb_sel_b:1;/* B_SESS_VLD debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A */
        unsigned int undefined_bits_14_15:2;
        unsigned int a_sess_vld_int_en:1;   /* A_SESS_VLD interrupt enable. If this field is set to 1, an interrupt is generated whenever A_SESS_VLD_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int a_sess_vld_chg_det:1;  /* A_SESS_VLD change detect. This field is set by hardware whenever a change is detected in the value of A_SESS_VLD. software writes a 1 to clear it 0 = UNSET 1 = SET */
        unsigned int a_sess_vld_sts:1;      /* A_SESS_VLD status. This is set to 1 whenever A_SESS_VLD sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int a_sess_vld_sw_en:1;    /* A_SESS_VLD software enable. Enable Software Controlled A_SESS_VLD. Software sets this bit to drive the value in A_SESS_VLD_SW_VALUE to the USB controller. 0 = DISABLE 1 = ENABLE */
        unsigned int a_sess_vld_sw_value:1; /* A_SESS_VLD software value. Software should write the appropriate value (1/0) to set/unset the A_SESS_VLD status. This is only valid when A_SESS_VLD_SW_EN is set. 0 = UNSET 1 = SET */
        unsigned int a_sess_vld_deb_sel_b:1;/* A_SESS_VLD debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A 1 = SEL_B */
        unsigned int undefined_bits_22_23:2;
        unsigned int a_vbus_vld_int_en:1;   /* A_VBUS_VLD interrupt enable. If this field is set to 1, an interrupt is generated whenever A_VBUS_VLD_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int a_vbus_vld_chg_det:1;  /* A_VBUS_VLD change detect. This field is set by hardware whenever a change is detected in the value of A_VBUS_VLD. software writes a 1 to clear it 0 = UNSET 1 = SET */
        unsigned int a_vbus_vld_sts:1;      /* A_VBUS_VLD status. This is set to 1 whenever A_VBUS_VLD sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int a_vbus_vld_sw_en:1;    /* A_VBUS_VLD software enable. Enable Software Controlled A_VBUS_VLD. Software sets this bit to drive the value in A_VBUS_VLD_SW_VALUE to the USB controller. 0 = DISABLE 1 = ENABLE */
        unsigned int a_vbus_vld_sw_value:1; /* A_VBUS_VLD software value. Software should write the appropriate value (1/0) to set/unset the A_VBUS_VLD status. This is only valid when A_VBUS_VLD_SW_EN is set; 0 = UNSET 1 = SET */
        unsigned int a_vbus_vld_deb_sel_b:1;/* A_VBUS_VLD debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A 1 = SEL_B */
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_usb_phy_vbus_sensors_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_usb_phy_vbus_sensors_u old_value_t = { .reg32 = value };
    const pp_usb_phy_vbus_sensors_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: b_sess_end_int_en:1",
              "B_SESS_END interrupt enable If this field is set to 1, an interrupt is generated whenever B_SESS_END_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.b_sess_end_int_en, new_value_t.b_sess_end_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: b_sess_end_chg_det:1",
              "B_SESS_END change detect. This field is set by hardware whenever a change is detected in the value of B_SESS_END. software writes a 1 to clear it\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_end_chg_det, new_value_t.b_sess_end_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "02: b_sess_end_sts:1",
              "B_SESS_END status. This is set to 1 whenever B_SESS_END sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_end_sts, new_value_t.b_sess_end_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "03: b_sess_end_sw_en:1",
              "B_SESS_END software enable. Enable Software Controlled B_SESS_END Software sets this bit to drive the value in B_SESS_END_SW_VALUE to the USB controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.b_sess_end_sw_en, new_value_t.b_sess_end_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: b_sess_end_sw_value:1",
              "B_SESS_END software value Software should write the appropriate value (1/0) to set/unset the B_SESS_END status. This is only valid when B_SESS_END_SW_EN is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_end_sw_value, new_value_t.b_sess_end_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "05: b_sess_end_deb_sel_b:1",
              "B_SESS_END debounce A/B select Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A\n1 = SEL_B",
              1, old_value_t.b_sess_end_deb_sel_b, new_value_t.b_sess_end_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: b_sess_vld_int_en:1",
              "B_SESS_VLD interrupt enable. If this field is set to 1, an interrupt is generated whenever B_SESS_VLD_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.b_sess_vld_int_en, new_value_t.b_sess_vld_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "09: b_sess_vld_chg_det:1",
              "B_SESS_VLD change detect. This field is set by hardware whenever a change is detected in the value of B_SESS_VLD. software writes a 1 to clear it\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_vld_chg_det, new_value_t.b_sess_vld_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "10: b_sess_vld_sts:1",
              "B_SESS_VLD status. This is set to 1 whenever B_SESS_VLD sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_vld_sts, new_value_t.b_sess_vld_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "11: b_sess_vld_sw_en:1",
              "B_SESS_VLD software enable. Enable Software Controlled B_SESS_VLD. Software sets this bit to drive the value in B_SESS_VLD_SW_VALUE to the USB controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.b_sess_vld_sw_en, new_value_t.b_sess_vld_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "12: b_sess_vld_sw_value:1",
              "B_SESS_VLD software value. Software should write the appropriate value (1/0) to set/unset the B_SESS_VLD status. This is only valid when B_SESS_VLD_SW_EN is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_vld_sw_value, new_value_t.b_sess_vld_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "13: b_sess_vld_deb_sel_b:1",
              "B_SESS_VLD debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A",
              1, old_value_t.b_sess_vld_deb_sel_b, new_value_t.b_sess_vld_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_15:2", "", 2, old_value_t.undefined_bits_14_15, new_value_t.undefined_bits_14_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: a_sess_vld_int_en:1",
              "A_SESS_VLD interrupt enable. If this field is set to 1, an interrupt is generated whenever A_SESS_VLD_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.a_sess_vld_int_en, new_value_t.a_sess_vld_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "17: a_sess_vld_chg_det:1",
              "A_SESS_VLD change detect. This field is set by hardware whenever a change is detected in the value of A_SESS_VLD. software writes a 1 to clear it\n0 = UNSET\n1 = SET",
              1, old_value_t.a_sess_vld_chg_det, new_value_t.a_sess_vld_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "18: a_sess_vld_sts:1",
              "A_SESS_VLD status. This is set to 1 whenever A_SESS_VLD sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.a_sess_vld_sts, new_value_t.a_sess_vld_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "19: a_sess_vld_sw_en:1",
              "A_SESS_VLD software enable. Enable Software Controlled A_SESS_VLD. Software sets this bit to drive the value in A_SESS_VLD_SW_VALUE to the USB controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.a_sess_vld_sw_en, new_value_t.a_sess_vld_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "20: a_sess_vld_sw_value:1",
              "A_SESS_VLD software value. Software should write the appropriate value (1/0) to set/unset the A_SESS_VLD status. This is only valid when A_SESS_VLD_SW_EN is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.a_sess_vld_sw_value, new_value_t.a_sess_vld_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "21: a_sess_vld_deb_sel_b:1",
              "A_SESS_VLD debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A\n1 = SEL_B",
              1, old_value_t.a_sess_vld_deb_sel_b, new_value_t.a_sess_vld_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_23:2", "", 2, old_value_t.undefined_bits_22_23, new_value_t.undefined_bits_22_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: a_vbus_vld_int_en:1",
              "A_VBUS_VLD interrupt enable. If this field is set to 1, an interrupt is generated whenever A_VBUS_VLD_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.a_vbus_vld_int_en, new_value_t.a_vbus_vld_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "25: a_vbus_vld_chg_det:1",
              "A_VBUS_VLD change detect. This field is set by hardware whenever a change is detected in the value of A_VBUS_VLD. software writes a 1 to clear it\n0 = UNSET\n1 = SET",
              1, old_value_t.a_vbus_vld_chg_det, new_value_t.a_vbus_vld_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "26: a_vbus_vld_sts:1",
              "A_VBUS_VLD status. This is set to 1 whenever A_VBUS_VLD sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.a_vbus_vld_sts, new_value_t.a_vbus_vld_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "27: a_vbus_vld_sw_en:1",
              "A_VBUS_VLD software enable. Enable Software Controlled A_VBUS_VLD. Software sets this bit to drive the value in A_VBUS_VLD_SW_VALUE to the USB controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.a_vbus_vld_sw_en, new_value_t.a_vbus_vld_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "28: a_vbus_vld_sw_value:1",
              "A_VBUS_VLD software value. Software should write the appropriate value (1/0) to set/unset the A_VBUS_VLD status. This is only valid when A_VBUS_VLD_SW_EN is set;\n0 = UNSET\n1 = SET",
              1, old_value_t.a_vbus_vld_sw_value, new_value_t.a_vbus_vld_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "29: a_vbus_vld_deb_sel_b:1",
              "A_VBUS_VLD debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A\n1 = SEL_B",
              1, old_value_t.a_vbus_vld_deb_sel_b, new_value_t.a_vbus_vld_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register controls the OTG VBUS sensors in the USB PHY.\nThe following 4 VBUS sensors are present:\n    * A_VBUS_VLD\n    * A_SESS_VLD\n    * B_SESS_VLD\n    * B_SESS_END\nThe debounced status of each sensor can be read from _STS. The field  _CHG_DET is set to 1 whenever a change is detected in the value. If _INT_EN is set, then an interrupt is generated to the processor. This interrupt can be routed to CPU/COP by appropriately writing the USBD bits in the interrupt controller registers.\n In case Software wants to override the value for ‘a’, it can set _SW_EN to 1, and set _SW_VALUE to 1 or 0 as per the requirement.\nThere are two debouncers for each sensor - DEBOUNCE_A and DEBOUNCE_B. The debounce values for them are controlled by the register UTMIP_DEBOUNCE_CFG0, fields UTMIP_BIAS_DEBOUNCE_A  and UTMIP_BIAS_DEBOUNCE_B. For each sensor, we can select whether to use DEBOUNCE_A or DEBOUNCE_B by setting the field _DEB_SEL_B to appropriate value (SEL_A or SEL_B).\nNote:\n Do not set either UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B to 0x0. If not using one of the debouncers, keep it at the default value of 0xFFFF.\nThe source for A_SESS_VLD sensor can be programmed according to the setting of VS_CTL in register USB_PHY_PARAM";
}

#define PP_USB_PHY_VBUS_WAKEUP_ID_OFFSET 0x74
#define PP_USB_PHY_VBUS_WAKEUP_ID_UNDEFMASK 0xC0C0C0C0
union pp_usb_phy_vbus_wakeup_id_u {
    struct {
        unsigned int id_int_en:1;           /* ID interrupt enable. If this field is set to 1, an interrupt is generated whenever ID_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int id_chg_det:1;          /* ID change detect. This field is set by hardware whenever a change is detected in the value of ID. software writes a 1 to clear it; 0 = UNSET 1 = SET */
        unsigned int id_sts:1;              /* ID status. This is set to 1 whenever ID sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int id_sw_en:1;            /* ID software enable. Enable Software Controlled ID. Software sets this bit to drive the value in ID_SW_VALUE to the USB controller 0 = DISABLE 1 = ENABLE */
        unsigned int id_sw_value:1;         /* ID software value. Software should write the appropriate value (1/0) to set/unset the ID status. This is only valid when ID_SW_EN is set. 0 = UNSET 1 = SET */
        unsigned int id_deb_sel_b:1;        /* ID debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A 1 = SEL_B */
        unsigned int undefined_bits_6_7:2;
        unsigned int vbus_wakeup_int_en:1;  /* VBUS_WAKEUP interrupt enable If this field is set to 1, an interrupt is generated whenever VBUS_WAKEUP_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int vbus_wakeup_chg_det:1; /* VBUS_WAKEUP change detect. This field is set by hardware whenever a change is detected in the value of VBUS_WAKEUP. software writes a 1 to clear it 0 = UNSET 1 = SET */
        unsigned int vbus_wakeup_sts:1;     /* VBUS_WAKEUP status. This is set to 1 whenever VBUS_WAKEUP sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int vbus_wakeup_sw_en:1;   /* VBUS_WAKEUP software enable. Enable Software Controlled VBUS_WAKEUP. Software sets this bit to drive the value in VBUS_WAKEUP_SW_VALUE to the USB controller. 0 = DISABLE 1 = ENABLE */
        unsigned int vbus_wakeup_sw_value:1;/* VBUS_WAKEUP software value. Software should write the appropriate value (1/0) to set/unset the VBUS_WAKEUP status. This is only valid when VBUS_WAKEUP_SW_EN is set. 0 = UNSET 1 = SET */
        unsigned int vbus_wakeup_deb_sel_b:1;/* VBUS_WAKEUP debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A 1 = SEL_B */
        unsigned int undefined_bits_14_15:2;
        unsigned int vdat_det_int_en:1;     /* VDAT_DET interrupt enable. If this field is set to 1, an interrupt is generated whenever VDAT_DET_CHG_DET is set to 1. 0 = DISABLE 1 = ENABLE */
        unsigned int vdat_det_chg_det:1;    /* VDAT_DET change detect. This field is set by hardware whenever a change is detected in the value of VDAT_DET. software writes a 1 to clear it; 0 = UNSET 1 = SET */
        unsigned int vdat_det_sts:1;        /* VDAT_DET status. This is set to 1 whenever VDAT_DET sensor output is 1. 0 = UNSET 1 = SET */
        unsigned int vdat_det_sw_en:1;      /* VDAT_DET software enable. Enable Software Controlled VDAT_DET. Software sets this bit to drive the value in VDAT_DET_SW_VALUE to the USB controller 0 = DISABLE 1 = ENABLE */
        unsigned int vdat_det_sw_value:1;   /* VDAT_DET software value. Software should write the appropriate value (1/0) to set/unset the VDAT_DET status. This is only valid when VDAT_DET_SW_EN is set. 0 = UNSET 1 = SET */
        unsigned int vdat_det_deb_sel_b:1;  /* VDAT_DET debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0. 0 = SEL_A 1 = SEL_B */
        unsigned int undefined_bits_22_23:2;
        unsigned int ip_delay_tx2tx_hs:6;   /* HS Tx to Tx inter-packet delay counter. Software should not change this */
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_usb_phy_vbus_wakeup_id_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_usb_phy_vbus_wakeup_id_u old_value_t = { .reg32 = value };
    const pp_usb_phy_vbus_wakeup_id_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: id_int_en:1",
              "ID interrupt enable. If this field is set to 1, an interrupt is generated whenever ID_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.id_int_en, new_value_t.id_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: id_chg_det:1",
              "ID change detect. This field is set by hardware whenever a change is detected in the value of ID. software writes a 1 to clear it;\n0 = UNSET\n1 = SET",
              1, old_value_t.id_chg_det, new_value_t.id_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "02: id_sts:1",
              "ID status. This is set to 1 whenever ID sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.id_sts, new_value_t.id_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "03: id_sw_en:1",
              "ID software enable. Enable Software Controlled ID. Software sets this bit to drive the value in ID_SW_VALUE to the USB controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.id_sw_en, new_value_t.id_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: id_sw_value:1",
              "ID software value. Software should write the appropriate value (1/0) to set/unset the ID status. This is only valid when ID_SW_EN is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.id_sw_value, new_value_t.id_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "05: id_deb_sel_b:1",
              "ID debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A\n1 = SEL_B",
              1, old_value_t.id_deb_sel_b, new_value_t.id_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vbus_wakeup_int_en:1",
              "VBUS_WAKEUP interrupt enable If this field is set to 1, an interrupt is generated whenever VBUS_WAKEUP_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vbus_wakeup_int_en, new_value_t.vbus_wakeup_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "09: vbus_wakeup_chg_det:1",
              "VBUS_WAKEUP change detect. This field is set by hardware whenever a change is detected in the value of VBUS_WAKEUP. software writes a 1 to clear it\n0 = UNSET\n1 = SET",
              1, old_value_t.vbus_wakeup_chg_det, new_value_t.vbus_wakeup_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vbus_wakeup_sts:1",
              "VBUS_WAKEUP status. This is set to 1 whenever VBUS_WAKEUP sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.vbus_wakeup_sts, new_value_t.vbus_wakeup_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vbus_wakeup_sw_en:1",
              "VBUS_WAKEUP software enable. Enable Software Controlled VBUS_WAKEUP. Software sets this bit to drive the value in VBUS_WAKEUP_SW_VALUE to the USB controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vbus_wakeup_sw_en, new_value_t.vbus_wakeup_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vbus_wakeup_sw_value:1",
              "VBUS_WAKEUP software value. Software should write the appropriate value (1/0) to set/unset the VBUS_WAKEUP status. This is only valid when VBUS_WAKEUP_SW_EN is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.vbus_wakeup_sw_value, new_value_t.vbus_wakeup_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "13: vbus_wakeup_deb_sel_b:1",
              "VBUS_WAKEUP debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A\n1 = SEL_B",
              1, old_value_t.vbus_wakeup_deb_sel_b, new_value_t.vbus_wakeup_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_15:2", "", 2, old_value_t.undefined_bits_14_15, new_value_t.undefined_bits_14_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: vdat_det_int_en:1",
              "VDAT_DET interrupt enable. If this field is set to 1, an interrupt is generated whenever VDAT_DET_CHG_DET is set to 1.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vdat_det_int_en, new_value_t.vdat_det_int_en };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vdat_det_chg_det:1",
              "VDAT_DET change detect. This field is set by hardware whenever a change is detected in the value of VDAT_DET. software writes a 1 to clear it;\n0 = UNSET\n1 = SET",
              1, old_value_t.vdat_det_chg_det, new_value_t.vdat_det_chg_det };
    m_bit_details_model.bits.append(entry);
    entry = { "18: vdat_det_sts:1",
              "VDAT_DET status. This is set to 1 whenever VDAT_DET sensor output is 1.\n0 = UNSET\n1 = SET",
              1, old_value_t.vdat_det_sts, new_value_t.vdat_det_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vdat_det_sw_en:1",
              "VDAT_DET software enable. Enable Software Controlled VDAT_DET. Software sets this bit to drive the value in VDAT_DET_SW_VALUE to the USB controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vdat_det_sw_en, new_value_t.vdat_det_sw_en };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vdat_det_sw_value:1",
              "VDAT_DET software value. Software should write the appropriate value (1/0) to set/unset the VDAT_DET status. This is only valid when VDAT_DET_SW_EN is set.\n0 = UNSET\n1 = SET",
              1, old_value_t.vdat_det_sw_value, new_value_t.vdat_det_sw_value };
    m_bit_details_model.bits.append(entry);
    entry = { "21: vdat_det_deb_sel_b:1",
              "VDAT_DET debounce A/B select. Selects between the two debounce values UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B from the register UTMIP_DEBOUNCE_CFG0.\n0 = SEL_A\n1 = SEL_B",
              1, old_value_t.vdat_det_deb_sel_b, new_value_t.vdat_det_deb_sel_b };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_23:2", "", 2, old_value_t.undefined_bits_22_23, new_value_t.undefined_bits_22_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ip_delay_tx2tx_hs:6",
              "HS Tx to Tx inter-packet delay counter. Software should not change this",
              6, old_value_t.ip_delay_tx2tx_hs, new_value_t.ip_delay_tx2tx_hs };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register controls the battery charger (VDAT_DET), VBUS_WAKEUP and ID sensors.\nThe following sensors are present in this register:\n    * VBUS_WAKEUP\n    * ID\n    * VDAT_DET\n The debounced status of each sensor can be read from _STS. The field _CHG_DET is set to 1 whenever a change is detected in the value of . If _INT_EN is set, then an interrupt is generated to the processor. This interrupt can be routed to CPU/COP by appropriately writing the USBD bits in the interrupt controller registers.\n In case Software wants to override the value for a , it can set _SW_EN to 1, and set _SW_VALUE to 1 or 0 as per the requirement.\n There are two debouncers for each sensor - DEBOUNCE_A and DEBOUNCE_B. The debounce values for them are controlled by the register UTMIP_DEBOUNCE_CFG0, fields UTMIP_BIAS_DEBOUNCE_A and UTMIP_BIAS_DEBOUNCE_B. For each sensor, we can select whether to use DEBOUNCE_A or DEBOUNCE_B by setting the field _DEB_SEL_B to approrpriate value (SEL_A or SEL_B).\nNote:\n Do not set either UTMIP_BIAS_DEBOUNCE_A or UTMIP_BIAS_DEBOUNCE_B to 0x0. If not using one of the debouncers, keep it at the default value of 0xFFFF.\nThere is no debouncer for VDAT_DET.\nUSB PHY VBUS wakeup and ID control register";
}

#define PP_USB_PHY_ALT_VBUS_STS_OFFSET 0x78
#define PP_USB_PHY_ALT_VBUS_STS_UNDEFMASK 0xFFFFFF80
union pp_usb_phy_alt_vbus_sts_u {
    struct {
        unsigned int vbus_wakeup_alt:1;     /* Vbus wakeup alternate status 0 = UNSET 1 = SET */
        unsigned int a_vbus_vld_alt:1;      /* A_VBUS_VLD alternate status 0 = UNSET 1 = SET */
        unsigned int static_gpi_alt:1;      /* Static GPI alternate status 0 = UNSET 1 = SET */
        unsigned int b_sess_end_alt:1;      /* B_SESS_END alternate status 0 = UNSET 1 = SET */
        unsigned int id_dig_alt:1;          /* ID alternate status 0 = UNSET 1 = SET */
        unsigned int b_sess_vld_alt:1;      /* B_SESS_VLD alternate status 0 = UNSET 1 = SET */
        unsigned int a_sess_vld_alt:1;      /* A_SESS_VLD alternate status 0 = UNSET 1 = SET */
        unsigned int undefined_bits_7_31:25;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_usb_phy_alt_vbus_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_usb_phy_alt_vbus_sts_u old_value_t = { .reg32 = value };
    const pp_usb_phy_alt_vbus_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vbus_wakeup_alt:1",
              "Vbus wakeup alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.vbus_wakeup_alt, new_value_t.vbus_wakeup_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "01: a_vbus_vld_alt:1",
              "A_VBUS_VLD alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.a_vbus_vld_alt, new_value_t.a_vbus_vld_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "02: static_gpi_alt:1",
              "Static GPI alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.static_gpi_alt, new_value_t.static_gpi_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "03: b_sess_end_alt:1",
              "B_SESS_END alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_end_alt, new_value_t.b_sess_end_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "04: id_dig_alt:1",
              "ID alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.id_dig_alt, new_value_t.id_dig_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "05: b_sess_vld_alt:1",
              "B_SESS_VLD alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.b_sess_vld_alt, new_value_t.b_sess_vld_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "06: a_sess_vld_alt:1",
              "A_SESS_VLD alternate status\n0 = UNSET\n1 = SET",
              1, old_value_t.a_sess_vld_alt, new_value_t.a_sess_vld_alt };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_31:25", "", 25, old_value_t.undefined_bits_7_31, new_value_t.undefined_bits_7_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "USB PHY Alternate VBUS status register";
}

#define PP_PIN_MUX_CTL_A_OFFSET 0x80
#define PP_PIN_MUX_CTL_A_UNDEFMASK 0x000C0C00
union pp_pin_mux_ctl_a_u {
    struct {
        unsigned int uaa_sel:2;             /* 0 = SPI3; 1 = MIPI_HS; 2 = UART1; 3 = ULPI */
        unsigned int uab_sel:2;             /* 0 = SPI2; 1 = MIPI_HS; 2 = UART1; 3 = ULPI */
        unsigned int uac_sel:2;             /* 0 = OWR; 1 = RSVD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int uad_sel:2;             /* 0 = IRDA; 1 = SPDIF; 2 = UART1; 3 = SPI4 */
        unsigned int uda_sel:2;             /* 0 = SPI1 1 = RSVD 2 = UART4 3 = ULPI */
        unsigned int undefined_bits_10_11:2;
        unsigned int ate_sel:2;             /* 0 = IDE; 1 = NAND; 2 = GMI; 3 = RSVD */
        unsigned int rm_sel:2;              /* 0 = I2C; 1 = RSVD1; 2 = RSVD2; 3 = RSVD3 */
        unsigned int atb_sel:2;             /* 0 = IDE; 1 = NAND; 2 = GMI; 3 = SDIO4 */
        unsigned int undefined_bits_18_19:2;
        unsigned int atd_sel:2;             /* 0 = IDE; 1 = NAND; 2 = GMI; 3 = SDIO4 */
        unsigned int atc_sel:2;             /* 0 = IDE; 1 = NAND; 2 = GMI; 3 = SDIO4 */
        unsigned int ata_sel:2;             /* 0 = IDE; 1 = NAND; 2 = GMI; 3 = RSVD */
        unsigned int kbcf_sel:2;            /* 0 = KBC; 1 = NAND; 2 = TRACE; 3 = MIO */
        unsigned int kbce_sel:2;            /* 0 = KBC; 1 = NAND; 2 = OWR; 3 = RSVD2 */
        unsigned int sdio1_sel:2;           /* 0 = SDIO1 1 = RSVD1 2 = UART5 3 = UART1 */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_a_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_a_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_a_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: uaa_sel:2",
              "0 = SPI3;\n1 = MIPI_HS;\n2 = UART1;\n3 = ULPI",
              2, old_value_t.uaa_sel, new_value_t.uaa_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: uab_sel:2",
              "0 = SPI2;\n1 = MIPI_HS;\n2 = UART1;\n3 = ULPI",
              2, old_value_t.uab_sel, new_value_t.uab_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uac_sel:2",
              "0 = OWR;\n1 = RSVD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.uac_sel, new_value_t.uac_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: uad_sel:2",
              "0 = IRDA;\n1 = SPDIF;\n2 = UART1;\n3 = SPI4",
              2, old_value_t.uad_sel, new_value_t.uad_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uda_sel:2",
              "0 = SPI1\n1 = RSVD\n2 = UART4\n3 = ULPI",
              2, old_value_t.uda_sel, new_value_t.uda_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_11:2", "", 2, old_value_t.undefined_bits_10_11, new_value_t.undefined_bits_10_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ate_sel:2",
              "0 = IDE;\n1 = NAND;\n2 = GMI;\n3 = RSVD",
              2, old_value_t.ate_sel, new_value_t.ate_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: rm_sel:2",
              "0 = I2C;\n1 = RSVD1;\n2 = RSVD2;\n3 = RSVD3",
              2, old_value_t.rm_sel, new_value_t.rm_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: atb_sel:2",
              "0 = IDE;\n1 = NAND;\n2 = GMI;\n3 = SDIO4",
              2, old_value_t.atb_sel, new_value_t.atb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: atd_sel:2",
              "0 = IDE;\n1 = NAND;\n2 = GMI;\n3 = SDIO4",
              2, old_value_t.atd_sel, new_value_t.atd_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: atc_sel:2",
              "0 = IDE;\n1 = NAND;\n2 = GMI;\n3 = SDIO4",
              2, old_value_t.atc_sel, new_value_t.atc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ata_sel:2",
              "0 = IDE;\n1 = NAND;\n2 = GMI;\n3 = RSVD",
              2, old_value_t.ata_sel, new_value_t.ata_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "26: kbcf_sel:2",
              "0 = KBC;\n1 = NAND;\n2 = TRACE;\n3 = MIO",
              2, old_value_t.kbcf_sel, new_value_t.kbcf_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: kbce_sel:2",
              "0 = KBC;\n1 = NAND;\n2 = OWR;\n3 = RSVD2",
              2, old_value_t.kbce_sel, new_value_t.kbce_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sdio1_sel:2",
              "0 = SDIO1\n1 = RSVD1\n2 = UART5\n3 = UART1",
              2, old_value_t.sdio1_sel, new_value_t.sdio1_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register A";
}

#define PP_PIN_MUX_CTL_B_OFFSET 0x84
#define PP_PIN_MUX_CTL_B_UNDEFMASK 0x03000000
union pp_pin_mux_ctl_b_u {
    struct {
        unsigned int gma_sel:2;             /* 0 = UART5 1 = SPI3 2 = GMI 3 = SDMMC4 */
        unsigned int gmc_sel:2;             /* 0 = UART4 1 = SPI4 2 = GMI 3 = SFLASH */
        unsigned int hdint_sel:2;           /* 0 = HDMI; 1 = RSVD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int slxa_sel:2;            /* 0 = PCIE; 1 = SPI4; 2 = SDIO3; 3 = SPI2 */
        unsigned int owc_sel:2;             /* 0 = OWR; 1 = RSVD1; 2 = RSVD2; 3 = RSVD3 */
        unsigned int slxc_sel:2;            /* 0 = SPDIF; 1 = SPI4; 2 = SDIO3; 3 = SPI2 */
        unsigned int slxd_sel:2;            /* 0 = SPDIF; 1 = SPI4; 2 = SDIO3; 3 = SPI2 */
        unsigned int slxk_sel:2;            /* 0 = PCIE; 1 = SPI4; 2 = SDIO3; 3 = SPI2 */
        unsigned int uca_sel:2;             /* 0 = UART3; 1 = RSVD2; 2 = GMI; 3 = RSVD4 */
        unsigned int ucb_sel:2;             /* 0 = UART3; 1 = PWM; 2 = GMI; 3 = RSVD4 */
        unsigned int dta_sel:2;             /* 0 = RSVD1; 1 = SDIO2; 2 = VI; 3 = RSVD4 */
        unsigned int dtb_sel:2;             /* 0 = RSVD1; 1 = RSVD2; 2 = VI; 3 = SPI1 */
        unsigned int undefined_bits_24_25:2;
        unsigned int dtc_sel:2;             /* 0 = RSVD1; 1 = RSVD2; 2 = VI; 3 = RSVD4 */
        unsigned int dtd_sel:2;             /* 0 = RSVD1; 1 = SDIO2; 2 = VI; 3 = RSVD4 */
        unsigned int dte_sel:2;             /* 0 = RSVD1; 1 = RSVD2; 2 = VI; 3 = SPI1 */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_b_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_b_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_b_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gma_sel:2",
              "0 = UART5\n1 = SPI3\n2 = GMI\n3 = SDMMC4",
              2, old_value_t.gma_sel, new_value_t.gma_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gmc_sel:2",
              "0 = UART4\n1 = SPI4\n2 = GMI\n3 = SFLASH",
              2, old_value_t.gmc_sel, new_value_t.gmc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: hdint_sel:2",
              "0 = HDMI;\n1 = RSVD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.hdint_sel, new_value_t.hdint_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: slxa_sel:2",
              "0 = PCIE;\n1 = SPI4;\n2 = SDIO3;\n3 = SPI2",
              2, old_value_t.slxa_sel, new_value_t.slxa_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: owc_sel:2",
              "0 = OWR;\n1 = RSVD1;\n2 = RSVD2;\n3 = RSVD3",
              2, old_value_t.owc_sel, new_value_t.owc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: slxc_sel:2",
              "0 = SPDIF;\n1 = SPI4;\n2 = SDIO3;\n3 = SPI2",
              2, old_value_t.slxc_sel, new_value_t.slxc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: slxd_sel:2",
              "0 = SPDIF;\n1 = SPI4;\n2 = SDIO3;\n3 = SPI2",
              2, old_value_t.slxd_sel, new_value_t.slxd_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: slxk_sel:2",
              "0 = PCIE;\n1 = SPI4;\n2 = SDIO3;\n3 = SPI2",
              2, old_value_t.slxk_sel, new_value_t.slxk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: uca_sel:2",
              "0 = UART3;\n1 = RSVD2;\n2 = GMI;\n3 = RSVD4",
              2, old_value_t.uca_sel, new_value_t.uca_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ucb_sel:2",
              "0 = UART3;\n1 = PWM;\n2 = GMI;\n3 = RSVD4",
              2, old_value_t.ucb_sel, new_value_t.ucb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dta_sel:2",
              "0 = RSVD1;\n1 = SDIO2;\n2 = VI;\n3 = RSVD4",
              2, old_value_t.dta_sel, new_value_t.dta_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: dtb_sel:2",
              "0 = RSVD1;\n1 = RSVD2;\n2 = VI;\n3 = SPI1",
              2, old_value_t.dtb_sel, new_value_t.dtb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_25:2", "", 2, old_value_t.undefined_bits_24_25, new_value_t.undefined_bits_24_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: dtc_sel:2",
              "0 = RSVD1;\n1 = RSVD2;\n2 = VI;\n3 = RSVD4",
              2, old_value_t.dtc_sel, new_value_t.dtc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dtd_sel:2",
              "0 = RSVD1;\n1 = SDIO2;\n2 = VI;\n3 = RSVD4",
              2, old_value_t.dtd_sel, new_value_t.dtd_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dte_sel:2",
              "0 = RSVD1;\n1 = RSVD2;\n2 = VI;\n3 = SPI1",
              2, old_value_t.dte_sel, new_value_t.dte_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register B";
}

#define PP_PIN_MUX_CTL_C_OFFSET 0x88
#define PP_PIN_MUX_CTL_C_UNDEFMASK 0x00000000
union pp_pin_mux_ctl_c_u {
    struct {
        unsigned int ddc_sel:2;             /* 0 = I2C2; 1 = RSVD1; 2 = RSVD2; 3 = RSVD3 */
        unsigned int cdev1_sel:2;           /* 0 = OSC; 1 = PLLA_OUT; 2 = PLLM_OUT1; 3 = AUDIO_SYNC */
        unsigned int cdev2_sel:2;           /* 0 = OSC; 1 = AHB_CLK; 2 = APB_CLK; 3 = PLLP_OUT4 */
        unsigned int csus_sel:2;            /* 0 = PLLC_OUT1; 1 = PLLP_OUT2; 2 = PLLP_OUT3; 3 = VI_SENSOR_CLK */
        unsigned int i2cp_sel:2;            /* 0 = I2C; 1 = RSVD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int kbca_sel:2;            /* 0 = KBC; 1 = NAND; 2 = SDIO2; 3 = EMC_TEST1_DLL */
        unsigned int kbcb_sel:2;            /* 0 = KBC; 1 = NAND; 2 = SDIO2; 3 = MIO */
        unsigned int kbcc_sel:2;            /* 0 = KBC; 1 = NAND; 2 = TRACE; 3 = EMC_TEST1_DLL */
        unsigned int irtx_sel:2;            /* 0 = UART1; 1 = UART2; 2 = GMI; 3 = SPI4 */
        unsigned int irrx_sel:2;            /* 0 = UART1; 1 = UART2; 2 = GMI; 3 = SPI4 */
        unsigned int dap1_sel:2;            /* 0 = DAP1; 1 = RSVD2; 2 = GMI; 3 = SDIO2 */
        unsigned int dap2_sel:2;            /* 0 = DAP2; 1 = TWC; 2 = RSVD3; 3 = GMI */
        unsigned int dap3_sel:2;            /* 0 = DAP3; 1 = RSVD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int dap4_sel:2;            /* 0 = DAP4; 1 = RSVD2; 2 = GMI; 3 = RSVD4 */
        unsigned int gmb_sel:2;             /* 0 = IDE 1 = NAND 2 = GMI 3 = GMI_INT */
        unsigned int gmd_sel:2;             /* 0 = RSVD1 1 = NAND 2 = GMI 3 = SFLASH */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_c_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_c_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_c_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ddc_sel:2",
              "0 = I2C2;\n1 = RSVD1;\n2 = RSVD2;\n3 = RSVD3",
              2, old_value_t.ddc_sel, new_value_t.ddc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cdev1_sel:2",
              "0 = OSC;\n1 = PLLA_OUT;\n2 = PLLM_OUT1;\n3 = AUDIO_SYNC",
              2, old_value_t.cdev1_sel, new_value_t.cdev1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cdev2_sel:2",
              "0 = OSC;\n1 = AHB_CLK;\n2 = APB_CLK;\n3 = PLLP_OUT4",
              2, old_value_t.cdev2_sel, new_value_t.cdev2_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: csus_sel:2",
              "0 = PLLC_OUT1;\n1 = PLLP_OUT2;\n2 = PLLP_OUT3;\n3 = VI_SENSOR_CLK",
              2, old_value_t.csus_sel, new_value_t.csus_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: i2cp_sel:2",
              "0 = I2C;\n1 = RSVD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.i2cp_sel, new_value_t.i2cp_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: kbca_sel:2",
              "0 = KBC;\n1 = NAND;\n2 = SDIO2;\n3 = EMC_TEST1_DLL",
              2, old_value_t.kbca_sel, new_value_t.kbca_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: kbcb_sel:2",
              "0 = KBC;\n1 = NAND;\n2 = SDIO2;\n3 = MIO",
              2, old_value_t.kbcb_sel, new_value_t.kbcb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: kbcc_sel:2",
              "0 = KBC;\n1 = NAND;\n2 = TRACE;\n3 = EMC_TEST1_DLL",
              2, old_value_t.kbcc_sel, new_value_t.kbcc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: irtx_sel:2",
              "0 = UART1;\n1 = UART2;\n2 = GMI;\n3 = SPI4",
              2, old_value_t.irtx_sel, new_value_t.irtx_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: irrx_sel:2",
              "0 = UART1;\n1 = UART2;\n2 = GMI;\n3 = SPI4",
              2, old_value_t.irrx_sel, new_value_t.irrx_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dap1_sel:2",
              "0 = DAP1;\n1 = RSVD2;\n2 = GMI;\n3 = SDIO2",
              2, old_value_t.dap1_sel, new_value_t.dap1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: dap2_sel:2",
              "0 = DAP2;\n1 = TWC;\n2 = RSVD3;\n3 = GMI",
              2, old_value_t.dap2_sel, new_value_t.dap2_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dap3_sel:2",
              "0 = DAP3;\n1 = RSVD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.dap3_sel, new_value_t.dap3_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "26: dap4_sel:2",
              "0 = DAP4;\n1 = RSVD2;\n2 = GMI;\n3 = RSVD4",
              2, old_value_t.dap4_sel, new_value_t.dap4_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: gmb_sel:2",
              "0 = IDE\n1 = NAND\n2 = GMI\n3 = GMI_INT",
              2, old_value_t.gmb_sel, new_value_t.gmb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: gmd_sel:2",
              "0 = RSVD1\n1 = NAND\n2 = GMI\n3 = SFLASH",
              2, old_value_t.gmd_sel, new_value_t.gmd_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register C";
}

#define PP_PIN_MUX_CTL_D_OFFSET 0x8C
#define PP_PIN_MUX_CTL_D_UNDEFMASK 0x00000000
union pp_pin_mux_ctl_d_u {
    struct {
        unsigned int gme_sel:2;             /* 0 = RSVD1; 1 = DAP5; 2 = GMI; 3 = SDIO4 */
        unsigned int gpv_sel:2;             /* 0 = PCIE; 1 = RSVD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int gpu_sel:2;             /* 0 = PWM; 1 = UART1; 2 = GMI; 3 = RSVD4 */
        unsigned int spdo_sel:2;            /* 0 = SPDIF; 1 = RSVD; 2 = I2C; 3 = SDIO2 */
        unsigned int spdi_sel:2;            /* 0 = SPDIF; 1 = RSVD; 2 = I2C; 3 = SDIO2 */
        unsigned int sdb_sel:2;             /* 0 = UART1; 1 = PWM; 2 = SDIO3; 3 = SPI2 */
        unsigned int sdc_sel:2;             /* 0 = PWM; 1 = TWC; 2 = SDIO3; 3 = SPI3 */
        unsigned int sdd_sel:2;             /* 0 = UART1; 1 = PWM; 2 = SDIO3; 3 = SPI3 */
        unsigned int spih_sel:2;            /* 0 = SPI3; 1 = SPI2; 2 = SPI2_ALT; 3 = I2C */
        unsigned int spig_sel:2;            /* 0 = SPI3; 1 = SPI2; 2 = SPI2_ALT; 3 = I2C */
        unsigned int spif_sel:2;            /* 0 = SPI3; 1 = SPI1; 2 = SPI2; 3 = RSVD */
        unsigned int spie_sel:2;            /* 0 = SPI2; 1 = SPI1; 2 = SPI2_ALT; 3 = GMI */
        unsigned int spid_sel:2;            /* 0 = SPI2; 1 = SPI1; 2 = SPI2_ALT; 3 = GMI */
        unsigned int spic_sel:2;            /* 0 = SPI1; 1 = SPI2; 2 = SPI3; 3 = GMI */
        unsigned int spib_sel:2;            /* 0 = SPI1; 1 = SPI2; 2 = SPI3; 3 = GMI */
        unsigned int spia_sel:2;            /* 0 = SPI1; 1 = SPI2; 2 = SPI3; 3 = GMI */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_d_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_d_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_d_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gme_sel:2",
              "0 = RSVD1;\n1 = DAP5;\n2 = GMI;\n3 = SDIO4",
              2, old_value_t.gme_sel, new_value_t.gme_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gpv_sel:2",
              "0 = PCIE;\n1 = RSVD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.gpv_sel, new_value_t.gpv_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: gpu_sel:2",
              "0 = PWM;\n1 = UART1;\n2 = GMI;\n3 = RSVD4",
              2, old_value_t.gpu_sel, new_value_t.gpu_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: spdo_sel:2",
              "0 = SPDIF;\n1 = RSVD;\n2 = I2C;\n3 = SDIO2",
              2, old_value_t.spdo_sel, new_value_t.spdo_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: spdi_sel:2",
              "0 = SPDIF;\n1 = RSVD;\n2 = I2C;\n3 = SDIO2",
              2, old_value_t.spdi_sel, new_value_t.spdi_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: sdb_sel:2",
              "0 = UART1;\n1 = PWM;\n2 = SDIO3;\n3 = SPI2",
              2, old_value_t.sdb_sel, new_value_t.sdb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: sdc_sel:2",
              "0 = PWM;\n1 = TWC;\n2 = SDIO3;\n3 = SPI3",
              2, old_value_t.sdc_sel, new_value_t.sdc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: sdd_sel:2",
              "0 = UART1;\n1 = PWM;\n2 = SDIO3;\n3 = SPI3",
              2, old_value_t.sdd_sel, new_value_t.sdd_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spih_sel:2",
              "0 = SPI3;\n1 = SPI2;\n2 = SPI2_ALT;\n3 = I2C",
              2, old_value_t.spih_sel, new_value_t.spih_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: spig_sel:2",
              "0 = SPI3;\n1 = SPI2;\n2 = SPI2_ALT;\n3 = I2C",
              2, old_value_t.spig_sel, new_value_t.spig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: spif_sel:2",
              "0 = SPI3;\n1 = SPI1;\n2 = SPI2;\n3 = RSVD",
              2, old_value_t.spif_sel, new_value_t.spif_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: spie_sel:2",
              "0 = SPI2;\n1 = SPI1;\n2 = SPI2_ALT;\n3 = GMI",
              2, old_value_t.spie_sel, new_value_t.spie_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: spid_sel:2",
              "0 = SPI2;\n1 = SPI1;\n2 = SPI2_ALT;\n3 = GMI",
              2, old_value_t.spid_sel, new_value_t.spid_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "26: spic_sel:2",
              "0 = SPI1;\n1 = SPI2;\n2 = SPI3;\n3 = GMI",
              2, old_value_t.spic_sel, new_value_t.spic_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: spib_sel:2",
              "0 = SPI1;\n1 = SPI2;\n2 = SPI3;\n3 = GMI",
              2, old_value_t.spib_sel, new_value_t.spib_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spia_sel:2",
              "0 = SPI1;\n1 = SPI2;\n2 = SPI3;\n3 = GMI",
              2, old_value_t.spia_sel, new_value_t.spia_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register D";
}

#define PP_PIN_MUX_CTL_E_OFFSET 0x90
#define PP_PIN_MUX_CTL_E_UNDEFMASK 0x00000000
union pp_pin_mux_ctl_e_u {
    struct {
        unsigned int lpw0_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = HDMI */
        unsigned int lpw1_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD; 3 = RSVD4 */
        unsigned int lpw2_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = HDMI */
        unsigned int lsdi_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = RSVD */
        unsigned int lsda_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = HDMI */
        unsigned int lspi_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = HDMI */
        unsigned int lcsn_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = RSVD4 */
        unsigned int ldc_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = RSVD; 3 = RSVD4 */
        unsigned int lsck_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = HDMI */
        unsigned int lsc0_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int lsc1_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = HDMI */
        unsigned int lhs_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int lvs_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int lm0_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = SPI3; 3 = RSVD */
        unsigned int lm1_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = CRT */
        unsigned int lvp0_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_e_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_e_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_e_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: lpw0_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = HDMI",
              2, old_value_t.lpw0_sel, new_value_t.lpw0_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: lpw1_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD;\n3 = RSVD4",
              2, old_value_t.lpw1_sel, new_value_t.lpw1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: lpw2_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = HDMI",
              2, old_value_t.lpw2_sel, new_value_t.lpw2_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: lsdi_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = RSVD",
              2, old_value_t.lsdi_sel, new_value_t.lsdi_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: lsda_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = HDMI",
              2, old_value_t.lsda_sel, new_value_t.lsda_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: lspi_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = HDMI",
              2, old_value_t.lspi_sel, new_value_t.lspi_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: lcsn_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = RSVD4",
              2, old_value_t.lcsn_sel, new_value_t.lcsn_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ldc_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD;\n3 = RSVD4",
              2, old_value_t.ldc_sel, new_value_t.ldc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: lsck_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = HDMI",
              2, old_value_t.lsck_sel, new_value_t.lsck_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: lsc0_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.lsc0_sel, new_value_t.lsc0_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: lsc1_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = HDMI",
              2, old_value_t.lsc1_sel, new_value_t.lsc1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: lhs_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.lhs_sel, new_value_t.lhs_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: lvs_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.lvs_sel, new_value_t.lvs_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "26: lm0_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = SPI3;\n3 = RSVD",
              2, old_value_t.lm0_sel, new_value_t.lm0_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: lm1_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = CRT",
              2, old_value_t.lm1_sel, new_value_t.lm1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: lvp0_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD",
              2, old_value_t.lvp0_sel, new_value_t.lvp0_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register E";
}

#define PP_PIN_MUX_CTL_F_OFFSET 0x94
#define PP_PIN_MUX_CTL_F_UNDEFMASK 0x00000000
union pp_pin_mux_ctl_f_u {
    struct {
        unsigned int ld0_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld1_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld2_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld3_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld4_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld5_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld6_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld7_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld8_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld9_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld10_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld11_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld12_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld13_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld14_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld15_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_f_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_f_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_f_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ld0_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld0_sel, new_value_t.ld0_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ld1_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld1_sel, new_value_t.ld1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ld2_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld2_sel, new_value_t.ld2_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ld3_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld3_sel, new_value_t.ld3_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ld4_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld4_sel, new_value_t.ld4_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ld5_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld5_sel, new_value_t.ld5_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ld6_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld6_sel, new_value_t.ld6_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ld7_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld7_sel, new_value_t.ld7_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ld8_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld8_sel, new_value_t.ld8_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ld9_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld9_sel, new_value_t.ld9_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: ld10_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld10_sel, new_value_t.ld10_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: ld11_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld11_sel, new_value_t.ld11_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ld12_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld12_sel, new_value_t.ld12_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ld13_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld13_sel, new_value_t.ld13_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ld14_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld14_sel, new_value_t.ld14_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ld15_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld15_sel, new_value_t.ld15_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register F";
}

#define PP_PIN_MUX_CTL_G_OFFSET 0x98
#define PP_PIN_MUX_CTL_G_UNDEFMASK 0x03003000
union pp_pin_mux_ctl_g_u {
    struct {
        unsigned int ld16_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = XIO; 3 = RSVD */
        unsigned int ld17_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD; 3 = RSVD */
        unsigned int lhp1_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD */
        unsigned int lhp2_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int lvp1_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int lhp0_sel:2;            /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD4 */
        unsigned int undefined_bits_12_13:2;
        unsigned int lpp_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD */
        unsigned int ldi_sel:2;             /* 0 = LCD1; 1 = LCD2; 2 = RSVD3; 3 = RSVD */
        unsigned int pmc_sel:2;             /* 0 = PWR_ON; 1 = PWR_INTR */
        unsigned int crtp_sel:2;            /* 0 = CRT 1 = RSVD2 2 = RSVD3 3 = RSVD4 */
        unsigned int pta_sel:2;             /* 0 = I2C2; 1 = HDMI; 2 = GMI; 3 = RSVD3 */
        unsigned int undefined_bits_24_25:2;
        unsigned int kbcd_sel:2;            /* 0 = KBC; 1 = NAND; 2 = SDIO2; 3 = MIO */
        unsigned int gpu7_sel:2;            /* 0 = RTCK; 1 = RSVD1; 2 = RSVD2; 3 = RSVD3 */
        unsigned int dtf_sel:2;             /* 0 = I2C3; 1 = RSVD2; 2 = VI; 3 = RSVD4 */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_g_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_g_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_g_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ld16_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = XIO;\n3 = RSVD",
              2, old_value_t.ld16_sel, new_value_t.ld16_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ld17_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD;\n3 = RSVD",
              2, old_value_t.ld17_sel, new_value_t.ld17_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: lhp1_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD",
              2, old_value_t.lhp1_sel, new_value_t.lhp1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: lhp2_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.lhp2_sel, new_value_t.lhp2_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: lvp1_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.lvp1_sel, new_value_t.lvp1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: lhp0_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD4",
              2, old_value_t.lhp0_sel, new_value_t.lhp0_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_13:2", "", 2, old_value_t.undefined_bits_12_13, new_value_t.undefined_bits_12_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: lpp_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD",
              2, old_value_t.lpp_sel, new_value_t.lpp_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ldi_sel:2",
              "0 = LCD1;\n1 = LCD2;\n2 = RSVD3;\n3 = RSVD",
              2, old_value_t.ldi_sel, new_value_t.ldi_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pmc_sel:2",
              "0 = PWR_ON;\n1 = PWR_INTR",
              2, old_value_t.pmc_sel, new_value_t.pmc_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: crtp_sel:2",
              "0 = CRT\n1 = RSVD2\n2 = RSVD3\n3 = RSVD4",
              2, old_value_t.crtp_sel, new_value_t.crtp_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pta_sel:2",
              "0 = I2C2;\n1 = HDMI;\n2 = GMI;\n3 = RSVD3",
              2, old_value_t.pta_sel, new_value_t.pta_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_25:2", "", 2, old_value_t.undefined_bits_24_25, new_value_t.undefined_bits_24_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: kbcd_sel:2",
              "0 = KBC;\n1 = NAND;\n2 = SDIO2;\n3 = MIO",
              2, old_value_t.kbcd_sel, new_value_t.kbcd_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: gpu7_sel:2",
              "0 = RTCK;\n1 = RSVD1;\n2 = RSVD2;\n3 = RSVD3",
              2, old_value_t.gpu7_sel, new_value_t.gpu7_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dtf_sel:2",
              "0 = I2C3;\n1 = RSVD2;\n2 = VI;\n3 = RSVD4",
              2, old_value_t.dtf_sel, new_value_t.dtf_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register G";
}

#define PP_PIN_MUX_CTL_H_OFFSET 0x9C
#define PP_PIN_MUX_CTL_H_UNDEFMASK 0xFFC00000
union pp_pin_mux_ctl_h_u {
    struct {
        unsigned int dap1_cntrl_mux_select:3;/* 0 = DAC1 1 = DAC2 2 = DAC3 3 = RSVD1 4 = RSVD2 5 = DAP2 6 = DAP3 7 = DAP4 */
        unsigned int dap2_cntrl_mux_select:3;/* 0 = DAC1 1 = DAC2 2 = DAC3 3 = RSVD1 4 = DAP1 5 = RSVD2 6 = DAP3 7 = DAP4 */
        unsigned int dap3_cntrl_mux_select:3;/* 0 = DAC1 1 = DAC2 2 = DAC3 3 = RSVD1 4 = DAP1 5 = DAP2 6 = RSVD2 7 = DAP4 */
        unsigned int dap4_cntrl_mux_select:3;/* 0 = DAC1 1 = DAC2 2 = DAC3 3 = RSVD 4 = DAP1 5 = DAP2 6 = DAP3 7 = RSVD2 */
        unsigned int dac1_sel:2;            /* 0 = DAP1 1 = DAP2 2 = DAP3 3 = DAP4 */
        unsigned int dac2_sel:2;            /* 0 = DAP1 1 = DAP2 2 = DAP3 3 = DAP4 */
        unsigned int dac3_sel:2;            /* 0 = DAP1 1 = DAP2 2 = DAP3 3 = DAP4 */
        unsigned int dap1m_sel:1;           /* 0 = DAP1_SLAVE 1 = DAP1_MASTER */
        unsigned int dap2m_sel:1;           /* 0 = DAP2_SLAVE 1 = DAP2_MASTER */
        unsigned int dap3m_sel:1;           /* 0 = DAP3_SLAVE 1 = DAP3_MASTER */
        unsigned int dap4m_sel:1;           /* 0 = DAP4_SLAVE 1 = DAP4_MASTER */
        unsigned int undefined_bits_22_31:10;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pin_mux_ctl_h_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pin_mux_ctl_h_u old_value_t = { .reg32 = value };
    const pp_pin_mux_ctl_h_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dap1_cntrl_mux_select:3",
              "0 = DAC1\n1 = DAC2\n2 = DAC3\n3 = RSVD1\n4 = RSVD2\n5 = DAP2\n6 = DAP3\n7 = DAP4",
              3, old_value_t.dap1_cntrl_mux_select, new_value_t.dap1_cntrl_mux_select };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dap2_cntrl_mux_select:3",
              "0 = DAC1\n1 = DAC2\n2 = DAC3\n3 = RSVD1\n4 = DAP1\n5 = RSVD2\n6 = DAP3\n7 = DAP4",
              3, old_value_t.dap2_cntrl_mux_select, new_value_t.dap2_cntrl_mux_select };
    m_bit_details_model.bits.append(entry);
    entry = { "06: dap3_cntrl_mux_select:3",
              "0 = DAC1\n1 = DAC2\n2 = DAC3\n3 = RSVD1\n4 = DAP1\n5 = DAP2\n6 = RSVD2\n7 = DAP4",
              3, old_value_t.dap3_cntrl_mux_select, new_value_t.dap3_cntrl_mux_select };
    m_bit_details_model.bits.append(entry);
    entry = { "09: dap4_cntrl_mux_select:3",
              "0 = DAC1\n1 = DAC2\n2 = DAC3\n3 = RSVD\n4 = DAP1\n5 = DAP2\n6 = DAP3\n7 = RSVD2",
              3, old_value_t.dap4_cntrl_mux_select, new_value_t.dap4_cntrl_mux_select };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dac1_sel:2",
              "0 = DAP1\n1 = DAP2\n2 = DAP3\n3 = DAP4",
              2, old_value_t.dac1_sel, new_value_t.dac1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "14: dac2_sel:2",
              "0 = DAP1\n1 = DAP2\n2 = DAP3\n3 = DAP4",
              2, old_value_t.dac2_sel, new_value_t.dac2_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dac3_sel:2",
              "0 = DAP1\n1 = DAP2\n2 = DAP3\n3 = DAP4",
              2, old_value_t.dac3_sel, new_value_t.dac3_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: dap1m_sel:1",
              "0 = DAP1_SLAVE\n1 = DAP1_MASTER",
              1, old_value_t.dap1m_sel, new_value_t.dap1m_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dap2m_sel:1",
              "0 = DAP2_SLAVE\n1 = DAP2_MASTER",
              1, old_value_t.dap2m_sel, new_value_t.dap2m_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dap3m_sel:1",
              "0 = DAP3_SLAVE\n1 = DAP3_MASTER",
              1, old_value_t.dap3m_sel, new_value_t.dap3m_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "21: dap4m_sel:1",
              "0 = DAP4_SLAVE\n1 = DAP4_MASTER",
              1, old_value_t.dap4m_sel, new_value_t.dap4m_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_31:10", "", 10, old_value_t.undefined_bits_22_31, new_value_t.undefined_bits_22_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PIN Multiplex Control Register H. This register is used for DAP-DAC selections.";
}

#define PP_PULLUPDOWN_REG_A_OFFSET 0xA0
#define PP_PULLUPDOWN_REG_A_UNDEFMASK 0x00000000
union pp_pullupdown_reg_a_u {
    struct {
        unsigned int ata_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int atb_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int atc_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int atd_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ate_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dap1_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dap2_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dap3_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dap4_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dta_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dtb_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dtc_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dtd_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dte_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int dtf_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int gpv_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pullupdown_reg_a_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pullupdown_reg_a_u old_value_t = { .reg32 = value };
    const pp_pullupdown_reg_a_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ata_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ata_pu_pd, new_value_t.ata_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: atb_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.atb_pu_pd, new_value_t.atb_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: atc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.atc_pu_pd, new_value_t.atc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: atd_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.atd_pu_pd, new_value_t.atd_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ate_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ate_pu_pd, new_value_t.ate_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "10: dap1_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dap1_pu_pd, new_value_t.dap1_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dap2_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dap2_pu_pd, new_value_t.dap2_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "14: dap3_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dap3_pu_pd, new_value_t.dap3_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dap4_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dap4_pu_pd, new_value_t.dap4_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "18: dta_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dta_pu_pd, new_value_t.dta_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dtb_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dtb_pu_pd, new_value_t.dtb_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "22: dtc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dtc_pu_pd, new_value_t.dtc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dtd_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dtd_pu_pd, new_value_t.dtd_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "26: dte_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dte_pu_pd, new_value_t.dte_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dtf_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.dtf_pu_pd, new_value_t.dtf_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "30: gpv_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.gpv_pu_pd, new_value_t.gpv_pu_pd };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PULL_UP/PULL_DOWN Control Register\nTable 41. Cross Reference of Fields with Ball Names (REG A)\nField Name\n Controls Balls\nGPV_PU_PD\n GPIO_PV[6:4]\nDTF_PU_PD\n CAM_I2C_SCK, CAM_I2C_SDA\nDTE_PU_PD\n VI_GP0, VI_GP[6:3]\nDTD_PU_PD\n VI_PCLK, VI_D[9:2]\nDTC_PU_PD\n VI_VSYNC, VI_HSYNC\nDTB_PU_PD\n VID_D[11:10]\nDTA_PU_PD\n VID_D[1:0]\nDAP4_PU_PD\n DAP4_FS, DAP4_DIN, DAP4_DOUT, DAP4_SCLK\nDAP3_PU_PD\n DAP3_FS, DAP3_DIN, DAP3_DOUT, DAP3_SCLK\nDAP2_PU_PD\n DAP2_FS, DAP2_DIN, DAP2_DOUT, DAP2_SCLK\nDAP1_PU_PD\n DAP1_FS, DAP1_DIN, DAP1_DOUT, DAP1_SCLK\nATE_PU_PD\n GMI_AD15, GMI_AD14, GMI_AD13, GMI_AD12GMI_AD[15:12]\nATD_PU_PD\n GMI_AD11, GMI_AD 10, GMI_AD 9, GMI_AD [11:8]\nATC_PU_PD\n GMI_IORDY, GMI_WAIT, GMI_CS4ADV_N, GMI_CS3CLK, GMI_CS2CS[4:2]_N, GMI_AD00,AD[7:0], GMI_AD01WR_N, GMI_AD02, GMI_AD03 OE_N\nATB_PU_PD\n GMI_CS5_N, GMI_DPD\nField Name\n Controls Balls\nATA_PU_PD\n GMI_CS6, GMI_CS7CS[7:6]_N, GMI_RST_N";
}

#define PP_PULLUPDOWN_REG_B_OFFSET 0xA4
#define PP_PULLUPDOWN_REG_B_UNDEFMASK 0x00000000
union pp_pullupdown_reg_b_u {
    struct {
        unsigned int rm_pu_pd:2;            /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int i2cp_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int pta_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int gpu7_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int kbca_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int kbcb_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int kbcc_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int kbcd_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spdi_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_U; 3 = RSVD */
        unsigned int spdo_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int gpu_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int slxa_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int crtp_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int slxc_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int slxd_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int slxk_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pullupdown_reg_b_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pullupdown_reg_b_u old_value_t = { .reg32 = value };
    const pp_pullupdown_reg_b_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rm_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.rm_pu_pd, new_value_t.rm_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: i2cp_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.i2cp_pu_pd, new_value_t.i2cp_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pta_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.pta_pu_pd, new_value_t.pta_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: gpu7_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.gpu7_pu_pd, new_value_t.gpu7_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "08: kbca_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.kbca_pu_pd, new_value_t.kbca_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "10: kbcb_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.kbcb_pu_pd, new_value_t.kbcb_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "12: kbcc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.kbcc_pu_pd, new_value_t.kbcc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "14: kbcd_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.kbcd_pu_pd, new_value_t.kbcd_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spdi_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_U;\n3 = RSVD",
              2, old_value_t.spdi_pu_pd, new_value_t.spdi_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "18: spdo_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spdo_pu_pd, new_value_t.spdo_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "20: gpu_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.gpu_pu_pd, new_value_t.gpu_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "22: slxa_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.slxa_pu_pd, new_value_t.slxa_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: crtp_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.crtp_pu_pd, new_value_t.crtp_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "26: slxc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.slxc_pu_pd, new_value_t.slxc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "28: slxd_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.slxd_pu_pd, new_value_t.slxd_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "30: slxk_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.slxk_pu_pd, new_value_t.slxk_pu_pd };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PULL_UP/PULL_DOWN Control Register\nTable 42. Cross Reference of Fields with Ball Names (REG B)\nField Name\n Controls Balls\nSLXK_PU_PD\n SDIO2_CLK\nSLXD_PU_PD\n SDIO2_DAT3\nSLXC_PU_PD\n SDIO2_DAT2\nSLXB_PU_PD\n SDIO2_DAT1\nSLXA_PU_PD\n SDIO2_DAT0\nGPU_PU_PD\n GPIO_PU[6:0]\nSPDO_PU_PD\n SPDIF_OUT\nSPDI_PU_PD\n SPDIF_IN\nKBCD_PU_PD\n KB_ROW[6:4]\nKBCC_PU_PD\n KB_COL[2:0]\nKBCB_PU_PD\n KB_ROW[12:7]\nKBCA_PU_PD\n KB_ROW[2:0]\nGPU7_PU_PD\n GPIO_PU7\nPTA_PU_PD\n GEN_I2C_SCL (GEN2_I2C_CLK), GEN_I2C_SDA (SCL, GEN2_I2C_DAT)SDA\nI2CP_PU_PD\n PWR_I2C_SCL, PWR_I2C_SDA\nRM_PU_PD\n GEN1_I2C_SDA, GEN1_I2C_SCL";
}

#define PP_PULLUPDOWN_REG_C_OFFSET 0xA8
#define PP_PULLUPDOWN_REG_C_UNDEFMASK 0x0C000000
union pp_pullupdown_reg_c_u {
    struct {
        unsigned int cdev1_pu_pd:2;         /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int cdev2_pu_pd:2;         /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spia_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spib_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spic_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spid_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spie_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spif_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spig_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int spih_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int irtx_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int irrx_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int gme_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int undefined_bits_26_27:2;
        unsigned int xm2d_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int xm2c_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pullupdown_reg_c_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pullupdown_reg_c_u old_value_t = { .reg32 = value };
    const pp_pullupdown_reg_c_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cdev1_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.cdev1_pu_pd, new_value_t.cdev1_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cdev2_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.cdev2_pu_pd, new_value_t.cdev2_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: spia_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spia_pu_pd, new_value_t.spia_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: spib_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spib_pu_pd, new_value_t.spib_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "08: spic_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spic_pu_pd, new_value_t.spic_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "10: spid_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spid_pu_pd, new_value_t.spid_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "12: spie_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spie_pu_pd, new_value_t.spie_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "14: spif_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spif_pu_pd, new_value_t.spif_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spig_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spig_pu_pd, new_value_t.spig_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "18: spih_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.spih_pu_pd, new_value_t.spih_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "20: irtx_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.irtx_pu_pd, new_value_t.irtx_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "22: irrx_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.irrx_pu_pd, new_value_t.irrx_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: gme_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.gme_pu_pd, new_value_t.gme_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_27:2", "", 2, old_value_t.undefined_bits_26_27, new_value_t.undefined_bits_26_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: xm2d_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.xm2d_pu_pd, new_value_t.xm2d_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "30: xm2c_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.xm2c_pu_pd, new_value_t.xm2c_pu_pd };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PULL_UP/PULL_DOWN Control Register\nTable 43. Cross Reference of Fields with Ball Names (REG C)\nField Name\n Controls Balls\nXM2D_PU_PD\n DDR_DQ[31:0]\nXM2C_PU_PD\n DDR_DQS[2:0]P, DDR_DQS[2:0]N, DDR_DM[3:0], DDR_A[14:0], DDR_BA[2:0], DDR_CKE[1:0], DDR_ODT, DDR_RAS_N, DDR_CAS_N, DDR_WE_N, DDR_CLK, DDR_CLK_N, DDR_QUSE[3:0]\nGME_PU_PD\n GMI_AD[27:24]\nIRRX_PU_PD\n UART2_RTS_N\nIRTX_PU_PD\n UART2_CTS_N\nSPIH_PU_PD\n SPI2_CS2_N\nSPIG_PU_PD\n SPI2_CS1_N\nField Name\n Controls Balls\nSPIF_PU_PD\n SPI1_MISO\nSPIE_PU_PD\n SPI1_SCK, SPI1_CS0_N\nSPID_PU_PD\n SPI1_MOSI\nSPIC_PU_PD\n SPI2_SCK, SPI2_CS0_N\nSPIB_PU_PD\n SPI2_MISO\nSPIA_PU_PD\n SPI2_MOSI\nCDEV2_PU_PD\n DAP_MCLK2\nCDEV1_PU_PD\n DAP_MCLK1";
}

#define PP_PULLUPDOWN_REG_D_OFFSET 0xAC
#define PP_PULLUPDOWN_REG_D_UNDEFMASK 0x00000000
union pp_pullupdown_reg_d_u {
    struct {
        unsigned int uaa_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int uab_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int uac_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int uad_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int uca_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ucb_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ld17_0_pu_pd:2;        /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ld19_18_pu_pd:2;       /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ld21_20_pu_pd:2;       /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ld23_22_pu_pd:2;       /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ls_pu_pd:2;            /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int lc_pu_pd:2;            /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int csus_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int ddrc_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int sdc_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int sdd_pu_pd:2;           /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pullupdown_reg_d_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pullupdown_reg_d_u old_value_t = { .reg32 = value };
    const pp_pullupdown_reg_d_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: uaa_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.uaa_pu_pd, new_value_t.uaa_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: uab_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.uab_pu_pd, new_value_t.uab_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: uac_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.uac_pu_pd, new_value_t.uac_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: uad_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.uad_pu_pd, new_value_t.uad_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "08: uca_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.uca_pu_pd, new_value_t.uca_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ucb_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ucb_pu_pd, new_value_t.ucb_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ld17_0_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ld17_0_pu_pd, new_value_t.ld17_0_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ld19_18_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ld19_18_pu_pd, new_value_t.ld19_18_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ld21_20_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ld21_20_pu_pd, new_value_t.ld21_20_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ld23_22_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ld23_22_pu_pd, new_value_t.ld23_22_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "20: ls_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ls_pu_pd, new_value_t.ls_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "22: lc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.lc_pu_pd, new_value_t.lc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: csus_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.csus_pu_pd, new_value_t.csus_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ddrc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.ddrc_pu_pd, new_value_t.ddrc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "28: sdc_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.sdc_pu_pd, new_value_t.sdc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sdd_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.sdd_pu_pd, new_value_t.sdd_pu_pd };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PULL_UP/PULL_DOWN Control Register\nTable 44. Cross Reference of Fields with Ball Names (REG D)\nField Name\n Controls Balls\nSDD_PU_PD\n SDIO3_CLK,SDIO3_CMD\nSDC_PU_PD\n SDIO3_DAT[3:0]\nSDB_PU_PD\n SDIO2_CMD\nCSUS_PU_PD\n VI_MCLK\nLC_PU_PD\n LCD_PCLK, LCD_DE, LCD_HSYNC, LCD_VSYNC, LCD_CS1_N, LCD_M1, LCD_DC1, HDMI_INT\nLS_PU_PD\n LCD_PWR1, LCD_PWR2, LCD_SDIN, LCD_SDOUT, LCD_WR_N, LCD_CS0_N, LCD_DC0, LCD_SCK, LCD_PWR0\nLD23_22_PU_PD\n LCD_D[23:22]\nLD21_20_PU_PD\n LCD_D[21:20]\nLD19_18_PU_PD\n LCD_D[19:18]\nLD17_0_PU_PD\n LCD_D[17:0]\nUCB_PU_PD\n UART3_RTS_N, UART3_CTS_N\nUCA_PU_PD\n UART3_TXD,UART3_RXD\nUAD_PU_PD\n UART2_TXD,UART2_RXD\nUAC_PU_PD\n GPIO_PV[3:0]\nUAB_PU_PD\n UART1_RI_,UART1_DCD_,UART1_DSR_,UART1_DTR_\nUAA_PU_PD\n UART1_TXD,UART1_RXD,UART1_CTS_,UART1_RTS";
}

#define PP_PULLUPDOWN_REG_E_OFFSET 0xB0
#define PP_PULLUPDOWN_REG_E_UNDEFMASK 0x00000000
union pp_pullupdown_reg_e_u {
    struct {
        unsigned int kbcf_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int kbce_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int pmca_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int pmcb_pu_pd:2;          /* 0 = NORMAL; 1 = PULL_DOWN; 2 = PULL_UP; 3 = RSVD */
        unsigned int pmcc_pu_pd:2;          /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int pmcd_pu_pd:2;          /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int pmce_pu_pd:2;          /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int ck32_pu_pd:2;          /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int uda_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int sdio1_pu_pd:2;         /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int gma_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int gmb_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int gmc_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int gmd_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int ddc_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
        unsigned int owc_pu_pd:2;           /* 0 = NORMAL 1 = PULL_DOWN 2 = PULL_UP 3 = RSVD */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_pullupdown_reg_e_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_pullupdown_reg_e_u old_value_t = { .reg32 = value };
    const pp_pullupdown_reg_e_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: kbcf_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.kbcf_pu_pd, new_value_t.kbcf_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: kbce_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.kbce_pu_pd, new_value_t.kbce_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pmca_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.pmca_pu_pd, new_value_t.pmca_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: pmcb_pu_pd:2",
              "0 = NORMAL;\n1 = PULL_DOWN;\n2 = PULL_UP;\n3 = RSVD",
              2, old_value_t.pmcb_pu_pd, new_value_t.pmcb_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pmcc_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.pmcc_pu_pd, new_value_t.pmcc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "10: pmcd_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.pmcd_pu_pd, new_value_t.pmcd_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pmce_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.pmce_pu_pd, new_value_t.pmce_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "14: ck32_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.ck32_pu_pd, new_value_t.ck32_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "16: uda_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.uda_pu_pd, new_value_t.uda_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "18: sdio1_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.sdio1_pu_pd, new_value_t.sdio1_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "20: gma_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.gma_pu_pd, new_value_t.gma_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "22: gmb_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.gmb_pu_pd, new_value_t.gmb_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: gmc_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.gmc_pu_pd, new_value_t.gmc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "26: gmd_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.gmd_pu_pd, new_value_t.gmd_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ddc_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.ddc_pu_pd, new_value_t.ddc_pu_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owc_pu_pd:2",
              "0 = NORMAL\n1 = PULL_DOWN\n2 = PULL_UP\n3 = RSVD",
              2, old_value_t.owc_pu_pd, new_value_t.owc_pu_pd };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Table 45. Cross Reference of Fields with Ball Names (REG E)\nField Name\n Controls Balls\nOWC_PU_PD\n OWR\nDDC_PU_PD\n DDC_SCL, DDC_SDA\nGMD_PU_PD\n GMI_CS[1:0]_N\nGMC_PU_PD\n GMI_AD[19:16]\nGMB_PU_PD\n GMI_WP_N\nGMA_PU_PD\n GMI_AD[23:20]\nSDIO1_PU_PD\n SDIO1_CLK, SDIO1_CMD, SDIO1_DAT[3:0]\nField Name\n Controls Balls\nUDA_PU_PD\n ULPI_CLK, ULPI_DIR, ULPI_NXT, ULPI_STP\nCK32_PU_PD\n CLK_32K_IN\nPMCE_PU_PD\n PWR_INT_N\nPMCD_PU_PD\n CPU_PWR_REQ\nPMCC_PU_PD\n CORE_PWR_REQ\nPMCB_PU_PD\n SYS_CLK_REQ\nPMCA_PU_PD\n CLK_32K_OUT\nKBCE_PU_PD\n KB_COL7\nKBCF_PU_PD\n KB_COL[6:2]";
}

#define PP_MISC_USB_CLK_RST_CTL_OFFSET 0xB4
#define PP_MISC_USB_CLK_RST_CTL_UNDEFMASK 0xFFFFFCF8
union pp_misc_usb_clk_rst_ctl_u {
    struct {
        unsigned int misc_usb_ce:1;         /* enable clocks to USB controller; 0 = DISABLE; 1 = ENABLE */
        unsigned int misc_usb2_ce:1;        /* enable clocks to USB2 controller; 0 = DISABLE; 1 = ENABLE */
        unsigned int misc_usb2_clk_ovr_on:1;/* Clock override for USB2 controller; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_3_7:5;
        unsigned int misc_usb_rst:1;        /* Reset (active high) for USB controller; 0 = DISABLE; 1 = ENABLE */
        unsigned int misc_usb2_rst:1;       /* Reset (active high) for USB2 controller; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_misc_usb_clk_rst_ctl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_misc_usb_clk_rst_ctl_u old_value_t = { .reg32 = value };
    const pp_misc_usb_clk_rst_ctl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: misc_usb_ce:1",
              "enable clocks to USB controller;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.misc_usb_ce, new_value_t.misc_usb_ce };
    m_bit_details_model.bits.append(entry);
    entry = { "01: misc_usb2_ce:1",
              "enable clocks to USB2 controller;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.misc_usb2_ce, new_value_t.misc_usb2_ce };
    m_bit_details_model.bits.append(entry);
    entry = { "02: misc_usb2_clk_ovr_on:1",
              "Clock override for USB2 controller;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.misc_usb2_clk_ovr_on, new_value_t.misc_usb2_clk_ovr_on };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: misc_usb_rst:1",
              "Reset (active high) for USB controller;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.misc_usb_rst, new_value_t.misc_usb_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: misc_usb2_rst:1",
              "Reset (active high) for USB2 controller;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.misc_usb2_rst, new_value_t.misc_usb2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register controls the clocks and resets going to USB and USB2 controllers.\nUSB and USB2 Clock and Reset Register";
}

#define GP_MODEREG_OFFSET 0x800
#define GP_MODEREG_UNDEFMASK 0xFFFFFCFE
union gp_modereg_u {
    struct {
        unsigned int standby_ie:1;          /* Standby pad input 1 = STANDBYN is asserted (low voltage), 0 = STANDBYN is deasserted (high voltage) 0 = DEASSERTED 1 = ASSERTED */
        unsigned int undefined_bits_1_7:7;
        unsigned int lpddr_strap0:1;        /* LP-DDR Strap option bit 0 */
        unsigned int lpddr_strap1:1;        /* LP-DDR Strap option bit 1 */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_modereg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_modereg_u old_value_t = { .reg32 = value };
    const gp_modereg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: standby_ie:1",
              "Standby pad input\n1 = STANDBYN is asserted (low voltage),\n0 = STANDBYN is deasserted (high voltage)\n0 = DEASSERTED\n1 = ASSERTED",
              1, old_value_t.standby_ie, new_value_t.standby_ie };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_7:7", "", 7, old_value_t.undefined_bits_1_7, new_value_t.undefined_bits_1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: lpddr_strap0:1",
              "LP-DDR Strap option bit 0",
              1, old_value_t.lpddr_strap0, new_value_t.lpddr_strap0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: lpddr_strap1:1",
              "LP-DDR Strap option bit 1",
              1, old_value_t.lpddr_strap1, new_value_t.lpddr_strap1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);
}

#define GP_HIDREV_OFFSET 0x804
#define GP_HIDREV_UNDEFMASK 0xFFF00000
union gp_hidrev_u {
    struct {
        unsigned int hidfam:4;              /* Chip ID family register; 7 = NVIDIA Mobile Applications Processor */
        unsigned int majorrev:4;            /* Chip ID major revision (0: Emulation, 1-15: Silicon) 0 = EMULATION 1 = A01 */
        unsigned int chipid:8;              /* Chip ID */
        unsigned int minorrev:4;            /* Chip ID minor revision (IF MAJORREV==0(Emulation) THEN 0: QT, 1:E388 FPGA) */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_hidrev_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_hidrev_u old_value_t = { .reg32 = value };
    const gp_hidrev_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hidfam:4",
              "Chip ID family register;\n7 = NVIDIA Mobile Applications Processor",
              4, old_value_t.hidfam, new_value_t.hidfam };
    m_bit_details_model.bits.append(entry);
    entry = { "04: majorrev:4",
              "Chip ID major revision (0: Emulation, 1-15: Silicon)\n0 = EMULATION\n1 = A01",
              4, old_value_t.majorrev, new_value_t.majorrev };
    m_bit_details_model.bits.append(entry);
    entry = { "08: chipid:8",
              "Chip ID",
              8, old_value_t.chipid, new_value_t.chipid };
    m_bit_details_model.bits.append(entry);
    entry = { "16: minorrev:4",
              "Chip ID minor revision (IF MAJORREV==0(Emulation) THEN 0: QT, 1:E388 FPGA)",
              4, old_value_t.minorrev, new_value_t.minorrev };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Chip ID Revision Register";
}

#define GP_EMU_REVID_OFFSET 0x860
#define GP_EMU_REVID_UNDEFMASK 0x00000000
union gp_emu_revid_u {
    struct {
        unsigned int netlist:16;            /* USED by emulators to indicate netlist #, 0 for silicon */
        unsigned int patch:16;              /* USED by emulators to indicate patch #, 0 for silicon */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_emu_revid_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_emu_revid_u old_value_t = { .reg32 = value };
    const gp_emu_revid_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: netlist:16",
              "USED by emulators to indicate netlist #, 0 for silicon",
              16, old_value_t.netlist, new_value_t.netlist };
    m_bit_details_model.bits.append(entry);
    entry = { "16: patch:16",
              "USED by emulators to indicate patch #, 0 for silicon",
              16, old_value_t.patch, new_value_t.patch };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "EMULATION SCRATCH REGISTERS";
}

#define GP_TRANSACTOR_SCRATCH_OFFSET 0x864
#define GP_TRANSACTOR_SCRATCH_UNDEFMASK 0x00000000
union gp_transactor_scratch_u {
    struct {
        unsigned int transactor_scratch:32; /* used for emulation to determine test results */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_transactor_scratch_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_transactor_scratch_u old_value_t = { .reg32 = value };
    const gp_transactor_scratch_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: transactor_scratch:32",
              "used for emulation to determine test results",
              32, old_value_t.transactor_scratch, new_value_t.transactor_scratch };
    m_bit_details_model.bits.append(entry);
}

#define GP_AOCFG1PADCTRL_OFFSET 0x868
#define GP_AOCFG1PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_aocfg1padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_aocfg1_hsm_en:1;/* AOCFG1 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_aocfg1_schmt_en:1;/* AOCFG1 data pins schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_aocfg1_lpmd:2; /* AOCFG1 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_aocfg1_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_aocfg1_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_aocfg1_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_aocfg1_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_aocfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_aocfg1padctrl_u old_value_t = { .reg32 = value };
    const gp_aocfg1padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_aocfg1_hsm_en:1",
              "AOCFG1 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_aocfg1_hsm_en, new_value_t.cfg2tmc_aocfg1_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_aocfg1_schmt_en:1",
              "AOCFG1 data pins schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_aocfg1_schmt_en, new_value_t.cfg2tmc_aocfg1_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_aocfg1_lpmd:2",
              "AOCFG1 data pins low power mode select",
              2, old_value_t.cfg2tmc_aocfg1_lpmd, new_value_t.cfg2tmc_aocfg1_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_aocfg1_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_aocfg1_cal_drvdn, new_value_t.cfg2tmc_aocfg1_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_aocfg1_cal_drvup:5", "", 5, old_value_t.cfg2tmc_aocfg1_cal_drvup, new_value_t.cfg2tmc_aocfg1_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_aocfg1_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_aocfg1_cal_drvdn_slwr, new_value_t.cfg2tmc_aocfg1_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_aocfg1_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_aocfg1_cal_drvup_slwf, new_value_t.cfg2tmc_aocfg1_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * SYS_RESET_\n    * PWR_I2C_SCL\n    * PWR_I2C_SDA\n    * KB_ROW[7:0]\nAOCFG1 Pad Control Register";
}

#define GP_AOCFG2PADCTRL_OFFSET 0x86C
#define GP_AOCFG2PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_aocfg2padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_aocfg2_hsm_en:1;/* AOCFG2 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_aocfg2_schmt_en:1;/* AOCFG2 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_aocfg2_lpmd:2; /* AOCFG2 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_aocfg2_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_aocfg2_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_aocfg2_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_aocfg2_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_aocfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_aocfg2padctrl_u old_value_t = { .reg32 = value };
    const gp_aocfg2padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_aocfg2_hsm_en:1",
              "AOCFG2 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_aocfg2_hsm_en, new_value_t.cfg2tmc_aocfg2_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_aocfg2_schmt_en:1",
              "AOCFG2 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_aocfg2_schmt_en, new_value_t.cfg2tmc_aocfg2_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_aocfg2_lpmd:2",
              "AOCFG2 data pins low power mode select",
              2, old_value_t.cfg2tmc_aocfg2_lpmd, new_value_t.cfg2tmc_aocfg2_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_aocfg2_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_aocfg2_cal_drvdn, new_value_t.cfg2tmc_aocfg2_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_aocfg2_cal_drvup:5", "", 5, old_value_t.cfg2tmc_aocfg2_cal_drvup, new_value_t.cfg2tmc_aocfg2_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_aocfg2_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_aocfg2_cal_drvdn_slwr, new_value_t.cfg2tmc_aocfg2_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_aocfg2_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_aocfg2_cal_drvup_slwf, new_value_t.cfg2tmc_aocfg2_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * KB_ROW[12:8]\n    * KB_COL[6:0]\n    * LED_BLINK\n    * SYS_CLK_REQ\n    * CORE_PWR_REQ\n    * CPU_PWR_REQ\n    * PWR_INT_\n    * CLK_32K_IN (CK32KHZ)\nAOCFG2 Pad Control Register";
}

#define GP_ATCFG1PADCTRL_OFFSET 0x870
#define GP_ATCFG1PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_atcfg1padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_atcfg1_hsm_en:1;/* ATCFG1 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_atcfg1_schmt_en:1;/* ATCFG1 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_atcfg1_lpmd:2; /* ATCFG1 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_atcfg1_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_atcfg1_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_atcfg1_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_atcfg1_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_atcfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_atcfg1padctrl_u old_value_t = { .reg32 = value };
    const gp_atcfg1padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_atcfg1_hsm_en:1",
              "ATCFG1 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_atcfg1_hsm_en, new_value_t.cfg2tmc_atcfg1_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_atcfg1_schmt_en:1",
              "ATCFG1 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_atcfg1_schmt_en, new_value_t.cfg2tmc_atcfg1_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_atcfg1_lpmd:2",
              "ATCFG1 data pins low power mode select",
              2, old_value_t.cfg2tmc_atcfg1_lpmd, new_value_t.cfg2tmc_atcfg1_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_atcfg1_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_atcfg1_cal_drvdn, new_value_t.cfg2tmc_atcfg1_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_atcfg1_cal_drvup:5", "", 5, old_value_t.cfg2tmc_atcfg1_cal_drvup, new_value_t.cfg2tmc_atcfg1_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_atcfg1_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_atcfg1_cal_drvdn_slwr, new_value_t.cfg2tmc_atcfg1_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_atcfg1_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_atcfg1_cal_drvup_slwf, new_value_t.cfg2tmc_atcfg1_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * GMI_IORDY\n    * GMI_AD[15:8]\n    * GMI_CS7\n    * GMI_DPD\n    * GEN_I2C_SCL (GEN2_I2C_CLK)\n    * GEN_I2C_SDA (GEN2_I2C_DAT)\nATCFG1 Pad Control Register";
}

#define GP_ATCFG2PADCTRL_OFFSET 0x874
#define GP_ATCFG2PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_atcfg2padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_atcfg2_hsm_en:1;/* ATCFG2 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_atcfg2_schmt_en:1;/* ATCFG2 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_atcfg2_lpmd:2; /* ATCFG2 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_atcfg2_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_atcfg2_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_atcfg2_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_atcfg2_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_atcfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_atcfg2padctrl_u old_value_t = { .reg32 = value };
    const gp_atcfg2padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_atcfg2_hsm_en:1",
              "ATCFG2 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_atcfg2_hsm_en, new_value_t.cfg2tmc_atcfg2_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_atcfg2_schmt_en:1",
              "ATCFG2 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_atcfg2_schmt_en, new_value_t.cfg2tmc_atcfg2_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_atcfg2_lpmd:2",
              "ATCFG2 data pins low power mode select",
              2, old_value_t.cfg2tmc_atcfg2_lpmd, new_value_t.cfg2tmc_atcfg2_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_atcfg2_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_atcfg2_cal_drvdn, new_value_t.cfg2tmc_atcfg2_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_atcfg2_cal_drvup:5", "", 5, old_value_t.cfg2tmc_atcfg2_cal_drvup, new_value_t.cfg2tmc_atcfg2_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_atcfg2_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_atcfg2_cal_drvdn_slwr, new_value_t.cfg2tmc_atcfg2_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_atcfg2_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_atcfg2_cal_drvup_slwf, new_value_t.cfg2tmc_atcfg2_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * GMI_WAIT\n    * GMI_ADV_N\n    * GMI_CLK\n    * GMI_CS[6:2]\n    * GMI_AD[7:0]\n    * GMI_HIOW\n    * GMI_HIOR\n    * GMI_RST_N\nATCFG2 Pad Control Register";
}

#define GP_CDEV1CFGPADCTRL_OFFSET 0x878
#define GP_CDEV1CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_cdev1cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_cdev1cfg_hsm_en:1;/* CDEV1CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_cdev1cfg_schmt_en:1;/* CDEV1CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_cdev1cfg_lpmd:2;/* CDEV1CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_cdev1cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_cdev1cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_cdev1cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_cdev1cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_cdev1cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_cdev1cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_cdev1cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_cdev1cfg_hsm_en:1",
              "CDEV1CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_cdev1cfg_hsm_en, new_value_t.cfg2tmc_cdev1cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_cdev1cfg_schmt_en:1",
              "CDEV1CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_cdev1cfg_schmt_en, new_value_t.cfg2tmc_cdev1cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_cdev1cfg_lpmd:2",
              "CDEV1CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_cdev1cfg_lpmd, new_value_t.cfg2tmc_cdev1cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_cdev1cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_cdev1cfg_cal_drvdn, new_value_t.cfg2tmc_cdev1cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_cdev1cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_cdev1cfg_cal_drvup, new_value_t.cfg2tmc_cdev1cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_cdev1cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_cdev1cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_cdev1cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_cdev1cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_cdev1cfg_cal_drvup_slwf, new_value_t.cfg2tmc_cdev1cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls:\n    * DAP_MCLK1\nCDEV1CFG Pad Control Register";
}

#define GP_CDEV2CFGPADCTRL_OFFSET 0x87C
#define GP_CDEV2CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_cdev2cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_cdev2cfg_hsm_en:1;/* CDEV2CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_cdev2cfg_schmt_en:1;/* CDEV2CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_cdev2cfg_lpmd:2;/* CDEV2CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_cdev2cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_cdev2cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_cdev2cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_cdev2cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_cdev2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_cdev2cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_cdev2cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_cdev2cfg_hsm_en:1",
              "CDEV2CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_cdev2cfg_hsm_en, new_value_t.cfg2tmc_cdev2cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_cdev2cfg_schmt_en:1",
              "CDEV2CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_cdev2cfg_schmt_en, new_value_t.cfg2tmc_cdev2cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_cdev2cfg_lpmd:2",
              "CDEV2CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_cdev2cfg_lpmd, new_value_t.cfg2tmc_cdev2cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_cdev2cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_cdev2cfg_cal_drvdn, new_value_t.cfg2tmc_cdev2cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_cdev2cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_cdev2cfg_cal_drvup, new_value_t.cfg2tmc_cdev2cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_cdev2cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_cdev2cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_cdev2cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_cdev2cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_cdev2cfg_cal_drvup_slwf, new_value_t.cfg2tmc_cdev2cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls:\n    * DAP_MCLK2\nCDEV2CFG Pad Control Register";
}

#define GP_CSUSCFGPADCTRL_OFFSET 0x880
#define GP_CSUSCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_csuscfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_csuscfg_hsm_en:1;/* CSUSCFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_csuscfg_schmt_en:1;/* CSUSCFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_csuscfg_lpmd:2;/* CSUSCFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_csuscfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_csuscfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_csuscfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_csuscfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_csuscfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_csuscfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_csuscfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_csuscfg_hsm_en:1",
              "CSUSCFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_csuscfg_hsm_en, new_value_t.cfg2tmc_csuscfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_csuscfg_schmt_en:1",
              "CSUSCFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_csuscfg_schmt_en, new_value_t.cfg2tmc_csuscfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_csuscfg_lpmd:2",
              "CSUSCFG data pins low power mode select",
              2, old_value_t.cfg2tmc_csuscfg_lpmd, new_value_t.cfg2tmc_csuscfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_csuscfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_csuscfg_cal_drvdn, new_value_t.cfg2tmc_csuscfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_csuscfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_csuscfg_cal_drvup, new_value_t.cfg2tmc_csuscfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_csuscfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_csuscfg_cal_drvdn_slwr, new_value_t.cfg2tmc_csuscfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_csuscfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_csuscfg_cal_drvup_slwf, new_value_t.cfg2tmc_csuscfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls:\n    * VI_MCLK\nCSUSCFG Pad Control Register";
}

#define GP_DAP1CFGPADCTRL_OFFSET 0x884
#define GP_DAP1CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_dap1cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_dap1cfg_hsm_en:1;/* DAP1CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap1cfg_schmt_en:1;/* DAP1CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap1cfg_lpmd:2;/* DAP1CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_dap1cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_dap1cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_dap1cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_dap1cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_dap1cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_dap1cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_dap1cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_dap1cfg_hsm_en:1",
              "DAP1CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap1cfg_hsm_en, new_value_t.cfg2tmc_dap1cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_dap1cfg_schmt_en:1",
              "DAP1CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap1cfg_schmt_en, new_value_t.cfg2tmc_dap1cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_dap1cfg_lpmd:2",
              "DAP1CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_dap1cfg_lpmd, new_value_t.cfg2tmc_dap1cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_dap1cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_dap1cfg_cal_drvdn, new_value_t.cfg2tmc_dap1cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_dap1cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_dap1cfg_cal_drvup, new_value_t.cfg2tmc_dap1cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_dap1cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_dap1cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_dap1cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_dap1cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_dap1cfg_cal_drvup_slwf, new_value_t.cfg2tmc_dap1cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * DAP1_FS\n    * DAP1_DIN\n    * DAP1_DOUT\n    * DAP1_SCLK\n    * SPDIF_OUT\n    * SPDIF_IN\nDAP1CFG Pad Control Register";
}

#define GP_DAP2CFGPADCTRL_OFFSET 0x888
#define GP_DAP2CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_dap2cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_dap2cfg_hsm_en:1;/* DAP2CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap2cfg_schmt_en:1;/* DAP2CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap2cfg_lpmd:2;/* DAP2CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_dap2cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_dap2cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_dap2cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_dap2cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_dap2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_dap2cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_dap2cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_dap2cfg_hsm_en:1",
              "DAP2CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap2cfg_hsm_en, new_value_t.cfg2tmc_dap2cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_dap2cfg_schmt_en:1",
              "DAP2CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap2cfg_schmt_en, new_value_t.cfg2tmc_dap2cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_dap2cfg_lpmd:2",
              "DAP2CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_dap2cfg_lpmd, new_value_t.cfg2tmc_dap2cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_dap2cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_dap2cfg_cal_drvdn, new_value_t.cfg2tmc_dap2cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_dap2cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_dap2cfg_cal_drvup, new_value_t.cfg2tmc_dap2cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_dap2cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_dap2cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_dap2cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_dap2cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_dap2cfg_cal_drvup_slwf, new_value_t.cfg2tmc_dap2cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * DAP2_FS\n    * DAP2_SCLK\n    * DAP2_DIN\n    * DAP2_DOUT\nDAP2CFG Pad Control Register";
}

#define GP_DAP3CFGPADCTRL_OFFSET 0x88C
#define GP_DAP3CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_dap3cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_dap3cfg_hsm_en:1;/* DAP3CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap3cfg_schmt_en:1;/* DAP3CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap3cfg_lpmd:2;/* DAP3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_dap3cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_dap3cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_dap3cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_dap3cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_dap3cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_dap3cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_dap3cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_dap3cfg_hsm_en:1",
              "DAP3CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap3cfg_hsm_en, new_value_t.cfg2tmc_dap3cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_dap3cfg_schmt_en:1",
              "DAP3CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap3cfg_schmt_en, new_value_t.cfg2tmc_dap3cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_dap3cfg_lpmd:2",
              "DAP3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_dap3cfg_lpmd, new_value_t.cfg2tmc_dap3cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_dap3cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_dap3cfg_cal_drvdn, new_value_t.cfg2tmc_dap3cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_dap3cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_dap3cfg_cal_drvup, new_value_t.cfg2tmc_dap3cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_dap3cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_dap3cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_dap3cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_dap3cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_dap3cfg_cal_drvup_slwf, new_value_t.cfg2tmc_dap3cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * DAP3_FS\n    * DAP3_DIN\n    * DAP3_DOUT\n    * DAP3_SCLK\nDAP3CFG Pad Control Register";
}

#define GP_DAP4CFGPADCTRL_OFFSET 0x890
#define GP_DAP4CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_dap4cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_dap4cfg_hsm_en:1;/* DAP4CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap4cfg_schmt_en:1;/* DAP4CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dap4cfg_lpmd:2;/* DAP4CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_dap4cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_dap4cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_dap4cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_dap4cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_dap4cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_dap4cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_dap4cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_dap4cfg_hsm_en:1",
              "DAP4CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap4cfg_hsm_en, new_value_t.cfg2tmc_dap4cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_dap4cfg_schmt_en:1",
              "DAP4CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dap4cfg_schmt_en, new_value_t.cfg2tmc_dap4cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_dap4cfg_lpmd:2",
              "DAP4CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_dap4cfg_lpmd, new_value_t.cfg2tmc_dap4cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_dap4cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_dap4cfg_cal_drvdn, new_value_t.cfg2tmc_dap4cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_dap4cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_dap4cfg_cal_drvup, new_value_t.cfg2tmc_dap4cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_dap4cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_dap4cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_dap4cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_dap4cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_dap4cfg_cal_drvup_slwf, new_value_t.cfg2tmc_dap4cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * DAP4_FS\n    * DAP4_DIN\n    * DAP4_DOUT\n    * DAP4_SCLK\nDAP4CFG Pad Control Register";
}

#define GP_DBGCFGPADCTRL_OFFSET 0x894
#define GP_DBGCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_dbgcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_dbgcfg_hsm_en:1;/* DBGCFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dbgcfg_schmt_en:1;/* DBGCFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_dbgcfg_lpmd:2; /* DBGCFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_dbgcfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_dbgcfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_dbgcfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_dbgcfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_dbgcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_dbgcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_dbgcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_dbgcfg_hsm_en:1",
              "DBGCFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dbgcfg_hsm_en, new_value_t.cfg2tmc_dbgcfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_dbgcfg_schmt_en:1",
              "DBGCFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_dbgcfg_schmt_en, new_value_t.cfg2tmc_dbgcfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_dbgcfg_lpmd:2",
              "DBGCFG data pins low power mode select",
              2, old_value_t.cfg2tmc_dbgcfg_lpmd, new_value_t.cfg2tmc_dbgcfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_dbgcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_dbgcfg_cal_drvdn, new_value_t.cfg2tmc_dbgcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_dbgcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_dbgcfg_cal_drvup, new_value_t.cfg2tmc_dbgcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_dbgcfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_dbgcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_dbgcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_dbgcfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_dbgcfg_cal_drvup_slwf, new_value_t.cfg2tmc_dbgcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * GPIO_PU[7:0]\n    * GEN1_I2C_SDA\n    * GEN1_I2C_SCL\nDBGCFG Pad Control Register";
}

#define GP_LCDCFG1PADCTRL_OFFSET 0x898
#define GP_LCDCFG1PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_lcdcfg1padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_lcdcfg1_hsm_en:1;/* LCDCFG1 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_lcdcfg1_schmt_en:1;/* LCDCFG1 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_lcdcfg1_lpmd:2;/* LCDCFG1 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_lcdcfg1_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_lcdcfg1_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_lcdcfg1_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_lcdcfg1_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_lcdcfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_lcdcfg1padctrl_u old_value_t = { .reg32 = value };
    const gp_lcdcfg1padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_lcdcfg1_hsm_en:1",
              "LCDCFG1 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_lcdcfg1_hsm_en, new_value_t.cfg2tmc_lcdcfg1_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_lcdcfg1_schmt_en:1",
              "LCDCFG1 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_lcdcfg1_schmt_en, new_value_t.cfg2tmc_lcdcfg1_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_lcdcfg1_lpmd:2",
              "LCDCFG1 data pins low power mode select",
              2, old_value_t.cfg2tmc_lcdcfg1_lpmd, new_value_t.cfg2tmc_lcdcfg1_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_lcdcfg1_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_lcdcfg1_cal_drvdn, new_value_t.cfg2tmc_lcdcfg1_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_lcdcfg1_cal_drvup:5", "", 5, old_value_t.cfg2tmc_lcdcfg1_cal_drvup, new_value_t.cfg2tmc_lcdcfg1_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_lcdcfg1_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_lcdcfg1_cal_drvdn_slwr, new_value_t.cfg2tmc_lcdcfg1_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_lcdcfg1_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_lcdcfg1_cal_drvup_slwf, new_value_t.cfg2tmc_lcdcfg1_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * LCD_PWR1\n    * LCD_PWR2\n    * LCD_SDIN\n    * LCD_SDOUT\n    * LCD_WR_\n    * LCD_CS0_\n    * LCD_DC0\n    * LCD_SCK\nLCDCFG1 Pad Control Register";
}

#define GP_LCDCFG2PADCTRL_OFFSET 0x89C
#define GP_LCDCFG2PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_lcdcfg2padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_lcdcfg2_hsm_en:1;/* LCDCFG2 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_lcdcfg2_schmt_en:1;/* LCDCFG2 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_lcdcfg2_lpmd:2;/* LCDCFG2 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_lcdcfg2_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_lcdcfg2_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_lcdcfg2_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_lcdcfg2_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_lcdcfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_lcdcfg2padctrl_u old_value_t = { .reg32 = value };
    const gp_lcdcfg2padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_lcdcfg2_hsm_en:1",
              "LCDCFG2 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_lcdcfg2_hsm_en, new_value_t.cfg2tmc_lcdcfg2_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_lcdcfg2_schmt_en:1",
              "LCDCFG2 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_lcdcfg2_schmt_en, new_value_t.cfg2tmc_lcdcfg2_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_lcdcfg2_lpmd:2",
              "LCDCFG2 data pins low power mode select",
              2, old_value_t.cfg2tmc_lcdcfg2_lpmd, new_value_t.cfg2tmc_lcdcfg2_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_lcdcfg2_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_lcdcfg2_cal_drvdn, new_value_t.cfg2tmc_lcdcfg2_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_lcdcfg2_cal_drvup:5", "", 5, old_value_t.cfg2tmc_lcdcfg2_cal_drvup, new_value_t.cfg2tmc_lcdcfg2_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_lcdcfg2_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_lcdcfg2_cal_drvdn_slwr, new_value_t.cfg2tmc_lcdcfg2_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_lcdcfg2_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_lcdcfg2_cal_drvup_slwf, new_value_t.cfg2tmc_lcdcfg2_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * LCD_PWR0\n    * LCD_PCLK\n    * LCD_DE\n    * LCD_HSYNC\n    * LCD_VSYNC\n    * LCD_D[23:0]\n    * LCD_CS1_\n    * LCD_M1\n    * LCD_DC1\nLCDCFG2 Pad Control Register";
}

#define GP_SDIO2CFGPADCTRL_OFFSET 0x8A0
#define GP_SDIO2CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_sdio2cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_sdio2cfg_hsm_en:1;/* SDIO2CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_sdio2cfg_schmt_en:1;/* SDIO2CFG data pins schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_sdio2cfg_lpmd:2;/* SDIO2CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_sdio2cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_sdio2cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_sdio2cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_sdio2cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_sdio2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_sdio2cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_sdio2cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_sdio2cfg_hsm_en:1",
              "SDIO2CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_sdio2cfg_hsm_en, new_value_t.cfg2tmc_sdio2cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_sdio2cfg_schmt_en:1",
              "SDIO2CFG data pins schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_sdio2cfg_schmt_en, new_value_t.cfg2tmc_sdio2cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_sdio2cfg_lpmd:2",
              "SDIO2CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_sdio2cfg_lpmd, new_value_t.cfg2tmc_sdio2cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_sdio2cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_sdio2cfg_cal_drvdn, new_value_t.cfg2tmc_sdio2cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_sdio2cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_sdio2cfg_cal_drvup, new_value_t.cfg2tmc_sdio2cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_sdio2cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_sdio2cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_sdio2cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_sdio2cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_sdio2cfg_cal_drvup_slwf, new_value_t.cfg2tmc_sdio2cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls following pins:\n    * SDIO2_DAT[3:0]\n    * SDIO2_CLK\n    * SDIO2_CMD\nSDIO2CFG Pad Control Register";
}

#define GP_SDIO3CFGPADCTRL_OFFSET 0x8A4
#define GP_SDIO3CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_sdio3cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_sdio3cfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_sdio3cfg_schmt_en:1;/* SDIO3CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_sdio3cfg_lpmd:2;/* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_sdio3cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_sdio3cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_sdio3cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_sdio3cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_sdio3cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_sdio3cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_sdio3cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_sdio3cfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_sdio3cfg_hsm_en, new_value_t.cfg2tmc_sdio3cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_sdio3cfg_schmt_en:1",
              "SDIO3CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_sdio3cfg_schmt_en, new_value_t.cfg2tmc_sdio3cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_sdio3cfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_sdio3cfg_lpmd, new_value_t.cfg2tmc_sdio3cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_sdio3cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_sdio3cfg_cal_drvdn, new_value_t.cfg2tmc_sdio3cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_sdio3cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_sdio3cfg_cal_drvup, new_value_t.cfg2tmc_sdio3cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_sdio3cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_sdio3cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_sdio3cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_sdio3cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_sdio3cfg_cal_drvup_slwf, new_value_t.cfg2tmc_sdio3cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * SDIO3_DAT[3:0]\n    * SDIO3_CLK\n    * SDIO3_CMD\n    * GPIO_PV[6:4]\nSDIO3CFG Pad Control Register";
}

#define GP_SPICFGPADCTRL_OFFSET 0x8A8
#define GP_SPICFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_spicfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_spicfg_hsm_en:1;/* SPICFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_spicfg_schmt_en:1;/* SPICFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_spicfg_lpmd:2; /* SPICFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_spicfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_spicfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_spicfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_spicfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_spicfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_spicfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_spicfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_spicfg_hsm_en:1",
              "SPICFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_spicfg_hsm_en, new_value_t.cfg2tmc_spicfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_spicfg_schmt_en:1",
              "SPICFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_spicfg_schmt_en, new_value_t.cfg2tmc_spicfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_spicfg_lpmd:2",
              "SPICFG data pins low power mode select",
              2, old_value_t.cfg2tmc_spicfg_lpmd, new_value_t.cfg2tmc_spicfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_spicfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_spicfg_cal_drvdn, new_value_t.cfg2tmc_spicfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_spicfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_spicfg_cal_drvup, new_value_t.cfg2tmc_spicfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_spicfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_spicfg_cal_drvdn_slwr, new_value_t.cfg2tmc_spicfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_spicfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_spicfg_cal_drvup_slwf, new_value_t.cfg2tmc_spicfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * SPI2_MOSI\n    * SPI2_MISO\n    * SPI2_SCK\n    * SPI2_CS0_\n    * SPI1_MOSI\n    * SPI1_SCK\n    * SPI1_CS0_\n    * SPI1_MISO\n    * SPI2_CS1_\n    * SPI2_CS2_\nSPICFG Pad Control Register";
}

#define GP_UAACFGPADCTRL_OFFSET 0x8AC
#define GP_UAACFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_uaacfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_uaacfg_hsm_en:1;/* UAACFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uaacfg_schmt_en:1;/* UAACFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uaacfg_lpmd:2; /* UAACFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_uaacfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_uaacfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_uaacfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_uaacfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_uaacfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_uaacfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_uaacfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_uaacfg_hsm_en:1",
              "UAACFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uaacfg_hsm_en, new_value_t.cfg2tmc_uaacfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_uaacfg_schmt_en:1",
              "UAACFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uaacfg_schmt_en, new_value_t.cfg2tmc_uaacfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_uaacfg_lpmd:2",
              "UAACFG data pins low power mode select",
              2, old_value_t.cfg2tmc_uaacfg_lpmd, new_value_t.cfg2tmc_uaacfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_uaacfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_uaacfg_cal_drvdn, new_value_t.cfg2tmc_uaacfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_uaacfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_uaacfg_cal_drvup, new_value_t.cfg2tmc_uaacfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_uaacfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_uaacfg_cal_drvdn_slwr, new_value_t.cfg2tmc_uaacfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_uaacfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_uaacfg_cal_drvup_slwf, new_value_t.cfg2tmc_uaacfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * UART1_TXD\n    *  UART1_RXD\n    *  UART1_CTS_\n    *  UART1_RTS_\nUAACFG Pad Control Register";
}

#define GP_UABCFGPADCTRL_OFFSET 0x8B0
#define GP_UABCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_uabcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_uabcfg_hsm_en:1;/* UABCFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uabcfg_schmt_en:1;/* UABCFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uabcfg_lpmd:2; /* UABCFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_uabcfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_uabcfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_uabcfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_uabcfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_uabcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_uabcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_uabcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_uabcfg_hsm_en:1",
              "UABCFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uabcfg_hsm_en, new_value_t.cfg2tmc_uabcfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_uabcfg_schmt_en:1",
              "UABCFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uabcfg_schmt_en, new_value_t.cfg2tmc_uabcfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_uabcfg_lpmd:2",
              "UABCFG data pins low power mode select",
              2, old_value_t.cfg2tmc_uabcfg_lpmd, new_value_t.cfg2tmc_uabcfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_uabcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_uabcfg_cal_drvdn, new_value_t.cfg2tmc_uabcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_uabcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_uabcfg_cal_drvup, new_value_t.cfg2tmc_uabcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_uabcfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_uabcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_uabcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_uabcfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_uabcfg_cal_drvup_slwf, new_value_t.cfg2tmc_uabcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * UART1_RI_\n    *  UART1_DCD_\n    *  UART1_DSR_\n    *  UART1_DTR_\n    * GPIO_PV[3:0]\nUABCFG Pad Control Register";
}

#define GP_UART2CFGPADCTRL_OFFSET 0x8B4
#define GP_UART2CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_uart2cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_uart2cfg_hsm_en:1;/* UART2CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uart2cfg_schmt_en:1;/* UART2CFG data pins schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uart2cfg_lpmd:2;/* UART2CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_uart2cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_uart2cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_uart2cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_uart2cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_uart2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_uart2cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_uart2cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_uart2cfg_hsm_en:1",
              "UART2CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uart2cfg_hsm_en, new_value_t.cfg2tmc_uart2cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_uart2cfg_schmt_en:1",
              "UART2CFG data pins schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uart2cfg_schmt_en, new_value_t.cfg2tmc_uart2cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_uart2cfg_lpmd:2",
              "UART2CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_uart2cfg_lpmd, new_value_t.cfg2tmc_uart2cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_uart2cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_uart2cfg_cal_drvdn, new_value_t.cfg2tmc_uart2cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_uart2cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_uart2cfg_cal_drvup, new_value_t.cfg2tmc_uart2cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_uart2cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_uart2cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_uart2cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_uart2cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_uart2cfg_cal_drvup_slwf, new_value_t.cfg2tmc_uart2cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * UART2_TXD\n    * UART2_RXD\n    * UART2_RTS_\n    * UART2_CTS_\nUART2CFG Pad Control Register";
}

#define GP_UART3CFGPADCTRL_OFFSET 0x8B8
#define GP_UART3CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_uart3cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_uart3cfg_hsm_en:1;/* UART3CFG data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uart3cfg_schmt_en:1;/* UART3CFG data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_uart3cfg_lpmd:2;/* UART3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_uart3cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_uart3cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_uart3cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_uart3cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_uart3cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_uart3cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_uart3cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_uart3cfg_hsm_en:1",
              "UART3CFG data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uart3cfg_hsm_en, new_value_t.cfg2tmc_uart3cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_uart3cfg_schmt_en:1",
              "UART3CFG data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_uart3cfg_schmt_en, new_value_t.cfg2tmc_uart3cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_uart3cfg_lpmd:2",
              "UART3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_uart3cfg_lpmd, new_value_t.cfg2tmc_uart3cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_uart3cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_uart3cfg_cal_drvdn, new_value_t.cfg2tmc_uart3cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_uart3cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_uart3cfg_cal_drvup, new_value_t.cfg2tmc_uart3cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_uart3cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_uart3cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_uart3cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_uart3cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_uart3cfg_cal_drvup_slwf, new_value_t.cfg2tmc_uart3cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * UART3_TXD\n    * UART3_RXD\n    * UART3_RTS_\n    * UART3_CTS_\nUART3CFG Pad Control Register";
}

#define GP_VICFG1PADCTRL_OFFSET 0x8BC
#define GP_VICFG1PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_vicfg1padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_vicfg1_hsm_en:1;/* VICFG1 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_vicfg1_schmt_en:1;/* VICFG1 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_vicfg1_lpmd:2; /* VICFG1 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_vicfg1_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_vicfg1_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_vicfg1_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_vicfg1_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_vicfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_vicfg1padctrl_u old_value_t = { .reg32 = value };
    const gp_vicfg1padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_vicfg1_hsm_en:1",
              "VICFG1 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_vicfg1_hsm_en, new_value_t.cfg2tmc_vicfg1_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_vicfg1_schmt_en:1",
              "VICFG1 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_vicfg1_schmt_en, new_value_t.cfg2tmc_vicfg1_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_vicfg1_lpmd:2",
              "VICFG1 data pins low power mode select",
              2, old_value_t.cfg2tmc_vicfg1_lpmd, new_value_t.cfg2tmc_vicfg1_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_vicfg1_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_vicfg1_cal_drvdn, new_value_t.cfg2tmc_vicfg1_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_vicfg1_cal_drvup:5", "", 5, old_value_t.cfg2tmc_vicfg1_cal_drvup, new_value_t.cfg2tmc_vicfg1_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_vicfg1_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_vicfg1_cal_drvdn_slwr, new_value_t.cfg2tmc_vicfg1_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_vicfg1_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_vicfg1_cal_drvup_slwf, new_value_t.cfg2tmc_vicfg1_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * VI_D[11:0]\n    * VI_PCLK\n    * VI_VSYNC\n    * VI_HSYNC\nVICFG1 Pad Control Register";
}

#define GP_VICFG2PADCTRL_OFFSET 0x8C0
#define GP_VICFG2PADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_vicfg2padctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_vicfg2_hsm_en:1;/* VICFG2 data pins high speed mode enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_vicfg2_schmt_en:1;/* VICFG2 data pins Schmidt enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int cfg2tmc_vicfg2_lpmd:2; /* VICFG2 data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_vicfg2_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_vicfg2_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_vicfg2_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_vicfg2_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_vicfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_vicfg2padctrl_u old_value_t = { .reg32 = value };
    const gp_vicfg2padctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_vicfg2_hsm_en:1",
              "VICFG2 data pins high speed mode enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_vicfg2_hsm_en, new_value_t.cfg2tmc_vicfg2_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_vicfg2_schmt_en:1",
              "VICFG2 data pins Schmidt enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cfg2tmc_vicfg2_schmt_en, new_value_t.cfg2tmc_vicfg2_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_vicfg2_lpmd:2",
              "VICFG2 data pins low power mode select",
              2, old_value_t.cfg2tmc_vicfg2_lpmd, new_value_t.cfg2tmc_vicfg2_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_vicfg2_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_vicfg2_cal_drvdn, new_value_t.cfg2tmc_vicfg2_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_vicfg2_cal_drvup:5", "", 5, old_value_t.cfg2tmc_vicfg2_cal_drvup, new_value_t.cfg2tmc_vicfg2_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_vicfg2_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_vicfg2_cal_drvdn_slwr, new_value_t.cfg2tmc_vicfg2_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_vicfg2_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_vicfg2_cal_drvup_slwf, new_value_t.cfg2tmc_vicfg2_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * VI_GP0\n    * CAM_I2C_SCK\n    * CAM_I2C_SDA\n    * VI_GP[6:3]\nVICFG2 Pad Control Register";
}

#define GP_XM2CFGAPADCTRL_OFFSET 0x8C4
#define GP_XM2CFGAPADCTRL_UNDEFMASK 0x00003F8F
union gp_xm2cfgapadctrl_u {
    struct {
        unsigned int undefined_bits_0_3:4;
        unsigned int cfg2tmc_xm2cfga_bypass_en:1;/* XM2CFGA data pins bypass outbound flop enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfga_preemp_en:1;/* XM2CFGA data pins preemp enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfga_clk_sel:1;/* pad clk_sel (ma bits get this value inverted in lpddr2 mode) */
        unsigned int undefined_bits_7_13:7;
        unsigned int cfg2tmc_xm2cfga_cal_drvdn:5;
        unsigned int cfg2tmc_xm2cfga_cal_drvup:5;
        unsigned int cfg2tmc_xm2cfga_cal_drvdn_slwr:4;
        unsigned int cfg2tmc_xm2cfga_cal_drvup_slwf:4;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2cfgapadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2cfgapadctrl_u old_value_t = { .reg32 = value };
    const gp_xm2cfgapadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_3:4", "", 4, old_value_t.undefined_bits_0_3, new_value_t.undefined_bits_0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_xm2cfga_bypass_en:1",
              "XM2CFGA data pins bypass outbound flop enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfga_bypass_en, new_value_t.cfg2tmc_xm2cfga_bypass_en };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cfg2tmc_xm2cfga_preemp_en:1",
              "XM2CFGA data pins preemp enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfga_preemp_en, new_value_t.cfg2tmc_xm2cfga_preemp_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cfg2tmc_xm2cfga_clk_sel:1",
              "pad clk_sel (ma bits get this value inverted in lpddr2 mode)",
              1, old_value_t.cfg2tmc_xm2cfga_clk_sel, new_value_t.cfg2tmc_xm2cfga_clk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_13:7", "", 7, old_value_t.undefined_bits_7_13, new_value_t.undefined_bits_7_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: cfg2tmc_xm2cfga_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_xm2cfga_cal_drvdn, new_value_t.cfg2tmc_xm2cfga_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "19: cfg2tmc_xm2cfga_cal_drvup:5", "", 5, old_value_t.cfg2tmc_xm2cfga_cal_drvup, new_value_t.cfg2tmc_xm2cfga_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2cfga_cal_drvdn_slwr:4", "", 4, old_value_t.cfg2tmc_xm2cfga_cal_drvdn_slwr, new_value_t.cfg2tmc_xm2cfga_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_xm2cfga_cal_drvup_slwf:4", "", 4, old_value_t.cfg2tmc_xm2cfga_cal_drvup_slwf, new_value_t.cfg2tmc_xm2cfga_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * SPI3_SCK\n    *  SPI3_DOUT\n    *  SPI3_DIN\n    *  SPI3_CS0_\n    *  DDR_A [13: 0]\n    *  DDR_BA0\n    *  DDR_BA1\nXM2CFGA Pad Control Register";
}

#define GP_XM2CFGCPADCTRL_OFFSET 0x8C8
#define GP_XM2CFGCPADCTRL_UNDEFMASK 0x00000007
union gp_xm2cfgcpadctrl_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int cfg2tmc_xm2cfgc_schmt_en:1;/* XM2CFGD data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_cal_drvdn_term:5;
        unsigned int cfg2tmc_xm2cfgc_cal_drvup_term:5;
        unsigned int cfg2tmc_xm2cfgc_cal_drvdn:5;
        unsigned int cfg2tmc_xm2cfgc_cal_drvup:5;
        unsigned int cfg2tmc_xm2cfgc_cal_drvdn_slwr:4;
        unsigned int cfg2tmc_xm2cfgc_cal_drvup_slwf:4;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2cfgcpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2cfgcpadctrl_u old_value_t = { .reg32 = value };
    const gp_xm2cfgcpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_xm2cfgc_schmt_en:1",
              "XM2CFGD data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_schmt_en, new_value_t.cfg2tmc_xm2cfgc_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_xm2cfgc_cal_drvdn_term:5", "", 5, old_value_t.cfg2tmc_xm2cfgc_cal_drvdn_term, new_value_t.cfg2tmc_xm2cfgc_cal_drvdn_term };
    m_bit_details_model.bits.append(entry);
    entry = { "09: cfg2tmc_xm2cfgc_cal_drvup_term:5", "", 5, old_value_t.cfg2tmc_xm2cfgc_cal_drvup_term, new_value_t.cfg2tmc_xm2cfgc_cal_drvup_term };
    m_bit_details_model.bits.append(entry);
    entry = { "14: cfg2tmc_xm2cfgc_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_xm2cfgc_cal_drvdn, new_value_t.cfg2tmc_xm2cfgc_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "19: cfg2tmc_xm2cfgc_cal_drvup:5", "", 5, old_value_t.cfg2tmc_xm2cfgc_cal_drvup, new_value_t.cfg2tmc_xm2cfgc_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2cfgc_cal_drvdn_slwr:4", "", 4, old_value_t.cfg2tmc_xm2cfgc_cal_drvdn_slwr, new_value_t.cfg2tmc_xm2cfgc_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_xm2cfgc_cal_drvup_slwf:4", "", 4, old_value_t.cfg2tmc_xm2cfgc_cal_drvup_slwf, new_value_t.cfg2tmc_xm2cfgc_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * MIO_IORDY\n    *  ROM_CS0_\n    *  MIO_CS0_\n    *  DDR_DQS0\n    *  DDR_DQS1\n    *  DDR_DQS2\n    *  DDR_DQS3\n    *  DDR_DM0\n    *  DDR_DM1\n    *  DDR_DM2\n    *  DDR_DM3\n    *  DDR_CS0_\n    *  DDR_CS1_\n    *  DDR_CKE\n    *  DDR_RAS_\n    *  DDR_CAS_\n    *  DDR_WE_\nXM2CFGC Pad Control Register";
}

#define GP_XM2CFGDPADCTRL_OFFSET 0x8CC
#define GP_XM2CFGDPADCTRL_UNDEFMASK 0x00000007
union gp_xm2cfgdpadctrl_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int cfg2tmc_xm2cfgd_schmt_en:1;/* XM2CFGD data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgd_cal_drvdn_term:5;
        unsigned int cfg2tmc_xm2cfgd_cal_drvup_term:5;
        unsigned int cfg2tmc_xm2cfgd_cal_drvdn:5;
        unsigned int cfg2tmc_xm2cfgd_cal_drvup:5;
        unsigned int cfg2tmc_xm2cfgd_cal_drvdn_slwr:4;
        unsigned int cfg2tmc_xm2cfgd_cal_drvup_slwf:4;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2cfgdpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2cfgdpadctrl_u old_value_t = { .reg32 = value };
    const gp_xm2cfgdpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_xm2cfgd_schmt_en:1",
              "XM2CFGD data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgd_schmt_en, new_value_t.cfg2tmc_xm2cfgd_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_xm2cfgd_cal_drvdn_term:5", "", 5, old_value_t.cfg2tmc_xm2cfgd_cal_drvdn_term, new_value_t.cfg2tmc_xm2cfgd_cal_drvdn_term };
    m_bit_details_model.bits.append(entry);
    entry = { "09: cfg2tmc_xm2cfgd_cal_drvup_term:5", "", 5, old_value_t.cfg2tmc_xm2cfgd_cal_drvup_term, new_value_t.cfg2tmc_xm2cfgd_cal_drvup_term };
    m_bit_details_model.bits.append(entry);
    entry = { "14: cfg2tmc_xm2cfgd_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_xm2cfgd_cal_drvdn, new_value_t.cfg2tmc_xm2cfgd_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "19: cfg2tmc_xm2cfgd_cal_drvup:5", "", 5, old_value_t.cfg2tmc_xm2cfgd_cal_drvup, new_value_t.cfg2tmc_xm2cfgd_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2cfgd_cal_drvdn_slwr:4", "", 4, old_value_t.cfg2tmc_xm2cfgd_cal_drvdn_slwr, new_value_t.cfg2tmc_xm2cfgd_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_xm2cfgd_cal_drvup_slwf:4", "", 4, old_value_t.cfg2tmc_xm2cfgd_cal_drvup_slwf, new_value_t.cfg2tmc_xm2cfgd_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * DDR_DQ[31:0]\nXM2CFGD Pad Control Register";
}

#define GP_XM2CLKCFGPADCTRL_OFFSET 0x8D0
#define GP_XM2CLKCFGPADCTRL_UNDEFMASK 0x00003FF1
union gp_xm2clkcfgpadctrl_u {
    struct {
        unsigned int undefined_bit_0:1;
        unsigned int cfg2tmc_xm2clkcfg_bypass_en:1;/* XM2 bypass outbound flop enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2clkcfg_preemp_en:1;/* preemp enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2clkcfg_cal_bypass_en:1;/* XM2CLKCFG bypass drvdn/up calibration  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_4_13:10;
        unsigned int cfg2tmc_xm2clkcfg_cal_drvdn:5;
        unsigned int cfg2tmc_xm2clkcfg_cal_drvup:5;
        unsigned int cfg2tmc_xm2clkcfg_cal_drvdn_slwr:4;
        unsigned int cfg2tmc_xm2clkcfg_cal_drvup_slwf:4;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2clkcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2clkcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_xm2clkcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bit_0:1", "", 1, old_value_t.undefined_bit_0, new_value_t.undefined_bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cfg2tmc_xm2clkcfg_bypass_en:1",
              "XM2 bypass outbound flop enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2clkcfg_bypass_en, new_value_t.cfg2tmc_xm2clkcfg_bypass_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_xm2clkcfg_preemp_en:1",
              "preemp enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2clkcfg_preemp_en, new_value_t.cfg2tmc_xm2clkcfg_preemp_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_xm2clkcfg_cal_bypass_en:1",
              "XM2CLKCFG bypass drvdn/up calibration \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2clkcfg_cal_bypass_en, new_value_t.cfg2tmc_xm2clkcfg_cal_bypass_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_13:10", "", 10, old_value_t.undefined_bits_4_13, new_value_t.undefined_bits_4_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: cfg2tmc_xm2clkcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_xm2clkcfg_cal_drvdn, new_value_t.cfg2tmc_xm2clkcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "19: cfg2tmc_xm2clkcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_xm2clkcfg_cal_drvup, new_value_t.cfg2tmc_xm2clkcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2clkcfg_cal_drvdn_slwr:4", "", 4, old_value_t.cfg2tmc_xm2clkcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_xm2clkcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_xm2clkcfg_cal_drvup_slwf:4", "", 4, old_value_t.cfg2tmc_xm2clkcfg_cal_drvup_slwf, new_value_t.cfg2tmc_xm2clkcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls the following pins:\n    * DDR_CLK\n    * DDR_CLK_\n    * DDR_CKE\nXM2CLKCFG Pad Control Register";
}

#define GP_XM2COMPPADCTRL_OFFSET 0x8D4
#define GP_XM2COMPPADCTRL_UNDEFMASK 0xFE0E0F00
union gp_xm2comppadctrl_u {
    struct {
        unsigned int cfg2tmc_xm2comp_vref_sel:4;
        unsigned int cfg2tmc_xm2comp_testout_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2comp_bias_sel:3;
        unsigned int undefined_bits_8_11:4;
        unsigned int cfg2tmc_xm2comp_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_xm2comp_drvup:5;
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2comppadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2comppadctrl_u old_value_t = { .reg32 = value };
    const gp_xm2comppadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg2tmc_xm2comp_vref_sel:4", "", 4, old_value_t.cfg2tmc_xm2comp_vref_sel, new_value_t.cfg2tmc_xm2comp_vref_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_xm2comp_testout_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2comp_testout_en, new_value_t.cfg2tmc_xm2comp_testout_en };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cfg2tmc_xm2comp_bias_sel:3", "", 3, old_value_t.cfg2tmc_xm2comp_bias_sel, new_value_t.cfg2tmc_xm2comp_bias_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_11:4", "", 4, old_value_t.undefined_bits_8_11, new_value_t.undefined_bits_8_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_xm2comp_drvdn:5", "", 5, old_value_t.cfg2tmc_xm2comp_drvdn, new_value_t.cfg2tmc_xm2comp_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_xm2comp_drvup:5", "", 5, old_value_t.cfg2tmc_xm2comp_drvup, new_value_t.cfg2tmc_xm2comp_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "MEM_COMP Pad Control Registers";
}

#define GP_XM2VTTGENPADCTRL_OFFSET 0x8D8
#define GP_XM2VTTGENPADCTRL_UNDEFMASK 0xF8F888FC
union gp_xm2vttgenpadctrl_u {
    struct {
        unsigned int cfg2tmc_xm2vttgen_short:1;
        unsigned int cfg2tmc_xm2vttgen_short_pwrgnd:1;/* dummy pin */
        unsigned int undefined_bits_2_7:6;
        unsigned int cfg2tmc_xm2vttgen_vclamp_level:3;
        unsigned int undefined_bit_11:1;
        unsigned int cfg2tmc_xm2vttgen_vauxp_level:3;
        unsigned int undefined_bit_15:1;
        unsigned int cfg2tmc_xm2vttgen_cal_drvdn:3;
        unsigned int undefined_bits_19_23:5;
        unsigned int cfg2tmc_xm2vttgen_cal_drvup:3;
        unsigned int undefined_bits_27_31:5;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2vttgenpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2vttgenpadctrl_u old_value_t = { .reg32 = value };
    const gp_xm2vttgenpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg2tmc_xm2vttgen_short:1", "", 1, old_value_t.cfg2tmc_xm2vttgen_short, new_value_t.cfg2tmc_xm2vttgen_short };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cfg2tmc_xm2vttgen_short_pwrgnd:1",
              "dummy pin",
              1, old_value_t.cfg2tmc_xm2vttgen_short_pwrgnd, new_value_t.cfg2tmc_xm2vttgen_short_pwrgnd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cfg2tmc_xm2vttgen_vclamp_level:3", "", 3, old_value_t.cfg2tmc_xm2vttgen_vclamp_level, new_value_t.cfg2tmc_xm2vttgen_vclamp_level };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bit_11:1", "", 1, old_value_t.undefined_bit_11, new_value_t.undefined_bit_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_xm2vttgen_vauxp_level:3", "", 3, old_value_t.cfg2tmc_xm2vttgen_vauxp_level, new_value_t.cfg2tmc_xm2vttgen_vauxp_level };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bit_15:1", "", 1, old_value_t.undefined_bit_15, new_value_t.undefined_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg2tmc_xm2vttgen_cal_drvdn:3", "", 3, old_value_t.cfg2tmc_xm2vttgen_cal_drvdn, new_value_t.cfg2tmc_xm2vttgen_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2vttgen_cal_drvup:3", "", 3, old_value_t.cfg2tmc_xm2vttgen_cal_drvup, new_value_t.cfg2tmc_xm2vttgen_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bits_27_31:5", "", 5, old_value_t.undefined_bits_27_31, new_value_t.undefined_bits_27_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XM2 MISC/VTTGEN Pad control register";
}

#define GP_PADCTL_DFT_OFFSET 0x8DC
#define GP_PADCTL_DFT_UNDEFMASK 0xFFFFFFFC
union gp_padctl_dft_u {
    struct {
        unsigned int pinshort_en:1;         /* Enable pin-shorting for tester mode pin-shorting 0 = DISABLE 1 = ENABLE */
        unsigned int pinshort_sel:1;        /* Select which pins are used for test-mode observe */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_padctl_dft_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_padctl_dft_u old_value_t = { .reg32 = value };
    const gp_padctl_dft_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pinshort_en:1",
              "Enable pin-shorting for tester mode pin-shorting\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pinshort_en, new_value_t.pinshort_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: pinshort_sel:1",
              "Select which pins are used for test-mode observe",
              1, old_value_t.pinshort_sel, new_value_t.pinshort_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DFT Pin shorting";
}

#define GP_SDIO1CFGPADCTRL_OFFSET 0x8E0
#define GP_SDIO1CFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_sdio1cfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_sdio1cfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_sdio1cfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_sdio1cfg_lpmd:2;/* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_sdio1cfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_sdio1cfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_sdio1cfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_sdio1cfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_sdio1cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_sdio1cfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_sdio1cfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_sdio1cfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_sdio1cfg_hsm_en, new_value_t.cfg2tmc_sdio1cfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_sdio1cfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_sdio1cfg_schmt_en, new_value_t.cfg2tmc_sdio1cfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_sdio1cfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_sdio1cfg_lpmd, new_value_t.cfg2tmc_sdio1cfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_sdio1cfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_sdio1cfg_cal_drvdn, new_value_t.cfg2tmc_sdio1cfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_sdio1cfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_sdio1cfg_cal_drvup, new_value_t.cfg2tmc_sdio1cfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_sdio1cfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_sdio1cfg_cal_drvdn_slwr, new_value_t.cfg2tmc_sdio1cfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_sdio1cfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_sdio1cfg_cal_drvup_slwf, new_value_t.cfg2tmc_sdio1cfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "SDIO1CFG Pad control register";
}

#define GP_XM2CFGCPADCTRL2_OFFSET 0x8E4
#define GP_XM2CFGCPADCTRL2_UNDEFMASK 0xF0F0FF00
union gp_xm2cfgcpadctrl2_u {
    struct {
        unsigned int cfg2tmc_xm2cfgc_rx_ft_rec_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_bypass_en:1;/* XM2CFGD data pins bypass outbound flop enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_preemp_en:1;/* XM2CFGD data pins preemp enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_ctt_hiz_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_vref_dqs_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_vref_dq_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgc_clksel_dq:1;
        unsigned int cfg2tmc_xm2cfgc_clksel_dqs:1;
        unsigned int undefined_bits_8_15:8;
        unsigned int cfg2tmc_xm2cfgc_vref_dqs:4;
        unsigned int undefined_bits_20_23:4;
        unsigned int cfg2tmc_xm2cfgc_vref_dq:4;
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2cfgcpadctrl2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2cfgcpadctrl2_u old_value_t = { .reg32 = value };
    const gp_xm2cfgcpadctrl2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg2tmc_xm2cfgc_rx_ft_rec_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_rx_ft_rec_en, new_value_t.cfg2tmc_xm2cfgc_rx_ft_rec_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cfg2tmc_xm2cfgc_bypass_en:1",
              "XM2CFGD data pins bypass outbound flop enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_bypass_en, new_value_t.cfg2tmc_xm2cfgc_bypass_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_xm2cfgc_preemp_en:1",
              "XM2CFGD data pins preemp enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_preemp_en, new_value_t.cfg2tmc_xm2cfgc_preemp_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_xm2cfgc_ctt_hiz_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_ctt_hiz_en, new_value_t.cfg2tmc_xm2cfgc_ctt_hiz_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_xm2cfgc_vref_dqs_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_vref_dqs_en, new_value_t.cfg2tmc_xm2cfgc_vref_dqs_en };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cfg2tmc_xm2cfgc_vref_dq_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgc_vref_dq_en, new_value_t.cfg2tmc_xm2cfgc_vref_dq_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cfg2tmc_xm2cfgc_clksel_dq:1", "", 1, old_value_t.cfg2tmc_xm2cfgc_clksel_dq, new_value_t.cfg2tmc_xm2cfgc_clksel_dq };
    m_bit_details_model.bits.append(entry);
    entry = { "07: cfg2tmc_xm2cfgc_clksel_dqs:1", "", 1, old_value_t.cfg2tmc_xm2cfgc_clksel_dqs, new_value_t.cfg2tmc_xm2cfgc_clksel_dqs };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg2tmc_xm2cfgc_vref_dqs:4", "", 4, old_value_t.cfg2tmc_xm2cfgc_vref_dqs, new_value_t.cfg2tmc_xm2cfgc_vref_dqs };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2cfgc_vref_dq:4", "", 4, old_value_t.cfg2tmc_xm2cfgc_vref_dq, new_value_t.cfg2tmc_xm2cfgc_vref_dq };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XM2CFGC Pad control register";
}

#define GP_XM2CFGDPADCTRL2_OFFSET 0x8E8
#define GP_XM2CFGDPADCTRL2_UNDEFMASK 0x8888FFF0
union gp_xm2cfgdpadctrl2_u {
    struct {
        unsigned int cfg2tmc_xm2cfgd_rx_ft_rec_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgd_bypass_en:1;/* XM2CFGD data pins bypass outbound flop enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgd_preemp_en:1;/* XM2CFGD data pins preemp enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_xm2cfgd_ctt_hiz_en:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_4_15:12;
        unsigned int cfg2tmc_xm2cfgd0_dlyin_trm:3;/* delay trim for byte 0 */
        unsigned int undefined_bit_19:1;
        unsigned int cfg2tmc_xm2cfgd1_dlyin_trm:3;/* delay trim for byte 1 */
        unsigned int undefined_bit_23:1;
        unsigned int cfg2tmc_xm2cfgd2_dlyin_trm:3;/* delay trim for byte 2 */
        unsigned int undefined_bit_27:1;
        unsigned int cfg2tmc_xm2cfgd3_dlyin_trm:3;/* delay trim for byte 3 */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_xm2cfgdpadctrl2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_xm2cfgdpadctrl2_u old_value_t = { .reg32 = value };
    const gp_xm2cfgdpadctrl2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg2tmc_xm2cfgd_rx_ft_rec_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgd_rx_ft_rec_en, new_value_t.cfg2tmc_xm2cfgd_rx_ft_rec_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cfg2tmc_xm2cfgd_bypass_en:1",
              "XM2CFGD data pins bypass outbound flop enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgd_bypass_en, new_value_t.cfg2tmc_xm2cfgd_bypass_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_xm2cfgd_preemp_en:1",
              "XM2CFGD data pins preemp enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgd_preemp_en, new_value_t.cfg2tmc_xm2cfgd_preemp_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_xm2cfgd_ctt_hiz_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_xm2cfgd_ctt_hiz_en, new_value_t.cfg2tmc_xm2cfgd_ctt_hiz_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_15:12", "", 12, old_value_t.undefined_bits_4_15, new_value_t.undefined_bits_4_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg2tmc_xm2cfgd0_dlyin_trm:3",
              "delay trim for byte 0",
              3, old_value_t.cfg2tmc_xm2cfgd0_dlyin_trm, new_value_t.cfg2tmc_xm2cfgd0_dlyin_trm };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bit_19:1", "", 1, old_value_t.undefined_bit_19, new_value_t.undefined_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_xm2cfgd1_dlyin_trm:3",
              "delay trim for byte 1",
              3, old_value_t.cfg2tmc_xm2cfgd1_dlyin_trm, new_value_t.cfg2tmc_xm2cfgd1_dlyin_trm };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bit_23:1", "", 1, old_value_t.undefined_bit_23, new_value_t.undefined_bit_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg2tmc_xm2cfgd2_dlyin_trm:3",
              "delay trim for byte 2",
              3, old_value_t.cfg2tmc_xm2cfgd2_dlyin_trm, new_value_t.cfg2tmc_xm2cfgd2_dlyin_trm };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bit_27:1", "", 1, old_value_t.undefined_bit_27, new_value_t.undefined_bit_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_xm2cfgd3_dlyin_trm:3",
              "delay trim for byte 3",
              3, old_value_t.cfg2tmc_xm2cfgd3_dlyin_trm, new_value_t.cfg2tmc_xm2cfgd3_dlyin_trm };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XM2CFGD Pad control register";
}

#define GP_CRTCFGPADCTRL_OFFSET 0x8EC
#define GP_CRTCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_crtcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_crtcfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_crtcfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_crtcfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_crtcfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_crtcfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_crtcfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_crtcfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_crtcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_crtcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_crtcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_crtcfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_crtcfg_hsm_en, new_value_t.cfg2tmc_crtcfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_crtcfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_crtcfg_schmt_en, new_value_t.cfg2tmc_crtcfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_crtcfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_crtcfg_lpmd, new_value_t.cfg2tmc_crtcfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_crtcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_crtcfg_cal_drvdn, new_value_t.cfg2tmc_crtcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_crtcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_crtcfg_cal_drvup, new_value_t.cfg2tmc_crtcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_crtcfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_crtcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_crtcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_crtcfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_crtcfg_cal_drvup_slwf, new_value_t.cfg2tmc_crtcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CRTCFG Pad control register";
}

#define GP_DDCCFGPADCTRL_OFFSET 0x8F0
#define GP_DDCCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_ddccfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_ddccfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_ddccfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_ddccfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_ddccfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_ddccfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_ddccfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_ddccfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_ddccfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_ddccfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_ddccfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_ddccfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_ddccfg_hsm_en, new_value_t.cfg2tmc_ddccfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_ddccfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_ddccfg_schmt_en, new_value_t.cfg2tmc_ddccfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_ddccfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_ddccfg_lpmd, new_value_t.cfg2tmc_ddccfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_ddccfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_ddccfg_cal_drvdn, new_value_t.cfg2tmc_ddccfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_ddccfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_ddccfg_cal_drvup, new_value_t.cfg2tmc_ddccfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_ddccfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_ddccfg_cal_drvdn_slwr, new_value_t.cfg2tmc_ddccfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_ddccfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_ddccfg_cal_drvup_slwf, new_value_t.cfg2tmc_ddccfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DDCCFG Pad control register";
}

#define GP_GMACFGPADCTRL_OFFSET 0x8F4
#define GP_GMACFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_gmacfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_gmacfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmacfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmacfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_gmacfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_gmacfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_gmacfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_gmacfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_gmacfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_gmacfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_gmacfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_gmacfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmacfg_hsm_en, new_value_t.cfg2tmc_gmacfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_gmacfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmacfg_schmt_en, new_value_t.cfg2tmc_gmacfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_gmacfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_gmacfg_lpmd, new_value_t.cfg2tmc_gmacfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_gmacfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_gmacfg_cal_drvdn, new_value_t.cfg2tmc_gmacfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_gmacfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_gmacfg_cal_drvup, new_value_t.cfg2tmc_gmacfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_gmacfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_gmacfg_cal_drvdn_slwr, new_value_t.cfg2tmc_gmacfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_gmacfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_gmacfg_cal_drvup_slwf, new_value_t.cfg2tmc_gmacfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GMACFG Pad control register";
}

#define GP_GMBCFGPADCTRL_OFFSET 0x8F8
#define GP_GMBCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_gmbcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_gmbcfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmbcfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmbcfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_gmbcfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_gmbcfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_gmbcfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_gmbcfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_gmbcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_gmbcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_gmbcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_gmbcfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmbcfg_hsm_en, new_value_t.cfg2tmc_gmbcfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_gmbcfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmbcfg_schmt_en, new_value_t.cfg2tmc_gmbcfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_gmbcfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_gmbcfg_lpmd, new_value_t.cfg2tmc_gmbcfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_gmbcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_gmbcfg_cal_drvdn, new_value_t.cfg2tmc_gmbcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_gmbcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_gmbcfg_cal_drvup, new_value_t.cfg2tmc_gmbcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_gmbcfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_gmbcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_gmbcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_gmbcfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_gmbcfg_cal_drvup_slwf, new_value_t.cfg2tmc_gmbcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GMBCFG Pad control register";
}

#define GP_GMCCFGPADCTRL_OFFSET 0x8FC
#define GP_GMCCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_gmccfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_gmccfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmccfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmccfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_gmccfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_gmccfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_gmccfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_gmccfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_gmccfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_gmccfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_gmccfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_gmccfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmccfg_hsm_en, new_value_t.cfg2tmc_gmccfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_gmccfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmccfg_schmt_en, new_value_t.cfg2tmc_gmccfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_gmccfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_gmccfg_lpmd, new_value_t.cfg2tmc_gmccfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_gmccfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_gmccfg_cal_drvdn, new_value_t.cfg2tmc_gmccfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_gmccfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_gmccfg_cal_drvup, new_value_t.cfg2tmc_gmccfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_gmccfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_gmccfg_cal_drvdn_slwr, new_value_t.cfg2tmc_gmccfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_gmccfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_gmccfg_cal_drvup_slwf, new_value_t.cfg2tmc_gmccfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GMCCFG Pad control register";
}

#define GP_GMDCFGPADCTRL_OFFSET 0x900
#define GP_GMDCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_gmdcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_gmdcfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmdcfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmdcfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_gmdcfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_gmdcfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_gmdcfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_gmdcfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_gmdcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_gmdcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_gmdcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_gmdcfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmdcfg_hsm_en, new_value_t.cfg2tmc_gmdcfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_gmdcfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmdcfg_schmt_en, new_value_t.cfg2tmc_gmdcfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_gmdcfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_gmdcfg_lpmd, new_value_t.cfg2tmc_gmdcfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_gmdcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_gmdcfg_cal_drvdn, new_value_t.cfg2tmc_gmdcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_gmdcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_gmdcfg_cal_drvup, new_value_t.cfg2tmc_gmdcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_gmdcfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_gmdcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_gmdcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_gmdcfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_gmdcfg_cal_drvup_slwf, new_value_t.cfg2tmc_gmdcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GMDCFG Pad control register";
}

#define GP_GMECFGPADCTRL_OFFSET 0x904
#define GP_GMECFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_gmecfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_gmecfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmecfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_gmecfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_gmecfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_gmecfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_gmecfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_gmecfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_gmecfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_gmecfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_gmecfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_gmecfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmecfg_hsm_en, new_value_t.cfg2tmc_gmecfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_gmecfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_gmecfg_schmt_en, new_value_t.cfg2tmc_gmecfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_gmecfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_gmecfg_lpmd, new_value_t.cfg2tmc_gmecfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_gmecfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_gmecfg_cal_drvdn, new_value_t.cfg2tmc_gmecfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_gmecfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_gmecfg_cal_drvup, new_value_t.cfg2tmc_gmecfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_gmecfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_gmecfg_cal_drvdn_slwr, new_value_t.cfg2tmc_gmecfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_gmecfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_gmecfg_cal_drvup_slwf, new_value_t.cfg2tmc_gmecfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GMECFG Pad control register";
}

#define GP_OWRCFGPADCTRL_OFFSET 0x908
#define GP_OWRCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_owrcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_owrcfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_owrcfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_owrcfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_owrcfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_owrcfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_owrcfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_owrcfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_owrcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_owrcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_owrcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_owrcfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_owrcfg_hsm_en, new_value_t.cfg2tmc_owrcfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_owrcfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_owrcfg_schmt_en, new_value_t.cfg2tmc_owrcfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_owrcfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_owrcfg_lpmd, new_value_t.cfg2tmc_owrcfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_owrcfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_owrcfg_cal_drvdn, new_value_t.cfg2tmc_owrcfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_owrcfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_owrcfg_cal_drvup, new_value_t.cfg2tmc_owrcfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_owrcfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_owrcfg_cal_drvdn_slwr, new_value_t.cfg2tmc_owrcfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_owrcfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_owrcfg_cal_drvup_slwf, new_value_t.cfg2tmc_owrcfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "OWRCFG Pad control register";
}

#define GP_UADCFGPADCTRL_OFFSET 0x90C
#define GP_UADCFGPADCTRL_UNDEFMASK 0x0E0E0FC3
union gp_uadcfgpadctrl_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int cfg2tmc_udacfg_hsm_en:1;/* SDIO3CFG data pins high speed mode enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_udacfg_schmt_en:1;/* SDIO3CFG data pins schmidt enable 0 = DISABLE 1 = ENABLE */
        unsigned int cfg2tmc_udacfg_lpmd:2; /* SDIO3CFG data pins low power mode select */
        unsigned int undefined_bits_6_11:6;
        unsigned int cfg2tmc_udacfg_cal_drvdn:5;
        unsigned int undefined_bits_17_19:3;
        unsigned int cfg2tmc_udacfg_cal_drvup:5;
        unsigned int undefined_bits_25_27:3;
        unsigned int cfg2tmc_udacfg_cal_drvdn_slwr:2;
        unsigned int cfg2tmc_udacfg_cal_drvup_slwf:2;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_gp_uadcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gp_uadcfgpadctrl_u old_value_t = { .reg32 = value };
    const gp_uadcfgpadctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg2tmc_udacfg_hsm_en:1",
              "SDIO3CFG data pins high speed mode enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_udacfg_hsm_en, new_value_t.cfg2tmc_udacfg_hsm_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg2tmc_udacfg_schmt_en:1",
              "SDIO3CFG data pins schmidt enable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg2tmc_udacfg_schmt_en, new_value_t.cfg2tmc_udacfg_schmt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg2tmc_udacfg_lpmd:2",
              "SDIO3CFG data pins low power mode select",
              2, old_value_t.cfg2tmc_udacfg_lpmd, new_value_t.cfg2tmc_udacfg_lpmd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_11:6", "", 6, old_value_t.undefined_bits_6_11, new_value_t.undefined_bits_6_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg2tmc_udacfg_cal_drvdn:5", "", 5, old_value_t.cfg2tmc_udacfg_cal_drvdn, new_value_t.cfg2tmc_udacfg_cal_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cfg2tmc_udacfg_cal_drvup:5", "", 5, old_value_t.cfg2tmc_udacfg_cal_drvup, new_value_t.cfg2tmc_udacfg_cal_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_27:3", "", 3, old_value_t.undefined_bits_25_27, new_value_t.undefined_bits_25_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg2tmc_udacfg_cal_drvdn_slwr:2", "", 2, old_value_t.cfg2tmc_udacfg_cal_drvdn_slwr, new_value_t.cfg2tmc_udacfg_cal_drvdn_slwr };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cfg2tmc_udacfg_cal_drvup_slwf:2", "", 2, old_value_t.cfg2tmc_udacfg_cal_drvup_slwf, new_value_t.cfg2tmc_udacfg_cal_drvup_slwf };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "UDACFG Pad control register";
}

#define DAS_DAP_CTRL_SEL_OFFSET 0xC00
#define DAS_DAP_CTRL_SEL_UNDEFMASK 0x1FFFFFE0
union das_dap_ctrl_sel_u {
    struct {
        unsigned int dap_ctrl_sel:5;        /* DAP selection bits to select one of the three DACs or one of the five DAPs 0 = DAC1 1 = DAC2 2 = DAC3 16 = DAP1 17 = DAP2 18 = DAP3 19 = DAP4 20 = DAP5 | */
        unsigned int undefined_bits_5_28:24;
        unsigned int dap_sdata2_rx_tx:1;    /* To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode 0 = RX 1 = TX */
        unsigned int dap_sdata1_tx_rx:1;    /* To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode 0 = TX 1 = RX */
        unsigned int dap_ms_sel:1;          /* This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode. 0 = SLAVE 1 = MASTER */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dap_ctrl_sel_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dap_ctrl_sel_u old_value_t = { .reg32 = value };
    const das_dap_ctrl_sel_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dap_ctrl_sel:5",
              "DAP selection bits to select one of the three DACs or one of the five DAPs\n0 = DAC1\n1 = DAC2\n2 = DAC3\n16 = DAP1\n17 = DAP2\n18 = DAP3\n19 = DAP4\n20 = DAP5 |",
              5, old_value_t.dap_ctrl_sel, new_value_t.dap_ctrl_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_28:24", "", 24, old_value_t.undefined_bits_5_28, new_value_t.undefined_bits_5_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: dap_sdata2_rx_tx:1",
              "To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode\n0 = RX\n1 = TX",
              1, old_value_t.dap_sdata2_rx_tx, new_value_t.dap_sdata2_rx_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dap_sdata1_tx_rx:1",
              "To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode\n0 = TX\n1 = RX",
              1, old_value_t.dap_sdata1_tx_rx, new_value_t.dap_sdata1_tx_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dap_ms_sel:1",
              "This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode.\n0 = SLAVE\n1 = MASTER",
              1, old_value_t.dap_ms_sel, new_value_t.dap_ms_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DAP Control Register\nThis is an array of 5 identical register entries; the register fields below apply to each entry.";
}

#define DAS_DAC_INPUT_DATA_CLK_SEL_OFFSET 0xC40
#define DAS_DAC_INPUT_DATA_CLK_SEL_UNDEFMASK 0x00FFFFF0
union das_dac_input_data_clk_sel_u {
    struct {
        unsigned int dac_clk_sel:4;         /* These bits are to control the selection of bit clock and fsync for DACs. 0 = DAP1 1 = DAP2 2 = DAP3 3 = DAP4 4 = DAP5 */
        unsigned int undefined_bits_4_23:20;
        unsigned int dac_sdata1_sel:4;      /* These bits are to control the selection of sdata1 input for DACs. 0 = DAP1 1 = DAP2 2 = DAP3 3 = DAP4 4 = DAP5 */
        unsigned int dac_sdata2_sel:4;      /* These bits are to control the selection of sdata2 input for DACs.  0 = DAP1 1 = DAP2 2 = DAP3 3 = DAP4 4 = DAP5 */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dac_input_data_clk_sel_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dac_input_data_clk_sel_u old_value_t = { .reg32 = value };
    const das_dac_input_data_clk_sel_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_clk_sel:4",
              "These bits are to control the selection of bit clock and fsync for DACs.\n0 = DAP1\n1 = DAP2\n2 = DAP3\n3 = DAP4\n4 = DAP5",
              4, old_value_t.dac_clk_sel, new_value_t.dac_clk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_23:20", "", 20, old_value_t.undefined_bits_4_23, new_value_t.undefined_bits_4_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dac_sdata1_sel:4",
              "These bits are to control the selection of sdata1 input for DACs.\n0 = DAP1\n1 = DAP2\n2 = DAP3\n3 = DAP4\n4 = DAP5",
              4, old_value_t.dac_sdata1_sel, new_value_t.dac_sdata1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dac_sdata2_sel:4",
              "These bits are to control the selection of sdata2 input for DACs.\n0 = DAP1\n1 = DAP2\n2 = DAP3\n3 = DAP4\n4 = DAP5",
              4, old_value_t.dac_sdata2_sel, new_value_t.dac_sdata2_sel };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DAC Input Data Selections\nThis is an array of 3 identical register entries; the register fields below apply to each entry.";
}

#define PP_MISC_SAVE_THE_DAY_OFFSET 0x7C
#define PP_MISC_SAVE_THE_DAY_UNDEFMASK 0x00000000
union pp_misc_save_the_day_u {
    struct {
        unsigned int save_the_day_d:8;      /* Reserved */
        unsigned int save_the_day_c:8;      /* Reserved */
        unsigned int save_the_day_b:8;      /* Reserved */
        unsigned int save_the_day_a:8;      /* Reserved */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_pp_misc_save_the_day_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pp_misc_save_the_day_u old_value_t = { .reg32 = value };
    const pp_misc_save_the_day_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: save_the_day_d:8",
              "Reserved",
              8, old_value_t.save_the_day_d, new_value_t.save_the_day_d };
    m_bit_details_model.bits.append(entry);
    entry = { "08: save_the_day_c:8",
              "Reserved",
              8, old_value_t.save_the_day_c, new_value_t.save_the_day_c };
    m_bit_details_model.bits.append(entry);
    entry = { "16: save_the_day_b:8",
              "Reserved",
              8, old_value_t.save_the_day_b, new_value_t.save_the_day_b };
    m_bit_details_model.bits.append(entry);
    entry = { "24: save_the_day_a:8",
              "Reserved",
              8, old_value_t.save_the_day_a, new_value_t.save_the_day_a };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_COREPWRCONFIG_OFFSET 0x400
#define ASYNC_COREPWRCONFIG_UNDEFMASK 0xFFFFFFF8
union async_corepwrconfig_u {
    struct {
        unsigned int td_corepwr_en:1;       /* Power is on in TDA/TDB partitions */
        unsigned int ve_corepwr_en:1;       /* Power is on in VE/MPE partitions */
        unsigned int cpu_corepwr_en:1;      /* Power is on in CPU partition */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_corepwrconfig_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_corepwrconfig_u old_value_t = { .reg32 = value };
    const async_corepwrconfig_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: td_corepwr_en:1",
              "Power is on in TDA/TDB partitions",
              1, old_value_t.td_corepwr_en, new_value_t.td_corepwr_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ve_corepwr_en:1",
              "Power is on in VE/MPE partitions",
              1, old_value_t.ve_corepwr_en, new_value_t.ve_corepwr_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cpu_corepwr_en:1",
              "Power is on in CPU partition",
              1, old_value_t.cpu_corepwr_en, new_value_t.cpu_corepwr_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_EMCPADEN_OFFSET 0x410
#define ASYNC_EMCPADEN_UNDEFMASK 0xFFFFFFFC
union async_emcpaden_u {
    struct {
        unsigned int emc_pad_output_en:1;   /* outputs enable for EMC pads */
        unsigned int emc_pad_input_en:1;    /* inputs enable for EMC pads */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_emcpaden_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_emcpaden_u old_value_t = { .reg32 = value };
    const async_emcpaden_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_pad_output_en:1",
              "outputs enable for EMC pads",
              1, old_value_t.emc_pad_output_en, new_value_t.emc_pad_output_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: emc_pad_input_en:1",
              "inputs enable for EMC pads",
              1, old_value_t.emc_pad_input_en, new_value_t.emc_pad_input_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_VCLKCTRL_OFFSET 0x42C
#define ASYNC_VCLKCTRL_UNDEFMASK 0xFFFFFFFC
union async_vclkctrl_u {
    struct {
        unsigned int vclk_pad_ie:1;         /* VCLK input enable */
        unsigned int vclk_pad_inversion:1;  /* VCLK invert enable */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_vclkctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_vclkctrl_u old_value_t = { .reg32 = value };
    const async_vclkctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vclk_pad_ie:1",
              "VCLK input enable",
              1, old_value_t.vclk_pad_ie, new_value_t.vclk_pad_ie };
    m_bit_details_model.bits.append(entry);
    entry = { "01: vclk_pad_inversion:1",
              "VCLK invert enable",
              1, old_value_t.vclk_pad_inversion, new_value_t.vclk_pad_inversion };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_TVDACVHSYNCCTRL_OFFSET 0x438
#define ASYNC_TVDACVHSYNCCTRL_UNDEFMASK 0xFFFFFFF0
union async_tvdacvhsyncctrl_u {
    struct {
        unsigned int tvdac_hsyncdly:2;
        unsigned int tvdac_vsyncdly:2;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_tvdacvhsyncctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_tvdacvhsyncctrl_u old_value_t = { .reg32 = value };
    const async_tvdacvhsyncctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tvdac_hsyncdly:2", "", 2, old_value_t.tvdac_hsyncdly, new_value_t.tvdac_hsyncdly };
    m_bit_details_model.bits.append(entry);
    entry = { "02: tvdac_vsyncdly:2", "", 2, old_value_t.tvdac_vsyncdly, new_value_t.tvdac_vsyncdly };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_TVDACCNTL_OFFSET 0x43C
#define ASYNC_TVDACCNTL_UNDEFMASK 0xE1000000
union async_tvdaccntl_u {
    struct {
        unsigned int dac_iddq:1;            /* Power down everything including the band-gap */
        unsigned int dac_powerdown:1;       /* Power down everything except the band-gap */
        unsigned int dac_detect_en:1;       /* Power down everything including the band-gap */
        unsigned int dac_sleepr:1;          /* Low power (sleep) mode. SHut down OUTR output */
        unsigned int dac_sleepg:1;          /* Low power (sleep) mode. SHut down OUTG output */
        unsigned int dac_sleepb:1;          /* Low power (sleep) mode. SHut down OUTB output */
        unsigned int dac_comp_th:2;         /* Adjust threshold voltage of comparator inside DAC */
        unsigned int dac_bgap_avg_on:1;     /* Turn bandgap averaging on/off */
        unsigned int dac_bgap_curve:3;      /* To adjust temp coeff */
        unsigned int dac_bgap_cntl:4;       /* Control bits for bandgap */
        unsigned int dac_atest:3;           /* For debugging. Selects internal analog output to be sent out of VREF pin */
        unsigned int dac_cntl:5;            /* Reserved for additional control */
        unsigned int undefined_bit_24:1;
        unsigned int dac_compr_en:1;        /* Enable COMPOUTR output */
        unsigned int dac_compg_en:1;        /* Enable COMPOUTG output */
        unsigned int dac_compb_en:1;        /* Enable COMPOUTB output */
        unsigned int dac_plug_ok:1;         /* Indicate load status */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_tvdaccntl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_tvdaccntl_u old_value_t = { .reg32 = value };
    const async_tvdaccntl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_iddq:1",
              "Power down everything including the band-gap",
              1, old_value_t.dac_iddq, new_value_t.dac_iddq };
    m_bit_details_model.bits.append(entry);
    entry = { "01: dac_powerdown:1",
              "Power down everything except the band-gap",
              1, old_value_t.dac_powerdown, new_value_t.dac_powerdown };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dac_detect_en:1",
              "Power down everything including the band-gap",
              1, old_value_t.dac_detect_en, new_value_t.dac_detect_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dac_sleepr:1",
              "Low power (sleep) mode. SHut down OUTR output",
              1, old_value_t.dac_sleepr, new_value_t.dac_sleepr };
    m_bit_details_model.bits.append(entry);
    entry = { "04: dac_sleepg:1",
              "Low power (sleep) mode. SHut down OUTG output",
              1, old_value_t.dac_sleepg, new_value_t.dac_sleepg };
    m_bit_details_model.bits.append(entry);
    entry = { "05: dac_sleepb:1",
              "Low power (sleep) mode. SHut down OUTB output",
              1, old_value_t.dac_sleepb, new_value_t.dac_sleepb };
    m_bit_details_model.bits.append(entry);
    entry = { "06: dac_comp_th:2",
              "Adjust threshold voltage of comparator inside DAC",
              2, old_value_t.dac_comp_th, new_value_t.dac_comp_th };
    m_bit_details_model.bits.append(entry);
    entry = { "08: dac_bgap_avg_on:1",
              "Turn bandgap averaging on/off",
              1, old_value_t.dac_bgap_avg_on, new_value_t.dac_bgap_avg_on };
    m_bit_details_model.bits.append(entry);
    entry = { "09: dac_bgap_curve:3",
              "To adjust temp coeff",
              3, old_value_t.dac_bgap_curve, new_value_t.dac_bgap_curve };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dac_bgap_cntl:4",
              "Control bits for bandgap",
              4, old_value_t.dac_bgap_cntl, new_value_t.dac_bgap_cntl };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dac_atest:3",
              "For debugging. Selects internal analog output to be sent out of VREF pin",
              3, old_value_t.dac_atest, new_value_t.dac_atest };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dac_cntl:5",
              "Reserved for additional control",
              5, old_value_t.dac_cntl, new_value_t.dac_cntl };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: dac_compr_en:1",
              "Enable COMPOUTR output",
              1, old_value_t.dac_compr_en, new_value_t.dac_compr_en };
    m_bit_details_model.bits.append(entry);
    entry = { "26: dac_compg_en:1",
              "Enable COMPOUTG output",
              1, old_value_t.dac_compg_en, new_value_t.dac_compg_en };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dac_compb_en:1",
              "Enable COMPOUTB output",
              1, old_value_t.dac_compb_en, new_value_t.dac_compb_en };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dac_plug_ok:1",
              "Indicate load status",
              1, old_value_t.dac_plug_ok, new_value_t.dac_plug_ok };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_TVDACSTATUS_OFFSET 0x440
#define ASYNC_TVDACSTATUS_UNDEFMASK 0xFFFFFFF8
union async_tvdacstatus_u {
    struct {
        unsigned int dac_compoutr:1;        /* Channel R comparator output for auto-detect 0 = COMPINR > threshold 1 = COMPINR < threshold, or when POWERDOWN==1 comparison threshold = 0.325V */
        unsigned int dac_compoutg:1;        /* Channel G comparator output for auto-detect 0 = COMPING > threshold 1 = COMPING < threshold, or when POWERDOWN==1 comparison threshold = 0.325V */
        unsigned int dac_compoutb:1;        /* Channel B comparator output for auto-detect 0 = COMPINB > threshold 1 = COMPINB < threshold, or when POWERDOWN==1 comparison threshold = 0.325V */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_tvdacstatus_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_tvdacstatus_u old_value_t = { .reg32 = value };
    const async_tvdacstatus_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_compoutr:1",
              "Channel R comparator output for auto-detect\n0 = COMPINR > threshold\n1 = COMPINR < threshold, or when POWERDOWN==1 comparison threshold = 0.325V",
              1, old_value_t.dac_compoutr, new_value_t.dac_compoutr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: dac_compoutg:1",
              "Channel G comparator output for auto-detect\n0 = COMPING > threshold\n1 = COMPING < threshold, or when POWERDOWN==1 comparison threshold = 0.325V",
              1, old_value_t.dac_compoutg, new_value_t.dac_compoutg };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dac_compoutb:1",
              "Channel B comparator output for auto-detect\n0 = COMPINB > threshold\n1 = COMPINB < threshold, or when POWERDOWN==1 comparison threshold = 0.325V",
              1, old_value_t.dac_compoutb, new_value_t.dac_compoutb };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_TVDACDINCONFIG_OFFSET 0x444
#define ASYNC_TVDACDINCONFIG_UNDEFMASK 0xF00002C8
union async_tvdacdinconfig_u {
    struct {
        unsigned int dac_fifo_th:3;         /* Data Input FIFO threshold */
        unsigned int undefined_bit_3:1;
        unsigned int dac_source:2;          /* INPUT source for TVDAC */
        unsigned int undefined_bits_6_7:2;
        unsigned int dac_din_oride_en:1;    /* Override DAC DIN inputs */
        unsigned int undefined_bit_9:1;
        unsigned int dac_din_oride:10;      /* DIN override */
        unsigned int dac_ampin:8;           /* AMPIN */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_tvdacdinconfig_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_tvdacdinconfig_u old_value_t = { .reg32 = value };
    const async_tvdacdinconfig_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_fifo_th:3",
              "Data Input FIFO threshold",
              3, old_value_t.dac_fifo_th, new_value_t.dac_fifo_th };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: dac_source:2",
              "INPUT source for TVDAC",
              2, old_value_t.dac_source, new_value_t.dac_source };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: dac_din_oride_en:1",
              "Override DAC DIN inputs",
              1, old_value_t.dac_din_oride_en, new_value_t.dac_din_oride_en };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bit_9:1", "", 1, old_value_t.undefined_bit_9, new_value_t.undefined_bit_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: dac_din_oride:10",
              "DIN override",
              10, old_value_t.dac_din_oride, new_value_t.dac_din_oride };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dac_ampin:8",
              "AMPIN",
              8, old_value_t.dac_ampin, new_value_t.dac_ampin };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_INT_STATUS_OFFSET 0x448
#define ASYNC_INT_STATUS_UNDEFMASK 0xFFFFE07F
union async_int_status_u {
    struct {
        unsigned int undefined_bits_0_6:7;
        unsigned int hgp7_int_status:1;     /* HGP7 Interrupt Status  (this is cleared on write)   0= interrupt not pending   1= interrupt pending */
        unsigned int hgp8_int_status:1;     /* HGP8 Interrupt Status  (this is cleared on write)   0= interrupt not pending   1= interrupt pending */
        unsigned int hgp9_int_status:1;     /* HGP9 Interrupt Status  (this is cleared on write)   0= interrupt not pending   1= interrupt pending */
        unsigned int hgp10_int_status:1;    /* HGP10 Interrupt Status  (this is cleared on write)   0= interrupt not pending   1= interrupt pending */
        unsigned int hgp11_int_status:1;    /* HGP11 Interrupt Status  (this is cleared on write)   0= interrupt not pending   1= interrupt pending */
        unsigned int hgp12_int_status:1;    /* HGP12 Interrupt Status  (this is cleared on write)   0= interrupt not pending   1= interrupt pending */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_int_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_int_status_u old_value_t = { .reg32 = value };
    const async_int_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_6:7", "", 7, old_value_t.undefined_bits_0_6, new_value_t.undefined_bits_0_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: hgp7_int_status:1",
              "HGP7 Interrupt Status  (this is cleared on write)  \n0= interrupt not pending  \n1= interrupt pending",
              1, old_value_t.hgp7_int_status, new_value_t.hgp7_int_status };
    m_bit_details_model.bits.append(entry);
    entry = { "08: hgp8_int_status:1",
              "HGP8 Interrupt Status  (this is cleared on write)  \n0= interrupt not pending  \n1= interrupt pending",
              1, old_value_t.hgp8_int_status, new_value_t.hgp8_int_status };
    m_bit_details_model.bits.append(entry);
    entry = { "09: hgp9_int_status:1",
              "HGP9 Interrupt Status  (this is cleared on write)  \n0= interrupt not pending  \n1= interrupt pending",
              1, old_value_t.hgp9_int_status, new_value_t.hgp9_int_status };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hgp10_int_status:1",
              "HGP10 Interrupt Status  (this is cleared on write)  \n0= interrupt not pending  \n1= interrupt pending",
              1, old_value_t.hgp10_int_status, new_value_t.hgp10_int_status };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hgp11_int_status:1",
              "HGP11 Interrupt Status  (this is cleared on write)  \n0= interrupt not pending  \n1= interrupt pending",
              1, old_value_t.hgp11_int_status, new_value_t.hgp11_int_status };
    m_bit_details_model.bits.append(entry);
    entry = { "12: hgp12_int_status:1",
              "HGP12 Interrupt Status  (this is cleared on write)  \n0= interrupt not pending  \n1= interrupt pending",
              1, old_value_t.hgp12_int_status, new_value_t.hgp12_int_status };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_INT_MASK_OFFSET 0x44C
#define ASYNC_INT_MASK_UNDEFMASK 0xFFFFE07F
union async_int_mask_u {
    struct {
        unsigned int undefined_bits_0_6:7;
        unsigned int hgp7_int_mask:1;       /* HGP7 Interrupt Mask   0= interrupt masked   1= interrupt not masked */
        unsigned int hgp8_int_mask:1;       /* HGP8 Interrupt Mask   0= interrupt masked   1= interrupt not masked */
        unsigned int hgp9_int_mask:1;       /* HGP9 Interrupt Mask   0= interrupt masked   1= interrupt not masked */
        unsigned int hgp10_int_mask:1;      /* HGP10 Interrupt Mask   0= interrupt masked   1= interrupt not masked */
        unsigned int hgp11_int_mask:1;      /* HGP11 Interrupt Mask   0= interrupt masked   1= interrupt not masked */
        unsigned int hgp12_int_mask:1;      /* HGP12 Interrupt Mask   0= interrupt masked   1= interrupt not masked */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_int_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_int_mask_u old_value_t = { .reg32 = value };
    const async_int_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_6:7", "", 7, old_value_t.undefined_bits_0_6, new_value_t.undefined_bits_0_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: hgp7_int_mask:1",
              "HGP7 Interrupt Mask  \n0= interrupt masked  \n1= interrupt not masked",
              1, old_value_t.hgp7_int_mask, new_value_t.hgp7_int_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "08: hgp8_int_mask:1",
              "HGP8 Interrupt Mask  \n0= interrupt masked  \n1= interrupt not masked",
              1, old_value_t.hgp8_int_mask, new_value_t.hgp8_int_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "09: hgp9_int_mask:1",
              "HGP9 Interrupt Mask  \n0= interrupt masked  \n1= interrupt not masked",
              1, old_value_t.hgp9_int_mask, new_value_t.hgp9_int_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hgp10_int_mask:1",
              "HGP10 Interrupt Mask  \n0= interrupt masked  \n1= interrupt not masked",
              1, old_value_t.hgp10_int_mask, new_value_t.hgp10_int_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hgp11_int_mask:1",
              "HGP11 Interrupt Mask  \n0= interrupt masked  \n1= interrupt not masked",
              1, old_value_t.hgp11_int_mask, new_value_t.hgp11_int_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "12: hgp12_int_mask:1",
              "HGP12 Interrupt Mask  \n0= interrupt masked  \n1= interrupt not masked",
              1, old_value_t.hgp12_int_mask, new_value_t.hgp12_int_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_INT_POLARITY_OFFSET 0x450
#define ASYNC_INT_POLARITY_UNDEFMASK 0xFFFFE07F
union async_int_polarity_u {
    struct {
        unsigned int undefined_bits_0_6:7;
        unsigned int hgp7_int_polarity:1;   /* HGP7 Interrupt Polarity   0= falling edge interrupt   1= rising edge interrupt */
        unsigned int hgp8_int_polarity:1;   /* HGP8 Interrupt Polarity   0= falling edge interrupt   1= rising edge interrupt */
        unsigned int hgp9_int_polarity:1;   /* HGP9 Interrupt Polarity   0= falling edge interrupt   1= rising edge interrupt */
        unsigned int hgp10_int_polarity:1;  /* HGP10 Interrupt Polarity   0= falling edge interrupt   1= rising edge interrupt */
        unsigned int hgp11_int_polarity:1;  /* HGP11 Interrupt Polarity   0= falling edge interrupt   1= rising edge interrupt */
        unsigned int hgp12_int_polarity:1;  /* HGP12 Interrupt Polarity   0= falling edge interrupt   1= rising edge interrupt */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_int_polarity_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_int_polarity_u old_value_t = { .reg32 = value };
    const async_int_polarity_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_6:7", "", 7, old_value_t.undefined_bits_0_6, new_value_t.undefined_bits_0_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: hgp7_int_polarity:1",
              "HGP7 Interrupt Polarity  \n0= falling edge interrupt  \n1= rising edge interrupt",
              1, old_value_t.hgp7_int_polarity, new_value_t.hgp7_int_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "08: hgp8_int_polarity:1",
              "HGP8 Interrupt Polarity  \n0= falling edge interrupt  \n1= rising edge interrupt",
              1, old_value_t.hgp8_int_polarity, new_value_t.hgp8_int_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "09: hgp9_int_polarity:1",
              "HGP9 Interrupt Polarity  \n0= falling edge interrupt  \n1= rising edge interrupt",
              1, old_value_t.hgp9_int_polarity, new_value_t.hgp9_int_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hgp10_int_polarity:1",
              "HGP10 Interrupt Polarity  \n0= falling edge interrupt  \n1= rising edge interrupt",
              1, old_value_t.hgp10_int_polarity, new_value_t.hgp10_int_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hgp11_int_polarity:1",
              "HGP11 Interrupt Polarity  \n0= falling edge interrupt  \n1= rising edge interrupt",
              1, old_value_t.hgp11_int_polarity, new_value_t.hgp11_int_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "12: hgp12_int_polarity:1",
              "HGP12 Interrupt Polarity  \n0= falling edge interrupt  \n1= rising edge interrupt",
              1, old_value_t.hgp12_int_polarity, new_value_t.hgp12_int_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define ASYNC_INT_TYPE_SELECT_OFFSET 0x454
#define ASYNC_INT_TYPE_SELECT_UNDEFMASK 0xFFFFE07F
union async_int_type_select_u {
    struct {
        unsigned int undefined_bits_0_6:7;
        unsigned int hgp7_int_type:1;       /* HGP7 Interrupt Type   0= Edge type   1= Level type */
        unsigned int hgp8_int_type:1;       /* HGP8 Interrupt Polarity   0= Edge type   1= Level type */
        unsigned int hgp9_int_type:1;       /* HGP9 Interrupt Polarity   0= Edge type   1= Level type */
        unsigned int hgp10_int_type:1;      /* HGP10 Interrupt Polarity   0= Edge type   1= Level type */
        unsigned int hgp11_int_type:1;      /* HGP11 Interrupt Polarity   0= Edge type   1= Level type */
        unsigned int hgp12_int_type:1;      /* HGP12 Interrupt Polarity   0= Edge type   1= Level type */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_async_int_type_select_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const async_int_type_select_u old_value_t = { .reg32 = value };
    const async_int_type_select_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_6:7", "", 7, old_value_t.undefined_bits_0_6, new_value_t.undefined_bits_0_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: hgp7_int_type:1",
              "HGP7 Interrupt Type  \n0= Edge type  \n1= Level type",
              1, old_value_t.hgp7_int_type, new_value_t.hgp7_int_type };
    m_bit_details_model.bits.append(entry);
    entry = { "08: hgp8_int_type:1",
              "HGP8 Interrupt Polarity  \n0= Edge type  \n1= Level type",
              1, old_value_t.hgp8_int_type, new_value_t.hgp8_int_type };
    m_bit_details_model.bits.append(entry);
    entry = { "09: hgp9_int_type:1",
              "HGP9 Interrupt Polarity  \n0= Edge type  \n1= Level type",
              1, old_value_t.hgp9_int_type, new_value_t.hgp9_int_type };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hgp10_int_type:1",
              "HGP10 Interrupt Polarity  \n0= Edge type  \n1= Level type",
              1, old_value_t.hgp10_int_type, new_value_t.hgp10_int_type };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hgp11_int_type:1",
              "HGP11 Interrupt Polarity  \n0= Edge type  \n1= Level type",
              1, old_value_t.hgp11_int_type, new_value_t.hgp11_int_type };
    m_bit_details_model.bits.append(entry);
    entry = { "12: hgp12_int_type:1",
              "HGP12 Interrupt Polarity  \n0= Edge type  \n1= Level type",
              1, old_value_t.hgp12_int_type, new_value_t.hgp12_int_type };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define DAS_DAP_CTRL_SEL_1_OFFSET 0xC04
#define DAS_DAP_CTRL_SEL_1_UNDEFMASK 0x1FFFFFE0
union das_dap_ctrl_sel_1_u {
    struct {
        unsigned int dap_ctrl_sel:5;        /* DAP selection bits to select one of the three DACs or one of the five DAPs */
        unsigned int undefined_bits_5_28:24;
        unsigned int dap_sdata2_rx_tx:1;    /* To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_sdata1_tx_rx:1;    /* To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_ms_sel:1;          /* This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode. */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dap_ctrl_sel_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dap_ctrl_sel_1_u old_value_t = { .reg32 = value };
    const das_dap_ctrl_sel_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dap_ctrl_sel:5",
              "DAP selection bits to select one of the three DACs or one of the five DAPs",
              5, old_value_t.dap_ctrl_sel, new_value_t.dap_ctrl_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_28:24", "", 24, old_value_t.undefined_bits_5_28, new_value_t.undefined_bits_5_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: dap_sdata2_rx_tx:1",
              "To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata2_rx_tx, new_value_t.dap_sdata2_rx_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dap_sdata1_tx_rx:1",
              "To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata1_tx_rx, new_value_t.dap_sdata1_tx_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dap_ms_sel:1",
              "This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode.",
              1, old_value_t.dap_ms_sel, new_value_t.dap_ms_sel };
    m_bit_details_model.bits.append(entry);
}

#define DAS_DAP_CTRL_SEL_2_OFFSET 0xC08
#define DAS_DAP_CTRL_SEL_2_UNDEFMASK 0x1FFFFFE0
union das_dap_ctrl_sel_2_u {
    struct {
        unsigned int dap_ctrl_sel:5;        /* DAP selection bits to select one of the three DACs or one of the five DAPs */
        unsigned int undefined_bits_5_28:24;
        unsigned int dap_sdata2_rx_tx:1;    /* To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_sdata1_tx_rx:1;    /* To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_ms_sel:1;          /* This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode. */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dap_ctrl_sel_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dap_ctrl_sel_2_u old_value_t = { .reg32 = value };
    const das_dap_ctrl_sel_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dap_ctrl_sel:5",
              "DAP selection bits to select one of the three DACs or one of the five DAPs",
              5, old_value_t.dap_ctrl_sel, new_value_t.dap_ctrl_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_28:24", "", 24, old_value_t.undefined_bits_5_28, new_value_t.undefined_bits_5_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: dap_sdata2_rx_tx:1",
              "To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata2_rx_tx, new_value_t.dap_sdata2_rx_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dap_sdata1_tx_rx:1",
              "To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata1_tx_rx, new_value_t.dap_sdata1_tx_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dap_ms_sel:1",
              "This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode.",
              1, old_value_t.dap_ms_sel, new_value_t.dap_ms_sel };
    m_bit_details_model.bits.append(entry);
}

#define DAS_DAP_CTRL_SEL_3_OFFSET 0xC0C
#define DAS_DAP_CTRL_SEL_3_UNDEFMASK 0x1FFFFFE0
union das_dap_ctrl_sel_3_u {
    struct {
        unsigned int dap_ctrl_sel:5;        /* DAP selection bits to select one of the three DACs or one of the five DAPs */
        unsigned int undefined_bits_5_28:24;
        unsigned int dap_sdata2_rx_tx:1;    /* To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_sdata1_tx_rx:1;    /* To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_ms_sel:1;          /* This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode. */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dap_ctrl_sel_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dap_ctrl_sel_3_u old_value_t = { .reg32 = value };
    const das_dap_ctrl_sel_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dap_ctrl_sel:5",
              "DAP selection bits to select one of the three DACs or one of the five DAPs",
              5, old_value_t.dap_ctrl_sel, new_value_t.dap_ctrl_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_28:24", "", 24, old_value_t.undefined_bits_5_28, new_value_t.undefined_bits_5_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: dap_sdata2_rx_tx:1",
              "To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata2_rx_tx, new_value_t.dap_sdata2_rx_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dap_sdata1_tx_rx:1",
              "To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata1_tx_rx, new_value_t.dap_sdata1_tx_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dap_ms_sel:1",
              "This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode.",
              1, old_value_t.dap_ms_sel, new_value_t.dap_ms_sel };
    m_bit_details_model.bits.append(entry);
}

#define DAS_DAP_CTRL_SEL_4_OFFSET 0xC10
#define DAS_DAP_CTRL_SEL_4_UNDEFMASK 0x1FFFFFE0
union das_dap_ctrl_sel_4_u {
    struct {
        unsigned int dap_ctrl_sel:5;        /* DAP selection bits to select one of the three DACs or one of the five DAPs */
        unsigned int undefined_bits_5_28:24;
        unsigned int dap_sdata2_rx_tx:1;    /* To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_sdata1_tx_rx:1;    /* To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode */
        unsigned int dap_ms_sel:1;          /* This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode. */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dap_ctrl_sel_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dap_ctrl_sel_4_u old_value_t = { .reg32 = value };
    const das_dap_ctrl_sel_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dap_ctrl_sel:5",
              "DAP selection bits to select one of the three DACs or one of the five DAPs",
              5, old_value_t.dap_ctrl_sel, new_value_t.dap_ctrl_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_28:24", "", 24, old_value_t.undefined_bits_5_28, new_value_t.undefined_bits_5_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: dap_sdata2_rx_tx:1",
              "To program sdata2 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata2_rx_tx, new_value_t.dap_sdata2_rx_tx };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dap_sdata1_tx_rx:1",
              "To program sdata1 in either tx or rx mode when two or more DAPs are in by-pass mode",
              1, old_value_t.dap_sdata1_tx_rx, new_value_t.dap_sdata1_tx_rx };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dap_ms_sel:1",
              "This bit is programmed to put particular DAP is either in master or slave mode when two or more DAPs are in by-pass mode.",
              1, old_value_t.dap_ms_sel, new_value_t.dap_ms_sel };
    m_bit_details_model.bits.append(entry);
}

#define DAS_DAC_INPUT_DATA_CLK_SEL_1_OFFSET 0xC44
#define DAS_DAC_INPUT_DATA_CLK_SEL_1_UNDEFMASK 0x00FFFFF0
union das_dac_input_data_clk_sel_1_u {
    struct {
        unsigned int dac_clk_sel:4;         /* These bits are to control the selection of bit clock and fsync for DACs. */
        unsigned int undefined_bits_4_23:20;
        unsigned int dac_sdata1_sel:4;      /* These bits are to control the selection of sdata1 input for DACs. */
        unsigned int dac_sdata2_sel:4;      /* These bits are to control the selection of sdata2 input for DACs.  */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dac_input_data_clk_sel_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dac_input_data_clk_sel_1_u old_value_t = { .reg32 = value };
    const das_dac_input_data_clk_sel_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_clk_sel:4",
              "These bits are to control the selection of bit clock and fsync for DACs.",
              4, old_value_t.dac_clk_sel, new_value_t.dac_clk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_23:20", "", 20, old_value_t.undefined_bits_4_23, new_value_t.undefined_bits_4_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dac_sdata1_sel:4",
              "These bits are to control the selection of sdata1 input for DACs.",
              4, old_value_t.dac_sdata1_sel, new_value_t.dac_sdata1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dac_sdata2_sel:4",
              "These bits are to control the selection of sdata2 input for DACs.",
              4, old_value_t.dac_sdata2_sel, new_value_t.dac_sdata2_sel };
    m_bit_details_model.bits.append(entry);
}

#define DAS_DAC_INPUT_DATA_CLK_SEL_2_OFFSET 0xC48
#define DAS_DAC_INPUT_DATA_CLK_SEL_2_UNDEFMASK 0x00FFFFF0
union das_dac_input_data_clk_sel_2_u {
    struct {
        unsigned int dac_clk_sel:4;         /* These bits are to control the selection of bit clock and fsync for DACs. */
        unsigned int undefined_bits_4_23:20;
        unsigned int dac_sdata1_sel:4;      /* These bits are to control the selection of sdata1 input for DACs. */
        unsigned int dac_sdata2_sel:4;      /* These bits are to control the selection of sdata2 input for DACs.  */
    };

    u_int32_t reg32;
};

void Apb_miscDev::fill_das_dac_input_data_clk_sel_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const das_dac_input_data_clk_sel_2_u old_value_t = { .reg32 = value };
    const das_dac_input_data_clk_sel_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_clk_sel:4",
              "These bits are to control the selection of bit clock and fsync for DACs.",
              4, old_value_t.dac_clk_sel, new_value_t.dac_clk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_23:20", "", 20, old_value_t.undefined_bits_4_23, new_value_t.undefined_bits_4_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: dac_sdata1_sel:4",
              "These bits are to control the selection of sdata1 input for DACs.",
              4, old_value_t.dac_sdata1_sel, new_value_t.dac_sdata1_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dac_sdata2_sel:4",
              "These bits are to control the selection of sdata2 input for DACs.",
              4, old_value_t.dac_sdata2_sel, new_value_t.dac_sdata2_sel };
    m_bit_details_model.bits.append(entry);
}

bool Apb_miscDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case PP_STRAPPING_OPT_A_OFFSET:
    case PP_TRISTATE_REG_A_OFFSET:
    case PP_TRISTATE_REG_B_OFFSET:
    case PP_TRISTATE_REG_C_OFFSET:
    case PP_TRISTATE_REG_D_OFFSET:
    case PP_CONFIG_CTL_OFFSET:
    case PP_MISC_USB_OTG_OFFSET:
    case PP_USB_PHY_PARAM_OFFSET:
    case PP_USB_PHY_VBUS_SENSORS_OFFSET:
    case PP_USB_PHY_VBUS_WAKEUP_ID_OFFSET:
    case PP_USB_PHY_ALT_VBUS_STS_OFFSET:
    case PP_PIN_MUX_CTL_A_OFFSET:
    case PP_PIN_MUX_CTL_B_OFFSET:
    case PP_PIN_MUX_CTL_C_OFFSET:
    case PP_PIN_MUX_CTL_D_OFFSET:
    case PP_PIN_MUX_CTL_E_OFFSET:
    case PP_PIN_MUX_CTL_F_OFFSET:
    case PP_PIN_MUX_CTL_G_OFFSET:
    case PP_PIN_MUX_CTL_H_OFFSET:
    case PP_PULLUPDOWN_REG_A_OFFSET:
    case PP_PULLUPDOWN_REG_B_OFFSET:
    case PP_PULLUPDOWN_REG_C_OFFSET:
    case PP_PULLUPDOWN_REG_D_OFFSET:
    case PP_PULLUPDOWN_REG_E_OFFSET:
    case PP_MISC_USB_CLK_RST_CTL_OFFSET:
    case GP_MODEREG_OFFSET:
    case GP_HIDREV_OFFSET:
    case GP_EMU_REVID_OFFSET:
    case GP_TRANSACTOR_SCRATCH_OFFSET:
    case GP_AOCFG1PADCTRL_OFFSET:
    case GP_AOCFG2PADCTRL_OFFSET:
    case GP_ATCFG1PADCTRL_OFFSET:
    case GP_ATCFG2PADCTRL_OFFSET:
    case GP_CDEV1CFGPADCTRL_OFFSET:
    case GP_CDEV2CFGPADCTRL_OFFSET:
    case GP_CSUSCFGPADCTRL_OFFSET:
    case GP_DAP1CFGPADCTRL_OFFSET:
    case GP_DAP2CFGPADCTRL_OFFSET:
    case GP_DAP3CFGPADCTRL_OFFSET:
    case GP_DAP4CFGPADCTRL_OFFSET:
    case GP_DBGCFGPADCTRL_OFFSET:
    case GP_LCDCFG1PADCTRL_OFFSET:
    case GP_LCDCFG2PADCTRL_OFFSET:
    case GP_SDIO2CFGPADCTRL_OFFSET:
    case GP_SDIO3CFGPADCTRL_OFFSET:
    case GP_SPICFGPADCTRL_OFFSET:
    case GP_UAACFGPADCTRL_OFFSET:
    case GP_UABCFGPADCTRL_OFFSET:
    case GP_UART2CFGPADCTRL_OFFSET:
    case GP_UART3CFGPADCTRL_OFFSET:
    case GP_VICFG1PADCTRL_OFFSET:
    case GP_VICFG2PADCTRL_OFFSET:
    case GP_XM2CFGAPADCTRL_OFFSET:
    case GP_XM2CFGCPADCTRL_OFFSET:
    case GP_XM2CFGDPADCTRL_OFFSET:
    case GP_XM2CLKCFGPADCTRL_OFFSET:
    case GP_XM2COMPPADCTRL_OFFSET:
    case GP_XM2VTTGENPADCTRL_OFFSET:
    case GP_PADCTL_DFT_OFFSET:
    case GP_SDIO1CFGPADCTRL_OFFSET:
    case GP_XM2CFGCPADCTRL2_OFFSET:
    case GP_XM2CFGDPADCTRL2_OFFSET:
    case GP_CRTCFGPADCTRL_OFFSET:
    case GP_DDCCFGPADCTRL_OFFSET:
    case GP_GMACFGPADCTRL_OFFSET:
    case GP_GMBCFGPADCTRL_OFFSET:
    case GP_GMCCFGPADCTRL_OFFSET:
    case GP_GMDCFGPADCTRL_OFFSET:
    case GP_GMECFGPADCTRL_OFFSET:
    case GP_OWRCFGPADCTRL_OFFSET:
    case GP_UADCFGPADCTRL_OFFSET:
    case DAS_DAP_CTRL_SEL_OFFSET:
    case DAS_DAC_INPUT_DATA_CLK_SEL_OFFSET:
    case PP_MISC_SAVE_THE_DAY_OFFSET:
    case ASYNC_COREPWRCONFIG_OFFSET:
    case ASYNC_EMCPADEN_OFFSET:
    case ASYNC_VCLKCTRL_OFFSET:
    case ASYNC_TVDACVHSYNCCTRL_OFFSET:
    case ASYNC_TVDACCNTL_OFFSET:
    case ASYNC_TVDACSTATUS_OFFSET:
    case ASYNC_TVDACDINCONFIG_OFFSET:
    case ASYNC_INT_STATUS_OFFSET:
    case ASYNC_INT_MASK_OFFSET:
    case ASYNC_INT_POLARITY_OFFSET:
    case ASYNC_INT_TYPE_SELECT_OFFSET:
    case DAS_DAP_CTRL_SEL_1_OFFSET:
    case DAS_DAP_CTRL_SEL_2_OFFSET:
    case DAS_DAP_CTRL_SEL_3_OFFSET:
    case DAS_DAP_CTRL_SEL_4_OFFSET:
    case DAS_DAC_INPUT_DATA_CLK_SEL_1_OFFSET:
    case DAS_DAC_INPUT_DATA_CLK_SEL_2_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Apb_miscDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case PP_STRAPPING_OPT_A_OFFSET:
        if ((value ^ new_value) & PP_STRAPPING_OPT_A_UNDEFMASK)
            return true;
        break;
    case PP_TRISTATE_REG_A_OFFSET:
        if ((value ^ new_value) & PP_TRISTATE_REG_A_UNDEFMASK)
            return true;
        break;
    case PP_TRISTATE_REG_B_OFFSET:
        if ((value ^ new_value) & PP_TRISTATE_REG_B_UNDEFMASK)
            return true;
        break;
    case PP_TRISTATE_REG_C_OFFSET:
        if ((value ^ new_value) & PP_TRISTATE_REG_C_UNDEFMASK)
            return true;
        break;
    case PP_TRISTATE_REG_D_OFFSET:
        if ((value ^ new_value) & PP_TRISTATE_REG_D_UNDEFMASK)
            return true;
        break;
    case PP_CONFIG_CTL_OFFSET:
        if ((value ^ new_value) & PP_CONFIG_CTL_UNDEFMASK)
            return true;
        break;
    case PP_MISC_USB_OTG_OFFSET:
        if ((value ^ new_value) & PP_MISC_USB_OTG_UNDEFMASK)
            return true;
        break;
    case PP_USB_PHY_PARAM_OFFSET:
        if ((value ^ new_value) & PP_USB_PHY_PARAM_UNDEFMASK)
            return true;
        break;
    case PP_USB_PHY_VBUS_SENSORS_OFFSET:
        if ((value ^ new_value) & PP_USB_PHY_VBUS_SENSORS_UNDEFMASK)
            return true;
        break;
    case PP_USB_PHY_VBUS_WAKEUP_ID_OFFSET:
        if ((value ^ new_value) & PP_USB_PHY_VBUS_WAKEUP_ID_UNDEFMASK)
            return true;
        break;
    case PP_USB_PHY_ALT_VBUS_STS_OFFSET:
        if ((value ^ new_value) & PP_USB_PHY_ALT_VBUS_STS_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_A_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_A_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_B_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_B_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_C_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_C_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_D_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_D_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_E_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_E_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_F_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_F_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_G_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_G_UNDEFMASK)
            return true;
        break;
    case PP_PIN_MUX_CTL_H_OFFSET:
        if ((value ^ new_value) & PP_PIN_MUX_CTL_H_UNDEFMASK)
            return true;
        break;
    case PP_PULLUPDOWN_REG_A_OFFSET:
        if ((value ^ new_value) & PP_PULLUPDOWN_REG_A_UNDEFMASK)
            return true;
        break;
    case PP_PULLUPDOWN_REG_B_OFFSET:
        if ((value ^ new_value) & PP_PULLUPDOWN_REG_B_UNDEFMASK)
            return true;
        break;
    case PP_PULLUPDOWN_REG_C_OFFSET:
        if ((value ^ new_value) & PP_PULLUPDOWN_REG_C_UNDEFMASK)
            return true;
        break;
    case PP_PULLUPDOWN_REG_D_OFFSET:
        if ((value ^ new_value) & PP_PULLUPDOWN_REG_D_UNDEFMASK)
            return true;
        break;
    case PP_PULLUPDOWN_REG_E_OFFSET:
        if ((value ^ new_value) & PP_PULLUPDOWN_REG_E_UNDEFMASK)
            return true;
        break;
    case PP_MISC_USB_CLK_RST_CTL_OFFSET:
        if ((value ^ new_value) & PP_MISC_USB_CLK_RST_CTL_UNDEFMASK)
            return true;
        break;
    case GP_MODEREG_OFFSET:
        if ((value ^ new_value) & GP_MODEREG_UNDEFMASK)
            return true;
        break;
    case GP_HIDREV_OFFSET:
        if ((value ^ new_value) & GP_HIDREV_UNDEFMASK)
            return true;
        break;
    case GP_EMU_REVID_OFFSET:
        if ((value ^ new_value) & GP_EMU_REVID_UNDEFMASK)
            return true;
        break;
    case GP_TRANSACTOR_SCRATCH_OFFSET:
        if ((value ^ new_value) & GP_TRANSACTOR_SCRATCH_UNDEFMASK)
            return true;
        break;
    case GP_AOCFG1PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_AOCFG1PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_AOCFG2PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_AOCFG2PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_ATCFG1PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_ATCFG1PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_ATCFG2PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_ATCFG2PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_CDEV1CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_CDEV1CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_CDEV2CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_CDEV2CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_CSUSCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_CSUSCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_DAP1CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_DAP1CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_DAP2CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_DAP2CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_DAP3CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_DAP3CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_DAP4CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_DAP4CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_DBGCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_DBGCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_LCDCFG1PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_LCDCFG1PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_LCDCFG2PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_LCDCFG2PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_SDIO2CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_SDIO2CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_SDIO3CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_SDIO3CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_SPICFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_SPICFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_UAACFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_UAACFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_UABCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_UABCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_UART2CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_UART2CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_UART3CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_UART3CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_VICFG1PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_VICFG1PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_VICFG2PADCTRL_OFFSET:
        if ((value ^ new_value) & GP_VICFG2PADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2CFGAPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_XM2CFGAPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2CFGCPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_XM2CFGCPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2CFGDPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_XM2CFGDPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2CLKCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_XM2CLKCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2COMPPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_XM2COMPPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2VTTGENPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_XM2VTTGENPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_PADCTL_DFT_OFFSET:
        if ((value ^ new_value) & GP_PADCTL_DFT_UNDEFMASK)
            return true;
        break;
    case GP_SDIO1CFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_SDIO1CFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_XM2CFGCPADCTRL2_OFFSET:
        if ((value ^ new_value) & GP_XM2CFGCPADCTRL2_UNDEFMASK)
            return true;
        break;
    case GP_XM2CFGDPADCTRL2_OFFSET:
        if ((value ^ new_value) & GP_XM2CFGDPADCTRL2_UNDEFMASK)
            return true;
        break;
    case GP_CRTCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_CRTCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_DDCCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_DDCCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_GMACFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_GMACFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_GMBCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_GMBCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_GMCCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_GMCCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_GMDCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_GMDCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_GMECFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_GMECFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_OWRCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_OWRCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case GP_UADCFGPADCTRL_OFFSET:
        if ((value ^ new_value) & GP_UADCFGPADCTRL_UNDEFMASK)
            return true;
        break;
    case DAS_DAP_CTRL_SEL_OFFSET:
        if ((value ^ new_value) & DAS_DAP_CTRL_SEL_UNDEFMASK)
            return true;
        break;
    case DAS_DAC_INPUT_DATA_CLK_SEL_OFFSET:
        if ((value ^ new_value) & DAS_DAC_INPUT_DATA_CLK_SEL_UNDEFMASK)
            return true;
        break;
    case PP_MISC_SAVE_THE_DAY_OFFSET:
        if ((value ^ new_value) & PP_MISC_SAVE_THE_DAY_UNDEFMASK)
            return true;
        break;
    case ASYNC_COREPWRCONFIG_OFFSET:
        if ((value ^ new_value) & ASYNC_COREPWRCONFIG_UNDEFMASK)
            return true;
        break;
    case ASYNC_EMCPADEN_OFFSET:
        if ((value ^ new_value) & ASYNC_EMCPADEN_UNDEFMASK)
            return true;
        break;
    case ASYNC_VCLKCTRL_OFFSET:
        if ((value ^ new_value) & ASYNC_VCLKCTRL_UNDEFMASK)
            return true;
        break;
    case ASYNC_TVDACVHSYNCCTRL_OFFSET:
        if ((value ^ new_value) & ASYNC_TVDACVHSYNCCTRL_UNDEFMASK)
            return true;
        break;
    case ASYNC_TVDACCNTL_OFFSET:
        if ((value ^ new_value) & ASYNC_TVDACCNTL_UNDEFMASK)
            return true;
        break;
    case ASYNC_TVDACSTATUS_OFFSET:
        if ((value ^ new_value) & ASYNC_TVDACSTATUS_UNDEFMASK)
            return true;
        break;
    case ASYNC_TVDACDINCONFIG_OFFSET:
        if ((value ^ new_value) & ASYNC_TVDACDINCONFIG_UNDEFMASK)
            return true;
        break;
    case ASYNC_INT_STATUS_OFFSET:
        if ((value ^ new_value) & ASYNC_INT_STATUS_UNDEFMASK)
            return true;
        break;
    case ASYNC_INT_MASK_OFFSET:
        if ((value ^ new_value) & ASYNC_INT_MASK_UNDEFMASK)
            return true;
        break;
    case ASYNC_INT_POLARITY_OFFSET:
        if ((value ^ new_value) & ASYNC_INT_POLARITY_UNDEFMASK)
            return true;
        break;
    case ASYNC_INT_TYPE_SELECT_OFFSET:
        if ((value ^ new_value) & ASYNC_INT_TYPE_SELECT_UNDEFMASK)
            return true;
        break;
    case DAS_DAP_CTRL_SEL_1_OFFSET:
        if ((value ^ new_value) & DAS_DAP_CTRL_SEL_1_UNDEFMASK)
            return true;
        break;
    case DAS_DAP_CTRL_SEL_2_OFFSET:
        if ((value ^ new_value) & DAS_DAP_CTRL_SEL_2_UNDEFMASK)
            return true;
        break;
    case DAS_DAP_CTRL_SEL_3_OFFSET:
        if ((value ^ new_value) & DAS_DAP_CTRL_SEL_3_UNDEFMASK)
            return true;
        break;
    case DAS_DAP_CTRL_SEL_4_OFFSET:
        if ((value ^ new_value) & DAS_DAP_CTRL_SEL_4_UNDEFMASK)
            return true;
        break;
    case DAS_DAC_INPUT_DATA_CLK_SEL_1_OFFSET:
        if ((value ^ new_value) & DAS_DAC_INPUT_DATA_CLK_SEL_1_UNDEFMASK)
            return true;
        break;
    case DAS_DAC_INPUT_DATA_CLK_SEL_2_OFFSET:
        if ((value ^ new_value) & DAS_DAC_INPUT_DATA_CLK_SEL_2_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Apb_miscDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case PP_STRAPPING_OPT_A_OFFSET:
        return QString("PP_STRAPPING_OPT_A");
    case PP_TRISTATE_REG_A_OFFSET:
        return QString("PP_TRISTATE_REG_A");
    case PP_TRISTATE_REG_B_OFFSET:
        return QString("PP_TRISTATE_REG_B");
    case PP_TRISTATE_REG_C_OFFSET:
        return QString("PP_TRISTATE_REG_C");
    case PP_TRISTATE_REG_D_OFFSET:
        return QString("PP_TRISTATE_REG_D");
    case PP_CONFIG_CTL_OFFSET:
        return QString("PP_CONFIG_CTL");
    case PP_MISC_USB_OTG_OFFSET:
        return QString("PP_MISC_USB_OTG");
    case PP_USB_PHY_PARAM_OFFSET:
        return QString("PP_USB_PHY_PARAM");
    case PP_USB_PHY_VBUS_SENSORS_OFFSET:
        return QString("PP_USB_PHY_VBUS_SENSORS");
    case PP_USB_PHY_VBUS_WAKEUP_ID_OFFSET:
        return QString("PP_USB_PHY_VBUS_WAKEUP_ID");
    case PP_USB_PHY_ALT_VBUS_STS_OFFSET:
        return QString("PP_USB_PHY_ALT_VBUS_STS");
    case PP_PIN_MUX_CTL_A_OFFSET:
        return QString("PP_PIN_MUX_CTL_A");
    case PP_PIN_MUX_CTL_B_OFFSET:
        return QString("PP_PIN_MUX_CTL_B");
    case PP_PIN_MUX_CTL_C_OFFSET:
        return QString("PP_PIN_MUX_CTL_C");
    case PP_PIN_MUX_CTL_D_OFFSET:
        return QString("PP_PIN_MUX_CTL_D");
    case PP_PIN_MUX_CTL_E_OFFSET:
        return QString("PP_PIN_MUX_CTL_E");
    case PP_PIN_MUX_CTL_F_OFFSET:
        return QString("PP_PIN_MUX_CTL_F");
    case PP_PIN_MUX_CTL_G_OFFSET:
        return QString("PP_PIN_MUX_CTL_G");
    case PP_PIN_MUX_CTL_H_OFFSET:
        return QString("PP_PIN_MUX_CTL_H");
    case PP_PULLUPDOWN_REG_A_OFFSET:
        return QString("PP_PULLUPDOWN_REG_A");
    case PP_PULLUPDOWN_REG_B_OFFSET:
        return QString("PP_PULLUPDOWN_REG_B");
    case PP_PULLUPDOWN_REG_C_OFFSET:
        return QString("PP_PULLUPDOWN_REG_C");
    case PP_PULLUPDOWN_REG_D_OFFSET:
        return QString("PP_PULLUPDOWN_REG_D");
    case PP_PULLUPDOWN_REG_E_OFFSET:
        return QString("PP_PULLUPDOWN_REG_E");
    case PP_MISC_USB_CLK_RST_CTL_OFFSET:
        return QString("PP_MISC_USB_CLK_RST_CTL");
    case GP_MODEREG_OFFSET:
        return QString("GP_MODEREG");
    case GP_HIDREV_OFFSET:
        return QString("GP_HIDREV");
    case GP_EMU_REVID_OFFSET:
        return QString("GP_EMU_REVID");
    case GP_TRANSACTOR_SCRATCH_OFFSET:
        return QString("GP_TRANSACTOR_SCRATCH");
    case GP_AOCFG1PADCTRL_OFFSET:
        return QString("GP_AOCFG1PADCTRL");
    case GP_AOCFG2PADCTRL_OFFSET:
        return QString("GP_AOCFG2PADCTRL");
    case GP_ATCFG1PADCTRL_OFFSET:
        return QString("GP_ATCFG1PADCTRL");
    case GP_ATCFG2PADCTRL_OFFSET:
        return QString("GP_ATCFG2PADCTRL");
    case GP_CDEV1CFGPADCTRL_OFFSET:
        return QString("GP_CDEV1CFGPADCTRL");
    case GP_CDEV2CFGPADCTRL_OFFSET:
        return QString("GP_CDEV2CFGPADCTRL");
    case GP_CSUSCFGPADCTRL_OFFSET:
        return QString("GP_CSUSCFGPADCTRL");
    case GP_DAP1CFGPADCTRL_OFFSET:
        return QString("GP_DAP1CFGPADCTRL");
    case GP_DAP2CFGPADCTRL_OFFSET:
        return QString("GP_DAP2CFGPADCTRL");
    case GP_DAP3CFGPADCTRL_OFFSET:
        return QString("GP_DAP3CFGPADCTRL");
    case GP_DAP4CFGPADCTRL_OFFSET:
        return QString("GP_DAP4CFGPADCTRL");
    case GP_DBGCFGPADCTRL_OFFSET:
        return QString("GP_DBGCFGPADCTRL");
    case GP_LCDCFG1PADCTRL_OFFSET:
        return QString("GP_LCDCFG1PADCTRL");
    case GP_LCDCFG2PADCTRL_OFFSET:
        return QString("GP_LCDCFG2PADCTRL");
    case GP_SDIO2CFGPADCTRL_OFFSET:
        return QString("GP_SDIO2CFGPADCTRL");
    case GP_SDIO3CFGPADCTRL_OFFSET:
        return QString("GP_SDIO3CFGPADCTRL");
    case GP_SPICFGPADCTRL_OFFSET:
        return QString("GP_SPICFGPADCTRL");
    case GP_UAACFGPADCTRL_OFFSET:
        return QString("GP_UAACFGPADCTRL");
    case GP_UABCFGPADCTRL_OFFSET:
        return QString("GP_UABCFGPADCTRL");
    case GP_UART2CFGPADCTRL_OFFSET:
        return QString("GP_UART2CFGPADCTRL");
    case GP_UART3CFGPADCTRL_OFFSET:
        return QString("GP_UART3CFGPADCTRL");
    case GP_VICFG1PADCTRL_OFFSET:
        return QString("GP_VICFG1PADCTRL");
    case GP_VICFG2PADCTRL_OFFSET:
        return QString("GP_VICFG2PADCTRL");
    case GP_XM2CFGAPADCTRL_OFFSET:
        return QString("GP_XM2CFGAPADCTRL");
    case GP_XM2CFGCPADCTRL_OFFSET:
        return QString("GP_XM2CFGCPADCTRL");
    case GP_XM2CFGDPADCTRL_OFFSET:
        return QString("GP_XM2CFGDPADCTRL");
    case GP_XM2CLKCFGPADCTRL_OFFSET:
        return QString("GP_XM2CLKCFGPADCTRL");
    case GP_XM2COMPPADCTRL_OFFSET:
        return QString("GP_XM2COMPPADCTRL");
    case GP_XM2VTTGENPADCTRL_OFFSET:
        return QString("GP_XM2VTTGENPADCTRL");
    case GP_PADCTL_DFT_OFFSET:
        return QString("GP_PADCTL_DFT");
    case GP_SDIO1CFGPADCTRL_OFFSET:
        return QString("GP_SDIO1CFGPADCTRL");
    case GP_XM2CFGCPADCTRL2_OFFSET:
        return QString("GP_XM2CFGCPADCTRL2");
    case GP_XM2CFGDPADCTRL2_OFFSET:
        return QString("GP_XM2CFGDPADCTRL2");
    case GP_CRTCFGPADCTRL_OFFSET:
        return QString("GP_CRTCFGPADCTRL");
    case GP_DDCCFGPADCTRL_OFFSET:
        return QString("GP_DDCCFGPADCTRL");
    case GP_GMACFGPADCTRL_OFFSET:
        return QString("GP_GMACFGPADCTRL");
    case GP_GMBCFGPADCTRL_OFFSET:
        return QString("GP_GMBCFGPADCTRL");
    case GP_GMCCFGPADCTRL_OFFSET:
        return QString("GP_GMCCFGPADCTRL");
    case GP_GMDCFGPADCTRL_OFFSET:
        return QString("GP_GMDCFGPADCTRL");
    case GP_GMECFGPADCTRL_OFFSET:
        return QString("GP_GMECFGPADCTRL");
    case GP_OWRCFGPADCTRL_OFFSET:
        return QString("GP_OWRCFGPADCTRL");
    case GP_UADCFGPADCTRL_OFFSET:
        return QString("GP_UADCFGPADCTRL");
    case DAS_DAP_CTRL_SEL_OFFSET:
        return QString("DAS_DAP_CTRL_SEL");
    case DAS_DAC_INPUT_DATA_CLK_SEL_OFFSET:
        return QString("DAS_DAC_INPUT_DATA_CLK_SEL");
    case PP_MISC_SAVE_THE_DAY_OFFSET:
        return QString("PP_MISC_SAVE_THE_DAY");
    case ASYNC_COREPWRCONFIG_OFFSET:
        return QString("ASYNC_COREPWRCONFIG");
    case ASYNC_EMCPADEN_OFFSET:
        return QString("ASYNC_EMCPADEN");
    case ASYNC_VCLKCTRL_OFFSET:
        return QString("ASYNC_VCLKCTRL");
    case ASYNC_TVDACVHSYNCCTRL_OFFSET:
        return QString("ASYNC_TVDACVHSYNCCTRL");
    case ASYNC_TVDACCNTL_OFFSET:
        return QString("ASYNC_TVDACCNTL");
    case ASYNC_TVDACSTATUS_OFFSET:
        return QString("ASYNC_TVDACSTATUS");
    case ASYNC_TVDACDINCONFIG_OFFSET:
        return QString("ASYNC_TVDACDINCONFIG");
    case ASYNC_INT_STATUS_OFFSET:
        return QString("ASYNC_INT_STATUS");
    case ASYNC_INT_MASK_OFFSET:
        return QString("ASYNC_INT_MASK");
    case ASYNC_INT_POLARITY_OFFSET:
        return QString("ASYNC_INT_POLARITY");
    case ASYNC_INT_TYPE_SELECT_OFFSET:
        return QString("ASYNC_INT_TYPE_SELECT");
    case DAS_DAP_CTRL_SEL_1_OFFSET:
        return QString("DAS_DAP_CTRL_SEL_1");
    case DAS_DAP_CTRL_SEL_2_OFFSET:
        return QString("DAS_DAP_CTRL_SEL_2");
    case DAS_DAP_CTRL_SEL_3_OFFSET:
        return QString("DAS_DAP_CTRL_SEL_3");
    case DAS_DAP_CTRL_SEL_4_OFFSET:
        return QString("DAS_DAP_CTRL_SEL_4");
    case DAS_DAC_INPUT_DATA_CLK_SEL_1_OFFSET:
        return QString("DAS_DAC_INPUT_DATA_CLK_SEL_1");
    case DAS_DAC_INPUT_DATA_CLK_SEL_2_OFFSET:
        return QString("DAS_DAC_INPUT_DATA_CLK_SEL_2");

    default:
        break;
    }

    qDebug() << QString().sprintf("APB_MISC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Apb_miscDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case PP_STRAPPING_OPT_A_OFFSET:
        fill_pp_strapping_opt_a_details(value, new_value);
        break;
    case PP_TRISTATE_REG_A_OFFSET:
        fill_pp_tristate_reg_a_details(value, new_value);
        break;
    case PP_TRISTATE_REG_B_OFFSET:
        fill_pp_tristate_reg_b_details(value, new_value);
        break;
    case PP_TRISTATE_REG_C_OFFSET:
        fill_pp_tristate_reg_c_details(value, new_value);
        break;
    case PP_TRISTATE_REG_D_OFFSET:
        fill_pp_tristate_reg_d_details(value, new_value);
        break;
    case PP_CONFIG_CTL_OFFSET:
        fill_pp_config_ctl_details(value, new_value);
        break;
    case PP_MISC_USB_OTG_OFFSET:
        fill_pp_misc_usb_otg_details(value, new_value);
        break;
    case PP_USB_PHY_PARAM_OFFSET:
        fill_pp_usb_phy_param_details(value, new_value);
        break;
    case PP_USB_PHY_VBUS_SENSORS_OFFSET:
        fill_pp_usb_phy_vbus_sensors_details(value, new_value);
        break;
    case PP_USB_PHY_VBUS_WAKEUP_ID_OFFSET:
        fill_pp_usb_phy_vbus_wakeup_id_details(value, new_value);
        break;
    case PP_USB_PHY_ALT_VBUS_STS_OFFSET:
        fill_pp_usb_phy_alt_vbus_sts_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_A_OFFSET:
        fill_pp_pin_mux_ctl_a_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_B_OFFSET:
        fill_pp_pin_mux_ctl_b_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_C_OFFSET:
        fill_pp_pin_mux_ctl_c_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_D_OFFSET:
        fill_pp_pin_mux_ctl_d_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_E_OFFSET:
        fill_pp_pin_mux_ctl_e_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_F_OFFSET:
        fill_pp_pin_mux_ctl_f_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_G_OFFSET:
        fill_pp_pin_mux_ctl_g_details(value, new_value);
        break;
    case PP_PIN_MUX_CTL_H_OFFSET:
        fill_pp_pin_mux_ctl_h_details(value, new_value);
        break;
    case PP_PULLUPDOWN_REG_A_OFFSET:
        fill_pp_pullupdown_reg_a_details(value, new_value);
        break;
    case PP_PULLUPDOWN_REG_B_OFFSET:
        fill_pp_pullupdown_reg_b_details(value, new_value);
        break;
    case PP_PULLUPDOWN_REG_C_OFFSET:
        fill_pp_pullupdown_reg_c_details(value, new_value);
        break;
    case PP_PULLUPDOWN_REG_D_OFFSET:
        fill_pp_pullupdown_reg_d_details(value, new_value);
        break;
    case PP_PULLUPDOWN_REG_E_OFFSET:
        fill_pp_pullupdown_reg_e_details(value, new_value);
        break;
    case PP_MISC_USB_CLK_RST_CTL_OFFSET:
        fill_pp_misc_usb_clk_rst_ctl_details(value, new_value);
        break;
    case GP_MODEREG_OFFSET:
        fill_gp_modereg_details(value, new_value);
        break;
    case GP_HIDREV_OFFSET:
        fill_gp_hidrev_details(value, new_value);
        break;
    case GP_EMU_REVID_OFFSET:
        fill_gp_emu_revid_details(value, new_value);
        break;
    case GP_TRANSACTOR_SCRATCH_OFFSET:
        fill_gp_transactor_scratch_details(value, new_value);
        break;
    case GP_AOCFG1PADCTRL_OFFSET:
        fill_gp_aocfg1padctrl_details(value, new_value);
        break;
    case GP_AOCFG2PADCTRL_OFFSET:
        fill_gp_aocfg2padctrl_details(value, new_value);
        break;
    case GP_ATCFG1PADCTRL_OFFSET:
        fill_gp_atcfg1padctrl_details(value, new_value);
        break;
    case GP_ATCFG2PADCTRL_OFFSET:
        fill_gp_atcfg2padctrl_details(value, new_value);
        break;
    case GP_CDEV1CFGPADCTRL_OFFSET:
        fill_gp_cdev1cfgpadctrl_details(value, new_value);
        break;
    case GP_CDEV2CFGPADCTRL_OFFSET:
        fill_gp_cdev2cfgpadctrl_details(value, new_value);
        break;
    case GP_CSUSCFGPADCTRL_OFFSET:
        fill_gp_csuscfgpadctrl_details(value, new_value);
        break;
    case GP_DAP1CFGPADCTRL_OFFSET:
        fill_gp_dap1cfgpadctrl_details(value, new_value);
        break;
    case GP_DAP2CFGPADCTRL_OFFSET:
        fill_gp_dap2cfgpadctrl_details(value, new_value);
        break;
    case GP_DAP3CFGPADCTRL_OFFSET:
        fill_gp_dap3cfgpadctrl_details(value, new_value);
        break;
    case GP_DAP4CFGPADCTRL_OFFSET:
        fill_gp_dap4cfgpadctrl_details(value, new_value);
        break;
    case GP_DBGCFGPADCTRL_OFFSET:
        fill_gp_dbgcfgpadctrl_details(value, new_value);
        break;
    case GP_LCDCFG1PADCTRL_OFFSET:
        fill_gp_lcdcfg1padctrl_details(value, new_value);
        break;
    case GP_LCDCFG2PADCTRL_OFFSET:
        fill_gp_lcdcfg2padctrl_details(value, new_value);
        break;
    case GP_SDIO2CFGPADCTRL_OFFSET:
        fill_gp_sdio2cfgpadctrl_details(value, new_value);
        break;
    case GP_SDIO3CFGPADCTRL_OFFSET:
        fill_gp_sdio3cfgpadctrl_details(value, new_value);
        break;
    case GP_SPICFGPADCTRL_OFFSET:
        fill_gp_spicfgpadctrl_details(value, new_value);
        break;
    case GP_UAACFGPADCTRL_OFFSET:
        fill_gp_uaacfgpadctrl_details(value, new_value);
        break;
    case GP_UABCFGPADCTRL_OFFSET:
        fill_gp_uabcfgpadctrl_details(value, new_value);
        break;
    case GP_UART2CFGPADCTRL_OFFSET:
        fill_gp_uart2cfgpadctrl_details(value, new_value);
        break;
    case GP_UART3CFGPADCTRL_OFFSET:
        fill_gp_uart3cfgpadctrl_details(value, new_value);
        break;
    case GP_VICFG1PADCTRL_OFFSET:
        fill_gp_vicfg1padctrl_details(value, new_value);
        break;
    case GP_VICFG2PADCTRL_OFFSET:
        fill_gp_vicfg2padctrl_details(value, new_value);
        break;
    case GP_XM2CFGAPADCTRL_OFFSET:
        fill_gp_xm2cfgapadctrl_details(value, new_value);
        break;
    case GP_XM2CFGCPADCTRL_OFFSET:
        fill_gp_xm2cfgcpadctrl_details(value, new_value);
        break;
    case GP_XM2CFGDPADCTRL_OFFSET:
        fill_gp_xm2cfgdpadctrl_details(value, new_value);
        break;
    case GP_XM2CLKCFGPADCTRL_OFFSET:
        fill_gp_xm2clkcfgpadctrl_details(value, new_value);
        break;
    case GP_XM2COMPPADCTRL_OFFSET:
        fill_gp_xm2comppadctrl_details(value, new_value);
        break;
    case GP_XM2VTTGENPADCTRL_OFFSET:
        fill_gp_xm2vttgenpadctrl_details(value, new_value);
        break;
    case GP_PADCTL_DFT_OFFSET:
        fill_gp_padctl_dft_details(value, new_value);
        break;
    case GP_SDIO1CFGPADCTRL_OFFSET:
        fill_gp_sdio1cfgpadctrl_details(value, new_value);
        break;
    case GP_XM2CFGCPADCTRL2_OFFSET:
        fill_gp_xm2cfgcpadctrl2_details(value, new_value);
        break;
    case GP_XM2CFGDPADCTRL2_OFFSET:
        fill_gp_xm2cfgdpadctrl2_details(value, new_value);
        break;
    case GP_CRTCFGPADCTRL_OFFSET:
        fill_gp_crtcfgpadctrl_details(value, new_value);
        break;
    case GP_DDCCFGPADCTRL_OFFSET:
        fill_gp_ddccfgpadctrl_details(value, new_value);
        break;
    case GP_GMACFGPADCTRL_OFFSET:
        fill_gp_gmacfgpadctrl_details(value, new_value);
        break;
    case GP_GMBCFGPADCTRL_OFFSET:
        fill_gp_gmbcfgpadctrl_details(value, new_value);
        break;
    case GP_GMCCFGPADCTRL_OFFSET:
        fill_gp_gmccfgpadctrl_details(value, new_value);
        break;
    case GP_GMDCFGPADCTRL_OFFSET:
        fill_gp_gmdcfgpadctrl_details(value, new_value);
        break;
    case GP_GMECFGPADCTRL_OFFSET:
        fill_gp_gmecfgpadctrl_details(value, new_value);
        break;
    case GP_OWRCFGPADCTRL_OFFSET:
        fill_gp_owrcfgpadctrl_details(value, new_value);
        break;
    case GP_UADCFGPADCTRL_OFFSET:
        fill_gp_uadcfgpadctrl_details(value, new_value);
        break;
    case DAS_DAP_CTRL_SEL_OFFSET:
        fill_das_dap_ctrl_sel_details(value, new_value);
        break;
    case DAS_DAC_INPUT_DATA_CLK_SEL_OFFSET:
        fill_das_dac_input_data_clk_sel_details(value, new_value);
        break;
    case PP_MISC_SAVE_THE_DAY_OFFSET:
        fill_pp_misc_save_the_day_details(value, new_value);
        break;
    case ASYNC_COREPWRCONFIG_OFFSET:
        fill_async_corepwrconfig_details(value, new_value);
        break;
    case ASYNC_EMCPADEN_OFFSET:
        fill_async_emcpaden_details(value, new_value);
        break;
    case ASYNC_VCLKCTRL_OFFSET:
        fill_async_vclkctrl_details(value, new_value);
        break;
    case ASYNC_TVDACVHSYNCCTRL_OFFSET:
        fill_async_tvdacvhsyncctrl_details(value, new_value);
        break;
    case ASYNC_TVDACCNTL_OFFSET:
        fill_async_tvdaccntl_details(value, new_value);
        break;
    case ASYNC_TVDACSTATUS_OFFSET:
        fill_async_tvdacstatus_details(value, new_value);
        break;
    case ASYNC_TVDACDINCONFIG_OFFSET:
        fill_async_tvdacdinconfig_details(value, new_value);
        break;
    case ASYNC_INT_STATUS_OFFSET:
        fill_async_int_status_details(value, new_value);
        break;
    case ASYNC_INT_MASK_OFFSET:
        fill_async_int_mask_details(value, new_value);
        break;
    case ASYNC_INT_POLARITY_OFFSET:
        fill_async_int_polarity_details(value, new_value);
        break;
    case ASYNC_INT_TYPE_SELECT_OFFSET:
        fill_async_int_type_select_details(value, new_value);
        break;
    case DAS_DAP_CTRL_SEL_1_OFFSET:
        fill_das_dap_ctrl_sel_1_details(value, new_value);
        break;
    case DAS_DAP_CTRL_SEL_2_OFFSET:
        fill_das_dap_ctrl_sel_2_details(value, new_value);
        break;
    case DAS_DAP_CTRL_SEL_3_OFFSET:
        fill_das_dap_ctrl_sel_3_details(value, new_value);
        break;
    case DAS_DAP_CTRL_SEL_4_OFFSET:
        fill_das_dap_ctrl_sel_4_details(value, new_value);
        break;
    case DAS_DAC_INPUT_DATA_CLK_SEL_1_OFFSET:
        fill_das_dac_input_data_clk_sel_1_details(value, new_value);
        break;
    case DAS_DAC_INPUT_DATA_CLK_SEL_2_OFFSET:
        fill_das_dac_input_data_clk_sel_2_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
