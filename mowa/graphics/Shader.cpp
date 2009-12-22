/*
 *  Shader.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-07.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "Shader.h"

#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace flow {
	
//------------------------------------------------------------------------------

bool Shader::load(const char* code) {
	log("Shader::load");
	string codeStr(code);
	vector<string> lines;
	stringExplode(codeStr, "\n", &lines);
	
	string vertexShaderCode;
	string fragmentShaderCode;
	string* currentShaderCode;

	for (int i=0; i<lines.size(); i++) {
		if (lines[i].compare("//[VERT]") == 0) {			
			currentShaderCode = &vertexShaderCode;
		}
		else if (lines[i].compare("//[FRAG]") == 0) {
			currentShaderCode = &fragmentShaderCode;
		}
		else {
			*currentShaderCode += lines[i] + "\n";
		}		
	}
	
	GLuint vertShaderObject = compileShader(GL_VERTEX_SHADER, vertexShaderCode.c_str());
	//cout << vertexShaderCode;
	GLuint fragShaderObject = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str());
	//cout << fragmentShaderCode;		
	programObject = compileProgram(vertShaderObject, fragShaderObject);
	return true;
}

//------------------------------------------------------------------------------
	
GLuint Shader::compileShader(GLenum type, const char *shaderSrc) {
	GLuint shader = glCreateShader(type);
	
	if(shader == 0) {
		return GL_FALSE;
	}
	
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);
	
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled ) {
		cout << "error" << "\n";
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		
		if(infoLen > 1 ) {
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf(infoLog);
			cout << "\n";
			free(infoLog);
		}
		
		glDeleteShader(shader);
		return GL_FALSE;
	}
	
	return shader;	
}

//------------------------------------------------------------------------------
	
GLuint Shader::compileProgram(GLuint vertexShaderObject, GLuint fragmentShaderObject) {
	GLuint programObject = glCreateProgram();
	
	if (programObject == 0) {		
		return GL_FALSE;
	}
	
	glAttachShader(programObject, vertexShaderObject);
	glAttachShader(programObject, fragmentShaderObject);							  
	glBindAttribLocation(programObject, 0, "position");
	//glBindAttribLocation(programObject, 1, "color");
	glBindAttribLocation(programObject, 1, "normal");
	glBindAttribLocation(programObject, 2, "texCoord0");	
	glLinkProgram(programObject);
	
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	
	if(!linked) {
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1) {
			char* infoLog = (char*)malloc (sizeof(char) * infoLen);
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			printf(infoLog);
			cout << "\n";
			free(infoLog);
		}
		
		glDeleteProgram(programObject);
		return GL_FALSE;
	}
	
	return programObject;
}
	
//------------------------------------------------------------------------------

void Shader::bind() {
	glUseProgram(programObject);
}
	
//------------------------------------------------------------------------------
	
void Shader::unbind() {
	glUseProgram(0);
}
	
//------------------------------------------------------------------------------

void Shader::setUniform(const char* name, float value) {
	int location = glGetUniformLocation(programObject, name);
	glUniform1f(location, value);
}
	
//------------------------------------------------------------------------------
	
void Shader::setUniform(const char* name, mat4& value) {
	int location = glGetUniformLocation(programObject, name);
	glUniformMatrix4fv(location, 1, 0, &(value[0][0]));
}
	
//------------------------------------------------------------------------------
	
}



