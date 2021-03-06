//
// 30fps full live images at 640x480 pixels, sent on 2 MIPI lanes at 811MHz (811 Mbps per lane);

//HEADER_FORMAT = V2.1

#ifndef _IMX208_1L_640x480_RAW10_30HZ_H_
#define _IMX208_1L_640x480_RAW10_30HZ_H_

#include "CameraDefines.h"
#include "mv_types.h"

#define IMX208_1L_640x480_RAW10_30HZ_I2C_CONFIG_STEPS (3)
//there must be at least 3 standard steps present in the file:
//0)          configure registers set0
//(1), (2)... optionally configure other registers set
//N-1)        set the streaming register (individual step)
//N)          set the standby register (individual step)

const u16 imx208_1L_640x480_RAW10_30Hz_I2Cregs[][2] =
{
//configuration step 0
{0x0103,0x01}, // SW Reset
// -----------start of official config from spreadsheet ------------
//PLL Setting
{0x0305, 0x04},
{0x0307, 0x87},
{0x303C, 0x4B},
{0x30A4, 0x00},  // 0x02->60fps, 0x00->30fps, 0x01->15fps
//Mode setting
{0x0112, 0x0A},
{0x0113, 0x0A},
{0x0340, 0x04},
{0x0341, 0xB0},
{0x0342, 0x04},
{0x0343, 0x64},
{0x0344, 0x00}, // X - readout start
{0x0345, 0x00},
{0x0346, 0x00}, // Y - readout start
{0x0347, 0x00},
{0x0348, 0x02}, // X - readout end
{0x0349, 0x7F},
{0x034A, 0x01}, // Y - readout end
{0x034B, 0xDF},
{0x034C, 0x02}, // X - size
{0x034D, 0x80},
{0x034E, 0x01}, // Y - size
{0x034F, 0xE0},
{0x0381, 0x01},
{0x0383, 0x01},
{0x0385, 0x01},
{0x0387, 0x01},
{0x3048, 0x00},
{0x304E, 0x0A},
{0x3050, 0x02},
{0x309B, 0x00},
{0x30D5, 0x00},
{0x3301, 0x01}, // [0:1] 00: 2 Lane output, 01: 1 Lane output
{0x3318, 0x61},
//Shutter Gain setting
{0x0202, 0x02}, //(exposure time)
{0x0203, 0x0b},
{0x0205, 0xC0}, //analog gain
{0x020E, 0x00}, //digital gain
{0x0210, 0x00}, //
{0x0212, 0x00}, //
{0x0214, 0x00}, //
// -----------End of official config from spreadsheet ------------
// unsuccessful attempt to enable XVS (from sync app note)
// {0x3063, 0x04},
// {0x3240, 0x14},
// {0x3242, 0x12},
// {0x30F9, 0x0F}, // make XVS as long as possible
// --------------------------------------------------------------
// registers obtained out of scoping the dev board
{0x3343,0x03}, // Manufacturer prohibited !?!
{0x30f6,0x00}, // Manufacturer prohibited !?!
{0x0600,0x00}, // test mode off

//configuration step 1 (individual step)
{0x0100,0x01},  // Enable streaming

//configuration step 2 (individual step)
{0x0100,0x00},  // Disable streaming
};

I2CConfigDescriptor imx208_1L_640x480_RAW10_30Hz_I2CConfigSteps[IMX208_1L_640x480_RAW10_30HZ_I2C_CONFIG_STEPS] =
{
      { .numberOfRegs = (sizeof(imx208_1L_640x480_RAW10_30Hz_I2Cregs)/sizeof(imx208_1L_640x480_RAW10_30Hz_I2Cregs[0])) - 2,
        .delayMs = 0
      },
      { .numberOfRegs = 1, //the streaming configuration step
        .delayMs = 0
      },
      { .numberOfRegs = 1, //the standby configuration step
        .delayMs = 0
      }
};


const mipiSpec imx208_1L_640x480_RAW10_30Hz_mipiCfg =
{
      .dataMode     = MIPI_D_MODE_0,
      .dataRateMbps = 405,
      .nbOflanes    = 1,
      .pixelFormat  = CSI_RAW_10
};


GenericCamSpec imx208_1L_640x480_RAW10_30Hz_camCfg =
{
      .frameWidth            = 640,
      .frameHeight           = 480,
      .hBackPorch            = 0,
      .hFrontPorch           = 0,
      .vBackPorch            = 0,
      .vFrontPorch           = 0,
      .bytesPerPixel         = 2,
      .internalPixelFormat   = RAW16,
      .mipiCfg               = &imx208_1L_640x480_RAW10_30Hz_mipiCfg,
      .idealRefFreq          = 24,
      .sensorI2CAddress1     = (0x6C >> 1),
      .sensorI2CAddress2     = (0x6E >> 1),
      .nbOfI2CConfigSteps    = IMX208_1L_640x480_RAW10_30HZ_I2C_CONFIG_STEPS,
      .i2cConfigSteps        = imx208_1L_640x480_RAW10_30Hz_I2CConfigSteps,
      .regSize               = 1, //data register size (register address size always on 2 bytes)
      .regValues             = imx208_1L_640x480_RAW10_30Hz_I2Cregs,
};



#endif /* _IMX208_1L_640x480_RAW10_30HZ_H_ */
