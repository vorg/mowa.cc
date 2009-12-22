/*
 *  Sphere.h
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_SPHERE_GEN_H
#define FLOW_SPHERE_GEN_H

#include "Geometry.h"

namespace flow {
	
//------------------------------------------------------------------------------
	
class Sphere : public Geometry {
public:
	Sphere();
	Sphere(float r, unsigned int nsides, unsigned int nsegments);
	~Sphere();
	
private:			
	void genSphere(float r, unsigned int nsides, unsigned int nsegments);
};
	
//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_SPHERE_GEN_H

