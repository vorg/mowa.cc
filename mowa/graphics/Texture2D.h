/*
 *  Texture2D.h
 *  DMA
 *
 *  Created by Marcin Ignac on 12/20/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FLOW_TEXTURE_2D_H
#define FLOW_TEXTURE_2D_H

#include <string>
#include "Texture.h"

namespace flow {

class Texture2D : public Texture {
public: 
	Texture2D();
	~Texture2D();
	static Texture2D* create(int width, int height);
	static Texture2D* fromFile(const char* fileName);
	static Texture2D* generateChecker();
};
	
}

#endif FLOW_TEXTURE_2D_H
