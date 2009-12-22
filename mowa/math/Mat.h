/*
 *  Mat.h
 *  DMA
 *
 *  Created by vorg on 2009-10-09.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_MAT_H
#define FLOW_MAT_H

#include <math.h>
#include "Vec.h"

namespace flow {
	
//------------------------------------------------------------------------------
	
class mat4 {		
public:
	vec4 col[4];
	
	mat4() {
		col[0] = vec4(0, 0, 0, 0);
		col[1] = vec4(0, 0, 0, 0);
		col[2] = vec4(0, 0, 0, 0);
		col[3] = vec4(0, 0, 0, 0);		
	}
	
	mat4(const mat4& m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		col[3] = m[3];
	}
	
	mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3) {
		col[0] = v0;
		col[1] = v1;
		col[2] = v2;
		col[3] = v3;
	}
	
	vec4& operator [] (unsigned int i) {
		return col[i];
	}
	
	const vec4& operator [] (unsigned int i) const {
		return col[i];
	}
	
	mat4& operator = (const mat4& m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		col[3] = m[3];
		return *this;
	}
	
	mat4& operator += (const mat4& m) {
		col[0] += m[0];
		col[1] += m[1];
		col[2] += m[2];
		col[3] += m[3];
		return *this;
	}
	
	mat4& operator -= (const mat4& m) {
		col[0] -= m[0];
		col[1] -= m[1];
		col[2] -= m[2];
		col[3] -= m[3];
		return *this;
	}
	
	mat4& operator *= (const mat4& m);
	
	mat4& operator *= (float f) {
		col[0] *= f;
		col[1] *= f;
		col[2] *= f;
		col[3] *= f;
		return *this;
	}
	
	friend bool operator == (const mat4& a, const mat4& b) {
		return((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]));
	}
	
	friend bool operator != (const mat4& a, const mat4& b) {
		return((a[0] != b[0]) || (a[1] != b[1]) || (a[2] != b[2]) || (a[3] != b[3]));
	}
	
	friend mat4 operator + (const mat4& a, const mat4& b) {
		mat4 result(a);
		result += b;
		return result;
	}
	
	friend mat4 operator - (const mat4& a, const mat4& b) {
		mat4 result(a);
		result -= b;
		return result;
	}
	
	friend mat4 operator * (const mat4& a, const mat4& b) {
		mat4 result(a);
		result *= b;
		return result;
	}
	
	friend vec3 operator * (mat4& m, const vec3& v) {
		vec4 result(v.x, v.y, v.z, 0.0);
		result = m * result;
		return vec3(result.x, result.y, result.z);
	}
	
	friend vec4 operator * (mat4& m, const vec4& v) {
		vec4 result;
		result.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3];
		result.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3];
		result.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3];
		result.w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + v.w * m[3][3];		
		return result;
	}
	
	friend mat4 operator * (const mat4& m, float f) {
		mat4 result(m);
		result *= f;
		return result;
	}
	
	friend mat4 operator * (float f, const mat4& m) {
		mat4 result(m);
		result *= f;
		return result;
	} 
	
	static mat4 identityMatrix();
	static mat4 rotationMatrix(const vec3& axis, float degrees);
	static mat4 translationMatrix(float x, float y, float z);
	static mat4 scaleMatrix(float x, float y, float z, float w = 1.0);
	static mat4 lookAtMatrix(const vec3& camPos, const vec3& camUp, const vec3& target );
	static mat4 frustumMatrix(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspectiveMatrix(float fov, float aspect, float near, float far);
	static mat4 orthoMatrix(float left, float right, float bottom, float top, float near = -1, float far = 1);
};
	
//------------------------------------------------------------------------------
	
mat4 transpose(const mat4& m);
mat4 invert(const mat4& m);
	
//------------------------------------------------------------------------------

} //end namespace flow

#endif FLOW_MAT_H

