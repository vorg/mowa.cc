/*
 *  GLApp.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "GLApp.h"
#include "Utils.h"
#include "Timer.h"

using namespace flow;

//------------------------------------------------------------------------------

void GLApp::init() {
	Log::msg("GLApp::init");
	
	Log::msg("	glGenFramebuffers");
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		
	Log::msg("	glGenRenderbuffers");
	glGenRenderbuffers(1, &colorRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);		
	Log::msg("	osRenderbufferStorage");
	osRenderbufferStorage();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);	
	
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &windowWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &windowHeight);
	
	Log::msg("	w:%d h:%d", windowWidth, windowHeight);
	
	Log::msg("	glGenRenderbuffers depthRenderbuffer");
	glGenRenderbuffers(1, &depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
	
	Log::msg("	glCheckFramebufferStatus");
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
	if(status != GL_FRAMEBUFFER_COMPLETE) {
		Log::msg("failed to make complete framebuffer object %x", status);
	}
	Log::msg("GLApp::init done");
}

//------------------------------------------------------------------------------

void GLApp::draw() {
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

//------------------------------------------------------------------------------

void GLApp::update() {
	Timer::getInstance().update();		
	
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
	draw();
	
	glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
	osPresentRenderbuffer();
}

//------------------------------------------------------------------------------

void GLApp::dispose() {
	if (framebuffer) {
		glDeleteFramebuffers(1, &framebuffer);
		framebuffer = 0;
	}
	
	if (colorRenderbuffer) {
		glDeleteRenderbuffers(1, &colorRenderbuffer);
		colorRenderbuffer = 0;
	}
}

//------------------------------------------------------------------------------

Dimensions GLApp::getWindowSize() {
	return Dimensions(windowWidth, windowHeight);
}

//------------------------------------------------------------------------------

