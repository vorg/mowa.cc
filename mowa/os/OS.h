/*
 *  os.h
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_OS_H
#define FLOW_OS_H

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_IPHONE
#define USE_OPENGL_ES
#endif

//------------------------------------------------------------------------------

extern const char* osLoadTextFile(const char* fileName);
extern unsigned char* osLoadImageFile(const char* fileName, unsigned int* width, unsigned int *height, unsigned int *bpp);
extern float osGetTime(); //time from the beginning of application start in seconds

//------------------------------------------------------------------------------

#endif FLOW_OS_UTILS_H


