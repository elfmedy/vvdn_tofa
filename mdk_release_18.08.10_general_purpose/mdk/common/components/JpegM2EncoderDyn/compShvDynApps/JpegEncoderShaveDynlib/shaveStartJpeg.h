#ifndef __SHAVE_START_JPEG_H__
#define __SHAVE_START_JPEG_H__

#include "jpegenc.h"
#include <stdlib.h>
#include <mv_types.h>
#include <stdio.h>
#include <svuCommonShave.h>
#include <swcFrameTypes.h>

#include "JpegEncoderApi.h"

void Entry(frameBuffer *imginfo, shaveinfotype *shaveInfo, u8 *outputDdr,
           u32 *outputSize, u32 imgWidth, u32 imgHeight, formatSpecific *formatS);

#endif //__SHAVE_START_JPEG_H__