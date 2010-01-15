/*
 *  Geometry.h
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_GEOMETRY_H
#define FLOW_GEOMETRY_H

#include "VertexStream.h"
#include "Shader.h"

namespace flow {

//------------------------------------------------------------------------------
	
class GeometryRenderer;
	
//------------------------------------------------------------------------------
	
class Geometry {
public:
	enum PrimitiveType {
		Points			= 0x0000,		//GL_POINTS
		Lines			= 0x0001,		//GL_LINES
		Triangles		= 0x0004,		//GL_TRIANGLES
		TrianglesStrip	= 0x0005		//GL_TRIANGLE_STRIP
	};
protected:
	VertexStream vertexStream;
	GeometryRenderer* renderer;
	PrimitiveType primitiveType;

public:
	
	Geometry();
	~Geometry();
	
	VertexStream& getVertexStream() { return vertexStream; }
	
	void invertNormals();
	void render(Shader* shader);
	void invalidate();
	
	PrimitiveType getPrimitiveType() { return primitiveType; }
	void setPrimitiveType(PrimitiveType primitiveType) { this->primitiveType = primitiveType; }
};	
//------------------------------------------------------------------------------
	
}

#endif FLOW_GEOMETRY_H

