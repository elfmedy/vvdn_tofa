///
/// @file
/// @copyright All code copyright Movidius Ltd 2015, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Some global config variables for app

#define KERNEL_SIZE 5

u16 convMatrix[KERNEL_SIZE * KERNEL_SIZE] =
{
    0x1271, 0x1EB8, 0x22D0, 0x1EB8, 0x1271,
    0x1EB8, 0x2B01, 0x2F1A, 0x2B01, 0x1EB8,
    0x22D0, 0x2F1A, 0x3334, 0x2F1A, 0x22D0,
    0x1EB8, 0x2B01, 0x2F1A, 0x2B01, 0x1EB8,
    0x1271, 0x1EB8, 0x22D0, 0x1EB8, 0x1271,
};

u16 hwKer[KERNEL_SIZE * KERNEL_SIZE] =
{
    0x1271, 0x1EB8, 0x22D0, 0x1EB8, 0x1271,
    0x1EB8, 0x2B01, 0x2F1A, 0x2B01, 0x1EB8,
    0x22D0, 0x2F1A, 0x3334, 0x2F1A, 0x22D0,
    0x1EB8, 0x2B01, 0x2F1A, 0x2B01, 0x1EB8,
    0x1271, 0x1EB8, 0x22D0, 0x1EB8, 0x1271,
};

// Define the 3x3 erosion Matrix
UInt8 erodeMat[3*3] =
    { 1, 1, 1,
      1, 1, 1,
      1, 1, 1
    };

//Define the 3x3 dilation matrix
UInt8 dilateMat[3*3] =
    { 1, 1, 1,
      1, 1, 1,
      1, 1, 1
    };
UInt16 lutTab[256] ALIGNED(8) =
{
    0x00, 0x05, 0x09, 0x0b, 0x0e, 0x10, 0x12, 0x15, 0x17, 0x19, 0x1a, 0x1c, 0x1e, 0x20, 0x21, 0x23,
    0x25, 0x26, 0x28, 0x29, 0x2b, 0x2c, 0x2e, 0x2f, 0x31, 0x32, 0x34, 0x35, 0x36, 0x38, 0x39, 0x3a, 0x3c,
    0x3d, 0x3e, 0x40, 0x41, 0x42, 0x43, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61,
    0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71,
    0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81,
    0x82, 0x83, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9d,
    0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa8, 0xa9, 0xaa, 0xab,
    0xac, 0xad, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb6, 0xb7, 0xb8,
    0xb9, 0xba, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xc9, 0xca, 0xcb, 0xcc, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd0, 0xd1,
    0xd2, 0xd3, 0xd3, 0xd4, 0xd5, 0xd6, 0xd6, 0xd7, 0xd8, 0xd9, 0xd9, 0xda, 0xdb, 0xdc, 0xdc, 0xdd,
    0xde, 0xdf, 0xdf, 0xe0, 0xe1, 0xe2, 0xe2, 0xe3, 0xe4, 0xe4, 0xe5, 0xe6, 0xe7, 0xe7, 0xe8, 0xe9,
    0xea, 0xea, 0xeb, 0xec, 0xed, 0xed, 0xee, 0xef, 0xef, 0xf0, 0xf1, 0xf2, 0xf2, 0xf3, 0xf4, 0xf4,
    0xf5, 0xf6, 0xf7, 0xf7, 0xf8, 0xf9, 0xf9, 0xfa, 0xfb, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff,
};


//-----------------------------------ISP PIPE PARAMS

#define ISP_PIPE_INPUT_BUFFER_WIDTH      1930
#define ISP_PIPE_INPUT_BUFFER_HEIGHT     1090
#define ISP_PIPE_INPUT_BUFFER_NUM_PLANES 1

/////////////////////////////////////////////
// LSC Params

#define BAYER_W    ISP_PIPE_INPUT_BUFFER_WIDTH
#define BAYER_H    ISP_PIPE_INPUT_BUFFER_HEIGHT

