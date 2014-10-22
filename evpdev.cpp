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

#include "evpdev.h"

#include <QDebug>

EvpDev::EvpDev(QObject *parent) :
    Device(parent)
{
}

#define EVP_RESET_VECTOR_OFFSET 0x0
#define EVP_RESET_VECTOR_UNDEFMASK 0x00000000
union evp_reset_vector_u {
    struct {
        unsigned int reset_vector:32;       /* RESET Exception Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_reset_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_reset_vector_u old_value_t = { .reg32 = value };
    const evp_reset_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: reset_vector:32",
              "RESET Exception Vector Pointer",
              32, old_value_t.reset_vector, new_value_t.reset_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_UNDEF_VECTOR_OFFSET 0x4
#define EVP_UNDEF_VECTOR_UNDEFMASK 0x00000000
union evp_undef_vector_u {
    struct {
        unsigned int undef_vector:32;       /* Undefined Exception Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_undef_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_undef_vector_u old_value_t = { .reg32 = value };
    const evp_undef_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undef_vector:32",
              "Undefined Exception Vector Pointer",
              32, old_value_t.undef_vector, new_value_t.undef_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_SWI_VECTOR_OFFSET 0x8
#define EVP_SWI_VECTOR_UNDEFMASK 0x00000000
union evp_swi_vector_u {
    struct {
        unsigned int swi_vector:32;         /* Software Interrupt Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_swi_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_swi_vector_u old_value_t = { .reg32 = value };
    const evp_swi_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: swi_vector:32",
              "Software Interrupt Vector Pointer",
              32, old_value_t.swi_vector, new_value_t.swi_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PREFETCH_ABORT_VECTOR_OFFSET 0xC
#define EVP_PREFETCH_ABORT_VECTOR_UNDEFMASK 0x00000000
union evp_prefetch_abort_vector_u {
    struct {
        unsigned int pre_abort_vector:32;   /* Code Prefetch ABORT Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_prefetch_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_prefetch_abort_vector_u old_value_t = { .reg32 = value };
    const evp_prefetch_abort_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pre_abort_vector:32",
              "Code Prefetch ABORT Vector Pointer",
              32, old_value_t.pre_abort_vector, new_value_t.pre_abort_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_DATA_ABORT_VECTOR_OFFSET 0x10
#define EVP_DATA_ABORT_VECTOR_UNDEFMASK 0x00000000
union evp_data_abort_vector_u {
    struct {
        unsigned int data_abort_vector:32;  /* Data ABORT Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_data_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_data_abort_vector_u old_value_t = { .reg32 = value };
    const evp_data_abort_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: data_abort_vector:32",
              "Data ABORT Vector Pointer",
              32, old_value_t.data_abort_vector, new_value_t.data_abort_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_RSVD_VECTOR_OFFSET 0x14
#define EVP_RSVD_VECTOR_UNDEFMASK 0x00000000
union evp_rsvd_vector_u {
    struct {
        unsigned int rsvd_vector:32;        /* Reserved Exception Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_rsvd_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_rsvd_vector_u old_value_t = { .reg32 = value };
    const evp_rsvd_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rsvd_vector:32",
              "Reserved Exception Vector Pointer",
              32, old_value_t.rsvd_vector, new_value_t.rsvd_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_IRQ_VECTOR_OFFSET 0x18
#define EVP_IRQ_VECTOR_UNDEFMASK 0x00000000
union evp_irq_vector_u {
    struct {
        unsigned int irq_vector:32;         /* IRQ Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_irq_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_irq_vector_u old_value_t = { .reg32 = value };
    const evp_irq_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: irq_vector:32",
              "IRQ Vector Pointer",
              32, old_value_t.irq_vector, new_value_t.irq_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_FIQ_VECTOR_OFFSET 0x1C
#define EVP_FIQ_VECTOR_UNDEFMASK 0x00000000
union evp_fiq_vector_u {
    struct {
        unsigned int fiq_vector:32;         /* FIQ Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_fiq_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_fiq_vector_u old_value_t = { .reg32 = value };
    const evp_fiq_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: fiq_vector:32",
              "FIQ Vector Pointer",
              32, old_value_t.fiq_vector, new_value_t.fiq_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_IRQ_STS_OFFSET 0x20
#define EVP_IRQ_STS_UNDEFMASK 0x00000000
union evp_irq_sts_u {
    struct {
        unsigned int irq_sts:32;            /* FFS (from lsb) IRQ index  (0x80 indicates no active IRQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_irq_sts_u old_value_t = { .reg32 = value };
    const evp_irq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: irq_sts:32",
              "FFS (from lsb) IRQ index  (0x80 indicates no active IRQ)",
              32, old_value_t.irq_sts, new_value_t.irq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_STS_OFFSET 0x24
#define EVP_PRI_IRQ_STS_UNDEFMASK 0x00000000
union evp_pri_irq_sts_u {
    struct {
        unsigned int pri_irq_sts:32;        /* Current highest priority active IRQ (0x80 indicates no active priority IRQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_sts_u old_value_t = { .reg32 = value };
    const evp_pri_irq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_sts:32",
              "Current highest priority active IRQ (0x80 indicates no active priority IRQ)",
              32, old_value_t.pri_irq_sts, new_value_t.pri_irq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_FIQ_STS_OFFSET 0x28
#define EVP_FIQ_STS_UNDEFMASK 0x00000000
union evp_fiq_sts_u {
    struct {
        unsigned int fiq_sts:32;            /* FFS (from lsb) FIQ index (0x80 indicates no active FIQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_fiq_sts_u old_value_t = { .reg32 = value };
    const evp_fiq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: fiq_sts:32",
              "FFS (from lsb) FIQ index (0x80 indicates no active FIQ)",
              32, old_value_t.fiq_sts, new_value_t.fiq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_STS_OFFSET 0x2C
#define EVP_PRI_FIQ_STS_UNDEFMASK 0x00000000
union evp_pri_fiq_sts_u {
    struct {
        unsigned int pri_fiq_sts:32;        /* Current highest priority active FIQ (0x80 indicates no active priority FIQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_sts_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_sts:32",
              "Current highest priority active FIQ (0x80 indicates no active priority FIQ)",
              32, old_value_t.pri_fiq_sts, new_value_t.pri_fiq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_0_OFFSET 0x40
#define EVP_PRI_IRQ_NUM_0_UNDEFMASK 0x00000000
union evp_pri_irq_num_0_u {
    struct {
        unsigned int pri_irq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_0_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_0:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_0, new_value_t.pri_irq_num_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_0_OFFSET 0x44
#define EVP_PRI_IRQ_VEC_0_UNDEFMASK 0x00000000
union evp_pri_irq_vec_0_u {
    struct {
        unsigned int pri_irq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_0_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_0:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_0, new_value_t.pri_irq_vec_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_1_OFFSET 0x48
#define EVP_PRI_IRQ_NUM_1_UNDEFMASK 0x00000000
union evp_pri_irq_num_1_u {
    struct {
        unsigned int pri_irq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_1_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_1:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_1, new_value_t.pri_irq_num_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_1_OFFSET 0x4C
#define EVP_PRI_IRQ_VEC_1_UNDEFMASK 0x00000000
union evp_pri_irq_vec_1_u {
    struct {
        unsigned int pri_irq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_1_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_1:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_1, new_value_t.pri_irq_vec_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_2_OFFSET 0x50
#define EVP_PRI_IRQ_NUM_2_UNDEFMASK 0x00000000
union evp_pri_irq_num_2_u {
    struct {
        unsigned int pri_irq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_2_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_2:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_2, new_value_t.pri_irq_num_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_2_OFFSET 0x54
#define EVP_PRI_IRQ_VEC_2_UNDEFMASK 0x00000000
union evp_pri_irq_vec_2_u {
    struct {
        unsigned int pri_irq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_2_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_2:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_2, new_value_t.pri_irq_vec_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_3_OFFSET 0x58
#define EVP_PRI_IRQ_NUM_3_UNDEFMASK 0x00000000
union evp_pri_irq_num_3_u {
    struct {
        unsigned int pri_irq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_3_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_3:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_3, new_value_t.pri_irq_num_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_3_OFFSET 0x5C
#define EVP_PRI_IRQ_VEC_3_UNDEFMASK 0x00000000
union evp_pri_irq_vec_3_u {
    struct {
        unsigned int pri_irq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_3_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_3:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_3, new_value_t.pri_irq_vec_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_4_OFFSET 0x60
#define EVP_PRI_IRQ_NUM_4_UNDEFMASK 0x00000000
union evp_pri_irq_num_4_u {
    struct {
        unsigned int pri_irq_num_4:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_4_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_4:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_4, new_value_t.pri_irq_num_4 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_4_OFFSET 0x64
#define EVP_PRI_IRQ_VEC_4_UNDEFMASK 0x00000000
union evp_pri_irq_vec_4_u {
    struct {
        unsigned int pri_irq_vec_4:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_4_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_4:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_4, new_value_t.pri_irq_vec_4 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_5_OFFSET 0x68
#define EVP_PRI_IRQ_NUM_5_UNDEFMASK 0x00000000
union evp_pri_irq_num_5_u {
    struct {
        unsigned int pri_irq_num_5:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_5_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_5:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_5, new_value_t.pri_irq_num_5 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_5_OFFSET 0x6C
#define EVP_PRI_IRQ_VEC_5_UNDEFMASK 0x00000000
union evp_pri_irq_vec_5_u {
    struct {
        unsigned int pri_irq_vec_5:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_5_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_5:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_5, new_value_t.pri_irq_vec_5 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_6_OFFSET 0x70
#define EVP_PRI_IRQ_NUM_6_UNDEFMASK 0x00000000
union evp_pri_irq_num_6_u {
    struct {
        unsigned int pri_irq_num_6:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_6_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_6:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_6, new_value_t.pri_irq_num_6 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_6_OFFSET 0x74
#define EVP_PRI_IRQ_VEC_6_UNDEFMASK 0x00000000
union evp_pri_irq_vec_6_u {
    struct {
        unsigned int pri_irq_vec_6:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_6_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_6:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_6, new_value_t.pri_irq_vec_6 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_NUM_7_OFFSET 0x78
#define EVP_PRI_IRQ_NUM_7_UNDEFMASK 0x00000000
union evp_pri_irq_num_7_u {
    struct {
        unsigned int pri_irq_num_7:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_num_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_num_7_u old_value_t = { .reg32 = value };
    const evp_pri_irq_num_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_7:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_7, new_value_t.pri_irq_num_7 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_IRQ_VEC_7_OFFSET 0x7C
#define EVP_PRI_IRQ_VEC_7_UNDEFMASK 0x00000000
union evp_pri_irq_vec_7_u {
    struct {
        unsigned int pri_irq_vec_7:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_irq_vec_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_irq_vec_7_u old_value_t = { .reg32 = value };
    const evp_pri_irq_vec_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_7:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_7, new_value_t.pri_irq_vec_7 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_NUM_0_OFFSET 0x80
#define EVP_PRI_FIQ_NUM_0_UNDEFMASK 0x00000000
union evp_pri_fiq_num_0_u {
    struct {
        unsigned int pri_fiq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_num_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_num_0_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_num_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_0:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_0, new_value_t.pri_fiq_num_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_VEC_0_OFFSET 0x84
#define EVP_PRI_FIQ_VEC_0_UNDEFMASK 0x00000000
union evp_pri_fiq_vec_0_u {
    struct {
        unsigned int pri_fiq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_vec_0_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_vec_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_0:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_0, new_value_t.pri_fiq_vec_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_NUM_1_OFFSET 0x88
#define EVP_PRI_FIQ_NUM_1_UNDEFMASK 0x00000000
union evp_pri_fiq_num_1_u {
    struct {
        unsigned int pri_fiq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_num_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_num_1_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_num_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_1:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_1, new_value_t.pri_fiq_num_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_VEC_1_OFFSET 0x8C
#define EVP_PRI_FIQ_VEC_1_UNDEFMASK 0x00000000
union evp_pri_fiq_vec_1_u {
    struct {
        unsigned int pri_fiq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_vec_1_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_vec_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_1:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_1, new_value_t.pri_fiq_vec_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_NUM_2_OFFSET 0x90
#define EVP_PRI_FIQ_NUM_2_UNDEFMASK 0x00000000
union evp_pri_fiq_num_2_u {
    struct {
        unsigned int pri_fiq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_num_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_num_2_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_num_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_2:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_2, new_value_t.pri_fiq_num_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_VEC_2_OFFSET 0x94
#define EVP_PRI_FIQ_VEC_2_UNDEFMASK 0x00000000
union evp_pri_fiq_vec_2_u {
    struct {
        unsigned int pri_fiq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_vec_2_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_vec_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_2:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_2, new_value_t.pri_fiq_vec_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_NUM_3_OFFSET 0x98
#define EVP_PRI_FIQ_NUM_3_UNDEFMASK 0x00000000
union evp_pri_fiq_num_3_u {
    struct {
        unsigned int pri_fiq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_num_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_num_3_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_num_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_3:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_3, new_value_t.pri_fiq_num_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_PRI_FIQ_VEC_3_OFFSET 0x9C
#define EVP_PRI_FIQ_VEC_3_UNDEFMASK 0x00000000
union evp_pri_fiq_vec_3_u {
    struct {
        unsigned int pri_fiq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_pri_fiq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_pri_fiq_vec_3_u old_value_t = { .reg32 = value };
    const evp_pri_fiq_vec_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_3:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_3, new_value_t.pri_fiq_vec_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_RESET_VECTOR_OFFSET 0x100
#define EVP_CPU_RESET_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_reset_vector_u {
    struct {
        unsigned int cpu_reset_vector:32;   /* RESET Exception Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_reset_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_reset_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_reset_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_reset_vector:32",
              "RESET Exception Vector Pointer",
              32, old_value_t.cpu_reset_vector, new_value_t.cpu_reset_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_UNDEF_VECTOR_OFFSET 0x104
#define EVP_CPU_UNDEF_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_undef_vector_u {
    struct {
        unsigned int cpu_undef_vector:32;   /* Undefined Exception Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_undef_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_undef_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_undef_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_undef_vector:32",
              "Undefined Exception Vector Pointer",
              32, old_value_t.cpu_undef_vector, new_value_t.cpu_undef_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_SWI_VECTOR_OFFSET 0x108
#define EVP_CPU_SWI_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_swi_vector_u {
    struct {
        unsigned int cpu_swi_vector:32;     /* Software Interrupt Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_swi_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_swi_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_swi_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_swi_vector:32",
              "Software Interrupt Vector Pointer",
              32, old_value_t.cpu_swi_vector, new_value_t.cpu_swi_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PREFETCH_ABORT_VECTOR_OFFSET 0x10C
#define EVP_CPU_PREFETCH_ABORT_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_prefetch_abort_vector_u {
    struct {
        unsigned int cpu_pre_abort_vector:32;/* Code Prefetch ABORT Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_prefetch_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_prefetch_abort_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_prefetch_abort_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_pre_abort_vector:32",
              "Code Prefetch ABORT Vector Pointer",
              32, old_value_t.cpu_pre_abort_vector, new_value_t.cpu_pre_abort_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_DATA_ABORT_VECTOR_OFFSET 0x110
#define EVP_CPU_DATA_ABORT_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_data_abort_vector_u {
    struct {
        unsigned int cpu_data_abort_vector:32;/* Data ABORT Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_data_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_data_abort_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_data_abort_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_data_abort_vector:32",
              "Data ABORT Vector Pointer",
              32, old_value_t.cpu_data_abort_vector, new_value_t.cpu_data_abort_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_RSVD_VECTOR_OFFSET 0x114
#define EVP_CPU_RSVD_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_rsvd_vector_u {
    struct {
        unsigned int cpu_rsvd_vector:32;    /* Reserved Exception Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_rsvd_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_rsvd_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_rsvd_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_rsvd_vector:32",
              "Reserved Exception Vector Pointer",
              32, old_value_t.cpu_rsvd_vector, new_value_t.cpu_rsvd_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_IRQ_VECTOR_OFFSET 0x118
#define EVP_CPU_IRQ_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_irq_vector_u {
    struct {
        unsigned int cpu_irq_vector:32;     /* IRQ Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_irq_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_irq_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_irq_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_irq_vector:32",
              "IRQ Vector Pointer",
              32, old_value_t.cpu_irq_vector, new_value_t.cpu_irq_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_FIQ_VECTOR_OFFSET 0x11C
#define EVP_CPU_FIQ_VECTOR_UNDEFMASK 0x00000000
union evp_cpu_fiq_vector_u {
    struct {
        unsigned int cpu_fiq_vector:32;     /* FIQ Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_fiq_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_fiq_vector_u old_value_t = { .reg32 = value };
    const evp_cpu_fiq_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_fiq_vector:32",
              "FIQ Vector Pointer",
              32, old_value_t.cpu_fiq_vector, new_value_t.cpu_fiq_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_IRQ_STS_OFFSET 0x120
#define EVP_CPU_IRQ_STS_UNDEFMASK 0x00000000
union evp_cpu_irq_sts_u {
    struct {
        unsigned int cpu_irq_sts:32;        /* FFS (from lsb) IRQ index  (0x80 indicates no active IRQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_irq_sts_u old_value_t = { .reg32 = value };
    const evp_cpu_irq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_irq_sts:32",
              "FFS (from lsb) IRQ index  (0x80 indicates no active IRQ)",
              32, old_value_t.cpu_irq_sts, new_value_t.cpu_irq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_STS_OFFSET 0x124
#define EVP_CPU_PRI_IRQ_STS_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_sts_u {
    struct {
        unsigned int cpu_pri_irq_sts:32;    /* Current highest priority active IRQ (0x80 indicates no active priority IRQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_sts_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_pri_irq_sts:32",
              "Current highest priority active IRQ (0x80 indicates no active priority IRQ)",
              32, old_value_t.cpu_pri_irq_sts, new_value_t.cpu_pri_irq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_FIQ_STS_OFFSET 0x128
#define EVP_CPU_FIQ_STS_UNDEFMASK 0x00000000
union evp_cpu_fiq_sts_u {
    struct {
        unsigned int cpu_fiq_sts:32;        /* FFS (from lsb) FIQ index (0x80 indicates no active FIQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_fiq_sts_u old_value_t = { .reg32 = value };
    const evp_cpu_fiq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_fiq_sts:32",
              "FFS (from lsb) FIQ index (0x80 indicates no active FIQ)",
              32, old_value_t.cpu_fiq_sts, new_value_t.cpu_fiq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_STS_OFFSET 0x12C
#define EVP_CPU_PRI_FIQ_STS_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_sts_u {
    struct {
        unsigned int cpu_pri_fiq_sts:32;    /* Current highest priority active FIQ (0x80 indicates no active priority FIQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_sts_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_pri_fiq_sts:32",
              "Current highest priority active FIQ (0x80 indicates no active priority FIQ)",
              32, old_value_t.cpu_pri_fiq_sts, new_value_t.cpu_pri_fiq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_0_OFFSET 0x140
#define EVP_CPU_PRI_IRQ_NUM_0_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_0_u {
    struct {
        unsigned int pri_irq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_0_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_0:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_0, new_value_t.pri_irq_num_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_0_OFFSET 0x144
#define EVP_CPU_PRI_IRQ_VEC_0_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_0_u {
    struct {
        unsigned int pri_irq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_0_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_0:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_0, new_value_t.pri_irq_vec_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_1_OFFSET 0x148
#define EVP_CPU_PRI_IRQ_NUM_1_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_1_u {
    struct {
        unsigned int pri_irq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_1_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_1:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_1, new_value_t.pri_irq_num_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_1_OFFSET 0x14C
#define EVP_CPU_PRI_IRQ_VEC_1_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_1_u {
    struct {
        unsigned int pri_irq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_1_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_1:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_1, new_value_t.pri_irq_vec_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_2_OFFSET 0x150
#define EVP_CPU_PRI_IRQ_NUM_2_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_2_u {
    struct {
        unsigned int pri_irq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_2_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_2:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_2, new_value_t.pri_irq_num_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_2_OFFSET 0x154
#define EVP_CPU_PRI_IRQ_VEC_2_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_2_u {
    struct {
        unsigned int pri_irq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_2_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_2:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_2, new_value_t.pri_irq_vec_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_3_OFFSET 0x158
#define EVP_CPU_PRI_IRQ_NUM_3_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_3_u {
    struct {
        unsigned int pri_irq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_3_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_3:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_3, new_value_t.pri_irq_num_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_3_OFFSET 0x15C
#define EVP_CPU_PRI_IRQ_VEC_3_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_3_u {
    struct {
        unsigned int pri_irq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_3_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_3:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_3, new_value_t.pri_irq_vec_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_4_OFFSET 0x160
#define EVP_CPU_PRI_IRQ_NUM_4_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_4_u {
    struct {
        unsigned int pri_irq_num_4:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_4_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_4:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_4, new_value_t.pri_irq_num_4 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_4_OFFSET 0x164
#define EVP_CPU_PRI_IRQ_VEC_4_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_4_u {
    struct {
        unsigned int pri_irq_vec_4:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_4_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_4:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_4, new_value_t.pri_irq_vec_4 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_5_OFFSET 0x168
#define EVP_CPU_PRI_IRQ_NUM_5_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_5_u {
    struct {
        unsigned int pri_irq_num_5:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_5_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_5:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_5, new_value_t.pri_irq_num_5 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_5_OFFSET 0x16C
#define EVP_CPU_PRI_IRQ_VEC_5_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_5_u {
    struct {
        unsigned int pri_irq_vec_5:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_5_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_5:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_5, new_value_t.pri_irq_vec_5 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_6_OFFSET 0x170
#define EVP_CPU_PRI_IRQ_NUM_6_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_6_u {
    struct {
        unsigned int pri_irq_num_6:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_6_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_6:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_6, new_value_t.pri_irq_num_6 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_6_OFFSET 0x174
#define EVP_CPU_PRI_IRQ_VEC_6_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_6_u {
    struct {
        unsigned int pri_irq_vec_6:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_6_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_6:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_6, new_value_t.pri_irq_vec_6 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_NUM_7_OFFSET 0x178
#define EVP_CPU_PRI_IRQ_NUM_7_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_num_7_u {
    struct {
        unsigned int pri_irq_num_7:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_num_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_num_7_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_num_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_7:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_7, new_value_t.pri_irq_num_7 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_IRQ_VEC_7_OFFSET 0x17C
#define EVP_CPU_PRI_IRQ_VEC_7_UNDEFMASK 0x00000000
union evp_cpu_pri_irq_vec_7_u {
    struct {
        unsigned int pri_irq_vec_7:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_irq_vec_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_irq_vec_7_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_irq_vec_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_7:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_7, new_value_t.pri_irq_vec_7 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_NUM_0_OFFSET 0x180
#define EVP_CPU_PRI_FIQ_NUM_0_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_num_0_u {
    struct {
        unsigned int pri_fiq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_num_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_num_0_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_num_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_0:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_0, new_value_t.pri_fiq_num_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_VEC_0_OFFSET 0x184
#define EVP_CPU_PRI_FIQ_VEC_0_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_vec_0_u {
    struct {
        unsigned int pri_fiq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_vec_0_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_vec_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_0:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_0, new_value_t.pri_fiq_vec_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_NUM_1_OFFSET 0x188
#define EVP_CPU_PRI_FIQ_NUM_1_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_num_1_u {
    struct {
        unsigned int pri_fiq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_num_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_num_1_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_num_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_1:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_1, new_value_t.pri_fiq_num_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_VEC_1_OFFSET 0x18C
#define EVP_CPU_PRI_FIQ_VEC_1_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_vec_1_u {
    struct {
        unsigned int pri_fiq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_vec_1_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_vec_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_1:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_1, new_value_t.pri_fiq_vec_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_NUM_2_OFFSET 0x190
#define EVP_CPU_PRI_FIQ_NUM_2_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_num_2_u {
    struct {
        unsigned int pri_fiq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_num_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_num_2_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_num_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_2:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_2, new_value_t.pri_fiq_num_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_VEC_2_OFFSET 0x194
#define EVP_CPU_PRI_FIQ_VEC_2_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_vec_2_u {
    struct {
        unsigned int pri_fiq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_vec_2_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_vec_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_2:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_2, new_value_t.pri_fiq_vec_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_NUM_3_OFFSET 0x198
#define EVP_CPU_PRI_FIQ_NUM_3_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_num_3_u {
    struct {
        unsigned int pri_fiq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_num_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_num_3_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_num_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_3:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_3, new_value_t.pri_fiq_num_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_CPU_PRI_FIQ_VEC_3_OFFSET 0x19C
#define EVP_CPU_PRI_FIQ_VEC_3_UNDEFMASK 0x00000000
union evp_cpu_pri_fiq_vec_3_u {
    struct {
        unsigned int pri_fiq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cpu_pri_fiq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cpu_pri_fiq_vec_3_u old_value_t = { .reg32 = value };
    const evp_cpu_pri_fiq_vec_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_3:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_3, new_value_t.pri_fiq_vec_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_RESET_VECTOR_OFFSET 0x200
#define EVP_COP_RESET_VECTOR_UNDEFMASK 0x00000000
union evp_cop_reset_vector_u {
    struct {
        unsigned int cop_reset_vector:32;   /* RESET Exception Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_reset_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_reset_vector_u old_value_t = { .reg32 = value };
    const evp_cop_reset_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_reset_vector:32",
              "RESET Exception Vector Pointer",
              32, old_value_t.cop_reset_vector, new_value_t.cop_reset_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_UNDEF_VECTOR_OFFSET 0x204
#define EVP_COP_UNDEF_VECTOR_UNDEFMASK 0x00000000
union evp_cop_undef_vector_u {
    struct {
        unsigned int cop_undef_vector:32;   /* Undefined Exception Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_undef_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_undef_vector_u old_value_t = { .reg32 = value };
    const evp_cop_undef_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_undef_vector:32",
              "Undefined Exception Vector Pointer",
              32, old_value_t.cop_undef_vector, new_value_t.cop_undef_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_SWI_VECTOR_OFFSET 0x208
#define EVP_COP_SWI_VECTOR_UNDEFMASK 0x00000000
union evp_cop_swi_vector_u {
    struct {
        unsigned int cop_swi_vector:32;     /* Software Interrupt Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_swi_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_swi_vector_u old_value_t = { .reg32 = value };
    const evp_cop_swi_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_swi_vector:32",
              "Software Interrupt Vector Pointer",
              32, old_value_t.cop_swi_vector, new_value_t.cop_swi_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PREFETCH_ABORT_VECTOR_OFFSET 0x20C
#define EVP_COP_PREFETCH_ABORT_VECTOR_UNDEFMASK 0x00000000
union evp_cop_prefetch_abort_vector_u {
    struct {
        unsigned int cop_pre_abort_vector:32;/* Code Prefetch ABORT Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_prefetch_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_prefetch_abort_vector_u old_value_t = { .reg32 = value };
    const evp_cop_prefetch_abort_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_pre_abort_vector:32",
              "Code Prefetch ABORT Vector Pointer",
              32, old_value_t.cop_pre_abort_vector, new_value_t.cop_pre_abort_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_DATA_ABORT_VECTOR_OFFSET 0x210
#define EVP_COP_DATA_ABORT_VECTOR_UNDEFMASK 0x00000000
union evp_cop_data_abort_vector_u {
    struct {
        unsigned int cop_data_abort_vector:32;/* Data ABORT Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_data_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_data_abort_vector_u old_value_t = { .reg32 = value };
    const evp_cop_data_abort_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_data_abort_vector:32",
              "Data ABORT Vector Pointer",
              32, old_value_t.cop_data_abort_vector, new_value_t.cop_data_abort_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_RSVD_VECTOR_OFFSET 0x214
#define EVP_COP_RSVD_VECTOR_UNDEFMASK 0x00000000
union evp_cop_rsvd_vector_u {
    struct {
        unsigned int cop_rsvd_vector:32;    /* Reserved Exception Vector Pointer */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_rsvd_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_rsvd_vector_u old_value_t = { .reg32 = value };
    const evp_cop_rsvd_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_rsvd_vector:32",
              "Reserved Exception Vector Pointer",
              32, old_value_t.cop_rsvd_vector, new_value_t.cop_rsvd_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_IRQ_VECTOR_OFFSET 0x218
#define EVP_COP_IRQ_VECTOR_UNDEFMASK 0x00000000
union evp_cop_irq_vector_u {
    struct {
        unsigned int cop_irq_vector:32;     /* IRQ Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_irq_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_irq_vector_u old_value_t = { .reg32 = value };
    const evp_cop_irq_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_irq_vector:32",
              "IRQ Vector Pointer",
              32, old_value_t.cop_irq_vector, new_value_t.cop_irq_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_FIQ_VECTOR_OFFSET 0x21C
#define EVP_COP_FIQ_VECTOR_UNDEFMASK 0x00000000
union evp_cop_fiq_vector_u {
    struct {
        unsigned int cop_fiq_vector:32;     /* FIQ Vector Pointer  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_fiq_vector_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_fiq_vector_u old_value_t = { .reg32 = value };
    const evp_cop_fiq_vector_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_fiq_vector:32",
              "FIQ Vector Pointer",
              32, old_value_t.cop_fiq_vector, new_value_t.cop_fiq_vector };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_IRQ_STS_OFFSET 0x220
#define EVP_COP_IRQ_STS_UNDEFMASK 0x00000000
union evp_cop_irq_sts_u {
    struct {
        unsigned int cop_irq_sts:32;        /* FFS (from lsb) IRQ index  (0x80 indicates no active IRQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_irq_sts_u old_value_t = { .reg32 = value };
    const evp_cop_irq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_irq_sts:32",
              "FFS (from lsb) IRQ index  (0x80 indicates no active IRQ)",
              32, old_value_t.cop_irq_sts, new_value_t.cop_irq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_STS_OFFSET 0x224
#define EVP_COP_PRI_IRQ_STS_UNDEFMASK 0x00000000
union evp_cop_pri_irq_sts_u {
    struct {
        unsigned int cop_pri_irq_sts:32;    /* Current highest priority active IRQ (0x80 indicates no active priority IRQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_sts_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_pri_irq_sts:32",
              "Current highest priority active IRQ (0x80 indicates no active priority IRQ)",
              32, old_value_t.cop_pri_irq_sts, new_value_t.cop_pri_irq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_FIQ_STS_OFFSET 0x228
#define EVP_COP_FIQ_STS_UNDEFMASK 0x00000000
union evp_cop_fiq_sts_u {
    struct {
        unsigned int cop_fiq_sts:32;        /* FFS (from lsb) FIQ index (0x80 indicates no active FIQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_fiq_sts_u old_value_t = { .reg32 = value };
    const evp_cop_fiq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_fiq_sts:32",
              "FFS (from lsb) FIQ index (0x80 indicates no active FIQ)",
              32, old_value_t.cop_fiq_sts, new_value_t.cop_fiq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_STS_OFFSET 0x22C
#define EVP_COP_PRI_FIQ_STS_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_sts_u {
    struct {
        unsigned int cop_pri_fiq_sts:32;    /* Current highest priority active FIQ (0x80 indicates no active priority FIQ) */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_sts_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_sts_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_pri_fiq_sts:32",
              "Current highest priority active FIQ (0x80 indicates no active priority FIQ)",
              32, old_value_t.cop_pri_fiq_sts, new_value_t.cop_pri_fiq_sts };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_0_OFFSET 0x240
#define EVP_COP_PRI_IRQ_NUM_0_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_0_u {
    struct {
        unsigned int pri_irq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_0_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_0:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_0, new_value_t.pri_irq_num_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_0_OFFSET 0x244
#define EVP_COP_PRI_IRQ_VEC_0_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_0_u {
    struct {
        unsigned int pri_irq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_0_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_0:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_0, new_value_t.pri_irq_vec_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_1_OFFSET 0x248
#define EVP_COP_PRI_IRQ_NUM_1_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_1_u {
    struct {
        unsigned int pri_irq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_1_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_1:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_1, new_value_t.pri_irq_num_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_1_OFFSET 0x24C
#define EVP_COP_PRI_IRQ_VEC_1_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_1_u {
    struct {
        unsigned int pri_irq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_1_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_1:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_1, new_value_t.pri_irq_vec_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_2_OFFSET 0x250
#define EVP_COP_PRI_IRQ_NUM_2_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_2_u {
    struct {
        unsigned int pri_irq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_2_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_2:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_2, new_value_t.pri_irq_num_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_2_OFFSET 0x254
#define EVP_COP_PRI_IRQ_VEC_2_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_2_u {
    struct {
        unsigned int pri_irq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_2_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_2:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_2, new_value_t.pri_irq_vec_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_3_OFFSET 0x258
#define EVP_COP_PRI_IRQ_NUM_3_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_3_u {
    struct {
        unsigned int pri_irq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_3_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_3:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_3, new_value_t.pri_irq_num_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_3_OFFSET 0x25C
#define EVP_COP_PRI_IRQ_VEC_3_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_3_u {
    struct {
        unsigned int pri_irq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_3_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_3:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_3, new_value_t.pri_irq_vec_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_4_OFFSET 0x260
#define EVP_COP_PRI_IRQ_NUM_4_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_4_u {
    struct {
        unsigned int pri_irq_num_4:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_4_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_4:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_4, new_value_t.pri_irq_num_4 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_4_OFFSET 0x264
#define EVP_COP_PRI_IRQ_VEC_4_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_4_u {
    struct {
        unsigned int pri_irq_vec_4:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_4_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_4:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_4, new_value_t.pri_irq_vec_4 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_5_OFFSET 0x268
#define EVP_COP_PRI_IRQ_NUM_5_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_5_u {
    struct {
        unsigned int pri_irq_num_5:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_5_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_5:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_5, new_value_t.pri_irq_num_5 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_5_OFFSET 0x26C
#define EVP_COP_PRI_IRQ_VEC_5_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_5_u {
    struct {
        unsigned int pri_irq_vec_5:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_5_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_5:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_5, new_value_t.pri_irq_vec_5 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_6_OFFSET 0x270
#define EVP_COP_PRI_IRQ_NUM_6_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_6_u {
    struct {
        unsigned int pri_irq_num_6:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_6_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_6:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_6, new_value_t.pri_irq_num_6 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_6_OFFSET 0x274
#define EVP_COP_PRI_IRQ_VEC_6_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_6_u {
    struct {
        unsigned int pri_irq_vec_6:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_6_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_6:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_6, new_value_t.pri_irq_vec_6 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_NUM_7_OFFSET 0x278
#define EVP_COP_PRI_IRQ_NUM_7_UNDEFMASK 0x00000000
union evp_cop_pri_irq_num_7_u {
    struct {
        unsigned int pri_irq_num_7:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_num_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_num_7_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_num_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_num_7:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_irq_num_7, new_value_t.pri_irq_num_7 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_IRQ_VEC_7_OFFSET 0x27C
#define EVP_COP_PRI_IRQ_VEC_7_UNDEFMASK 0x00000000
union evp_cop_pri_irq_vec_7_u {
    struct {
        unsigned int pri_irq_vec_7:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_irq_vec_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_irq_vec_7_u old_value_t = { .reg32 = value };
    const evp_cop_pri_irq_vec_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_irq_vec_7:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_irq_vec_7, new_value_t.pri_irq_vec_7 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_NUM_0_OFFSET 0x280
#define EVP_COP_PRI_FIQ_NUM_0_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_num_0_u {
    struct {
        unsigned int pri_fiq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_num_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_num_0_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_num_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_0:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_0, new_value_t.pri_fiq_num_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_VEC_0_OFFSET 0x284
#define EVP_COP_PRI_FIQ_VEC_0_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_vec_0_u {
    struct {
        unsigned int pri_fiq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_vec_0_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_vec_0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_0:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_0, new_value_t.pri_fiq_vec_0 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_NUM_1_OFFSET 0x288
#define EVP_COP_PRI_FIQ_NUM_1_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_num_1_u {
    struct {
        unsigned int pri_fiq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_num_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_num_1_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_num_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_1:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_1, new_value_t.pri_fiq_num_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_VEC_1_OFFSET 0x28C
#define EVP_COP_PRI_FIQ_VEC_1_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_vec_1_u {
    struct {
        unsigned int pri_fiq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_vec_1_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_vec_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_1:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_1, new_value_t.pri_fiq_vec_1 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_NUM_2_OFFSET 0x290
#define EVP_COP_PRI_FIQ_NUM_2_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_num_2_u {
    struct {
        unsigned int pri_fiq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_num_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_num_2_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_num_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_2:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_2, new_value_t.pri_fiq_num_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_VEC_2_OFFSET 0x294
#define EVP_COP_PRI_FIQ_VEC_2_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_vec_2_u {
    struct {
        unsigned int pri_fiq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_vec_2_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_vec_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_2:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_2, new_value_t.pri_fiq_vec_2 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_NUM_3_OFFSET 0x298
#define EVP_COP_PRI_FIQ_NUM_3_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_num_3_u {
    struct {
        unsigned int pri_fiq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_num_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_num_3_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_num_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_num_3:32",
              "Number for the Interrupt associated with this entry",
              32, old_value_t.pri_fiq_num_3, new_value_t.pri_fiq_num_3 };
    m_bit_details_model.bits.append(entry);
}

#define EVP_COP_PRI_FIQ_VEC_3_OFFSET 0x29C
#define EVP_COP_PRI_FIQ_VEC_3_UNDEFMASK 0x00000000
union evp_cop_pri_fiq_vec_3_u {
    struct {
        unsigned int pri_fiq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    u_int32_t reg32;
};

void EvpDev::fill_evp_cop_pri_fiq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const evp_cop_pri_fiq_vec_3_u old_value_t = { .reg32 = value };
    const evp_cop_pri_fiq_vec_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pri_fiq_vec_3:32",
              "Pointer to the interrupt handler for the above interrupt",
              32, old_value_t.pri_fiq_vec_3, new_value_t.pri_fiq_vec_3 };
    m_bit_details_model.bits.append(entry);
}



bool EvpDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case EVP_RESET_VECTOR_OFFSET:
    case EVP_UNDEF_VECTOR_OFFSET:
    case EVP_SWI_VECTOR_OFFSET:
    case EVP_PREFETCH_ABORT_VECTOR_OFFSET:
    case EVP_DATA_ABORT_VECTOR_OFFSET:
    case EVP_RSVD_VECTOR_OFFSET:
    case EVP_IRQ_VECTOR_OFFSET:
    case EVP_FIQ_VECTOR_OFFSET:
    case EVP_IRQ_STS_OFFSET:
    case EVP_PRI_IRQ_STS_OFFSET:
    case EVP_FIQ_STS_OFFSET:
    case EVP_PRI_FIQ_STS_OFFSET:
    case EVP_PRI_IRQ_NUM_0_OFFSET:
    case EVP_PRI_IRQ_VEC_0_OFFSET:
    case EVP_PRI_IRQ_NUM_1_OFFSET:
    case EVP_PRI_IRQ_VEC_1_OFFSET:
    case EVP_PRI_IRQ_NUM_2_OFFSET:
    case EVP_PRI_IRQ_VEC_2_OFFSET:
    case EVP_PRI_IRQ_NUM_3_OFFSET:
    case EVP_PRI_IRQ_VEC_3_OFFSET:
    case EVP_PRI_IRQ_NUM_4_OFFSET:
    case EVP_PRI_IRQ_VEC_4_OFFSET:
    case EVP_PRI_IRQ_NUM_5_OFFSET:
    case EVP_PRI_IRQ_VEC_5_OFFSET:
    case EVP_PRI_IRQ_NUM_6_OFFSET:
    case EVP_PRI_IRQ_VEC_6_OFFSET:
    case EVP_PRI_IRQ_NUM_7_OFFSET:
    case EVP_PRI_IRQ_VEC_7_OFFSET:
    case EVP_PRI_FIQ_NUM_0_OFFSET:
    case EVP_PRI_FIQ_VEC_0_OFFSET:
    case EVP_PRI_FIQ_NUM_1_OFFSET:
    case EVP_PRI_FIQ_VEC_1_OFFSET:
    case EVP_PRI_FIQ_NUM_2_OFFSET:
    case EVP_PRI_FIQ_VEC_2_OFFSET:
    case EVP_PRI_FIQ_NUM_3_OFFSET:
    case EVP_PRI_FIQ_VEC_3_OFFSET:
    case EVP_CPU_RESET_VECTOR_OFFSET:
    case EVP_CPU_UNDEF_VECTOR_OFFSET:
    case EVP_CPU_SWI_VECTOR_OFFSET:
    case EVP_CPU_PREFETCH_ABORT_VECTOR_OFFSET:
    case EVP_CPU_DATA_ABORT_VECTOR_OFFSET:
    case EVP_CPU_RSVD_VECTOR_OFFSET:
    case EVP_CPU_IRQ_VECTOR_OFFSET:
    case EVP_CPU_FIQ_VECTOR_OFFSET:
    case EVP_CPU_IRQ_STS_OFFSET:
    case EVP_CPU_PRI_IRQ_STS_OFFSET:
    case EVP_CPU_FIQ_STS_OFFSET:
    case EVP_CPU_PRI_FIQ_STS_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_0_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_0_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_1_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_1_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_2_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_2_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_3_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_3_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_4_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_4_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_5_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_5_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_6_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_6_OFFSET:
    case EVP_CPU_PRI_IRQ_NUM_7_OFFSET:
    case EVP_CPU_PRI_IRQ_VEC_7_OFFSET:
    case EVP_CPU_PRI_FIQ_NUM_0_OFFSET:
    case EVP_CPU_PRI_FIQ_VEC_0_OFFSET:
    case EVP_CPU_PRI_FIQ_NUM_1_OFFSET:
    case EVP_CPU_PRI_FIQ_VEC_1_OFFSET:
    case EVP_CPU_PRI_FIQ_NUM_2_OFFSET:
    case EVP_CPU_PRI_FIQ_VEC_2_OFFSET:
    case EVP_CPU_PRI_FIQ_NUM_3_OFFSET:
    case EVP_CPU_PRI_FIQ_VEC_3_OFFSET:
    case EVP_COP_RESET_VECTOR_OFFSET:
    case EVP_COP_UNDEF_VECTOR_OFFSET:
    case EVP_COP_SWI_VECTOR_OFFSET:
    case EVP_COP_PREFETCH_ABORT_VECTOR_OFFSET:
    case EVP_COP_DATA_ABORT_VECTOR_OFFSET:
    case EVP_COP_RSVD_VECTOR_OFFSET:
    case EVP_COP_IRQ_VECTOR_OFFSET:
    case EVP_COP_FIQ_VECTOR_OFFSET:
    case EVP_COP_IRQ_STS_OFFSET:
    case EVP_COP_PRI_IRQ_STS_OFFSET:
    case EVP_COP_FIQ_STS_OFFSET:
    case EVP_COP_PRI_FIQ_STS_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_0_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_0_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_1_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_1_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_2_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_2_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_3_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_3_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_4_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_4_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_5_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_5_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_6_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_6_OFFSET:
    case EVP_COP_PRI_IRQ_NUM_7_OFFSET:
    case EVP_COP_PRI_IRQ_VEC_7_OFFSET:
    case EVP_COP_PRI_FIQ_NUM_0_OFFSET:
    case EVP_COP_PRI_FIQ_VEC_0_OFFSET:
    case EVP_COP_PRI_FIQ_NUM_1_OFFSET:
    case EVP_COP_PRI_FIQ_VEC_1_OFFSET:
    case EVP_COP_PRI_FIQ_NUM_2_OFFSET:
    case EVP_COP_PRI_FIQ_VEC_2_OFFSET:
    case EVP_COP_PRI_FIQ_NUM_3_OFFSET:
    case EVP_COP_PRI_FIQ_VEC_3_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool EvpDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case EVP_RESET_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_RESET_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_UNDEF_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_UNDEF_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_SWI_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_SWI_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_PREFETCH_ABORT_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_PREFETCH_ABORT_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_DATA_ABORT_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_DATA_ABORT_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_RSVD_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_RSVD_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_IRQ_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_IRQ_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_FIQ_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_FIQ_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_IRQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_IRQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_FIQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_FIQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_0_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_0_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_0_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_0_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_1_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_1_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_1_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_1_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_2_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_2_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_2_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_2_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_3_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_3_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_3_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_3_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_4_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_4_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_4_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_4_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_5_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_5_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_5_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_5_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_6_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_6_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_6_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_6_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_NUM_7_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_NUM_7_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_IRQ_VEC_7_OFFSET:
        if ((value ^ new_value) & EVP_PRI_IRQ_VEC_7_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_NUM_0_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_NUM_0_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_VEC_0_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_VEC_0_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_NUM_1_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_NUM_1_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_VEC_1_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_VEC_1_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_NUM_2_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_NUM_2_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_VEC_2_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_VEC_2_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_NUM_3_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_NUM_3_UNDEFMASK)
            return true;
        break;
    case EVP_PRI_FIQ_VEC_3_OFFSET:
        if ((value ^ new_value) & EVP_PRI_FIQ_VEC_3_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_RESET_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_RESET_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_UNDEF_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_UNDEF_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_SWI_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_SWI_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PREFETCH_ABORT_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PREFETCH_ABORT_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_DATA_ABORT_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_DATA_ABORT_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_RSVD_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_RSVD_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_IRQ_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_IRQ_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_FIQ_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_CPU_FIQ_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_IRQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_CPU_IRQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_FIQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_CPU_FIQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_0_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_0_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_0_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_0_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_1_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_1_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_1_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_1_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_2_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_2_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_2_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_2_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_3_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_3_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_3_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_3_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_4_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_4_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_4_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_4_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_5_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_5_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_5_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_5_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_6_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_6_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_6_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_6_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_NUM_7_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_NUM_7_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_IRQ_VEC_7_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_IRQ_VEC_7_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_NUM_0_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_NUM_0_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_VEC_0_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_VEC_0_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_NUM_1_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_NUM_1_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_VEC_1_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_VEC_1_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_NUM_2_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_NUM_2_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_VEC_2_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_VEC_2_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_NUM_3_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_NUM_3_UNDEFMASK)
            return true;
        break;
    case EVP_CPU_PRI_FIQ_VEC_3_OFFSET:
        if ((value ^ new_value) & EVP_CPU_PRI_FIQ_VEC_3_UNDEFMASK)
            return true;
        break;
    case EVP_COP_RESET_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_RESET_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_UNDEF_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_UNDEF_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_SWI_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_SWI_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PREFETCH_ABORT_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_PREFETCH_ABORT_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_DATA_ABORT_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_DATA_ABORT_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_RSVD_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_RSVD_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_IRQ_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_IRQ_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_FIQ_VECTOR_OFFSET:
        if ((value ^ new_value) & EVP_COP_FIQ_VECTOR_UNDEFMASK)
            return true;
        break;
    case EVP_COP_IRQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_COP_IRQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_COP_FIQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_COP_FIQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_STS_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_STS_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_0_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_0_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_0_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_0_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_1_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_1_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_1_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_1_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_2_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_2_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_2_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_2_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_3_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_3_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_3_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_3_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_4_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_4_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_4_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_4_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_5_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_5_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_5_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_5_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_6_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_6_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_6_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_6_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_NUM_7_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_NUM_7_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_IRQ_VEC_7_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_IRQ_VEC_7_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_NUM_0_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_NUM_0_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_VEC_0_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_VEC_0_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_NUM_1_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_NUM_1_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_VEC_1_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_VEC_1_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_NUM_2_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_NUM_2_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_VEC_2_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_VEC_2_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_NUM_3_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_NUM_3_UNDEFMASK)
            return true;
        break;
    case EVP_COP_PRI_FIQ_VEC_3_OFFSET:
        if ((value ^ new_value) & EVP_COP_PRI_FIQ_VEC_3_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString EvpDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case EVP_RESET_VECTOR_OFFSET:
        return QString("EVP_RESET_VECTOR");
    case EVP_UNDEF_VECTOR_OFFSET:
        return QString("EVP_UNDEF_VECTOR");
    case EVP_SWI_VECTOR_OFFSET:
        return QString("EVP_SWI_VECTOR");
    case EVP_PREFETCH_ABORT_VECTOR_OFFSET:
        return QString("EVP_PREFETCH_ABORT_VECTOR");
    case EVP_DATA_ABORT_VECTOR_OFFSET:
        return QString("EVP_DATA_ABORT_VECTOR");
    case EVP_RSVD_VECTOR_OFFSET:
        return QString("EVP_RSVD_VECTOR");
    case EVP_IRQ_VECTOR_OFFSET:
        return QString("EVP_IRQ_VECTOR");
    case EVP_FIQ_VECTOR_OFFSET:
        return QString("EVP_FIQ_VECTOR");
    case EVP_IRQ_STS_OFFSET:
        return QString("EVP_IRQ_STS");
    case EVP_PRI_IRQ_STS_OFFSET:
        return QString("EVP_PRI_IRQ_STS");
    case EVP_FIQ_STS_OFFSET:
        return QString("EVP_FIQ_STS");
    case EVP_PRI_FIQ_STS_OFFSET:
        return QString("EVP_PRI_FIQ_STS");
    case EVP_PRI_IRQ_NUM_0_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_0");
    case EVP_PRI_IRQ_VEC_0_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_0");
    case EVP_PRI_IRQ_NUM_1_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_1");
    case EVP_PRI_IRQ_VEC_1_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_1");
    case EVP_PRI_IRQ_NUM_2_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_2");
    case EVP_PRI_IRQ_VEC_2_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_2");
    case EVP_PRI_IRQ_NUM_3_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_3");
    case EVP_PRI_IRQ_VEC_3_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_3");
    case EVP_PRI_IRQ_NUM_4_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_4");
    case EVP_PRI_IRQ_VEC_4_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_4");
    case EVP_PRI_IRQ_NUM_5_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_5");
    case EVP_PRI_IRQ_VEC_5_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_5");
    case EVP_PRI_IRQ_NUM_6_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_6");
    case EVP_PRI_IRQ_VEC_6_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_6");
    case EVP_PRI_IRQ_NUM_7_OFFSET:
        return QString("EVP_PRI_IRQ_NUM_7");
    case EVP_PRI_IRQ_VEC_7_OFFSET:
        return QString("EVP_PRI_IRQ_VEC_7");
    case EVP_PRI_FIQ_NUM_0_OFFSET:
        return QString("EVP_PRI_FIQ_NUM_0");
    case EVP_PRI_FIQ_VEC_0_OFFSET:
        return QString("EVP_PRI_FIQ_VEC_0");
    case EVP_PRI_FIQ_NUM_1_OFFSET:
        return QString("EVP_PRI_FIQ_NUM_1");
    case EVP_PRI_FIQ_VEC_1_OFFSET:
        return QString("EVP_PRI_FIQ_VEC_1");
    case EVP_PRI_FIQ_NUM_2_OFFSET:
        return QString("EVP_PRI_FIQ_NUM_2");
    case EVP_PRI_FIQ_VEC_2_OFFSET:
        return QString("EVP_PRI_FIQ_VEC_2");
    case EVP_PRI_FIQ_NUM_3_OFFSET:
        return QString("EVP_PRI_FIQ_NUM_3");
    case EVP_PRI_FIQ_VEC_3_OFFSET:
        return QString("EVP_PRI_FIQ_VEC_3");
    case EVP_CPU_RESET_VECTOR_OFFSET:
        return QString("EVP_CPU_RESET_VECTOR");
    case EVP_CPU_UNDEF_VECTOR_OFFSET:
        return QString("EVP_CPU_UNDEF_VECTOR");
    case EVP_CPU_SWI_VECTOR_OFFSET:
        return QString("EVP_CPU_SWI_VECTOR");
    case EVP_CPU_PREFETCH_ABORT_VECTOR_OFFSET:
        return QString("EVP_CPU_PREFETCH_ABORT_VECTOR");
    case EVP_CPU_DATA_ABORT_VECTOR_OFFSET:
        return QString("EVP_CPU_DATA_ABORT_VECTOR");
    case EVP_CPU_RSVD_VECTOR_OFFSET:
        return QString("EVP_CPU_RSVD_VECTOR");
    case EVP_CPU_IRQ_VECTOR_OFFSET:
        return QString("EVP_CPU_IRQ_VECTOR");
    case EVP_CPU_FIQ_VECTOR_OFFSET:
        return QString("EVP_CPU_FIQ_VECTOR");
    case EVP_CPU_IRQ_STS_OFFSET:
        return QString("EVP_CPU_IRQ_STS");
    case EVP_CPU_PRI_IRQ_STS_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_STS");
    case EVP_CPU_FIQ_STS_OFFSET:
        return QString("EVP_CPU_FIQ_STS");
    case EVP_CPU_PRI_FIQ_STS_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_STS");
    case EVP_CPU_PRI_IRQ_NUM_0_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_0");
    case EVP_CPU_PRI_IRQ_VEC_0_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_0");
    case EVP_CPU_PRI_IRQ_NUM_1_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_1");
    case EVP_CPU_PRI_IRQ_VEC_1_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_1");
    case EVP_CPU_PRI_IRQ_NUM_2_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_2");
    case EVP_CPU_PRI_IRQ_VEC_2_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_2");
    case EVP_CPU_PRI_IRQ_NUM_3_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_3");
    case EVP_CPU_PRI_IRQ_VEC_3_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_3");
    case EVP_CPU_PRI_IRQ_NUM_4_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_4");
    case EVP_CPU_PRI_IRQ_VEC_4_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_4");
    case EVP_CPU_PRI_IRQ_NUM_5_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_5");
    case EVP_CPU_PRI_IRQ_VEC_5_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_5");
    case EVP_CPU_PRI_IRQ_NUM_6_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_6");
    case EVP_CPU_PRI_IRQ_VEC_6_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_6");
    case EVP_CPU_PRI_IRQ_NUM_7_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_NUM_7");
    case EVP_CPU_PRI_IRQ_VEC_7_OFFSET:
        return QString("EVP_CPU_PRI_IRQ_VEC_7");
    case EVP_CPU_PRI_FIQ_NUM_0_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_NUM_0");
    case EVP_CPU_PRI_FIQ_VEC_0_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_VEC_0");
    case EVP_CPU_PRI_FIQ_NUM_1_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_NUM_1");
    case EVP_CPU_PRI_FIQ_VEC_1_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_VEC_1");
    case EVP_CPU_PRI_FIQ_NUM_2_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_NUM_2");
    case EVP_CPU_PRI_FIQ_VEC_2_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_VEC_2");
    case EVP_CPU_PRI_FIQ_NUM_3_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_NUM_3");
    case EVP_CPU_PRI_FIQ_VEC_3_OFFSET:
        return QString("EVP_CPU_PRI_FIQ_VEC_3");
    case EVP_COP_RESET_VECTOR_OFFSET:
        return QString("EVP_COP_RESET_VECTOR");
    case EVP_COP_UNDEF_VECTOR_OFFSET:
        return QString("EVP_COP_UNDEF_VECTOR");
    case EVP_COP_SWI_VECTOR_OFFSET:
        return QString("EVP_COP_SWI_VECTOR");
    case EVP_COP_PREFETCH_ABORT_VECTOR_OFFSET:
        return QString("EVP_COP_PREFETCH_ABORT_VECTOR");
    case EVP_COP_DATA_ABORT_VECTOR_OFFSET:
        return QString("EVP_COP_DATA_ABORT_VECTOR");
    case EVP_COP_RSVD_VECTOR_OFFSET:
        return QString("EVP_COP_RSVD_VECTOR");
    case EVP_COP_IRQ_VECTOR_OFFSET:
        return QString("EVP_COP_IRQ_VECTOR");
    case EVP_COP_FIQ_VECTOR_OFFSET:
        return QString("EVP_COP_FIQ_VECTOR");
    case EVP_COP_IRQ_STS_OFFSET:
        return QString("EVP_COP_IRQ_STS");
    case EVP_COP_PRI_IRQ_STS_OFFSET:
        return QString("EVP_COP_PRI_IRQ_STS");
    case EVP_COP_FIQ_STS_OFFSET:
        return QString("EVP_COP_FIQ_STS");
    case EVP_COP_PRI_FIQ_STS_OFFSET:
        return QString("EVP_COP_PRI_FIQ_STS");
    case EVP_COP_PRI_IRQ_NUM_0_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_0");
    case EVP_COP_PRI_IRQ_VEC_0_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_0");
    case EVP_COP_PRI_IRQ_NUM_1_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_1");
    case EVP_COP_PRI_IRQ_VEC_1_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_1");
    case EVP_COP_PRI_IRQ_NUM_2_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_2");
    case EVP_COP_PRI_IRQ_VEC_2_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_2");
    case EVP_COP_PRI_IRQ_NUM_3_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_3");
    case EVP_COP_PRI_IRQ_VEC_3_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_3");
    case EVP_COP_PRI_IRQ_NUM_4_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_4");
    case EVP_COP_PRI_IRQ_VEC_4_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_4");
    case EVP_COP_PRI_IRQ_NUM_5_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_5");
    case EVP_COP_PRI_IRQ_VEC_5_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_5");
    case EVP_COP_PRI_IRQ_NUM_6_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_6");
    case EVP_COP_PRI_IRQ_VEC_6_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_6");
    case EVP_COP_PRI_IRQ_NUM_7_OFFSET:
        return QString("EVP_COP_PRI_IRQ_NUM_7");
    case EVP_COP_PRI_IRQ_VEC_7_OFFSET:
        return QString("EVP_COP_PRI_IRQ_VEC_7");
    case EVP_COP_PRI_FIQ_NUM_0_OFFSET:
        return QString("EVP_COP_PRI_FIQ_NUM_0");
    case EVP_COP_PRI_FIQ_VEC_0_OFFSET:
        return QString("EVP_COP_PRI_FIQ_VEC_0");
    case EVP_COP_PRI_FIQ_NUM_1_OFFSET:
        return QString("EVP_COP_PRI_FIQ_NUM_1");
    case EVP_COP_PRI_FIQ_VEC_1_OFFSET:
        return QString("EVP_COP_PRI_FIQ_VEC_1");
    case EVP_COP_PRI_FIQ_NUM_2_OFFSET:
        return QString("EVP_COP_PRI_FIQ_NUM_2");
    case EVP_COP_PRI_FIQ_VEC_2_OFFSET:
        return QString("EVP_COP_PRI_FIQ_VEC_2");
    case EVP_COP_PRI_FIQ_NUM_3_OFFSET:
        return QString("EVP_COP_PRI_FIQ_NUM_3");
    case EVP_COP_PRI_FIQ_VEC_3_OFFSET:
        return QString("EVP_COP_PRI_FIQ_VEC_3");

    default:
        break;
    }

