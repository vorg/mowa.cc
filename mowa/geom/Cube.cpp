/*
 *  Cube.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/31/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "Cube.h"
#include "Plane.h"
#include "MathLib.h"
#include "Utils.h"

namespace flow {	

//------------------------------------------------------------------------------

Cube::Cube(float sx, float sy, float sz, int nx, int ny, int nz, bool smoothNormals) {	
	//Log::msg("Cube::Cube sx:%f sy:%f sz:%f nx:%d ny:%d nz:%d", sx, sy, sz, nx, ny, nz);
	vertexStream.addAttrib("position", TYPE_VEC3);
	vertexStream.addAttrib("normal", TYPE_VEC3);
	vertexStream.addAttrib("texCoord0", TYPE_VEC2);
	
	genCube(sx, sy, sz, nx, ny, nz, smoothNormals);
}	

//------------------------------------------------------------------------------

Cube::~Cube() {
}


//------------------------------------------------------------------------------

void Cube::genCube(float sx, float sy, float sz, int nx, int ny, int nz, bool smoothNormals) {
	int estimatedNumPoints = 2*(nx+1)*(ny+1) + 2*(nx+1)*(nz+1) + 2*(ny+1)*(nz+1);
	
	vertexStream.setNumVertices(estimatedNumPoints);
	vertexStream.setNumIndices((2*nx*ny + 2*nx*nz + 2*ny*nz) * 6);
	
	VertexAttrib* posAttrib = vertexStream.getAttrib("position", TYPE_VEC3);
	vec3* posBuf = (vec3*)posAttrib->getBuffer();
	
	unsigned short* indexBuf = vertexStream.getIndices();
	//unsigned short* indexBuf2 = vertexStream.getIndices2();
	
	VertexAttrib* normalAttrib = vertexStream.getAttrib("normal", TYPE_VEC3);
	vec3* normalBuf = (vec3*)normalAttrib->getBuffer();
	
	VertexAttrib* texCoord0Attrib = vertexStream.getAttrib("texCoord0", TYPE_VEC2);
	vec2* texCoord0Buf = (vec2*)texCoord0Attrib->getBuffer();
	
	//tabela pomocnicza z iloscia segmentow scianki
	//zrobiona zeby mozna ja bylo uzyac w for(;;){}
	int def[3][2] = {
		{ny, nz},
		{nx, nz},
		{nx, ny}
	};
	
	int axis[] = {
		Plane::X,
		Plane::Y,
		Plane::Z
	};
	
	//rozmiary sicanek
	float size[3][2] = {
		{sy, sz},
		{sx, sz},
		{sx, sy}
	};
	
	//o tyle nalezy przesunac kolejne scianki z pkt (0,0)
	vec3 shift[] = {
		vec3(-sx/2,  0,  0),
		vec3(  0,-sy/2,  0),
		vec3(  0,  0,-sz/2)
	};
	
	//o te wartosci przemnazamy scianke orginalna zeby otrzymac jej odbicie po drugiej stronie
	vec3 mirror[] = {
		vec3( 1, 1, 1),
		vec3(-1, 1,-1),
		vec3( 1, 1,-1),
		vec3( 1,-1, 1),
		vec3( 1, 1, 1),
		vec3( 1,-1,-1)
	};
	
	//		o te wartosci przemnazamy scianke orginalna zeby otrzymac jej odbicie po drugiej stronie
	vec3 normals[] = {
		vec3(-1, 0, 0),
		vec3( 1, 0, 0),
		vec3( 0,-1, 0),
		vec3( 0, 1, 0),
		vec3( 0, 0,-1),
		vec3( 0, 0, 1)
	};
	
	int allIndices = 0;
	int allVertices = 0;
	for(int axisNum=0; axisNum<3; axisNum++) {
		//FloatVertexAttrib planePosAttrib = (FloatVertexAttrib)planeVS.getAttribByName("pos");
		//float[] planePosBuf = planePosAttrib.getBuffer();
		//FloatVertexAttrib planeNormalAttrib = (FloatVertexAttrib)planeVS.getAttribByName("normal");
		//planeNormalAttrib.getBuffer();
		//FloatVertexAttrib planeTexCoord0Attrib = (FloatVertexAttrib)planeVS.getAttribByName("texCoord0");
		//float[] planeTexCoor0Buf = planeTexCoord0Attrib.getBuffer();
		//int[] planeIndexBuf = planeVS.getIndexBuffer().getBuffer();
		
		Plane* plane = new Plane(size[axisNum][0], size[axisNum][1], axis[axisNum], def[axisNum][0], def[axisNum][1]);
		VertexStream planeVS = plane->getVertexStream();
		
		VertexAttrib* planePosAttrib = planeVS.getAttrib("position", TYPE_VEC3);
		vec3* planePosBuf = (vec3*)planePosAttrib->getBuffer();
		
		VertexAttrib* planeTexCoord0Attrib = planeVS.getAttrib("texCoord0", TYPE_VEC2);
		vec2* planeTexCoord0Buf = (vec2*)planeTexCoord0Attrib->getBuffer();
		
		unsigned short* planeIndexBuf = planeVS.getIndices();		
		
		int numPlaneVertices = planeVS.getNumVertices();//sizeof(planePosBuf)/sizeof(vec3);
		int numPlaneIndices = planeVS.getNumIndices();//sizeof(planeIndexBuf)/sizeof(unsigned short);
		//Log::msg("npv:%d npi:%d", numPlaneVertices, numPlaneIndices);
		
		for(int mirrorSide=0; mirrorSide<2; mirrorSide++) {
			for(int i=0; i<numPlaneVertices; i++) {
				//posBuf[(allVertices+i)*3+0] = ((planePosBuf[i*3  ]) + shift[axisNum].getX()) * mirror[axisNum*2 + mirrorSide].getX();
				//posBuf[(allVertices+i)*3+1] = ((planePosBuf[i*3+1]) + shift[axisNum].getY()) * mirror[axisNum*2 + mirrorSide].getY();
				//posBuf[(allVertices+i)*3+2] = ((planePosBuf[i*3+2]) + shift[axisNum].getZ()) * mirror[axisNum*2 + mirrorSide].getZ();
				posBuf[allVertices+i] = planePosBuf[i] + shift[axisNum];
				posBuf[allVertices+i].x *= mirror[axisNum*2 + mirrorSide].x;
				posBuf[allVertices+i].y *= mirror[axisNum*2 + mirrorSide].y;
				posBuf[allVertices+i].z *= mirror[axisNum*2 + mirrorSide].z;
				if (smoothNormals) {
					//normalBuf[(allVertices+i)*3  ] = posBuf[(allVertices+i)*3  ];
					//normalBuf[(allVertices+i)*3+1] = posBuf[(allVertices+i)*3+1];
					//normalBuf[(allVertices+i)*3+2] = posBuf[(allVertices+i)*3+2];
					normalBuf[allVertices+i] = vec3(posBuf[allVertices+i]);
				}
				else {
					//normalBuf[(allVertices+i)*3  ] = normals[axisNum*2 + mirrorSide].getX();
					//normalBuf[(allVertices+i)*3+1] = normals[axisNum*2 + mirrorSide].getY();
					//normalBuf[(allVertices+i)*3+2] = normals[axisNum*2 + mirrorSide].getZ();
					normalBuf[allVertices+i] = normals[axisNum*2 + mirrorSide];
				}
				//texCoord0Buf[(allVertices+i)*2  ] = planeTexCoor0Buf[i*2  ];
				//texCoord0Buf[(allVertices+i)*2+1] = planeTexCoor0Buf[i*2+1];
				texCoord0Buf[allVertices+i] = planeTexCoord0Buf[i];
			}
			for(int i=0; i<numPlaneIndices; i++) {
				indexBuf[allIndices + i] = allVertices + planeIndexBuf[i];
			}
			
			allVertices += numPlaneVertices;
			allIndices += numPlaneIndices;
		}
		
	}		
}

//------------------------------------------------------------------------------


}

