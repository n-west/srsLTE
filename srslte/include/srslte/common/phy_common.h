/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2015 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of the srsLTE library.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

/**********************************************************************************************
 *  File:         phy_common.h
 *
 *  Description:  Common parameters and lookup functions for PHY
 *
 *  Reference:    3GPP TS 36.211 version 10.0.0 Release 10
 *********************************************************************************************/

#ifndef _LTEBASE_
#define _LTEBASE_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "srslte/config.h"

#define SRSLTE_NSUBFRAMES_X_FRAME  10
#define SRSLTE_NSLOTS_X_FRAME      (2*SRSLTE_NSUBFRAMES_X_FRAME)

#define SRSLTE_NSOFT_BITS  250368 // Soft buffer size for Category 1 UE

#define SRSLTE_PC_MAX 23         // Maximum TX power for Category 1 UE (in dBm)

#define SRSLTE_MAX_PORTS     4
#define SRSLTE_MAX_LAYERS    8
#define SRSLTE_MAX_CODEWORDS 2

#define SRSLTE_LTE_CRC24A  0x1864CFB
#define SRSLTE_LTE_CRC24B  0X1800063
#define SRSLTE_LTE_CRC16   0x11021
#define SRSLTE_LTE_CRC8    0x19B

typedef enum {SRSLTE_CP_NORM, SRSLTE_CP_EXT} srslte_cp_t;


#define SRSLTE_CRNTI_START  0x003D
#define SRSLTE_CRNTI_END    0xFFF3
#define SRSLTE_RARNTI_START 0x0001
#define SRSLTE_RARNTI_END   0x003C
#define SRSLTE_SIRNTI       0xFFFF
#define SRSLTE_PRNTI        0xFFFE
#define SRSLTE_MRNTI        0xFFFD

#define SRSLTE_CELL_ID_UNKNOWN         1000

#define SRSLTE_MAX_NSYMB     7

#define SRSLTE_MAX_PRB   110
#define SRSLTE_NRE       12

#define SRSLTE_SYMBOL_SZ_MAX   2048

#define SRSLTE_CP_NORM_NSYMB    7
#define SRSLTE_CP_NORM_SF_NSYMB (2*SRSLTE_CP_NORM_NSYMB)
#define SRSLTE_CP_NORM_0_LEN    160
#define SRSLTE_CP_NORM_LEN      144

#define SRSLTE_CP_EXT_NSYMB     6
#define SRSLTE_CP_EXT_SF_NSYMB  (2*SRSLTE_CP_EXT_NSYMB)
#define SRSLTE_CP_EXT_LEN       512
#define SRSLTE_CP_EXT_7_5_LEN   1024

#define SRSLTE_CP_ISNORM(cp) (cp==SRSLTE_CP_NORM)
#define SRSLTE_CP_ISEXT(cp) (cp==SRSLTE_CP_EXT)
#define SRSLTE_CP_NSYMB(cp) (SRSLTE_CP_ISNORM(cp)?SRSLTE_CP_NORM_NSYMB:SRSLTE_CP_EXT_NSYMB)

#define SRSLTE_CP_LEN(symbol_sz, c)           ((int) ceil((((float) (c)*(symbol_sz))/2048)))
#define SRSLTE_CP_LEN_NORM(symbol, symbol_sz) ((symbol==0)?SRSLTE_CP_LEN((symbol_sz),SRSLTE_CP_NORM_0_LEN):SRSLTE_CP_LEN((symbol_sz),SRSLTE_CP_NORM_LEN))
#define SRSLTE_CP_LEN_EXT(symbol_sz)          (SRSLTE_CP_LEN((symbol_sz),SRSLTE_CP_EXT_LEN))

#define SRSLTE_SLOT_LEN(symbol_sz)     (symbol_sz*15/2)
#define SRSLTE_SF_LEN(symbol_sz)       (symbol_sz*15)
#define SRSLTE_SF_LEN_MAX              (SRSLTE_SF_LEN(SRSLTE_SYMBOL_SZ_MAX))