#define BAYER_BITS 10

//Black level should not be used really...
//just use the img dumped after -= Black level
#define BLACK_LEVEL 0.015625 //for data in range [0..1]

//gains are 8.8 fixed point format
#define LSC_GAIN_MAP_W 56
#define LSC_GAIN_MAP_H 44

//Bayer gain map:
extern UInt16 lscMesh[44 * 56] ALIGNED(8);

/////////////////////////////////////////////
// RAW Params

//Bad pixel suppression
#define BAD_PIX_ALPHA_G_HOT    0x6    // 4 bits
#define BAD_PIX_ALPHA_RB_HOT   0x6    // 4 bits
#define BAD_PIX_ALPHA_G_COLD   0x6    // 4 bits
#define BAD_PIX_ALPHA_RB_COLD  0x6    // 4 bits
#define BAD_PIX_NOISE_LEVEL    0x0000 //16 bits


//GR-GB imbalance filter
//#define GRGB_IMBAL_PLAT_DARK     576
//#define GRGB_IMBAL_DECAY_DARK    640
//#define GRGB_IMBAL_PLAT_BRIGHT   800
//#define GRGB_IMBAL_DECAY_BRIGHT  960
//#define GRGB_IMBAL_THRESHOLD     250  // 8 bits
#define GRGB_IMBAL_PLAT_DARK     150
#define GRGB_IMBAL_DECAY_DARK    200
#define GRGB_IMBAL_PLAT_BRIGHT   400
#define GRGB_IMBAL_DECAY_BRIGHT  500
#define GRGB_IMBAL_THRESHOLD     16  // 8 bits


#define CHROMA_GEN_EPSILON     0.000978
#define CHROMA_MEDIAN_SIZE     3

//AWB digital gains are 8.8 fixed-point format
#define DIGI_GAIN_GR    0x0104>>2  //8.8 bits
#define DIGI_GAIN_GB    0x0104>>2  //8.8 bits
#define DIGI_GAIN_R     0x01ab>>2  //8.8 bits
#define DIGI_GAIN_B     0x01ac>>2  //8.8 bits

#define DIGI_SAT_GR     255    //16 bits
#define DIGI_SAT_GB     255    //16 bits
#define DIGI_SAT_R      255    //16 bits
#define DIGI_SAT_B      255    //16 bits

/////////////////////////////////////////////
// Debayer Params


/////////////////////////////////////////////
// Polyfir Params

#define ISP_CHROMA_PIPE_SCALED_BUFFER_WIDTH      (ISP_PIPE_INPUT_BUFFER_WIDTH >> 1)
#define ISP_CHROMA_PIPE_SCALED_BUFFER_HEIGHT     (ISP_PIPE_INPUT_BUFFER_HEIGHT >> 1)
#define ISP_CHROMA_PIPE_SCALED_BUFFER_NUM_PLANES 3

//2X downscale
#define HORZ_N     1
#define HORZ_D     2

#define VERT_N     1
#define VERT_D     2

#define CCM_COEF(x) (UInt16)(x*1024)

/////////////////////////////////////////////
// Sharpen Params

#define SHARP_SIGMA        1.300000
#define SHARP_STRENGTH     0x3e00    //fp16 (fp32 value is: 1.500000)
#define SHARP_ALPHA        0x3666    //fp16 (fp32 value is: 0.400000)
#define SHARP_OVERSHOOT    0x3c9a    //fp16 (fp32 value is: 1.150000)
#define SHARP_UNDERSHOOT   0x3af5    //fp16 (fp32 value is: 0.869565)

#define SHARP_RANGE_STOP_0 0x1c04    //fp16 [0..1] (fp32 value is: 1.000000)
#define SHARP_RANGE_STOP_1 0x2d05    //fp16 [0..1] (fp32 value is: 20.000000)
#define SHARP_RANGE_STOP_2 0x3ae7    //fp16 [0..1] (fp32 value is: 220.000000)
#define SHARP_RANGE_STOP_3 0x3bd8    //fp16 [0..1] (fp32 value is: 250.000000)

