/*
 *  ExampleLighting.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/3/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#include "ExampleLighting.h"
#include "timer.h"


//------------------------------------------------------------------------------

ExampleLighting::ExampleLighting() {
	cube = new Cube(15, 10, 15);
	cube->invertNormals();
	torus = new Torus(2, 0.6);	
	lightShader = NULL;
		
	ball = new Sphere(0.3, 6, 6);
	ballShader = Shader::fromFile("ExampleLightingSolidColor.glsl");
	ballColor = vec3(1, 0, 0);
	
	cameraPos = vec3(5, 3, 5);
	lightPos = vec3(5, 4, 5);
}

//------------------------------------------------------------------------------

ExampleLighting::~ExampleLighting() {
	delete cube;
	delete torus;
	delete lightShader;
	
	delete ball;
	delete ballShader;
}

//------------------------------------------------------------------------------

void ExampleLighting::draw() {
	drawPointLight2();
}

//------------------------------------------------------------------------------

void ExampleLighting::drawPointLight() {
	if (!lightShader) {
		lightShader = Shader::fromFile("ExampleLightingPointLight.glsl");
	}
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);	
	
	float time = Timer::getInstance().getTime();
	lightPos.x = 0;
	lightPos.y = 0;
	lightPos.z = 7*sin(time);
	
	mat4 projectionMatrix = mat4::perspectiveMatrix(60, 480.0f/320.0f, 0.1, 100.0);
	mat4 viewMatrix = mat4::lookAtMatrix(cameraPos, vec3(0,1,0), vec3(0,0,0));
	mat4 modelWorldMatrix = mat4::translationMatrix(0, 0, 0);
	mat4 modelViewMatrix = viewMatrix * modelWorldMatrix;	
	lightShader->bind();
	lightShader->setUniform("projectionMatrix", projectionMatrix);
	lightShader->setUniform("modelViewMatrix", modelViewMatrix);
	lightShader->setUniform("modelWorldMatrix", modelWorldMatrix);
	lightShader->setUniform("lightPos", lightPos);
	render(cube, lightShader);
	render(torus, lightShader);
	
	mat4 ballModelViewMatrix = viewMatrix * mat4::translationMatrix(lightPos.x, lightPos.y, lightPos.z);	
	ballShader->bind();
	ballShader->setUniform("projectionMatrix", projectionMatrix);
	ballShader->setUniform("modelViewMatrix", ballModelViewMatrix);
	ballShader->setUniform("color", ballColor);
	render(ball, ballShader);
}

//------------------------------------------------------------------------------

void ExampleLighting::drawPointLight2() {
	if (!lightShader) {
		lightShader = Shader::fromFile("ExampleLightingPointLight2.glsl");
		//lightShader = Shader::fromFile("ExampleLighingPointLightEyeSpace.glsl");		
	}
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);	
	
	float time = Timer::getInstance().getTime();
	lightPos.x = 0;
	lightPos.y = 0;
	lightPos.z = 7*sin(time);
	
	cameraPos.x = 7*cos(time*0.5);	
	cameraPos.z = 7*sin(time*0.5);
	
	vec4 ambientColor = vec4(0.0, 0.0, 0.0, 0.0);//vec4(0.4, 0.4, 0.4, 1.0);
	vec4 diffuseColor = vec4(0.99, 0.2, 0.1, 1.0);
	vec4 diffuseColor2 = vec4(0.1, 0.2, 0.99, 1.0);
	vec4 specularColor = vec4(0.8, 0.8, 0.8, 1.0);	
	mat4 projectionMatrix = mat4::perspectiveMatrix(60, 480.0f/320.0f, 0.1, 100.0);
	mat4 viewMatrix = mat4::lookAtMatrix(cameraPos, vec3(0,1,0), vec3(0,0,0));
	mat4 modelWorldMatrix = mat4::translationMatrix(0, 0, 0);
	mat4 modelViewMatrix = viewMatrix * modelWorldMatrix;	
	lightShader->bind();
	lightShader->setUniform("projectionMatrix", projectionMatrix);
	lightShader->setUniform("modelViewMatrix", modelViewMatrix);
	lightShader->setUniform("modelWorldMatrix", modelWorldMatrix);
	vec3 ecLightPos = viewMatrix * lightPos;
	lightShader->setUniform("ecLightPos", ecLightPos);
	lightShader->setUniform("lightPos", lightPos);
	vec3 lightPos2 = vec3(lightPos.x/2, lightPos.y, lightPos.x);
	lightShader->setUniform("lightPos2", lightPos2);
	lightShader->setUniform("ambientColor", ambientColor);
	lightShader->setUniform("diffuseColor", diffuseColor);
	lightShader->setUniform("diffuseColor2", diffuseColor2);
	lightShader->setUniform("specularColor", specularColor);
	lightShader->setUniform("cameraPos", cameraPos);
	render(cube, lightShader);
	render(torus, lightShader);
	
	mat4 ballModelViewMatrix = viewMatrix * mat4::translationMatrix(lightPos.x, lightPos.y, lightPos.z);	
	ballShader->bind();
	ballShader->setUniform("projectionMatrix", projectionMatrix);
	ballShader->setUniform("modelViewMatrix", ballModelViewMatrix);
	ballShader->setUniform("color", ballColor);
	render(ball, ballShader);
}

//------------------------------------------------------------------------------

void ExampleLighting::onMouseDown(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void ExampleLighting::onMouseMove(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void ExampleLighting::onMouseUp(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void ExampleLighting::render(Geometry* geom, Shader* shader) {
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






