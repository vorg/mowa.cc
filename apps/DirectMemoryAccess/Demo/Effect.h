/*
 *  Effect.h
 *  DMA
 *
 *  Created by vorg on 2009-10-17.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef EFFECT_H
#define EFFECT_H

#include "Utils.h"

using namespace flow;

class Effect {
public:
	Effect() {}
	virtual ~Effect() {};
	
	virtual void draw() {};	
	
	virtual void onMouseDown(int x, int y, int key = 1) {};
	virtual void onMouseUp(int x, int y, int key = 1) {};	
	virtual void onMouseMove(int x, int y, int key = 1) {};	
};

#endif EFFECT_H

