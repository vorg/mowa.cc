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
		GLuint width;
		GLuint height;
		
	public:
		virtual ~Texture() {
			if (textureObject > 0) {
				glDeleteTextures(1, &textureObject);
			}
		};
	
		void bind() {
			glBindTexture(textureTarget, textureObject);
		};
	};
	
}

#endif
