/*
 *  RaytracedTunnel.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/23/09.
 *  Copyright 2009 vorg. All rights reserved.
 *
 */

#include "RaytracedTunnel.h"
#include "Timer.h"

// attribute index
enum {
    ATTRIB_POSITON,
	ATTRIB_NORMAL,
	ATTRIB_TEXCOORD0,	
    NUM_ATTRIBUTES
};

//------------------------------------------------------------------------------

RaytracedTunnel::RaytracedTunnel() {	
	Log::msg("RaytracedTunnel+");
	
	shader = new Shader();
	const char* shaderCode = osLoadTextFile("raytracedTunnel.glsl");
	shader->load(shaderCode);
	
	//texture = Texture2D::create(256, 256);
	texture = Texture2D::generateChecker();
}

//------------------------------------------------------------------------------

RaytracedTunnel::~RaytracedTunnel() {
	Log::msg("RaytracedTunnel-");	
	delete texture;
	delete shader;
}

//------------------------------------------------------------------------------

void RaytracedTunnel::draw() {			
	glClearColor(0, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	static float positions[] = {
		-1, -1, 
		-1,  1, 
		 1,  1, 
		-1, -1,
		 1,  1,
		 1, -1
	};	
	
	static float texCoords[] = {
		0, 0, 
		0, 1, 
		1, 1, 
		0, 0,
		1, 1,
		1, 0
	};	
	static unsigned short indices[] = {0, 1, 2, 3, 4, 5};
	
	shader->bind();
	shader->setUniform("time", Timer::getInstance().getTime());
	shader->setUniform("diffuseTex", 0);	
	
	//Log::msg("time: %f", Timer::getInstance().getTime());
	
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	
	glVertexAttribPointer(ATTRIB_POSITON, 2, GL_FLOAT, false, 0, positions);
	glEnableVertexAttribArray(ATTRIB_POSITON);
	
	glVertexAttribPointer(ATTRIB_NORMAL, 2, GL_FLOAT, false, 0, positions);	
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	
	glVertexAttribPointer(ATTRIB_TEXCOORD0, 2, GL_FLOAT, false, 0, texCoords);	
	glEnableVertexAttribArray(ATTRIB_TEXCOORD0);	
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);		
}

//------------------------------------------------------------------------------


