///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Application configuration Leon header
///

#ifndef _VIDEODEMO_H_
#define _VIDEODEMO_H_

// 1: Includes
// ----------------------------------------------------------------------------
#include "protovideo.h"
#include "ucallback.h"
#include "mv_types.h"
#include "UsbSend.h"

__TMS_TYPE_DEF_STRUCT(VIDEODEMO_CONTEXT);
__TMS_TYPE_DEF_STRUCT(VIDEODEMO_BUFFER_HDR);
__TMS_TYPE_DEF_STRUCT(VIDEODEMO_BUFFER);
__TMS_TYPE_DEF_STRUCT(PROCESSING_UNIT);
__TMS_TYPE_DEF_STRUCT(CAMERA_TERMINAL);
__TMS_TYPE_DEF_STRUCT(PROBE_COMMIT);
__TMS_TYPE_DEF_STRUCT(STILL_PROBE_COMMIT);

// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------
#define USB_HIGH_SPEED   2
#define USB_SUPER_SPEED  3

#ifndef    VIDEODEMO_CONFIG_CONTROLBUFFER_SIZE    /*PARAM*/
# define VIDEODEMO_CONFIG_CONTROLBUFFER_SIZE    (32)
#endif

#ifndef    VIDEODEMO_CONFIG_MAXQUEUED_BUFFER    /*PARAM*/
# define VIDEODEMO_CONFIG_MAXQUEUED_BUFFER    (16)
#endif

#if USE_STATIC_FRAME_BUFFER
    #define STATIC_FRAME_BUFFER_WIDTH       (640)
    #define STATIC_FRAME_BUFFER_HEIGHT      (480)
    #define STATIC_FRAME_BPP                (2)
    #define STATIC_FRAME_LINE_SIZE          (STATIC_FRAME_BUFFER_WIDTH * STATIC_FRAME_BPP)
    #define STATIC_FRAME_SIZE               (STATIC_FRAME_LINE_SIZE * STATIC_FRAME_BUFFER_HEIGHT)
    // The bytes of data between 2 header
    #define UVC_PAYLOAD_HEADER_SIZE         (12)
    #define UVC_PAYLOAD_HEADER_OFFSET       (16)
#endif // USE_STATIC_FRAME_BUFFER

// The bytes of data between 2 header
#define PAYLOAD_HEADER_SIZE        (12)

#define UNCOMPRESSED_HDR_HLE_OFFSET        0
#define UNCOMPRESSED_HDR_BFH_OFFSET        1
#define UNCOMPRESSED_HDR_PTS_OFFSET        2
#define UNCOMPRESSED_HDR_SCR_STC_OFFSET    6
#define UNCOMPRESSED_HDR_SCR_SOF_OFFSET    10
#define UNCOMPRESSED_HDR_EOH            (1 << 7)
#define UNCOMPRESSED_HDR_ERR            (1 << 6)
#define UNCOMPRESSED_HDR_STI            (1 << 5)
#define UNCOMPRESSED_HDR_RES            (1 << 4)
#define UNCOMPRESSED_HDR_SCR            (1 << 3)
#define UNCOMPRESSED_HDR_PTS            (1 << 2)
#define UNCOMPRESSED_HDR_EOF            (1 << 1)
#define UNCOMPRESSED_HDR_FID            (1 << 0)

/* Constants of Camera Terminal */
#define CT_IRIS_ABSOLUTE_CONTROL_INFO   0x0000
#define CT_IRIS_ABSOLUTE_CONTROL_MIN    0x0000
#define CT_IRIS_ABSOLUTE_CONTROL_MAX    0xFFFF
#define CT_IRIS_ABSOLUTE_CONTROL_RES    0x0001
#define CT_IRIS_ABSOLUTE_CONTROL_DEF    0x0000

/* Constants of Processing Unit */
#define PU_BACKLIGHT_COMPENSATION_CONTROL_INFO   0x03
#define PU_BACKLIGHT_COMPENSATION_CONTROL_MIN    0x0000
#define PU_BACKLIGHT_COMPENSATION_CONTROL_MAX    0x0003
#define PU_BACKLIGHT_COMPENSATION_CONTROL_RES    0x0001
#define PU_BACKLIGHT_COMPENSATION_CONTROL_DEF    0x0000

#define PU_BRIGHTNESS_CONTROL_INFO       0x03
#define PU_BRIGHTNESS_CONTROL_MIN        0x0000
#define PU_BRIGHTNESS_CONTROL_MAX        0x00FF
#define PU_BRIGHTNESS_CONTROL_RES        0x0001
#define PU_BRIGHTNESS_CONTROL_DEF        0x007F

