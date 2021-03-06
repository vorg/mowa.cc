/*
 *  Shader.h
 *  DMA
 *
 *  Created by vorg on 2009-10-07.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_GRAPHICS_SHADER_H
#define FLOW_GRAPHICS_SHADER_H

#include "Graphics.h"
#include "VertexStream.h"
#include "Mat.h"

namespace flow {
	
//------------------------------------------------------------------------------
	
class Shader {
private:
	GLuint programObject;
	GLuint compileShader(GLenum type, const char *shaderSrc);
	GLuint compileProgram(GLuint vertexShaderId, GLuint fragmentShaderId);	
	
public:
	Shader();
	~Shader();
	
	bool load(const char*);
	void bind();
	void unbind();
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float value);
	void setUniform(const char* name, double value);
	void setUniform(const char* name, vec3& value);
	void setUniform(const char* name, vec4& value);	
	void setUniform(const char* name, mat4& value);
	
	static Shader* fromFile(const char* fileName);
	std::vector<VertexAttribDeclaration*> attribDeclarations;
};
	
//------------------------------------------------------------------------------
	
}

#endif

