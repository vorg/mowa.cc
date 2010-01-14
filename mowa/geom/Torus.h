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
	Torus(float R=1, float r=0.3, unsigned int nsides=36, unsigned int nsegments=36);
	~Torus();
private:			
	void genTorus(float R, float r, unsigned int nsides, unsigned int nsegments);
};

//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_TORUS_H
