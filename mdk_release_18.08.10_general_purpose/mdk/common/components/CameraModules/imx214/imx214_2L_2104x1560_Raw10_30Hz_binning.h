//
// 30fps binned (cropped) live images at 2104x1560 pixels, sent on 2 MIPI lanes at 1200MHz (1200 Mbps per lane);
// need a system clock/aux clock of at least 480 Mhz !
//
// This is "reg_B2" from Sony Spreadsheet
//
//HEADER_FORMAT = V2.1

#ifndef _IMX214_2L_2104x1560_RAW10_30Hz_BINN_H_
#define _IMX214_2L_2104x1560_RAW10_30Hz_BINN_H_

#include "mv_types.h"
#include "CameraDefines.h"


#define IMX214_2L_2104x1560_RAW10_30HZ_BINN_I2C_CONFIG_STEPS (3)
//there must be at least 3 standard steps present in the file:
//0)          configure registers set0
//(1), (2)... optionally configure other registers set
//N-1)        set the streaming register (individual step)
//N)          set the standby register (individual step)
#define IMX214_I2C_ADDRESS     (0x20 >> 1)
#define IMX214_REG_ID          (0x0016)
#define IMX214_ID              (0x0214)

const u16 imx214_2L_2104x1560_RAW10_30Hz_binn_I2Cregs[][2] = {
//configuration step 0

//External Clock Setting
{ 0x0136, 0x18},
{ 0x0137, 0x00},

//Global Setting - basic config
{ 0x0101, 0x00},
{ 0x0105, 0x01},
{ 0x0106, 0x01},
{ 0x4601, 0x00},
{ 0x4642, 0x05},
{ 0x6276, 0x00},
{ 0x900E, 0x06},
{ 0xA802, 0x90},
{ 0xA803, 0x11},
{ 0xA804, 0x62},
{ 0xA805, 0x77},
{ 0xA806, 0xAE},
{ 0xA807, 0x34},
{ 0xA808, 0xAE},
{ 0xA809, 0x35},
{ 0xA80A, 0x62},
{ 0xA80B, 0x83},
{ 0xAE33, 0x00},

//Global Setting - analog settings
{ 0x4174, 0x00},
{ 0x4175, 0x11},
{ 0x4612, 0x29},
{ 0x461B, 0x12},
{ 0x461F, 0x06},
{ 0x4635, 0x07},
{ 0x4637, 0x30},
{ 0x463F, 0x18},
{ 0x4641, 0x0D},
{ 0x465B, 0x12},
{ 0x465F, 0x11},
{ 0x4663, 0x11},
{ 0x4667, 0x0F},
{ 0x466F, 0x0F},
{ 0x470E, 0x09},
{ 0x4909, 0xAB},
{ 0x490B, 0x95},
{ 0x4915, 0x5D},
{ 0x4A5F, 0xFF},
{ 0x4A61, 0xFF},
{ 0x4A73, 0x62},
{ 0x4A85, 0x00},
{ 0x4A87, 0xFF},
{ 0x583C, 0x04},
{ 0x620E, 0x04},
{ 0x6EB2, 0x01},
{ 0x6EB3, 0x00},
{ 0x9300, 0x02},
// H : 2104
// V : 1560
// mode settings
{ 0x0114, 0x01},
{ 0x0220, 0x00},
{ 0x0221, 0x11},
{ 0x0222, 0x01},
{ 0x0340, 0x06},
{ 0x0341, 0x40},
{ 0x0342, 0x13},
{ 0x0343, 0x90},
{ 0x0344, 0x00},
{ 0x0345, 0x00},
{ 0x0346, 0x00},
{ 0x0347, 0x00},
{ 0x0348, 0x10},
{ 0x0349, 0x6F},
{ 0x034A, 0x0C},
{ 0x034B, 0x2F},
{ 0x0381, 0x01},
{ 0x0383, 0x01},
{ 0x0385, 0x01},
{ 0x0387, 0x01},
{ 0x0900, 0x01},
{ 0x0901, 0x22},
{ 0x0902, 0x02},
{ 0x3000, 0x35},
{ 0x3054, 0x01},
{ 0x305C, 0x11},

//Output Size setting
{ 0x0112, 0x0A},
{ 0x0113, 0x0A},
{ 0x034C, 0x08},
{ 0x034D, 0x38},
{ 0x034E, 0x06},
{ 0x034F, 0x18},
{ 0x0401, 0x00},
{ 0x0404, 0x00},
{ 0x0405, 0x10},
{ 0x0408, 0x00},
{ 0x0409, 0x00},
{ 0x040A, 0x00},
{ 0x040B, 0x00},
{ 0x040C, 0x08},
{ 0x040D, 0x38},
{ 0x040E, 0x06},
{ 0x040F, 0x18},

//Clock setting
{ 0x0301, 0x05},
{ 0x0303, 0x04},
{ 0x0305, 0x03},
{ 0x0306, 0x00},
{ 0x0307, 0x96},
{ 0x0309, 0x0A},
{ 0x030B, 0x01},
{ 0x0310, 0x00},

//Data Rate setting
{ 0x0820, 0x09},
{ 0x0821, 0x60},
{ 0x0822, 0x00},
{ 0x0823, 0x00},

//WaterMark setting
{ 0x3A03, 0x06},
{ 0x3A04, 0x68},
{ 0x3A05, 0x01},

//Enable setting
{ 0x0B06, 0x01},
{ 0x30A2, 0x00},

//Test setting},
{ 0x30B4, 0x00},

//HDR setting},
{ 0x3A02, 0xFF},

//STATS setting
{ 0x3013, 0x00},

//Integration Time Setting
{ 0x0202, 0x06},
{ 0x0203, 0x36},
{ 0x0224, 0x01},
{ 0x0225, 0xF4},

// Gain Setting
{ 0x0204, 0x01},
{ 0x0205, 0x90},
{ 0x020E, 0x01},
{ 0x020F, 0x00},
{ 0x0210, 0x01},
{ 0x0211, 0x00},
{ 0x0212, 0x01},
{ 0x0213, 0x00},
{ 0x0214, 0x01},
{ 0x0215, 0x00},
{ 0x0216, 0x00},
{ 0x0217, 0x00},

{ 0x0600, 0x00},  // test mode off
//{ 0x0601, 0x02},

//Analog Setting
{ 0x4170, 0x00},
{ 0x4171, 0x10},
{ 0x4176, 0x00},
{ 0x4177, 0x3C},
{ 0xAE20, 0x04},
{ 0xAE21, 0x5C},

//Streaming setting

//configuration step 1 (individual step)
{0x0100,0x01},  // Enable streaming

//configuration step 2 (individual step)
{0x0100,0x00},  // Disable streaming

};