#define SHARP_MIN_THR      0x1a25    //fp16 (fp32 value is: 0.003000)

/////////////////////////////////////////////
// Luma denoise params:
#define LUMA_DNS_STRENGTH  12.000000
#define LUMA_DNS_ALPHA     96 //8bit value

//following coefs are to be mirrored by HW and thus obtain 7x7 window
//the 16 coefs represent the top-left square of a 7x7 symetrical kernel
//each entry is 2 bit, and represents number of shifts
#define LUMA_DNS_F2         0x55555555

//Luma Denoise reference LUT (weights for distances from the center... )
extern UInt8 yDnsRefLut[256];
extern UInt8 yDnsGammaLut[256];

#define LUMA_DNS_REF_SHIFT      14
#define LUMA_DNS_REF_GAMMA      0.800000

// New Luma denoise
#define LUMA_DNS_X_OFFSET            0
#define LUMA_DNS_Y_OFFSET            0

//Luma random noise params:
#define LUMA_RAND_NOISE_STRENGTH 0.080000


//Chroma denoise params:
#define CHROMA_DNS_T1      4
#define CHROMA_DNS_T2      5
#define CHROMA_DNS_LIM     4
#define CHROMA_DNS_H_ENAB  1


//Chroma-block params:
#define DESAT_T1  0.007843
#define DESAT_MUL 19.615385


//Display Gamma params:
#define GAMMA_DARK       1.700000
#define GAMMA_BRIGHT     2.200000
#define GAMMA_ACE_SUB    0.047059
#define GAMMA_ACE_MUL    1.053719


extern float ccm[9] ;
extern UInt16 sharpen_coeffs[4] ;
extern UInt16  gammaTable[256] ALIGNED(8);
extern UInt8  lumaDnsLut[32] ALIGNED(8) ;
extern UInt8 horzCoefs[] ALIGNED(8);
extern UInt8 vertCoefs[] ALIGNED(8);
extern int  bitpos;
extern UInt32 gaussLut[4] ALIGNED(8);
extern UInt32 gammaLut[5] ALIGNED(8);
extern UInt8 distLUT[] ALIGNED(8);



Int8   coefX[6] = { -1,  1, -2, 2, -1, 1 };
Int8   coefY[6] = { -1, -2, -1, 1,  2, 1 };


// Define the gamma curve LUT
//The LUT contains u8 data, but LUT storage must always be u16

UInt16  sharpen_coeffs[4] = {0x2583, //fp16 values
                             0x2E0C,
                             0x3358,
                             0x34F0 };

UInt16  gammaTable[256] ALIGNED(8) = {
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x114f,0x17e8,0x1a89,0x1c8a,0x1dca,0x1f06,0x201e,0x20b8,0x214f,
    0x21e4,0x230a,0x2414,0x24a0,0x2529,0x25b0,0x2634,0x26b5,0x2735,0x27b2,0x2817,0x2853,0x288f,0x28ca,0x2904,0x293e,
    0x2977,0x29e6,0x2a53,0x2abd,0x2b26,0x2b8c,0x2bf1,0x2c29,0x2c5a,0x2c8a,0x2cb9,0x2ce7,0x2d14,0x2d41,0x2d6e,0x2d9a,
    0x2dc5,0x2e1a,0x2e6d,0x2ebf,0x2f0e,0x2f5d,0x2fa9,0x2ff5,0x301f,0x3044,0x3068,0x308b,0x30ae,0x30d1,0x30f3,0x3114,
    0x3135,0x3177,0x31b6,0x31f5,0x3232,0x326e,0x32a9,0x32e3,0x331c,0x3354,0x338b,0x33c1,0x33f7,0x3416,0x3430,0x3449,
    0x3463,0x3495,0x34c6,0x34f5,0x3524,0x3552,0x357f,0x35ab,0x35d6,0x3600,0x362a,0x3653,0x367c,0x36a4,0x36cb,0x36f2,
    0x3718,0x3762,0x37ab,0x37f2,0x381b,0x383d,0x385e,0x387e,0x389d,0x38bc,0x38da,0x38f8,0x3915,0x3931,0x394d,0x3968,
    0x3982,0x39b6,0x39e8,0x3a18,0x3a46,0x3a73,0x3a9e,0x3ac8,0x3af1,0x3b18,0x3b3d,0x3b62,0x3b85,0x3ba8,0x3bc9,0x3be9,
    0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,0x3c00,
};

