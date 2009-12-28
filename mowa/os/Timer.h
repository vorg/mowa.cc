/*
 *  Timer.h
 *  DMA
 *
 *  Created by vorg on 2009-10-07.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "OS.h"
#include <math.h>

#ifndef FLOW_TIMER_H
#define FLOW_TIMER_H

namespace flow {
	
//------------------------------------------------------------------------------

class Timer {
private:
	float startTime;
	float currTime;
	float fpsStartTime;
	float fpsEndTime;
	int fpsFrameCount;
	int totalFrameCount;
	float fps;
	float prevTime;
	float time;
	float timeShift;
	bool isPaused;
	
	Timer() {
		startTime = 0;
		currTime = 0;
		fpsStartTime = 0;
		fpsEndTime = 0;
		fpsFrameCount = 0;
		totalFrameCount = 0;
		fps = 0;
		prevTime = 0;
		time = 0;
		timeShift = 0;
		isPaused = false;
	}
public:
	static Timer& getInstance() {
		static Timer instance;
		return instance;
	}
	
	void update() {
		if (isPaused) {
			return;
		}		
		if (fpsStartTime == 0) {
			fpsStartTime = osGetTime();
		}
		if (startTime == 0) {
			startTime = osGetTime();
		}
		
		currTime = osGetTime();
		prevTime = time;
		time = (currTime - startTime);
		++totalFrameCount;
		if (++fpsFrameCount >= 33) {
			fpsEndTime = osGetTime();
			fps = 33.0f / (fpsEndTime - fpsStartTime);
			fps = floor(fps*100.0f)/100.0f;
			fpsFrameCount = 0;
			fpsStartTime = osGetTime();
		}		
	}
	
	void reset() {
		startTime = 0;
	}
	
	float getFPS() {
		return fps;
	}
	
	void setTime(float t) {
		timeShift = t - time;
	}
	
	float getTime() {
		return time + timeShift;
	}
	
	float getFrameTime() {
		return time - prevTime;
	}
	
	int getTotalFrameCount() {
		return totalFrameCount;
	}
	
	float getTimeShift() {
		return timeShift;
	}
	
	void setTimeShift(float t) {
		timeShift = t;
	}
	
	void pause() {
		isPaused = true;
	}
	
	void start() {
		isPaused = false;
	}
};
	
//------------------------------------------------------------------------------
	
} //end namespace flow

#endif FLOW_TIMER_H

