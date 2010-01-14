/*
 *  EmptyExample.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/3/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#include "EmptyExample.h"


//------------------------------------------------------------------------------

EmptyExample::EmptyExample() {
}

//------------------------------------------------------------------------------

EmptyExample::~EmptyExample() {
}

//------------------------------------------------------------------------------

void EmptyExample::draw() {
}

//------------------------------------------------------------------------------

void EmptyExample::onMouseDown(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void EmptyExample::onMouseMove(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void EmptyExample::onMouseUp(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void EmptyExample::render(Geometry* geom, Shader* shader) {
	VertexStream* vs = &geom->getVertexStream();
	
	for(int i=0; i<shader->attribDeclarations.size(); i++) {
		VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
		VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
		void* buf = attrib->getBuffer();
		glVertexAttribPointer(i, attrib->getSize(), GL_FLOAT, false, 0, buf);
		glEnableVertexAttribArray(i);
	}
	
	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());	
}

//------------------------------------------------------------------------------





