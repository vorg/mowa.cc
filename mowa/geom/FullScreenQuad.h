/*
 *  ScreenQuad.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/1/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_FULLSCREEN_QUAD_H
#define FLOW_FULLSCREEN_QUAD_H

#include "Geometry.h"

namespace flow {
	
//------------------------------------------------------------------------------

class FullScreenQuad : public Geometry {
public:	
	FullScreenQuad();
	~FullScreenQuad();
private:			
	void genFullScreenQuad();
};

//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_FULLSCREEN_QUAD_H

