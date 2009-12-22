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

namespace flow { 
	
//------------------------------------------------------------------------------

void log(const char *formatStr, ...);
void stringExplode(string str, string separator, vector<string>* results);
	
//------------------------------------------------------------------------------

} //end namespace flow