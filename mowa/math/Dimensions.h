/*
 *  Size.h
 *  DMA
 *
 *  Created by vorg on 2009-10-17.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_DIMENSIONS_H
#define FLOW_DIMENSIONS_H

struct Dimensions {
public:
	int width;
	int height;
	
	Dimensions(int w, int h) {
		this->width = w;
		this->height = h;
	}	
};

#endif FLOW_DIMENSIONS_H