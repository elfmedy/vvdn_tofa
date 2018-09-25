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

#include <osal/osal_stdtypes.h>
#include <osal/osal_stdlib.h>
#include <osal/osal_mutex.h>
#include <utils/mms_debug.h>

#include <camera.h>
#include <camera_config_index.h>
#include <camera_config_struct.h>

#include "camera_control.h"

mmsdbg_define_variable(
        vdl_camera_control,
        DL_DEFAULT,
        0,
        "vdl_camera_control",
        "Camera Control."
    );
#define MMSDEBUGLEVEL mmsdbg_use_variable(vdl_camera_control)

#ifndef GUZZI_INSTANCES_MAX
#define GUZZI_INSTANCES_MAX 3
#endif

typedef struct {
    camera_t *camera;
    osal_sem *cmd_sem;
    osal_mutex *config_mutex;
    int configs_to_skip;
    int stop;
    int start_err;
    guzzi_camera3_controls_capture_request_guzzi_fr_id_t guzzi_fr_id;
} camera_control_t;

static camera_control_t g_camera_control[GUZZI_INSTANCES_MAX];

static void callback(
        camera_t *camera,
        void *app_prv_void,
        camera_event_t event,
        int datan,
        void *datap
    )
{
    camera_control_t *camera_control;

    camera_control = app_prv_void;

    UNUSED(camera);
    UNUSED(datap);

    switch (event.type) {
        case CAMERA_EVENT_ERROR:
            mmsdbg(DL_ERROR, "Camera CB ERROR event.");
            break;
        case CAMERA_EVENT_ERROR_START:
            mmsdbg(DL_ERROR, "Camera CB ERROR_START event.");
            camera_control->start_err = -1;
            osal_sem_post(camera_control->cmd_sem);
            break;
        case CAMERA_EVENT_START_DONE:
            mmsdbg(DL_ERROR, "Camera CB START_DONE event.");
            osal_sem_post(camera_control->cmd_sem);
            break;
        case CAMERA_EVENT_STOP_DONE:
            mmsdbg(DL_MESSAGE, "Camera CB STOP_DONE event.");
            osal_sem_post(camera_control->cmd_sem);
            break;
        case CAMERA_EVENT_FLUSH_DONE:
            mmsdbg(DL_MESSAGE, "Camera CB FLUSH_DONE event.");
            osal_sem_post(camera_control->cmd_sem);
            break;
        case CAMERA_EVENT_PROCESS_DONE:
            mmsdbg(DL_MESSAGE, "Camera CB PROCESS_DONE event.");
            break;
        case CAMERA_EVENT_BUFFER_FLUSH:
            mmsdbg(DL_MESSAGE, "Camera CB BUFFER_FLUSH event.");
            break;
        case CAMERA_EVENT_GENERIC:
            mmsdbg(DL_MESSAGE, "Camera CB GENERIC event: sub_type=%d, num=%d.", event.sub_type, datan);

            osal_mutex_lock(camera_control->config_mutex);
            if (camera_control->stop == 0)
            {
                if (!camera_control->configs_to_skip) {
                    camera_control->guzzi_fr_id.v++;
                    camera_config_set_begin(camera_control->camera);
                    camera_config_set(
                            camera_control->camera,
                            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
                            &camera_control->guzzi_fr_id
                        );
                    camera_config_set_end(camera_control->camera);
                } else {
                    camera_control->configs_to_skip--;
                }
            }
            osal_mutex_unlock(camera_control->config_mutex);
            break;
        default:
            mmsdbg(DL_ERROR, "Unkonw camera event (%d)!", event.v);
    }
}

uint32_t camera_control_is_active(int cam_id)
{
    return (g_camera_control[cam_id].camera != NULL);
}