    qDebug() << QString().sprintf("EVP: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void EvpDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case EVP_RESET_VECTOR_OFFSET:
        fill_evp_reset_vector_details(value, new_value);
        break;
    case EVP_UNDEF_VECTOR_OFFSET:
        fill_evp_undef_vector_details(value, new_value);
        break;
    case EVP_SWI_VECTOR_OFFSET:
        fill_evp_swi_vector_details(value, new_value);
        break;
    case EVP_PREFETCH_ABORT_VECTOR_OFFSET:
        fill_evp_prefetch_abort_vector_details(value, new_value);
        break;
    case EVP_DATA_ABORT_VECTOR_OFFSET:
        fill_evp_data_abort_vector_details(value, new_value);
        break;
    case EVP_RSVD_VECTOR_OFFSET:
        fill_evp_rsvd_vector_details(value, new_value);
        break;
    case EVP_IRQ_VECTOR_OFFSET:
        fill_evp_irq_vector_details(value, new_value);
        break;
    case EVP_FIQ_VECTOR_OFFSET:
        fill_evp_fiq_vector_details(value, new_value);
        break;
    case EVP_IRQ_STS_OFFSET:
        fill_evp_irq_sts_details(value, new_value);
        break;
    case EVP_PRI_IRQ_STS_OFFSET:
        fill_evp_pri_irq_sts_details(value, new_value);
        break;
    case EVP_FIQ_STS_OFFSET:
        fill_evp_fiq_sts_details(value, new_value);
        break;
    case EVP_PRI_FIQ_STS_OFFSET:
        fill_evp_pri_fiq_sts_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_0_OFFSET:
        fill_evp_pri_irq_num_0_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_0_OFFSET:
        fill_evp_pri_irq_vec_0_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_1_OFFSET:
        fill_evp_pri_irq_num_1_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_1_OFFSET:
        fill_evp_pri_irq_vec_1_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_2_OFFSET:
        fill_evp_pri_irq_num_2_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_2_OFFSET:
        fill_evp_pri_irq_vec_2_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_3_OFFSET:
        fill_evp_pri_irq_num_3_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_3_OFFSET:
        fill_evp_pri_irq_vec_3_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_4_OFFSET:
        fill_evp_pri_irq_num_4_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_4_OFFSET:
        fill_evp_pri_irq_vec_4_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_5_OFFSET:
        fill_evp_pri_irq_num_5_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_5_OFFSET:
        fill_evp_pri_irq_vec_5_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_6_OFFSET:
        fill_evp_pri_irq_num_6_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_6_OFFSET:
        fill_evp_pri_irq_vec_6_details(value, new_value);
        break;
    case EVP_PRI_IRQ_NUM_7_OFFSET:
        fill_evp_pri_irq_num_7_details(value, new_value);
        break;
    case EVP_PRI_IRQ_VEC_7_OFFSET:
        fill_evp_pri_irq_vec_7_details(value, new_value);
        break;
    case EVP_PRI_FIQ_NUM_0_OFFSET:
        fill_evp_pri_fiq_num_0_details(value, new_value);
        break;
    case EVP_PRI_FIQ_VEC_0_OFFSET:
        fill_evp_pri_fiq_vec_0_details(value, new_value);
        break;
    case EVP_PRI_FIQ_NUM_1_OFFSET:
        fill_evp_pri_fiq_num_1_details(value, new_value);
        break;
    case EVP_PRI_FIQ_VEC_1_OFFSET:
        fill_evp_pri_fiq_vec_1_details(value, new_value);
        break;
    case EVP_PRI_FIQ_NUM_2_OFFSET:
        fill_evp_pri_fiq_num_2_details(value, new_value);
        break;
    case EVP_PRI_FIQ_VEC_2_OFFSET:
        fill_evp_pri_fiq_vec_2_details(value, new_value);
        break;
    case EVP_PRI_FIQ_NUM_3_OFFSET:
        fill_evp_pri_fiq_num_3_details(value, new_value);
        break;
    case EVP_PRI_FIQ_VEC_3_OFFSET:
        fill_evp_pri_fiq_vec_3_details(value, new_value);
        break;
    case EVP_CPU_RESET_VECTOR_OFFSET:
        fill_evp_cpu_reset_vector_details(value, new_value);
        break;
    case EVP_CPU_UNDEF_VECTOR_OFFSET:
        fill_evp_cpu_undef_vector_details(value, new_value);
        break;
    case EVP_CPU_SWI_VECTOR_OFFSET:
        fill_evp_cpu_swi_vector_details(value, new_value);
        break;
    case EVP_CPU_PREFETCH_ABORT_VECTOR_OFFSET:
        fill_evp_cpu_prefetch_abort_vector_details(value, new_value);
        break;
    case EVP_CPU_DATA_ABORT_VECTOR_OFFSET:
        fill_evp_cpu_data_abort_vector_details(value, new_value);
        break;
    case EVP_CPU_RSVD_VECTOR_OFFSET:
        fill_evp_cpu_rsvd_vector_details(value, new_value);
        break;
    case EVP_CPU_IRQ_VECTOR_OFFSET:
        fill_evp_cpu_irq_vector_details(value, new_value);
        break;
    case EVP_CPU_FIQ_VECTOR_OFFSET:
        fill_evp_cpu_fiq_vector_details(value, new_value);
        break;
    case EVP_CPU_IRQ_STS_OFFSET:
        fill_evp_cpu_irq_sts_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_STS_OFFSET:
        fill_evp_cpu_pri_irq_sts_details(value, new_value);
        break;
    case EVP_CPU_FIQ_STS_OFFSET:
        fill_evp_cpu_fiq_sts_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_STS_OFFSET:
        fill_evp_cpu_pri_fiq_sts_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_0_OFFSET:
        fill_evp_cpu_pri_irq_num_0_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_0_OFFSET:
        fill_evp_cpu_pri_irq_vec_0_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_1_OFFSET:
        fill_evp_cpu_pri_irq_num_1_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_1_OFFSET:
        fill_evp_cpu_pri_irq_vec_1_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_2_OFFSET:
        fill_evp_cpu_pri_irq_num_2_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_2_OFFSET:
        fill_evp_cpu_pri_irq_vec_2_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_3_OFFSET:
        fill_evp_cpu_pri_irq_num_3_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_3_OFFSET:
        fill_evp_cpu_pri_irq_vec_3_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_4_OFFSET:
        fill_evp_cpu_pri_irq_num_4_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_4_OFFSET:
        fill_evp_cpu_pri_irq_vec_4_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_5_OFFSET:
        fill_evp_cpu_pri_irq_num_5_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_5_OFFSET:
        fill_evp_cpu_pri_irq_vec_5_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_6_OFFSET:
        fill_evp_cpu_pri_irq_num_6_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_6_OFFSET:
        fill_evp_cpu_pri_irq_vec_6_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_NUM_7_OFFSET:
        fill_evp_cpu_pri_irq_num_7_details(value, new_value);
        break;
    case EVP_CPU_PRI_IRQ_VEC_7_OFFSET:
        fill_evp_cpu_pri_irq_vec_7_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_NUM_0_OFFSET:
        fill_evp_cpu_pri_fiq_num_0_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_VEC_0_OFFSET:
        fill_evp_cpu_pri_fiq_vec_0_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_NUM_1_OFFSET:
        fill_evp_cpu_pri_fiq_num_1_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_VEC_1_OFFSET:
        fill_evp_cpu_pri_fiq_vec_1_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_NUM_2_OFFSET:
        fill_evp_cpu_pri_fiq_num_2_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_VEC_2_OFFSET:
        fill_evp_cpu_pri_fiq_vec_2_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_NUM_3_OFFSET:
        fill_evp_cpu_pri_fiq_num_3_details(value, new_value);
        break;
    case EVP_CPU_PRI_FIQ_VEC_3_OFFSET:
        fill_evp_cpu_pri_fiq_vec_3_details(value, new_value);
        break;
    case EVP_COP_RESET_VECTOR_OFFSET:
        fill_evp_cop_reset_vector_details(value, new_value);
        break;
    case EVP_COP_UNDEF_VECTOR_OFFSET:
        fill_evp_cop_undef_vector_details(value, new_value);
        break;
    case EVP_COP_SWI_VECTOR_OFFSET:
        fill_evp_cop_swi_vector_details(value, new_value);
        break;
    case EVP_COP_PREFETCH_ABORT_VECTOR_OFFSET:
        fill_evp_cop_prefetch_abort_vector_details(value, new_value);
        break;
    case EVP_COP_DATA_ABORT_VECTOR_OFFSET:
        fill_evp_cop_data_abort_vector_details(value, new_value);
        break;
    case EVP_COP_RSVD_VECTOR_OFFSET:
        fill_evp_cop_rsvd_vector_details(value, new_value);
        break;
    case EVP_COP_IRQ_VECTOR_OFFSET:
        fill_evp_cop_irq_vector_details(value, new_value);
        break;
    case EVP_COP_FIQ_VECTOR_OFFSET:
        fill_evp_cop_fiq_vector_details(value, new_value);
        break;
    case EVP_COP_IRQ_STS_OFFSET:
        fill_evp_cop_irq_sts_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_STS_OFFSET:
        fill_evp_cop_pri_irq_sts_details(value, new_value);
        break;
    case EVP_COP_FIQ_STS_OFFSET:
        fill_evp_cop_fiq_sts_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_STS_OFFSET:
        fill_evp_cop_pri_fiq_sts_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_0_OFFSET:
        fill_evp_cop_pri_irq_num_0_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_0_OFFSET:
        fill_evp_cop_pri_irq_vec_0_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_1_OFFSET:
        fill_evp_cop_pri_irq_num_1_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_1_OFFSET:
        fill_evp_cop_pri_irq_vec_1_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_2_OFFSET:
        fill_evp_cop_pri_irq_num_2_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_2_OFFSET:
        fill_evp_cop_pri_irq_vec_2_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_3_OFFSET:
        fill_evp_cop_pri_irq_num_3_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_3_OFFSET:
        fill_evp_cop_pri_irq_vec_3_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_4_OFFSET:
        fill_evp_cop_pri_irq_num_4_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_4_OFFSET:
        fill_evp_cop_pri_irq_vec_4_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_5_OFFSET:
        fill_evp_cop_pri_irq_num_5_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_5_OFFSET:
        fill_evp_cop_pri_irq_vec_5_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_6_OFFSET:
        fill_evp_cop_pri_irq_num_6_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_6_OFFSET:
        fill_evp_cop_pri_irq_vec_6_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_NUM_7_OFFSET:
        fill_evp_cop_pri_irq_num_7_details(value, new_value);
        break;
    case EVP_COP_PRI_IRQ_VEC_7_OFFSET:
        fill_evp_cop_pri_irq_vec_7_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_NUM_0_OFFSET:
        fill_evp_cop_pri_fiq_num_0_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_VEC_0_OFFSET:
        fill_evp_cop_pri_fiq_vec_0_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_NUM_1_OFFSET:
        fill_evp_cop_pri_fiq_num_1_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_VEC_1_OFFSET:
        fill_evp_cop_pri_fiq_vec_1_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_NUM_2_OFFSET:
        fill_evp_cop_pri_fiq_num_2_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_VEC_2_OFFSET:
        fill_evp_cop_pri_fiq_vec_2_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_NUM_3_OFFSET:
        fill_evp_cop_pri_fiq_num_3_details(value, new_value);
        break;
    case EVP_COP_PRI_FIQ_VEC_3_OFFSET:
        fill_evp_cop_pri_fiq_vec_3_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
