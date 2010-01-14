/*
 *  Shader.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-07.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "Shader.h"
#include "OS.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;


namespace flow {

//------------------------------------------------------------------------------
	
Shader::Shader() {	
	//Log::msg("Shader+");
	programObject = 0;
}

//------------------------------------------------------------------------------

Shader::~Shader() {	
	//Log::msg("Shader-");	
	if (programObject) {
		glDeleteProgram(programObject);
	}	
	while(!attribDeclarations.empty()) {
		delete attribDeclarations.back();
		attribDeclarations.pop_back();
	}
}
	
//------------------------------------------------------------------------------

bool Shader::load(const char* code) {
	//Log::msg("Shader::load");
	string codeStr(code);
	vector<string> lines;
	stringExplode(codeStr, "\n", &lines);
	
	string vertexShaderCode;
	string fragmentShaderCode;
	fragmentShaderCode += "precision highp float;\n";
	fragmentShaderCode += "precision highp int;\n";
	string* currentShaderCode = NULL;

	for (int i=0; i<lines.size(); i++) {
		if (lines[i].compare("//[VERT]") == 0) {			
			currentShaderCode = &vertexShaderCode;
		}
		else if (lines[i].compare("//[FRAG]") == 0) {
			currentShaderCode = &fragmentShaderCode;
		}
		else if (currentShaderCode != NULL){
			*currentShaderCode += lines[i] + "\n";
			//searching for attribs defined in source
			if (lines[i].find("attribute") != string::npos) {
				size_t secondSpace = lines[i].find(" ", 10); //10 is length of "attribute"+1
				string attrType = lines[i].substr(10, secondSpace-10);
				string attrName = lines[i].substr(secondSpace+1, lines[i].length() - secondSpace - 2);
								
				if (attrType == "vec3") {
					attribDeclarations.push_back(new VertexAttribDeclaration(attrName, TYPE_VEC3));
				}
				else if (attrType == "vec2") {
					attribDeclarations.push_back(new VertexAttribDeclaration(attrName, TYPE_VEC2));
				}
				else {
					Log::error("Shader::load Unsupported attrib type:%s name:%s", attrType.c_str(), attrName.c_str());
					return false;
				}
			}			
		}		
	}
	
	GLuint vertShaderObject = compileShader(GL_VERTEX_SHADER, vertexShaderCode.c_str());
	//cout << vertexShaderCode;
	GLuint fragShaderObject = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str());
	//cout << fragmentShaderCode;		
	programObject = compileProgram(vertShaderObject, fragShaderObject);
	return vertShaderObject && fragShaderObject;
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
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		
		if(infoLen > 1 ) {
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("%s", infoLog);
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
	for(int i=0; i<attribDeclarations.size(); i++) {
		glBindAttribLocation(programObject, i, attribDeclarations[i]->name.c_str());
	}
	//glBindAttribLocation(programObject, 0, "position");
	//glBindAttribLocation(programObject, 1, "color");
	//glBindAttribLocation(programObject, 1, "normal");
	//glBindAttribLocation(programObject, 2, "texCoord0");	
	glLinkProgram(programObject);
	
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	
	if(!linked) {
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1) {
			char* infoLog = (char*)malloc (sizeof(char) * infoLen);
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			printf("%s", infoLog);
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

void Shader::setUniform(const char* name, int value) {
	int location = glGetUniformLocation(programObject, name);
	glUniform1i(location, value);
}

//------------------------------------------------------------------------------

void Shader::setUniform(const char* name, float value) {
	int location = glGetUniformLocation(programObject, name);
	glUniform1f(location, value);
}
	
//------------------------------------------------------------------------------

void Shader::setUniform(const char* name, double value) {
	int location = glGetUniformLocation(programObject, name);
	glUniform1f(location, (float)value);
}
	
//------------------------------------------------------------------------------
	
void Shader::setUniform(const char* name, vec3& value) {
	int location = glGetUniformLocation(programObject, name);
	glUniform3fv(location, 1, &(value[0]));
}
	
//------------------------------------------------------------------------------

void Shader::setUniform(const char* name, vec4& value) {
	int location = glGetUniformLocation(programObject, name);
	glUniform4fv(location, 1, &(value[0]));
}
		
//------------------------------------------------------------------------------

void Shader::setUniform(const char* name, mat4& value) {
	int location = glGetUniformLocation(programObject, name);
	glUniformMatrix4fv(location, 1, 0, &(value[0][0]));
}
	
//------------------------------------------------------------------------------
	
Shader* Shader::fromFile(const char* fileName) {
	const char* shaderCode = osLoadTextFile(fileName);
	if (shaderCode) {
		Shader* shader = new Shader();
		if (!shader->load(shaderCode)) {
			Log::error("Shader::fromFile invalid code in '%s'", fileName);
		}
		return shader;
	}
	else {
		Log::error("Shader::fromFile failed to load '%s'", fileName);
		return NULL;
	}
}
	
//------------------------------------------------------------------------------
	
}



