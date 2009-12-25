/*
 *  DistortedSphere.h
 *  DMA
 *
 *  Created by vorg on 2009-10-17.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef DISTORED_SPHERE_H
#define DISTORED_SPHERE_H

#include "Effect.h"
#include "Utils.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace flow;

class DistortedSphere : public Effect {
private:
	Shader* shader;
	Sphere* sphere;
	Texture2D* texture;
	float	strength;
	
public:
	DistortedSphere();
	~DistortedSphere();
	
	void draw();	
	
	void onMouseDown(int x, int y);
};

#endif DISTORED_SPHERE_H