#define SRSLTE_SLOT_LEN_PRB(nof_prb)   (SRSLTE_SLOT_LEN(srslte_symbol_sz(nof_prb)))
#define SRSLTE_SF_LEN_PRB(nof_prb)     (SRSLTE_SF_LEN(srslte_symbol_sz(nof_prb)))

#define SRSLTE_SLOT_LEN_RE(nof_prb, cp)        (nof_prb*SRSLTE_NRE*SRSLTE_CP_NSYMB(cp))
#define SRSLTE_SF_LEN_RE(nof_prb, cp)          (2*SRSLTE_SLOT_LEN_RE(nof_prb, cp))

#define SRSLTE_TA_OFFSET      (10e-6)

#define SRSLTE_LTE_TS         1.0/(15000.0*2048)

#define SRSLTE_SLOT_IDX_CPNORM(symbol_idx, symbol_sz) (symbol_idx==0?0:(symbol_sz + SRSLTE_CP_LEN(symbol_sz, SRSLTE_CP_NORM_0_LEN) + \
                                                (symbol_idx-1)*(symbol_sz+SRSLTE_CP_LEN(symbol_sz, SRSLTE_CP_NORM_LEN))))
#define SRSLTE_SLOT_IDX_CPEXT(idx, symbol_sz) (idx*(symbol_sz+SRSLTE_CP(symbol_sz, SRSLTE_CP_EXT_LEN)))

#define SRSLTE_RE_IDX(nof_prb, symbol_idx, sample_idx) ((symbol_idx)*(nof_prb)*(SRSLTE_NRE) + sample_idx)

#define SRSLTE_RS_VSHIFT(cell_id) (cell_id%6)

#define SRSLTE_GUARD_RE(nof_prb) ((srslte_symbol_sz(nof_prb)-nof_prb*SRSLTE_NRE)/2)

#define SRSLTE_SYMBOL_HAS_REF(l, cp, nof_ports) ((l == 1 && nof_ports == 4) \
        || l == 0 \
        || l == SRSLTE_CP_NSYMB(cp) - 3)


#define SRSLTE_NOF_LTE_BANDS 29

typedef enum SRSLTE_API { 
  SRSLTE_PHICH_NORM = 0, 
  SRSLTE_PHICH_EXT  
} srslte_phich_length_t;

typedef enum SRSLTE_API { 
  SRSLTE_PHICH_SRSLTE_PHICH_R_1_6 = 0, 
  SRSLTE_PHICH_SRSLTE_PHICH_R_1_2, 
  SRSLTE_PHICH_R_1, 
  SRSLTE_PHICH_R_2
  
} srslte_phich_resources_t;

typedef enum {
  SRSLTE_RNTI_USER = 0,
  SRSLTE_RNTI_SI,
  SRSLTE_RNTI_RAR,
  SRSLTE_RNTI_TEMP,
  SRSLTE_RNTI_SPS,
  SRSLTE_RNTI_PCH,  
  SRSLTE_RNTI_NOF_TYPES
} srslte_rnti_type_t;

typedef struct SRSLTE_API {
  uint32_t nof_prb;
  uint32_t nof_ports; 
  uint32_t bw_idx; 
  uint32_t id;
  srslte_cp_t cp;
  srslte_phich_length_t phich_length;
  srslte_phich_resources_t phich_resources;
}srslte_cell_t;

typedef enum SRSLTE_API {
  SRSLTE_MIMO_TYPE_SINGLE_ANTENNA,
  SRSLTE_MIMO_TYPE_TX_DIVERSITY, 
  SRSLTE_MIMO_TYPE_SPATIAL_MULTIPLEX
} srslte_mimo_type_t;

