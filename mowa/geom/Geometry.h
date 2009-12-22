/*
 *  Geometry.h
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "VertexStream.h"

namespace flow {
	
//------------------------------------------------------------------------------
class Geometry {
protected:
	VertexStream vertexStream;
public:
	VertexStream& getVertexStream() { return vertexStream; }
};	
//------------------------------------------------------------------------------
	
}

