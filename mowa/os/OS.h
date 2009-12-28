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

//------------------------------------------------------------------------------

extern const char* osLoadTextFile(const char* fileName);
extern unsigned char* osLoadImageFile(const char* fileName, unsigned int* width, unsigned int *height);
extern float osGetTime(); //time from the beginning of application start

//------------------------------------------------------------------------------

#endif FLOW_OS_UTILS_H


