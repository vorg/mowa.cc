/*
 *  Adalaj.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/13/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#include "Adalaj.h"
#include "Cube.h"
#include "Timer.h"


//------------------------------------------------------------------------------

Adalaj::Adalaj() {
	cube = new Cube(1,1,1);
	shader = Shader::fromFile("AdalajStone.glsl");	
	tex0 = Texture2D::fromFile("rabbit.png");
	//tex0 = Texture2D::fromFile("metal.jpg");
}

//------------------------------------------------------------------------------

Adalaj::~Adalaj() {
	delete cube;
	delete shader;
	delete tex0;
}

//------------------------------------------------------------------------------
int timesPerFrame = 0;
void Adalaj::draw() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);	
	
	float time = Timer::getInstance().getTime();
	mat4 projectionMatrix = mat4::perspectiveMatrix(60.00, 480.0f/320.0f, 0.1f, 100.0f);
	mat4 modelViewMatrix = mat4::translationMatrix(0, 0, -3)
	* mat4::rotationMatrix(vec3(0,1,0), 2*time*30)
	* mat4::rotationMatrix(vec3(1,0,0), 0);
	
	shader->bind();
	shader->setUniform("projectionMatrix", projectionMatrix);
	shader->setUniform("modelViewMatrix", modelViewMatrix);
	shader->setUniform("time", time*1.5);
	shader->setUniform("tex0", 0);
	
	tex0->bind();
	
	float dx = 5;
	float dz = 4;
	float dy = 3;	
	float nx = 4;	
	float nz = 12;
	//mat4 cameraMatrix = mat4::lookAtMatrix(vec3(0, 0, -time*2), vec3(sin(time/4.0),cos(time/4.0),0), vec3(0, 0, -time*2-100));
	mat4 cameraMatrix = mat4::lookAtMatrix(vec3(0, 0, -time*2), vec3(0,1,0), vec3(0, 0, -time*2-100));

	timesPerFrame = 0;
	
	//firstTime = 1;
	for(float x=-dx/2*1.5*nx/2; x<=dx/2*1.5*nx/2; x+=dx) {
		for(float z=0; z>-nz*dz; z-=dz) {
			if (z > -time*2) {
				//continue;
			}
			modelViewMatrix = cameraMatrix * mat4::translationMatrix(x, -dy/2, z);
			modelViewMatrix *= mat4::scaleMatrix(0.8, 1, 0.8);
			shader->setUniform("modelViewMatrix", modelViewMatrix);
			render(cube, shader);
			
			if (x >= -dx/2*1.5 && x <= dx/2*1.5) {
				modelViewMatrix = cameraMatrix * mat4::translationMatrix(x, -dy/2-0.25, z);
				modelViewMatrix *= mat4::scaleMatrix(0.5, 0.5, 2.0);
				shader->setUniform("modelViewMatrix", modelViewMatrix);
				render(cube, shader);
				
				
				modelViewMatrix = cameraMatrix * mat4::translationMatrix(x, -dy/2-0.25, z);
				modelViewMatrix *= mat4::scaleMatrix(2.0, 0.5, 0.5);
				shader->setUniform("modelViewMatrix", modelViewMatrix);
				render(cube, shader);
			}
			
			modelViewMatrix = cameraMatrix * mat4::translationMatrix(x,  dy/2, z);
			modelViewMatrix *= mat4::scaleMatrix(0.8, 1, 0.8);
			shader->setUniform("modelViewMatrix", modelViewMatrix);
			render(cube, shader);
			
			if (x >= -dx/2*1.5 && x <= dx/2*1.5) {
				modelViewMatrix = cameraMatrix * mat4::translationMatrix(x, dy/2+0.25, z);
				modelViewMatrix *= mat4::scaleMatrix(0.5, 0.5, 1.6												 );
				shader->setUniform("modelViewMatrix", modelViewMatrix);
				render(cube, shader);
				
				modelViewMatrix = cameraMatrix * mat4::translationMatrix(x, dy/2+0.25, z);
				modelViewMatrix *= mat4::scaleMatrix(1.6, 0.5, 0.5);
				shader->setUniform("modelViewMatrix", modelViewMatrix);
				render(cube, shader);
			}
			
			modelViewMatrix = cameraMatrix * mat4::translationMatrix(x, 0, z);
			modelViewMatrix *= mat4::scaleMatrix(0.6, 3, 0.6);
			shader->setUniform("modelViewMatrix", modelViewMatrix);
			render(cube, shader);
			
			
		}
	}
	
	modelViewMatrix = cameraMatrix * mat4::translationMatrix(0, -dy/2 - 0.8, -nz*dz/2);
	modelViewMatrix *= mat4::scaleMatrix(dx*nx, 0.4, nz*dz);
	shader->setUniform("modelViewMatrix", modelViewMatrix);
	render(cube, shader);
	
	modelViewMatrix = cameraMatrix * mat4::translationMatrix(0, dy/2 + 0.8, -nz*dz/2);
	modelViewMatrix *= mat4::scaleMatrix(dx*nx, 0.4, nz*dz);
	shader->setUniform("modelViewMatrix", modelViewMatrix);
	render(cube, shader);	
}

//------------------------------------------------------------------------------

void Adalaj::onMouseDown(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void Adalaj::onMouseMove(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void Adalaj::onMouseUp(int x, int y, int key) {
}

//------------------------------------------------------------------------------

int whichTime = 0;
GLuint vertexBuffers[3]; //GLuint
GLuint indexBuffer;

void Adalaj::render(Geometry* geom, Shader* shader) {
	geom->render(shader);
	return;
	
	/**/
	VertexStream* vs = &geom->getVertexStream();	
	if (whichTime == 0) {
		whichTime = 1;
		
		for(int i=0; i<shader->attribDeclarations.size(); i++) {
			VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
			VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
			void* buf = attrib->getBuffer();
			glGenBuffers(1, &vertexBuffers[i]);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i]);
			int size = attrib->getNumVertices() * attrib->getSize() * attrib->getStride();
			glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);			
		}
		
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		int size = vs->getNumIndices() * sizeof(unsigned short);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vs->getIndices(), GL_STATIC_DRAW);
	}
	else if (whichTime >= 1) {	
		//return;
		whichTime = 2;
		
		for(int i=0; i<shader->attribDeclarations.size(); i++) {
			VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
			VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i]);
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attrib->getSize(), GL_FLOAT, false, 0, 0);
		}
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, 0);
	}
	else {
		glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, 0);
	}
	/**/
	
	
	/**
	VertexStream* vs = &geom->getVertexStream();
		
	for(int i=0; i<shader->attribDeclarations.size(); i++) {
		VertexAttribDeclaration* attribDeclaration = shader->attribDeclarations[i];
		VertexAttrib* attrib = vs->getAttrib(attribDeclaration->name, attribDeclaration->dataType);
		void* buf = attrib->getBuffer();
		glVertexAttribPointer(i, attrib->getSize(), GL_FLOAT, false, 0, buf);
		glEnableVertexAttribArray(i);
	}
	
	glDrawElements(GL_TRIANGLES, vs->getNumIndices(), GL_UNSIGNED_SHORT, vs->getIndices());	
	/**/
}

//------------------------------------------------------------------------------

