/*
 *  Plane.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_PLANE_H
#define FLOW_PLANE_H

#include "Geometry.h"

namespace flow {
	
//------------------------------------------------------------------------------

class Plane : public Geometry {
public:	
	static const int X = 0;
	static const int Y = 1;
	static const int Z = 2;
	Plane(float s1=1, float s2=1, int axis=0, int n1=1, int n2=1);
	~Plane();
private:			
	void genPlane(float size1, float size2, int axis, int n1, int n2);
};

//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_PLANE_H

