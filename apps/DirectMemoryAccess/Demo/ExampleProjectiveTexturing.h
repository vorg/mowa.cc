/*
 *  ExampleProjectiveTexturing.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/3/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef EXAMPLE_PROJECTIVE_TEXTURING_H
#define EXAMPLE_PROJECTIVE_TEXTURING_H

#include "Effect.h"
#include "Cube.h"
#include "Torus.h"
#include "Sphere.h"
#include "Shader.h"

using namespace flow;
class ExampleProjectiveTexturing : public Effect {
private:
	Shader* projectiveTextureShader;
	Torus* torus;
	Cube* cube;
	Sphere* sphere;
	
public:
	ExampleProjectiveTexturing();
	~ExampleProjectiveTexturing();
	
	void draw();		
	void onMouseMove(int x, int y, int key);
	void render(Geometry* geom, Shader* shader);
};	

#endif EXAMPLE_PROJECTIVE_TEXTURING_H

