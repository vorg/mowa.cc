/*
 *  EmptyExample.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/3/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef EMPTY_EXAMPLE_H
#define EMPTY_EXAMPLE_H

#include "Effect.h"
#include "Geometry.h"
#include "Shader.h"

using namespace flow;

class EmptyExample : public Effect {
private:
	Shader* shader;
	Geometry* geom;
	
public:
	EmptyExample();
	~EmptyExample();
	
	void draw();		
	void onMouseDown(int x, int y, int key);	
	void onMouseMove(int x, int y, int key);
	void onMouseUp(int x, int y, int key);	
	void render(Geometry* geom, Shader* shader);
};	

#endif EMPTY_EXAMPLE_H

