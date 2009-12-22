/*
 *  glsl_math.h
 *  DMA
 *
 *  Created by vorg on 2009-09-28.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_VEC_H
#define FLOW_VEC_H

#include <math.h>

namespace flow {

//------------------------------------------------------------------------------

class vec2 {
public:
	union {
		float v[2];
		struct {
			float x;
			float y;
		};
		struct {
			float s;
			float t;
		};
	};
	
	vec2(void) : x(0), y(0) {
	}
	
	vec2(float nx, float ny) : x(nx), y(ny) {
	}
	
	vec2(const vec2& vec) {
		x = vec.x;
		y = vec.y;
	}
	
	bool operator==(const vec2& vec) const {
		return (x==vec.x && y==vec.y);
	}
	
	bool operator!=(const vec2& vec) const {
		return (x!=vec.x || y==vec.y);
	}
	
	vec2 operator+(const vec2& vec) const {
		return vec2(x + vec.x, y + vec.y);
	}
	
	vec2 operator-(const vec2 &vec) const {
		return vec2(x-vec.x, y-vec.y);
	}
	
	vec2 operator*(float f) {
		return vec2(x*f, y*f);
	}
	
	vec2 operator/(float f) {
		return vec2(x/f, y/f);
	}
	
	vec2& operator+=(const vec2& vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	
	vec2& operator-=(const vec2& vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	
	vec2 operator-(void) {
		return vec2(-x,-y);
	}
	
	float& operator [] (unsigned int i) {
		return v[i];
	}
	
	const float& operator [] (unsigned int i) const {
		return v[i];
	}
};
	
//------------------------------------------------------------------------------

class vec3 {
public:
	union {
		float v[3];				
		struct {
			float x;
			float y;
			float z;					
		};
		struct {
			float r;
			float g;
			float b;					
		};
		struct {
			float s;
			float t;
			float q;					
		};				
	};
	
	vec3(void) : x(0), y(0), z(0) {
	}
	
	vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {
	}
	
	vec3(const vec3& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
	
	bool operator==(const vec3& vec) const {
		return (x==vec.x && y==vec.y && z==vec.z);
	}
	
	bool operator!=(const vec3& vec) const {
		return (x!=vec.x || y==vec.y || z==vec.z);
	}
	
	vec3 operator+(const vec3& vec) const {
		return vec3(x + vec.x, y + vec.y, z + vec.z);
	}
	
	vec3 operator-(const vec3 &vec) const {
		return vec3(x - vec.x, y - vec.y, z - vec.z);
	}
	
	vec3 operator*(float f) {
		return vec3(x*f, y*f, z*f);
	}
	
	vec3 operator/(float f) {
		return vec3(x/f, y/f, z/f);
	}
	
	vec3& operator+=(const vec3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;				
		return *this;
	}
	
	vec3& operator-=(const vec3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;				
		return *this;
	}
	
	vec3 operator-(void) {
		return vec3(-x, -y, -z);
	}
	
	float& operator [] (unsigned int i) {
		return v[i];
	}
	
	const float& operator [] (unsigned int i) const {
		return v[i];
	}
};	
	
//------------------------------------------------------------------------------

class vec4 {
public:
	union {
		float v[4];				
		struct {
			float x;
			float y;
			float z;					
			float w;
		};
		struct {
			float r;
			float g;
			float b;
			float a;
		};
		struct {
			float s;
			float t;
			float p;
			float q;
		};					
	};
	
	vec4(void) : x(0), y(0), z(0), w(0) {
	}
	
	vec4(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw) {
	}
	
	vec4(const vec4& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}
	
	bool operator==(const vec4& vec) const {
		return (x==vec.x && y==vec.y && z==vec.z && w==vec.w);
	}
	
	bool operator!=(const vec4& vec) const {
		return (x!=vec.x || y==vec.y || z==vec.z || w==vec.w);
	}
	
	vec4 operator+(const vec4& vec) const {
		return vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}
	
	vec4 operator-(const vec4 &vec) const {
		return vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}
	
	vec4 operator*(float f) {
		return vec4(x*f, y*f, z*f, w*f);
	}
	
	vec4 operator/(float f) {
		return vec4(x/f, y/f, z/f, w/f);
	}
	
	vec4& operator+=(const vec4& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;	
		w += vec.w;						
		return *this;
	}
	
	vec4& operator-=(const vec4& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;	
		w -= vec.w;
		return *this;
	}
	
	vec4& operator*=(const float f) {
		x *= f;
		y *= f;
		z *= f;	
		w *= f;
		return *this;
	}
	
	vec4 operator-(void) {
		return vec4(-x, -y, -z, -w);
	}
		
	float& operator [] (unsigned int i) {
		return v[i];
	}
	
	const float& operator [] (unsigned int i) const {
		return v[i];
	}
};		
	
//------------------------------------------------------------------------------

inline float length(const vec2 &vec);
inline float length(const vec3 &vec);
inline float length(const vec4 &vec);
inline float distance(const vec2 &a, const vec2 &b);
inline float distance(const vec3 &a, const vec3 &b);
inline float distance(const vec4 &a, const vec4 &b);
inline float dot(const vec2& a, const vec2& b);
inline float dot(const vec3& a, const vec3& b);
vec3 cross(const vec3& a, const vec3& b);
vec2 normalize(const vec2& vec);
vec3 normalize(const vec3& vec);
vec4 normalize(const vec4& vec);
	
//------------------------------------------------------------------------------
	
} //end namespace flow

#endif FLOW_VEC_H

