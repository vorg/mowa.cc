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

namespace flow {
	
//------------------------------------------------------------------------------
class Geometry {
protected:
	VertexStream vertexStream;
public:
	VertexStream& getVertexStream() { return vertexStream; }
	
	void invertNormals();
};	
//------------------------------------------------------------------------------
	
}

#endif FLOW_GEOMETRY_H

