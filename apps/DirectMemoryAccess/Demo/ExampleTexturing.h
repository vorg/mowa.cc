/*
 *  ExampleTexturing.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/25/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef EXAMPLE_TEXTURING_H
#define EXAMPLE_TEXTURING_H

#include "Effect.h"
#include "Utils.h"
#include "Torus.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace flow;

class ExampleTexturing : public Effect {
private:
	Shader* shader;
	Geometry* geom;
	Texture* texture;
	Sphere* sphere;
	float strength;
	float rotX;
	float rotY;
	int mode;
public:
	ExampleTexturing();
	~ExampleTexturing();
	
	void draw();		
	void setupBasic();
	void setupSphericalEnvironmentMapping();
	void setupCubeMapping();
	void onMouseDown(int x, int y, int key);
	void onMouseMove(int x, int y, int key);
};

#endif EXAMPLE_TEXTURING_H


