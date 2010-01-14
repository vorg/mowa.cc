/*
 *  ExampleLighting.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/3/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */


#ifndef EXAMPLE_LIGHTING_H
#define EXAMPLE_LIGHTING_H

#include "Effect.h"
#include "Torus.h"
#include "Cube.h"
#include "Sphere.h"
#include "Shader.h"
#include "Camera.h"

using namespace flow;

class ExampleLighting : public Effect {
private:
	Shader* lightShader;
	Cube* cube;
	Torus* torus;

	Sphere* ball;
	Shader* ballShader;
	vec3 ballColor;
	
	vec3 lightPos;
	vec3 cameraPos;
	
public:
	ExampleLighting();
	~ExampleLighting();
	
	void draw();		
	void onMouseDown(int x, int y, int key);	
	void onMouseMove(int x, int y, int key);
	void onMouseUp(int x, int y, int key);	
	void render(Geometry* geom, Shader* shader);
	
	void drawPointLight();
	void drawPointLight2();	
};	

#endif EXAMPLE_LIGHTING_H