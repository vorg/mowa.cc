/*
 *  DataType.h
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_DATA_TYPE_H
#define FLOW_DATA_TYPE_H

#include <string>

namespace flow {
	
//------------------------------------------------------------------------------

enum DataType {
	TYPE_UNKNOWN	= 0,
	TYPE_NULL		= 0,
	TYPE_BOOLEAN	= 1,		
	TYPE_INT		= 2,
	TYPE_FLOAT		= 3,
	TYPE_VEC2		= 4,
	TYPE_VEC3		= 5,
	TYPE_STRING		= 6		
};
	
//------------------------------------------------------------------------------
	
} //namespace flow

#endif //FLOW_DATA_TYPE_H


