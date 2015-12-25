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

#include "host1x_syncdev.h"

#include <QDebug>

#define INTSTATUS_OFFSET 0x0
#define INTSTATUS_UNDEFMASK 0x3FFFE080
union host1x_intstatus_u {
    struct {
        unsigned int host_int:1;            /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int mpe_int:1;             /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int vi_int:1;              /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int epp_int:1;             /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int isp_int:1;             /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int gr2d_int:1;            /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int gr3d_int:1;            /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int undefined_bit_7:1;
        unsigned int display_int:1;         /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int displayb_int:1;        /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int hdmi_int:1;            /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int tvo_int:1;             /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int dsi_int:1;             /* 0 = NOT_PENDING 1 = PENDING */
        unsigned int undefined_bits_13_29:17;
        unsigned int syncpt_cpu0_int:1;     /* set if SYNC_SYNCPT_THRESH_CPU0_INT_STATUS has a pending interrupt 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_cpu1_int:1;     /* set if SYNC_SYNCPT_THRESH_CPU1_INT_STATUS has a pending interrupt 0 = NOT_PENDING 1 = PENDING */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_intstatus_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const host1x_intstatus_u old_value_t = { .reg32 = value };
    const host1x_intstatus_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.host_int, new_value_t.host_int };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mpe_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.mpe_int, new_value_t.mpe_int };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vi_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.vi_int, new_value_t.vi_int };
    m_bit_details_model.bits.append(entry);
    entry = { "03: epp_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.epp_int, new_value_t.epp_int };
    m_bit_details_model.bits.append(entry);
    entry = { "04: isp_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.isp_int, new_value_t.isp_int };
    m_bit_details_model.bits.append(entry);
    entry = { "05: gr2d_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.gr2d_int, new_value_t.gr2d_int };
    m_bit_details_model.bits.append(entry);
    entry = { "06: gr3d_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.gr3d_int, new_value_t.gr3d_int };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bit_7:1", "", 1, old_value_t.undefined_bit_7, new_value_t.undefined_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.display_int, new_value_t.display_int };
    m_bit_details_model.bits.append(entry);
    entry = { "09: displayb_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.displayb_int, new_value_t.displayb_int };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hdmi_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.hdmi_int, new_value_t.hdmi_int };
    m_bit_details_model.bits.append(entry);
    entry = { "11: tvo_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.tvo_int, new_value_t.tvo_int };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dsi_int:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.dsi_int, new_value_t.dsi_int };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_29:17", "", 17, old_value_t.undefined_bits_13_29, new_value_t.undefined_bits_13_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_cpu0_int:1",
              "set if SYNC_SYNCPT_THRESH_CPU0_INT_STATUS has a pending interrupt\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_cpu0_int, new_value_t.syncpt_cpu0_int };
    m_bit_details_model.bits.append(entry);
    entry = { "31: syncpt_cpu1_int:1",
              "set if SYNC_SYNCPT_THRESH_CPU1_INT_STATUS has a pending interrupt\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_cpu1_int, new_value_t.syncpt_cpu1_int };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "INTSTATUS - interrupt status contains the interrupt status for all of the client modules. These status bits are only status.  Writing '1' to them will not clear them.  SW must clear the interrupt in the appropriate module, which should be reflected here.";
}

#define INTMASK_OFFSET 0x4
#define INTMASK_UNDEFMASK 0xFFFFFFFC
union host1x_intmask_u {
    struct {
        unsigned int cpu0_int_mask_all:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int cpu1_int_mask_all:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_intmask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const host1x_intmask_u old_value_t = { .reg32 = value };
    const host1x_intmask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu0_int_mask_all:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cpu0_int_mask_all, new_value_t.cpu0_int_mask_all };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cpu1_int_mask_all:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cpu1_int_mask_all, new_value_t.cpu1_int_mask_all };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Contains a master interrupt mask for all interrupt signals.  If the interface's MASK_ALL bit is disabled, no interrupts will be triggered on that interface. This applies to only the non-syncpt interrupts.";
}

#define INTC0MASK_OFFSET 0x8
#define INTC0MASK_UNDEFMASK 0xFFFFE080
union intc0mask_u {
    struct {
        unsigned int host_int_c0mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int mpe_int_c0mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int vi_int_c0mask:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int epp_int_c0mask:1;      /* 0 = DISABLE; 1 = ENABLE */
        unsigned int isp_int_c0mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int gr2d_int_c0mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int gr3d_int_c0mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_7:1;
        unsigned int display_int_c0mask:1;  /* 0 = DISABLE 1 = ENABLE */
        unsigned int displayb_int_c0mask:1; /* 0 = DISABLE 1 = ENABLE */
        unsigned int hdmi_int_c0mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int tvo_int_c0mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int dsi_int_c0mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_intc0mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intc0mask_u old_value_t = { .reg32 = value };
    const intc0mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.host_int_c0mask, new_value_t.host_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mpe_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.mpe_int_c0mask, new_value_t.mpe_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vi_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vi_int_c0mask, new_value_t.vi_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "03: epp_int_c0mask:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.epp_int_c0mask, new_value_t.epp_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "04: isp_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.isp_int_c0mask, new_value_t.isp_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "05: gr2d_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.gr2d_int_c0mask, new_value_t.gr2d_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "06: gr3d_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.gr3d_int_c0mask, new_value_t.gr3d_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bit_7:1", "", 1, old_value_t.undefined_bit_7, new_value_t.undefined_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.display_int_c0mask, new_value_t.display_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "09: displayb_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.displayb_int_c0mask, new_value_t.displayb_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hdmi_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hdmi_int_c0mask, new_value_t.hdmi_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "11: tvo_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.tvo_int_c0mask, new_value_t.tvo_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dsi_int_c0mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dsi_int_c0mask, new_value_t.dsi_int_c0mask };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "INTC0MASK - interrupt mask for CPU0 Contains the interrupt mask bits for all of the client modules. If the INT_MASK is ENABLED for a particular module, the modules INT bit from INTSTATUS contributes to CPU0's interrupt signal.";
}

#define INTC1MASK_OFFSET 0xC
#define INTC1MASK_UNDEFMASK 0xFFFFE080
union intc1mask_u {
    struct {
        unsigned int host_int_c1mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int mpe_int_c1mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int vi_int_c1mask:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int epp_int_c1mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int isp_int_c1mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int gr2d_int_c1mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int gr3d_int_c1mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_7:1;
        unsigned int display_int_c1mask:1;  /* 0 = DISABLE 1 = ENABLE */
        unsigned int displayb_int_c1mask:1; /* 0 = DISABLE 1 = ENABLE */
        unsigned int hdmi_int_c1mask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int tvo_int_c1mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int dsi_int_c1mask:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_intc1mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intc1mask_u old_value_t = { .reg32 = value };
    const intc1mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.host_int_c1mask, new_value_t.host_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mpe_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.mpe_int_c1mask, new_value_t.mpe_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vi_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.vi_int_c1mask, new_value_t.vi_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "03: epp_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.epp_int_c1mask, new_value_t.epp_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "04: isp_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.isp_int_c1mask, new_value_t.isp_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "05: gr2d_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.gr2d_int_c1mask, new_value_t.gr2d_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "06: gr3d_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.gr3d_int_c1mask, new_value_t.gr3d_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bit_7:1", "", 1, old_value_t.undefined_bit_7, new_value_t.undefined_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.display_int_c1mask, new_value_t.display_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "09: displayb_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.displayb_int_c1mask, new_value_t.displayb_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hdmi_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hdmi_int_c1mask, new_value_t.hdmi_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "11: tvo_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.tvo_int_c1mask, new_value_t.tvo_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dsi_int_c1mask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dsi_int_c1mask, new_value_t.dsi_int_c1mask };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "INTC1MASK - interrupt mask for CPU1 Contains the interrupt mask bits for all of the client modules. If the INT_MASK is ENABLED for a particular module, the modules INT bit from INTSTATUS contributes to CPU1's interrupt signal.";
}

#define HINTSTATUS_OFFSET 0x20
#define HINTSTATUS_UNDEFMASK 0x1FF0FF00
union hintstatus_u {
    struct {
        unsigned int wait_int0:1;           /* WAIT has completed on channel 0 0 = NOT_PENDING 1 = PENDING */
        unsigned int wait_int1:1;           /* WAIT has completed on channel 1 0 = NOT_PENDING; 1 = PENDING */
        unsigned int wait_int2:1;           /* WAIT has completed on channel 2 0 = NOT_PENDING 1 = PENDING */
        unsigned int wait_int3:1;           /* WAIT has completed on channel 3 0 = NOT_PENDING 1 = PENDING */
        unsigned int wait_int4:1;           /* WAIT has completed on channel 4 0 = NOT_PENDING 1 = PENDING */
        unsigned int wait_int5:1;           /* WAIT has completed on channel 5 0 = NOT_PENDING 1 = PENDING */
        unsigned int wait_int6:1;           /* WAIT has completed on channel 6 0 = NOT_PENDING 1 = PENDING */
        unsigned int wait_int7:1;           /* WAIT has completed on channel 7 0 = NOT_PENDING 1 = PENDING */
        unsigned int undefined_bits_8_15:8;
        unsigned int rdma_inval_clreq_int:1;/* Invalid client request to read DMA 0 = NOT_PENDING 1 = PENDING */
        unsigned int rdma_buf_oflow_int0:1; /* Buffer overflow in read DMA port0 0 = NOT_PENDING 1 = PENDING */
        unsigned int rdma_buf_thold_int0:1; /* Buffer threshold reached in read DMA port0 0 = NOT_PENDING 1 = PENDING */
        unsigned int rdma_databuf_thold_int0:1;/* Read DMA data FIFO in port0 reached high level watermark 0 = NOT_PENDING 1 = PENDING */
        unsigned int undefined_bits_20_28:9;
        unsigned int csw_host1xw2mc_int:1;  /* Host write client FIFO has filled up */
        unsigned int timer_intp:1;          /* Timer Interrupt from the Protected Channel 0 = NOT_PENDING 1 = PENDING */
        unsigned int hintstatus_ext_int:1;  /* Additional interrupts pending in the HINSTATUS_EXT register 0 = NOT_PENDING 1 = PENDING */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hintstatus_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hintstatus_u old_value_t = { .reg32 = value };
    const hintstatus_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wait_int0:1",
              "WAIT has completed on channel 0\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int0, new_value_t.wait_int0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: wait_int1:1",
              "WAIT has completed on channel 1\n0 = NOT_PENDING;\n1 = PENDING",
              1, old_value_t.wait_int1, new_value_t.wait_int1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wait_int2:1",
              "WAIT has completed on channel 2\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int2, new_value_t.wait_int2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: wait_int3:1",
              "WAIT has completed on channel 3\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int3, new_value_t.wait_int3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: wait_int4:1",
              "WAIT has completed on channel 4\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int4, new_value_t.wait_int4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: wait_int5:1",
              "WAIT has completed on channel 5\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int5, new_value_t.wait_int5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: wait_int6:1",
              "WAIT has completed on channel 6\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int6, new_value_t.wait_int6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: wait_int7:1",
              "WAIT has completed on channel 7\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.wait_int7, new_value_t.wait_int7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rdma_inval_clreq_int:1",
              "Invalid client request to read DMA\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.rdma_inval_clreq_int, new_value_t.rdma_inval_clreq_int };
    m_bit_details_model.bits.append(entry);
    entry = { "17: rdma_buf_oflow_int0:1",
              "Buffer overflow in read DMA port0\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.rdma_buf_oflow_int0, new_value_t.rdma_buf_oflow_int0 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: rdma_buf_thold_int0:1",
              "Buffer threshold reached in read DMA port0\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.rdma_buf_thold_int0, new_value_t.rdma_buf_thold_int0 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rdma_databuf_thold_int0:1",
              "Read DMA data FIFO in port0 reached high level watermark\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.rdma_databuf_thold_int0, new_value_t.rdma_databuf_thold_int0 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_28:9", "", 9, old_value_t.undefined_bits_20_28, new_value_t.undefined_bits_20_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: csw_host1xw2mc_int:1",
              "Host write client FIFO has filled up",
              1, old_value_t.csw_host1xw2mc_int, new_value_t.csw_host1xw2mc_int };
    m_bit_details_model.bits.append(entry);
    entry = { "30: timer_intp:1",
              "Timer Interrupt from the Protected Channel\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.timer_intp, new_value_t.timer_intp };
    m_bit_details_model.bits.append(entry);
    entry = { "31: hintstatus_ext_int:1",
              "Additional interrupts pending in the HINSTATUS_EXT register\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.hintstatus_ext_int, new_value_t.hintstatus_ext_int };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " Host interrupt status Contains the interrupt status for the various host interrupts. The status is sticky and is PENDING until cleared (write 1's to INTSTATUS to clear).";
}

#define HINTMASK_OFFSET 0x24
#define HINTMASK_UNDEFMASK 0x1FF0FF00
union hintmask_u {
    struct {
        unsigned int wait_intmask0:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask1:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask2:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask3:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask4:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask5:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask6:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int wait_intmask7:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int rdma_inval_clreq_intmask:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int rdma_buf_oflow_intmask0:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int rdma_buf_thold_intmask0:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int rdma_databuf_thold_intmask0:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_20_28:9;
        unsigned int csw_host1xw2mc_intmask:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int timer_intmaskp:1;      /* Timer Interrupt Mask for the Protected Channel 0 = DISABLE 1 = ENABLE */
        unsigned int hintstatus_ext_intmask:1;/* 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hintmask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hintmask_u old_value_t = { .reg32 = value };
    const hintmask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wait_intmask0:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask0, new_value_t.wait_intmask0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: wait_intmask1:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask1, new_value_t.wait_intmask1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wait_intmask2:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask2, new_value_t.wait_intmask2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: wait_intmask3:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask3, new_value_t.wait_intmask3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: wait_intmask4:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask4, new_value_t.wait_intmask4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: wait_intmask5:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask5, new_value_t.wait_intmask5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: wait_intmask6:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask6, new_value_t.wait_intmask6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: wait_intmask7:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wait_intmask7, new_value_t.wait_intmask7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rdma_inval_clreq_intmask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.rdma_inval_clreq_intmask, new_value_t.rdma_inval_clreq_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "17: rdma_buf_oflow_intmask0:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.rdma_buf_oflow_intmask0, new_value_t.rdma_buf_oflow_intmask0 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: rdma_buf_thold_intmask0:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.rdma_buf_thold_intmask0, new_value_t.rdma_buf_thold_intmask0 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rdma_databuf_thold_intmask0:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.rdma_databuf_thold_intmask0, new_value_t.rdma_databuf_thold_intmask0 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_28:9", "", 9, old_value_t.undefined_bits_20_28, new_value_t.undefined_bits_20_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: csw_host1xw2mc_intmask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.csw_host1xw2mc_intmask, new_value_t.csw_host1xw2mc_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "30: timer_intmaskp:1",
              "Timer Interrupt Mask for the Protected Channel\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.timer_intmaskp, new_value_t.timer_intmaskp };
    m_bit_details_model.bits.append(entry);
    entry = { "31: hintstatus_ext_intmask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hintstatus_ext_intmask, new_value_t.hintstatus_ext_intmask };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Host interrupt mask contains the interrupt mask bits for all of the host interrupts. If the INT_MASK is ENABLED for a particular module, the modules INT bit from INTSTATUS contributes to the global interrupt signal.";
}

#define HINTSTATUS_EXT_OFFSET 0x28
#define HINTSTATUS_EXT_UNDEFMASK 0x3FFFFF00
union hintstatus_ext_u {
    struct {
        unsigned int cmdpp_illegal_opcode_int0:1;/* CMDPP0 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int1:1;/* CMDPP1 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int2:1;/* CMDPP2 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int3:1;/* CMDPP3 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int4:1;/* CMDPP4 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int5:1;/* CMDPP5 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int6:1;/* CMDPP6 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int cmdpp_illegal_opcode_int7:1;/* CMDPP7 has seen an illegal opcode.  0 = NOT_PENDING 1 = PENDING */
        unsigned int undefined_bits_8_29:22;
        unsigned int ip_read_int:1;         /* Read transaction timeout occured after IP_BUSY_TIMEOUT cycles. Offending address in IP_READ_TIMEOUT_ADDR. 0 = NOT_PENDING 1 = PENDING */
        unsigned int ip_write_int:1;        /* Write transaction timeout occured after IP_BUSY_TIMEOUT cycles. Offending address in IP_WRITE_TIMEOUT_ADDR. 0 = NOT_PENDING 1 = PENDING */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hintstatus_ext_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hintstatus_ext_u old_value_t = { .reg32 = value };
    const hintstatus_ext_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmdpp_illegal_opcode_int0:1",
              "CMDPP0 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int0, new_value_t.cmdpp_illegal_opcode_int0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cmdpp_illegal_opcode_int1:1",
              "CMDPP1 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int1, new_value_t.cmdpp_illegal_opcode_int1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cmdpp_illegal_opcode_int2:1",
              "CMDPP2 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int2, new_value_t.cmdpp_illegal_opcode_int2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cmdpp_illegal_opcode_int3:1",
              "CMDPP3 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int3, new_value_t.cmdpp_illegal_opcode_int3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cmdpp_illegal_opcode_int4:1",
              "CMDPP4 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int4, new_value_t.cmdpp_illegal_opcode_int4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cmdpp_illegal_opcode_int5:1",
              "CMDPP5 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int5, new_value_t.cmdpp_illegal_opcode_int5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cmdpp_illegal_opcode_int6:1",
              "CMDPP6 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int6, new_value_t.cmdpp_illegal_opcode_int6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: cmdpp_illegal_opcode_int7:1",
              "CMDPP7 has seen an illegal opcode.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.cmdpp_illegal_opcode_int7, new_value_t.cmdpp_illegal_opcode_int7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ip_read_int:1",
              "Read transaction timeout occured after IP_BUSY_TIMEOUT cycles. Offending address in IP_READ_TIMEOUT_ADDR.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.ip_read_int, new_value_t.ip_read_int };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ip_write_int:1",
              "Write transaction timeout occured after IP_BUSY_TIMEOUT cycles. Offending address in IP_WRITE_TIMEOUT_ADDR.\n0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.ip_write_int, new_value_t.ip_write_int };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " Extended Host interrupt status Contains additional interrupt status bits that did not fit in the HINTSTATUS register. When any of these bits is set, the HINTSTATUS_EXT_INT bit will also be set in the HINSTATUS register. Each status bit is sticky and PENDING until cleared (write 1's to HINTSTATUS_EXT to clear).";
}

#define HINTMASK_EXT_OFFSET 0x2C
#define HINTMASK_EXT_UNDEFMASK 0x3FFFFF00
union hintmask_ext_u {
    struct {
        unsigned int cmdpp_illegal_opcode_intmask0:1;/* Mask CMDPP_ILLEGAL_OPCODE_INT0 interrupt bit. 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask1:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask2:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask3:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask4:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask5:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask6:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int cmdpp_illegal_opcode_intmask7:1;/* See CMDPP_ILLEGAL_OPCODE_INTMASK0 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_8_29:22;
        unsigned int ip_read_intmask:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int ip_write_intmask:1;    /* 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hintmask_ext_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hintmask_ext_u old_value_t = { .reg32 = value };
    const hintmask_ext_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmdpp_illegal_opcode_intmask0:1",
              "Mask CMDPP_ILLEGAL_OPCODE_INT0 interrupt bit.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask0, new_value_t.cmdpp_illegal_opcode_intmask0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cmdpp_illegal_opcode_intmask1:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask1, new_value_t.cmdpp_illegal_opcode_intmask1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cmdpp_illegal_opcode_intmask2:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask2, new_value_t.cmdpp_illegal_opcode_intmask2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cmdpp_illegal_opcode_intmask3:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask3, new_value_t.cmdpp_illegal_opcode_intmask3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cmdpp_illegal_opcode_intmask4:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask4, new_value_t.cmdpp_illegal_opcode_intmask4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cmdpp_illegal_opcode_intmask5:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask5, new_value_t.cmdpp_illegal_opcode_intmask5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cmdpp_illegal_opcode_intmask6:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask6, new_value_t.cmdpp_illegal_opcode_intmask6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: cmdpp_illegal_opcode_intmask7:1",
              "See CMDPP_ILLEGAL_OPCODE_INTMASK0\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmdpp_illegal_opcode_intmask7, new_value_t.cmdpp_illegal_opcode_intmask7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ip_read_intmask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ip_read_intmask, new_value_t.ip_read_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ip_write_intmask:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ip_write_intmask, new_value_t.ip_write_intmask };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_THRESH_CPU0_INT_STATUS_OFFSET 0x40
#define SYNCPT_THRESH_CPU0_INT_STATUS_UNDEFMASK 0x00000000
union syncpt_thresh_cpu0_int_status_u {
    struct {
        unsigned int syncpt_thresh_cpu0_int_status_0:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_1:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_2:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_3:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_4:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_5:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_6:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_7:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_8:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_9:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_10:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_11:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_12:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_13:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_14:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_15:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_16:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_17:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_18:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_19:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_20:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_21:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_22:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_23:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_24:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_25:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_26:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_27:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_28:1;/* 0 = NOT_PENDING; 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_29:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_30:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu0_int_status_31:1;/* 0 = NOT_PENDING 1 = PENDING */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_cpu0_int_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_cpu0_int_status_u old_value_t = { .reg32 = value };
    const syncpt_thresh_cpu0_int_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_cpu0_int_status_0:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_0, new_value_t.syncpt_thresh_cpu0_int_status_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: syncpt_thresh_cpu0_int_status_1:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_1, new_value_t.syncpt_thresh_cpu0_int_status_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_cpu0_int_status_2:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_2, new_value_t.syncpt_thresh_cpu0_int_status_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: syncpt_thresh_cpu0_int_status_3:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_3, new_value_t.syncpt_thresh_cpu0_int_status_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_cpu0_int_status_4:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_4, new_value_t.syncpt_thresh_cpu0_int_status_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: syncpt_thresh_cpu0_int_status_5:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_5, new_value_t.syncpt_thresh_cpu0_int_status_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_cpu0_int_status_6:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_6, new_value_t.syncpt_thresh_cpu0_int_status_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: syncpt_thresh_cpu0_int_status_7:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_7, new_value_t.syncpt_thresh_cpu0_int_status_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_cpu0_int_status_8:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_8, new_value_t.syncpt_thresh_cpu0_int_status_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: syncpt_thresh_cpu0_int_status_9:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_9, new_value_t.syncpt_thresh_cpu0_int_status_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_cpu0_int_status_10:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_10, new_value_t.syncpt_thresh_cpu0_int_status_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: syncpt_thresh_cpu0_int_status_11:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_11, new_value_t.syncpt_thresh_cpu0_int_status_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_cpu0_int_status_12:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_12, new_value_t.syncpt_thresh_cpu0_int_status_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: syncpt_thresh_cpu0_int_status_13:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_13, new_value_t.syncpt_thresh_cpu0_int_status_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_cpu0_int_status_14:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_14, new_value_t.syncpt_thresh_cpu0_int_status_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: syncpt_thresh_cpu0_int_status_15:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_15, new_value_t.syncpt_thresh_cpu0_int_status_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_cpu0_int_status_16:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_16, new_value_t.syncpt_thresh_cpu0_int_status_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: syncpt_thresh_cpu0_int_status_17:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_17, new_value_t.syncpt_thresh_cpu0_int_status_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_cpu0_int_status_18:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_18, new_value_t.syncpt_thresh_cpu0_int_status_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: syncpt_thresh_cpu0_int_status_19:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_19, new_value_t.syncpt_thresh_cpu0_int_status_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_cpu0_int_status_20:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_20, new_value_t.syncpt_thresh_cpu0_int_status_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: syncpt_thresh_cpu0_int_status_21:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_21, new_value_t.syncpt_thresh_cpu0_int_status_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_cpu0_int_status_22:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_22, new_value_t.syncpt_thresh_cpu0_int_status_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: syncpt_thresh_cpu0_int_status_23:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_23, new_value_t.syncpt_thresh_cpu0_int_status_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_cpu0_int_status_24:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_24, new_value_t.syncpt_thresh_cpu0_int_status_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: syncpt_thresh_cpu0_int_status_25:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_25, new_value_t.syncpt_thresh_cpu0_int_status_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_cpu0_int_status_26:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_26, new_value_t.syncpt_thresh_cpu0_int_status_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: syncpt_thresh_cpu0_int_status_27:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_27, new_value_t.syncpt_thresh_cpu0_int_status_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_cpu0_int_status_28:1",
              "0 = NOT_PENDING;\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_28, new_value_t.syncpt_thresh_cpu0_int_status_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: syncpt_thresh_cpu0_int_status_29:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_29, new_value_t.syncpt_thresh_cpu0_int_status_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_cpu0_int_status_30:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_30, new_value_t.syncpt_thresh_cpu0_int_status_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: syncpt_thresh_cpu0_int_status_31:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu0_int_status_31, new_value_t.syncpt_thresh_cpu0_int_status_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Syncpt threshold interrupt status Two registers -- one for CPU0 (ARM11) and one for CPU1 (ARM7) Status is sticky and is PENDING until cleared. An interrupt routed to cpuN occurs when (SYNCPT[indx] >= SYNCPT_INT_THRESH[indx]) && (SYNCPT_THRESH_INT_MASK[indx] == cpuN) (compare takes into account wrap). Write 1's to clear.";
}

#define SYNCPT_THRESH_CPU1_INT_STATUS_OFFSET 0x48
#define SYNCPT_THRESH_CPU1_INT_STATUS_UNDEFMASK 0x00000000
union syncpt_thresh_cpu1_int_status_u {
    struct {
        unsigned int syncpt_thresh_cpu1_int_status_0:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_1:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_2:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_3:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_4:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_5:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_6:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_7:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_8:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_9:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_10:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_11:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_12:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_13:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_14:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_15:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_16:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_17:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_18:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_19:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_20:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_21:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_22:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_23:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_24:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_25:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_26:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_27:1;/* 0 = NOT_PENDING; 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_28:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_29:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_30:1;/* 0 = NOT_PENDING 1 = PENDING */
        unsigned int syncpt_thresh_cpu1_int_status_31:1;/* 0 = NOT_PENDING 1 = PENDING */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_cpu1_int_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_cpu1_int_status_u old_value_t = { .reg32 = value };
    const syncpt_thresh_cpu1_int_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_cpu1_int_status_0:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_0, new_value_t.syncpt_thresh_cpu1_int_status_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: syncpt_thresh_cpu1_int_status_1:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_1, new_value_t.syncpt_thresh_cpu1_int_status_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_cpu1_int_status_2:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_2, new_value_t.syncpt_thresh_cpu1_int_status_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: syncpt_thresh_cpu1_int_status_3:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_3, new_value_t.syncpt_thresh_cpu1_int_status_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_cpu1_int_status_4:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_4, new_value_t.syncpt_thresh_cpu1_int_status_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: syncpt_thresh_cpu1_int_status_5:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_5, new_value_t.syncpt_thresh_cpu1_int_status_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_cpu1_int_status_6:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_6, new_value_t.syncpt_thresh_cpu1_int_status_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: syncpt_thresh_cpu1_int_status_7:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_7, new_value_t.syncpt_thresh_cpu1_int_status_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_cpu1_int_status_8:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_8, new_value_t.syncpt_thresh_cpu1_int_status_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: syncpt_thresh_cpu1_int_status_9:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_9, new_value_t.syncpt_thresh_cpu1_int_status_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_cpu1_int_status_10:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_10, new_value_t.syncpt_thresh_cpu1_int_status_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: syncpt_thresh_cpu1_int_status_11:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_11, new_value_t.syncpt_thresh_cpu1_int_status_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_cpu1_int_status_12:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_12, new_value_t.syncpt_thresh_cpu1_int_status_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: syncpt_thresh_cpu1_int_status_13:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_13, new_value_t.syncpt_thresh_cpu1_int_status_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_cpu1_int_status_14:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_14, new_value_t.syncpt_thresh_cpu1_int_status_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: syncpt_thresh_cpu1_int_status_15:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_15, new_value_t.syncpt_thresh_cpu1_int_status_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_cpu1_int_status_16:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_16, new_value_t.syncpt_thresh_cpu1_int_status_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: syncpt_thresh_cpu1_int_status_17:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_17, new_value_t.syncpt_thresh_cpu1_int_status_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_cpu1_int_status_18:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_18, new_value_t.syncpt_thresh_cpu1_int_status_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: syncpt_thresh_cpu1_int_status_19:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_19, new_value_t.syncpt_thresh_cpu1_int_status_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_cpu1_int_status_20:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_20, new_value_t.syncpt_thresh_cpu1_int_status_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: syncpt_thresh_cpu1_int_status_21:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_21, new_value_t.syncpt_thresh_cpu1_int_status_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_cpu1_int_status_22:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_22, new_value_t.syncpt_thresh_cpu1_int_status_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: syncpt_thresh_cpu1_int_status_23:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_23, new_value_t.syncpt_thresh_cpu1_int_status_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_cpu1_int_status_24:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_24, new_value_t.syncpt_thresh_cpu1_int_status_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: syncpt_thresh_cpu1_int_status_25:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_25, new_value_t.syncpt_thresh_cpu1_int_status_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_cpu1_int_status_26:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_26, new_value_t.syncpt_thresh_cpu1_int_status_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: syncpt_thresh_cpu1_int_status_27:1",
              "0 = NOT_PENDING;\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_27, new_value_t.syncpt_thresh_cpu1_int_status_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_cpu1_int_status_28:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_28, new_value_t.syncpt_thresh_cpu1_int_status_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: syncpt_thresh_cpu1_int_status_29:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_29, new_value_t.syncpt_thresh_cpu1_int_status_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_cpu1_int_status_30:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_30, new_value_t.syncpt_thresh_cpu1_int_status_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: syncpt_thresh_cpu1_int_status_31:1",
              "0 = NOT_PENDING\n1 = PENDING",
              1, old_value_t.syncpt_thresh_cpu1_int_status_31, new_value_t.syncpt_thresh_cpu1_int_status_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_THRESH_INT_MASK_OFFSET 0x50
#define SYNCPT_THRESH_INT_MASK_UNDEFMASK 0x00000000
union syncpt_thresh_int_mask_u {
    struct {
        unsigned int syncpt_thresh_int_mask_0:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_1:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_2:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_3:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_4:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_5:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_6:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_7:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_8:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_9:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_10:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_11:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_12:2;/* 0 = DISABLE 1 = ENABLE_CPU0; 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_13:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_14:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_15:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_int_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_int_mask_u old_value_t = { .reg32 = value };
    const syncpt_thresh_int_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_int_mask_0:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_0, new_value_t.syncpt_thresh_int_mask_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_int_mask_1:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_1, new_value_t.syncpt_thresh_int_mask_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_int_mask_2:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_2, new_value_t.syncpt_thresh_int_mask_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_int_mask_3:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_3, new_value_t.syncpt_thresh_int_mask_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_int_mask_4:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_4, new_value_t.syncpt_thresh_int_mask_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_int_mask_5:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_5, new_value_t.syncpt_thresh_int_mask_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_int_mask_6:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_6, new_value_t.syncpt_thresh_int_mask_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_int_mask_7:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_7, new_value_t.syncpt_thresh_int_mask_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_int_mask_8:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_8, new_value_t.syncpt_thresh_int_mask_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_int_mask_9:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_9, new_value_t.syncpt_thresh_int_mask_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_int_mask_10:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_10, new_value_t.syncpt_thresh_int_mask_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_int_mask_11:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_11, new_value_t.syncpt_thresh_int_mask_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_int_mask_12:2",
              "0 = DISABLE\n1 = ENABLE_CPU0;\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_12, new_value_t.syncpt_thresh_int_mask_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_int_mask_13:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_13, new_value_t.syncpt_thresh_int_mask_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_int_mask_14:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_14, new_value_t.syncpt_thresh_int_mask_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_int_mask_15:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_15, new_value_t.syncpt_thresh_int_mask_15 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Syncpt threshold interrupt mask. If set to ENABLE_CPU0, routed to ARM11's interrupt signal If set to ENABLE_CPU1, routed to ARM7's interrupt signal.";
}

#define SYNCPT_THRESH_INT_MASK_1_OFFSET 0x54
#define SYNCPT_THRESH_INT_MASK_1_UNDEFMASK 0x00000000
union syncpt_thresh_int_mask_1_u {
    struct {
        unsigned int syncpt_thresh_int_mask_16:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_17:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_18:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_19:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_20:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_21:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_22:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_23:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_24:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_25:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_26:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_27:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_28:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_29:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_30:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_mask_31:2;/* 0 = DISABLE 1 = ENABLE_CPU0 2 = ENABLE_CPU1 */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_int_mask_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_int_mask_1_u old_value_t = { .reg32 = value };
    const syncpt_thresh_int_mask_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_int_mask_16:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_16, new_value_t.syncpt_thresh_int_mask_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_int_mask_17:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_17, new_value_t.syncpt_thresh_int_mask_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_int_mask_18:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_18, new_value_t.syncpt_thresh_int_mask_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_int_mask_19:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_19, new_value_t.syncpt_thresh_int_mask_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_int_mask_20:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_20, new_value_t.syncpt_thresh_int_mask_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_int_mask_21:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_21, new_value_t.syncpt_thresh_int_mask_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_int_mask_22:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_22, new_value_t.syncpt_thresh_int_mask_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_int_mask_23:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_23, new_value_t.syncpt_thresh_int_mask_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_int_mask_24:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_24, new_value_t.syncpt_thresh_int_mask_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_int_mask_25:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_25, new_value_t.syncpt_thresh_int_mask_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_int_mask_26:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_26, new_value_t.syncpt_thresh_int_mask_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_int_mask_27:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_27, new_value_t.syncpt_thresh_int_mask_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_int_mask_28:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_28, new_value_t.syncpt_thresh_int_mask_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_int_mask_29:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_29, new_value_t.syncpt_thresh_int_mask_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_int_mask_30:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_30, new_value_t.syncpt_thresh_int_mask_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_int_mask_31:2",
              "0 = DISABLE\n1 = ENABLE_CPU0\n2 = ENABLE_CPU1",
              2, old_value_t.syncpt_thresh_int_mask_31, new_value_t.syncpt_thresh_int_mask_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_THRESH_INT_DISABLE_OFFSET 0x60
#define SYNCPT_THRESH_INT_DISABLE_UNDEFMASK 0x00000000
union syncpt_thresh_int_disable_u {
    struct {
        unsigned int syncpt_thresh_int_disable_0:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_1:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_2:1;/* 0 = NO_CHANGE; 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_3:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_4:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_5:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_6:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_7:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_8:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_9:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_10:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_11:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_12:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_13:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_14:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_15:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_16:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_17:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_18:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_19:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_20:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_21:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_22:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_23:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_24:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_25:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_26:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_27:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_28:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_29:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_30:1;/* 0 = NO_CHANGE 1 = DISABLE */
        unsigned int syncpt_thresh_int_disable_31:1;/* 0 = NO_CHANGE 1 = DISABLE */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_int_disable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_int_disable_u old_value_t = { .reg32 = value };
    const syncpt_thresh_int_disable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_int_disable_0:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_0, new_value_t.syncpt_thresh_int_disable_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: syncpt_thresh_int_disable_1:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_1, new_value_t.syncpt_thresh_int_disable_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_int_disable_2:1",
              "0 = NO_CHANGE;\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_2, new_value_t.syncpt_thresh_int_disable_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: syncpt_thresh_int_disable_3:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_3, new_value_t.syncpt_thresh_int_disable_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_int_disable_4:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_4, new_value_t.syncpt_thresh_int_disable_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: syncpt_thresh_int_disable_5:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_5, new_value_t.syncpt_thresh_int_disable_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_int_disable_6:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_6, new_value_t.syncpt_thresh_int_disable_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: syncpt_thresh_int_disable_7:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_7, new_value_t.syncpt_thresh_int_disable_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_int_disable_8:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_8, new_value_t.syncpt_thresh_int_disable_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: syncpt_thresh_int_disable_9:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_9, new_value_t.syncpt_thresh_int_disable_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_int_disable_10:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_10, new_value_t.syncpt_thresh_int_disable_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: syncpt_thresh_int_disable_11:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_11, new_value_t.syncpt_thresh_int_disable_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_int_disable_12:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_12, new_value_t.syncpt_thresh_int_disable_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: syncpt_thresh_int_disable_13:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_13, new_value_t.syncpt_thresh_int_disable_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_int_disable_14:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_14, new_value_t.syncpt_thresh_int_disable_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: syncpt_thresh_int_disable_15:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_15, new_value_t.syncpt_thresh_int_disable_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_int_disable_16:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_16, new_value_t.syncpt_thresh_int_disable_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: syncpt_thresh_int_disable_17:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_17, new_value_t.syncpt_thresh_int_disable_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_int_disable_18:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_18, new_value_t.syncpt_thresh_int_disable_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: syncpt_thresh_int_disable_19:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_19, new_value_t.syncpt_thresh_int_disable_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_int_disable_20:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_20, new_value_t.syncpt_thresh_int_disable_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: syncpt_thresh_int_disable_21:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_21, new_value_t.syncpt_thresh_int_disable_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_int_disable_22:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_22, new_value_t.syncpt_thresh_int_disable_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: syncpt_thresh_int_disable_23:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_23, new_value_t.syncpt_thresh_int_disable_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_int_disable_24:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_24, new_value_t.syncpt_thresh_int_disable_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: syncpt_thresh_int_disable_25:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_25, new_value_t.syncpt_thresh_int_disable_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_int_disable_26:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_26, new_value_t.syncpt_thresh_int_disable_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: syncpt_thresh_int_disable_27:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_27, new_value_t.syncpt_thresh_int_disable_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_int_disable_28:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_28, new_value_t.syncpt_thresh_int_disable_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: syncpt_thresh_int_disable_29:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_29, new_value_t.syncpt_thresh_int_disable_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_int_disable_30:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_30, new_value_t.syncpt_thresh_int_disable_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: syncpt_thresh_int_disable_31:1",
              "0 = NO_CHANGE\n1 = DISABLE",
              1, old_value_t.syncpt_thresh_int_disable_31, new_value_t.syncpt_thresh_int_disable_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Write-only registers to change state of SYNCPT_THRESH_INT_MASK fields. Write a 1 to the Nth position to change syncpt[N]'s threshold interrupt mask. These register provide an alternative way to change the mask which is multiprocessor safe.";
}

#define SYNCPT_THRESH_INT_ENABLE_CPU0_OFFSET 0x68
#define SYNCPT_THRESH_INT_ENABLE_CPU0_UNDEFMASK 0x00000000
union syncpt_thresh_int_enable_cpu0_u {
    struct {
        unsigned int syncpt_thresh_int_enable_cpu0_0:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_1:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_2:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_3:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_4:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_5:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_6:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_7:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_8:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_9:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_10:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_11:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_12:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_13:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_14:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_15:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_16:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_17:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_18:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_19:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_20:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_21:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_22:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_23:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_24:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_25:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_26:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_27:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_28:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_29:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_30:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
        unsigned int syncpt_thresh_int_enable_cpu0_31:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU0 */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_int_enable_cpu0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_int_enable_cpu0_u old_value_t = { .reg32 = value };
    const syncpt_thresh_int_enable_cpu0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_int_enable_cpu0_0:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_0, new_value_t.syncpt_thresh_int_enable_cpu0_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: syncpt_thresh_int_enable_cpu0_1:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_1, new_value_t.syncpt_thresh_int_enable_cpu0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_int_enable_cpu0_2:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_2, new_value_t.syncpt_thresh_int_enable_cpu0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: syncpt_thresh_int_enable_cpu0_3:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_3, new_value_t.syncpt_thresh_int_enable_cpu0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_int_enable_cpu0_4:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_4, new_value_t.syncpt_thresh_int_enable_cpu0_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: syncpt_thresh_int_enable_cpu0_5:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_5, new_value_t.syncpt_thresh_int_enable_cpu0_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_int_enable_cpu0_6:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_6, new_value_t.syncpt_thresh_int_enable_cpu0_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: syncpt_thresh_int_enable_cpu0_7:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_7, new_value_t.syncpt_thresh_int_enable_cpu0_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_int_enable_cpu0_8:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_8, new_value_t.syncpt_thresh_int_enable_cpu0_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: syncpt_thresh_int_enable_cpu0_9:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_9, new_value_t.syncpt_thresh_int_enable_cpu0_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_int_enable_cpu0_10:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_10, new_value_t.syncpt_thresh_int_enable_cpu0_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: syncpt_thresh_int_enable_cpu0_11:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_11, new_value_t.syncpt_thresh_int_enable_cpu0_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_int_enable_cpu0_12:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_12, new_value_t.syncpt_thresh_int_enable_cpu0_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: syncpt_thresh_int_enable_cpu0_13:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_13, new_value_t.syncpt_thresh_int_enable_cpu0_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_int_enable_cpu0_14:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_14, new_value_t.syncpt_thresh_int_enable_cpu0_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: syncpt_thresh_int_enable_cpu0_15:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_15, new_value_t.syncpt_thresh_int_enable_cpu0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_int_enable_cpu0_16:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_16, new_value_t.syncpt_thresh_int_enable_cpu0_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: syncpt_thresh_int_enable_cpu0_17:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_17, new_value_t.syncpt_thresh_int_enable_cpu0_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_int_enable_cpu0_18:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_18, new_value_t.syncpt_thresh_int_enable_cpu0_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: syncpt_thresh_int_enable_cpu0_19:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_19, new_value_t.syncpt_thresh_int_enable_cpu0_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_int_enable_cpu0_20:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_20, new_value_t.syncpt_thresh_int_enable_cpu0_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: syncpt_thresh_int_enable_cpu0_21:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_21, new_value_t.syncpt_thresh_int_enable_cpu0_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_int_enable_cpu0_22:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_22, new_value_t.syncpt_thresh_int_enable_cpu0_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: syncpt_thresh_int_enable_cpu0_23:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_23, new_value_t.syncpt_thresh_int_enable_cpu0_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_int_enable_cpu0_24:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_24, new_value_t.syncpt_thresh_int_enable_cpu0_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: syncpt_thresh_int_enable_cpu0_25:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_25, new_value_t.syncpt_thresh_int_enable_cpu0_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_int_enable_cpu0_26:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_26, new_value_t.syncpt_thresh_int_enable_cpu0_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: syncpt_thresh_int_enable_cpu0_27:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_27, new_value_t.syncpt_thresh_int_enable_cpu0_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_int_enable_cpu0_28:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_28, new_value_t.syncpt_thresh_int_enable_cpu0_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: syncpt_thresh_int_enable_cpu0_29:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_29, new_value_t.syncpt_thresh_int_enable_cpu0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_int_enable_cpu0_30:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_30, new_value_t.syncpt_thresh_int_enable_cpu0_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: syncpt_thresh_int_enable_cpu0_31:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU0",
              1, old_value_t.syncpt_thresh_int_enable_cpu0_31, new_value_t.syncpt_thresh_int_enable_cpu0_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_THRESH_INT_ENABLE_CPU1_OFFSET 0x70
#define SYNCPT_THRESH_INT_ENABLE_CPU1_UNDEFMASK 0x00000000
union syncpt_thresh_int_enable_cpu1_u {
    struct {
        unsigned int syncpt_thresh_int_enable_cpu1_0:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_1:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_2:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_3:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_4:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_5:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_6:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_7:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_8:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_9:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_10:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_11:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_12:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_13:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_14:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_15:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_16:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_17:1;/* 0 = NO_CHANGE; 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_18:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_19:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_20:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_21:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_22:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_23:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_24:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_25:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_26:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_27:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_28:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_29:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_30:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
        unsigned int syncpt_thresh_int_enable_cpu1_31:1;/* 0 = NO_CHANGE 1 = ENABLE_CPU1 */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_thresh_int_enable_cpu1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_thresh_int_enable_cpu1_u old_value_t = { .reg32 = value };
    const syncpt_thresh_int_enable_cpu1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_thresh_int_enable_cpu1_0:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_0, new_value_t.syncpt_thresh_int_enable_cpu1_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: syncpt_thresh_int_enable_cpu1_1:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_1, new_value_t.syncpt_thresh_int_enable_cpu1_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: syncpt_thresh_int_enable_cpu1_2:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_2, new_value_t.syncpt_thresh_int_enable_cpu1_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: syncpt_thresh_int_enable_cpu1_3:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_3, new_value_t.syncpt_thresh_int_enable_cpu1_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: syncpt_thresh_int_enable_cpu1_4:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_4, new_value_t.syncpt_thresh_int_enable_cpu1_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: syncpt_thresh_int_enable_cpu1_5:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_5, new_value_t.syncpt_thresh_int_enable_cpu1_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: syncpt_thresh_int_enable_cpu1_6:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_6, new_value_t.syncpt_thresh_int_enable_cpu1_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: syncpt_thresh_int_enable_cpu1_7:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_7, new_value_t.syncpt_thresh_int_enable_cpu1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: syncpt_thresh_int_enable_cpu1_8:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_8, new_value_t.syncpt_thresh_int_enable_cpu1_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: syncpt_thresh_int_enable_cpu1_9:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_9, new_value_t.syncpt_thresh_int_enable_cpu1_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: syncpt_thresh_int_enable_cpu1_10:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_10, new_value_t.syncpt_thresh_int_enable_cpu1_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: syncpt_thresh_int_enable_cpu1_11:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_11, new_value_t.syncpt_thresh_int_enable_cpu1_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: syncpt_thresh_int_enable_cpu1_12:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_12, new_value_t.syncpt_thresh_int_enable_cpu1_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: syncpt_thresh_int_enable_cpu1_13:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_13, new_value_t.syncpt_thresh_int_enable_cpu1_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: syncpt_thresh_int_enable_cpu1_14:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_14, new_value_t.syncpt_thresh_int_enable_cpu1_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: syncpt_thresh_int_enable_cpu1_15:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_15, new_value_t.syncpt_thresh_int_enable_cpu1_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: syncpt_thresh_int_enable_cpu1_16:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_16, new_value_t.syncpt_thresh_int_enable_cpu1_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: syncpt_thresh_int_enable_cpu1_17:1",
              "0 = NO_CHANGE;\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_17, new_value_t.syncpt_thresh_int_enable_cpu1_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: syncpt_thresh_int_enable_cpu1_18:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_18, new_value_t.syncpt_thresh_int_enable_cpu1_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: syncpt_thresh_int_enable_cpu1_19:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_19, new_value_t.syncpt_thresh_int_enable_cpu1_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: syncpt_thresh_int_enable_cpu1_20:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_20, new_value_t.syncpt_thresh_int_enable_cpu1_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: syncpt_thresh_int_enable_cpu1_21:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_21, new_value_t.syncpt_thresh_int_enable_cpu1_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: syncpt_thresh_int_enable_cpu1_22:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_22, new_value_t.syncpt_thresh_int_enable_cpu1_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: syncpt_thresh_int_enable_cpu1_23:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_23, new_value_t.syncpt_thresh_int_enable_cpu1_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: syncpt_thresh_int_enable_cpu1_24:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_24, new_value_t.syncpt_thresh_int_enable_cpu1_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: syncpt_thresh_int_enable_cpu1_25:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_25, new_value_t.syncpt_thresh_int_enable_cpu1_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: syncpt_thresh_int_enable_cpu1_26:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_26, new_value_t.syncpt_thresh_int_enable_cpu1_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: syncpt_thresh_int_enable_cpu1_27:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_27, new_value_t.syncpt_thresh_int_enable_cpu1_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: syncpt_thresh_int_enable_cpu1_28:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_28, new_value_t.syncpt_thresh_int_enable_cpu1_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: syncpt_thresh_int_enable_cpu1_29:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_29, new_value_t.syncpt_thresh_int_enable_cpu1_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: syncpt_thresh_int_enable_cpu1_30:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_30, new_value_t.syncpt_thresh_int_enable_cpu1_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: syncpt_thresh_int_enable_cpu1_31:1",
              "0 = NO_CHANGE\n1 = ENABLE_CPU1",
              1, old_value_t.syncpt_thresh_int_enable_cpu1_31, new_value_t.syncpt_thresh_int_enable_cpu1_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF0_SETUP_OFFSET 0x80
#define CF0_SETUP_UNDEFMASK 0xFE00FE00
union cf0_setup_u {
    struct {
        unsigned int cf0_base:9;            /* Channel 0 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf0_limit:9;           /* Channel 0 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf0_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf0_setup_u old_value_t = { .reg32 = value };
    const cf0_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf0_base:9",
              "Channel 0 FIFO base",
              9, old_value_t.cf0_base, new_value_t.cf0_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf0_limit:9",
              "Channel 0 FIFO limit (highest address)",
              9, old_value_t.cf0_limit, new_value_t.cf0_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n Channel Processor and FIFO Setup, Control, Status\nCommand FIFO setup registers.  Sets up the various regions of the command FIFO.  SHOULD ONLY BE CHANGED WHEN THE FIFO IS EMPTY. These are initialized to 8 equal-sized FIFOs.";
}

#define CF1_SETUP_OFFSET 0x84
#define CF1_SETUP_UNDEFMASK 0xFE00FE00
union cf1_setup_u {
    struct {
        unsigned int cf1_base:9;            /* Channel 1 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf1_limit:9;           /* Channel 1 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf1_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf1_setup_u old_value_t = { .reg32 = value };
    const cf1_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf1_base:9",
              "Channel 1 FIFO base",
              9, old_value_t.cf1_base, new_value_t.cf1_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf1_limit:9",
              "Channel 1 FIFO limit (highest address)",
              9, old_value_t.cf1_limit, new_value_t.cf1_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF2_SETUP_OFFSET 0x88
#define CF2_SETUP_UNDEFMASK 0xFE00FE00
union cf2_setup_u {
    struct {
        unsigned int cf2_base:9;            /* Channel 2 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf2_limit:9;           /* Channel 2 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf2_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf2_setup_u old_value_t = { .reg32 = value };
    const cf2_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf2_base:9",
              "Channel 2 FIFO base",
              9, old_value_t.cf2_base, new_value_t.cf2_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf2_limit:9",
              "Channel 2 FIFO limit (highest address)",
              9, old_value_t.cf2_limit, new_value_t.cf2_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF3_SETUP_OFFSET 0x8C
#define CF3_SETUP_UNDEFMASK 0xFE00FE00
union cf3_setup_u {
    struct {
        unsigned int cf3_base:9;            /* Channel 3 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf3_limit:9;           /* Channel 3 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf3_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf3_setup_u old_value_t = { .reg32 = value };
    const cf3_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf3_base:9",
              "Channel 3 FIFO base",
              9, old_value_t.cf3_base, new_value_t.cf3_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf3_limit:9",
              "Channel 3 FIFO limit (highest address)",
              9, old_value_t.cf3_limit, new_value_t.cf3_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF4_SETUP_OFFSET 0x90
#define CF4_SETUP_UNDEFMASK 0xFE00FE00
union cf4_setup_u {
    struct {
        unsigned int cf4_base:9;            /* Channel 4 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf4_limit:9;           /* Channel 4 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf4_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf4_setup_u old_value_t = { .reg32 = value };
    const cf4_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf4_base:9",
              "Channel 4 FIFO base",
              9, old_value_t.cf4_base, new_value_t.cf4_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf4_limit:9",
              "Channel 4 FIFO limit (highest address)",
              9, old_value_t.cf4_limit, new_value_t.cf4_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF5_SETUP_OFFSET 0x94
#define CF5_SETUP_UNDEFMASK 0xFE00FE00
union cf5_setup_u {
    struct {
        unsigned int cf5_base:9;            /* Channel 5 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf5_limit:9;           /* Channel 5 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf5_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf5_setup_u old_value_t = { .reg32 = value };
    const cf5_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf5_base:9",
              "Channel 5 FIFO base",
              9, old_value_t.cf5_base, new_value_t.cf5_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf5_limit:9",
              "Channel 5 FIFO limit (highest address)",
              9, old_value_t.cf5_limit, new_value_t.cf5_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF6_SETUP_OFFSET 0x98
#define CF6_SETUP_UNDEFMASK 0xFE00FE00
union cf6_setup_u {
    struct {
        unsigned int cf6_base:9;            /* Channel 6 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf6_limit:9;           /* Channel 6 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf6_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf6_setup_u old_value_t = { .reg32 = value };
    const cf6_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf6_base:9",
              "Channel 6 FIFO base",
              9, old_value_t.cf6_base, new_value_t.cf6_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf6_limit:9",
              "Channel 6 FIFO limit (highest address)",
              9, old_value_t.cf6_limit, new_value_t.cf6_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF7_SETUP_OFFSET 0x9C
#define CF7_SETUP_UNDEFMASK 0xFE00FE00
union cf7_setup_u {
    struct {
        unsigned int cf7_base:9;            /* Channel 7 FIFO base */
        unsigned int undefined_bits_9_15:7;
        unsigned int cf7_limit:9;           /* Channel 7 FIFO limit (highest address) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf7_setup_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf7_setup_u old_value_t = { .reg32 = value };
    const cf7_setup_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf7_base:9",
              "Channel 7 FIFO base",
              9, old_value_t.cf7_base, new_value_t.cf7_base };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf7_limit:9",
              "Channel 7 FIFO limit (highest address)",
              9, old_value_t.cf7_limit, new_value_t.cf7_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CF_SETUPDONE_OFFSET 0xA0
#define CF_SETUPDONE_UNDEFMASK 0xFFFFFFFE
union cf_setupdone_u {
    struct {
        unsigned int cf_setupdone:1;        /* Dummy bit */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cf_setupdone_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cf_setupdone_u old_value_t = { .reg32 = value };
    const cf_setupdone_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf_setupdone:1",
              "Dummy bit",
              1, old_value_t.cf_setupdone, new_value_t.cf_setupdone };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Write to this register to trigger an update of the FIFO's pointers. ONLY DO THIS WHEN THE FIFO IS EMPTY.";
}

#define CMDPROC_CTRL_OFFSET 0xA4
#define CMDPROC_CTRL_UNDEFMASK 0xFFFFFFD9
union cmdproc_ctrl_u {
    struct {
        unsigned int undefined_bit_0:1;
        unsigned int drop_illegal_opcodes:1;
        unsigned int gather_parse_disabled:1;
        unsigned int undefined_bits_3_4:2;
        unsigned int intfc_clken_ovr:1;
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cmdproc_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmdproc_ctrl_u old_value_t = { .reg32 = value };
    const cmdproc_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bit_0:1", "", 1, old_value_t.undefined_bit_0, new_value_t.undefined_bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: drop_illegal_opcodes:1", "", 1, old_value_t.drop_illegal_opcodes, new_value_t.drop_illegal_opcodes };
    m_bit_details_model.bits.append(entry);
    entry = { "02: gather_parse_disabled:1", "", 1, old_value_t.gather_parse_disabled, new_value_t.gather_parse_disabled };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_4:2", "", 2, old_value_t.undefined_bits_3_4, new_value_t.undefined_bits_3_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: intfc_clken_ovr:1", "", 1, old_value_t.intfc_clken_ovr, new_value_t.intfc_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);
}

#define CMDPROC_STAT_OFFSET 0xA8
#define CMDPROC_STAT_UNDEFMASK 0xFFFFFF00
union cmdproc_stat_u {
    struct {
        unsigned int illegal_opcode:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cmdproc_stat_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmdproc_stat_u old_value_t = { .reg32 = value };
    const cmdproc_stat_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: illegal_opcode:8", "", 8, old_value_t.illegal_opcode, new_value_t.illegal_opcode };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define CMDPROC_STOP_OFFSET 0xAC
#define CMDPROC_STOP_UNDEFMASK 0xFFFFFF00
union cmdproc_stop_u {
    struct {
        unsigned int ch0_cmdproc_stop:1;
        unsigned int ch1_cmdproc_stop:1;
        unsigned int ch2_cmdproc_stop:1;
        unsigned int ch3_cmdproc_stop:1;
        unsigned int ch4_cmdproc_stop:1;
        unsigned int ch5_cmdproc_stop:1;    /* 0 = RUN 1 = STOP */
        unsigned int ch6_cmdproc_stop:1;    /* 0 = RUN 1 = STOP */
        unsigned int ch7_cmdproc_stop:1;    /* 0 = RUN 1 = STOP */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cmdproc_stop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmdproc_stop_u old_value_t = { .reg32 = value };
    const cmdproc_stop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0_cmdproc_stop:1", "", 1, old_value_t.ch0_cmdproc_stop, new_value_t.ch0_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1_cmdproc_stop:1", "", 1, old_value_t.ch1_cmdproc_stop, new_value_t.ch1_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2_cmdproc_stop:1", "", 1, old_value_t.ch2_cmdproc_stop, new_value_t.ch2_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3_cmdproc_stop:1", "", 1, old_value_t.ch3_cmdproc_stop, new_value_t.ch3_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4_cmdproc_stop:1", "", 1, old_value_t.ch4_cmdproc_stop, new_value_t.ch4_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5_cmdproc_stop:1",
              "0 = RUN\n1 = STOP",
              1, old_value_t.ch5_cmdproc_stop, new_value_t.ch5_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6_cmdproc_stop:1",
              "0 = RUN\n1 = STOP",
              1, old_value_t.ch6_cmdproc_stop, new_value_t.ch6_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7_cmdproc_stop:1",
              "0 = RUN\n1 = STOP",
              1, old_value_t.ch7_cmdproc_stop, new_value_t.ch7_cmdproc_stop };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CH*_CMDPROC_STOP stops issuing commands from the command FIFO.  This is useful to stop other channels when a channel teardown is needed to prevent unwanted traffic from happening at the same time.";
}

#define CH_TEARDOWN_OFFSET 0xB0
#define CH_TEARDOWN_UNDEFMASK 0xFFFFFF00
union ch_teardown_u {
    struct {
        unsigned int ch0_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch1_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch2_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch3_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch4_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch5_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch6_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int ch7_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch_teardown_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch_teardown_u old_value_t = { .reg32 = value };
    const ch_teardown_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch0_teardown, new_value_t.ch0_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch1_teardown, new_value_t.ch1_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch2_teardown, new_value_t.ch2_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch3_teardown, new_value_t.ch3_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ch4_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch4_teardown, new_value_t.ch4_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ch5_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch5_teardown, new_value_t.ch5_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ch6_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch6_teardown, new_value_t.ch6_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ch7_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.ch7_teardown, new_value_t.ch7_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Channel teardown register.  Tells the hardware that a channel has gone away. Will reset that channel's command FIFO and release any locks it has in the arbiter.  Will NOT reset that channel's output FIFO, which can be emptied by reading out all remaining entries.";
}

#define MOD_TEARDOWN_OFFSET 0xB4
#define MOD_TEARDOWN_UNDEFMASK 0xFFFFE081
union mod_teardown_u {
    struct {
        unsigned int undefined_bit_0:1;
        unsigned int mpe_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int vi_teardown:1;         /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int epp_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int isp_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int gr2d_teardown:1;       /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int gr3d_teardown:1;       /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int undefined_bit_7:1;
        unsigned int display_teardown:1;    /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int displayb_teardown:1;   /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int hdmi_teardown:1;       /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int tvo_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int dsi_teardown:1;        /* 0 = NO_ACTION 1 = TEARDOWN */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mod_teardown_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mod_teardown_u old_value_t = { .reg32 = value };
    const mod_teardown_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bit_0:1", "", 1, old_value_t.undefined_bit_0, new_value_t.undefined_bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mpe_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.mpe_teardown, new_value_t.mpe_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vi_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.vi_teardown, new_value_t.vi_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "03: epp_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.epp_teardown, new_value_t.epp_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "04: isp_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.isp_teardown, new_value_t.isp_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "05: gr2d_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.gr2d_teardown, new_value_t.gr2d_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "06: gr3d_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.gr3d_teardown, new_value_t.gr3d_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bit_7:1", "", 1, old_value_t.undefined_bit_7, new_value_t.undefined_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.display_teardown, new_value_t.display_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "09: displayb_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.displayb_teardown, new_value_t.displayb_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "10: hdmi_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.hdmi_teardown, new_value_t.hdmi_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "11: tvo_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.tvo_teardown, new_value_t.tvo_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dsi_teardown:1",
              "0 = NO_ACTION\n1 = TEARDOWN",
              1, old_value_t.dsi_teardown, new_value_t.dsi_teardown };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Module teardown register.  If a module is reset, the host needs to reset its state with respect to which channels own that module.  Whenever a module is reset, the corresponding teardown bit in this register should be written. Module teardown will only work if the command FIFO/command processor are in a good state (the FIFO is empty of traffic for that channel and the command processor is at an opcode boundary).  If an entire channel needs to be reset, the CH_TEARDOWN register should be used instead.";
}

#define CH0_STATUS_OFFSET 0xB8
#define CH0_STATUS_UNDEFMASK 0x7C00FFFF
union ch0_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class0:10;       /* Current or blocked (requested) class for channel 0 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending0:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch0_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch0_status_u old_value_t = { .reg32 = value };
    const ch0_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class0:10",
              "Current or blocked (requested) class for channel 0",
              10, old_value_t.chout_class0, new_value_t.chout_class0 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending0:1", "", 1, old_value_t.ctxsw_pending0, new_value_t.ctxsw_pending0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The channel status registers show each channel's working class. CHOUT_CLASS* holds the requested class in the case of a blocked context switch.";
}

#define CH1_STATUS_OFFSET 0xBC
#define CH1_STATUS_UNDEFMASK 0x7C00FFFF
union ch1_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class1:10;       /* Current or blocked (requested) class for channel 1 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending1:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch1_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch1_status_u old_value_t = { .reg32 = value };
    const ch1_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class1:10",
              "Current or blocked (requested) class for channel 1",
              10, old_value_t.chout_class1, new_value_t.chout_class1 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending1:1", "", 1, old_value_t.ctxsw_pending1, new_value_t.ctxsw_pending1 };
    m_bit_details_model.bits.append(entry);
}

#define CH2_STATUS_OFFSET 0xC0
#define CH2_STATUS_UNDEFMASK 0x7C00FFFF
union ch2_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class2:10;       /* Current or blocked (requested) class for channel 2 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending2:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch2_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch2_status_u old_value_t = { .reg32 = value };
    const ch2_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class2:10",
              "Current or blocked (requested) class for channel 2",
              10, old_value_t.chout_class2, new_value_t.chout_class2 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending2:1", "", 1, old_value_t.ctxsw_pending2, new_value_t.ctxsw_pending2 };
    m_bit_details_model.bits.append(entry);
}

#define CH3_STATUS_OFFSET 0xC4
#define CH3_STATUS_UNDEFMASK 0x7C00FFFF
union ch3_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class3:10;       /* Current or blocked (requested) class for channel 3 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending3:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch3_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch3_status_u old_value_t = { .reg32 = value };
    const ch3_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class3:10",
              "Current or blocked (requested) class for channel 3",
              10, old_value_t.chout_class3, new_value_t.chout_class3 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending3:1", "", 1, old_value_t.ctxsw_pending3, new_value_t.ctxsw_pending3 };
    m_bit_details_model.bits.append(entry);
}

#define CH4_STATUS_OFFSET 0xC8
#define CH4_STATUS_UNDEFMASK 0x7C00FFFF
union ch4_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class4:10;       /* Current or blocked (requested) class for channel 4 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending4:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch4_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch4_status_u old_value_t = { .reg32 = value };
    const ch4_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class4:10",
              "Current or blocked (requested) class for channel 4",
              10, old_value_t.chout_class4, new_value_t.chout_class4 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending4:1", "", 1, old_value_t.ctxsw_pending4, new_value_t.ctxsw_pending4 };
    m_bit_details_model.bits.append(entry);
}

#define CH5_STATUS_OFFSET 0xCC
#define CH5_STATUS_UNDEFMASK 0x7C00FFFF
union ch5_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class5:10;       /* Current or blocked (requested) class for channel 5 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending5:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch5_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch5_status_u old_value_t = { .reg32 = value };
    const ch5_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class5:10",
              "Current or blocked (requested) class for channel 5",
              10, old_value_t.chout_class5, new_value_t.chout_class5 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending5:1", "", 1, old_value_t.ctxsw_pending5, new_value_t.ctxsw_pending5 };
    m_bit_details_model.bits.append(entry);
}

#define CH6_STATUS_OFFSET 0xD0
#define CH6_STATUS_UNDEFMASK 0x7C00FFFF
union ch6_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class6:10;       /* Current or blocked (requested) class for channel 6 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending6:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch6_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch6_status_u old_value_t = { .reg32 = value };
    const ch6_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class6:10",
              "Current or blocked (requested) class for channel 6",
              10, old_value_t.chout_class6, new_value_t.chout_class6 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending6:1", "", 1, old_value_t.ctxsw_pending6, new_value_t.ctxsw_pending6 };
    m_bit_details_model.bits.append(entry);
}

#define CH7_STATUS_OFFSET 0xD4
#define CH7_STATUS_UNDEFMASK 0x7C00FFFF
union ch7_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int chout_class7:10;       /* Current or blocked (requested) class for channel 7 */
        unsigned int undefined_bits_26_30:5;
        unsigned int ctxsw_pending7:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ch7_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ch7_status_u old_value_t = { .reg32 = value };
    const ch7_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: chout_class7:10",
              "Current or blocked (requested) class for channel 7",
              10, old_value_t.chout_class7, new_value_t.chout_class7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_30:5", "", 5, old_value_t.undefined_bits_26_30, new_value_t.undefined_bits_26_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ctxsw_pending7:1", "", 1, old_value_t.ctxsw_pending7, new_value_t.ctxsw_pending7 };
    m_bit_details_model.bits.append(entry);
}

#define DISPLAY_STATUS_OFFSET 0xD8
#define DISPLAY_STATUS_UNDEFMASK 0xFC00FFFF
union display_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int display_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_display_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const display_status_u old_value_t = { .reg32 = value };
    const display_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: display_currcl:10", "", 10, old_value_t.display_currcl, new_value_t.display_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The per-client status registers indicate which channel owns each client as well as the current working class for each client.  This is useful for determining each client's state with regard to granting context switches. _CURRCL is the current class id for that module.";
}

#define DISPLAYB_STATUS_OFFSET 0xDC
#define DISPLAYB_STATUS_UNDEFMASK 0xFC00FFFF
union displayb_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int displayb_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_displayb_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const displayb_status_u old_value_t = { .reg32 = value };
    const displayb_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: displayb_currcl:10", "", 10, old_value_t.displayb_currcl, new_value_t.displayb_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define EPP_STATUS_OFFSET 0xE0
#define EPP_STATUS_UNDEFMASK 0xFC00FFFF
union epp_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int epp_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_epp_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const epp_status_u old_value_t = { .reg32 = value };
    const epp_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: epp_currcl:10", "", 10, old_value_t.epp_currcl, new_value_t.epp_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define GR3D_STATUS_OFFSET 0xE4
#define GR3D_STATUS_UNDEFMASK 0xFC00FFFF
union gr3d_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int gr3d_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_gr3d_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gr3d_status_u old_value_t = { .reg32 = value };
    const gr3d_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: gr3d_currcl:10", "", 10, old_value_t.gr3d_currcl, new_value_t.gr3d_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define ISP_STATUS_OFFSET 0xE8
#define ISP_STATUS_UNDEFMASK 0xFC00FFFF
union isp_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int isp_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_isp_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const isp_status_u old_value_t = { .reg32 = value };
    const isp_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: isp_currcl:10", "", 10, old_value_t.isp_currcl, new_value_t.isp_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define MPE_STATUS_OFFSET 0xEC
#define MPE_STATUS_UNDEFMASK 0xFC00FFFF
union mpe_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int mpe_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mpe_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mpe_status_u old_value_t = { .reg32 = value };
    const mpe_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: mpe_currcl:10", "", 10, old_value_t.mpe_currcl, new_value_t.mpe_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define TVO_STATUS_OFFSET 0xF0
#define TVO_STATUS_UNDEFMASK 0xFC00FFFF
union tvo_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int tvo_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_tvo_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tvo_status_u old_value_t = { .reg32 = value };
    const tvo_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: tvo_currcl:10", "", 10, old_value_t.tvo_currcl, new_value_t.tvo_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define DSI_STATUS_OFFSET 0xF4
#define DSI_STATUS_UNDEFMASK 0xFC00FFFF
union dsi_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int dsi_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_dsi_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dsi_status_u old_value_t = { .reg32 = value };
    const dsi_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dsi_currcl:10", "", 10, old_value_t.dsi_currcl, new_value_t.dsi_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define HDMI_STATUS_OFFSET 0xF8
#define HDMI_STATUS_UNDEFMASK 0xFC00FFFF
union hdmi_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int hdmi_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hdmi_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hdmi_status_u old_value_t = { .reg32 = value };
    const hdmi_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: hdmi_currcl:10", "", 10, old_value_t.hdmi_currcl, new_value_t.hdmi_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define VI_STATUS_OFFSET 0xFC
#define VI_STATUS_UNDEFMASK 0xFC00FFFF
union vi_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int vi_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_vi_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vi_status_u old_value_t = { .reg32 = value };
    const vi_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: vi_currcl:10", "", 10, old_value_t.vi_currcl, new_value_t.vi_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define GR2D_STATUS_OFFSET 0x100
#define GR2D_STATUS_UNDEFMASK 0xFC00FFFF
union gr2d_status_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int gr2d_currcl:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_gr2d_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gr2d_status_u old_value_t = { .reg32 = value };
    const gr2d_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: gr2d_currcl:10", "", 10, old_value_t.gr2d_currcl, new_value_t.gr2d_currcl };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define DIRECT_MODULE_CONFIG_OFFSET 0x1A0
#define DIRECT_MODULE_CONFIG_UNDEFMASK 0x00000003
union direct_module_config_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int base:30;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_direct_module_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const direct_module_config_u old_value_t = { .reg32 = value };
    const direct_module_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: base:30", "", 30, old_value_t.base, new_value_t.base };
    m_bit_details_model.bits.append(entry);
}

#define USEC_CLK_OFFSET 0x1A4
#define USEC_CLK_UNDEFMASK 0xFFFFF000
union usec_clk_u {
    struct {
        unsigned int usec_clks:12;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_usec_clk_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usec_clk_u old_value_t = { .reg32 = value };
    const usec_clk_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: usec_clks:12", "", 12, old_value_t.usec_clks, new_value_t.usec_clks };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Number of host clocks needed to make a microsecond.  Used for the DELAY host\n method.  For example, if the host clock is 250 MHz, this register should be\n programmed to 250.  If the host clock is 150 MHz, this register should be\n programmed to 150.";
}

#define CTXSW_TIMEOUT_CFG_OFFSET 0x1A8
#define CTXSW_TIMEOUT_CFG_UNDEFMASK 0xFFFFFF00
union ctxsw_timeout_cfg_u {
    struct {
        unsigned int wait_ctxsw_cnt:8;      /* # of cycles to wait */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ctxsw_timeout_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ctxsw_timeout_cfg_u old_value_t = { .reg32 = value };
    const ctxsw_timeout_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wait_ctxsw_cnt:8",
              "# of cycles to wait",
              8, old_value_t.wait_ctxsw_cnt, new_value_t.wait_ctxsw_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "With channel ownership of modules removed, only generate ctxsw if a channel writes to a new class on a client. To keep from continually switching contexts if channels are addressing same client, keep a counter of commands issued to client, and don't switch until the client has either received WAIT_CTXSW_CNT clocks\nbefore switching or the channel stops targeting it.  So if 4 channels are currently in use, with 2 channels targeting different classes on the same client, if the value were set to 6, it would guarantee 2 commands were sent from any channel to the client's current class";
}

#define INDREG_DMA_CTRL_OFFSET 0x1AC
#define INDREG_DMA_CTRL_UNDEFMASK 0xFFFFFF10
union indreg_dma_ctrl_u {
    struct {
        unsigned int ahbdma_chid:4;         /* channel being used by indirect rd for dma (which chout FIFO to monitor) */
        unsigned int undefined_bit_4:1;
        unsigned int ahbdma_attn_lvl:2;     /* # of entries to rx'd before sending dma req, 1, 4, or 8 */
        unsigned int ahbdma_enable:1;       /* enable generation of req to dma engine  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_indreg_dma_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const indreg_dma_ctrl_u old_value_t = { .reg32 = value };
    const indreg_dma_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ahbdma_chid:4",
              "channel being used by indirect rd for dma (which chout FIFO to monitor)",
              4, old_value_t.ahbdma_chid, new_value_t.ahbdma_chid };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bit_4:1", "", 1, old_value_t.undefined_bit_4, new_value_t.undefined_bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ahbdma_attn_lvl:2",
              "# of entries to rx'd before sending dma req, 1, 4, or 8",
              2, old_value_t.ahbdma_attn_lvl, new_value_t.ahbdma_attn_lvl };
    m_bit_details_model.bits.append(entry);
    entry = { "07: ahbdma_enable:1",
              "enable generation of req to dma engine \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahbdma_enable, new_value_t.ahbdma_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Enable use of dma engine to move data from indirect reg interface to memory. ATTN_LVL controls flow between host and DMA.  DMA will not start transfer until the set # of slots are full:\n    * 00 = 1  slot\n    * 01 = 4  slots\n    * 10 = 8  slots";
}

#define CHANNEL_PRIORITY_OFFSET 0x1B0
#define CHANNEL_PRIORITY_UNDEFMASK 0xFFFFFF00
union channel_priority_u {
    struct {
        unsigned int hipri_ch0:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int hipri_ch1:1;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int hipri_ch2:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int hipri_ch3:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int hipri_ch4:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int hipri_ch5:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int hipri_ch6:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int hipri_ch7:1;           /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_channel_priority_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channel_priority_u old_value_t = { .reg32 = value };
    const channel_priority_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hipri_ch0:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch0, new_value_t.hipri_ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: hipri_ch1:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hipri_ch1, new_value_t.hipri_ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: hipri_ch2:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch2, new_value_t.hipri_ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: hipri_ch3:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch3, new_value_t.hipri_ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: hipri_ch4:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch4, new_value_t.hipri_ch4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: hipri_ch5:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch5, new_value_t.hipri_ch5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: hipri_ch6:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch6, new_value_t.hipri_ch6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: hipri_ch7:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hipri_ch7, new_value_t.hipri_ch7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Set channel priority for dual ring arbitration (hi/lo). Used in arbitrating MLOCK's.";
}

#define CDMA_ASM_TIMEOUT_OFFSET 0x1B4
#define CDMA_ASM_TIMEOUT_UNDEFMASK 0xFFFFE0E0
union cdma_asm_timeout_u {
    struct {
        unsigned int cdma_asm_dfifo_timeout:5;
        unsigned int undefined_bits_5_7:3;
        unsigned int cdma_asm_gfifo_timeout:5;
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cdma_asm_timeout_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cdma_asm_timeout_u old_value_t = { .reg32 = value };
    const cdma_asm_timeout_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cdma_asm_dfifo_timeout:5", "", 5, old_value_t.cdma_asm_dfifo_timeout, new_value_t.cdma_asm_dfifo_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cdma_asm_gfifo_timeout:5", "", 5, old_value_t.cdma_asm_gfifo_timeout, new_value_t.cdma_asm_gfifo_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Timeout value: determines how long the assembly logic will wait before it flushes data from the data FIFO to avoid head-of-line blocking.\nNote:\n Do not use a value of zero -- causes immediate flushing so no forward progress is made.";
}

#define CDMA_MISC_OFFSET 0x1B8
#define CDMA_MISC_UNDEFMASK 0xFFFFF8C0
union cdma_misc_u {
    struct {
        unsigned int cdma_delay_put:6;
        unsigned int undefined_bits_6_7:2;
        unsigned int cdma_simple_prefetch:1;
        unsigned int cdma_put_sync_disable:1;
        unsigned int cdma_clken_ovr:1;
        unsigned int undefined_bits_11_31:21;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cdma_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cdma_misc_u old_value_t = { .reg32 = value };
    const cdma_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cdma_delay_put:6", "", 6, old_value_t.cdma_delay_put, new_value_t.cdma_delay_put };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cdma_simple_prefetch:1", "", 1, old_value_t.cdma_simple_prefetch, new_value_t.cdma_simple_prefetch };
    m_bit_details_model.bits.append(entry);
    entry = { "09: cdma_put_sync_disable:1", "", 1, old_value_t.cdma_put_sync_disable, new_value_t.cdma_put_sync_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "10: cdma_clken_ovr:1", "", 1, old_value_t.cdma_clken_ovr, new_value_t.cdma_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bits_11_31:21", "", 21, old_value_t.undefined_bits_11_31, new_value_t.undefined_bits_11_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CDMA_DELAY_PUT\nDelay put_addr updates. This can potentially increase MC performance slighlty by gathering multiple consecutive put_addr updates into 1 update which reduced the amount of requests to the MC. In addition, it can be used to cover a race condition where a write to memory hasn't completed before CDMA starts fetching the data. But in this case, the counter has to be set to a high value, which *will* affect performance.\nCDMA_SIMPLE_PREFETCH\nReduce per-channel requests to 1 every 3 cycles. This can reduce performance in 2 ways:\n    * The memory request FIFO will fill up slighly slower, but the impact will be minimal.\n    * It will cause the channel arbiter to switch to other channels when they have a request available, which will reduce locality.\nCDMA_PUT_SYNC_DISABLE\nCDMA_EN_STATS\nEnable statistics counters.\n    *  - Count the number of 128-bit words fetched by CDMA\n    *  - Count the number of 128-bit words thrown away by CDMA\nThis allows us to get a idea how efficient the CDMA really is when there are multiple pushbuffers are active at the same time.";
}

#define IP_BUSY_TIMEOUT_OFFSET 0x1BC
#define IP_BUSY_TIMEOUT_UNDEFMASK 0xFFFF0000
union ip_busy_timeout_u {
    struct {
        unsigned int ip_busy_timeout:16;    /* Number of busy cycles before requesting a retry. 0 = disabled */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ip_busy_timeout_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ip_busy_timeout_u old_value_t = { .reg32 = value };
    const ip_busy_timeout_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ip_busy_timeout:16",
              "Number of busy cycles before requesting a retry.\n0 = disabled",
              16, old_value_t.ip_busy_timeout, new_value_t.ip_busy_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define IP_READ_TIMEOUT_ADDR_OFFSET 0x1C0
#define IP_READ_TIMEOUT_ADDR_UNDEFMASK 0x00000003
union ip_read_timeout_addr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ip_read_timeout_addr:30;/* Address of transaction that caused an AXI read timeout */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ip_read_timeout_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ip_read_timeout_addr_u old_value_t = { .reg32 = value };
    const ip_read_timeout_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ip_read_timeout_addr:30",
              "Address of transaction that caused an AXI read timeout",
              30, old_value_t.ip_read_timeout_addr, new_value_t.ip_read_timeout_addr };
    m_bit_details_model.bits.append(entry);
}

#define IP_WRITE_TIMEOUT_ADDR_OFFSET 0x1C4
#define IP_WRITE_TIMEOUT_ADDR_UNDEFMASK 0x00000003
union ip_write_timeout_addr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ip_write_timeout_addr:30;/* Address of transaction that caused an AXI write timeout */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_ip_write_timeout_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ip_write_timeout_addr_u old_value_t = { .reg32 = value };
    const ip_write_timeout_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ip_write_timeout_addr:30",
              "Address of transaction that caused an AXI write timeout",
              30, old_value_t.ip_write_timeout_addr, new_value_t.ip_write_timeout_addr };
    m_bit_details_model.bits.append(entry);
}

#define MCCIF_THCTRL_OFFSET 0x1D8
#define MCCIF_THCTRL_UNDEFMASK 0xFFFFC0C0
union mccif_thctrl_u {
    struct {
        unsigned int csw_host1xw_fifostat:6;
        unsigned int undefined_bits_6_7:2;
        unsigned int csw_host1xw2mc_hpth:6;
        unsigned int undefined_bits_14_31:18;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mccif_thctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mccif_thctrl_u old_value_t = { .reg32 = value };
    const mccif_thctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: csw_host1xw_fifostat:6", "", 6, old_value_t.csw_host1xw_fifostat, new_value_t.csw_host1xw_fifostat };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: csw_host1xw2mc_hpth:6", "", 6, old_value_t.csw_host1xw2mc_hpth, new_value_t.csw_host1xw2mc_hpth };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_31:18", "", 18, old_value_t.undefined_bits_14_31, new_value_t.undefined_bits_14_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Memory write client FIFO status. Reads out the available 128-bit entries. If writing through the buffered framebuffer write region, writes are accumulated up to 128 bits before being flushed, so 10 entries can mean up to 40 writes. Memory client high-priority threshold control register.  Sets the threshold of when the client becomes high-priority.";
}

#define HC_MCCIF_FIFOCTRL_OFFSET 0x1DC
#define HC_MCCIF_FIFOCTRL_UNDEFMASK 0xFFFFFFF0
union hc_mccif_fifoctrl_u {
    struct {
        unsigned int hc_mccif_wrcl_mcle2x:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int hc_mccif_rdmc_rdfast:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int hc_mccif_wrmc_clle2x:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int hc_mccif_rdcl_rdfast:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hc_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hc_mccif_fifoctrl_u old_value_t = { .reg32 = value };
    const hc_mccif_fifoctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hc_mccif_wrcl_mcle2x:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hc_mccif_wrcl_mcle2x, new_value_t.hc_mccif_wrcl_mcle2x };
    m_bit_details_model.bits.append(entry);
    entry = { "01: hc_mccif_rdmc_rdfast:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hc_mccif_rdmc_rdfast, new_value_t.hc_mccif_rdmc_rdfast };
    m_bit_details_model.bits.append(entry);
    entry = { "02: hc_mccif_wrmc_clle2x:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hc_mccif_wrmc_clle2x, new_value_t.hc_mccif_wrmc_clle2x };
    m_bit_details_model.bits.append(entry);
    entry = { "03: hc_mccif_rdcl_rdfast:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hc_mccif_rdcl_rdfast, new_value_t.hc_mccif_rdcl_rdfast };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Memory Client Interface FIFO Control Register. The registers below allow to optimize the synchronization timing in the memory client asynchronous FIFOs. When they can be used depend on the client and memory controller clock ratio. Additionally, the RDMC_RDFAST/RDCL_RDFAST fields can increase power consumption if the asynchronous FIFO is implemented as a real ram. There is no power impact on latch-based FIFOs. Flipflop-based FIFOs do not use these fields. See recommended settings below.\nNote:\n IMPORTANT: The register fields can only be changed when the memory client async FIFOs are empty.\nThe register field ending with WRCL_MCLE2X (if any) can be set to improve async FIFO synchronization on the write side by one client clock cycle if the memory controller clock frequency is less or equal to twice the client clock frequency:\nmcclk_freq <= 2 * clientclk_freq\nThe register field ending with WRMC_CLLE2X (if any) can be set to improve async FIFO synchronization on the write side by one memory controller clock cycle if the client clock frequency is less or equal to twice the memory controller clock frequency:\nclientclk_freq <= 2 * mcclk_freq\nThe register field ending with RDMC_RDFAST (if any) can be set to improve async FIFO synchronization on the read side by one memory controller clock cycle.\nNote:\n WARNING:\nRDMC_RDFAST can be used along with WRCL_MCLE2X only when:\nmcclk_freq <= clientclk_freq\nThe register field ending with RDCL_RDFAST (if any) can be set to improve async FIFO synchronization on the read side by one client clock cycle.\nRDCL_RDFAST can be used along with WRMC_CLLE2X only when:\nclientclk_freq <= mcclk_freq\nRecommended Settings\nClient writing to FIFO, memory controller reading from FIFO\n    * mcclk_freq <= clientclk_freq\nYou can enable both RDMC_RDFAST and WRCL_CLLE2X. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDMC_RDFAST.\n    * clientclk_freq < mcclk_freq <= 2 * clientclk_freq\nYou can enable RDMC_RDFAST or WRCL_MCLE2X, but because the client clock is slower, you should enable only WRCL_MCLE2X.\n    * 2 * clientclk_freq < mcclk_freq\nYou can only enable RDMC_RDFAST. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDMC_RDFAST.\nMemory controller writing to FIFO, client reading from FIFO\n    * clientclk_freq <= mcclk_freq\nYou can enable both RDCL_RDFAST and WRMC_CLLE2X. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDCL_RDFAST.\n    * mcclk_freq < clientclk_freq <= 2 * mcclk_freq\nYou can enable RDCL_RDFAST or WRMC_CLLE2X, but because the memory controller clock is slower, you should enable only WRMC_CLLE2X.\n    * 2 * mcclk_freq < clientclk_freq\nYou can only enable RDCL_RDFAST. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDCL_RDFAST.";
}

#define TIMEOUT_WCOAL_HC_OFFSET 0x1E0
#define TIMEOUT_WCOAL_HC_UNDEFMASK 0xFFFFFF00
union timeout_wcoal_hc_u {
    struct {
        unsigned int host1xw_wcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_timeout_wcoal_hc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_wcoal_hc_u old_value_t = { .reg32 = value };
    const timeout_wcoal_hc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1xw_wcoal_tmval:8", "", 8, old_value_t.host1xw_wcoal_tmval, new_value_t.host1xw_wcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Write Coalescing Time-Out Register. This register exists only for write clients. Reset value defaults to  to 50 for most clients, but may be different for certain clients. Write coalescing happens inside the memory client. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_MW-bit request. The register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the memory controller.\nWrite coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced write guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe write coalescing time-out should be programmed depending on the client behavior. The first write is obviously delayed by an amount of client cycles equal to the time-out value. Note that writes tagged by the client (i.e. the client expects a write response, usually for coherency), and the last write of a block transfer are not delayed. They only have a one-cycle opportunity to get coalesced.";
}

#define HWLOCK0_OFFSET 0x280
#define HWLOCK0_UNDEFMASK 0xFFFFFFFE
union hwlock0_u {
    struct {
        unsigned int hwlock0:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock0_u old_value_t = { .reg32 = value };
    const hwlock0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock0:1", "", 1, old_value_t.hwlock0, new_value_t.hwlock0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n HWLOCK REGISTERS\nHardware lock registers.  These registers are general-purpose and allow software to do an atomic operation to gain ownership of a resource.  These registers read back '1' if the reader has obtained ownership and '0' if they have not. This is done by initializing the register to '1'.  The act of reading it resets it to '0'.  Software must then write '1' back to it when it no longer needs the resource.";
}

#define HWLOCK1_OFFSET 0x284
#define HWLOCK1_UNDEFMASK 0xFFFFFFFE
union hwlock1_u {
    struct {
        unsigned int hwlock1:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock1_u old_value_t = { .reg32 = value };
    const hwlock1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock1:1", "", 1, old_value_t.hwlock1, new_value_t.hwlock1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define HWLOCK2_OFFSET 0x288
#define HWLOCK2_UNDEFMASK 0xFFFFFFFE
union hwlock2_u {
    struct {
        unsigned int hwlock2:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock2_u old_value_t = { .reg32 = value };
    const hwlock2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock2:1", "", 1, old_value_t.hwlock2, new_value_t.hwlock2 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define HWLOCK3_OFFSET 0x28C
#define HWLOCK3_UNDEFMASK 0xFFFFFFFE
union hwlock3_u {
    struct {
        unsigned int hwlock3:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock3_u old_value_t = { .reg32 = value };
    const hwlock3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock3:1", "", 1, old_value_t.hwlock3, new_value_t.hwlock3 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define HWLOCK4_OFFSET 0x290
#define HWLOCK4_UNDEFMASK 0xFFFFFFFE
union hwlock4_u {
    struct {
        unsigned int hwlock4:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock4_u old_value_t = { .reg32 = value };
    const hwlock4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock4:1", "", 1, old_value_t.hwlock4, new_value_t.hwlock4 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define HWLOCK5_OFFSET 0x294
#define HWLOCK5_UNDEFMASK 0xFFFFFFFE
union hwlock5_u {
    struct {
        unsigned int hwlock5:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock5_u old_value_t = { .reg32 = value };
    const hwlock5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock5:1", "", 1, old_value_t.hwlock5, new_value_t.hwlock5 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define HWLOCK6_OFFSET 0x298
#define HWLOCK6_UNDEFMASK 0xFFFFFFFE
union hwlock6_u {
    struct {
        unsigned int hwlock6:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock6_u old_value_t = { .reg32 = value };
    const hwlock6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock6:1", "", 1, old_value_t.hwlock6, new_value_t.hwlock6 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define HWLOCK7_OFFSET 0x29C
#define HWLOCK7_UNDEFMASK 0xFFFFFFFE
union hwlock7_u {
    struct {
        unsigned int hwlock7:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_hwlock7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hwlock7_u old_value_t = { .reg32 = value };
    const hwlock7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hwlock7:1", "", 1, old_value_t.hwlock7, new_value_t.hwlock7 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OFFSET 0x2C0
#define MLOCK_UNDEFMASK 0xFFFFFFFE
union mlock_u {
    struct {
        unsigned int mlock_0:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_u old_value_t = { .reg32 = value };
    const mlock_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_0:1", "", 1, old_value_t.mlock_0, new_value_t.mlock_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n MLOCK REGISTERS\nMLOCK is 1 whenever someone holds the lock, and is 0 otherwise. MLOCK is normally set and cleared using the host methods ACQUIRE_MLOCK and RELEASE_MLOCK. If a CPU wants to acquire a lock, then it reads this register, and if the value returned is zero, it has successfully acquired the MLOCK.  A return value of 1 indicates that the acquire failed. At any time, the CPU can write 0 to MLOCK, releasing the MLOCK (note that HW does not check if the CPU owned the lock). If the CPU writes 1 to MLOCK, this is undefined and is ignored by the hardware (a nop). Use MLOCK_OWNER to read the status of a lock (since reading MLOCK itself has a side effect).";
}

#define MLOCK_1_OFFSET 0x2C4
#define MLOCK_1_UNDEFMASK 0xFFFFFFFE
union mlock_1_u {
    struct {
        unsigned int mlock_1:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_1_u old_value_t = { .reg32 = value };
    const mlock_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_1:1", "", 1, old_value_t.mlock_1, new_value_t.mlock_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_2_OFFSET 0x2C8
#define MLOCK_2_UNDEFMASK 0xFFFFFFFE
union mlock_2_u {
    struct {
        unsigned int mlock_2:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_2_u old_value_t = { .reg32 = value };
    const mlock_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_2:1", "", 1, old_value_t.mlock_2, new_value_t.mlock_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_3_OFFSET 0x2CC
#define MLOCK_3_UNDEFMASK 0xFFFFFFFE
union mlock_3_u {
    struct {
        unsigned int mlock_3:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_3_u old_value_t = { .reg32 = value };
    const mlock_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_3:1", "", 1, old_value_t.mlock_3, new_value_t.mlock_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_4_OFFSET 0x2D0
#define MLOCK_4_UNDEFMASK 0xFFFFFFFE
union mlock_4_u {
    struct {
        unsigned int mlock_4:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_4_u old_value_t = { .reg32 = value };
    const mlock_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_4:1", "", 1, old_value_t.mlock_4, new_value_t.mlock_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_5_OFFSET 0x2D4
#define MLOCK_5_UNDEFMASK 0xFFFFFFFE
union mlock_5_u {
    struct {
        unsigned int mlock_5:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_5_u old_value_t = { .reg32 = value };
    const mlock_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_5:1", "", 1, old_value_t.mlock_5, new_value_t.mlock_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_6_OFFSET 0x2D8
#define MLOCK_6_UNDEFMASK 0xFFFFFFFE
union mlock_6_u {
    struct {
        unsigned int mlock_6:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_6_u old_value_t = { .reg32 = value };
    const mlock_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_6:1", "", 1, old_value_t.mlock_6, new_value_t.mlock_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_7_OFFSET 0x2DC
#define MLOCK_7_UNDEFMASK 0xFFFFFFFE
union mlock_7_u {
    struct {
        unsigned int mlock_7:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_7_u old_value_t = { .reg32 = value };
    const mlock_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_7:1", "", 1, old_value_t.mlock_7, new_value_t.mlock_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_8_OFFSET 0x2E0
#define MLOCK_8_UNDEFMASK 0xFFFFFFFE
union mlock_8_u {
    struct {
        unsigned int mlock_8:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_8_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_8_u old_value_t = { .reg32 = value };
    const mlock_8_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_8:1", "", 1, old_value_t.mlock_8, new_value_t.mlock_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_9_OFFSET 0x2E4
#define MLOCK_9_UNDEFMASK 0xFFFFFFFE
union mlock_9_u {
    struct {
        unsigned int mlock_9:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_9_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_9_u old_value_t = { .reg32 = value };
    const mlock_9_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_9:1", "", 1, old_value_t.mlock_9, new_value_t.mlock_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_10_OFFSET 0x2E8
#define MLOCK_10_UNDEFMASK 0xFFFFFFFE
union mlock_10_u {
    struct {
        unsigned int mlock_10:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_10_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_10_u old_value_t = { .reg32 = value };
    const mlock_10_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_10:1", "", 1, old_value_t.mlock_10, new_value_t.mlock_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_11_OFFSET 0x2EC
#define MLOCK_11_UNDEFMASK 0xFFFFFFFE
union mlock_11_u {
    struct {
        unsigned int mlock_11:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_11_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_11_u old_value_t = { .reg32 = value };
    const mlock_11_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_11:1", "", 1, old_value_t.mlock_11, new_value_t.mlock_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_12_OFFSET 0x2F0
#define MLOCK_12_UNDEFMASK 0xFFFFFFFE
union mlock_12_u {
    struct {
        unsigned int mlock_12:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_12_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_12_u old_value_t = { .reg32 = value };
    const mlock_12_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_12:1", "", 1, old_value_t.mlock_12, new_value_t.mlock_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_13_OFFSET 0x2F4
#define MLOCK_13_UNDEFMASK 0xFFFFFFFE
union mlock_13_u {
    struct {
        unsigned int mlock_13:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_13_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_13_u old_value_t = { .reg32 = value };
    const mlock_13_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_13:1", "", 1, old_value_t.mlock_13, new_value_t.mlock_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_14_OFFSET 0x2F8
#define MLOCK_14_UNDEFMASK 0xFFFFFFFE
union mlock_14_u {
    struct {
        unsigned int mlock_14:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_14_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_14_u old_value_t = { .reg32 = value };
    const mlock_14_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_14:1", "", 1, old_value_t.mlock_14, new_value_t.mlock_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_15_OFFSET 0x2FC
#define MLOCK_15_UNDEFMASK 0xFFFFFFFE
union mlock_15_u {
    struct {
        unsigned int mlock_15:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_15_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_15_u old_value_t = { .reg32 = value };
    const mlock_15_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_15:1", "", 1, old_value_t.mlock_15, new_value_t.mlock_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_OFFSET 0x340
#define MLOCK_OWNER_UNDEFMASK 0xFFFFF0FC
union mlock_owner_u {
    struct {
        unsigned int mlock_ch_owns_0:1;
        unsigned int mlock_cpu_owns_0:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_0:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_u old_value_t = { .reg32 = value };
    const mlock_owner_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_0:1", "", 1, old_value_t.mlock_ch_owns_0, new_value_t.mlock_ch_owns_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_0:1", "", 1, old_value_t.mlock_cpu_owns_0, new_value_t.mlock_cpu_owns_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_0:4", "", 4, old_value_t.mlock_owner_chid_0, new_value_t.mlock_owner_chid_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "MLOCK_OWNER is a read-only status for MLOCK. When MLOCK_*_OWNS are all zero, it indicates that the MLOCK is free (zero). When MLOCK has been acquired (set), then one of MLOCK_*_OWNS will be non-zero. Either bit 0 or 1 will be set -- indicating whether a channel or a CPU has acquired the MLOCK.  If a channel owns the MLOCK, then the channel number is given by the MLOCK_OWNER_CHID field.";
}

#define MLOCK_OWNER_1_OFFSET 0x344
#define MLOCK_OWNER_1_UNDEFMASK 0xFFFFF0FC
union mlock_owner_1_u {
    struct {
        unsigned int mlock_ch_owns_1:1;
        unsigned int mlock_cpu_owns_1:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_1:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_1_u old_value_t = { .reg32 = value };
    const mlock_owner_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_1:1", "", 1, old_value_t.mlock_ch_owns_1, new_value_t.mlock_ch_owns_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_1:1", "", 1, old_value_t.mlock_cpu_owns_1, new_value_t.mlock_cpu_owns_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_1:4", "", 4, old_value_t.mlock_owner_chid_1, new_value_t.mlock_owner_chid_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_2_OFFSET 0x348
#define MLOCK_OWNER_2_UNDEFMASK 0xFFFFF0FC
union mlock_owner_2_u {
    struct {
        unsigned int mlock_ch_owns_2:1;
        unsigned int mlock_cpu_owns_2:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_2:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_2_u old_value_t = { .reg32 = value };
    const mlock_owner_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_2:1", "", 1, old_value_t.mlock_ch_owns_2, new_value_t.mlock_ch_owns_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_2:1", "", 1, old_value_t.mlock_cpu_owns_2, new_value_t.mlock_cpu_owns_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_2:4", "", 4, old_value_t.mlock_owner_chid_2, new_value_t.mlock_owner_chid_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_3_OFFSET 0x34C
#define MLOCK_OWNER_3_UNDEFMASK 0xFFFFF0FC
union mlock_owner_3_u {
    struct {
        unsigned int mlock_ch_owns_3:1;
        unsigned int mlock_cpu_owns_3:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_3:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_3_u old_value_t = { .reg32 = value };
    const mlock_owner_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_3:1", "", 1, old_value_t.mlock_ch_owns_3, new_value_t.mlock_ch_owns_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_3:1", "", 1, old_value_t.mlock_cpu_owns_3, new_value_t.mlock_cpu_owns_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_3:4", "", 4, old_value_t.mlock_owner_chid_3, new_value_t.mlock_owner_chid_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_4_OFFSET 0x350
#define MLOCK_OWNER_4_UNDEFMASK 0xFFFFF0FC
union mlock_owner_4_u {
    struct {
        unsigned int mlock_ch_owns_4:1;
        unsigned int mlock_cpu_owns_4:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_4:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_4_u old_value_t = { .reg32 = value };
    const mlock_owner_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_4:1", "", 1, old_value_t.mlock_ch_owns_4, new_value_t.mlock_ch_owns_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_4:1", "", 1, old_value_t.mlock_cpu_owns_4, new_value_t.mlock_cpu_owns_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_4:4", "", 4, old_value_t.mlock_owner_chid_4, new_value_t.mlock_owner_chid_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_5_OFFSET 0x354
#define MLOCK_OWNER_5_UNDEFMASK 0xFFFFF0FC
union mlock_owner_5_u {
    struct {
        unsigned int mlock_ch_owns_5:1;
        unsigned int mlock_cpu_owns_5:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_5:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_5_u old_value_t = { .reg32 = value };
    const mlock_owner_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_5:1", "", 1, old_value_t.mlock_ch_owns_5, new_value_t.mlock_ch_owns_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_5:1", "", 1, old_value_t.mlock_cpu_owns_5, new_value_t.mlock_cpu_owns_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_5:4", "", 4, old_value_t.mlock_owner_chid_5, new_value_t.mlock_owner_chid_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_6_OFFSET 0x358
#define MLOCK_OWNER_6_UNDEFMASK 0xFFFFF0FC
union mlock_owner_6_u {
    struct {
        unsigned int mlock_ch_owns_6:1;
        unsigned int mlock_cpu_owns_6:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_6:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_6_u old_value_t = { .reg32 = value };
    const mlock_owner_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_6:1", "", 1, old_value_t.mlock_ch_owns_6, new_value_t.mlock_ch_owns_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_6:1", "", 1, old_value_t.mlock_cpu_owns_6, new_value_t.mlock_cpu_owns_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_6:4", "", 4, old_value_t.mlock_owner_chid_6, new_value_t.mlock_owner_chid_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_7_OFFSET 0x35C
#define MLOCK_OWNER_7_UNDEFMASK 0xFFFFF0FC
union mlock_owner_7_u {
    struct {
        unsigned int mlock_ch_owns_7:1;
        unsigned int mlock_cpu_owns_7:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_7:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_7_u old_value_t = { .reg32 = value };
    const mlock_owner_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_7:1", "", 1, old_value_t.mlock_ch_owns_7, new_value_t.mlock_ch_owns_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_7:1", "", 1, old_value_t.mlock_cpu_owns_7, new_value_t.mlock_cpu_owns_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_7:4", "", 4, old_value_t.mlock_owner_chid_7, new_value_t.mlock_owner_chid_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_8_OFFSET 0x360
#define MLOCK_OWNER_8_UNDEFMASK 0xFFFFF0FC
union mlock_owner_8_u {
    struct {
        unsigned int mlock_ch_owns_8:1;
        unsigned int mlock_cpu_owns_8:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_8:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_8_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_8_u old_value_t = { .reg32 = value };
    const mlock_owner_8_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_8:1", "", 1, old_value_t.mlock_ch_owns_8, new_value_t.mlock_ch_owns_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_8:1", "", 1, old_value_t.mlock_cpu_owns_8, new_value_t.mlock_cpu_owns_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_8:4", "", 4, old_value_t.mlock_owner_chid_8, new_value_t.mlock_owner_chid_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_9_OFFSET 0x364
#define MLOCK_OWNER_9_UNDEFMASK 0xFFFFF0FC
union mlock_owner_9_u {
    struct {
        unsigned int mlock_ch_owns_9:1;
        unsigned int mlock_cpu_owns_9:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_9:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_9_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_9_u old_value_t = { .reg32 = value };
    const mlock_owner_9_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_9:1", "", 1, old_value_t.mlock_ch_owns_9, new_value_t.mlock_ch_owns_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_9:1", "", 1, old_value_t.mlock_cpu_owns_9, new_value_t.mlock_cpu_owns_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_9:4", "", 4, old_value_t.mlock_owner_chid_9, new_value_t.mlock_owner_chid_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_10_OFFSET 0x368
#define MLOCK_OWNER_10_UNDEFMASK 0xFFFFF0FC
union mlock_owner_10_u {
    struct {
        unsigned int mlock_ch_owns_10:1;
        unsigned int mlock_cpu_owns_10:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_10:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_10_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_10_u old_value_t = { .reg32 = value };
    const mlock_owner_10_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_10:1", "", 1, old_value_t.mlock_ch_owns_10, new_value_t.mlock_ch_owns_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_10:1", "", 1, old_value_t.mlock_cpu_owns_10, new_value_t.mlock_cpu_owns_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_10:4", "", 4, old_value_t.mlock_owner_chid_10, new_value_t.mlock_owner_chid_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_11_OFFSET 0x36C
#define MLOCK_OWNER_11_UNDEFMASK 0xFFFFF0FC
union mlock_owner_11_u {
    struct {
        unsigned int mlock_ch_owns_11:1;
        unsigned int mlock_cpu_owns_11:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_11:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_11_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_11_u old_value_t = { .reg32 = value };
    const mlock_owner_11_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_11:1", "", 1, old_value_t.mlock_ch_owns_11, new_value_t.mlock_ch_owns_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_11:1", "", 1, old_value_t.mlock_cpu_owns_11, new_value_t.mlock_cpu_owns_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_11:4", "", 4, old_value_t.mlock_owner_chid_11, new_value_t.mlock_owner_chid_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_12_OFFSET 0x370
#define MLOCK_OWNER_12_UNDEFMASK 0xFFFFF0FC
union mlock_owner_12_u {
    struct {
        unsigned int mlock_ch_owns_12:1;
        unsigned int mlock_cpu_owns_12:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_12:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_12_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_12_u old_value_t = { .reg32 = value };
    const mlock_owner_12_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_12:1", "", 1, old_value_t.mlock_ch_owns_12, new_value_t.mlock_ch_owns_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_12:1", "", 1, old_value_t.mlock_cpu_owns_12, new_value_t.mlock_cpu_owns_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_12:4", "", 4, old_value_t.mlock_owner_chid_12, new_value_t.mlock_owner_chid_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_13_OFFSET 0x374
#define MLOCK_OWNER_13_UNDEFMASK 0xFFFFF0FC
union mlock_owner_13_u {
    struct {
        unsigned int mlock_ch_owns_13:1;
        unsigned int mlock_cpu_owns_13:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_13:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_13_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_13_u old_value_t = { .reg32 = value };
    const mlock_owner_13_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_13:1", "", 1, old_value_t.mlock_ch_owns_13, new_value_t.mlock_ch_owns_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_13:1", "", 1, old_value_t.mlock_cpu_owns_13, new_value_t.mlock_cpu_owns_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_13:4", "", 4, old_value_t.mlock_owner_chid_13, new_value_t.mlock_owner_chid_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_14_OFFSET 0x378
#define MLOCK_OWNER_14_UNDEFMASK 0xFFFFF0FC
union mlock_owner_14_u {
    struct {
        unsigned int mlock_ch_owns_14:1;
        unsigned int mlock_cpu_owns_14:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_14:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_14_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_14_u old_value_t = { .reg32 = value };
    const mlock_owner_14_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_14:1", "", 1, old_value_t.mlock_ch_owns_14, new_value_t.mlock_ch_owns_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_14:1", "", 1, old_value_t.mlock_cpu_owns_14, new_value_t.mlock_cpu_owns_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_14:4", "", 4, old_value_t.mlock_owner_chid_14, new_value_t.mlock_owner_chid_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_OWNER_15_OFFSET 0x37C
#define MLOCK_OWNER_15_UNDEFMASK 0xFFFFF0FC
union mlock_owner_15_u {
    struct {
        unsigned int mlock_ch_owns_15:1;
        unsigned int mlock_cpu_owns_15:1;
        unsigned int undefined_bits_2_7:6;
        unsigned int mlock_owner_chid_15:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_owner_15_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_owner_15_u old_value_t = { .reg32 = value };
    const mlock_owner_15_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_ch_owns_15:1", "", 1, old_value_t.mlock_ch_owns_15, new_value_t.mlock_ch_owns_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_cpu_owns_15:1", "", 1, old_value_t.mlock_cpu_owns_15, new_value_t.mlock_cpu_owns_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_owner_chid_15:4", "", 4, old_value_t.mlock_owner_chid_15, new_value_t.mlock_owner_chid_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define MLOCK_ERROR_OFFSET 0x3C0
#define MLOCK_ERROR_UNDEFMASK 0xFFFF0000
union mlock_error_u {
    struct {
        unsigned int mlock_error_0:1;
        unsigned int mlock_error_1:1;
        unsigned int mlock_error_2:1;
        unsigned int mlock_error_3:1;
        unsigned int mlock_error_4:1;
        unsigned int mlock_error_5:1;
        unsigned int mlock_error_6:1;
        unsigned int mlock_error_7:1;
        unsigned int mlock_error_8:1;
        unsigned int mlock_error_9:1;
        unsigned int mlock_error_10:1;
        unsigned int mlock_error_11:1;
        unsigned int mlock_error_12:1;
        unsigned int mlock_error_13:1;
        unsigned int mlock_error_14:1;
        unsigned int mlock_error_15:1;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_mlock_error_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mlock_error_u old_value_t = { .reg32 = value };
    const mlock_error_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mlock_error_0:1", "", 1, old_value_t.mlock_error_0, new_value_t.mlock_error_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mlock_error_1:1", "", 1, old_value_t.mlock_error_1, new_value_t.mlock_error_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: mlock_error_2:1", "", 1, old_value_t.mlock_error_2, new_value_t.mlock_error_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: mlock_error_3:1", "", 1, old_value_t.mlock_error_3, new_value_t.mlock_error_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mlock_error_4:1", "", 1, old_value_t.mlock_error_4, new_value_t.mlock_error_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: mlock_error_5:1", "", 1, old_value_t.mlock_error_5, new_value_t.mlock_error_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: mlock_error_6:1", "", 1, old_value_t.mlock_error_6, new_value_t.mlock_error_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mlock_error_7:1", "", 1, old_value_t.mlock_error_7, new_value_t.mlock_error_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mlock_error_8:1", "", 1, old_value_t.mlock_error_8, new_value_t.mlock_error_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: mlock_error_9:1", "", 1, old_value_t.mlock_error_9, new_value_t.mlock_error_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: mlock_error_10:1", "", 1, old_value_t.mlock_error_10, new_value_t.mlock_error_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mlock_error_11:1", "", 1, old_value_t.mlock_error_11, new_value_t.mlock_error_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: mlock_error_12:1", "", 1, old_value_t.mlock_error_12, new_value_t.mlock_error_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mlock_error_13:1", "", 1, old_value_t.mlock_error_13, new_value_t.mlock_error_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: mlock_error_14:1", "", 1, old_value_t.mlock_error_14, new_value_t.mlock_error_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: mlock_error_15:1", "", 1, old_value_t.mlock_error_15, new_value_t.mlock_error_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "If a channel attempts to release an MLOCK that it does not own, then the release has no effect on MLOCK, but the corresponding error bit is set (this includes releasing an MLOCK owned by no-one).";
}

#define SYNCPT_OFFSET 0x400
#define SYNCPT_UNDEFMASK 0x00000000
union syncpt_u {
    struct {
        unsigned int syncpt_0:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_u old_value_t = { .reg32 = value };
    const syncpt_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_0:32", "", 32, old_value_t.syncpt_0, new_value_t.syncpt_0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n SYNCPT REGISTERS\nAlthough the CPU can read and write these registers, typically they are modified and compared using increment syncpt client methods and wait syncpt host methods";
}

#define SYNCPT_1_OFFSET 0x404
#define SYNCPT_1_UNDEFMASK 0x00000000
union syncpt_1_u {
    struct {
        unsigned int syncpt_1:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_1_u old_value_t = { .reg32 = value };
    const syncpt_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_1:32", "", 32, old_value_t.syncpt_1, new_value_t.syncpt_1 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_2_OFFSET 0x408
#define SYNCPT_2_UNDEFMASK 0x00000000
union syncpt_2_u {
    struct {
        unsigned int syncpt_2:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_2_u old_value_t = { .reg32 = value };
    const syncpt_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_2:32", "", 32, old_value_t.syncpt_2, new_value_t.syncpt_2 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_3_OFFSET 0x40C
#define SYNCPT_3_UNDEFMASK 0x00000000
union syncpt_3_u {
    struct {
        unsigned int syncpt_3:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_3_u old_value_t = { .reg32 = value };
    const syncpt_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_3:32", "", 32, old_value_t.syncpt_3, new_value_t.syncpt_3 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_4_OFFSET 0x410
#define SYNCPT_4_UNDEFMASK 0x00000000
union syncpt_4_u {
    struct {
        unsigned int syncpt_4:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_4_u old_value_t = { .reg32 = value };
    const syncpt_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_4:32", "", 32, old_value_t.syncpt_4, new_value_t.syncpt_4 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_5_OFFSET 0x414
#define SYNCPT_5_UNDEFMASK 0x00000000
union syncpt_5_u {
    struct {
        unsigned int syncpt_5:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_5_u old_value_t = { .reg32 = value };
    const syncpt_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_5:32", "", 32, old_value_t.syncpt_5, new_value_t.syncpt_5 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_6_OFFSET 0x418
#define SYNCPT_6_UNDEFMASK 0x00000000
union syncpt_6_u {
    struct {
        unsigned int syncpt_6:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_6_u old_value_t = { .reg32 = value };
    const syncpt_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_6:32", "", 32, old_value_t.syncpt_6, new_value_t.syncpt_6 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_7_OFFSET 0x41C
#define SYNCPT_7_UNDEFMASK 0x00000000
union syncpt_7_u {
    struct {
        unsigned int syncpt_7:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_7_u old_value_t = { .reg32 = value };
    const syncpt_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_7:32", "", 32, old_value_t.syncpt_7, new_value_t.syncpt_7 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_8_OFFSET 0x420
#define SYNCPT_8_UNDEFMASK 0x00000000
union syncpt_8_u {
    struct {
        unsigned int syncpt_8:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_8_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_8_u old_value_t = { .reg32 = value };
    const syncpt_8_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_8:32", "", 32, old_value_t.syncpt_8, new_value_t.syncpt_8 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_9_OFFSET 0x424
#define SYNCPT_9_UNDEFMASK 0x00000000
union syncpt_9_u {
    struct {
        unsigned int syncpt_9:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_9_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_9_u old_value_t = { .reg32 = value };
    const syncpt_9_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_9:32", "", 32, old_value_t.syncpt_9, new_value_t.syncpt_9 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_10_OFFSET 0x428
#define SYNCPT_10_UNDEFMASK 0x00000000
union syncpt_10_u {
    struct {
        unsigned int syncpt_10:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_10_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_10_u old_value_t = { .reg32 = value };
    const syncpt_10_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_10:32", "", 32, old_value_t.syncpt_10, new_value_t.syncpt_10 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_11_OFFSET 0x42C
#define SYNCPT_11_UNDEFMASK 0x00000000
union syncpt_11_u {
    struct {
        unsigned int syncpt_11:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_11_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_11_u old_value_t = { .reg32 = value };
    const syncpt_11_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_11:32", "", 32, old_value_t.syncpt_11, new_value_t.syncpt_11 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_12_OFFSET 0x430
#define SYNCPT_12_UNDEFMASK 0x00000000
union syncpt_12_u {
    struct {
        unsigned int syncpt_12:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_12_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_12_u old_value_t = { .reg32 = value };
    const syncpt_12_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_12:32", "", 32, old_value_t.syncpt_12, new_value_t.syncpt_12 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_13_OFFSET 0x434
#define SYNCPT_13_UNDEFMASK 0x00000000
union syncpt_13_u {
    struct {
        unsigned int syncpt_13:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_13_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_13_u old_value_t = { .reg32 = value };
    const syncpt_13_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_13:32", "", 32, old_value_t.syncpt_13, new_value_t.syncpt_13 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_14_OFFSET 0x438
#define SYNCPT_14_UNDEFMASK 0x00000000
union syncpt_14_u {
    struct {
        unsigned int syncpt_14:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_14_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_14_u old_value_t = { .reg32 = value };
    const syncpt_14_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_14:32", "", 32, old_value_t.syncpt_14, new_value_t.syncpt_14 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_15_OFFSET 0x43C
#define SYNCPT_15_UNDEFMASK 0x00000000
union syncpt_15_u {
    struct {
        unsigned int syncpt_15:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_15_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_15_u old_value_t = { .reg32 = value };
    const syncpt_15_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_15:32", "", 32, old_value_t.syncpt_15, new_value_t.syncpt_15 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_16_OFFSET 0x440
#define SYNCPT_16_UNDEFMASK 0x00000000
union syncpt_16_u {
    struct {
        unsigned int syncpt_16:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_16_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_16_u old_value_t = { .reg32 = value };
    const syncpt_16_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_16:32", "", 32, old_value_t.syncpt_16, new_value_t.syncpt_16 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_17_OFFSET 0x444
#define SYNCPT_17_UNDEFMASK 0x00000000
union syncpt_17_u {
    struct {
        unsigned int syncpt_17:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_17_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_17_u old_value_t = { .reg32 = value };
    const syncpt_17_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_17:32", "", 32, old_value_t.syncpt_17, new_value_t.syncpt_17 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_18_OFFSET 0x448
#define SYNCPT_18_UNDEFMASK 0x00000000
union syncpt_18_u {
    struct {
        unsigned int syncpt_18:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_18_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_18_u old_value_t = { .reg32 = value };
    const syncpt_18_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_18:32", "", 32, old_value_t.syncpt_18, new_value_t.syncpt_18 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_19_OFFSET 0x44C
#define SYNCPT_19_UNDEFMASK 0x00000000
union syncpt_19_u {
    struct {
        unsigned int syncpt_19:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_19_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_19_u old_value_t = { .reg32 = value };
    const syncpt_19_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_19:32", "", 32, old_value_t.syncpt_19, new_value_t.syncpt_19 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_20_OFFSET 0x450
#define SYNCPT_20_UNDEFMASK 0x00000000
union syncpt_20_u {
    struct {
        unsigned int syncpt_20:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_20_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_20_u old_value_t = { .reg32 = value };
    const syncpt_20_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_20:32", "", 32, old_value_t.syncpt_20, new_value_t.syncpt_20 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_21_OFFSET 0x454
#define SYNCPT_21_UNDEFMASK 0x00000000
union syncpt_21_u {
    struct {
        unsigned int syncpt_21:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_21_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_21_u old_value_t = { .reg32 = value };
    const syncpt_21_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_21:32", "", 32, old_value_t.syncpt_21, new_value_t.syncpt_21 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_22_OFFSET 0x458
#define SYNCPT_22_UNDEFMASK 0x00000000
union syncpt_22_u {
    struct {
        unsigned int syncpt_22:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_22_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_22_u old_value_t = { .reg32 = value };
    const syncpt_22_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_22:32", "", 32, old_value_t.syncpt_22, new_value_t.syncpt_22 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_23_OFFSET 0x45C
#define SYNCPT_23_UNDEFMASK 0x00000000
union syncpt_23_u {
    struct {
        unsigned int syncpt_23:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_23_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_23_u old_value_t = { .reg32 = value };
    const syncpt_23_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_23:32", "", 32, old_value_t.syncpt_23, new_value_t.syncpt_23 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_24_OFFSET 0x460
#define SYNCPT_24_UNDEFMASK 0x00000000
union syncpt_24_u {
    struct {
        unsigned int syncpt_24:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_24_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_24_u old_value_t = { .reg32 = value };
    const syncpt_24_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_24:32", "", 32, old_value_t.syncpt_24, new_value_t.syncpt_24 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_25_OFFSET 0x464
#define SYNCPT_25_UNDEFMASK 0x00000000
union syncpt_25_u {
    struct {
        unsigned int syncpt_25:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_25_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_25_u old_value_t = { .reg32 = value };
    const syncpt_25_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_25:32", "", 32, old_value_t.syncpt_25, new_value_t.syncpt_25 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_26_OFFSET 0x468
#define SYNCPT_26_UNDEFMASK 0x00000000
union syncpt_26_u {
    struct {
        unsigned int syncpt_26:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_26_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_26_u old_value_t = { .reg32 = value };
    const syncpt_26_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_26:32", "", 32, old_value_t.syncpt_26, new_value_t.syncpt_26 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_27_OFFSET 0x46C
#define SYNCPT_27_UNDEFMASK 0x00000000
union syncpt_27_u {
    struct {
        unsigned int syncpt_27:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_27_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_27_u old_value_t = { .reg32 = value };
    const syncpt_27_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_27:32", "", 32, old_value_t.syncpt_27, new_value_t.syncpt_27 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_28_OFFSET 0x470
#define SYNCPT_28_UNDEFMASK 0x00000000
union syncpt_28_u {
    struct {
        unsigned int syncpt_28:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_28_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_28_u old_value_t = { .reg32 = value };
    const syncpt_28_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_28:32", "", 32, old_value_t.syncpt_28, new_value_t.syncpt_28 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_29_OFFSET 0x474
#define SYNCPT_29_UNDEFMASK 0x00000000
union syncpt_29_u {
    struct {
        unsigned int syncpt_29:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_29_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_29_u old_value_t = { .reg32 = value };
    const syncpt_29_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_29:32", "", 32, old_value_t.syncpt_29, new_value_t.syncpt_29 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_30_OFFSET 0x478
#define SYNCPT_30_UNDEFMASK 0x00000000
union syncpt_30_u {
    struct {
        unsigned int syncpt_30:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_30_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_30_u old_value_t = { .reg32 = value };
    const syncpt_30_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_30:32", "", 32, old_value_t.syncpt_30, new_value_t.syncpt_30 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_31_OFFSET 0x47C
#define SYNCPT_31_UNDEFMASK 0x00000000
union syncpt_31_u {
    struct {
        unsigned int syncpt_31:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_31_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_31_u old_value_t = { .reg32 = value };
    const syncpt_31_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_31:32", "", 32, old_value_t.syncpt_31, new_value_t.syncpt_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_OFFSET 0x500
#define SYNCPT_INT_THRESH_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_u {
    struct {
        unsigned int int_thresh_0:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_0:16", "", 16, old_value_t.int_thresh_0, new_value_t.int_thresh_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Syncpt interrupt thresholds When a syncpt threshold interrupt is enabled, an interrupt is signaled when (SYNCPT_THRESH_INT_MASK[indx] == cpu) && (SYNCPT[indx] >= SYNCPT_INT_THRESH[indx]) where the comparison takes into account wrapping, and the interrupt is routed to the specified CPU.";
}

#define SYNCPT_INT_THRESH_1_OFFSET 0x504
#define SYNCPT_INT_THRESH_1_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_1_u {
    struct {
        unsigned int int_thresh_1:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_1_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_1:16", "", 16, old_value_t.int_thresh_1, new_value_t.int_thresh_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_2_OFFSET 0x508
#define SYNCPT_INT_THRESH_2_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_2_u {
    struct {
        unsigned int int_thresh_2:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_2_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_2:16", "", 16, old_value_t.int_thresh_2, new_value_t.int_thresh_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_3_OFFSET 0x50C
#define SYNCPT_INT_THRESH_3_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_3_u {
    struct {
        unsigned int int_thresh_3:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_3_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_3:16", "", 16, old_value_t.int_thresh_3, new_value_t.int_thresh_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_4_OFFSET 0x510
#define SYNCPT_INT_THRESH_4_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_4_u {
    struct {
        unsigned int int_thresh_4:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_4_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_4:16", "", 16, old_value_t.int_thresh_4, new_value_t.int_thresh_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_5_OFFSET 0x514
#define SYNCPT_INT_THRESH_5_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_5_u {
    struct {
        unsigned int int_thresh_5:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_5_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_5:16", "", 16, old_value_t.int_thresh_5, new_value_t.int_thresh_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_6_OFFSET 0x518
#define SYNCPT_INT_THRESH_6_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_6_u {
    struct {
        unsigned int int_thresh_6:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_6_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_6:16", "", 16, old_value_t.int_thresh_6, new_value_t.int_thresh_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_7_OFFSET 0x51C
#define SYNCPT_INT_THRESH_7_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_7_u {
    struct {
        unsigned int int_thresh_7:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_7_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_7:16", "", 16, old_value_t.int_thresh_7, new_value_t.int_thresh_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_8_OFFSET 0x520
#define SYNCPT_INT_THRESH_8_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_8_u {
    struct {
        unsigned int int_thresh_8:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_8_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_8_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_8_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_8:16", "", 16, old_value_t.int_thresh_8, new_value_t.int_thresh_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_9_OFFSET 0x524
#define SYNCPT_INT_THRESH_9_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_9_u {
    struct {
        unsigned int int_thresh_9:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_9_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_9_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_9_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_9:16", "", 16, old_value_t.int_thresh_9, new_value_t.int_thresh_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_10_OFFSET 0x528
#define SYNCPT_INT_THRESH_10_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_10_u {
    struct {
        unsigned int int_thresh_10:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_10_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_10_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_10_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_10:16", "", 16, old_value_t.int_thresh_10, new_value_t.int_thresh_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_11_OFFSET 0x52C
#define SYNCPT_INT_THRESH_11_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_11_u {
    struct {
        unsigned int int_thresh_11:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_11_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_11_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_11_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_11:16", "", 16, old_value_t.int_thresh_11, new_value_t.int_thresh_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_12_OFFSET 0x530
#define SYNCPT_INT_THRESH_12_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_12_u {
    struct {
        unsigned int int_thresh_12:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_12_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_12_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_12_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_12:16", "", 16, old_value_t.int_thresh_12, new_value_t.int_thresh_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_13_OFFSET 0x534
#define SYNCPT_INT_THRESH_13_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_13_u {
    struct {
        unsigned int int_thresh_13:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_13_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_13_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_13_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_13:16", "", 16, old_value_t.int_thresh_13, new_value_t.int_thresh_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_14_OFFSET 0x538
#define SYNCPT_INT_THRESH_14_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_14_u {
    struct {
        unsigned int int_thresh_14:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_14_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_14_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_14_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_14:16", "", 16, old_value_t.int_thresh_14, new_value_t.int_thresh_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_15_OFFSET 0x53C
#define SYNCPT_INT_THRESH_15_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_15_u {
    struct {
        unsigned int int_thresh_15:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_15_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_15_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_15_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_15:16", "", 16, old_value_t.int_thresh_15, new_value_t.int_thresh_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_16_OFFSET 0x540
#define SYNCPT_INT_THRESH_16_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_16_u {
    struct {
        unsigned int int_thresh_16:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_16_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_16_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_16_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_16:16", "", 16, old_value_t.int_thresh_16, new_value_t.int_thresh_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_17_OFFSET 0x544
#define SYNCPT_INT_THRESH_17_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_17_u {
    struct {
        unsigned int int_thresh_17:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_17_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_17_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_17_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_17:16", "", 16, old_value_t.int_thresh_17, new_value_t.int_thresh_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_18_OFFSET 0x548
#define SYNCPT_INT_THRESH_18_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_18_u {
    struct {
        unsigned int int_thresh_18:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_18_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_18_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_18_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_18:16", "", 16, old_value_t.int_thresh_18, new_value_t.int_thresh_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_19_OFFSET 0x54C
#define SYNCPT_INT_THRESH_19_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_19_u {
    struct {
        unsigned int int_thresh_19:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_19_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_19_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_19_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_19:16", "", 16, old_value_t.int_thresh_19, new_value_t.int_thresh_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_20_OFFSET 0x550
#define SYNCPT_INT_THRESH_20_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_20_u {
    struct {
        unsigned int int_thresh_20:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_20_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_20_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_20_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_20:16", "", 16, old_value_t.int_thresh_20, new_value_t.int_thresh_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_21_OFFSET 0x554
#define SYNCPT_INT_THRESH_21_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_21_u {
    struct {
        unsigned int int_thresh_21:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_21_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_21_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_21_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_21:16", "", 16, old_value_t.int_thresh_21, new_value_t.int_thresh_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_22_OFFSET 0x558
#define SYNCPT_INT_THRESH_22_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_22_u {
    struct {
        unsigned int int_thresh_22:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_22_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_22_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_22_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_22:16", "", 16, old_value_t.int_thresh_22, new_value_t.int_thresh_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_23_OFFSET 0x55C
#define SYNCPT_INT_THRESH_23_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_23_u {
    struct {
        unsigned int int_thresh_23:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_23_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_23_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_23_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_23:16", "", 16, old_value_t.int_thresh_23, new_value_t.int_thresh_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_24_OFFSET 0x560
#define SYNCPT_INT_THRESH_24_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_24_u {
    struct {
        unsigned int int_thresh_24:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_24_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_24_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_24_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_24:16", "", 16, old_value_t.int_thresh_24, new_value_t.int_thresh_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_25_OFFSET 0x564
#define SYNCPT_INT_THRESH_25_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_25_u {
    struct {
        unsigned int int_thresh_25:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_25_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_25_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_25_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_25:16", "", 16, old_value_t.int_thresh_25, new_value_t.int_thresh_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_26_OFFSET 0x568
#define SYNCPT_INT_THRESH_26_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_26_u {
    struct {
        unsigned int int_thresh_26:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_26_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_26_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_26_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_26:16", "", 16, old_value_t.int_thresh_26, new_value_t.int_thresh_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_27_OFFSET 0x56C
#define SYNCPT_INT_THRESH_27_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_27_u {
    struct {
        unsigned int int_thresh_27:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_27_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_27_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_27_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_27:16", "", 16, old_value_t.int_thresh_27, new_value_t.int_thresh_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_28_OFFSET 0x570
#define SYNCPT_INT_THRESH_28_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_28_u {
    struct {
        unsigned int int_thresh_28:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_28_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_28_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_28_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_28:16", "", 16, old_value_t.int_thresh_28, new_value_t.int_thresh_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_29_OFFSET 0x574
#define SYNCPT_INT_THRESH_29_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_29_u {
    struct {
        unsigned int int_thresh_29:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_29_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_29_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_29_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_29:16", "", 16, old_value_t.int_thresh_29, new_value_t.int_thresh_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_30_OFFSET 0x578
#define SYNCPT_INT_THRESH_30_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_30_u {
    struct {
        unsigned int int_thresh_30:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_30_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_30_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_30_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_30:16", "", 16, old_value_t.int_thresh_30, new_value_t.int_thresh_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_INT_THRESH_31_OFFSET 0x57C
#define SYNCPT_INT_THRESH_31_UNDEFMASK 0xFFFF0000
union syncpt_int_thresh_31_u {
    struct {
        unsigned int int_thresh_31:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_int_thresh_31_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_int_thresh_31_u old_value_t = { .reg32 = value };
    const syncpt_int_thresh_31_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: int_thresh_31:16", "", 16, old_value_t.int_thresh_31, new_value_t.int_thresh_31 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_OFFSET 0x600
#define SYNCPT_BASE_UNDEFMASK 0xFFFF0000
union syncpt_base_u {
    struct {
        unsigned int base_0:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_u old_value_t = { .reg32 = value };
    const syncpt_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_0:16", "", 16, old_value_t.base_0, new_value_t.base_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Syncpt base registers are used by wait_syncpt_base method.  The wait will be released when SYNCPT[indx] >= (BASE[base_indx] + offset) where indx, base_indx, and offset are supplied by the wait method.";
}

#define SYNCPT_BASE_1_OFFSET 0x604
#define SYNCPT_BASE_1_UNDEFMASK 0xFFFF0000
union syncpt_base_1_u {
    struct {
        unsigned int base_1:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_1_u old_value_t = { .reg32 = value };
    const syncpt_base_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_1:16", "", 16, old_value_t.base_1, new_value_t.base_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_2_OFFSET 0x608
#define SYNCPT_BASE_2_UNDEFMASK 0xFFFF0000
union syncpt_base_2_u {
    struct {
        unsigned int base_2:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_2_u old_value_t = { .reg32 = value };
    const syncpt_base_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_2:16", "", 16, old_value_t.base_2, new_value_t.base_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_3_OFFSET 0x60C
#define SYNCPT_BASE_3_UNDEFMASK 0xFFFF0000
union syncpt_base_3_u {
    struct {
        unsigned int base_3:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_3_u old_value_t = { .reg32 = value };
    const syncpt_base_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_3:16", "", 16, old_value_t.base_3, new_value_t.base_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_4_OFFSET 0x610
#define SYNCPT_BASE_4_UNDEFMASK 0xFFFF0000
union syncpt_base_4_u {
    struct {
        unsigned int base_4:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_4_u old_value_t = { .reg32 = value };
    const syncpt_base_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_4:16", "", 16, old_value_t.base_4, new_value_t.base_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_5_OFFSET 0x614
#define SYNCPT_BASE_5_UNDEFMASK 0xFFFF0000
union syncpt_base_5_u {
    struct {
        unsigned int base_5:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_5_u old_value_t = { .reg32 = value };
    const syncpt_base_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_5:16", "", 16, old_value_t.base_5, new_value_t.base_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_6_OFFSET 0x618
#define SYNCPT_BASE_6_UNDEFMASK 0xFFFF0000
union syncpt_base_6_u {
    struct {
        unsigned int base_6:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_6_u old_value_t = { .reg32 = value };
    const syncpt_base_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_6:16", "", 16, old_value_t.base_6, new_value_t.base_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_BASE_7_OFFSET 0x61C
#define SYNCPT_BASE_7_UNDEFMASK 0xFFFF0000
union syncpt_base_7_u {
    struct {
        unsigned int base_7:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_base_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_base_7_u old_value_t = { .reg32 = value };
    const syncpt_base_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: base_7:16", "", 16, old_value_t.base_7, new_value_t.base_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define SYNCPT_CPU_INCR_OFFSET 0x700
#define SYNCPT_CPU_INCR_UNDEFMASK 0x00000000
union syncpt_cpu_incr_u {
    struct {
        unsigned int syncpt_cpu_incr_vector:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_syncpt_cpu_incr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const syncpt_cpu_incr_u old_value_t = { .reg32 = value };
    const syncpt_cpu_incr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: syncpt_cpu_incr_vector:32", "", 32, old_value_t.syncpt_cpu_incr_vector, new_value_t.syncpt_cpu_incr_vector };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "When a CPU writes the vector to this register, if vector[i] is set, then syncpt[i] is incremented. Read returns undefined value.";
}

#define CBREAD0_OFFSET 0x720
#define CBREAD0_UNDEFMASK 0x00000000
union cbread0_u {
    struct {
        unsigned int cbread0:32;            /* Channel 0 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread0_u old_value_t = { .reg32 = value };
    const cbread0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread0:32",
              "Channel 0 command FIFO read",
              32, old_value_t.cbread0, new_value_t.cbread0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n DEBUG REGISTERS\nCommand buffer debug read.  Will read the bottom of the command FIFO for all channels, including the register FIFO.  Will also display the current class and offset for a particular channel.";
}

#define CBREAD1_OFFSET 0x724
#define CBREAD1_UNDEFMASK 0x00000000
union cbread1_u {
    struct {
        unsigned int cbread1:32;            /* Channel 1 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread1_u old_value_t = { .reg32 = value };
    const cbread1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread1:32",
              "Channel 1 command FIFO read",
              32, old_value_t.cbread1, new_value_t.cbread1 };
    m_bit_details_model.bits.append(entry);
}

#define CBREAD2_OFFSET 0x728
#define CBREAD2_UNDEFMASK 0x00000000
union cbread2_u {
    struct {
        unsigned int cbread2:32;            /* Channel 2 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread2_u old_value_t = { .reg32 = value };
    const cbread2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread2:32",
              "Channel 2 command FIFO read",
              32, old_value_t.cbread2, new_value_t.cbread2 };
    m_bit_details_model.bits.append(entry);
}

#define CBREAD3_OFFSET 0x72C
#define CBREAD3_UNDEFMASK 0x00000000
union cbread3_u {
    struct {
        unsigned int cbread3:32;            /* Channel 3 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread3_u old_value_t = { .reg32 = value };
    const cbread3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread3:32",
              "Channel 3 command FIFO read",
              32, old_value_t.cbread3, new_value_t.cbread3 };
    m_bit_details_model.bits.append(entry);
}

#define CBREAD4_OFFSET 0x730
#define CBREAD4_UNDEFMASK 0x00000000
union cbread4_u {
    struct {
        unsigned int cbread4:32;            /* Channel 4 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread4_u old_value_t = { .reg32 = value };
    const cbread4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread4:32",
              "Channel 4 command FIFO read",
              32, old_value_t.cbread4, new_value_t.cbread4 };
    m_bit_details_model.bits.append(entry);
}

#define CBREAD5_OFFSET 0x734
#define CBREAD5_UNDEFMASK 0x00000000
union cbread5_u {
    struct {
        unsigned int cbread5:32;            /* Channel 5 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread5_u old_value_t = { .reg32 = value };
    const cbread5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread5:32",
              "Channel 5 command FIFO read",
              32, old_value_t.cbread5, new_value_t.cbread5 };
    m_bit_details_model.bits.append(entry);
}

#define CBREAD6_OFFSET 0x738
#define CBREAD6_UNDEFMASK 0x00000000
union cbread6_u {
    struct {
        unsigned int cbread6:32;            /* Channel 6 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread6_u old_value_t = { .reg32 = value };
    const cbread6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread6:32",
              "Channel 6 command FIFO read",
              32, old_value_t.cbread6, new_value_t.cbread6 };
    m_bit_details_model.bits.append(entry);
}

#define CBREAD7_OFFSET 0x73C
#define CBREAD7_UNDEFMASK 0x00000000
union cbread7_u {
    struct {
        unsigned int cbread7:32;            /* Channel 7 command FIFO read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbread7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbread7_u old_value_t = { .reg32 = value };
    const cbread7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cbread7:32",
              "Channel 7 command FIFO read",
              32, old_value_t.cbread7, new_value_t.cbread7 };
    m_bit_details_model.bits.append(entry);
}

#define REGF_DATA_OFFSET 0x740
#define REGF_DATA_UNDEFMASK 0x00000000
union regf_data_u {
    struct {
        unsigned int regf_data:32;          /* Register FIFO data read */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_regf_data_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const regf_data_u old_value_t = { .reg32 = value };
    const regf_data_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: regf_data:32",
              "Register FIFO data read",
              32, old_value_t.regf_data, new_value_t.regf_data };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Register FIFO debug read.  Will read the bottom of the register FIFO, including all offset and control signals.";
}

#define REGF_ADDR_OFFSET 0x744
#define REGF_ADDR_UNDEFMASK 0xE0000000
union regf_addr_u {
    struct {
        unsigned int regf_offset:16;        /* Register FIFO offset read */
        unsigned int regf_be:4;             /* Register FIFO byte enables */
        unsigned int regf_moduleid:8;       /* Register FIFO module ID read 0 = HOST1X 1 = MPE 2 = VI 3 = EPP 4 = ISP 5 = GR2D 6 = GR3D 8 = DISPLAY 11 = TVO 9 = DISPLAYB 12 = DSI 10 = HDMI */
        unsigned int regf_rwn:1;            /* Register FIFO read/write signal read 0 = WRITE 1 = READ */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_regf_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const regf_addr_u old_value_t = { .reg32 = value };
    const regf_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: regf_offset:16",
              "Register FIFO offset read",
              16, old_value_t.regf_offset, new_value_t.regf_offset };
    m_bit_details_model.bits.append(entry);
    entry = { "16: regf_be:4",
              "Register FIFO byte enables",
              4, old_value_t.regf_be, new_value_t.regf_be };
    m_bit_details_model.bits.append(entry);
    entry = { "20: regf_moduleid:8",
              "Register FIFO module ID read\n0 = HOST1X\n1 = MPE\n2 = VI\n3 = EPP\n4 = ISP\n5 = GR2D\n6 = GR3D\n8 = DISPLAY\n11 = TVO\n9 = DISPLAYB\n12 = DSI\n10 = HDMI",
              8, old_value_t.regf_moduleid, new_value_t.regf_moduleid };
    m_bit_details_model.bits.append(entry);
    entry = { "28: regf_rwn:1",
              "Register FIFO read/write signal read\n0 = WRITE\n1 = READ",
              1, old_value_t.regf_rwn, new_value_t.regf_rwn };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);
}

#define WAITOVR_OFFSET 0x748
#define WAITOVR_UNDEFMASK 0xFFFFFF00
union waitovr_u {
    struct {
        unsigned int waitovr0:1;            /* Channel 0 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr1:1;            /* Channel 1 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr2:1;            /* Channel 2 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr3:1;            /* Channel 3 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr4:1;            /* Channel 4 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr5:1;            /* Channel 5 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr6:1;            /* Channel 6 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int waitovr7:1;            /* Channel 7 WAIT override 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_waitovr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const waitovr_u old_value_t = { .reg32 = value };
    const waitovr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: waitovr0:1",
              "Channel 0 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr0, new_value_t.waitovr0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: waitovr1:1",
              "Channel 1 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr1, new_value_t.waitovr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: waitovr2:1",
              "Channel 2 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr2, new_value_t.waitovr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: waitovr3:1",
              "Channel 3 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr3, new_value_t.waitovr3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: waitovr4:1",
              "Channel 4 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr4, new_value_t.waitovr4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: waitovr5:1",
              "Channel 5 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr5, new_value_t.waitovr5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: waitovr6:1",
              "Channel 6 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr6, new_value_t.waitovr6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: waitovr7:1",
              "Channel 7 WAIT override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.waitovr7, new_value_t.waitovr7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Wait override.  When written to '1', steps past a single stuck wait in the command buffer. Needs to be written back to '0' between overrides.";
}

#define CFPEEK_CTRL_OFFSET 0x74C
#define CFPEEK_CTRL_UNDEFMASK 0x7FF8FE00
union cfpeek_ctrl_u {
    struct {
        unsigned int cfpeek_addr:9;
        unsigned int undefined_bits_9_15:7;
        unsigned int cfpeek_channr:3;
        unsigned int undefined_bits_19_30:12;
        unsigned int cfpeek_ena:1;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cfpeek_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfpeek_ctrl_u old_value_t = { .reg32 = value };
    const cfpeek_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfpeek_addr:9", "", 9, old_value_t.cfpeek_addr, new_value_t.cfpeek_addr };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfpeek_channr:3", "", 3, old_value_t.cfpeek_channr, new_value_t.cfpeek_channr };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_30:12", "", 12, old_value_t.undefined_bits_19_30, new_value_t.undefined_bits_19_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: cfpeek_ena:1", "", 1, old_value_t.cfpeek_ena, new_value_t.cfpeek_ena };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Command FIFO debugging register:\nWhen CFPEEK_ENA is asserted, the command FIFO will read the data that is stored at adress CFPEEK_ADDR. The data will be available in CFPEEK_DATA. This gives visibility into all locations of the RAM.Channel related requests to read from the command FIFO RAM are blocked. This effectively freezes the contents of whatever is stored in the command FIFO RAM on the read side. The write side logic (PIO or CDMA) is still allowed to add data to the command FIFO's (until, per channel, the FIFO is full.) If this is undesired, one could first issue a DMASTOP for all CDMA channels.\nThe command FIFO's are implemented with chasing read/write pointers. Since CFPEEK_ADDR is directly connected to the RAM address input, the value at, say, address 0 will not necessarily correspond to the top of a FIFO. The values of read and write pointers into a command FIFO can be found in the CFPEEK_PTRS register. The CFPEEK_CHANNR field selects the channels for which the pointers are shown. The begin and end addresses of a command FIFO can be foudn in the CFx_BASE and CFx_LIMIT registers.";
}

#define CFPEEK_READ_OFFSET 0x750
#define CFPEEK_READ_UNDEFMASK 0x00000000
union cfpeek_read_u {
    struct {
        unsigned int cfpeek_data:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cfpeek_read_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfpeek_read_u old_value_t = { .reg32 = value };
    const cfpeek_read_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfpeek_data:32", "", 32, old_value_t.cfpeek_data, new_value_t.cfpeek_data };
    m_bit_details_model.bits.append(entry);
}

#define CFPEEK_PTRS_OFFSET 0x754
#define CFPEEK_PTRS_UNDEFMASK 0xFE00FE00
union cfpeek_ptrs_u {
    struct {
        unsigned int cf_rd_ptr:9;
        unsigned int undefined_bits_9_15:7;
        unsigned int cf_wr_ptr:9;
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cfpeek_ptrs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfpeek_ptrs_u old_value_t = { .reg32 = value };
    const cfpeek_ptrs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cf_rd_ptr:9", "", 9, old_value_t.cf_rd_ptr, new_value_t.cf_rd_ptr };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cf_wr_ptr:9", "", 9, old_value_t.cf_wr_ptr, new_value_t.cf_wr_ptr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT0_OFFSET 0x758
#define CBSTAT0_UNDEFMASK 0xFC000000
union cbstat0_u {
    struct {
        unsigned int cboffset0:16;          /* Channel 0 command processor current offset */
        unsigned int cbclass0:10;           /* Channel 0 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat0_u old_value_t = { .reg32 = value };
    const cbstat0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset0:16",
              "Channel 0 command processor current offset",
              16, old_value_t.cboffset0, new_value_t.cboffset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass0:10",
              "Channel 0 command processor current class",
              10, old_value_t.cbclass0, new_value_t.cbclass0 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Command buffer debug read. Will read the bottom of the command FIFO for all channels, including the register FIFO. Will also display the current class and offset for a particular channel.";
}

#define CBSTAT1_OFFSET 0x75C
#define CBSTAT1_UNDEFMASK 0xFC000000
union cbstat1_u {
    struct {
        unsigned int cboffset1:16;          /* Channel 1 command processor current offset */
        unsigned int cbclass1:10;           /* Channel 1 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat1_u old_value_t = { .reg32 = value };
    const cbstat1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset1:16",
              "Channel 1 command processor current offset",
              16, old_value_t.cboffset1, new_value_t.cboffset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass1:10",
              "Channel 1 command processor current class",
              10, old_value_t.cbclass1, new_value_t.cbclass1 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT2_OFFSET 0x760
#define CBSTAT2_UNDEFMASK 0xFC000000
union cbstat2_u {
    struct {
        unsigned int cboffset2:16;          /* Channel 2 command processor current offset */
        unsigned int cbclass2:10;           /* Channel 2 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat2_u old_value_t = { .reg32 = value };
    const cbstat2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset2:16",
              "Channel 2 command processor current offset",
              16, old_value_t.cboffset2, new_value_t.cboffset2 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass2:10",
              "Channel 2 command processor current class",
              10, old_value_t.cbclass2, new_value_t.cbclass2 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT3_OFFSET 0x764
#define CBSTAT3_UNDEFMASK 0xFC000000
union cbstat3_u {
    struct {
        unsigned int cboffset3:16;          /* Channel 3 command processor current offset */
        unsigned int cbclass3:10;           /* Channel 3 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat3_u old_value_t = { .reg32 = value };
    const cbstat3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset3:16",
              "Channel 3 command processor current offset",
              16, old_value_t.cboffset3, new_value_t.cboffset3 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass3:10",
              "Channel 3 command processor current class",
              10, old_value_t.cbclass3, new_value_t.cbclass3 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT4_OFFSET 0x768
#define CBSTAT4_UNDEFMASK 0xFC000000
union cbstat4_u {
    struct {
        unsigned int cboffset4:16;          /* Channel 4 command processor current offset */
        unsigned int cbclass4:10;           /* Channel 4 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat4_u old_value_t = { .reg32 = value };
    const cbstat4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset4:16",
              "Channel 4 command processor current offset",
              16, old_value_t.cboffset4, new_value_t.cboffset4 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass4:10",
              "Channel 4 command processor current class",
              10, old_value_t.cbclass4, new_value_t.cbclass4 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT5_OFFSET 0x76C
#define CBSTAT5_UNDEFMASK 0xFC000000
union cbstat5_u {
    struct {
        unsigned int cboffset5:16;          /* Channel 5 command processor current offset */
        unsigned int cbclass5:10;           /* Channel 5 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat5_u old_value_t = { .reg32 = value };
    const cbstat5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset5:16",
              "Channel 5 command processor current offset",
              16, old_value_t.cboffset5, new_value_t.cboffset5 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass5:10",
              "Channel 5 command processor current class",
              10, old_value_t.cbclass5, new_value_t.cbclass5 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT6_OFFSET 0x770
#define CBSTAT6_UNDEFMASK 0xFC000000
union cbstat6_u {
    struct {
        unsigned int cboffset6:16;          /* Channel 6 command processor current offset */
        unsigned int cbclass6:10;           /* Channel 6 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat6_u old_value_t = { .reg32 = value };
    const cbstat6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset6:16",
              "Channel 6 command processor current offset",
              16, old_value_t.cboffset6, new_value_t.cboffset6 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass6:10",
              "Channel 6 command processor current class",
              10, old_value_t.cbclass6, new_value_t.cbclass6 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CBSTAT7_OFFSET 0x774
#define CBSTAT7_UNDEFMASK 0xFC000000
union cbstat7_u {
    struct {
        unsigned int cboffset7:16;          /* Channel 7 command processor current offset */
        unsigned int cbclass7:10;           /* Channel 7 command processor current class */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cbstat7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cbstat7_u old_value_t = { .reg32 = value };
    const cbstat7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cboffset7:16",
              "Channel 7 command processor current offset",
              16, old_value_t.cboffset7, new_value_t.cboffset7 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cbclass7:10",
              "Channel 7 command processor current class",
              10, old_value_t.cbclass7, new_value_t.cbclass7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define CDMA_STATS_WORDS_FETCHED_OFFSET 0x898
#define CDMA_STATS_WORDS_FETCHED_UNDEFMASK 0x00000000
union cdma_stats_words_fetched_u {
    struct {
        unsigned int cdma_words_fetched:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cdma_stats_words_fetched_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cdma_stats_words_fetched_u old_value_t = { .reg32 = value };
    const cdma_stats_words_fetched_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cdma_words_fetched:32", "", 32, old_value_t.cdma_words_fetched, new_value_t.cdma_words_fetched };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The total number of 128-bit words fetched by all CDMA channels. This register gets reset to 0 at startup and is then just a wrap-around register. There is no other way to clear its value, so to do a measurement, one should read the initial value before the start of the testing period and read it again after. The counter will only be updated when the CDMA_EN_STATS bit is enabled.";
}

#define CDMA_STATS_WORDS_DISCARDED_OFFSET 0x89C
#define CDMA_STATS_WORDS_DISCARDED_UNDEFMASK 0x00000000
union cdma_stats_words_discarded_u {
    struct {
        unsigned int cdma_words_discarded:32;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cdma_stats_words_discarded_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cdma_stats_words_discarded_u old_value_t = { .reg32 = value };
    const cdma_stats_words_discarded_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cdma_words_discarded:32", "", 32, old_value_t.cdma_words_discarded, new_value_t.cdma_words_discarded };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The total number of 128-bit words that are discarded by the CDMA to avoid  head-of-line blocking in the prefetching pipeline. This register gets reset to 0 at startup and is then just a wrap-around register. There is no other way to clear its value, so to do a measurement, one should read the initial value before the start of the testing period and read it again after. The counter will only be updated when the CDMA_EN_STATS bit is enabled.\nTo calculate the efficiency of the CDMA, one should divided the value of this register with the one of CDMA_WORDS_FETCHED.";
}

#define CFG_OFFSET 0x94C
#define CFG_UNDEFMASK 0x0000FFFE
union host1x_cfg_u {
    struct {
        unsigned int disable_use_idle_div:1;/* Prevent use of low freq clock */
        unsigned int undefined_bits_1_15:15;
        unsigned int idle_wait_cnt:16;      /* Number of idle cycles to wait before changing divider */
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const host1x_cfg_u old_value_t = { .reg32 = value };
    const host1x_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: disable_use_idle_div:1",
              "Prevent use of low freq clock",
              1, old_value_t.disable_use_idle_div, new_value_t.disable_use_idle_div };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_15:15", "", 15, old_value_t.undefined_bits_1_15, new_value_t.undefined_bits_1_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: idle_wait_cnt:16",
              "Number of idle cycles to wait before changing divider",
              16, old_value_t.idle_wait_cnt, new_value_t.idle_wait_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DISABLE_USE_IDLE_DIV: host1x_use_idle_div is signal to car to switch host1x to low freq clock.  CYA to disable";
}

#define RDMA_MISC_OFFSET 0x8A0
#define RDMA_MISC_UNDEFMASK 0xFFFFEEE0
union rdma_misc_u {
    struct {
        unsigned int rdma_rect_allow_last:1;
        unsigned int rdma_clken_ovr:1;
        unsigned int rdma_force_jpege_stride:1;
        unsigned int rdma_clken_simple:1;
        unsigned int rdma_reset_pend_mem_req:1;
        unsigned int undefined_bits_5_7:3;
        unsigned int rdma_rect_align:1;
        unsigned int undefined_bits_9_11:3;
        unsigned int rdma_hndsk_stall:1;
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_misc_u old_value_t = { .reg32 = value };
    const rdma_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_rect_allow_last:1", "", 1, old_value_t.rdma_rect_allow_last, new_value_t.rdma_rect_allow_last };
    m_bit_details_model.bits.append(entry);
    entry = { "01: rdma_clken_ovr:1", "", 1, old_value_t.rdma_clken_ovr, new_value_t.rdma_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rdma_force_jpege_stride:1", "", 1, old_value_t.rdma_force_jpege_stride, new_value_t.rdma_force_jpege_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "03: rdma_clken_simple:1", "", 1, old_value_t.rdma_clken_simple, new_value_t.rdma_clken_simple };
    m_bit_details_model.bits.append(entry);
    entry = { "04: rdma_reset_pend_mem_req:1", "", 1, old_value_t.rdma_reset_pend_mem_req, new_value_t.rdma_reset_pend_mem_req };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: rdma_rect_align:1", "", 1, old_value_t.rdma_rect_align, new_value_t.rdma_rect_align };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_11:3", "", 3, old_value_t.undefined_bits_9_11, new_value_t.undefined_bits_9_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: rdma_hndsk_stall:1", "", 1, old_value_t.rdma_hndsk_stall, new_value_t.rdma_hndsk_stall };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_ARB_COUNT_OFFSET 0x8C0
#define RDMA_ARB_COUNT_UNDEFMASK 0xFFFFFFF0
union rdma_arb_count_u {
    struct {
        unsigned int rdma_arb_count:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_arb_count_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_arb_count_u old_value_t = { .reg32 = value };
    const rdma_arb_count_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_arb_count:4", "", 4, old_value_t.rdma_arb_count, new_value_t.rdma_arb_count };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_CONFIG_OFFSET 0x8C4
#define RDMA_CONFIG_UNDEFMASK 0xFFFFFFFE
union rdma_config_u {
    struct {
        unsigned int rdma_rectangular_buffer:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_config_u old_value_t = { .reg32 = value };
    const rdma_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_rectangular_buffer:1", "", 1, old_value_t.rdma_rectangular_buffer, new_value_t.rdma_rectangular_buffer };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_WRAP_OFFSET 0x8C8
#define RDMA_WRAP_UNDEFMASK 0xFFFFFFFE
union rdma_wrap_u {
    struct {
        unsigned int rdma_wrap:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_wrap_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_wrap_u old_value_t = { .reg32 = value };
    const rdma_wrap_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_wrap:1", "", 1, old_value_t.rdma_wrap, new_value_t.rdma_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_STATUS0_OFFSET 0x8CC
#define RDMA_STATUS0_UNDEFMASK 0xFFF00000
union rdma_status0_u {
    struct {
        unsigned int rdma_wrapped0:1;       /* read DMA port wrapped to base address */
        unsigned int rdma_outfentries0:6;   /* number of 32-bit words in read DMA fifo. Note: hardcoded to ensure SW backward compatibility if buffer is scaled down later. */
        unsigned int rdma_pendbufrdy0:9;    /* number of pending buffer_rdy's (pending buffers in memory) */
        unsigned int rdma_pend_mem_req0:4;  /* pending memory requests on port0 */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_status0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_status0_u old_value_t = { .reg32 = value };
    const rdma_status0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_wrapped0:1",
              "read DMA port wrapped to base address",
              1, old_value_t.rdma_wrapped0, new_value_t.rdma_wrapped0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: rdma_outfentries0:6",
              "number of 32-bit words in read DMA fifo. Note: hardcoded to ensure SW backward compatibility if buffer is scaled down later.",
              6, old_value_t.rdma_outfentries0, new_value_t.rdma_outfentries0 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: rdma_pendbufrdy0:9",
              "number of pending buffer_rdy's (pending buffers in memory)",
              9, old_value_t.rdma_pendbufrdy0, new_value_t.rdma_pendbufrdy0 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rdma_pend_mem_req0:4",
              "pending memory requests on port0",
              4, old_value_t.rdma_pend_mem_req0, new_value_t.rdma_pend_mem_req0 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_BUFFER_THRESHOLD0_OFFSET 0x8D0
#define RDMA_BUFFER_THRESHOLD0_UNDEFMASK 0xFFFF8000
union rdma_buffer_threshold0_u {
    struct {
        unsigned int buffer_threshold0:9;   /* Threshold of number of buffers pending in memory at which an interrupt is generated */
        unsigned int databuf_threshold0:6;  /* Threshold of number of words in out_fifo at which an interrupt is generated */
        unsigned int undefined_bits_15_31:17;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_buffer_threshold0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_buffer_threshold0_u old_value_t = { .reg32 = value };
    const rdma_buffer_threshold0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: buffer_threshold0:9",
              "Threshold of number of buffers pending in memory at which an interrupt is generated",
              9, old_value_t.buffer_threshold0, new_value_t.buffer_threshold0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: databuf_threshold0:6",
              "Threshold of number of words in out_fifo at which an interrupt is generated",
              6, old_value_t.databuf_threshold0, new_value_t.databuf_threshold0 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bits_15_31:17", "", 17, old_value_t.undefined_bits_15_31, new_value_t.undefined_bits_15_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_CONF0_OFFSET 0x8D4
#define RDMA_CONF0_UNDEFMASK 0xFFC00000
union rdma_conf0_u {
    struct {
        unsigned int rdma_num_buffers0:9;   /* Number of buffers defined for read DMA FIFO0 */
        unsigned int rdma_num_lines0:12;    /* Rectangular reads: Number of lines per buffer */
        unsigned int rdma_store_hdr0:1;     /* Store header with bufferdata in DMA fifo (data is sent to DSP/CPU) */
        unsigned int undefined_bits_22_31:10;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_conf0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_conf0_u old_value_t = { .reg32 = value };
    const rdma_conf0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_num_buffers0:9",
              "Number of buffers defined for read DMA FIFO0",
              9, old_value_t.rdma_num_buffers0, new_value_t.rdma_num_buffers0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: rdma_num_lines0:12",
              "Rectangular reads: Number of lines per buffer",
              12, old_value_t.rdma_num_lines0, new_value_t.rdma_num_lines0 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: rdma_store_hdr0:1",
              "Store header with bufferdata in DMA fifo (data is sent to DSP/CPU)",
              1, old_value_t.rdma_store_hdr0, new_value_t.rdma_store_hdr0 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_31:10", "", 10, old_value_t.undefined_bits_22_31, new_value_t.undefined_bits_22_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_SWAP0_OFFSET 0x8D8
#define RDMA_SWAP0_UNDEFMASK 0xFFFFFFF0
union rdma_swap0_u {
    struct {
        unsigned int rdma_data_swap0:2;
        unsigned int rdma_header_swap0:2;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_swap0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_swap0_u old_value_t = { .reg32 = value };
    const rdma_swap0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_data_swap0:2", "", 2, old_value_t.rdma_data_swap0, new_value_t.rdma_data_swap0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rdma_header_swap0:2", "", 2, old_value_t.rdma_header_swap0, new_value_t.rdma_header_swap0 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_LINE0_OFFSET 0x8DC
#define RDMA_LINE0_UNDEFMASK 0x00000000
union rdma_line0_u {
    struct {
        unsigned int rdma_line_stride0:12;  /* rectangular reads: line_stride(bytes); JPEGE: buffer_stride (16 byte aligned!!) */
        unsigned int rdma_line_width0:12;   /* rectangular reads: line_width (bytes) */
        unsigned int rdma_line_msb_stride0:4;
        unsigned int rdma_line_msb_width0:4;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_line0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_line0_u old_value_t = { .reg32 = value };
    const rdma_line0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_line_stride0:12",
              "rectangular reads: line_stride(bytes); JPEGE: buffer_stride (16 byte aligned!!)",
              12, old_value_t.rdma_line_stride0, new_value_t.rdma_line_stride0 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: rdma_line_width0:12",
              "rectangular reads: line_width (bytes)",
              12, old_value_t.rdma_line_width0, new_value_t.rdma_line_width0 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: rdma_line_msb_stride0:4", "", 4, old_value_t.rdma_line_msb_stride0, new_value_t.rdma_line_msb_stride0 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: rdma_line_msb_width0:4", "", 4, old_value_t.rdma_line_msb_width0, new_value_t.rdma_line_msb_width0 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_CLID0_OFFSET 0x8E0
#define RDMA_CLID0_UNDEFMASK 0xFFFFFFF0
union rdma_clid0_u {
    struct {
        unsigned int rdma_clientid0:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_clid0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_clid0_u old_value_t = { .reg32 = value };
    const rdma_clid0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_clientid0:4", "", 4, old_value_t.rdma_clientid0, new_value_t.rdma_clientid0 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_BADDR0_OFFSET 0x8E4
#define RDMA_BADDR0_UNDEFMASK 0x00000000
union rdma_baddr0_u {
    struct {
        unsigned int rdma_base_addr_lsb0:2;
        unsigned int rdma_base_addr0:30;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_baddr0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_baddr0_u old_value_t = { .reg32 = value };
    const rdma_baddr0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_base_addr_lsb0:2", "", 2, old_value_t.rdma_base_addr_lsb0, new_value_t.rdma_base_addr_lsb0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rdma_base_addr0:30", "", 30, old_value_t.rdma_base_addr0, new_value_t.rdma_base_addr0 };
    m_bit_details_model.bits.append(entry);
}

#define RDMA_DMATRIGGER0_OFFSET 0x8E8
#define RDMA_DMATRIGGER0_UNDEFMASK 0xFFFFFFF8
union rdma_dmatrigger0_u {
    struct {
        unsigned int rdma_buf_init0:1;      /* buffer_init: initializes read DMA port */
        unsigned int rdma_buf_rdy0:1;       /* buffer_rdy : indicates buffer is pending in memory */
        unsigned int rdma_last_buf0:1;      /* last_buffer: indicates this is the last buffer in a chain */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void Host1x_syncDev::fill_rdma_dmatrigger0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdma_dmatrigger0_u old_value_t = { .reg32 = value };
    const rdma_dmatrigger0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdma_buf_init0:1",
              "buffer_init: initializes read DMA port",
              1, old_value_t.rdma_buf_init0, new_value_t.rdma_buf_init0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: rdma_buf_rdy0:1",
              "buffer_rdy : indicates buffer is pending in memory",
              1, old_value_t.rdma_buf_rdy0, new_value_t.rdma_buf_rdy0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rdma_last_buf0:1",
              "last_buffer: indicates this is the last buffer in a chain",
              1, old_value_t.rdma_last_buf0, new_value_t.rdma_last_buf0 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

bool Host1x_syncDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset & 0xfff) {
    case INTSTATUS_OFFSET:
    case INTMASK_OFFSET:
    case INTC0MASK_OFFSET:
    case INTC1MASK_OFFSET:
    case HINTSTATUS_OFFSET:
    case HINTMASK_OFFSET:
    case HINTSTATUS_EXT_OFFSET:
    case HINTMASK_EXT_OFFSET:
    case SYNCPT_THRESH_CPU0_INT_STATUS_OFFSET:
    case SYNCPT_THRESH_CPU1_INT_STATUS_OFFSET:
    case SYNCPT_THRESH_INT_MASK_OFFSET:
    case SYNCPT_THRESH_INT_MASK_1_OFFSET:
    case SYNCPT_THRESH_INT_DISABLE_OFFSET:
    case SYNCPT_THRESH_INT_ENABLE_CPU0_OFFSET:
    case SYNCPT_THRESH_INT_ENABLE_CPU1_OFFSET:
    case CF0_SETUP_OFFSET:
    case CF1_SETUP_OFFSET:
    case CF2_SETUP_OFFSET:
    case CF3_SETUP_OFFSET:
    case CF4_SETUP_OFFSET:
    case CF5_SETUP_OFFSET:
    case CF6_SETUP_OFFSET:
    case CF7_SETUP_OFFSET:
    case CF_SETUPDONE_OFFSET:
    case CMDPROC_CTRL_OFFSET:
    case CMDPROC_STAT_OFFSET:
    case CMDPROC_STOP_OFFSET:
    case CH_TEARDOWN_OFFSET:
    case MOD_TEARDOWN_OFFSET:
    case CH0_STATUS_OFFSET:
    case CH1_STATUS_OFFSET:
    case CH2_STATUS_OFFSET:
    case CH3_STATUS_OFFSET:
    case CH4_STATUS_OFFSET:
    case CH5_STATUS_OFFSET:
    case CH6_STATUS_OFFSET:
    case CH7_STATUS_OFFSET:
    case DISPLAY_STATUS_OFFSET:
    case DISPLAYB_STATUS_OFFSET:
    case EPP_STATUS_OFFSET:
    case GR3D_STATUS_OFFSET:
    case ISP_STATUS_OFFSET:
    case MPE_STATUS_OFFSET:
    case TVO_STATUS_OFFSET:
    case DSI_STATUS_OFFSET:
    case HDMI_STATUS_OFFSET:
    case VI_STATUS_OFFSET:
    case GR2D_STATUS_OFFSET:
    case DIRECT_MODULE_CONFIG_OFFSET:
    case USEC_CLK_OFFSET:
    case CTXSW_TIMEOUT_CFG_OFFSET:
    case INDREG_DMA_CTRL_OFFSET:
    case CHANNEL_PRIORITY_OFFSET:
    case CDMA_ASM_TIMEOUT_OFFSET:
    case CDMA_MISC_OFFSET:
    case IP_BUSY_TIMEOUT_OFFSET:
    case IP_READ_TIMEOUT_ADDR_OFFSET:
    case IP_WRITE_TIMEOUT_ADDR_OFFSET:
    case MCCIF_THCTRL_OFFSET:
    case HC_MCCIF_FIFOCTRL_OFFSET:
    case TIMEOUT_WCOAL_HC_OFFSET:
    case HWLOCK0_OFFSET:
    case HWLOCK1_OFFSET:
    case HWLOCK2_OFFSET:
    case HWLOCK3_OFFSET:
    case HWLOCK4_OFFSET:
    case HWLOCK5_OFFSET:
    case HWLOCK6_OFFSET:
    case HWLOCK7_OFFSET:
    case MLOCK_OFFSET:
    case MLOCK_1_OFFSET:
    case MLOCK_2_OFFSET:
    case MLOCK_3_OFFSET:
    case MLOCK_4_OFFSET:
    case MLOCK_5_OFFSET:
    case MLOCK_6_OFFSET:
    case MLOCK_7_OFFSET:
    case MLOCK_8_OFFSET:
    case MLOCK_9_OFFSET:
    case MLOCK_10_OFFSET:
    case MLOCK_11_OFFSET:
    case MLOCK_12_OFFSET:
    case MLOCK_13_OFFSET:
    case MLOCK_14_OFFSET:
    case MLOCK_15_OFFSET:
    case MLOCK_OWNER_OFFSET:
    case MLOCK_OWNER_1_OFFSET:
    case MLOCK_OWNER_2_OFFSET:
    case MLOCK_OWNER_3_OFFSET:
    case MLOCK_OWNER_4_OFFSET:
    case MLOCK_OWNER_5_OFFSET:
    case MLOCK_OWNER_6_OFFSET:
    case MLOCK_OWNER_7_OFFSET:
    case MLOCK_OWNER_8_OFFSET:
    case MLOCK_OWNER_9_OFFSET:
    case MLOCK_OWNER_10_OFFSET:
    case MLOCK_OWNER_11_OFFSET:
    case MLOCK_OWNER_12_OFFSET:
    case MLOCK_OWNER_13_OFFSET:
    case MLOCK_OWNER_14_OFFSET:
    case MLOCK_OWNER_15_OFFSET:
    case MLOCK_ERROR_OFFSET:
    case SYNCPT_OFFSET:
    case SYNCPT_1_OFFSET:
    case SYNCPT_2_OFFSET:
    case SYNCPT_3_OFFSET:
    case SYNCPT_4_OFFSET:
    case SYNCPT_5_OFFSET:
    case SYNCPT_6_OFFSET:
    case SYNCPT_7_OFFSET:
    case SYNCPT_8_OFFSET:
    case SYNCPT_9_OFFSET:
    case SYNCPT_10_OFFSET:
    case SYNCPT_11_OFFSET:
    case SYNCPT_12_OFFSET:
    case SYNCPT_13_OFFSET:
    case SYNCPT_14_OFFSET:
    case SYNCPT_15_OFFSET:
    case SYNCPT_16_OFFSET:
    case SYNCPT_17_OFFSET:
    case SYNCPT_18_OFFSET:
    case SYNCPT_19_OFFSET:
    case SYNCPT_20_OFFSET:
    case SYNCPT_21_OFFSET:
    case SYNCPT_22_OFFSET:
    case SYNCPT_23_OFFSET:
    case SYNCPT_24_OFFSET:
    case SYNCPT_25_OFFSET:
    case SYNCPT_26_OFFSET:
    case SYNCPT_27_OFFSET:
    case SYNCPT_28_OFFSET:
    case SYNCPT_29_OFFSET:
    case SYNCPT_30_OFFSET:
    case SYNCPT_31_OFFSET:
    case SYNCPT_INT_THRESH_OFFSET:
    case SYNCPT_INT_THRESH_1_OFFSET:
    case SYNCPT_INT_THRESH_2_OFFSET:
    case SYNCPT_INT_THRESH_3_OFFSET:
    case SYNCPT_INT_THRESH_4_OFFSET:
    case SYNCPT_INT_THRESH_5_OFFSET:
    case SYNCPT_INT_THRESH_6_OFFSET:
    case SYNCPT_INT_THRESH_7_OFFSET:
    case SYNCPT_INT_THRESH_8_OFFSET:
    case SYNCPT_INT_THRESH_9_OFFSET:
    case SYNCPT_INT_THRESH_10_OFFSET:
    case SYNCPT_INT_THRESH_11_OFFSET:
    case SYNCPT_INT_THRESH_12_OFFSET:
    case SYNCPT_INT_THRESH_13_OFFSET:
    case SYNCPT_INT_THRESH_14_OFFSET:
    case SYNCPT_INT_THRESH_15_OFFSET:
    case SYNCPT_INT_THRESH_16_OFFSET:
    case SYNCPT_INT_THRESH_17_OFFSET:
    case SYNCPT_INT_THRESH_18_OFFSET:
    case SYNCPT_INT_THRESH_19_OFFSET:
    case SYNCPT_INT_THRESH_20_OFFSET:
    case SYNCPT_INT_THRESH_21_OFFSET:
    case SYNCPT_INT_THRESH_22_OFFSET:
    case SYNCPT_INT_THRESH_23_OFFSET:
    case SYNCPT_INT_THRESH_24_OFFSET:
    case SYNCPT_INT_THRESH_25_OFFSET:
    case SYNCPT_INT_THRESH_26_OFFSET:
    case SYNCPT_INT_THRESH_27_OFFSET:
    case SYNCPT_INT_THRESH_28_OFFSET:
    case SYNCPT_INT_THRESH_29_OFFSET:
    case SYNCPT_INT_THRESH_30_OFFSET:
    case SYNCPT_INT_THRESH_31_OFFSET:
    case SYNCPT_BASE_OFFSET:
    case SYNCPT_BASE_1_OFFSET:
    case SYNCPT_BASE_2_OFFSET:
    case SYNCPT_BASE_3_OFFSET:
    case SYNCPT_BASE_4_OFFSET:
    case SYNCPT_BASE_5_OFFSET:
    case SYNCPT_BASE_6_OFFSET:
    case SYNCPT_BASE_7_OFFSET:
    case SYNCPT_CPU_INCR_OFFSET:
    case CBREAD0_OFFSET:
    case CBREAD1_OFFSET:
    case CBREAD2_OFFSET:
    case CBREAD3_OFFSET:
    case CBREAD4_OFFSET:
    case CBREAD5_OFFSET:
    case CBREAD6_OFFSET:
    case CBREAD7_OFFSET:
    case REGF_DATA_OFFSET:
    case REGF_ADDR_OFFSET:
    case WAITOVR_OFFSET:
    case CFPEEK_CTRL_OFFSET:
    case CFPEEK_READ_OFFSET:
    case CFPEEK_PTRS_OFFSET:
    case CBSTAT0_OFFSET:
    case CBSTAT1_OFFSET:
    case CBSTAT2_OFFSET:
    case CBSTAT3_OFFSET:
    case CBSTAT4_OFFSET:
    case CBSTAT5_OFFSET:
    case CBSTAT6_OFFSET:
    case CBSTAT7_OFFSET:
    case CDMA_STATS_WORDS_FETCHED_OFFSET:
    case CDMA_STATS_WORDS_DISCARDED_OFFSET:
    case CFG_OFFSET:
    case RDMA_MISC_OFFSET:
    case RDMA_ARB_COUNT_OFFSET:
    case RDMA_CONFIG_OFFSET:
    case RDMA_WRAP_OFFSET:
    case RDMA_STATUS0_OFFSET:
    case RDMA_BUFFER_THRESHOLD0_OFFSET:
    case RDMA_CONF0_OFFSET:
    case RDMA_SWAP0_OFFSET:
    case RDMA_LINE0_OFFSET:
    case RDMA_CLID0_OFFSET:
    case RDMA_BADDR0_OFFSET:
    case RDMA_DMATRIGGER0_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Host1x_syncDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset & 0xfff) {
    case INTSTATUS_OFFSET:
        if ((value ^ new_value) & INTSTATUS_UNDEFMASK)
            return true;
        break;
    case INTMASK_OFFSET:
        if ((value ^ new_value) & INTMASK_UNDEFMASK)
            return true;
        break;
    case INTC0MASK_OFFSET:
        if ((value ^ new_value) & INTC0MASK_UNDEFMASK)
            return true;
        break;
    case INTC1MASK_OFFSET:
        if ((value ^ new_value) & INTC1MASK_UNDEFMASK)
            return true;
        break;
    case HINTSTATUS_OFFSET:
        if ((value ^ new_value) & HINTSTATUS_UNDEFMASK)
            return true;
        break;
    case HINTMASK_OFFSET:
        if ((value ^ new_value) & HINTMASK_UNDEFMASK)
            return true;
        break;
    case HINTSTATUS_EXT_OFFSET:
        if ((value ^ new_value) & HINTSTATUS_EXT_UNDEFMASK)
            return true;
        break;
    case HINTMASK_EXT_OFFSET:
        if ((value ^ new_value) & HINTMASK_EXT_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_CPU0_INT_STATUS_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_CPU0_INT_STATUS_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_CPU1_INT_STATUS_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_CPU1_INT_STATUS_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_INT_MASK_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_INT_MASK_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_INT_MASK_1_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_INT_MASK_1_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_INT_DISABLE_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_INT_DISABLE_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_INT_ENABLE_CPU0_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_INT_ENABLE_CPU0_UNDEFMASK)
            return true;
        break;
    case SYNCPT_THRESH_INT_ENABLE_CPU1_OFFSET:
        if ((value ^ new_value) & SYNCPT_THRESH_INT_ENABLE_CPU1_UNDEFMASK)
            return true;
        break;
    case CF0_SETUP_OFFSET:
        if ((value ^ new_value) & CF0_SETUP_UNDEFMASK)
            return true;
        break;
    case CF1_SETUP_OFFSET:
        if ((value ^ new_value) & CF1_SETUP_UNDEFMASK)
            return true;
        break;
    case CF2_SETUP_OFFSET:
        if ((value ^ new_value) & CF2_SETUP_UNDEFMASK)
            return true;
        break;
    case CF3_SETUP_OFFSET:
        if ((value ^ new_value) & CF3_SETUP_UNDEFMASK)
            return true;
        break;
    case CF4_SETUP_OFFSET:
        if ((value ^ new_value) & CF4_SETUP_UNDEFMASK)
            return true;
        break;
    case CF5_SETUP_OFFSET:
        if ((value ^ new_value) & CF5_SETUP_UNDEFMASK)
            return true;
        break;
    case CF6_SETUP_OFFSET:
        if ((value ^ new_value) & CF6_SETUP_UNDEFMASK)
            return true;
        break;
    case CF7_SETUP_OFFSET:
        if ((value ^ new_value) & CF7_SETUP_UNDEFMASK)
            return true;
        break;
    case CF_SETUPDONE_OFFSET:
        if ((value ^ new_value) & CF_SETUPDONE_UNDEFMASK)
            return true;
        break;
    case CMDPROC_CTRL_OFFSET:
        if ((value ^ new_value) & CMDPROC_CTRL_UNDEFMASK)
            return true;
        break;
    case CMDPROC_STAT_OFFSET:
        if ((value ^ new_value) & CMDPROC_STAT_UNDEFMASK)
            return true;
        break;
    case CMDPROC_STOP_OFFSET:
        if ((value ^ new_value) & CMDPROC_STOP_UNDEFMASK)
            return true;
        break;
    case CH_TEARDOWN_OFFSET:
        if ((value ^ new_value) & CH_TEARDOWN_UNDEFMASK)
            return true;
        break;
    case MOD_TEARDOWN_OFFSET:
        if ((value ^ new_value) & MOD_TEARDOWN_UNDEFMASK)
            return true;
        break;
    case CH0_STATUS_OFFSET:
        if ((value ^ new_value) & CH0_STATUS_UNDEFMASK)
            return true;
        break;
    case CH1_STATUS_OFFSET:
        if ((value ^ new_value) & CH1_STATUS_UNDEFMASK)
            return true;
        break;
    case CH2_STATUS_OFFSET:
        if ((value ^ new_value) & CH2_STATUS_UNDEFMASK)
            return true;
        break;
    case CH3_STATUS_OFFSET:
        if ((value ^ new_value) & CH3_STATUS_UNDEFMASK)
            return true;
        break;
    case CH4_STATUS_OFFSET:
        if ((value ^ new_value) & CH4_STATUS_UNDEFMASK)
            return true;
        break;
    case CH5_STATUS_OFFSET:
        if ((value ^ new_value) & CH5_STATUS_UNDEFMASK)
            return true;
        break;
    case CH6_STATUS_OFFSET:
        if ((value ^ new_value) & CH6_STATUS_UNDEFMASK)
            return true;
        break;
    case CH7_STATUS_OFFSET:
        if ((value ^ new_value) & CH7_STATUS_UNDEFMASK)
            return true;
        break;
    case DISPLAY_STATUS_OFFSET:
        if ((value ^ new_value) & DISPLAY_STATUS_UNDEFMASK)
            return true;
        break;
    case DISPLAYB_STATUS_OFFSET:
        if ((value ^ new_value) & DISPLAYB_STATUS_UNDEFMASK)
            return true;
        break;
    case EPP_STATUS_OFFSET:
        if ((value ^ new_value) & EPP_STATUS_UNDEFMASK)
            return true;
        break;
    case GR3D_STATUS_OFFSET:
        if ((value ^ new_value) & GR3D_STATUS_UNDEFMASK)
            return true;
        break;
    case ISP_STATUS_OFFSET:
        if ((value ^ new_value) & ISP_STATUS_UNDEFMASK)
            return true;
        break;
    case MPE_STATUS_OFFSET:
        if ((value ^ new_value) & MPE_STATUS_UNDEFMASK)
            return true;
        break;
    case TVO_STATUS_OFFSET:
        if ((value ^ new_value) & TVO_STATUS_UNDEFMASK)
            return true;
        break;
    case DSI_STATUS_OFFSET:
        if ((value ^ new_value) & DSI_STATUS_UNDEFMASK)
            return true;
        break;
    case HDMI_STATUS_OFFSET:
        if ((value ^ new_value) & HDMI_STATUS_UNDEFMASK)
            return true;
        break;
    case VI_STATUS_OFFSET:
        if ((value ^ new_value) & VI_STATUS_UNDEFMASK)
            return true;
        break;
    case GR2D_STATUS_OFFSET:
        if ((value ^ new_value) & GR2D_STATUS_UNDEFMASK)
            return true;
        break;
    case DIRECT_MODULE_CONFIG_OFFSET:
        if ((value ^ new_value) & DIRECT_MODULE_CONFIG_UNDEFMASK)
            return true;
        break;
    case USEC_CLK_OFFSET:
        if ((value ^ new_value) & USEC_CLK_UNDEFMASK)
            return true;
        break;
    case CTXSW_TIMEOUT_CFG_OFFSET:
        if ((value ^ new_value) & CTXSW_TIMEOUT_CFG_UNDEFMASK)
            return true;
        break;
    case INDREG_DMA_CTRL_OFFSET:
        if ((value ^ new_value) & INDREG_DMA_CTRL_UNDEFMASK)
            return true;
        break;
    case CHANNEL_PRIORITY_OFFSET:
        if ((value ^ new_value) & CHANNEL_PRIORITY_UNDEFMASK)
            return true;
        break;
    case CDMA_ASM_TIMEOUT_OFFSET:
        if ((value ^ new_value) & CDMA_ASM_TIMEOUT_UNDEFMASK)
            return true;
        break;
    case CDMA_MISC_OFFSET:
        if ((value ^ new_value) & CDMA_MISC_UNDEFMASK)
            return true;
        break;
    case IP_BUSY_TIMEOUT_OFFSET:
        if ((value ^ new_value) & IP_BUSY_TIMEOUT_UNDEFMASK)
            return true;
        break;
    case IP_READ_TIMEOUT_ADDR_OFFSET:
        if ((value ^ new_value) & IP_READ_TIMEOUT_ADDR_UNDEFMASK)
            return true;
        break;
    case IP_WRITE_TIMEOUT_ADDR_OFFSET:
        if ((value ^ new_value) & IP_WRITE_TIMEOUT_ADDR_UNDEFMASK)
            return true;
        break;
    case MCCIF_THCTRL_OFFSET:
        if ((value ^ new_value) & MCCIF_THCTRL_UNDEFMASK)
            return true;
        break;
    case HC_MCCIF_FIFOCTRL_OFFSET:
        if ((value ^ new_value) & HC_MCCIF_FIFOCTRL_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_WCOAL_HC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_WCOAL_HC_UNDEFMASK)
            return true;
        break;
    case HWLOCK0_OFFSET:
        if ((value ^ new_value) & HWLOCK0_UNDEFMASK)
            return true;
        break;
    case HWLOCK1_OFFSET:
        if ((value ^ new_value) & HWLOCK1_UNDEFMASK)
            return true;
        break;
    case HWLOCK2_OFFSET:
        if ((value ^ new_value) & HWLOCK2_UNDEFMASK)
            return true;
        break;
    case HWLOCK3_OFFSET:
        if ((value ^ new_value) & HWLOCK3_UNDEFMASK)
            return true;
        break;
    case HWLOCK4_OFFSET:
        if ((value ^ new_value) & HWLOCK4_UNDEFMASK)
            return true;
        break;
    case HWLOCK5_OFFSET:
        if ((value ^ new_value) & HWLOCK5_UNDEFMASK)
            return true;
        break;
    case HWLOCK6_OFFSET:
        if ((value ^ new_value) & HWLOCK6_UNDEFMASK)
            return true;
        break;
    case HWLOCK7_OFFSET:
        if ((value ^ new_value) & HWLOCK7_UNDEFMASK)
            return true;
        break;
    case MLOCK_OFFSET:
        if ((value ^ new_value) & MLOCK_UNDEFMASK)
            return true;
        break;
    case MLOCK_1_OFFSET:
        if ((value ^ new_value) & MLOCK_1_UNDEFMASK)
            return true;
        break;
    case MLOCK_2_OFFSET:
        if ((value ^ new_value) & MLOCK_2_UNDEFMASK)
            return true;
        break;
    case MLOCK_3_OFFSET:
        if ((value ^ new_value) & MLOCK_3_UNDEFMASK)
            return true;
        break;
    case MLOCK_4_OFFSET:
        if ((value ^ new_value) & MLOCK_4_UNDEFMASK)
            return true;
        break;
    case MLOCK_5_OFFSET:
        if ((value ^ new_value) & MLOCK_5_UNDEFMASK)
            return true;
        break;
    case MLOCK_6_OFFSET:
        if ((value ^ new_value) & MLOCK_6_UNDEFMASK)
            return true;
        break;
    case MLOCK_7_OFFSET:
        if ((value ^ new_value) & MLOCK_7_UNDEFMASK)
            return true;
        break;
    case MLOCK_8_OFFSET:
        if ((value ^ new_value) & MLOCK_8_UNDEFMASK)
            return true;
        break;
    case MLOCK_9_OFFSET:
        if ((value ^ new_value) & MLOCK_9_UNDEFMASK)
            return true;
        break;
    case MLOCK_10_OFFSET:
        if ((value ^ new_value) & MLOCK_10_UNDEFMASK)
            return true;
        break;
    case MLOCK_11_OFFSET:
        if ((value ^ new_value) & MLOCK_11_UNDEFMASK)
            return true;
        break;
    case MLOCK_12_OFFSET:
        if ((value ^ new_value) & MLOCK_12_UNDEFMASK)
            return true;
        break;
    case MLOCK_13_OFFSET:
        if ((value ^ new_value) & MLOCK_13_UNDEFMASK)
            return true;
        break;
    case MLOCK_14_OFFSET:
        if ((value ^ new_value) & MLOCK_14_UNDEFMASK)
            return true;
        break;
    case MLOCK_15_OFFSET:
        if ((value ^ new_value) & MLOCK_15_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_1_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_1_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_2_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_2_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_3_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_3_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_4_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_4_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_5_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_5_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_6_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_6_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_7_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_7_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_8_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_8_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_9_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_9_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_10_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_10_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_11_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_11_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_12_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_12_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_13_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_13_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_14_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_14_UNDEFMASK)
            return true;
        break;
    case MLOCK_OWNER_15_OFFSET:
        if ((value ^ new_value) & MLOCK_OWNER_15_UNDEFMASK)
            return true;
        break;
    case MLOCK_ERROR_OFFSET:
        if ((value ^ new_value) & MLOCK_ERROR_UNDEFMASK)
            return true;
        break;
    case SYNCPT_OFFSET:
        if ((value ^ new_value) & SYNCPT_UNDEFMASK)
            return true;
        break;
    case SYNCPT_1_OFFSET:
        if ((value ^ new_value) & SYNCPT_1_UNDEFMASK)
            return true;
        break;
    case SYNCPT_2_OFFSET:
        if ((value ^ new_value) & SYNCPT_2_UNDEFMASK)
            return true;
        break;
    case SYNCPT_3_OFFSET:
        if ((value ^ new_value) & SYNCPT_3_UNDEFMASK)
            return true;
        break;
    case SYNCPT_4_OFFSET:
        if ((value ^ new_value) & SYNCPT_4_UNDEFMASK)
            return true;
        break;
    case SYNCPT_5_OFFSET:
        if ((value ^ new_value) & SYNCPT_5_UNDEFMASK)
            return true;
        break;
    case SYNCPT_6_OFFSET:
        if ((value ^ new_value) & SYNCPT_6_UNDEFMASK)
            return true;
        break;
    case SYNCPT_7_OFFSET:
        if ((value ^ new_value) & SYNCPT_7_UNDEFMASK)
            return true;
        break;
    case SYNCPT_8_OFFSET:
        if ((value ^ new_value) & SYNCPT_8_UNDEFMASK)
            return true;
        break;
    case SYNCPT_9_OFFSET:
        if ((value ^ new_value) & SYNCPT_9_UNDEFMASK)
            return true;
        break;
    case SYNCPT_10_OFFSET:
        if ((value ^ new_value) & SYNCPT_10_UNDEFMASK)
            return true;
        break;
    case SYNCPT_11_OFFSET:
        if ((value ^ new_value) & SYNCPT_11_UNDEFMASK)
            return true;
        break;
    case SYNCPT_12_OFFSET:
        if ((value ^ new_value) & SYNCPT_12_UNDEFMASK)
            return true;
        break;
    case SYNCPT_13_OFFSET:
        if ((value ^ new_value) & SYNCPT_13_UNDEFMASK)
            return true;
        break;
    case SYNCPT_14_OFFSET:
        if ((value ^ new_value) & SYNCPT_14_UNDEFMASK)
            return true;
        break;
    case SYNCPT_15_OFFSET:
        if ((value ^ new_value) & SYNCPT_15_UNDEFMASK)
            return true;
        break;
    case SYNCPT_16_OFFSET:
        if ((value ^ new_value) & SYNCPT_16_UNDEFMASK)
            return true;
        break;
    case SYNCPT_17_OFFSET:
        if ((value ^ new_value) & SYNCPT_17_UNDEFMASK)
            return true;
        break;
    case SYNCPT_18_OFFSET:
        if ((value ^ new_value) & SYNCPT_18_UNDEFMASK)
            return true;
        break;
    case SYNCPT_19_OFFSET:
        if ((value ^ new_value) & SYNCPT_19_UNDEFMASK)
            return true;
        break;
    case SYNCPT_20_OFFSET:
        if ((value ^ new_value) & SYNCPT_20_UNDEFMASK)
            return true;
        break;
    case SYNCPT_21_OFFSET:
        if ((value ^ new_value) & SYNCPT_21_UNDEFMASK)
            return true;
        break;
    case SYNCPT_22_OFFSET:
        if ((value ^ new_value) & SYNCPT_22_UNDEFMASK)
            return true;
        break;
    case SYNCPT_23_OFFSET:
        if ((value ^ new_value) & SYNCPT_23_UNDEFMASK)
            return true;
        break;
    case SYNCPT_24_OFFSET:
        if ((value ^ new_value) & SYNCPT_24_UNDEFMASK)
            return true;
        break;
    case SYNCPT_25_OFFSET:
        if ((value ^ new_value) & SYNCPT_25_UNDEFMASK)
            return true;
        break;
    case SYNCPT_26_OFFSET:
        if ((value ^ new_value) & SYNCPT_26_UNDEFMASK)
            return true;
        break;
    case SYNCPT_27_OFFSET:
        if ((value ^ new_value) & SYNCPT_27_UNDEFMASK)
            return true;
        break;
    case SYNCPT_28_OFFSET:
        if ((value ^ new_value) & SYNCPT_28_UNDEFMASK)
            return true;
        break;
    case SYNCPT_29_OFFSET:
        if ((value ^ new_value) & SYNCPT_29_UNDEFMASK)
            return true;
        break;
    case SYNCPT_30_OFFSET:
        if ((value ^ new_value) & SYNCPT_30_UNDEFMASK)
            return true;
        break;
    case SYNCPT_31_OFFSET:
        if ((value ^ new_value) & SYNCPT_31_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_1_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_1_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_2_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_2_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_3_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_3_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_4_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_4_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_5_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_5_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_6_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_6_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_7_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_7_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_8_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_8_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_9_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_9_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_10_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_10_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_11_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_11_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_12_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_12_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_13_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_13_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_14_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_14_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_15_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_15_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_16_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_16_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_17_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_17_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_18_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_18_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_19_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_19_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_20_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_20_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_21_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_21_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_22_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_22_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_23_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_23_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_24_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_24_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_25_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_25_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_26_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_26_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_27_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_27_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_28_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_28_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_29_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_29_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_30_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_30_UNDEFMASK)
            return true;
        break;
    case SYNCPT_INT_THRESH_31_OFFSET:
        if ((value ^ new_value) & SYNCPT_INT_THRESH_31_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_1_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_1_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_2_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_2_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_3_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_3_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_4_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_4_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_5_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_5_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_6_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_6_UNDEFMASK)
            return true;
        break;
    case SYNCPT_BASE_7_OFFSET:
        if ((value ^ new_value) & SYNCPT_BASE_7_UNDEFMASK)
            return true;
        break;
    case SYNCPT_CPU_INCR_OFFSET:
        if ((value ^ new_value) & SYNCPT_CPU_INCR_UNDEFMASK)
            return true;
        break;
    case CBREAD0_OFFSET:
        if ((value ^ new_value) & CBREAD0_UNDEFMASK)
            return true;
        break;
    case CBREAD1_OFFSET:
        if ((value ^ new_value) & CBREAD1_UNDEFMASK)
            return true;
        break;
    case CBREAD2_OFFSET:
        if ((value ^ new_value) & CBREAD2_UNDEFMASK)
            return true;
        break;
    case CBREAD3_OFFSET:
        if ((value ^ new_value) & CBREAD3_UNDEFMASK)
            return true;
        break;
    case CBREAD4_OFFSET:
        if ((value ^ new_value) & CBREAD4_UNDEFMASK)
            return true;
        break;
    case CBREAD5_OFFSET:
        if ((value ^ new_value) & CBREAD5_UNDEFMASK)
            return true;
        break;
    case CBREAD6_OFFSET:
        if ((value ^ new_value) & CBREAD6_UNDEFMASK)
            return true;
        break;
    case CBREAD7_OFFSET:
        if ((value ^ new_value) & CBREAD7_UNDEFMASK)
            return true;
        break;
    case REGF_DATA_OFFSET:
        if ((value ^ new_value) & REGF_DATA_UNDEFMASK)
            return true;
        break;
    case REGF_ADDR_OFFSET:
        if ((value ^ new_value) & REGF_ADDR_UNDEFMASK)
            return true;
        break;
    case WAITOVR_OFFSET:
        if ((value ^ new_value) & WAITOVR_UNDEFMASK)
            return true;
        break;
    case CFPEEK_CTRL_OFFSET:
        if ((value ^ new_value) & CFPEEK_CTRL_UNDEFMASK)
            return true;
        break;
    case CFPEEK_READ_OFFSET:
        if ((value ^ new_value) & CFPEEK_READ_UNDEFMASK)
            return true;
        break;
    case CFPEEK_PTRS_OFFSET:
        if ((value ^ new_value) & CFPEEK_PTRS_UNDEFMASK)
            return true;
        break;
    case CBSTAT0_OFFSET:
        if ((value ^ new_value) & CBSTAT0_UNDEFMASK)
            return true;
        break;
    case CBSTAT1_OFFSET:
        if ((value ^ new_value) & CBSTAT1_UNDEFMASK)
            return true;
        break;
    case CBSTAT2_OFFSET:
        if ((value ^ new_value) & CBSTAT2_UNDEFMASK)
            return true;
        break;
    case CBSTAT3_OFFSET:
        if ((value ^ new_value) & CBSTAT3_UNDEFMASK)
            return true;
        break;
    case CBSTAT4_OFFSET:
        if ((value ^ new_value) & CBSTAT4_UNDEFMASK)
            return true;
        break;
    case CBSTAT5_OFFSET:
        if ((value ^ new_value) & CBSTAT5_UNDEFMASK)
            return true;
        break;
    case CBSTAT6_OFFSET:
        if ((value ^ new_value) & CBSTAT6_UNDEFMASK)
            return true;
        break;
    case CBSTAT7_OFFSET:
        if ((value ^ new_value) & CBSTAT7_UNDEFMASK)
            return true;
        break;
    case CDMA_STATS_WORDS_FETCHED_OFFSET:
        if ((value ^ new_value) & CDMA_STATS_WORDS_FETCHED_UNDEFMASK)
            return true;
        break;
    case CDMA_STATS_WORDS_DISCARDED_OFFSET:
        if ((value ^ new_value) & CDMA_STATS_WORDS_DISCARDED_UNDEFMASK)
            return true;
        break;
    case CFG_OFFSET:
        if ((value ^ new_value) & CFG_UNDEFMASK)
            return true;
        break;
    case RDMA_MISC_OFFSET:
        if ((value ^ new_value) & RDMA_MISC_UNDEFMASK)
            return true;
        break;
    case RDMA_ARB_COUNT_OFFSET:
        if ((value ^ new_value) & RDMA_ARB_COUNT_UNDEFMASK)
            return true;
        break;
    case RDMA_CONFIG_OFFSET:
        if ((value ^ new_value) & RDMA_CONFIG_UNDEFMASK)
            return true;
        break;
    case RDMA_WRAP_OFFSET:
        if ((value ^ new_value) & RDMA_WRAP_UNDEFMASK)
            return true;
        break;
    case RDMA_STATUS0_OFFSET:
        if ((value ^ new_value) & RDMA_STATUS0_UNDEFMASK)
            return true;
        break;
    case RDMA_BUFFER_THRESHOLD0_OFFSET:
        if ((value ^ new_value) & RDMA_BUFFER_THRESHOLD0_UNDEFMASK)
            return true;
        break;
    case RDMA_CONF0_OFFSET:
        if ((value ^ new_value) & RDMA_CONF0_UNDEFMASK)
            return true;
        break;
    case RDMA_SWAP0_OFFSET:
        if ((value ^ new_value) & RDMA_SWAP0_UNDEFMASK)
            return true;
        break;
    case RDMA_LINE0_OFFSET:
        if ((value ^ new_value) & RDMA_LINE0_UNDEFMASK)
            return true;
        break;
    case RDMA_CLID0_OFFSET:
        if ((value ^ new_value) & RDMA_CLID0_UNDEFMASK)
            return true;
        break;
    case RDMA_BADDR0_OFFSET:
        if ((value ^ new_value) & RDMA_BADDR0_UNDEFMASK)
            return true;
        break;
    case RDMA_DMATRIGGER0_OFFSET:
        if ((value ^ new_value) & RDMA_DMATRIGGER0_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Host1x_syncDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset & 0xfff) {
    case INTSTATUS_OFFSET:
        return QString("INTSTATUS");
    case INTMASK_OFFSET:
        return QString("INTMASK");
    case INTC0MASK_OFFSET:
        return QString("INTC0MASK");
    case INTC1MASK_OFFSET:
        return QString("INTC1MASK");
    case HINTSTATUS_OFFSET:
        return QString("HINTSTATUS");
    case HINTMASK_OFFSET:
        return QString("HINTMASK");
    case HINTSTATUS_EXT_OFFSET:
        return QString("HINTSTATUS_EXT");
    case HINTMASK_EXT_OFFSET:
        return QString("HINTMASK_EXT");
    case SYNCPT_THRESH_CPU0_INT_STATUS_OFFSET:
        return QString("SYNCPT_THRESH_CPU0_INT_STATUS");
    case SYNCPT_THRESH_CPU1_INT_STATUS_OFFSET:
        return QString("SYNCPT_THRESH_CPU1_INT_STATUS");
    case SYNCPT_THRESH_INT_MASK_OFFSET:
        return QString("SYNCPT_THRESH_INT_MASK");
    case SYNCPT_THRESH_INT_MASK_1_OFFSET:
        return QString("SYNCPT_THRESH_INT_MASK_1");
    case SYNCPT_THRESH_INT_DISABLE_OFFSET:
        return QString("SYNCPT_THRESH_INT_DISABLE");
    case SYNCPT_THRESH_INT_ENABLE_CPU0_OFFSET:
        return QString("SYNCPT_THRESH_INT_ENABLE_CPU0");
    case SYNCPT_THRESH_INT_ENABLE_CPU1_OFFSET:
        return QString("SYNCPT_THRESH_INT_ENABLE_CPU1");
    case CF0_SETUP_OFFSET:
        return QString("CF0_SETUP");
    case CF1_SETUP_OFFSET:
        return QString("CF1_SETUP");
    case CF2_SETUP_OFFSET:
        return QString("CF2_SETUP");
    case CF3_SETUP_OFFSET:
        return QString("CF3_SETUP");
    case CF4_SETUP_OFFSET:
        return QString("CF4_SETUP");
    case CF5_SETUP_OFFSET:
        return QString("CF5_SETUP");
    case CF6_SETUP_OFFSET:
        return QString("CF6_SETUP");
    case CF7_SETUP_OFFSET:
        return QString("CF7_SETUP");
    case CF_SETUPDONE_OFFSET:
        return QString("CF_SETUPDONE");
    case CMDPROC_CTRL_OFFSET:
        return QString("CMDPROC_CTRL");
    case CMDPROC_STAT_OFFSET:
        return QString("CMDPROC_STAT");
    case CMDPROC_STOP_OFFSET:
        return QString("CMDPROC_STOP");
    case CH_TEARDOWN_OFFSET:
        return QString("CH_TEARDOWN");
    case MOD_TEARDOWN_OFFSET:
        return QString("MOD_TEARDOWN");
    case CH0_STATUS_OFFSET:
        return QString("CH0_STATUS");
    case CH1_STATUS_OFFSET:
        return QString("CH1_STATUS");
    case CH2_STATUS_OFFSET:
        return QString("CH2_STATUS");
    case CH3_STATUS_OFFSET:
        return QString("CH3_STATUS");
    case CH4_STATUS_OFFSET:
        return QString("CH4_STATUS");
    case CH5_STATUS_OFFSET:
        return QString("CH5_STATUS");
    case CH6_STATUS_OFFSET:
        return QString("CH6_STATUS");
    case CH7_STATUS_OFFSET:
        return QString("CH7_STATUS");
    case DISPLAY_STATUS_OFFSET:
        return QString("DISPLAY_STATUS");
    case DISPLAYB_STATUS_OFFSET:
        return QString("DISPLAYB_STATUS");
    case EPP_STATUS_OFFSET:
        return QString("EPP_STATUS");
    case GR3D_STATUS_OFFSET:
        return QString("GR3D_STATUS");
    case ISP_STATUS_OFFSET:
        return QString("ISP_STATUS");
    case MPE_STATUS_OFFSET:
        return QString("MPE_STATUS");
    case TVO_STATUS_OFFSET:
        return QString("TVO_STATUS");
    case DSI_STATUS_OFFSET:
        return QString("DSI_STATUS");
    case HDMI_STATUS_OFFSET:
        return QString("HDMI_STATUS");
    case VI_STATUS_OFFSET:
        return QString("VI_STATUS");
    case GR2D_STATUS_OFFSET:
        return QString("GR2D_STATUS");
    case DIRECT_MODULE_CONFIG_OFFSET:
        return QString("DIRECT_MODULE_CONFIG");
    case USEC_CLK_OFFSET:
        return QString("USEC_CLK");
    case CTXSW_TIMEOUT_CFG_OFFSET:
        return QString("CTXSW_TIMEOUT_CFG");
    case INDREG_DMA_CTRL_OFFSET:
        return QString("INDREG_DMA_CTRL");
    case CHANNEL_PRIORITY_OFFSET:
        return QString("CHANNEL_PRIORITY");
    case CDMA_ASM_TIMEOUT_OFFSET:
        return QString("CDMA_ASM_TIMEOUT");
    case CDMA_MISC_OFFSET:
        return QString("CDMA_MISC");
    case IP_BUSY_TIMEOUT_OFFSET:
        return QString("IP_BUSY_TIMEOUT");
    case IP_READ_TIMEOUT_ADDR_OFFSET:
        return QString("IP_READ_TIMEOUT_ADDR");
    case IP_WRITE_TIMEOUT_ADDR_OFFSET:
        return QString("IP_WRITE_TIMEOUT_ADDR");
    case MCCIF_THCTRL_OFFSET:
        return QString("MCCIF_THCTRL");
    case HC_MCCIF_FIFOCTRL_OFFSET:
        return QString("HC_MCCIF_FIFOCTRL");
    case TIMEOUT_WCOAL_HC_OFFSET:
        return QString("TIMEOUT_WCOAL_HC");
    case HWLOCK0_OFFSET:
        return QString("HWLOCK0");
    case HWLOCK1_OFFSET:
        return QString("HWLOCK1");
    case HWLOCK2_OFFSET:
        return QString("HWLOCK2");
    case HWLOCK3_OFFSET:
        return QString("HWLOCK3");
    case HWLOCK4_OFFSET:
        return QString("HWLOCK4");
    case HWLOCK5_OFFSET:
        return QString("HWLOCK5");
    case HWLOCK6_OFFSET:
        return QString("HWLOCK6");
    case HWLOCK7_OFFSET:
        return QString("HWLOCK7");
    case MLOCK_OFFSET:
        return QString("MLOCK");
    case MLOCK_1_OFFSET:
        return QString("MLOCK_1");
    case MLOCK_2_OFFSET:
        return QString("MLOCK_2");
    case MLOCK_3_OFFSET:
        return QString("MLOCK_3");
    case MLOCK_4_OFFSET:
        return QString("MLOCK_4");
    case MLOCK_5_OFFSET:
        return QString("MLOCK_5");
    case MLOCK_6_OFFSET:
        return QString("MLOCK_6");
    case MLOCK_7_OFFSET:
        return QString("MLOCK_7");
    case MLOCK_8_OFFSET:
        return QString("MLOCK_8");
    case MLOCK_9_OFFSET:
        return QString("MLOCK_9");
    case MLOCK_10_OFFSET:
        return QString("MLOCK_10");
    case MLOCK_11_OFFSET:
        return QString("MLOCK_11");
    case MLOCK_12_OFFSET:
        return QString("MLOCK_12");
    case MLOCK_13_OFFSET:
        return QString("MLOCK_13");
    case MLOCK_14_OFFSET:
        return QString("MLOCK_14");
    case MLOCK_15_OFFSET:
        return QString("MLOCK_15");
    case MLOCK_OWNER_OFFSET:
        return QString("MLOCK_OWNER");
    case MLOCK_OWNER_1_OFFSET:
        return QString("MLOCK_OWNER_1");
    case MLOCK_OWNER_2_OFFSET:
        return QString("MLOCK_OWNER_2");
    case MLOCK_OWNER_3_OFFSET:
        return QString("MLOCK_OWNER_3");
    case MLOCK_OWNER_4_OFFSET:
        return QString("MLOCK_OWNER_4");
    case MLOCK_OWNER_5_OFFSET:
        return QString("MLOCK_OWNER_5");
    case MLOCK_OWNER_6_OFFSET:
        return QString("MLOCK_OWNER_6");
    case MLOCK_OWNER_7_OFFSET:
        return QString("MLOCK_OWNER_7");
    case MLOCK_OWNER_8_OFFSET:
        return QString("MLOCK_OWNER_8");
    case MLOCK_OWNER_9_OFFSET:
        return QString("MLOCK_OWNER_9");
    case MLOCK_OWNER_10_OFFSET:
        return QString("MLOCK_OWNER_10");
    case MLOCK_OWNER_11_OFFSET:
        return QString("MLOCK_OWNER_11");
    case MLOCK_OWNER_12_OFFSET:
        return QString("MLOCK_OWNER_12");
    case MLOCK_OWNER_13_OFFSET:
        return QString("MLOCK_OWNER_13");
    case MLOCK_OWNER_14_OFFSET:
        return QString("MLOCK_OWNER_14");
    case MLOCK_OWNER_15_OFFSET:
        return QString("MLOCK_OWNER_15");
    case MLOCK_ERROR_OFFSET:
        return QString("MLOCK_ERROR");
    case SYNCPT_OFFSET:
        return QString("SYNCPT");
    case SYNCPT_1_OFFSET:
        return QString("SYNCPT_1");
    case SYNCPT_2_OFFSET:
        return QString("SYNCPT_2");
    case SYNCPT_3_OFFSET:
        return QString("SYNCPT_3");
    case SYNCPT_4_OFFSET:
        return QString("SYNCPT_4");
    case SYNCPT_5_OFFSET:
        return QString("SYNCPT_5");
    case SYNCPT_6_OFFSET:
        return QString("SYNCPT_6");
    case SYNCPT_7_OFFSET:
        return QString("SYNCPT_7");
    case SYNCPT_8_OFFSET:
        return QString("SYNCPT_8");
    case SYNCPT_9_OFFSET:
        return QString("SYNCPT_9");
    case SYNCPT_10_OFFSET:
        return QString("SYNCPT_10");
    case SYNCPT_11_OFFSET:
        return QString("SYNCPT_11");
    case SYNCPT_12_OFFSET:
        return QString("SYNCPT_12");
    case SYNCPT_13_OFFSET:
        return QString("SYNCPT_13");
    case SYNCPT_14_OFFSET:
        return QString("SYNCPT_14");
    case SYNCPT_15_OFFSET:
        return QString("SYNCPT_15");
    case SYNCPT_16_OFFSET:
        return QString("SYNCPT_16");
    case SYNCPT_17_OFFSET:
        return QString("SYNCPT_17");
    case SYNCPT_18_OFFSET:
        return QString("SYNCPT_18");
    case SYNCPT_19_OFFSET:
        return QString("SYNCPT_19");
    case SYNCPT_20_OFFSET:
        return QString("SYNCPT_20");
    case SYNCPT_21_OFFSET:
        return QString("SYNCPT_21");
    case SYNCPT_22_OFFSET:
        return QString("SYNCPT_22");
    case SYNCPT_23_OFFSET:
        return QString("SYNCPT_23");
    case SYNCPT_24_OFFSET:
        return QString("SYNCPT_24");
    case SYNCPT_25_OFFSET:
        return QString("SYNCPT_25");
    case SYNCPT_26_OFFSET:
        return QString("SYNCPT_26");
    case SYNCPT_27_OFFSET:
        return QString("SYNCPT_27");
    case SYNCPT_28_OFFSET:
        return QString("SYNCPT_28");
    case SYNCPT_29_OFFSET:
        return QString("SYNCPT_29");
    case SYNCPT_30_OFFSET:
        return QString("SYNCPT_30");
    case SYNCPT_31_OFFSET:
        return QString("SYNCPT_31");
    case SYNCPT_INT_THRESH_OFFSET:
        return QString("SYNCPT_INT_THRESH");
    case SYNCPT_INT_THRESH_1_OFFSET:
        return QString("SYNCPT_INT_THRESH_1");
    case SYNCPT_INT_THRESH_2_OFFSET:
        return QString("SYNCPT_INT_THRESH_2");
    case SYNCPT_INT_THRESH_3_OFFSET:
        return QString("SYNCPT_INT_THRESH_3");
    case SYNCPT_INT_THRESH_4_OFFSET:
        return QString("SYNCPT_INT_THRESH_4");
    case SYNCPT_INT_THRESH_5_OFFSET:
        return QString("SYNCPT_INT_THRESH_5");
    case SYNCPT_INT_THRESH_6_OFFSET:
        return QString("SYNCPT_INT_THRESH_6");
    case SYNCPT_INT_THRESH_7_OFFSET:
        return QString("SYNCPT_INT_THRESH_7");
    case SYNCPT_INT_THRESH_8_OFFSET:
        return QString("SYNCPT_INT_THRESH_8");
    case SYNCPT_INT_THRESH_9_OFFSET:
        return QString("SYNCPT_INT_THRESH_9");
    case SYNCPT_INT_THRESH_10_OFFSET:
        return QString("SYNCPT_INT_THRESH_10");
    case SYNCPT_INT_THRESH_11_OFFSET:
        return QString("SYNCPT_INT_THRESH_11");
    case SYNCPT_INT_THRESH_12_OFFSET:
        return QString("SYNCPT_INT_THRESH_12");
    case SYNCPT_INT_THRESH_13_OFFSET:
        return QString("SYNCPT_INT_THRESH_13");
    case SYNCPT_INT_THRESH_14_OFFSET:
        return QString("SYNCPT_INT_THRESH_14");
    case SYNCPT_INT_THRESH_15_OFFSET:
        return QString("SYNCPT_INT_THRESH_15");
    case SYNCPT_INT_THRESH_16_OFFSET:
        return QString("SYNCPT_INT_THRESH_16");
    case SYNCPT_INT_THRESH_17_OFFSET:
        return QString("SYNCPT_INT_THRESH_17");
    case SYNCPT_INT_THRESH_18_OFFSET:
        return QString("SYNCPT_INT_THRESH_18");
    case SYNCPT_INT_THRESH_19_OFFSET:
        return QString("SYNCPT_INT_THRESH_19");
    case SYNCPT_INT_THRESH_20_OFFSET:
        return QString("SYNCPT_INT_THRESH_20");
    case SYNCPT_INT_THRESH_21_OFFSET:
        return QString("SYNCPT_INT_THRESH_21");
    case SYNCPT_INT_THRESH_22_OFFSET:
        return QString("SYNCPT_INT_THRESH_22");
    case SYNCPT_INT_THRESH_23_OFFSET:
        return QString("SYNCPT_INT_THRESH_23");
    case SYNCPT_INT_THRESH_24_OFFSET:
        return QString("SYNCPT_INT_THRESH_24");
    case SYNCPT_INT_THRESH_25_OFFSET:
        return QString("SYNCPT_INT_THRESH_25");
    case SYNCPT_INT_THRESH_26_OFFSET:
        return QString("SYNCPT_INT_THRESH_26");
    case SYNCPT_INT_THRESH_27_OFFSET:
        return QString("SYNCPT_INT_THRESH_27");
    case SYNCPT_INT_THRESH_28_OFFSET:
        return QString("SYNCPT_INT_THRESH_28");
    case SYNCPT_INT_THRESH_29_OFFSET:
        return QString("SYNCPT_INT_THRESH_29");
    case SYNCPT_INT_THRESH_30_OFFSET:
        return QString("SYNCPT_INT_THRESH_30");
    case SYNCPT_INT_THRESH_31_OFFSET:
        return QString("SYNCPT_INT_THRESH_31");
    case SYNCPT_BASE_OFFSET:
        return QString("SYNCPT_BASE");
    case SYNCPT_BASE_1_OFFSET:
        return QString("SYNCPT_BASE_1");
    case SYNCPT_BASE_2_OFFSET:
        return QString("SYNCPT_BASE_2");
    case SYNCPT_BASE_3_OFFSET:
        return QString("SYNCPT_BASE_3");
    case SYNCPT_BASE_4_OFFSET:
        return QString("SYNCPT_BASE_4");
    case SYNCPT_BASE_5_OFFSET:
        return QString("SYNCPT_BASE_5");
    case SYNCPT_BASE_6_OFFSET:
        return QString("SYNCPT_BASE_6");
    case SYNCPT_BASE_7_OFFSET:
        return QString("SYNCPT_BASE_7");
    case SYNCPT_CPU_INCR_OFFSET:
        return QString("SYNCPT_CPU_INCR");
    case CBREAD0_OFFSET:
        return QString("CBREAD0");
    case CBREAD1_OFFSET:
        return QString("CBREAD1");
    case CBREAD2_OFFSET:
        return QString("CBREAD2");
    case CBREAD3_OFFSET:
        return QString("CBREAD3");
    case CBREAD4_OFFSET:
        return QString("CBREAD4");
    case CBREAD5_OFFSET:
        return QString("CBREAD5");
    case CBREAD6_OFFSET:
        return QString("CBREAD6");
    case CBREAD7_OFFSET:
        return QString("CBREAD7");
    case REGF_DATA_OFFSET:
        return QString("REGF_DATA");
    case REGF_ADDR_OFFSET:
        return QString("REGF_ADDR");
    case WAITOVR_OFFSET:
        return QString("WAITOVR");
    case CFPEEK_CTRL_OFFSET:
        return QString("CFPEEK_CTRL");
    case CFPEEK_READ_OFFSET:
        return QString("CFPEEK_READ");
    case CFPEEK_PTRS_OFFSET:
        return QString("CFPEEK_PTRS");
    case CBSTAT0_OFFSET:
        return QString("CBSTAT0");
    case CBSTAT1_OFFSET:
        return QString("CBSTAT1");
    case CBSTAT2_OFFSET:
        return QString("CBSTAT2");
    case CBSTAT3_OFFSET:
        return QString("CBSTAT3");
    case CBSTAT4_OFFSET:
        return QString("CBSTAT4");
    case CBSTAT5_OFFSET:
        return QString("CBSTAT5");
    case CBSTAT6_OFFSET:
        return QString("CBSTAT6");
    case CBSTAT7_OFFSET:
        return QString("CBSTAT7");
    case CDMA_STATS_WORDS_FETCHED_OFFSET:
        return QString("CDMA_STATS_WORDS_FETCHED");
    case CDMA_STATS_WORDS_DISCARDED_OFFSET:
        return QString("CDMA_STATS_WORDS_DISCARDED");
    case CFG_OFFSET:
        return QString("CFG");
    case RDMA_MISC_OFFSET:
        return QString("RDMA_MISC");
    case RDMA_ARB_COUNT_OFFSET:
        return QString("RDMA_ARB_COUNT");
    case RDMA_CONFIG_OFFSET:
        return QString("RDMA_CONFIG");
    case RDMA_WRAP_OFFSET:
        return QString("RDMA_WRAP");
    case RDMA_STATUS0_OFFSET:
        return QString("RDMA_STATUS0");
    case RDMA_BUFFER_THRESHOLD0_OFFSET:
        return QString("RDMA_BUFFER_THRESHOLD0");
    case RDMA_CONF0_OFFSET:
        return QString("RDMA_CONF0");
    case RDMA_SWAP0_OFFSET:
        return QString("RDMA_SWAP0");
    case RDMA_LINE0_OFFSET:
        return QString("RDMA_LINE0");
    case RDMA_CLID0_OFFSET:
        return QString("RDMA_CLID0");
    case RDMA_BADDR0_OFFSET:
        return QString("RDMA_BADDR0");
    case RDMA_DMATRIGGER0_OFFSET:
        return QString("RDMA_DMATRIGGER0");

    default:
        break;
    }

    qDebug() << QString().sprintf("HOST1X_SYNC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Host1x_syncDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset & 0xfff) {
    case INTSTATUS_OFFSET:
        fill_intstatus_details(value, new_value);
        break;
    case INTMASK_OFFSET:
        fill_intmask_details(value, new_value);
        break;
    case INTC0MASK_OFFSET:
        fill_intc0mask_details(value, new_value);
        break;
    case INTC1MASK_OFFSET:
        fill_intc1mask_details(value, new_value);
        break;
    case HINTSTATUS_OFFSET:
        fill_hintstatus_details(value, new_value);
        break;
    case HINTMASK_OFFSET:
        fill_hintmask_details(value, new_value);
        break;
    case HINTSTATUS_EXT_OFFSET:
        fill_hintstatus_ext_details(value, new_value);
        break;
    case HINTMASK_EXT_OFFSET:
        fill_hintmask_ext_details(value, new_value);
        break;
    case SYNCPT_THRESH_CPU0_INT_STATUS_OFFSET:
        fill_syncpt_thresh_cpu0_int_status_details(value, new_value);
        break;
    case SYNCPT_THRESH_CPU1_INT_STATUS_OFFSET:
        fill_syncpt_thresh_cpu1_int_status_details(value, new_value);
        break;
    case SYNCPT_THRESH_INT_MASK_OFFSET:
        fill_syncpt_thresh_int_mask_details(value, new_value);
        break;
    case SYNCPT_THRESH_INT_MASK_1_OFFSET:
        fill_syncpt_thresh_int_mask_1_details(value, new_value);
        break;
    case SYNCPT_THRESH_INT_DISABLE_OFFSET:
        fill_syncpt_thresh_int_disable_details(value, new_value);
        break;
    case SYNCPT_THRESH_INT_ENABLE_CPU0_OFFSET:
        fill_syncpt_thresh_int_enable_cpu0_details(value, new_value);
        break;
    case SYNCPT_THRESH_INT_ENABLE_CPU1_OFFSET:
        fill_syncpt_thresh_int_enable_cpu1_details(value, new_value);
        break;
    case CF0_SETUP_OFFSET:
        fill_cf0_setup_details(value, new_value);
        break;
    case CF1_SETUP_OFFSET:
        fill_cf1_setup_details(value, new_value);
        break;
    case CF2_SETUP_OFFSET:
        fill_cf2_setup_details(value, new_value);
        break;
    case CF3_SETUP_OFFSET:
        fill_cf3_setup_details(value, new_value);
        break;
    case CF4_SETUP_OFFSET:
        fill_cf4_setup_details(value, new_value);
        break;
    case CF5_SETUP_OFFSET:
        fill_cf5_setup_details(value, new_value);
        break;
    case CF6_SETUP_OFFSET:
        fill_cf6_setup_details(value, new_value);
        break;
    case CF7_SETUP_OFFSET:
        fill_cf7_setup_details(value, new_value);
        break;
    case CF_SETUPDONE_OFFSET:
        fill_cf_setupdone_details(value, new_value);
        break;
    case CMDPROC_CTRL_OFFSET:
        fill_cmdproc_ctrl_details(value, new_value);
        break;
    case CMDPROC_STAT_OFFSET:
        fill_cmdproc_stat_details(value, new_value);
        break;
    case CMDPROC_STOP_OFFSET:
        fill_cmdproc_stop_details(value, new_value);
        break;
    case CH_TEARDOWN_OFFSET:
        fill_ch_teardown_details(value, new_value);
        break;
    case MOD_TEARDOWN_OFFSET:
        fill_mod_teardown_details(value, new_value);
        break;
    case CH0_STATUS_OFFSET:
        fill_ch0_status_details(value, new_value);
        break;
    case CH1_STATUS_OFFSET:
        fill_ch1_status_details(value, new_value);
        break;
    case CH2_STATUS_OFFSET:
        fill_ch2_status_details(value, new_value);
        break;
    case CH3_STATUS_OFFSET:
        fill_ch3_status_details(value, new_value);
        break;
    case CH4_STATUS_OFFSET:
        fill_ch4_status_details(value, new_value);
        break;
    case CH5_STATUS_OFFSET:
        fill_ch5_status_details(value, new_value);
        break;
    case CH6_STATUS_OFFSET:
        fill_ch6_status_details(value, new_value);
        break;
    case CH7_STATUS_OFFSET:
        fill_ch7_status_details(value, new_value);
        break;
    case DISPLAY_STATUS_OFFSET:
        fill_display_status_details(value, new_value);
        break;
    case DISPLAYB_STATUS_OFFSET:
        fill_displayb_status_details(value, new_value);
        break;
    case EPP_STATUS_OFFSET:
        fill_epp_status_details(value, new_value);
        break;
    case GR3D_STATUS_OFFSET:
        fill_gr3d_status_details(value, new_value);
        break;
    case ISP_STATUS_OFFSET:
        fill_isp_status_details(value, new_value);
        break;
    case MPE_STATUS_OFFSET:
        fill_mpe_status_details(value, new_value);
        break;
    case TVO_STATUS_OFFSET:
        fill_tvo_status_details(value, new_value);
        break;
    case DSI_STATUS_OFFSET:
        fill_dsi_status_details(value, new_value);
        break;
    case HDMI_STATUS_OFFSET:
        fill_hdmi_status_details(value, new_value);
        break;
    case VI_STATUS_OFFSET:
        fill_vi_status_details(value, new_value);
        break;
    case GR2D_STATUS_OFFSET:
        fill_gr2d_status_details(value, new_value);
        break;
    case DIRECT_MODULE_CONFIG_OFFSET:
        fill_direct_module_config_details(value, new_value);
        break;
    case USEC_CLK_OFFSET:
        fill_usec_clk_details(value, new_value);
        break;
    case CTXSW_TIMEOUT_CFG_OFFSET:
        fill_ctxsw_timeout_cfg_details(value, new_value);
        break;
    case INDREG_DMA_CTRL_OFFSET:
        fill_indreg_dma_ctrl_details(value, new_value);
        break;
    case CHANNEL_PRIORITY_OFFSET:
        fill_channel_priority_details(value, new_value);
        break;
    case CDMA_ASM_TIMEOUT_OFFSET:
        fill_cdma_asm_timeout_details(value, new_value);
        break;
    case CDMA_MISC_OFFSET:
        fill_cdma_misc_details(value, new_value);
        break;
    case IP_BUSY_TIMEOUT_OFFSET:
        fill_ip_busy_timeout_details(value, new_value);
        break;
    case IP_READ_TIMEOUT_ADDR_OFFSET:
        fill_ip_read_timeout_addr_details(value, new_value);
        break;
    case IP_WRITE_TIMEOUT_ADDR_OFFSET:
        fill_ip_write_timeout_addr_details(value, new_value);
        break;
    case MCCIF_THCTRL_OFFSET:
        fill_mccif_thctrl_details(value, new_value);
        break;
    case HC_MCCIF_FIFOCTRL_OFFSET:
        fill_hc_mccif_fifoctrl_details(value, new_value);
        break;
    case TIMEOUT_WCOAL_HC_OFFSET:
        fill_timeout_wcoal_hc_details(value, new_value);
        break;
    case HWLOCK0_OFFSET:
        fill_hwlock0_details(value, new_value);
        break;
    case HWLOCK1_OFFSET:
        fill_hwlock1_details(value, new_value);
        break;
    case HWLOCK2_OFFSET:
        fill_hwlock2_details(value, new_value);
        break;
    case HWLOCK3_OFFSET:
        fill_hwlock3_details(value, new_value);
        break;
    case HWLOCK4_OFFSET:
        fill_hwlock4_details(value, new_value);
        break;
    case HWLOCK5_OFFSET:
        fill_hwlock5_details(value, new_value);
        break;
    case HWLOCK6_OFFSET:
        fill_hwlock6_details(value, new_value);
        break;
    case HWLOCK7_OFFSET:
        fill_hwlock7_details(value, new_value);
        break;
    case MLOCK_OFFSET:
        fill_mlock_details(value, new_value);
        break;
    case MLOCK_1_OFFSET:
        fill_mlock_1_details(value, new_value);
        break;
    case MLOCK_2_OFFSET:
        fill_mlock_2_details(value, new_value);
        break;
    case MLOCK_3_OFFSET:
        fill_mlock_3_details(value, new_value);
        break;
    case MLOCK_4_OFFSET:
        fill_mlock_4_details(value, new_value);
        break;
    case MLOCK_5_OFFSET:
        fill_mlock_5_details(value, new_value);
        break;
    case MLOCK_6_OFFSET:
        fill_mlock_6_details(value, new_value);
        break;
    case MLOCK_7_OFFSET:
        fill_mlock_7_details(value, new_value);
        break;
    case MLOCK_8_OFFSET:
        fill_mlock_8_details(value, new_value);
        break;
    case MLOCK_9_OFFSET:
        fill_mlock_9_details(value, new_value);
        break;
    case MLOCK_10_OFFSET:
        fill_mlock_10_details(value, new_value);
        break;
    case MLOCK_11_OFFSET:
        fill_mlock_11_details(value, new_value);
        break;
    case MLOCK_12_OFFSET:
        fill_mlock_12_details(value, new_value);
        break;
    case MLOCK_13_OFFSET:
        fill_mlock_13_details(value, new_value);
        break;
    case MLOCK_14_OFFSET:
        fill_mlock_14_details(value, new_value);
        break;
    case MLOCK_15_OFFSET:
        fill_mlock_15_details(value, new_value);
        break;
    case MLOCK_OWNER_OFFSET:
        fill_mlock_owner_details(value, new_value);
        break;
    case MLOCK_OWNER_1_OFFSET:
        fill_mlock_owner_1_details(value, new_value);
        break;
    case MLOCK_OWNER_2_OFFSET:
        fill_mlock_owner_2_details(value, new_value);
        break;
    case MLOCK_OWNER_3_OFFSET:
        fill_mlock_owner_3_details(value, new_value);
        break;
    case MLOCK_OWNER_4_OFFSET:
        fill_mlock_owner_4_details(value, new_value);
        break;
    case MLOCK_OWNER_5_OFFSET:
        fill_mlock_owner_5_details(value, new_value);
        break;
    case MLOCK_OWNER_6_OFFSET:
        fill_mlock_owner_6_details(value, new_value);
        break;
    case MLOCK_OWNER_7_OFFSET:
        fill_mlock_owner_7_details(value, new_value);
        break;
    case MLOCK_OWNER_8_OFFSET:
        fill_mlock_owner_8_details(value, new_value);
        break;
    case MLOCK_OWNER_9_OFFSET:
        fill_mlock_owner_9_details(value, new_value);
        break;
    case MLOCK_OWNER_10_OFFSET:
        fill_mlock_owner_10_details(value, new_value);
        break;
    case MLOCK_OWNER_11_OFFSET:
        fill_mlock_owner_11_details(value, new_value);
        break;
    case MLOCK_OWNER_12_OFFSET:
        fill_mlock_owner_12_details(value, new_value);
        break;
    case MLOCK_OWNER_13_OFFSET:
        fill_mlock_owner_13_details(value, new_value);
        break;
    case MLOCK_OWNER_14_OFFSET:
        fill_mlock_owner_14_details(value, new_value);
        break;
    case MLOCK_OWNER_15_OFFSET:
        fill_mlock_owner_15_details(value, new_value);
        break;
    case MLOCK_ERROR_OFFSET:
        fill_mlock_error_details(value, new_value);
        break;
    case SYNCPT_OFFSET:
        fill_syncpt_details(value, new_value);
        break;
    case SYNCPT_1_OFFSET:
        fill_syncpt_1_details(value, new_value);
        break;
    case SYNCPT_2_OFFSET:
        fill_syncpt_2_details(value, new_value);
        break;
    case SYNCPT_3_OFFSET:
        fill_syncpt_3_details(value, new_value);
        break;
    case SYNCPT_4_OFFSET:
        fill_syncpt_4_details(value, new_value);
        break;
    case SYNCPT_5_OFFSET:
        fill_syncpt_5_details(value, new_value);
        break;
    case SYNCPT_6_OFFSET:
        fill_syncpt_6_details(value, new_value);
        break;
    case SYNCPT_7_OFFSET:
        fill_syncpt_7_details(value, new_value);
        break;
    case SYNCPT_8_OFFSET:
        fill_syncpt_8_details(value, new_value);
        break;
    case SYNCPT_9_OFFSET:
        fill_syncpt_9_details(value, new_value);
        break;
    case SYNCPT_10_OFFSET:
        fill_syncpt_10_details(value, new_value);
        break;
    case SYNCPT_11_OFFSET:
        fill_syncpt_11_details(value, new_value);
        break;
    case SYNCPT_12_OFFSET:
        fill_syncpt_12_details(value, new_value);
        break;
    case SYNCPT_13_OFFSET:
        fill_syncpt_13_details(value, new_value);
        break;
    case SYNCPT_14_OFFSET:
        fill_syncpt_14_details(value, new_value);
        break;
    case SYNCPT_15_OFFSET:
        fill_syncpt_15_details(value, new_value);
        break;
    case SYNCPT_16_OFFSET:
        fill_syncpt_16_details(value, new_value);
        break;
    case SYNCPT_17_OFFSET:
        fill_syncpt_17_details(value, new_value);
        break;
    case SYNCPT_18_OFFSET:
        fill_syncpt_18_details(value, new_value);
        break;
    case SYNCPT_19_OFFSET:
        fill_syncpt_19_details(value, new_value);
        break;
    case SYNCPT_20_OFFSET:
        fill_syncpt_20_details(value, new_value);
        break;
    case SYNCPT_21_OFFSET:
        fill_syncpt_21_details(value, new_value);
        break;
    case SYNCPT_22_OFFSET:
        fill_syncpt_22_details(value, new_value);
        break;
    case SYNCPT_23_OFFSET:
        fill_syncpt_23_details(value, new_value);
        break;
    case SYNCPT_24_OFFSET:
        fill_syncpt_24_details(value, new_value);
        break;
    case SYNCPT_25_OFFSET:
        fill_syncpt_25_details(value, new_value);
        break;
    case SYNCPT_26_OFFSET:
        fill_syncpt_26_details(value, new_value);
        break;
    case SYNCPT_27_OFFSET:
        fill_syncpt_27_details(value, new_value);
        break;
    case SYNCPT_28_OFFSET:
        fill_syncpt_28_details(value, new_value);
        break;
    case SYNCPT_29_OFFSET:
        fill_syncpt_29_details(value, new_value);
        break;
    case SYNCPT_30_OFFSET:
        fill_syncpt_30_details(value, new_value);
        break;
    case SYNCPT_31_OFFSET:
        fill_syncpt_31_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_OFFSET:
        fill_syncpt_int_thresh_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_1_OFFSET:
        fill_syncpt_int_thresh_1_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_2_OFFSET:
        fill_syncpt_int_thresh_2_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_3_OFFSET:
        fill_syncpt_int_thresh_3_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_4_OFFSET:
        fill_syncpt_int_thresh_4_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_5_OFFSET:
        fill_syncpt_int_thresh_5_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_6_OFFSET:
        fill_syncpt_int_thresh_6_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_7_OFFSET:
        fill_syncpt_int_thresh_7_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_8_OFFSET:
        fill_syncpt_int_thresh_8_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_9_OFFSET:
        fill_syncpt_int_thresh_9_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_10_OFFSET:
        fill_syncpt_int_thresh_10_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_11_OFFSET:
        fill_syncpt_int_thresh_11_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_12_OFFSET:
        fill_syncpt_int_thresh_12_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_13_OFFSET:
        fill_syncpt_int_thresh_13_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_14_OFFSET:
        fill_syncpt_int_thresh_14_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_15_OFFSET:
        fill_syncpt_int_thresh_15_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_16_OFFSET:
        fill_syncpt_int_thresh_16_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_17_OFFSET:
        fill_syncpt_int_thresh_17_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_18_OFFSET:
        fill_syncpt_int_thresh_18_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_19_OFFSET:
        fill_syncpt_int_thresh_19_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_20_OFFSET:
        fill_syncpt_int_thresh_20_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_21_OFFSET:
        fill_syncpt_int_thresh_21_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_22_OFFSET:
        fill_syncpt_int_thresh_22_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_23_OFFSET:
        fill_syncpt_int_thresh_23_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_24_OFFSET:
        fill_syncpt_int_thresh_24_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_25_OFFSET:
        fill_syncpt_int_thresh_25_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_26_OFFSET:
        fill_syncpt_int_thresh_26_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_27_OFFSET:
        fill_syncpt_int_thresh_27_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_28_OFFSET:
        fill_syncpt_int_thresh_28_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_29_OFFSET:
        fill_syncpt_int_thresh_29_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_30_OFFSET:
        fill_syncpt_int_thresh_30_details(value, new_value);
        break;
    case SYNCPT_INT_THRESH_31_OFFSET:
        fill_syncpt_int_thresh_31_details(value, new_value);
        break;
    case SYNCPT_BASE_OFFSET:
        fill_syncpt_base_details(value, new_value);
        break;
    case SYNCPT_BASE_1_OFFSET:
        fill_syncpt_base_1_details(value, new_value);
        break;
    case SYNCPT_BASE_2_OFFSET:
        fill_syncpt_base_2_details(value, new_value);
        break;
    case SYNCPT_BASE_3_OFFSET:
        fill_syncpt_base_3_details(value, new_value);
        break;
    case SYNCPT_BASE_4_OFFSET:
        fill_syncpt_base_4_details(value, new_value);
        break;
    case SYNCPT_BASE_5_OFFSET:
        fill_syncpt_base_5_details(value, new_value);
        break;
    case SYNCPT_BASE_6_OFFSET:
        fill_syncpt_base_6_details(value, new_value);
        break;
    case SYNCPT_BASE_7_OFFSET:
        fill_syncpt_base_7_details(value, new_value);
        break;
    case SYNCPT_CPU_INCR_OFFSET:
        fill_syncpt_cpu_incr_details(value, new_value);
        break;
    case CBREAD0_OFFSET:
        fill_cbread0_details(value, new_value);
        break;
    case CBREAD1_OFFSET:
        fill_cbread1_details(value, new_value);
        break;
    case CBREAD2_OFFSET:
        fill_cbread2_details(value, new_value);
        break;
    case CBREAD3_OFFSET:
        fill_cbread3_details(value, new_value);
        break;
    case CBREAD4_OFFSET:
        fill_cbread4_details(value, new_value);
        break;
    case CBREAD5_OFFSET:
        fill_cbread5_details(value, new_value);
        break;
    case CBREAD6_OFFSET:
        fill_cbread6_details(value, new_value);
        break;
    case CBREAD7_OFFSET:
        fill_cbread7_details(value, new_value);
        break;
    case REGF_DATA_OFFSET:
        fill_regf_data_details(value, new_value);
        break;
    case REGF_ADDR_OFFSET:
        fill_regf_addr_details(value, new_value);
        break;
    case WAITOVR_OFFSET:
        fill_waitovr_details(value, new_value);
        break;
    case CFPEEK_CTRL_OFFSET:
        fill_cfpeek_ctrl_details(value, new_value);
        break;
    case CFPEEK_READ_OFFSET:
        fill_cfpeek_read_details(value, new_value);
        break;
    case CFPEEK_PTRS_OFFSET:
        fill_cfpeek_ptrs_details(value, new_value);
        break;
    case CBSTAT0_OFFSET:
        fill_cbstat0_details(value, new_value);
        break;
    case CBSTAT1_OFFSET:
        fill_cbstat1_details(value, new_value);
        break;
    case CBSTAT2_OFFSET:
        fill_cbstat2_details(value, new_value);
        break;
    case CBSTAT3_OFFSET:
        fill_cbstat3_details(value, new_value);
        break;
    case CBSTAT4_OFFSET:
        fill_cbstat4_details(value, new_value);
        break;
    case CBSTAT5_OFFSET:
        fill_cbstat5_details(value, new_value);
        break;
    case CBSTAT6_OFFSET:
        fill_cbstat6_details(value, new_value);
        break;
    case CBSTAT7_OFFSET:
        fill_cbstat7_details(value, new_value);
        break;
    case CDMA_STATS_WORDS_FETCHED_OFFSET:
        fill_cdma_stats_words_fetched_details(value, new_value);
        break;
    case CDMA_STATS_WORDS_DISCARDED_OFFSET:
        fill_cdma_stats_words_discarded_details(value, new_value);
        break;
    case CFG_OFFSET:
        fill_cfg_details(value, new_value);
        break;
    case RDMA_MISC_OFFSET:
        fill_rdma_misc_details(value, new_value);
        break;
    case RDMA_ARB_COUNT_OFFSET:
        fill_rdma_arb_count_details(value, new_value);
        break;
    case RDMA_CONFIG_OFFSET:
        fill_rdma_config_details(value, new_value);
        break;
    case RDMA_WRAP_OFFSET:
        fill_rdma_wrap_details(value, new_value);
        break;
    case RDMA_STATUS0_OFFSET:
        fill_rdma_status0_details(value, new_value);
        break;
    case RDMA_BUFFER_THRESHOLD0_OFFSET:
        fill_rdma_buffer_threshold0_details(value, new_value);
        break;
    case RDMA_CONF0_OFFSET:
        fill_rdma_conf0_details(value, new_value);
        break;
    case RDMA_SWAP0_OFFSET:
        fill_rdma_swap0_details(value, new_value);
        break;
    case RDMA_LINE0_OFFSET:
        fill_rdma_line0_details(value, new_value);
        break;
    case RDMA_CLID0_OFFSET:
        fill_rdma_clid0_details(value, new_value);
        break;
    case RDMA_BADDR0_OFFSET:
        fill_rdma_baddr0_details(value, new_value);
        break;
    case RDMA_DMATRIGGER0_OFFSET:
        fill_rdma_dmatrigger0_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
