/* =============================================================================
* Copyright (c) 2013-2014 MM Solutions AD
* All rights reserved. Property of MM Solutions AD.
*
* This source code may not be used against the terms and conditions stipulated
* in the licensing agreement under which it has been supplied, or without the
* written permission of MM Solutions. Rights to use, copy, modify, and
* distribute or disclose this source code and its documentation are granted only
* through signed licensing agreement, provided that this copyright notice
* appears in all copies, modifications, and distributions and subject to the
* following conditions:
* THIS SOURCE CODE AND ACCOMPANYING DOCUMENTATION, IS PROVIDED AS IS, WITHOUT
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. MM SOLUTIONS SPECIFICALLY DISCLAIMS
* ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN
* NO EVENT SHALL MM SOLUTIONS BE LIABLE TO ANY PARTY FOR ANY CLAIM, DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
* PROFITS, OR OTHER LIABILITY, ARISING OUT OF THE USE OF OR IN CONNECTION WITH
* THIS SOURCE CODE AND ITS DOCUMENTATION.
* =========================================================================== */
/**
* @file hai_nvm.h
*
* @author ( MM Solutions AD )
*
*/
/* -----------------------------------------------------------------------------
*!
*! Revision History
*! ===================================
*! 05-Nov-2013 : Author ( MM Solutions AD )
*! Created
* =========================================================================== */

#ifndef __HAL_API_EEPROM_H__
#define __HAL_API_EEPROM_H__

#include <osal/osal_stdtypes.h>

//#include <hal/hat_ipipe.h>
#include <hal/hat_eeprom.h>

int hai_otp_version(struct hat_object *obj,
    struct hat_otp_version **ver);

int hai_otp_lsc_array(struct hat_object *obj,
    struct hat_otp_lsc **lsc);

int hai_otp_center_sensetivity(struct hat_object *obj,
    struct hat_otp_center_spot **spot);

int hai_otp_lens_positions(struct hat_object *obj,
    struct hat_otp_lens **lens);

int hai_otp_defect_pixel(struct hat_object *obj,
    struct hat_otp_dpc **dpc);

int hai_otp_get_black_level(struct hat_object *obj,
    struct hat_otp_black_vs_gain **blevel);

#endif // __HAL_API_EEPROM_H__

