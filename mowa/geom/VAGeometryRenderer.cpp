/*
 *  VAGeometryRenderer.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/14/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#include "VAGeometryRenderer.h"
#include "Geometry.h"

namespace flow {

//------------------------------------------------------------------------------
	
VAGeometryRenderer::VAGeometryRenderer(Geometry* geom) : GeometryRenderer(geom) {
	
}
	
	
//------------------------------------------------------------------------------

VAGeometryRenderer::~VAGeometryRenderer() {
	
}
	
//------------------------------------------------------------------------------
	
void VAGeometryRenderer::render(Shader* shader) {
	VertexStream* vs = &geom->getVertexStream();
	
	for(int i=0; i<shader->attribDeclarations.size(); i++) {
		VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
		VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
		void* buf = attrib->getBuffer();
		glVertexAttribPointer(i, attrib->getSize(), GL_FLOAT, false, 0, buf);
		glEnableVertexAttribArray(i);
	}
	
	glDrawElements(geom->getPrimitiveType(), vs->getNumIndices(), vs->getIndexType(), vs->getIndices());		
}

//------------------------------------------------------------------------------
	
	
}