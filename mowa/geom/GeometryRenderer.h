/*
 *  GeometryRenderer.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/14/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_GEOMETRY_RENDERER_H
#define FLOW_GEOMETRY_RENDERER_H

#include "Shader.h"

namespace flow {
	
class Geometry;

//------------------------------------------------------------------------------

class GeometryRenderer {
protected:
	bool isValid;
	Geometry* geom;
public:	
	GeometryRenderer(Geometry* geom) { this->geom = geom; isValid = false; };
	virtual ~GeometryRenderer() { };
	virtual void render(Shader* shader) = 0;
	void invalidate() { isValid = false; }
};		

//------------------------------------------------------------------------------

} //namespace flow	

#endif FLOW_GEOMETRY_RENDERER_H

