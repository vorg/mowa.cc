/*
 *  TextureCube.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/27/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */


#ifndef FLOW_TEXTURE_CUBE_H
#define FLOW_TEXTURE_CUBE_H

#include <string>
#include "Texture.h"

namespace flow {
	
class TextureCube : public Texture {
public: 
	TextureCube();
	~TextureCube();
	static TextureCube* fromFile(const char* fileName);
};
	
}

#endif FLOW_TEXTURE_CUBE_H

