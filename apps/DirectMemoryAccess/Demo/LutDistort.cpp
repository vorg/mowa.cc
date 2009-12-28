/*
 *  LutDistort.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/25/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "LutDistort.h"


#include "LutDistort.h"
#include "Timer.h"

// attribute index
enum {
    ATTRIB_POSITON,
	ATTRIB_NORMAL,
	ATTRIB_TEXCOORD0,	
    NUM_ATTRIBUTES
};

//------------------------------------------------------------------------------

LutDistort::LutDistort() {	
	Log::msg("LutDistort+");
	
	shader = new Shader();
	const char* shaderCode = osLoadTextFile("lutDistort.glsl");
	shader->load(shaderCode);
	
	////textureClouds = Texture2D::fromFile("clouds_mirror.png");
	textureStripes = Texture2D::fromFile("stripes.png");
	textureStripes3 = Texture2D::fromFile("stripes3.png");
	textureChecker = Texture2D::generateChecker();	
	
	const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
	const char* ext = "OES_texture_float";
	char* pos = strstr(extensions, ext);
	Log::msg("%s:%d", ext, pos);
		
	numModes = 9;
	mode = numModes-1;
	crossFade = 0;
}

//------------------------------------------------------------------------------

LutDistort::~LutDistort() {
	Log::msg("LutDistort-");	
	delete textureClouds;
	delete textureStripes;
	delete textureStripes3;	
	delete textureChecker;	
	delete shader;
}

//------------------------------------------------------------------------------

void LutDistort::createLut() {
	float* data;
	int w = 512;
	int h = 512;	
	for( int j=0; j < w; j++ ) {
		for( int i=0; i < h; i++ ) {
			const float x = -1.00f + 2.00f*(float)i/(float)w;
			const float y = -1.00f + 2.00f*(float)j/(float)h;
			const float d = sqrtf( x*x + y*y );
			const float a = atan2f( y, x );
			
			float u = cosf( a )/d;
			float v = sinf( a )/d;
			
			*data++ = fmodf( u, 1.0f );
			*data++ = fmodf( v, 1.0f );
		}
	}
}

//------------------------------------------------------------------------------

void LutDistort::draw() {			
	glClearColor(0, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthMask(false);
	
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
	shader->setUniform("mode", mode);	
	shader->setUniform("crossFade", crossFade);	
	
	//Log::msg("time: %f", Timer::getInstance().getTime());
	
	glActiveTexture(GL_TEXTURE0);
	if (mode == 1) {
		textureStripes3->bind();
	}
	else if (mode == 2) {
		textureStripes->bind();
	}
	else if (mode == 8) {
		textureChecker->bind();
	}
	else {
		textureClouds->bind();
	}
	
	glVertexAttribPointer(ATTRIB_POSITON, 2, GL_FLOAT, false, 0, positions);
	glEnableVertexAttribArray(ATTRIB_POSITON);
	
	glVertexAttribPointer(ATTRIB_NORMAL, 2, GL_FLOAT, false, 0, positions);	
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	
	glVertexAttribPointer(ATTRIB_TEXCOORD0, 2, GL_FLOAT, false, 0, texCoords);	
	glEnableVertexAttribArray(ATTRIB_TEXCOORD0);	
	
	glDepthMask(false);	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);		
	glDepthMask(true);
}

//------------------------------------------------------------------------------

void LutDistort::onMouseDown(int x, int y, int key) {
	mode = (mode + 1) % numModes;
}

//------------------------------------------------------------------------------

void LutDistort::onMouseMove(int x, int y, int key) {
	crossFade = x / 480.0f;
	Log::msg("%f", crossFade);
}

//------------------------------------------------------------------------------



