/*
 *  ScreenQuad.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/1/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#include "FullScreenQuad.h"
#include "MathLib.h"
#include "Utils.h"

namespace flow {	

//------------------------------------------------------------------------------

FullScreenQuad::FullScreenQuad() {	
	vertexStream.addAttrib("position", TYPE_VEC2);
	vertexStream.addAttrib("texCoord0", TYPE_VEC2);
	genFullScreenQuad();
}	

//------------------------------------------------------------------------------

FullScreenQuad::~FullScreenQuad() {
}


//------------------------------------------------------------------------------

void FullScreenQuad::genFullScreenQuad() {
	vertexStream.setNumVertices(6);
	vertexStream.setNumIndices(6);
	
	VertexAttrib* posAttrib = vertexStream.getAttrib("position", TYPE_VEC2);
	vec2* posBuf = (vec2*)posAttrib->getBuffer();
	
	VertexStreamIndex* indexBuf = vertexStream.getIndices();
	
	VertexAttrib* texCoord0Attrib = vertexStream.getAttrib("texCoord0", TYPE_VEC2);
	vec2* texCoord0Buf = (vec2*)texCoord0Attrib->getBuffer();
	
	posBuf[0] = vec2(-1, -1);
	posBuf[1] = vec2(-1,  1);
	posBuf[2] = vec2( 1,  1);
	posBuf[3] = vec2(-1, -1);
	posBuf[4] = vec2( 1,  1);
	posBuf[5] = vec2( 1, -1);
	
	texCoord0Buf[0] = vec2(0,1);
	texCoord0Buf[1] = vec2(0,0);
	texCoord0Buf[2] = vec2(1,0);
	texCoord0Buf[3] = vec2(0,1);
	texCoord0Buf[4] = vec2(1,0);
	texCoord0Buf[5] = vec2(1,1);
	
	indexBuf[0] = 0;
	indexBuf[1] = 1;
	indexBuf[2] = 2;
	indexBuf[3] = 3;
	indexBuf[4] = 4;
	indexBuf[5] = 5;	
}

//------------------------------------------------------------------------------


}


