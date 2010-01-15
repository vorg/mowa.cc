/*
 *  VAGeometryRenderer.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/14/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_VA_GEOMETRY_RENDERER_H
#define FLOW_VA_GEOMETRY_RENDERER_H

#include "GeometryRenderer.h"

namespace flow {
	
//------------------------------------------------------------------------------
	
class VAGeometryRenderer : public GeometryRenderer {
public:
	VAGeometryRenderer(Geometry* geom);
	~VAGeometryRenderer();
	void render(Shader* shader);
};
	
//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_VA_GEOMETRY_RENDERER_H
