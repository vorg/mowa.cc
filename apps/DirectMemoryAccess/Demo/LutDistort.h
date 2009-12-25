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
	Texture2D* lutTex;
	Texture2D* texture;
	
public:
	LutDistort();
	~LutDistort();
	
	void draw();		
};

#endif LUT_DISTORT_H



