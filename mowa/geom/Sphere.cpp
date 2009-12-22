/*
 *  Sphere.cpp
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#include "Sphere.h"
#include "MathLib.h"
#include "Utils.h"

namespace flow {
	
//------------------------------------------------------------------------------
	
Sphere::Sphere() {	
	log("Sphere::Sphere default r:1 nsides:32 nsegments:32");
	vertexStream.addAttrib("position", TYPE_VEC3);
	vertexStream.addAttrib("normal", TYPE_VEC3);
	vertexStream.addAttrib("texCoord0", TYPE_VEC2);	
	genSphere(1, 32, 32);
}
	
//------------------------------------------------------------------------------
	
Sphere::Sphere(float r, unsigned int nsides, unsigned int nsegments) {	
	log("Sphere::Sphere r:%f nsides:%d nsegments:%d", r, nsides, nsegments);
	vertexStream.addAttrib("position", TYPE_VEC3);
	vertexStream.addAttrib("normal", TYPE_VEC3);
	vertexStream.addAttrib("texCoord0", TYPE_VEC2);
	
	genSphere(r, nsides, nsegments);
}	

//------------------------------------------------------------------------------

Sphere::~Sphere() {
}


//------------------------------------------------------------------------------

void Sphere::genSphere(float r, unsigned int nsides, unsigned int nsegments) {
	log("Sphere::genSphere r:%f nsides:%d nsegments:%d", r, nsides, nsegments);		
	
	float theta,phi;
	float dtheta = 180.0f/nsegments;
	float dphi   = 360.0f/nsides;
	unsigned int segment;
	unsigned int side;
	vec3 pos;
	vec3 normal;
	vec2 coord;
	
	unsigned int estimatedNumPoints = (unsigned int)(360/dtheta + 1) * (unsigned int)(360/dphi + 1);
	
	vertexStream.setNumVertices(estimatedNumPoints);
	vertexStream.setNumIndices(estimatedNumPoints * 6);
	vertexStream.setNumIndices2(estimatedNumPoints * 8);
	
	log("Sphere::genSphere numPoints:%d numIndices:%d", estimatedNumPoints, estimatedNumPoints*6);		
	
	VertexAttrib* posAttrib = vertexStream.getAttrib("position", TYPE_VEC3);
	vec3* posBuf = (vec3*)posAttrib->getBuffer();
	
	unsigned short* indexBuf = vertexStream.getIndices();
	unsigned short* indexBuf2 = vertexStream.getIndices2();
	
	VertexAttrib* normAttrib = vertexStream.getAttrib("normal", TYPE_VEC3);
	vec3* normBuf = (vec3*)normAttrib->getBuffer();
	
	VertexAttrib* tex0Attrib = vertexStream.getAttrib("texCoord0", TYPE_VEC2);
	vec2* tex0Buf = (vec2*)tex0Attrib->getBuffer();
	
	for (theta=0, segment=0; theta<=180; theta+=dtheta, ++segment) {
		for (phi=0, side=0; phi<=360; phi+=dphi, ++side) {
			pos.x = (float)(r * sin(degToRad(theta)) * sin(degToRad(phi)));
			pos.y = (float)(r * cos(degToRad(theta)));
			pos.z = (float)(r * sin(degToRad(theta)) * cos(degToRad(phi)));
			normal = normalize(pos);

			coord.s = theta/180.0f;
			coord.t = phi/360.0f;
			
			*posBuf = pos;
			++posBuf;
			
			*normBuf = normal;
			++normBuf;
			
			*tex0Buf = coord;
			++tex0Buf;
			
			//na dolnym biegunie nie dodajemy juz face'ow
			if (segment == nsegments) continue;
			if (side == nsides) continue;
			
			*indexBuf = ((segment  )*(nsides+1) + side); 
			++indexBuf;
			*indexBuf = ((segment+1)*(nsides+1) + side);			
			++indexBuf;
			*indexBuf = ((segment+1)*(nsides+1) + side + 1);
			++indexBuf;
			
			*indexBuf = ((segment  )*(nsides+1) + side); 
			++indexBuf;
			*indexBuf = ((segment+1)*(nsides+1) + side + 1);
			++indexBuf;
			*indexBuf = ((segment  )*(nsides+1) + side + 1);
			++indexBuf;		
			
			
			*indexBuf2 = ((segment  )*(nsides+1) + side); 
			++indexBuf2;
			*indexBuf2 = ((segment+1)*(nsides+1) + side);			
			++indexBuf2;
			
			*indexBuf2 = ((segment+1)*(nsides+1) + side);			
			++indexBuf2;			
			*indexBuf2 = ((segment+1)*(nsides+1) + side + 1);
			++indexBuf2;
			
			*indexBuf2 = ((segment+1)*(nsides+1) + side + 1);
			++indexBuf2;			
			*indexBuf2 = ((segment  )*(nsides+1) + side + 1);
			++indexBuf2;
			
			*indexBuf2 = ((segment  )*(nsides+1) + side + 1);
			++indexBuf2;
			*indexBuf2 = ((segment  )*(nsides+1) + side); 
			++indexBuf2;
		}
	}
	
	log(" vertexStream %d .numAttribs: %d", &vertexStream, vertexStream.getNumAttribs());
}

//------------------------------------------------------------------------------

} //namespace vrg