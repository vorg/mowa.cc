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
protected:
	VertexStream vertexStream;
	GeometryRenderer* renderer;
public:
	Geometry();
	~Geometry();
	
	VertexStream& getVertexStream() { return vertexStream; }
	
	void invertNormals();
	void render(Shader* shader);
	void invalidate();
};	
//------------------------------------------------------------------------------
	
}

#endif FLOW_GEOMETRY_H

