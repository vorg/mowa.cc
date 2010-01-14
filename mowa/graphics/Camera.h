/*
 *  Camera.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/30/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#ifndef FLOW_CAMERA_H
#define FLOW_CAMERA_H

#include "MathLib.h"

namespace flow {

class Camera {
public:
	vec3 pos;
	vec3 target;
	vec3 up;
};

}

#endif FLOW_CAMERA_H

