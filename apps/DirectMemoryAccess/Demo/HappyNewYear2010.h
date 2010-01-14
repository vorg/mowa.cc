/*
 *  HappyNewYear2010.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */


#ifndef HAPPY_NEW_YEAR_2010_H
#define HAPPY_NEW_YEAR_2010_H

#include "Effect.h"
#include "Utils.h"
#include "Torus.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Cube.h"

using namespace flow;

class HappyNewYear2010 : public Effect {
private:
	Shader* bgShader;
	Shader* torusShader;
	
	Texture* torusTexture;
	Texture* bgTexture;
	Geometry* torus;	
	Cube* cube;
	
	Shader* reflectionShader;
	Geometry* mainObject;
	Texture* reflectionTexture;	
	
	Geometry* quad;
	Shader* overlayShader;
	Texture2D* overlayTex;	
	
	float rotY;
	float posY;
	float rotYVel;
	float posYVel;
	
	unsigned int color_tex;
	unsigned int fb;
	unsigned int depth_rb;
public:
	HappyNewYear2010();
	~HappyNewYear2010();
	
	void draw();		
	void onMouseMove(int x, int y, int key);
	void onMouseDown(int x, int y, int key);	
	void onMouseUp(int x, int y, int key);	
	void render(Geometry* geom, Shader* shader);
};

#endif HAPPY_NEW_YEAR_2010_H