UInt8  lumaDnsLut[32] ALIGNED(8) =
{ 0xF,0xF,0xF,0xE,0xE,0xD,0xC,0xB,
  0xA,0x9,0x8,0x7,0x6,0x5,0x4,0x3,
  0x3,0x2,0x1,0x1,0x1,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};

//UInt16 horzCoefs[] ALIGNED(8) = {
//    0x0000, 0x0000, 0x0000, 0x3C00, 0x0000, 0x0000, 0x0000,    0x0000 /*padding*/
//};
// Biased U8F version of coefs now required

UInt8 horzCoefs[] ALIGNED(8) = {
    0x40, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40,     0x00 /*padding*/
//    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,     0xC0 /*padding*/
};

//UInt16 vertCoefs[] ALIGNED(8) = {
//    0x0000, 0x0000, 0x0000, 0x3C00, 0x0000, 0x0000, 0x0000,    0x0000 /*padding*/
//};

// Biased U8F version of coefs now required
UInt8 vertCoefs[] ALIGNED(8) = {
    0x40, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40,     0x00 /*padding*/
};


int  bitpos = 3;

float ccm[9] = {
    2.23759131f, -0.73843198f, -0.49916066f,
    -0.61364868f, 2.12908996f, -0.51544266f,
    -0.38126266f, -0.74079798f, 2.12207336f,
};

//UInt32 gaussLut[4] ALIGNED(8) = {0x9abddeef,0x12234578,0x0,0x0};
UInt32 gaussLut[4] ALIGNED(8) = {0xbcdeefff,0x3456789a,0x00011123,0x0};
UInt32 gammaLut[5] ALIGNED(8) = {0x665a4900,0x837d776f,0xa8890089,0xeadecfbe,0x1000fff5};