I2CConfigDescriptor imx214_2L_2104x1560_RAW10_30Hz_binn_mipiCfg_i2cConfigSteps[IMX214_2L_2104x1560_RAW10_30HZ_BINN_I2C_CONFIG_STEPS] =
{
      { .numberOfRegs = (sizeof(imx214_2L_2104x1560_RAW10_30Hz_binn_I2Cregs)/sizeof(imx214_2L_2104x1560_RAW10_30Hz_binn_I2Cregs[0]) -2),
        .delayMs = 0,
      },
      { .numberOfRegs = 1, //the streaming configuration step
        .delayMs = 0
      },
      { .numberOfRegs = 1, //the standby configuration step
        .delayMs = 0
      }
};

const mipiSpec imx214_2L_2104x1560_RAW10_30Hz_binn_mipiCfg =
{
      .dataMode     = MIPI_D_MODE_0,
      .dataRateMbps = 1200,
      .nbOflanes    = 2,
      .pixelFormat  = CSI_RAW_10
};

GenericCamSpec imx214_2L_2104x1560_RAW10_30Hz_binn_camCfg =
{
      .frameWidth            = 2104,
      .frameHeight           = 1560,
      .hBackPorch            = 0,
      .hFrontPorch           = 0,
      .vBackPorch            = 0,
      .vFrontPorch           = 0,
      .bytesPerPixel         = 2,
      .internalPixelFormat   = RAW16,
      .mipiCfg               = &imx214_2L_2104x1560_RAW10_30Hz_binn_mipiCfg,
      .idealRefFreq          = 24,
      .sensorI2CAddress1     = IMX214_I2C_ADDRESS,
      .sensorI2CAddress2     = 0,             //only used for stereo cameras
      .nbOfI2CConfigSteps    = IMX214_2L_2104x1560_RAW10_30HZ_BINN_I2C_CONFIG_STEPS,
      .i2cConfigSteps        = imx214_2L_2104x1560_RAW10_30Hz_binn_mipiCfg_i2cConfigSteps,
      .regSize               = 1,
      .regValues             = imx214_2L_2104x1560_RAW10_30Hz_binn_I2Cregs,
};


#endif /* _IMX214_2L_2104x1560_RAW10_30Hz_BINN_H_ */