void camera_control_start(int cam_id)
{
    camera_control_t *camera_control;
    camera_create_params_t create_params;
    guzzi_camera3_dynamic_control_af_mode_t af_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    camera_control->cmd_sem = osal_sem_create(0);
    if (!camera_control->cmd_sem) {
        mmsdbg(DL_ERROR, "Failed to create camera control command semphore!");
        goto exit1;
    }
    camera_control->config_mutex = osal_mutex_create();
    if (!camera_control->config_mutex) {
        mmsdbg(DL_ERROR, "Failed to create camera control config mutex!");
        goto exit2;
    }

    create_params.camera_id = cam_id;
    create_params.mode = CAMERA_MODE_MOV_CONFIG_DRIVEN;
    create_params.dtp_server = NULL;
    create_params.callback = callback;
    create_params.app_prv = camera_control;
    camera_control->camera = camera_create(&create_params);
    if (!camera_control->camera) {
        mmsdbg(DL_ERROR, "Failed to create camera!");
        goto exit3;
    }

    err = camera_start(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Failed to start camera!");
        goto exit3;
    }
    mmsdbg(DL_ERROR, "Camera_id = %d started.\n", cam_id);
    osal_sem_wait(camera_control->cmd_sem);
    if (camera_control->start_err) {
        mmsdbg(DL_ERROR, "Failed to start camera!");
        goto exit3;
    }

    camera_control->guzzi_fr_id.v = 0;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_OFF;
    camera_config_set_begin(camera_control->camera);
    camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AF_MODE,
            &af_mode
        );
    camera_config_set_end(camera_control->camera);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    camera_config_set_end(camera_control->camera);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    camera_config_set_end(camera_control->camera);

    camera_control->configs_to_skip = 0;

    osal_mutex_unlock(camera_control->config_mutex);

    return;
//exit4:
//    camera_destroy(camera_control->camera);
exit3:
    osal_mutex_destroy(camera_control->config_mutex);
exit2:
    osal_sem_destroy(camera_control->cmd_sem);
exit1:
    camera_control->camera = NULL;
    return;
}

void camera_control_stop(int cam_id)
{
    camera_control_t *camera_control;

    camera_control = &g_camera_control[cam_id];
    int err;

    if (!camera_control->camera) {
        return;
    }
    osal_mutex_lock(camera_control->config_mutex);
    camera_control->stop = 1;
    osal_mutex_unlock(camera_control->config_mutex);

    camera_flush(camera_control->camera);
    osal_sem_wait(camera_control->cmd_sem);

    err = camera_stop(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Failed to stop camera!");
    }
    osal_sem_wait(camera_control->cmd_sem);
    mmsdbg(DL_ERROR, "Camera id = %d stopped.\n", cam_id);

    camera_destroy(camera_control->camera);
    osal_mutex_destroy(camera_control->config_mutex);
    osal_sem_destroy(camera_control->cmd_sem);

    camera_control->camera = NULL;
    camera_control->stop = 0;
}

