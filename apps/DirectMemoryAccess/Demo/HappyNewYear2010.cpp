/*
 *  HappyNewYear2010.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "HappyNewYear2010.h"
#include "Timer.h"
#include "TextureCube.h"
#include "Plane.h"
#include "Cube.h"
#include "FullScreenQuad.h"

//------------------------------------------------------------------------------

HappyNewYear2010::HappyNewYear2010() {
	//bgShader = Shader::fromFile("HappyNewYear2010Bg.glsl");
	bgShader = Shader::fromFile("ExampleTexturingBasic.glsl");
	torusShader = Shader::fromFile("HappyNewYear2010Scene.glsl");
	torusTexture = Texture2D::generateChecker(); //Texture2D::fromFile("rainbow.png");
	//bgTexture = TextureCube::fromFile("");
	bgTexture = Texture2D::fromFile("ExampleTexturingSEMLightProbeWarm.png");
	torus = new Torus(1.0, 0.1, 18, 18);
	reflectionShader = Shader::fromFile("HappyNewYear2010Reflection.glsl");
	
	cube = new Cube(10, 10, 10, 1, 1, 1, true);
	
	quad = new FullScreenQuad();
	overlayShader = Shader::fromFile("FullScreenQuad.glsl");
	overlayTex = Texture2D::fromFile("overlay.png");
	
	//mainObject = new Torus(1, 0.6, 18, 18);
	//mainObject = new Sphere(1, 36, 36);
	//mainObject = new Plane(2, 2, Plane::X, 1, 1);	
	mainObject = new Cube(1,1,1);//2,4,2, 1, 1, 1, true
	
	reflectionTexture = TextureCube::fromFile("");
	
	rotY = 0;
	rotYVel = 0;
	posY = 2;
	posYVel = 0;
	
	glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, color_tex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+0, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+1, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+2, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+3, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+4, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+5, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	
	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, color_tex, 0);
	
	glGenRenderbuffers(1, &depth_rb);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 256, 256);	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rb);
	
	GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE:
			//Log::msg("HappyNewYear2010::HappyNewYear2010 framebuffer ok");
			break;
		default:
			Log::msg("HappyNewYear2010::HappyNewYear2010 framebuffer failed");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//------------------------------------------------------------------------------

HappyNewYear2010::~HappyNewYear2010() {
	//TODO: delete all
}

//------------------------------------------------------------------------------

void HappyNewYear2010::draw() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);	
	
	mat4 cameraMatrix;
	mat4 projectionMatrix;
	mat4 modelViewMatrix;
	mat4 modelWorldMatrix;
	
	float time = Timer::getInstance().getTime();
	//time = 0;
	
	rotY += rotYVel;
	posY += posYVel;
	
	//toruses
	
	vec3 toruses[] = {
		vec3( 0, 0, 0), vec3(1, 0, 0),
		vec3(+3, 3,+3), vec3(0, 1, 0),
		vec3(+3, 0, 0), vec3(0, 1, 1),
		vec3( 0, 0,-3), vec3(0, 0, 1),
		vec3( 0, 0,+3), vec3(1, 1, 0),
		vec3( 0, 3, 1), vec3(0, 0.7, 1),
		vec3( 1,-3, 0), vec3(1, 0.4, 0)
	};
	vec3 cameraPositions[] = {
		vec3(0, 0, 0), vec3(0,-1, 0), vec3( 1, 0, 0), //+x
		vec3(0, 0, 0), vec3(0,-1, 0), vec3(-1, 0, 0), //-x
		vec3(0, 0, 0), vec3(0, 0, 1), vec3( 0, 1, 0), //+y
		vec3(0, 0, 0), vec3(0, 0,-1), vec3( 0,-1, 0), //-y
		vec3(0, 0, 0), vec3(0,-1, 0), vec3( 0, 0, 1), //+z
		vec3(0, 0, 0), vec3(0,-1, 0), vec3( 0, 0,-1), //-z
		vec3(0, 0, 3), vec3(0, 1, 0), vec3( 0, 0, 0)
	};
		
	//cameraPositions[18] = vec3(3*cos(rotY), posY, 3*sin(rotY));
	float r = 1.5;//*sin(time)+1.6;
	cameraPositions[18] = vec3(r*cos(time), 2+0*2*sin(time), r*sin(time));
	
	int debug = -1;
	
	for(int c=0; c<7; c++) {				
		if (debug != -1 && debug != c) {
			continue;
		}
		cameraMatrix = mat4::lookAtMatrix(cameraPositions[c*3], cameraPositions[c*3+1], cameraPositions[c*3+2]);			
		
		if (c < 6) {
			projectionMatrix = mat4::perspectiveMatrix(90.0f, 256.0f/256.0f, 0.1f, 100.0f);
			if (debug == -1) {
				glViewport(0, 0, 256, 256);
				glBindFramebuffer(GL_FRAMEBUFFER, fb);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + c, color_tex, 0);			
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}
		else {		
			glViewport(0, 0, 480, 320);			
			projectionMatrix = mat4::perspectiveMatrix(60.0f, 480.0f/320.0f, 0.1f, 100.0f);			
			glBindFramebuffer(GL_FRAMEBUFFER, 1);
		}		
		
		for(int i=0; i<7; i++) {	
			//if (i == 3 && c == 6) {
			//	continue;
			//}
			modelViewMatrix = cameraMatrix
			* mat4::translationMatrix(toruses[i*2].x, toruses[i*2].y, toruses[i*2].z)
			* mat4::rotationMatrix(vec3(0,1,0), 2*time*30) //2*Timer::getInstance().getTime()*30
			* mat4::rotationMatrix(vec3(1,0,0), i*time*30);
			if (i == 0) {
				modelViewMatrix = cameraMatrix * mat4::translationMatrix(0, 0*2*sin(-1+time), 0) * mat4::rotationMatrix(vec3(1,0,0), 90+30*time) * mat4::scaleMatrix(2.5, 2.5, 2.5);
			}
			else if (i == 1) {
				//modelViewMatrix = cameraMatrix * mat4::translationMatrix(-25, 0, 0) * mat4::rotationMatrix(vec3(1,0,0), 90) * mat4::scaleMatrix(25, 25, 25);
			}
			torusTexture->bind();	
			torusShader->bind();
			torusShader->setUniform("projectionMatrix", projectionMatrix);
			torusShader->setUniform("modelViewMatrix", modelViewMatrix);
			torusShader->setUniform("tex0", 0);	
			torusShader->setUniform("time", time);	
			torusShader->setUniform("color", toruses[i*2+1]);
			
			render(torus, torusShader);
		}	
		
		bgTexture->bind();
		modelViewMatrix = cameraMatrix
		* mat4::translationMatrix(0, 0, 0)
		* mat4::rotationMatrix(vec3(0,1,0), 0) //2*Timer::getInstance().getTime()*30
		* mat4::rotationMatrix(vec3(1,0,0), 0);
		bgShader->bind();	
		bgShader->bind();
		bgShader->setUniform("projectionMatrix", projectionMatrix);
		bgShader->setUniform("modelViewMatrix", modelViewMatrix);
		bgShader->setUniform("tex0", 0);	
		bgShader->setUniform("time", time);	
		vec3 cubeColor(1,1,1);
		bgShader->setUniform("color", cubeColor);
		
		render(cube, bgShader);
		
		if (c == 6) {
			//main torus
						
			for(int x=0; x<3; x++) {
				for(int z=0; z<3; z++) {
					modelWorldMatrix = mat4::translationMatrix(3*0.5-x*1.5, 0, 3*0.5-z*1.5)
					* mat4::rotationMatrix(vec3(0,1,0), 0) //2*Timer::getInstance().getTime()*30
					* mat4::rotationMatrix(vec3(1,0,0), 0);//1*Timer::getInstance().getTime()*30
					
					modelViewMatrix = cameraMatrix * modelWorldMatrix;
					
					//torusTexture->bind();	
					glBindTexture(GL_TEXTURE_CUBE_MAP, color_tex);
					//reflectionTexture->bind();
					
					reflectionShader->bind();
					reflectionShader->setUniform("projectionMatrix", projectionMatrix);
					reflectionShader->setUniform("modelViewMatrix", modelViewMatrix);
					reflectionShader->setUniform("modelWorldMatrix", modelWorldMatrix);
					vec3 camPos(cameraPositions[18].x, cameraPositions[18].y, cameraPositions[18].z);			
					reflectionShader->setUniform("camPos", camPos);
					reflectionShader->setUniform("tex0", 0);
					
					render(mainObject, reflectionShader);
				}
			}
			
			glDisable(GL_DEPTH_TEST);
			overlayShader->bind();
			overlayShader->setUniform("tex0", 0);
			overlayTex->bind();
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			render(quad, overlayShader);
			glDisable(GL_BLEND);			
		}	
		if (debug >= 0) {
			break;
		}		
	}	
}

//------------------------------------------------------------------------------

void HappyNewYear2010::onMouseMove(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void HappyNewYear2010::onMouseDown(int x, int y, int key) {
	if (x < 50) {
		rotYVel = 0.1;
	}
	else if (x > 480 - 50) {
		rotYVel = -0.1;
	}	
	else {
		if (y < 50) {
			posYVel =  0.1;
		}
		if (y > 320 - 50) {
			posYVel =  -0.1;
		}
	}
}

//------------------------------------------------------------------------------

void HappyNewYear2010::onMouseUp(int x, int y, int key) {
	rotYVel = 0;
	posYVel = 0;
}

//------------------------------------------------------------------------------

void HappyNewYear2010::render(Geometry* geom, Shader* shader) {
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



