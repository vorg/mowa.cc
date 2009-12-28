/*
 *  Torus.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/27/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_TORUS_H
#define FLOW_TORUS_H

#include "Geometry.h"

namespace flow {
	
//------------------------------------------------------------------------------

class Torus : public Geometry {
public:	
	Torus(float R, float r, unsigned int nsides, unsigned int nsegments);
	~Torus();
private:			
	void genTorus(float R, float r, unsigned int nsides, unsigned int nsegments);
};

//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_TORUS_H
