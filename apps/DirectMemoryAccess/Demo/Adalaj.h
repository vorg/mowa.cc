/*
 *  Adalaj.h
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 1/13/10.
 *  Copyright 2010 marcinignac.com. All rights reserved.
 *
 */

#ifndef ADALAJ_H
#define ADALAJ_H

#include "Effect.h"
#include "Geometry.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace flow;

class Adalaj : public Effect {
private:
	Shader* shader;
	Geometry* cube;
	Texture2D* tex0;
	
public:
	Adalaj();
	~Adalaj();
	
	void draw();		
	void onMouseDown(int x, int y, int key);	
	void onMouseMove(int x, int y, int key);
	void onMouseUp(int x, int y, int key);	
	void render(Geometry* geom, Shader* shader);
};	

#endif ADALAJ_H


