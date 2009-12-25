/*
 *  DistortedSphere.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-17.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "DistortedSphere.h"
#include "Timer.h"

//------------------------------------------------------------------------------

enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};

GLint uniforms[NUM_UNIFORMS];

//------------------------------------------------------------------------------

// attribute index
enum {
    ATTRIB_POSITON,
    //ATTRIB_COLOR,
	ATTRIB_NORMAL,
	ATTRIB_TEXCOORD0,	
    NUM_ATTRIBUTES
};

//------------------------------------------------------------------------------

DistortedSphere::DistortedSphere() {	
	Log::msg("DistortedSphere+");

	shader = new Shader();
	const char* shaderCode = osLoadTextFile("envMap.glsl");
	shader->load(shaderCode);
	
	sphere = new Sphere(1, 32, 16);
	
	strength = 2.0f;	
	
	//texture = Texture2D::create(256, 256);
	//texture = Texture2D::generateChecker();
	texture = Texture2D::fromFile("sphereMap.jpg");
}

//------------------------------------------------------------------------------

DistortedSphere::~DistortedSphere() {
	Log::msg("DistortedSphere-");	
	delete texture;
	delete shader;
	delete sphere;
}

//------------------------------------------------------------------------------

void DistortedSphere::draw() {			
	//glClearColor(0, 0, 0, 0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mat4 projectionMatrix = mat4::perspectiveMatrix(60.00, 480.0f/320.0f, 0.1f, 100.0f);
	mat4 modelviewMatrix = mat4::translationMatrix(0, 0, -3)
		* mat4::rotationMatrix(vec3(0,1,0), 5*Timer::getInstance().getTime()*30)
	* mat4::rotationMatrix(vec3(1,0,0), 3*Timer::getInstance().getTime()*30)
	* mat4::scaleMatrix(0.5, 0.5, 0.5);
	mat4 invModelviewMatrix = invert(modelviewMatrix);
	
	
	shader->bind();
	shader->setUniform("projectionMatrix", projectionMatrix);
	shader->setUniform("modelviewMatrix", modelviewMatrix);
	shader->setUniform("invModelviewMatrix", invModelviewMatrix);
	shader->setUniform("time", Timer::getInstance().getTime());
	if (strength > 0.3) {
		strength *= 0.99;
	}
	shader->setUniform("strength", strength);
	shader->setUniform("diffuseTex", 0);	
	
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	
	/**
	 glVertexAttribPointer(ATTRIB_POSITON, 2, GL_FLOAT, false, 0, squareVertices);
	 glEnableVertexAttribArray(ATTRIB_POSITON);
	 glVertexAttribPointer(ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, 1, 0, squareColors);
	 glEnableVertexAttribArray(ATTRIB_COLOR);
	 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	
	 /**/
	
	VertexStream* vs = &sphere->getVertexStream();
	//	
	//	float positionBuf[] = {0,0,0,0,1,0,1,1,0};
	//	glVertexAttribPointer(ATTRIB_POSITON, 3, GL_FLOAT, false, 0, positionBuf);
	//	glEnableVertexAttribArray(ATTRIB_POSITON);
	//	
	//	unsigned short indexBuf[] = {0,1,2};
	
	glEnable(GL_DEPTH_TEST);
	
	glVertexAttribPointer(ATTRIB_POSITON, 3, GL_FLOAT, false, 0, vs->getAttrib("position", TYPE_VEC3)->getBuffer());
	glEnableVertexAttribArray(ATTRIB_POSITON);
	
	//glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, false, 0, vs->getAttrib("normal", TYPE_VEC3)->getBuffer());	
	//glEnableVertexAttribArray(ATTRIB_COLOR);
	
	glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, false, 0, vs->getAttrib("normal", TYPE_VEC3)->getBuffer());	
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	
	glVertexAttribPointer(ATTRIB_TEXCOORD0, 2, GL_FLOAT, false, 0, vs->getAttrib("texCoord0", TYPE_VEC2)->getBuffer());	
	glEnableVertexAttribArray(ATTRIB_TEXCOORD0);	
	
	shader->setUniform("wireframe", 0.0);
	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());	
	
	shader->setUniform("wireframe", 1.0);	
	glDrawElements(GL_LINES, vs->getNumIndices2(), GL_UNSIGNED_SHORT, vs->getIndices2());
	
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);	
}

//------------------------------------------------------------------------------

void DistortedSphere::onMouseDown(int x, int y) {
	strength = 2.0f;
}

//------------------------------------------------------------------------------
