/*
 *  ExampleTexturing.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/25/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "ExampleTexturing.h"
#include "Timer.h"
#include "Sphere.h"
#include "Texture2D.h"
#include "TextureCube.h"

//------------------------------------------------------------------------------

ExampleTexturing::ExampleTexturing() {	
	Log::msg("ExampleTexturing+");
	
	shader = NULL;
	texture = NULL;	
	texture2 = Texture2D::generateChecker();
	geom = new Torus(1, 0.3, 36, 18);	
	sphere = NULL;
	//geom = new Sphere(1, 36, 10);
	strength = 0.0;	
	rotX = 0;
	rotY = 0;
	mode = 2;
}

//------------------------------------------------------------------------------

ExampleTexturing::~ExampleTexturing() {
	Log::msg("ExampleTexturing-");	
	delete texture;
	delete shader;
	delete geom;
	delete sphere;
}

//------------------------------------------------------------------------------

void ExampleTexturing::draw() {			
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);	
	
	switch(mode) {
		case 0: drawBasic(); break;
		case 1: drawSphericalEnvironmentMapping(); break;			
		case 2: drawCubeMapping(); break;			
	}
	
	//VertexStream* vs = &geom->getVertexStream();
//	
//	glVertexAttribPointer(ATTRIB_POSITON, 3, GL_FLOAT, false, 0, vs->getAttrib("position", TYPE_VEC3)->getBuffer());
//	glEnableVertexAttribArray(ATTRIB_POSITON);
//	
//	glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, false, 0, vs->getAttrib("normal", TYPE_VEC3)->getBuffer());	
//	glEnableVertexAttribArray(ATTRIB_NORMAL);
//	
//	glVertexAttribPointer(ATTRIB_TEXCOORD0, 2, GL_FLOAT, false, 0, vs->getAttrib("texCoord0", TYPE_VEC2)->getBuffer());	
//	glEnableVertexAttribArray(ATTRIB_TEXCOORD0);	
//	
//	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());
	
	
	//mat4 modelViewMatrix = mat4::translationMatrix(0, 0, -3)
//	* mat4::rotationMatrix(vec3(0,1,0), rotY) //2*Timer::getInstance().getTime()*30
//	* mat4::rotationMatrix(vec3(1,0,0), rotX)//1*Timer::getInstance().getTime()*30
//	* mat4::scaleMatrix(0.4, 0.4, 0.4);
//	
//	shader->setUniform("modelViewMatrix", modelViewMatrix);
//	
//	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());
	
	//if (sphere) {
//		VertexStream* vs = &sphere->getVertexStream();
//		
//		glEnable(GL_DEPTH_TEST);
//		
//		glVertexAttribPointer(ATTRIB_POSITON, 3, GL_FLOAT, false, 0, vs->getAttrib("position", TYPE_VEC3)->getBuffer());
//		glEnableVertexAttribArray(ATTRIB_POSITON);
//		
//		glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, false, 0, vs->getAttrib("normal", TYPE_VEC3)->getBuffer());	
//		glEnableVertexAttribArray(ATTRIB_NORMAL);
//		
//		glVertexAttribPointer(ATTRIB_TEXCOORD0, 2, GL_FLOAT, false, 0, vs->getAttrib("texCoord0", TYPE_VEC2)->getBuffer());	
//		glEnableVertexAttribArray(ATTRIB_TEXCOORD0);	
//		
//		glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());
//	}
}

//------------------------------------------------------------------------------

void ExampleTexturing::drawBasic() {
	if (!shader) {
		shader = Shader::fromFile("ExampleTexturingBasic.glsl");
	}
	if (!texture) {
		texture = Texture2D::generateChecker();
		//texture = Texture2D::fromFile("rainbow.jpg"); 
	}

	mat4 projectionMatrix = mat4::perspectiveMatrix(60.00, 480.0f/320.0f, 0.1f, 100.0f);
	mat4 modelViewMatrix = mat4::translationMatrix(0, 0, -3)
	* mat4::rotationMatrix(vec3(0,1,0), rotY) //2*Timer::getInstance().getTime()*30
	* mat4::rotationMatrix(vec3(1,0,0), rotX);//1*Timer::getInstance().getTime()*30
	
	shader->bind();
	shader->setUniform("projectionMatrix", projectionMatrix);
	shader->setUniform("modelViewMatrix", modelViewMatrix);
	shader->setUniform("tex0", 0);		
	
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	
	
	render(geom, shader);
}

//------------------------------------------------------------------------------

void ExampleTexturing::drawSphericalEnvironmentMapping() {
	if (!shader) {
		//shader = Shader::fromFile("ExampleTexturingBasic.glsl");
		shader = Shader::fromFile("ExampleTexturingSEM.glsl");		
	}
	if (!texture) {
		//texture = Texture2D::fromFile("ExampleTexturingSEMSpecularMap.jpg"); 
		//texture = Texture2D::fromFile("ExampleTexturingSEMRoom.jpg");
		//texture = Texture2D::fromFile("ExampleTexturingSSEMMetal.jpg");
		//texture = Texture2D::fromFile("ExampleTexturingSEMLightProbeCold.png");		
		texture = Texture2D::fromFile("ExampleTexturingSEMLightProbeWarm.png");
	}
	
	mat4 projectionMatrix = mat4::perspectiveMatrix(60.00, 480.0f/320.0f, 0.1f, 100.0f);
	mat4 modelViewMatrix = mat4::translationMatrix(0, 0, -3)
	* mat4::rotationMatrix(vec3(0,1,0), rotY) //2*Timer::getInstance().getTime()*30
	* mat4::rotationMatrix(vec3(1,0,0), rotX);//1*Timer::getInstance().getTime()*30
	
	shader->bind();
	shader->setUniform("projectionMatrix", projectionMatrix);
	shader->setUniform("modelViewMatrix", modelViewMatrix);
	shader->setUniform("time", Timer::getInstance().getTime());
	shader->setUniform("tex0", 0);	
	
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	
	render(geom, shader);
}

void ExampleTexturing::drawCubeMapping() {
	rotCamY += 30 * Timer::getInstance().getFrameTime();
	
	if (!shader) {
		//shader = Shader::fromFile("ExampleTexturingBasic.glsl");		
		shader = Shader::fromFile("ExampleTexturingCubeMapping.glsl");		
	}
	if (!texture) {		
		texture = TextureCube::fromFile("skyPosX.png");
	}
	if (!sphere) {
		sphere = new Sphere(5, 18, 5);
	}
	
	mat4 projectionMatrix = mat4::perspectiveMatrix(60.00, 480.0f/320.0f, 0.1f, 100.0f);
	
	mat4 modelViewMatrix = mat4::translationMatrix(0, 0, -3)
	* mat4::rotationMatrix(vec3(0,1,0), rotY + rotCamY) //2*Timer::getInstance().getTime()*30
	* mat4::rotationMatrix(vec3(1,0,0), rotX);//1*Timer::getInstance().getTime()*30
	
	mat4 modelWorldMatrix = mat4::rotationMatrix(vec3(0,1,0), rotY) //2*Timer::getInstance().getTime()*30
	* mat4::rotationMatrix(vec3(1,0,0), rotX);//1*Timer::getInstance().getTime()*30		
	
	mat4 sphereModelViewMatrix = mat4::translationMatrix(0, 0, -3) * mat4::rotationMatrix(vec3(0,1,0), rotCamY);	
	
	shader->bind();
	shader->setUniform("projectionMatrix", projectionMatrix);
	shader->setUniform("modelViewMatrix", modelViewMatrix);
	shader->setUniform("modelWorldMatrix", modelWorldMatrix);
	shader->setUniform("tex0", 0);
	shader->setUniform("tex1", 1);
	vec3 camPos(0, 0, 3);
	camPos = sphereModelViewMatrix * camPos;
	shader->setUniform("camPos", camPos);
	shader->setUniform("skybox", 0.0f);
	shader->setUniform("scale", 1.0f);
	
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	glActiveTexture(GL_TEXTURE1);
	texture2->bind();

	
	render(geom, shader);
	
	shader->setUniform("scale", 0.4);
	render(geom, shader);
	
	shader->setUniform("modelViewMatrix", sphereModelViewMatrix);
	shader->setUniform("skybox", 1.0);
	shader->setUniform("scale", 1.0);
	
	render(sphere, shader);	
}	

//------------------------------------------------------------------------------

void ExampleTexturing::onMouseDown(int x, int y, int key) {
	strength = 2.0f;
	
	if (key == 2) {
		mode = (mode + 1) % 3; //numModes
		if (texture) {
			delete texture;
			texture = NULL;
		}
		if (shader) {
			delete shader;
			shader = NULL;
		}
	}
}

//------------------------------------------------------------------------------

void ExampleTexturing::onMouseMove(int x, int y, int key) {
	rotX = 90+360 * y/480.0f;
	rotY = 360 * x/320;
}

//------------------------------------------------------------------------------

void ExampleTexturing::render(Geometry* geom, Shader* shader) {
	VertexStream* vs = &geom->getVertexStream();
	
	for(int i=0; i<shader->attribDeclarations.size(); i++) {
		VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
		VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
		void* buf = attrib->getBuffer();
		glVertexAttribPointer(i, attrib->getSize(), GL_FLOAT, false, 0, buf);
		glEnableVertexAttribArray(i);
	}
	
	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());
	
}
//------------------------------------------------------------------------------


