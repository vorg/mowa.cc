/*
 *  MathUtil.h
 *  DMA
 *
 *  Created by vorg on 2009-10-09.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_MATHUTILS_H
#define FLOW_MATHUTILS_H

//------------------------------------------------------------------------------

extern const float PI;
extern const float TWOPI;
extern const float EPSILON;

//------------------------------------------------------------------------------

float clamp(float val, float min, float max);
int	clamp(int val, int min, int max);
float floatEqual(float a, float b, float tolerance = EPSILON);

static inline float degToRad(float a) { return a*0.01745329252f;};
static inline float radToDeg(float a) { return a*57.29577951f;}; 

//------------------------------------------------------------------------------

#endif