/*
 *  DirectMemoryAccess.h
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef DIRECT_MEMORY_ACCESS_H
#define DIRECT_MEMORY_ACCESS_H

#include "GLApp.h"
#include "Graphics.h"
#include "Sphere.h"
#include "Effect.h"

using namespace flow;

//------------------------------------------------------------------------------

class DirectMemoryAccess : public GLApp {
private:
	Effect* effect;
protected:
	void draw();
public:
	void init();
	void dispose();	
	void onMouseDown(int x, int y, int key);
	void onMouseUp(int x, int y, int key);
	void onMouseMove(int x, int y, int key);
};

//------------------------------------------------------------------------------

#endif DIRECT_MEMORY_ACCESS_H

