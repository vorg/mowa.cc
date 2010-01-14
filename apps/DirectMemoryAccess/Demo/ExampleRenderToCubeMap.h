/*
 *  ExampleRenderToCubeMap.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef EXAMPLE_RENDER_TO_CUBEMAP_H
#define EXAMPLE_RENDER_TO_CUBEMAP_H

#include "Effect.h"
#include "Utils.h"
#include "Torus.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace flow;

class ExampleRenderToCubeMap : public Effect {
private:
	Shader* torusShader;
	Texture* torusTexture;
	Geometry* torus;		
	Shader* reflectionShader;
	Texture* reflectionTexture;
	unsigned int color_tex;
	unsigned int fb;
	unsigned int depth_rb;
public:
	ExampleRenderToCubeMap();
	~ExampleRenderToCubeMap();
	
	void draw();		
	void onMouseMove(int x, int y, int key);
	void render(Geometry* geom, Shader* shader);
};

#endif EXAMPLE_RENDER_TO_CUBEMAP_H



