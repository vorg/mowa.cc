/*
 *  ExampleRenderToCubeMap.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "ExampleRenderToCubeMap.h"
#include "Timer.h"
#include "TextureCube.h"

//------------------------------------------------------------------------------

ExampleRenderToCubeMap::ExampleRenderToCubeMap() {
	torusShader = Shader::fromFile("ExampleRenderToCubeMapScene.glsl");
	torusTexture = Texture2D::generateChecker();
	torus = new Torus(1, 0.3, 36, 18);
	reflectionShader = Shader::fromFile("ExampleRenderToCubeMapReflection.glsl");
	
	
	
	//RGBA8 Cubemap texture, 24 bit depth texture, 256x256
	glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, color_tex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, 0x8072, GL_CLAMP_TO_EDGE); //GL_TEXTURE_WRAP_R
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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
			Log::msg("ExampleRenderToCubeMap::ExampleRenderToCubeMap framebuffer ok");
			break;
		default:
			Log::msg("ExampleRenderToCubeMap::ExampleRenderToCubeMap framebuffer failed");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	reflectionTexture = TextureCube::fromFile("");
}

//------------------------------------------------------------------------------

ExampleRenderToCubeMap::~ExampleRenderToCubeMap() {
	//TODO: delete all
}

//------------------------------------------------------------------------------

void ExampleRenderToCubeMap::draw() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);	
	
	mat4 cameraMatrix;
	mat4 projectionMatrix;
	mat4 modelViewMatrix;
	mat4 modelWorldMatrix;
	
	//toruses
	
	vec3 toruses[] = {
		vec3(-3, 0, 0), vec3(1, 1, 1),
		vec3(+3, 0, 0), vec3(0, 1, 0),
		vec3( 0, 0,-3), vec3(0, 0, 1),
		vec3( 0, 0,+3), vec3(1, 1, 0)
	};
	vec3 cameraPositions[] = {
		vec3(0, 0, 0), vec3(0,-1, 0), vec3( 1, 0, 0), //+x
		vec3(0, 0, 0), vec3(0,-1, 0), vec3(-1, 0, 0), //-x
		vec3(0, 0, 0), vec3(0, 0, 1), vec3( 0, 1, 0), //+y
		vec3(0, 0, 0), vec3(0, 0,-1), vec3( 0,-1, 0), //-y
		vec3(0, 0, 0), vec3(0,-1, 0), vec3( 0, 0, 1), //+z
		vec3(0, 0, 0), vec3(0,-1, 0), vec3( 0, 0,-1), //-z
		vec3(0, 2, 3), vec3(0, 1, 0), vec3( 0, 0, 0)
	};
		
	/*
	 GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	 GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	 GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	 GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	 GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	 GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	*/
	
	float time = Timer::getInstance().getTime();
	
	for(int c=0; c<7; c++) {		
		cameraMatrix = mat4::lookAtMatrix(cameraPositions[c*3], cameraPositions[c*3+1], cameraPositions[c*3+2]);		
		if (c < 6) {
			projectionMatrix = mat4::perspectiveMatrix(90.0f, 256.0f/256.0f, 0.1f, 100.0f);
			glBindFramebuffer(GL_FRAMEBUFFER, fb);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + c, color_tex, 0);
			//glClearColor(1.0f, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, 256, 256);			
		}
		else {					
			projectionMatrix = mat4::perspectiveMatrix(60.0f, 480.0f/320.0f, 0.1f, 100.0f);
			glBindFramebuffer(GL_FRAMEBUFFER, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
			glViewport(0, 0, 480, 320);
		}		
		
		for(int i=0; i<4; i++) {	
			modelViewMatrix = cameraMatrix
			* mat4::translationMatrix(toruses[i*2].x, toruses[i*2].y, toruses[i*2].z)
			* mat4::rotationMatrix(vec3(0,1,0), 2*time*30) //2*Timer::getInstance().getTime()*30
			* mat4::rotationMatrix(vec3(1,0,0), i*time*30);
			if (i == 0) {
				modelViewMatrix = cameraMatrix * mat4::translationMatrix(-15, 0, 0) * mat4::rotationMatrix(vec3(1,0,0), 90) * mat4::scaleMatrix(15, 15, 15);
			}
			torusTexture->bind();	
			torusShader->bind();
			torusShader->setUniform("projectionMatrix", projectionMatrix);
			torusShader->setUniform("modelViewMatrix", modelViewMatrix);
			torusShader->setUniform("tex0", 0);	
			torusShader->setUniform("color", toruses[i*2+1]);
			
			render(torus, torusShader);
		}		
		
		if (c == 6) {
			//main torus
			
			cameraMatrix = mat4::lookAtMatrix(vec3(0, 2, 3), vec3(0, 1, 0), vec3(0,0,0));
			modelWorldMatrix = mat4::translationMatrix(0, 0, 0)
			* mat4::rotationMatrix(vec3(0,1,0), 2*Timer::getInstance().getTime()*30) //2*Timer::getInstance().getTime()*30
			* mat4::rotationMatrix(vec3(1,0,0), 1*Timer::getInstance().getTime()*30);//1*Timer::getInstance().getTime()*30
			
			modelViewMatrix = cameraMatrix * modelWorldMatrix;
						
			//torusTexture->bind();	
			glBindTexture(GL_TEXTURE_CUBE_MAP, color_tex);
			//reflectionTexture->bind();
			
			reflectionShader->bind();
			reflectionShader->setUniform("projectionMatrix", projectionMatrix);
			reflectionShader->setUniform("modelViewMatrix", modelViewMatrix);
			reflectionShader->setUniform("modelWorldMatrix", modelWorldMatrix);
			vec3 camPos(0, 2, 3);			
			reflectionShader->setUniform("camPos", camPos);
			reflectionShader->setUniform("tex0", 0);
			
			render(torus, reflectionShader);
		}		
	}
	
}

//------------------------------------------------------------------------------

void ExampleRenderToCubeMap::onMouseMove(int x, int y, int key) {
}

//------------------------------------------------------------------------------

void ExampleRenderToCubeMap::render(Geometry* geom, Shader* shader) {
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

