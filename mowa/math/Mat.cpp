/*
 *  Mat.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-09.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "Mat.h"
#include "MathUtils.h"

namespace flow {
	
//------------------------------------------------------------------------------

mat4& mat4::operator *= (const mat4& m) {
	mat4 t;
	for (int r=0; r<4; r++)  {
		for (int c=0; c<4; c++) {
			float f = 0;			
			f += (col[0][r] * m[c][0]);
			f += (col[1][r] * m[c][1]);
			f += (col[2][r] * m[c][2]);
			f += (col[3][r] * m[c][3]);
			
			t[c][r] = f;
		}
	}
	*this = t;
	return *this;
} 
	
//-----------------------------------------------------------------------------
	
mat4 mat4::identityMatrix() {
	mat4 result;
	result.col[0] = vec4(1.0, 0.0, 0.0, 0.0);
	result.col[1] = vec4(0.0, 1.0, 0.0, 0.0);
	result.col[2] = vec4(0.0, 0.0, 1.0, 0.0);
	result.col[3] = vec4(0.0, 0.0, 0.0, 1.0);
	
	return result;
}


//-----------------------------------------------------------------------------

mat4 mat4::rotationMatrix(const vec3& axis, float degrees) {
	mat4 result;
	float rad = degToRad(degrees);
	float sinA, cosA;
	float invCosA;
	float x, y, z;
	float xSq, ySq, zSq;
	vec3 nrm = normalize(axis);

	sinA = (float)sin(rad);
	cosA = (float)cos(rad);
	invCosA = 1.0f - cosA;
	
	x = nrm.x;
	y = nrm.y;
	z = nrm.z;
	
	xSq = x * x;
	ySq = y * y;
	zSq = z * z;
	
	result[0][0] = (invCosA * xSq) + (cosA);
	result[1][0] = (invCosA * x * y) - (sinA * z );
	result[2][0] = (invCosA * x * z) + (sinA * y );
	result[3][0] = 0.0f;
	
	result[0][1] = (invCosA * x * y) + (sinA * z);
	result[1][1] = (invCosA * ySq) + (cosA);
	result[2][1] = (invCosA * y * z) - (sinA * x);
	result[3][1] = 0.0f;
	
	result[0][2] = (invCosA * x * z) - (sinA * y);
	result[1][2] = (invCosA * y * z) + (sinA * x);
	result[2][2] = (invCosA * zSq) + (cosA);
	result[3][2] = 0.0f;
	
	result[0][3] = 0.0f;
	result[1][3] = 0.0f;
	result[2][3] = 0.0f;
	result[3][3] = 1.0f;
	
	return result; 
}

//-----------------------------------------------------------------------------

mat4 mat4::translationMatrix(float x, float y, float z) {
	mat4 result = mat4::identityMatrix();

	result[3][0] = x;
	result[3][1] = y;
	result[3][2] = z;
	
	return result; 
}

//-----------------------------------------------------------------------------

mat4 mat4::scaleMatrix(float x, float y, float z, float w) {
	mat4 result = mat4::identityMatrix();

	result[0][0] = x;
	result[1][1] = y;
	result[2][2] = z;
	result[3][3] = w;
	
	return result; 
}

//-----------------------------------------------------------------------------

mat4 mat4::lookAtMatrix(const vec3& camPos, const vec3& camUp, const vec3& target ) {
	mat4 result;
	
	vec3 F = normalize(target - camPos);	
	vec3 S = normalize(cross(F, normalize(camUp)));	
	vec3 U = normalize(cross(S, F));
	
	result[0][0] = S.x;
	result[1][0] = S.y;
	result[2][0] = S.z;
	result[3][0] = 0.0;
	
	result[0][1] = U.x;
	result[1][1] = U.y;
	result[2][1] = U.z;
	result[3][1] = 0.0;
	
	result[0][2] = -F.x;
	result[1][2] = -F.y;
	result[2][2] = -F.z;
	result[3][2] = 0.0;
	
	result[0][3] = 0.0f;
	result[1][3] = 0.0f;
	result[2][3] = 0.0f;
	result[3][3] = 1.0f;
	
	result *= mat4::translationMatrix(-camPos.x, -camPos.y, -camPos.z);
	
	return result; 
}

//-----------------------------------------------------------------------------

mat4 mat4::frustumMatrix(float left, float right, float bottom, float top, float near, float far) {
	mat4 result;
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;
	
	result[0][0] = (2*near) / width;
	result[0][1] = 0.0f;
	result[0][2] = 0.0f;
	result[0][3] = 0.0f;
	
	result[1][0] = 0.0f;
	result[1][1] = (2*near) / height;
	result[1][2] = 0.0f;
	result[1][3] = 0.0f;
	
	result[2][0] = (right + left) / width;
	result[2][1] = (top + bottom) / height;
	result[2][2] = -(far + near) / depth;
	result[2][3] = -1.0f;
	
	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = -(2*far*near) / depth;
	result[3][3] = 0.0f;
	
	return result; 
}

//-----------------------------------------------------------------------------

mat4 mat4::perspectiveMatrix(float fov, float aspect, float near, float far) {
	mat4 result;
	float angle;
	float cot;
	
	angle = fov / 2.0f;
	angle = degToRad( angle );
	
	cot = (float)cos(angle) / (float)sin(angle);
	
	result[0][0] = cot / aspect;
	result[0][1] = 0.0f;
	result[0][2] = 0.0f;
	result[0][3] = 0.0f;
	
	result[1][0] = 0.0f;
	result[1][1] = cot;
	result[1][2] = 0.0f;
	result[1][3] = 0.0f;
	
	result[2][0] = 0.0f;
	result[2][1] = 0.0f;
	result[2][2] = -(far + near) / (far - near); //-1
	result[2][3] = -1.0f;
	
	
	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = -(2*far*near) / (far - near);//-2*near;
	result[3][3] = 0.0f;
	
	return result; 
}

//-----------------------------------------------------------------------------

mat4 mat4::orthoMatrix(float left, float right, float bottom, float top, float near, float far) {
	mat4 result;
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;
	
	result[0][0] = 2.0f / width;
	result[0][1] = 0.0f;
	result[0][2] = 0.0f;
	result[0][3] = 0.0f;
	
	result[1][0] = 0.0f;
	result[1][1] = 2.0f / height;
	result[1][2] = 0.0f;
	result[1][3] = 0.0f;
	
	result[2][0] = 0.0f;
	result[2][1] = 0.0f;
	result[2][2] = -(2.0f) / depth;
	result[2][3] = 0.0f;
	
	result[3][0] = -(right + left) / width;
	result[3][1] = -(top + bottom) / height;
	result[3][2] = -(far + near) / depth;
	result[3][3] = 1.0f;
	
	return result; 
}
	
//-----------------------------------------------------------------------------

// Invert the matrix44
mat4 invert(const mat4& m) {	
	mat4 a(m);
	mat4 b = mat4::identityMatrix();
	
	int r, c;
	int cc;
	int rowMax; // Points to max abs value row in this column
	int row;
	float tmp;
	
	// Go through columns
	for (c=0; c<4; c++) {
		// Find the row with max value in this column
		rowMax = c;
		for (r=c+1; r<4; r++) {
			if (fabs(a[c][r]) > fabs(a[c][rowMax]))	{
				rowMax = r;
			}
		}
		
		// If the max value here is 0, we can't invert.  Return identity.
		if (a[rowMax][c] == 0.0f)
			return(mat4::identityMatrix());
		
		// Swap row "rowMax" with row "c"
		for (cc=0; cc<4; cc++) {
			tmp = a[cc][c];
			a[cc][c] = a[cc][rowMax];
			a[cc][rowMax] = tmp;
			tmp = b[cc][c];
			b[cc][c] = b[cc][rowMax];
			b[cc][rowMax] = tmp;
		}
		
		// Now everything we do is on row "c".
		// Set the max cell to 1 by dividing the entire row by that value
		tmp = a[c][c];
		for (cc=0; cc<4; cc++) {
			a[cc][c] /= tmp;
			b[cc][c] /= tmp;
		}
		
		// Now do the other rows, so that this column only has a 1 and 0's
		for (row = 0; row < 4; row++) {
			if (row != c) {
				tmp = a[c][row];
				for (cc=0; cc<4; cc++){
					a[cc][row] -= a[cc][c] * tmp;
					b[cc][row] -= b[cc][c] * tmp;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------
	
/*
 mat4& mat4::transpose()  {
 float t;
 
 for (int c=0; c<4; c++) {
 for (int r=c+1; r<4; r++) {
 t = col[c][r];
 col[c][r] = col[r][c];
 col[r][c] = t;
 } 
 } 
 
 return *this;
 } 
 
 //-----------------------------------------------------------------------------
 
 // Invert the matrix44
 mat4& mat4::invert() 
 {
 mat4 a(*this);
 mat4 b = mat4::createIdentityMatrix();
 
 int r, c;
 int cc;
 int rowMax; // Points to max abs value row in this column
 int row;
 float tmp;
 
 // Go through columns
 for (c=0; c<4; c++) {
 // Find the row with max value in this column
 rowMax = c;
 for (r=c+1; r<4; r++) {
 if (fabs(a[c][r]) > fabs(a[c][rowMax]))	{
 rowMax = r;
 }
 }
 
 // If the max value here is 0, we can't invert.  Return identity.
 if (a[rowMax][c] == 0.0f)
 return(identity());
 
 // Swap row "rowMax" with row "c"
 for (cc=0; cc<4; cc++) {
 tmp = a[cc][c];
 a[cc][c] = a[cc][rowMax];
 a[cc][rowMax] = tmp;
 tmp = b[cc][c];
 b[cc][c] = b[cc][rowMax];
 b[cc][rowMax] = tmp;
 }
 
 // Now everything we do is on row "c".
 // Set the max cell to 1 by dividing the entire row by that value
 tmp = a[c][c];
 for (cc=0; cc<4; cc++) {
 a[cc][c] /= tmp;
 b[cc][c] /= tmp;
 }
 
 // Now do the other rows, so that this column only has a 1 and 0's
 for (row = 0; row < 4; row++) {
 if (row != c) {
 tmp = a[c][row];
 for (cc=0; cc<4; cc++){
 a[cc][row] -= a[cc][c] * tmp;
 b[cc][row] -= b[cc][c] * tmp;
 }
 }
 }
 
 }
 
 *this = b;
 
 return *this;
 } 
*/

}