#define PU_CONTRAST_CONTROL_INFO           0x03
#define PU_CONTRAST_CONTROL_MIN            0x0000
#define PU_CONTRAST_CONTROL_MAX            0x00FF
#define PU_CONTRAST_CONTROL_RES            0x0001
#define PU_CONTRAST_CONTROL_DEF            0x007F

#define PU_POWER_LINE_FREQUENCY_CONTROL_INFO   0x03
#define PU_POWER_LINE_FREQUENCY_CONTROL_MIN    0x00
#define PU_POWER_LINE_FREQUENCY_CONTROL_MAX    0x02
#define PU_POWER_LINE_FREQUENCY_CONTROL_RES    0x01
#define PU_POWER_LINE_FREQUENCY_CONTROL_DEF    0x01

#define PU_HUE_CONTROL_INFO           0x03
#define PU_HUE_CONTROL_MIN            0x0000
#define PU_HUE_CONTROL_MAX            0x0168
#define PU_HUE_CONTROL_RES            0x0064
#define PU_HUE_CONTROL_DEF            0x0000

#define PU_SATURATION_CONTROL_INFO       0x03
#define PU_SATURATION_CONTROL_MIN        0x0000
#define PU_SATURATION_CONTROL_MAX        0x00FF
#define PU_SATURATION_CONTROL_RES        0x0001
#define PU_SATURATION_CONTROL_DEF        0x007F

#define PU_SHARPNESS_CONTROL_INFO       0x03
#define PU_SHARPNESS_CONTROL_MIN        0x0000
#define PU_SHARPNESS_CONTROL_MAX        0x000F
#define PU_SHARPNESS_CONTROL_RES        0x0001
#define PU_SHARPNESS_CONTROL_DEF        0x0000

#define PU_GAMMA_CONTROL_INFO           0x03
#define PU_GAMMA_CONTROL_MIN            0x0064
#define PU_GAMMA_CONTROL_MAX            0x00DC
#define PU_GAMMA_CONTROL_RES            0x003C
#define PU_GAMMA_CONTROL_DEF            0x00A0

#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL_INFO   0x03
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL_MIN    0x0AFA
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL_MAX    0x1964
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL_RES    0x03E8
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL_DEF    0x16A8

#define PU_HUE_AUTO_CONTROL_INFO        0x1
#define PU_HUE_AUTO_CONTROL_MIN         0x0
#define PU_HUE_AUTO_CONTROL_MAX         0x1
#define PU_HUE_AUTO_CONTROL_RES         0x1
#define PU_HUE_AUTO_CONTROL_DEF         0x0

#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL_INFO  0x01
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL_MIN   0x00
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL_MAX   0xFF
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL_RES   0x01
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL_DEF   0x01

// Constants of Probe/Commit
#define PROBE_DEFAULT_bmHint              0x0000
#define PROBE_DEFAULT_bFormatIndex        0x01
#define PROBE_DEFAULT_bFrameIndex         0x01
#define PROBE_DEFAULT_dwFrameInterval     166666
#define PROBE_DEFAULT_wKeyFrameRate       0x0001
#define PROBE_DEFAULT_wPFrameRate         0x0000
#define PROBE_DEFAULT_wCompQuality        0x0000
#define PROBE_DEFAULT_wCompWindowSize     0x0000
#define PROBE_DEFAULT_wDelay              0x000

#define CAM_WINDOW_DEFAULT_WIDTH    SEND_OUT_MAX_WIDTH //the current width must be x16
#define CAM_WINDOW_DEFAULT_HEIGHT   SEND_OUT_MAX_HEIGHT
#define CAM_FRAME_DEFAULT_SIZE_BYTES   CAM_WINDOW_DEFAULT_WIDTH * CAM_WINDOW_DEFAULT_HEIGHT

#define PROBE_DEFAULT_dwMaxVideoFrameSize         (CAM_WINDOW_DEFAULT_WIDTH * CAM_WINDOW_DEFAULT_HEIGHT * 2 + PAYLOAD_HEADER_SIZE)
#define PROBE_DEFAULT_dwMaxPayloadTransferSize    (614400 * 2 + PAYLOAD_HEADER_SIZE)
/* number of payloads is depending on PROBE_DEFAULT_dwMaxPayloadTransferSize */
#ifndef SEND_OUT_USB_NO_OF_PAYLOAD_MAX
#define SEND_OUT_USB_NO_OF_PAYLOAD_MAX 20
#endif

