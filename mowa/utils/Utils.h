/*
 *  utils.h
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include <string>
#include <vector>
using namespace std;

#ifndef FLOW_UTILS_H
#define FLOW_UTILS_H

namespace flow { 	

//------------------------------------------------------------------------------

class Log {
public:
	static void msg(const char *formatStr, ...);
};
	
//------------------------------------------------------------------------------

void stringExplode(string str, string separator, vector<string>* results);
	
//------------------------------------------------------------------------------

} //end namespace flow

#endif //FLOW_UTILS_H