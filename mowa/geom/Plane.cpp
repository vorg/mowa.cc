/*
 *  Plane.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "Plane.h"
#include "MathLib.h"
#include "Utils.h"

namespace flow {	
	
//------------------------------------------------------------------------------

Plane::Plane(float s1, float s2, int axis, int n1, int n2) {	
	//Log::msg("Plane::Plane size1:%f size2:%f axis:%d n1:%d n2:%d", s1, s2, axis, n1, n2);
	vertexStream.addAttrib("position", TYPE_VEC3);
	vertexStream.addAttrib("normal", TYPE_VEC3);
	vertexStream.addAttrib("texCoord0", TYPE_VEC2);
	
	genPlane(s1, s2, axis, n1, n2);
}	

//------------------------------------------------------------------------------

Plane::~Plane() {
}


//------------------------------------------------------------------------------

void Plane::genPlane(float s1, float s2, int axis, int n1, int n2) {
	int estimatedNumPoints = (n1+1)*(n2+1);
	
	vertexStream.setNumVertices(estimatedNumPoints);
	vertexStream.setNumIndices(n1 * n2 * 6);
	
	VertexAttrib* posAttrib = vertexStream.getAttrib("position", TYPE_VEC3);
	vec3* posBuf = (vec3*)posAttrib->getBuffer();
	
	unsigned short* indexBuf = vertexStream.getIndices();
	//unsigned short* indexBuf2 = vertexStream.getIndices2();
	
	VertexAttrib* normAttrib = vertexStream.getAttrib("normal", TYPE_VEC3);
	vec3* normBuf = (vec3*)normAttrib->getBuffer();
	
	VertexAttrib* texCoord0Attrib = vertexStream.getAttrib("texCoord0", TYPE_VEC2);
	vec2* texCoord0Buf = (vec2*)texCoord0Attrib->getBuffer();
	
	float k1, k2; 
	vec3 normal;
	
	if (axis == Plane::X) {
		normal = vec3(1,0,0);
	}
	else if (axis == Plane::Y) {
		normal = vec3(0,1,0);
	}
	else if (axis == Plane::Z) {
		normal = vec3(0,0,1);
	}
	
	
	int i = 0;
	int ii = 0;
	for(int y=0; y<=n2; y++) {
		k2 = y/(float)n2;
		for(int x=0; x<=n1; x++) {
			k1 = x/(float)n1;			
			if (axis == Plane::X) {
				posBuf[i] = vec3(0, s1/2*(-1+2*k1), s2/2*(-1+2*k2));
			}
			else if (axis == Plane::Y) {
				posBuf[i] = vec3(s1/2*(-1+2*k1),0, s2/2*(-1+2*k2));
			}
			else if (axis == Plane::Z) {
				posBuf[i] = vec3(s1/2*(-1+2*k1), s2/2*(-1+2*k2), 0);
			}
			
			normBuf[i] = vec3(normal.x, normal.y, normal.z);
			texCoord0Buf[i ] = -vec2(k1, k2);
			
			if (x<n1 && y<n2) {
				//nx+1 bo nx to liczba segmentow, a punktow jest o jeden wiecej
				//flist.push_back(Face(i+j*(n1+1), i+(j+1)*(n1+1)+1, i+j*(n1+1)+1));
				indexBuf[ii*6  ] = x+y*(n1+1); 
				indexBuf[ii*6+1] = x+(y+1)*(n1+1)+1;
				indexBuf[ii*6+2] = x+y*(n1+1)+1;
				
				//flist.push_back(Face(i+j*(n1+1), i+(j+1)*(n1+1), i+(j+1)*(n1+1)+1));			
				indexBuf[ii*6+3] = x+y*(n1+1); 
				indexBuf[ii*6+4] = x+(y+1)*(n1+1);
				indexBuf[ii*6+5] = x+(y+1)*(n1+1)+1;
				ii++;
			}
			
			i++;
		}
	}
}
	
//------------------------------------------------------------------------------

	
}

