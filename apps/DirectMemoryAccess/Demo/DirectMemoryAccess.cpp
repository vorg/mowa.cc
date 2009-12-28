/*
 *  DirectMemoryAccess.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "DirectMemoryAccess.h"
#include "Utils.h"
#include "OS.h"
#include "Timer.h"
#include "MathLib.h"
#include "Effect.h"
#include "DistortedSphere.h"
#include "RaytracedTunnel.h"
#include "LutDistort.h"
#include "ExampleTexturing.h"

using namespace flow;

//------------------------------------------------------------------------------

void DirectMemoryAccess::init() {
	Log::msg("DirectMemoryAccess::init");
	GLApp::init();
	
	effect = new ExampleTexturing();
	//effect = new LutDistort();
}

//------------------------------------------------------------------------------

void DirectMemoryAccess::draw() {	
	GLApp::draw();
	if (Timer::getInstance().getTotalFrameCount() % 100 == 33) {
		Log::msg("draw %f", Timer::getInstance().getFPS());
	}				
	effect->draw();
}

//------------------------------------------------------------------------------

void DirectMemoryAccess::dispose() {
	if (effect) {
		delete effect;
		effect = NULL;
	}
}

//------------------------------------------------------------------------------

void DirectMemoryAccess::onMouseDown(int x, int y, int key = 1) {
	effect->onMouseDown(x, y, key);
}

//------------------------------------------------------------------------------

void DirectMemoryAccess::onMouseUp(int x, int y, int key = 1) {
	effect->onMouseUp(x, y, key);
}

//------------------------------------------------------------------------------

void DirectMemoryAccess::onMouseMove(int x, int y, int key = 1) {
	effect->onMouseMove(x, y, key);
}

//------------------------------------------------------------------------------
