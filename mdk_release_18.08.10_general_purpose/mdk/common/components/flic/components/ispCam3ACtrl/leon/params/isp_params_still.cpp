///
/// @file      isp_params_still.cpp
/// @copyright All code copyright Movidius Ltd 2017, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief	   Parameters for the filters from the ISP Pipeline after pre-processor
///            Platform(s) supported : ma2x8x
///


#include <stdint.h>

#include "isp_params_still.h"

uint8_t ispcLowpassKernel[9] = {
   28, 28, 28,
   28, 31, 28,
   28, 28, 28,
};

uint8_t ispcLumaDnsLut[32] = {
	15, 15, 14, 14, 13, 12, 10, 9, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

// Luma Denoise reference LUT (weights for distances from the center... )
uint8_t ispcYDnsDistLut[256]  __attribute__((aligned(8)))  __attribute__((section(".cmx.opipe"))) = {
  0xff, 0xfe, 0xfc, 0xfb, 0xf9, 0xf8, 0xf6, 0xf5,
  0xf3, 0xf2, 0xf0, 0xef, 0xed, 0xec, 0xeb, 0xe9,
  0xe8, 0xe6, 0xe5, 0xe4, 0xe2, 0xe1, 0xe0, 0xde,
  0xdd, 0xdc, 0xda, 0xd9, 0xd8, 0xd6, 0xd5, 0xd4,
  0xd3, 0xd1, 0xd0, 0xcf, 0xcd, 0xcc, 0xcb, 0xca,
  0xc8, 0xc7, 0xc6, 0xc5, 0xc4, 0xc2, 0xc1, 0xc0,
  0xbf, 0xbe, 0xbd, 0xbb, 0xba, 0xb9, 0xb8, 0xb7,
  0xb6, 0xb4, 0xb3, 0xb2, 0xb1, 0xb0, 0xaf, 0xae,
  0xad, 0xac, 0xab, 0xa9, 0xa8, 0xa7, 0xa6, 0xa5,
  0xa4, 0xa3, 0xa2, 0xa1, 0xa0, 0x9f, 0x9e, 0x9d,
  0x9c, 0x9b, 0x9a, 0x99, 0x98, 0x97, 0x96, 0x95,
  0x94, 0x93, 0x92, 0x91, 0x90, 0x8f, 0x8f, 0x8e,
  0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88, 0x87, 0x86,
  0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x7f,
  0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x7b, 0x7a, 0x79,
  0x78, 0x77, 0x76, 0x76, 0x75, 0x74, 0x73, 0x73,
  0x72, 0x71, 0x70, 0x6f, 0x6f, 0x6e, 0x6d, 0x6c,
  0x6c, 0x6b, 0x6a, 0x6a, 0x69, 0x68, 0x67, 0x67,
  0x66, 0x65, 0x65, 0x64, 0x63, 0x63, 0x62, 0x61,
  0x60, 0x60, 0x5f, 0x5e, 0x5e, 0x5d, 0x5d, 0x5c,
  0x5b, 0x5b, 0x5a, 0x59, 0x59, 0x58, 0x57, 0x57,
  0x56, 0x56, 0x55, 0x54, 0x54, 0x53, 0x53, 0x52,
  0x51, 0x51, 0x50, 0x50, 0x4f, 0x4f, 0x4e, 0x4d,
  0x4d, 0x4c, 0x4c, 0x4b, 0x4b, 0x4a, 0x4a, 0x49,
  0x49, 0x48, 0x47, 0x47, 0x46, 0x46, 0x45, 0x45,
  0x44, 0x44, 0x43, 0x43, 0x42, 0x42, 0x41, 0x41,
  0x40, 0x40, 0x3f, 0x3f, 0x3e, 0x3e, 0x3e, 0x3d,
  0x3d, 0x3c, 0x3c, 0x3b, 0x3b, 0x3a, 0x3a, 0x39,
  0x39, 0x39, 0x38, 0x38, 0x37, 0x37, 0x36, 0x36,
  0x36, 0x35, 0x35, 0x34, 0x34, 0x34, 0x33, 0x33,
  0x32, 0x32, 0x32, 0x31, 0x31, 0x30, 0x30, 0x30,
  0x2f, 0x2f, 0x2f, 0x2e, 0x2e, 0x2d, 0x2d, 0x2d,
};

uint8_t ispcGammaLut0_32[9] = {
	0, 26, 38, 47, 56, 63, 70, 76, 81,
};

uint8_t ispcGammaLut32_255[9] = {
	0, 81, 119, 149, 175, 197, 218, 237, 255,
};

// Local Tone Mapping curves:
float ispcLtmCurves[16*8] = {
	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,
	0.066667,	0.066667,	0.066667,	0.066667,	0.066667,	0.066667,	0.066667,	0.066667,
	0.133333,	0.133333,	0.133333,	0.133333,	0.133333,	0.133333,	0.133333,	0.133333,
	0.200000,	0.200000,	0.200000,	0.200000,	0.200000,	0.200000,	0.200000,	0.200000,
	0.266667,	0.266667,	0.266667,	0.266667,	0.266667,	0.266667,	0.266667,	0.266667,
	0.333333,	0.333333,	0.333333,	0.333333,	0.333333,	0.333333,	0.333333,	0.333333,
	0.400000,	0.400000,	0.400000,	0.400000,	0.400000,	0.400000,	0.400000,	0.400000,
	0.466667,	0.466667,	0.466667,	0.466667,	0.466667,	0.466667,	0.466667,	0.466667,
	0.533333,	0.533333,	0.533333,	0.533333,	0.533333,	0.533333,	0.533333,	0.533333,
	0.600000,	0.600000,	0.600000,	0.600000,	0.600000,	0.600000,	0.600000,	0.600000,
	0.666667,	0.666667,	0.666667,	0.666667,	0.666667,	0.666667,	0.666667,	0.666667,
	0.733333,	0.733333,	0.733333,	0.733333,	0.733333,	0.733333,	0.733333,	0.733333,
	0.800000,	0.800000,	0.800000,	0.800000,	0.800000,	0.800000,	0.800000,	0.800000,
	0.866667,	0.866667,	0.866667,	0.866667,	0.866667,	0.866667,	0.866667,	0.866667,
	0.933333,	0.933333,	0.933333,	0.933333,	0.933333,	0.933333,	0.933333,	0.933333,
	1.000000,	1.000000,	1.000000,	1.000000,	1.000000,	1.000000,	1.000000,	1.000000,
};

// DoG kernel co-efficients:
uint8_t dogCoeffs11[6] = {
	0,	2,	9,	28,	54,	69,
};
uint8_t dogCoeffs15[8] = {
	7,	10,	13,	17,	20,	23,	24,	27,
};

// Color Combine params:
float ispcCCM[9] = {
   0.81754847f, 0.02981318f, 0.15293034f,
   -0.12115417f, 0.87679269f, 0.24463626f,
   0.01191091f, -0.68448108f, 1.67303051f,
};

float ispcCCMOff[3] = {
   0.00000000f, 0.00000000f, 0.00000000f,
};

// Color Space Conversion params:
float ispcCSC[9] = {
   0.25700000f, 0.50400000f, 0.09800000f,
   -0.14800000f, -0.29100000f, 0.43900000f,
   0.43900000f, -0.36800000f, -0.07100000f,
};

float ispcCSCOff[3] = {
   0.06250000f, 0.50000000f, 0.50000000f,
};

//up to 8 phases
uint8_t hCoefs[]  __attribute__((aligned(8))) = {
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-0
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-1
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-2
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-3
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-4
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-5
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-6
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-7
};

uint8_t vCoefs[]  __attribute__((aligned(8))) = {
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-0
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-1
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-2
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-3
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-4
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-5
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-6
     64, 64, 64,  192,  64, 64, 64, 64,  //phase-7
};
