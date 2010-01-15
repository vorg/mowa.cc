/*
 *  Texture.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/27/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_TEXTURE_H
#define FLOW_TEXTURE_H

#include <string>
#include "Graphics.h"

namespace flow {
	
class Texture {
protected:
	GLuint textureObject; 
	GLuint textureTarget;
	unsigned int width;
	unsigned int height;
	unsigned int bpp;
	unsigned char* pixels;
	
public:
	Texture() : width(0), height(0), bpp(0), pixels(NULL) {
	}
	
	virtual ~Texture() {
		if (textureObject > 0) {
			glDeleteTextures(1, &textureObject);
		}
		if (pixels != NULL) {
			free(pixels);
		}
	}

	unsigned char* getPixels() { return pixels; }
	unsigned int getWidth() { return width; }
	unsigned int getHeight() { return height; }
	unsigned int getBpp() { return bpp; }	

	void bind() {
		glBindTexture(textureTarget, textureObject);
	}
};	
}

#endif
