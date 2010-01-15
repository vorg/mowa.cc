/*
 *  VBOGeometryRenderer.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/14/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_VBO_GEOMETRY_RENDERER_H
#define FLOW_VBO_GEOMETRY_RENDERER_H

#include "GeometryRenderer.h"

namespace flow {
	
//------------------------------------------------------------------------------

class VBOGeometryRenderer : public GeometryRenderer {
private:
	std::vector<unsigned int>	attribBuffers;
	unsigned int				indexBuffer;
	void rebuild();
public:
	VBOGeometryRenderer(Geometry* geom);
	~VBOGeometryRenderer();
	void render(Shader* shader);
};

//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_VBO_GEOMETRY_RENDERER_H