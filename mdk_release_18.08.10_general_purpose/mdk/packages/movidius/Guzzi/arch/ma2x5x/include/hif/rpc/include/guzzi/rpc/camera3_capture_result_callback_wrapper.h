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
* @file
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

#ifndef _RPC_GUZZI_CAMERA3_CAPTURE_RESULT_CALLBACK_WRAPPER_H
#define _RPC_GUZZI_CAMERA3_CAPTURE_RESULT_CALLBACK_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void guzzi_camera3_capture_result_callback_t(
        void *prv,
        int camera_id,
        unsigned int stream_id,
        unsigned int frame_number,
        void *data,
        unsigned int data_size
    );

int guzzi_camera3_capture_result_callback_set(
        int camera_id,
        void *prv,
        guzzi_camera3_capture_result_callback_t *func
    );
int guzzi_camera3_capture_result_callback_clear(int camera_id);

#ifdef __cplusplus
}
#endif

#endif /* _RPC_GUZZI_CAMERA3_CAPTURE_RESULT_CALLBACK_WRAPPER_H */

