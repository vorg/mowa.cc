/*
 *  Vec.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-13.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "Vec.h"

namespace flow {
	
//------------------------------------------------------------------------------

inline float length(const vec2 &vec) {
	return sqrtf(vec.x*vec.x + vec.y*+vec.y);
}
	
//------------------------------------------------------------------------------

inline float length(const vec3 &vec) {
	return sqrtf(vec.x*vec.x + vec.y*+vec.y + vec.z*+vec.z);
}
	
//------------------------------------------------------------------------------

inline float length(const vec4 &vec) {
	return sqrtf(vec.x*vec.x + vec.y*+vec.y + vec.z*+vec.z + vec.w*+vec.w);
}
	
//------------------------------------------------------------------------------

inline float distance(const vec2 &a, const vec2 &b) {
	return length(b - a);
}
	
//------------------------------------------------------------------------------

inline float distance(const vec3 &a, const vec3 &b) {
	return length(b - a);
}
	
//------------------------------------------------------------------------------

inline float distance(const vec4 &a, const vec4 &b) {
	return length(b - a);
}
	
//------------------------------------------------------------------------------

vec2 normalize(const vec2& vec) {
	float len = length(vec);
	if (len == 0) {
		return vec2();
	}
	float oneOverLen = 1.0f/len;
	return vec2(vec.x * oneOverLen, vec.y * oneOverLen);
}
	
//------------------------------------------------------------------------------

vec3 normalize(const vec3& vec) {
	float len = length(vec);
	if (len == 0) {
		return vec3();
	}
	float oneOverLen = 1.0f/len;
	return vec3(vec.x * oneOverLen, vec.y * oneOverLen, vec.z * oneOverLen);
}
	
//------------------------------------------------------------------------------

vec4 normalize(const vec4& vec) {
	float len = length(vec);
	if (len == 0) {
		return vec4();
	}
	float oneOverLen = 1.0f/len;
	return vec4(vec.x * oneOverLen, vec.y * oneOverLen, vec.z * oneOverLen, vec.w * oneOverLen);
}
	
//------------------------------------------------------------------------------

inline float dot(const vec2& a, const vec2& b) {
	return  a.x*b.x + a.y*b.y;
}
	
//------------------------------------------------------------------------------

inline float dot(const vec3& a, const vec3& b) {
	return  a.x*b.x + a.y*b.y + a.z*b.z;
}
	
//------------------------------------------------------------------------------

vec3 cross(const vec3& a, const vec3& b) {
	return vec3( a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x );
}
	
//------------------------------------------------------------------------------

} //end namespace flow

