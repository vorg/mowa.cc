/*
 *  VBOGeometryRenderer.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/14/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#include "VBOGeometryRenderer.h"
#include "Geometry.h"

namespace flow {
	
//------------------------------------------------------------------------------

VBOGeometryRenderer::VBOGeometryRenderer(Geometry* geom) : GeometryRenderer(geom) {
	
}

//------------------------------------------------------------------------------

VBOGeometryRenderer::~VBOGeometryRenderer() {
}

//------------------------------------------------------------------------------

void VBOGeometryRenderer::render(Shader* shader) {
	if (!isValid) {		
		rebuild();
	}
	VertexStream* vs = &geom->getVertexStream();
	
	for(int i=0; i<shader->attribDeclarations.size(); i++) {
		VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
		VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
		glBindBuffer(GL_ARRAY_BUFFER, attribBuffers[vs->getAttribIndex(attrib)]);		
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrib->getSize(), GL_FLOAT, false, 0, 0);
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, 0);	
}

//------------------------------------------------------------------------------
	
//TODO: invalidation proof
void VBOGeometryRenderer::rebuild() {
	VertexStream* vs = &geom->getVertexStream();
	for(int i=0; i<vs->getNumAttribs(); i++) {
		VertexAttrib* attrib = vs->getAttrib(i);
		void* buf = attrib->getBuffer();
		unsigned int bufferId;
		glGenBuffers(1, &bufferId);
		attribBuffers.push_back(bufferId);		
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		int size = attrib->getNumVertices() * attrib->getSize() * attrib->getStride();
		glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);			
	}	
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	int size = vs->getNumIndices() * sizeof(unsigned short);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vs->getIndices(), GL_STATIC_DRAW);
	
	isValid = true;
}
	
//------------------------------------------------------------------------------

} //namespace flow