#define PROBE_DEFAULT_dwClockFrequency   0x00000000
#define PROBE_DEFAULT_bmFramingInfo      0x03
#define PROBE_DEFAULT_bPreferedVersion   0x00
#define PROBE_DEFAULT_bMinVersion        0x00
#define PROBE_DEFAULT_bMaxVersion        0x00

// Constants of Still Image Probe/Commit
#define STILL_PROBE_DEFAULT_bFormatIndex              0x01
#define STILL_PROBE_DEFAULT_bFrameIndex               0x01
#define STILL_PROBE_DEFAULT_bCompressionIndex         0x00
#define STILL_PROBE_DEFAULT_dwMaxVideoFrameSize       PROBE_DEFAULT_dwMaxVideoFrameSize
#define STILL_PROBE_DEFAULT_dwMaxPayLoadTransferSize  PROBE_DEFAULT_dwMaxPayloadTransferSize

// constants of STILL_IMAGE_TRIGGER_CONTROL
#define STILL_IMAGE_NORMAL_OPERATION          0x00
#define STILL_IMAGE_TRANSMIT                  0x01
#define STILL_IMAGE_TRANSMIT_VIA_DIDICATED    0x02
#define STILL_IMAGE_TRANSMISSION_ABORT        0x03

#define START_VIDEO_FRAME_INDEX 0

struct __TMS_STRUCTNAME(PROCESSING_UNIT)
{
    u16 wBackLightCompensation;
    u16 wBrightness;
    u16 wContrast;
    u8 bPowerLineFrequency;
    u16 wHue;
    u16 wSaturation;
    u16 wSharpness;
    u16 wGamma;
    u16 wWhiteBalanceTemperature;
    u8 bHueAuto;
    u8 bWhiteBalanceTemperatureAuto;
};

struct __TMS_STRUCTNAME(CAMERA_TERMINAL)
{
    u8     bScanningMode;
    u8     bAutoExposureMode;
    u8     bAutoExposurePriority;
    u32    dwExposureTimeAbsolute;
    u8     bExposureTimeRelative;
    u16    wFocusAbsolute;

    struct
    {
        u8     bFocusRelative;
        u8     bSpeed;
    }focus_rel;

    u8     bFocusAuto;
    u16    wIrisAbsolute;
    u8     bIrisRelative;
    u16    wObjectiveFocalLength;

    struct
    {
        u8     bZoom;
        u8     bDigitalZoom;
        u8     bSpeed;
    }zoom_rel;


    struct
    {
        u32        dwPanAbsolute;
        u32        dwTiltAbsolute;
    }pan_tilt_abs;


    struct
    {
        u8     bPanRelative;
        u8     bPanSpeed;
        u8     bTiltRelative;
        u8     bTiltSpeed;
    }pan_tilt_rel;

    u16        wRollAbsolute;

    struct
    {
        u8     bRollRelative;
        u8     bSpeed;
    }roll_rel;

    u8     bPrivacy;
};



struct __TMS_STRUCTNAME(PROBE_COMMIT)
{
    u16 bmHint;
    u8 bFormatIndex;
    u8 bFrameIndex;
    u32 dwFrameInterval;
    u16 wKeyFrameRate;
    u16 wPFrameRate;
    u16 wCompQuality;
    u16 wCompWindowSize;
    u16 wDelay;
    u32 dwMaxVideoFrameSize;
    u32 dwMaxPayloadTransferSize;
    u32 dwClockFrequency;
    u8 bmFramingInfo;
    u8 bPreferedVersion;
    u8 bMinVersion;
    u8 bMaxVersion;
};

struct __TMS_STRUCTNAME(STILL_PROBE_COMMIT)
{
    u8 bFormatIndex;
    u8 bFrameIndex;
    u8 bCompressionIndex;
    u32 dwMaxVideoFrameSize;
    u32 dwMaxPayloadTransferSize;
};

struct __TMS_STRUCTNAME(VIDEODEMO_CONTEXT)
{
    __TMS_UPROTO_VIDEO * pVideo;
    __TMS_UPLATFORM * pPlatform;

    __TMS_VOID * pAppContext;

    // Videon IN/OUT stream handle
    __TMS_UPROTO_VIDEO_STREAM_HANDLE hVideoIn;    // USB OUT
    __TMS_UPROTO_VIDEO_STREAM_HANDLE hVideoOut;    // USB IN

    u32 wVideoInMaxPacketSize;
    u32 wVideoOutMaxPacketSize;

    u16 wTransportHeaderSize; // ISO header
    u16 wISOPacketNumber;     // ISO header

