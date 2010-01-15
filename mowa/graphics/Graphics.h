/*
 *  GL.h
 *  DMA
 *
 *  Created by vorg on 2009-10-07.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_GRAPHICS_H
#define FLOW_GRAPHICS_H

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_IPHONE

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

extern void osRenderbufferStorage();
extern void osPresentRenderbuffer();

#endif

#include "Shader.h"

#endif FLOW_GRAPHICS_H
