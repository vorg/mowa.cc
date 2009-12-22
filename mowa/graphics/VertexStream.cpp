/*
 *  VertexStream.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "VertexStream.h"
#include "Vec.h"
#include "Utils.h"

namespace flow {

//-----------------------------------------------------------------------------

VertexAttrib::VertexAttrib(VertexAttribType vertexAttribType, DataType dataType) {
	numVertices = 0;
	this->vertexAttribType = vertexAttribType;
	this->dataType = dataType;
	
	switch(dataType) {
		case TYPE_FLOAT:	stride = sizeof(float); break;
		case TYPE_VEC2:		stride = sizeof(vec2); break;
		case TYPE_VEC3:		stride = sizeof(vec3); break;
		default :	
			stride = 0;		
			Log::msg("ERROR: Vertex AttribType have to be float, vec2 or vec3");
	}
}

//-----------------------------------------------------------------------------

void* VertexAttrib::getBuffer() {
	if (buffer.size() > 0) return (void*)&(buffer[0]);
	else return NULL;
}

//-----------------------------------------------------------------------------

unsigned int VertexAttrib::getNumVertices() {
	return numVertices;
}

//-----------------------------------------------------------------------------

VertexAttribType VertexAttrib::getVertexAttribType() {
	return vertexAttribType;
}

//-----------------------------------------------------------------------------

DataType VertexAttrib::getDataType() {
	return dataType;
}

//-----------------------------------------------------------------------------

unsigned char VertexAttrib::getStride() {
	return stride;
}

//-----------------------------------------------------------------------------

void VertexAttrib::setNumVertices(unsigned int numVertices) {
	this->numVertices = numVertices;
	buffer.resize(numVertices * stride);
}

//-----------------------------------------------------------------------------

VertexStream::VertexStream() : numVertices(0) {
	
}


//-----------------------------------------------------------------------------
VertexStream::~VertexStream() {
	for(int i=0; i<attribs.size(); i++) {
		delete attribs[i];
	}
	attribs.clear();
}
//-----------------------------------------------------------------------------

unsigned int VertexStream::getNumAttribs() {
	return attribs.size();
}

//-----------------------------------------------------------------------------

VertexAttrib* VertexStream::addAttrib(VertexAttribType type, DataType dataType) {	
	VertexAttrib* attrib = getAttrib(type, dataType);
	if (attrib != NULL) return attrib; //taki atrybut juz mamy
	
	VertexAttrib* newAttrib = new VertexAttrib(type, dataType);
	attribs.push_back(newAttrib);
	
	attrib = attribs[attribs.size()-1];
	attrib->setNumVertices(numVertices);
	
	return attrib;
}

//-----------------------------------------------------------------------------

VertexAttrib* VertexStream::getAttrib(VertexAttribType type, DataType dataType) {
	for(int i=0; i<attribs.size(); i++) {
		if ((attribs[i]->getVertexAttribType() == type)
			&& (attribs[i]->getDataType() == dataType)) {
			return attribs[i];
		}
	}
	
	return NULL;
}

//-----------------------------------------------------------------------------

VertexAttrib* VertexStream::getAttrib(unsigned int index) {
	if (index > attribs.size()) return NULL;
	else return attribs[index];
}

//-----------------------------------------------------------------------------

unsigned int VertexStream::getNumVertices() {
	return numVertices;
}

//-----------------------------------------------------------------------------

void VertexStream::setNumVertices(unsigned int numVertices) {
	this->numVertices = numVertices;
	
	for(int i=0; i<attribs.size(); i++) {
		Log::msg(" %d %s", i, attribs[i]->getVertexAttribType().c_str());
		attribs[i]->setNumVertices(numVertices);
	}
}

//-----------------------------------------------------------------------------

unsigned int VertexStream::getNumIndices() {
	return indices.size();
}

//-----------------------------------------------------------------------------

void VertexStream::setNumIndices(unsigned int numIndices) {
	indices.resize(numIndices);
}

//-----------------------------------------------------------------------------

unsigned short* VertexStream::getIndices() {
	if (indices.size() > 0) return &indices[0];
	else return NULL;
}
	
//-----------------------------------------------------------------------------

unsigned int VertexStream::getNumIndices2() {
	return indices2.size();
}

//-----------------------------------------------------------------------------

void VertexStream::setNumIndices2(unsigned int numIndices) {
	indices2.resize(numIndices);
}

//-----------------------------------------------------------------------------

unsigned short* VertexStream::getIndices2() {
	if (indices2.size() > 0) return &indices2[0];
	else return NULL;
}

//-----------------------------------------------------------------------------

} //namespace flow