typedef enum SRSLTE_API {
  SRSLTE_MOD_BPSK = 0, 
  SRSLTE_MOD_QPSK, 
  SRSLTE_MOD_16QAM, 
  SRSLTE_MOD_64QAM
} srslte_mod_t;

typedef struct SRSLTE_API {
  int id;
  float fd;
} srslte_earfcn_t;

enum band_geographical_area {
  SRSLTE_BAND_GEO_AREA_ALL, 
  SRSLTE_BAND_GEO_AREA_NAR, 
  SRSLTE_BAND_GEO_AREA_APAC, 
  SRSLTE_BAND_GEO_AREA_EMEA, 
  SRSLTE_BAND_GEO_AREA_JAPAN, 
  SRSLTE_BAND_GEO_AREA_CALA, 
  SRSLTE_BAND_GEO_AREA_NA
};

SRSLTE_API bool srslte_cell_isvalid(srslte_cell_t *cell);

SRSLTE_API void srslte_cell_fprint(FILE *stream, 
                                   srslte_cell_t *cell, 
                                   uint32_t sfn);

SRSLTE_API bool srslte_cellid_isvalid(uint32_t cell_id);

SRSLTE_API bool srslte_nofprb_isvalid(uint32_t nof_prb);

SRSLTE_API bool srslte_sfidx_isvalid(uint32_t sf_idx);

SRSLTE_API bool srslte_portid_isvalid(uint32_t port_id);

SRSLTE_API bool srslte_N_id_2_isvalid(uint32_t N_id_2);

SRSLTE_API bool srslte_N_id_1_isvalid(uint32_t N_id_1);

SRSLTE_API bool srslte_symbol_sz_isvalid(uint32_t symbol_sz); 

SRSLTE_API int srslte_symbol_sz(uint32_t nof_prb);

SRSLTE_API int srslte_symbol_sz_power2(uint32_t nof_prb); 

SRSLTE_API int srslte_nof_prb(uint32_t symbol_sz);

SRSLTE_API int srslte_sampling_freq_hz(uint32_t nof_prb);

SRSLTE_API uint32_t srslte_re_x_prb(uint32_t ns, 
                                    uint32_t symbol, 
                                    uint32_t nof_ports, 
                                    uint32_t nof_symbols);

SRSLTE_API uint32_t srslte_voffset(uint32_t symbol_id, 
                                   uint32_t cell_id, 
                                   uint32_t nof_ports);

SRSLTE_API int srslte_group_hopping_f_gh(uint32_t f_gh[SRSLTE_NSLOTS_X_FRAME], 
                                         uint32_t cell_id); 

SRSLTE_API uint32_t srslte_N_ta_new_rar(uint32_t ta);

SRSLTE_API uint32_t srslte_N_ta_new(uint32_t N_ta_old, 
                                    uint32_t ta);

SRSLTE_API char *srslte_cp_string(srslte_cp_t cp); 

SRSLTE_API char *srslte_mod_string(srslte_mod_t mod);

SRSLTE_API uint32_t srslte_mod_bits_x_symbol(srslte_mod_t mod);

SRSLTE_API float srslte_band_fd(uint32_t earfcn);

SRSLTE_API int srslte_band_get_fd_band(uint32_t band, 
                                       srslte_earfcn_t *earfcn, 
                                       int earfcn_start, 
                                       int earfcn_end, 
                                       uint32_t max_elems);

SRSLTE_API int srslte_band_get_fd_band_all(uint32_t band, 
                                           srslte_earfcn_t *earfcn, 
                                           uint32_t max_nelems);

SRSLTE_API int srslte_band_get_fd_region(enum band_geographical_area region, 
                                         srslte_earfcn_t *earfcn, 
                                         uint32_t max_elems);

SRSLTE_API int srslte_str2mimotype(char *mimo_type_str, 
                                   srslte_mimo_type_t *type);

SRSLTE_API uint32_t srslte_tti_interval(uint32_t tti1, 
                                        uint32_t tti2); 

#endif
