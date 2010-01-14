/*
 *  Cube.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/31/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_CUBE_H
#define FLOW_CUBE_H

#include "Geometry.h"

namespace flow {
	
//------------------------------------------------------------------------------

class Cube : public Geometry {
public:	
	static const int X = 0;
	static const int Y = 1;
	static const int Z = 2;
	Cube(float sx=1, float sy=1, float sz=1, int nx=1, int ny=1, int nz=1, bool smoothNormals=false);
	~Cube();
private:			
	void genCube(float sx, float sy, float sz, int nx, int ny, int nz, bool smoothNormals);
};

//------------------------------------------------------------------------------
	
} //namespace flow

#endif FLOW_CUBE_H