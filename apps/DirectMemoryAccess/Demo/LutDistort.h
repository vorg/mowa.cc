/*
 *  LutDistort.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/25/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef LUT_DISTORT_H
#define LUT_DISTORT_H

#include "Effect.h"
#include "Utils.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace flow;

class LutDistort : public Effect {
private:
	Shader* shader;
	
	Texture2D* textureClouds;
	Texture2D* textureStripes;
	Texture2D* textureChecker;
	int mode;
	int numModes;
	float crossFade;
	
public:
	LutDistort();
	~LutDistort();
	
	void createLut();	
	void draw();	
	
	void onMouseDown(int x, int y);
	void onMouseMove(int x, int y);	
};

#endif LUT_DISTORT_H



