/*
 *  GLApp.h
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef GL_APP_H
#define GL_APP_H

#include "Graphics.h"
#include "Dimensions.h"

//------------------------------------------------------------------------------

class GLApp {
protected:
	GLuint framebuffer;
	GLuint colorRenderbuffer;
	GLuint depthRenderbuffer;
	GLint windowWidth;
	GLint windowHeight;

	virtual void draw();
	
public:
	GLApp() { };
	virtual ~GLApp() { dispose(); };
	virtual void init();
	virtual void update();
	virtual void dispose();
	virtual void onMouseDown(int x, int y, int key = 1) {};
	virtual void onMouseUp(int x, int y, int key = 1) {};
	virtual void onMouseMove(int x, int y, int key = 1) {};
	
	
	Dimensions getWindowSize();
};

//------------------------------------------------------------------------------

#endif GL_APP_H
