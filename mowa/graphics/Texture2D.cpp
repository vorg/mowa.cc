/*
 *  Texture2D.cpp
 *  DMA
 *
 *  Created by Marcin Ignac on 12/20/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Texture2D.h"
#include "Utils.h"

namespace flow {

Texture2D::Texture2D() {
	log("Texture2D+");	
}
	
	
Texture2D::~Texture2D() {
	log("Texture2D-");
	if (textureObject > 0) {
		glDeleteTextures(1, &textureObject);
	}
}
	
Texture2D* Texture2D::create(int width, int height) {
	log("Texture2D::create w:%d h:%d", width, height);

	Texture2D* texture2D = new Texture2D();
	
	texture2D->textureTarget = GL_TEXTURE_2D;
	glGenTextures(1, &texture2D->textureObject);
	texture2D->width = width;
	texture2D->height = height;
	
	glBindTexture(texture2D->textureTarget, texture2D->textureObject);
	glTexParameteri(texture2D->textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texture2D->textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	//if (mipmap) {
	//glTexParameteri(texture2D->textureTarget, GL_GENERATE_MIPMAP, GL_TRUE);
	//}	
	glTexImage2D(texture2D->textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	int error = glGetError();
	if (error != GL_NO_ERROR) {
		log("Texture2D::create error");
	}	
	return texture2D;
}

	/*
Texture2D* Texture2D::generateChecker() {
	int width = 256;
	int height = 256;
	unsigned char* pixels = new unsigned char[width * height];
	//* pixels = new int[width * height];
	
	Texture2D* texture2D = Texture2D::create(width, height);
	//glActiveTexture(GL_TEXTURE0);	
	glBindTexture(texture2D->textureTarget, texture2D->textureObject);
	log("texture2D->textureObject %d", texture2D->textureObject);
	
	int c;
	//int r, g, b, rgb;
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			c = (unsigned char)(((x&16)^(y&16))*255);
			//c = (255 << 24) | (255 << 16) | (255 < 8) | (255);
			//r = c << 16;
			//g = c << 0;
			//b = c << 0;
			//rgb = r + g + b;
			pixels[(x + y*width) + 0] = c;
		}
	}
	
	//glTexImage2D(texture2D->textureTarget, 0, GL_RGBA, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
	glTexImage2D(texture2D->textureTarget, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(texture2D->textureTarget);
	glTexParameteri(texture2D->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(texture2D->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	return texture2D;	
}
	 */
	

Texture2D* Texture2D::generateChecker() {
	int width = 256;
	int height = 256;
	unsigned char* pixels = new unsigned char[width * height * 4];
	//* pixels = new int[width * height];
	
	Texture2D* texture2D = Texture2D::create(width, height);
	//glActiveTexture(GL_TEXTURE0);	
	glBindTexture(texture2D->textureTarget, texture2D->textureObject);
	log("texture2D->textureObject %d", texture2D->textureObject);
	
	int c;
	//int r, g, b, rgb;
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			c = (unsigned char)(((x&16)^(y&16))*255);
			//c = (255 << 24) | (255 << 16) | (255 < 8) | (255);
			//r = c << 16;
			//g = c << 0;
			//b = c << 0;
			//rgb = r + g + b;
			pixels[(x + y*width)*4 + 0] = c;
			pixels[(x + y*width)*4 + 1] = c;
			pixels[(x + y*width)*4 + 2] = 255;
			pixels[(x + y*width)*4 + 3] = 255;
		}
	}
	
	//glTexImage2D(texture2D->textureTarget, 0, GL_RGBA, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
	glTexImage2D(texture2D->textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(texture2D->textureTarget);
	glTexParameteri(texture2D->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(texture2D->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	return texture2D;	
}

	
void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, textureObject);
}
	
}