UInt8 distLUT[] ALIGNED(8) =
{ 0xff, 0xfe, 0xfc, 0xfb, 0xf9, 0xf8, 0xf7, 0xf5, 0xf4, 0xf3, 0xf1, 0xf0, 0xef, 0xed, 0xec, 0xeb,
  0xea, 0xe8, 0xe7, 0xe6, 0xe4, 0xe3, 0xe2, 0xe1, 0xdf, 0xde, 0xdd, 0xdc, 0xda, 0xd9, 0xd8, 0xd7,
  0xd6, 0xd4, 0xd3, 0xd2, 0xd1, 0xd0, 0xce, 0xcd, 0xcc, 0xcb, 0xca, 0xc9, 0xc8, 0xc6, 0xc5, 0xc4,
  0xc3, 0xc2, 0xc1, 0xc0, 0xbf, 0xbe, 0xbd, 0xbb, 0xba, 0xb9, 0xb8, 0xb7, 0xb6, 0xb5, 0xb4, 0xb3,
  0xb2, 0xb1, 0xb0, 0xaf, 0xae, 0xad, 0xac, 0xab, 0xaa, 0xa9, 0xa8, 0xa7, 0xa6, 0xa5, 0xa4, 0xa3,
  0xa2, 0xa1, 0xa0, 0x9f, 0x9e, 0x9d, 0x9c, 0x9b, 0x9b, 0x9a, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94,
  0x93, 0x92, 0x92, 0x91, 0x90, 0x8f, 0x8e, 0x8d, 0x8c, 0x8c, 0x8b, 0x8a, 0x89, 0x88, 0x87, 0x87,
  0x86, 0x85, 0x84, 0x83, 0x83, 0x82, 0x81, 0x80, 0x7f, 0x7f, 0x7e, 0x7d, 0x7c, 0x7c, 0x7b, 0x7a,
  0x79, 0x79, 0x78, 0x77, 0x76, 0x76, 0x75, 0x74, 0x73, 0x73, 0x72, 0x71, 0x71, 0x70, 0x6f, 0x6e,
  0x6e, 0x6d, 0x6c, 0x6c, 0x6b, 0x6a, 0x6a, 0x69, 0x68, 0x68, 0x67, 0x66, 0x66, 0x65, 0x64, 0x64,
  0x63, 0x62, 0x62, 0x61, 0x61, 0x60, 0x5f, 0x5f, 0x5e, 0x5e, 0x5d, 0x5c, 0x5c, 0x5b, 0x5b, 0x5a,
  0x59, 0x59, 0x58, 0x58, 0x57, 0x56, 0x56, 0x55, 0x55, 0x54, 0x54, 0x53, 0x53, 0x52, 0x51, 0x51,
  0x50, 0x50, 0x4f, 0x4f, 0x4e, 0x4e, 0x4d, 0x4d, 0x4c, 0x4c, 0x4b, 0x4b, 0x4a, 0x4a, 0x49, 0x49,
  0x48, 0x48, 0x47, 0x47, 0x46, 0x46, 0x45, 0x45, 0x44, 0x44, 0x43, 0x43, 0x43, 0x42, 0x42, 0x41,
  0x41, 0x40, 0x40, 0x3f, 0x3f, 0x3e, 0x3e, 0x3e, 0x3d, 0x3d, 0x3c, 0x3c, 0x3b, 0x3b, 0x3b, 0x3a,
  0x3a, 0x39, 0x39, 0x39, 0x38, 0x38, 0x37, 0x37, 0x37, 0x36, 0x36, 0x35, 0x35, 0x35, 0x34, 0x34};

UInt8 yDnsGammaLut[256] = {
  0x00, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0e,
  0x10, 0x12, 0x13, 0x15, 0x16, 0x18, 0x19, 0x1a,
  0x1c, 0x1d, 0x1f, 0x20, 0x21, 0x23, 0x24, 0x25,
  0x27, 0x28, 0x29, 0x2a, 0x2c, 0x2d, 0x2e, 0x2f,
  0x30, 0x32, 0x33, 0x34, 0x35, 0x36, 0x38, 0x39,
  0x3a, 0x3b, 0x3c, 0x3d, 0x3f, 0x40, 0x41, 0x42,
  0x43, 0x44, 0x45, 0x46, 0x47, 0x49, 0x4a, 0x4b,
  0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53,
  0x54, 0x55, 0x56, 0x58, 0x59, 0x5a, 0x5b, 0x5c,
  0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64,
  0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,
  0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74,
  0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7b,
  0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83,
  0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b,
  0x8c, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92,
  0x93, 0x94, 0x95, 0x96, 0x97, 0x97, 0x98, 0x99,
  0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1,
  0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
  0xa9, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
  0xb0, 0xb1, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
  0xb7, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd,
  0xbe, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4,
  0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xca,
  0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xcf, 0xd0, 0xd1,
  0xd2, 0xd3, 0xd4, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8,
  0xd9, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xde,
  0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe3, 0xe4, 0xe5,
  0xe6, 0xe7, 0xe8, 0xe8, 0xe9, 0xea, 0xeb, 0xec,
  0xec, 0xed, 0xee, 0xef, 0xf0, 0xf0, 0xf1, 0xf2,
  0xf3, 0xf4, 0xf5, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
  0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfd, 0xfe, 0xff,
 };