    __TMS_BOOL fInputActivate;
    __TMS_BOOL fOutputActivate;

    __TMS_VIDEODEMO_BUFFER_HDR * pReadBufferHdr;
    u16 nReadBufferHdr;

    __TMS_VIDEODEMO_BUFFER_HDR * pWriteBufferHdr;
    u16 nWriteBufferHdr;

    // Current Camera Terminal
    __TMS_CAMERA_TERMINAL CamTerm_Cur;

    // Current setting of Processing Unit
    __TMS_PROCESSING_UNIT ProcUnitCur;

    // Current setting of Probe
    __TMS_PROBE_COMMIT ProbeCur;

    // Current setting of Commit
    __TMS_PROBE_COMMIT CommitCur;

    // Current setting of Probe
    __TMS_PROBE_COMMIT ProbeMin;

    // Current setting of Probe
    __TMS_PROBE_COMMIT ProbeMax;

    // Current setting of Probe
    __TMS_PROBE_COMMIT ProbeDef;


    // Current setting of Probe
    __TMS_PROBE_COMMIT CommitMin;

    // Current setting of Probe
    __TMS_PROBE_COMMIT CommitMax;

    // Current setting of Probe
    __TMS_PROBE_COMMIT CommitDef;

    // Current setting of Still Probe
    __TMS_STILL_PROBE_COMMIT StillProbeCur;

    // Current setting of Still Commit
    __TMS_STILL_PROBE_COMMIT StillCommitCur;

    u8 bStillTrigger;
    u8 nVideoFrameIndex;

    // Video protocol interface callabck completion
    __TMS_UCALLBACKCOMPLETION InitCompletion;
    __TMS_UCALLBACKCOMPLETION WriteCallback;

    __TMS_UCALLBACKCOMPLETION SetupCompletion;
    __TMS_UPROTO_VIDEO_CONTROL_REQUEST ControlRequest;
#ifdef SEND_OUT_USB_SEND_USE_XU
    __TMS_UINT8 ControlRequestScratchBuffer[512 - __TMS_UPROTO_VIDEO_XU_DATA_SIZE];
#endif
    __TMS_UPROTO_VIDEO_STREAM_HANDLE hStreamRequest;
    __TMS_UPROTO_VIDEO_STREAM_REQUEST StreamRequest;
};

struct __TMS_STRUCTNAME(VIDEODEMO_BUFFER_HDR)
{
    __TMS_VIDEODEMO_BUFFER_HDR * pNext;
    __TMS_VIDEODEMO_BUFFER_HDR * pLast;
    u32 nBuffer;
    u32 nData;
};

struct __TMS_STRUCTNAME(VIDEODEMO_BUFFER)
{
    __TMS_VIDEODEMO_BUFFER_HDR Hdr;
    u8 pBuffer[1];
};

// 3: Data
// ----------------------------------------------------------------------------
extern __TMS_CONST  __TMS_UPROTO_VIDEO_CONFIG gk_VideoDemo_ProtoConfig;
extern __TMS_CONST  __TMS_UPROTO_VIDEO_OUTSWITCH gk_VideoDemo_OutSwitch;

extern __TMS_CONST  __TMS_TEXT * __TMS_CONST gk_VideoDemo_ErrorName[];
extern __TMS_CONST  __TMS_TEXT * __TMS_CONST gk_VideoDemo_StatusName[];


// 4:  Exported Functions (non-inline)
// ----------------------------------------------------------------------------
__TMS_BEGIN_DECLS

__TMS_VIDEODEMO_CONTEXT *
VideoDemo_UncompressedDemoInit(__TMS_UPLATFORM * pPlatform,
        __TMS_USBPUMP_OBJECT_HEADER * pVideoFunction);

__TMS_VOID VideoDemo_WriteOneFrame(VOID *ctx);

__TMS_VOID VideoDemo_Start(__TMS_VIDEODEMO_CONTEXT * pVideoDemoCtx);

__TMS_UPROTO_VIDEO_CONTROL_STATUS_EVENT_CB_FN VideoDemo_ControlStatusEvent;
__TMS_UPROTO_VIDEO_CONTROL_REQUEST_CB_FN VideoDemo_ControlEvent;
__TMS_UPROTO_VIDEO_STREAM_STATUS_EVENT_CB_FN VideoDemo_StreamStatusEvent;
__TMS_UPROTO_VIDEO_STREAM_REQUEST_CB_FN VideoDemo_StreamInterfaceEvent;

__TMS_END_DECLS

/**** end of videodemo.h ****/
#endif // _VIDEODEMO_H_