void camera_control_capture(int cam_id)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_capture_intent_t intent_req;
    int err;

    camera_control = &g_camera_control[cam_id];

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    intent_req.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_ZERO_SHUTTER_LAG;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_CAPTURE_INTENT,
            &intent_req
        );
    camera_config_set_end(camera_control->camera);

    camera_control->guzzi_fr_id.v++;
    intent_req.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_PREVIEW;
    camera_config_set_begin(camera_control->camera);
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_CAPTURE_INTENT,
            &intent_req
        );
    camera_config_set_end(camera_control->camera);

    if (err) {
        mmsdbg(DL_ERROR, "Capture failed.\n");
    } else {
        mmsdbg(DL_ERROR, "Camera id = %d capture succeeded.\n", cam_id);
    }

    camera_control->configs_to_skip = 1;

    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_lens_move(int cam_id, int lens_position)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_lens_focal_length_t foc_len;
    guzzi_camera3_dynamic_control_af_mode_t af_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    if (lens_position > 255) {
        lens_position = 255;
    }

    if (lens_position < 0) {
        lens_position = 0;
    }

    foc_len.v   = (float) lens_position / 255.0;
    af_mode.v   = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_OFF;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;

    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AF_MODE,
            &af_mode
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_LENS_FOCAL_LENGTH,
            &foc_len
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Lens move failed.\n");
    } else {
        mmsdbg(DL_ERROR, "Lens move succeeded camera_id = %d, lens_position = %d.\n", cam_id, lens_position);
    }

    camera_control->configs_to_skip = 1;

    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_focus_trigger(int cam_id)
{
    camera_control_t *camera_control;
    static guzzi_camera3_dynamic_control_af_mode_t af_mode;
    static guzzi_camera3_dynamic_control_af_trigger_id_t af_trigger;
    int err;

    camera_control  = &g_camera_control[cam_id];

    af_mode.v       = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_AUTO;
    af_trigger.v    = GUZZI_CAMERA3_ENUM_CONTROL_AF_TRIGGER_START;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AF_MODE,
            &af_mode
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AF_TRIGGER,
            &af_trigger
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Focus trigger failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Focus trigger succeeded camera_id = %d.\n", cam_id);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_ae_manual(
        int cam_id,
        uint32_t time_us,
        uint32_t sensitivity_iso,
        uint32_t frame_duration_us
    )
{
    camera_control_t *camera_control;
    guzzi_camera3_dynamic_sensor_exposure_time_t sensor_exposure_time;
    guzzi_camera3_dynamic_sensor_sensitivity_t sensor_sensitivity;
    guzzi_camera3_dynamic_sensor_frame_duration_t sensor_frame_duration;
    guzzi_camera3_controls_control_ae_mode_t ae_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    sensor_exposure_time.v = 1000 * time_us;
    sensor_sensitivity.v = sensitivity_iso;
    sensor_frame_duration.v = 1000 * frame_duration_us;
    ae_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_MODE_OFF;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_SENSOR_EXPOSURE_TIME,
            &sensor_exposure_time
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_SENSOR_SENSITIVITY,
            &sensor_sensitivity
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_SENSOR_FRAME_DURATION,
            &sensor_frame_duration
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_MODE,
            &ae_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Manual ae failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Manual ae succeeded camera_id = %d, time_us = %d, "
                "sensitivity_iso = %d, frame_duration_us = %d.\n",
                cam_id, (int)time_us, (int)sensitivity_iso, (int)frame_duration_us);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_ae_auto(int cam_id, uint32_t flash_mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_ae_mode_t ae_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (flash_mode) {
        case CAMERA_CONTROL__AE_AUTO__FLASH_MODE__OFF:
            ae_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_MODE_ON;
            break;
        case CAMERA_CONTROL__AE_AUTO__FLASH_MODE__AUTO:
            ae_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_MODE_ON_AUTO_FLASH;
            break;
        case CAMERA_CONTROL__AE_AUTO__FLASH_MODE__ALWAYS:
            ae_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_MODE_ON_ALWAYS_FLASH;
            break;
        case CAMERA_CONTROL__AE_AUTO__FLASH_MODE__AUTO_REDEYE:
            ae_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_MODE_ON_AUTO_FLASH_REDEYE;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown flash mode: %d!", (int)flash_mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_MODE,
            &ae_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Auto ae failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Auto ae succeeded camera_id = %d.\n", cam_id);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_awb_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_awb_mode_t awb_mode;
    guzzi_camera3_controls_control_mode_t ctrl_mode;
    int err;

    camera_control = &g_camera_control[cam_id];
    ctrl_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_MODE_AUTO;

    switch (mode) {
        case CAMERA_CONTROL__AWB_MODE__OFF:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_OFF;
            break;
        case CAMERA_CONTROL__AWB_MODE__AUTO:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_AUTO;
            break;
        case CAMERA_CONTROL__AWB_MODE__INCANDESCENT:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_INCANDESCENT;
            break;
        case CAMERA_CONTROL__AWB_MODE__FLUORESCENT:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_FLUORESCENT;
            break;
        case CAMERA_CONTROL__AWB_MODE__WARM_FLUORESCENT:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_WARM_FLUORESCENT;
            break;
        case CAMERA_CONTROL__AWB_MODE__DAYLIGHT:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_DAYLIGHT;
            break;
        case CAMERA_CONTROL__AWB_MODE__CLOUDY_DAYLIGHT:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_CLOUDY_DAYLIGHT;
            break;
        case CAMERA_CONTROL__AWB_MODE__TWILIGHT:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_TWILIGHT;
            break;
        case CAMERA_CONTROL__AWB_MODE__SHADE:
            awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_SHADE;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown awb mode: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    //mmsdbg(DL_ERROR, "Set awb mode failed.\n");
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_MODE,
            &ctrl_mode
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AWB_MODE,
            &awb_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set awb mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Awb mode set succeeded camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_scene_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_scene_mode_t scene_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (mode) {
        case CAMERA_CONTROL__SCENE_MODE__UNSUPPORTED:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_UNSUPPORTED;
            break;
        case CAMERA_CONTROL__SCENE_MODE__FACE_PRIORITY:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_FACE_PRIORITY;
            break;
        case CAMERA_CONTROL__SCENE_MODE__ACTION:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_ACTION;
            break;
        case CAMERA_CONTROL__SCENE_MODE__PORTRAIT:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_PORTRAIT;
            break;
        case CAMERA_CONTROL__SCENE_MODE__LANDSCAPE:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_LANDSCAPE;
            break;
        case CAMERA_CONTROL__SCENE_MODE__NIGHT:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_NIGHT;
            break;
        case CAMERA_CONTROL__SCENE_MODE__NIGHT_PORTRAIT:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_NIGHT_PORTRAIT;
            break;
        case CAMERA_CONTROL__SCENE_MODE__THEATRE:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_THEATRE;
            break;
        case CAMERA_CONTROL__SCENE_MODE__BEACH:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_BEACH;
            break;
        case CAMERA_CONTROL__SCENE_MODE__SNOW:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_SNOW;
            break;
        case CAMERA_CONTROL__SCENE_MODE__SUNSET:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_SUNSET;
            break;
        case CAMERA_CONTROL__SCENE_MODE__STEADYPHOTO:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_STEADYPHOTO;
            break;
        case CAMERA_CONTROL__SCENE_MODE__FIREWORKS:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_FIREWORKS;
            break;
        case CAMERA_CONTROL__SCENE_MODE__SPORTS:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_SPORTS;
            break;
        case CAMERA_CONTROL__SCENE_MODE__PARTY:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_PARTY;
            break;
        case CAMERA_CONTROL__SCENE_MODE__CANDLELIGHT:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_CANDLELIGHT;
            break;
        case CAMERA_CONTROL__SCENE_MODE__BARCODE:
            scene_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_SCENE_MODE_BARCODE;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown awb mode: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    //mmsdbg(DL_ERROR, "Set awb mode failed.\n");

    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_SCENE_MODE,
            &scene_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set scene mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Scene mode set succeeded camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_antibanding_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_ae_antibanding_mode_t antibanding_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (mode) {
        case CAMERA_CONTROL__AE_ANTIBANDING_MODE__OFF:
            antibanding_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_ANTIBANDING_MODE_OFF;
            break;
        case CAMERA_CONTROL__AE_ANTIBANDING_MODE__50HZ:
            antibanding_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_ANTIBANDING_MODE_50HZ;
            break;
        case CAMERA_CONTROL__AE_ANTIBANDING_MODE__60HZ:
            antibanding_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_ANTIBANDING_MODE_60HZ;
            break;
        case CAMERA_CONTROL__AE_ANTIBANDING_MODE__AUTO:
            antibanding_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_ANTIBANDING_MODE_AUTO;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown antibanding mode: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_ANTIBANDING_MODE,
            &antibanding_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set antibanding mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Antibanding mode set succeeded camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_ae_lock_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_ae_lock_t ae_lock_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (mode) {
        case CAMERA_CONTROL__AE_LOCK__OFF:
            ae_lock_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_LOCK_OFF;
            break;
        case CAMERA_CONTROL__AE_LOCK__ON:
            ae_lock_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_LOCK_ON;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown ae_lock command: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_LOCK,
            &ae_lock_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set ae_lock control mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Ae_lock control succeeded: camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_ae_target_fps_range(int cam_id, uint32_t min_fps, uint32_t max_fps)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_ae_target_fps_range_t target_fps_range;
    guzzi_camera3_static_control_ae_available_target_fps_ranges_t check;
    int err;

    camera_control = &g_camera_control[cam_id];
    target_fps_range.dim_size_1 =
            GUZZI_CAMERA3_STATIC_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES_DIM_MAX_SIZE_1;
    target_fps_range.v[0] = min_fps;
    target_fps_range.v[1] = max_fps;

    camera_config_get(
                camera_control->camera,
                GUZZI_CAMERA3_INDEX_STATIC_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES,
                &check
            );
    mmsdbg(DL_ERROR, "Available ranges: dim1:%d, dim2:%d\n",
            check.dim_size_1, check.dim_size_2);

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_TARGET_FPS_RANGE,
            &target_fps_range
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set target_fps control mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Target_fps set succeeded: camera_id = %d, min_fps = %d, max_fps = %d.\n",
                cam_id, (int)min_fps, (int)max_fps);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_awb_lock_mode(int cam_id, uint32_t type)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_awb_lock_t awb_lock_control;
    guzzi_camera3_controls_control_awb_mode_t awb_mode;
    int err;

    camera_control = &g_camera_control[cam_id];
    awb_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_MODE_AUTO;

    switch (type) {
        case CAMERA_CONTROL__AWB_LOCK__OFF:
            awb_lock_control.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_LOCK_OFF;
            break;
        case CAMERA_CONTROL__AWB_LOCK__ON:
            awb_lock_control.v = GUZZI_CAMERA3_ENUM_CONTROL_AWB_LOCK_ON;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown awb_lock command: %d!", (int)type);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AWB_MODE,
            &awb_mode
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AWB_LOCK,
            &awb_lock_control
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set awb_lock control mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Awb_lock control succeeded: camera_id = %d, mode = %d.\n", cam_id, (int)type);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_capture_intent(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_capture_intent_t capture_intent;
    guzzi_camera3_controls_control_mode_t ctrl_mode;
    int err;

    camera_control = &g_camera_control[cam_id];
    ctrl_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_MODE_AUTO;

    switch (mode) {
        case CAMERA_CONTROL__CAPTURE_INTENT__CUSTOM:
            capture_intent.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_CUSTOM;
            break;
        case CAMERA_CONTROL__CAPTURE_INTENT__PREVIEW:
            capture_intent.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_PREVIEW;
            break;
        case CAMERA_CONTROL__CAPTURE_INTENT__STILL_CAPTURE:
            capture_intent.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_STILL_CAPTURE;
            break;
        case CAMERA_CONTROL__CAPTURE_INTENT__VIDEO_RECORD:
            capture_intent.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_VIDEO_RECORD;
            break;
        case CAMERA_CONTROL__CAPTURE_INTENT__VIDEO_SNAPSHOT:
            capture_intent.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_VIDEO_SNAPSHOT;
            break;
        case CAMERA_CONTROL__CAPTURE_INTENT__ZERO_SHUTTER_LAG:
            capture_intent.v = GUZZI_CAMERA3_ENUM_CONTROL_CAPTURE_INTENT_ZERO_SHUTTER_LAG;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown capture_intent command: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_MODE,
            &ctrl_mode
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_CAPTURE_INTENT,
            &capture_intent
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set capture_intent control mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Capture_intent control succeeded: camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_mode_t ctrl_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (mode) {
        case CAMERA_CONTROL__MODE__OFF:
            ctrl_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_MODE_OFF;
            break;
        case CAMERA_CONTROL__MODE__AUTO:
            ctrl_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_MODE_AUTO;
            break;
        case CAMERA_CONTROL__MODE__USE_SCENE_MODE:
            ctrl_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_MODE_USE_SCENE_MODE;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown ctrl_mode command: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_MODE,
            &ctrl_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set control mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Control mode set succeeded: camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_frame_duration(int cam_id, uint64_t val)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_sensor_frame_duration_t frame_duration;
    int err;

    camera_control = &g_camera_control[cam_id];
    frame_duration.v = val;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_SENSOR_FRAME_DURATION,
            &frame_duration
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set sensor frame duration failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Sensor frame duration set succeeded: camera_id = %d, duration = %d.\n", cam_id, (int)val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}


void camera_control_exp_compensation(int cam_id, uint32_t val)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_ae_exposure_compensation_t exp_compensation;
    int err;

    camera_control = &g_camera_control[cam_id];
    exp_compensation.v = val;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_EXPOSURE_COMPENSATION,
            &exp_compensation
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set exposure compensation failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Exposure compensation set succeeded: camera_id = %d, val = %d.\n", cam_id, (int)val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_sensitivity(int cam_id, uint32_t iso_val)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_sensor_sensitivity_t sensitivity;
    //guzzi_camera3_dynamic_sensor_sensitivity_t sensitivity;
    guzzi_camera3_controls_control_ae_mode_t ae_mode;
    int err;

    camera_control = &g_camera_control[cam_id];
    sensitivity.v = iso_val;
    ae_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AE_MODE_OFF;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_SENSOR_SENSITIVITY,
            &sensitivity
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AE_MODE,
            &ae_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set ISO failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "ISO set succeeded: camera_id = %d, val = %d.\n", cam_id, (int)iso_val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_effect_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_effect_mode_t effect_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (mode) {
        case CAMERA_CONTROL__EFFECT_MODE__OFF:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_OFF;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__MONO:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_MONO;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__NEGATIVE:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_NEGATIVE;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__SOLARIZE:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_SOLARIZE;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__SEPIA:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_SEPIA;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__POSTERIZE:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_POSTERIZE;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__WHITEBOARD:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_WHITEBOARD;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__BLACKBOARD:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_BLACKBOARD;
            break;
        case CAMERA_CONTROL__EFFECT_MODE__AQUA:
            effect_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_EFFECT_MODE_AQUA;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown awb mode: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    //mmsdbg(DL_ERROR, "Set awb mode failed.\n");
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_EFFECT_MODE,
            &effect_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set effect mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Effect mode set succeeded camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_af_mode(int cam_id, uint32_t mode)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_control_af_mode_t af_mode;
    int err;

    camera_control = &g_camera_control[cam_id];

    switch (mode) {
        case CAMERA_CONTROL__AF_MODE_OFF:
            af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_OFF;
            break;
        case CAMERA_CONTROL__AF_MODE_AUTO:
            af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_AUTO;
            break;
        case CAMERA_CONTROL__AF_MODE_MACRO:
            af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_MACRO;
            break;
        case CAMERA_CONTROL__AF_MODE_CONTINUOUS_VIDEO:
            af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_CONTINUOUS_VIDEO;
            break;
        case CAMERA_CONTROL__AF_MODE_CONTINUOUS_PICTURE:
            af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_CONTINUOUS_PICTURE;
            break;
        case CAMERA_CONTROL__AF_MODE_EDOF:
            af_mode.v = GUZZI_CAMERA3_ENUM_CONTROL_AF_MODE_EDOF;
            break;
        default:
            mmsdbg(DL_ERROR, "Unknown af mode: %d!", (int)mode);
            return;
    }

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CONTROL_AF_MODE,
            &af_mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set af mode failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Af mode set succeeded camera_id = %d, mode = %d.\n", cam_id, (int)mode);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_noise_reduction_strength(int cam_id, uint32_t strength_val)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_noise_reduction_strength_t strength;
    guzzi_camera3_controls_noise_reduction_mode_t mode;
    int err;

    camera_control = &g_camera_control[cam_id];
    strength.v = strength_val;
    mode.v = GUZZI_CAMERA3_ENUM_NOISE_REDUCTION_MODE_FAST;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_NOISE_REDUCTION_STRENGTH,
            &strength
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_NOISE_REDUCTION_MODE,
            &mode
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set noise reduction strength failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Noise reduction strength set succeeded: camera_id = %d, val = %d.\n",
                cam_id, (int)strength_val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_saturation(int cam_id, uint32_t saturation_val)
{
    camera_control_t *camera_control;
    //guzzi_camera3_controls_noise_reduction_strength_t strength;
    int err;

    camera_control = &g_camera_control[cam_id];
    //strength.v = saturation_val;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    /*err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_NOISE_REDUCTION_STRENGTH,
            &strength
        );*/
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set saturation failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Saturation set succeeded: camera_id = %d, saturation_val = %d.\n",
                cam_id, (int)saturation_val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_brightness(int cam_id, uint32_t brightness_val)
{
    camera_control_t *camera_control;
    //guzzi_camera3_controls_noise_reduction_strength_t brightness;
    int err;

    camera_control = &g_camera_control[cam_id];
    //brightness.v = brightness_val;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    /*err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_NOISE_REDUCTION_STRENGTH,
            &brightness
        );*/
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set brightness failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Brightness set succeeded: camera_id = %d, brightness_val = %d.\n",
                cam_id, (int)brightness_val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}

void camera_control_format(int cam_id, uint32_t format_type)
{
//    camera_control_t *camera_control;
//    guzzi_camera3_controls_stream_config_format_t format;
//    int err;

//    camera_control = &g_camera_control[cam_id];
//    format.dim_size_1 = 1;
//    format.v[0] = format_type;

    mmsdbg(DL_ERROR,
                    "Stream format set succeeded: camera_id = %d, format = %d.\n",
                    cam_id, (int)format_type);

    /*osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);

    SET(GUZZI_CAMERA3_INDEX_CONTROLS_STREAM_CONFIG_FORMAT, &format);

    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set stream format failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Stream format set succeeded: camera_id = %d, format = %d.\n",
                cam_id, format_type);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);*/
}

void camera_control_resolution(int cam_id, uint32_t w, uint32_t h)
{
//   camera_control_t *camera_control;
//    guzzi_camera3_controls_stream_config_width_t width;
//    guzzi_camera3_controls_stream_config_height_t height;
//    int err;

//    camera_control = &g_camera_control[cam_id];
//    width.dim_size_1 = 1;
//    width.v[0] = w;
//    height.dim_size_1 = 1;
//    height.v[0] = w;

    mmsdbg(DL_ERROR,
                    "Resolution received: camera_id = %d, width = %d height = %d.\n",
                    cam_id, (int)w, (int)h);

    /*osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);

    SET(GUZZI_CAMERA3_INDEX_CONTROLS_STREAM_CONFIG_FORMAT, &format);

    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set stream format failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Stream format set succeeded: camera_id = %d, format = %d.\n",
                cam_id, format_type);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);*/
}

void camera_control_sharpness(int cam_id, uint32_t sharpness_val)
{
    camera_control_t *camera_control;
    guzzi_camera3_controls_edge_strength_t sharpness;
    int err;

    camera_control = &g_camera_control[cam_id];
    sharpness.v = sharpness_val;

    osal_mutex_lock(camera_control->config_mutex);

    camera_control->guzzi_fr_id.v++;
    camera_config_set_begin(camera_control->camera);
    err = camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_CAPTURE_REQUEST_GUZZI_FR_ID,
            &camera_control->guzzi_fr_id
        );
    err += camera_config_set(
            camera_control->camera,
            GUZZI_CAMERA3_INDEX_CONTROLS_EDGE_STRENGTH,
            &sharpness
        );
    camera_config_set_end(camera_control->camera);
    if (err) {
        mmsdbg(DL_ERROR, "Set sharpness failed.\n");
    } else {
        mmsdbg(DL_ERROR,
                "Sharpness set succeeded: camera_id = %d, sharpness_val = %d.\n",
                cam_id, (int)sharpness_val);
    }
    camera_control->configs_to_skip = 1;
    osal_mutex_unlock(camera_control->config_mutex);
}