UInt8 yDnsRefLut[256] = {
 0xff, 0xfe, 0xfd, 0xfc, 0xfc, 0xfb, 0xfa, 0xf9,
 0xf8, 0xf7, 0xf7, 0xf6, 0xf5, 0xf4, 0xf3, 0xf2,
 0xf2, 0xf1, 0xf0, 0xef, 0xee, 0xed, 0xed, 0xec,
 0xeb, 0xea, 0xe9, 0xe9, 0xe8, 0xe7, 0xe6, 0xe5,
 0xe5, 0xe4, 0xe3, 0xe2, 0xe2, 0xe1, 0xe0, 0xdf,
 0xde, 0xde, 0xdd, 0xdc, 0xdb, 0xdb, 0xda, 0xd9,
 0xd8, 0xd8, 0xd7, 0xd6, 0xd5, 0xd5, 0xd4, 0xd3,
 0xd2, 0xd2, 0xd1, 0xd0, 0xd0, 0xcf, 0xce, 0xcd,
 0xcd, 0xcc, 0xcb, 0xcb, 0xca, 0xc9, 0xc8, 0xc8,
 0xc7, 0xc6, 0xc6, 0xc5, 0xc4, 0xc4, 0xc3, 0xc2,
 0xc1, 0xc1, 0xc0, 0xbf, 0xbf, 0xbe, 0xbd, 0xbd,
 0xbc, 0xbb, 0xbb, 0xba, 0xb9, 0xb9, 0xb8, 0xb7,
 0xb7, 0xb6, 0xb5, 0xb5, 0xb4, 0xb4, 0xb3, 0xb2,
 0xb2, 0xb1, 0xb0, 0xb0, 0xaf, 0xae, 0xae, 0xad,
 0xad, 0xac, 0xab, 0xab, 0xaa, 0xaa, 0xa9, 0xa8,
 0xa8, 0xa7, 0xa6, 0xa6, 0xa5, 0xa5, 0xa4, 0xa3,
 0xa3, 0xa2, 0xa2, 0xa1, 0xa1, 0xa0, 0x9f, 0x9f,
 0x9e, 0x9e, 0x9d, 0x9c, 0x9c, 0x9b, 0x9b, 0x9a,
 0x9a, 0x99, 0x99, 0x98, 0x97, 0x97, 0x96, 0x96,
 0x95, 0x95, 0x94, 0x94, 0x93, 0x92, 0x92, 0x91,
 0x91, 0x90, 0x90, 0x8f, 0x8f, 0x8e, 0x8e, 0x8d,
 0x8d, 0x8c, 0x8c, 0x8b, 0x8a, 0x8a, 0x89, 0x89,
 0x88, 0x88, 0x87, 0x87, 0x86, 0x86, 0x85, 0x85,
 0x84, 0x84, 0x83, 0x83, 0x82, 0x82, 0x81, 0x81,
 0x80, 0x80, 0x7f, 0x7f, 0x7e, 0x7e, 0x7e, 0x7d,
 0x7d, 0x7c, 0x7c, 0x7b, 0x7b, 0x7a, 0x7a, 0x79,
 0x79, 0x78, 0x78, 0x77, 0x77, 0x77, 0x76, 0x76,
 0x75, 0x75, 0x74, 0x74, 0x73, 0x73, 0x72, 0x72,
 0x72, 0x71, 0x71, 0x70, 0x70, 0x6f, 0x6f, 0x6f,
 0x6e, 0x6e, 0x6d, 0x6d, 0x6c, 0x6c, 0x6c, 0x6b,
 0x6b, 0x6a, 0x6a, 0x69, 0x69, 0x69, 0x68, 0x68,
 0x67, 0x67, 0x67, 0x66, 0x66, 0x65, 0x65, 0x65,
};


UInt16 lscMesh[44 * 56]  ALIGNED(8) =
{
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100,
};
