/*
 *  utils.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-06.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "Utils.h"

namespace flow { 
	
//------------------------------------------------------------------------------

void Log::msg(const char *formatStr, ...) {	
	
	va_list params;
	char buf[256];file://localhost/Users/vorg/Workspace/vorg-mowa-cc/mowa/old
	
	va_start ( params, formatStr );
	vsprintf ( buf, formatStr, params );
	
	printf ( "%s\n", buf );
	
	va_end ( params );
}
	
//------------------------------------------------------------------------------
	
void stringExplode(string str, string separator, vector<string>* results) {
	int found;
	found = str.find_first_of(separator);
	while(found != string::npos) {
		if(found > 0){
			results->push_back(str.substr(0,found));
		}
		str = str.substr(found+1);
		found = str.find_first_of(separator);
	}
	if(str.length() > 0) {
		results->push_back(str);
	}
}
	
//------------------------------------------------------------------------------
	
} //namespace flow

