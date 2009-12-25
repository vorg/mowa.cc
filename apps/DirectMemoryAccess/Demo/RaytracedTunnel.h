/*
 *  RaytracedTunnel.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/23/09.
 *  Copyright 2009 vorg. All rights reserved.
 *
 */

#ifndef RAYTRACED_TUNNEL_H
#define RAYTRACED_TUNNEL_H

#include "Effect.h"
#include "Utils.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace flow;

class RaytracedTunnel : public Effect {
private:
	Shader* shader;
	Texture2D* texture;
	
public:
	RaytracedTunnel();
	~RaytracedTunnel();
	
	void draw();		
};

#endif RAYTRACED_TUNNEL_H

