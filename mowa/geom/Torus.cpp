/*
 *  Torus.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/27/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */


#include "Torus.h"
#include "MathLib.h"
#include "Utils.h"

namespace flow {	

//------------------------------------------------------------------------------

Torus::Torus(float R=1, float r=0.3, unsigned int nsides=36, unsigned int nsegments=36) {	
	Log::msg("Torus::Torus R:%f r:%f nsides:%d nsegments:%d", R, r, nsides, nsegments);
	vertexStream.addAttrib("position", TYPE_VEC3);
	vertexStream.addAttrib("normal", TYPE_VEC3);
	vertexStream.addAttrib("texCoord0", TYPE_VEC2);
	
	genTorus(R, r, nsides, nsegments);
}	

//------------------------------------------------------------------------------

Torus::~Torus() {
}


//------------------------------------------------------------------------------

void Torus::genTorus(float R, float r, unsigned int nsides, unsigned int nsegments) {
	float theta, phi;
	float dtheta = 360.0f/nsides;
	float dphi   = 360.0f/nsegments;
	unsigned int segment;
	unsigned int side;
	vec3 pos;
	vec3 posOnR;
	vec3 normal;
	vec2 coord;
	
	unsigned int estimatedNumPoints = (unsigned int)(360/dtheta + 1) * (unsigned int)(360/dphi + 1);
	
	vertexStream.setNumVertices(estimatedNumPoints);
	vertexStream.setNumIndices(estimatedNumPoints * 6);
	vertexStream.setNumIndices2(estimatedNumPoints * 8);
	
	Log::msg("Torus::genTorus numPoints:%d numIndices:%d dtheta:%f dphi:%f", estimatedNumPoints, estimatedNumPoints*6, dtheta, dphi);		
	
	VertexAttrib* posAttrib = vertexStream.getAttrib("position", TYPE_VEC3);
	vec3* posBuf = (vec3*)posAttrib->getBuffer();
	
	unsigned short* indexBuf = vertexStream.getIndices();
	unsigned short* indexBuf2 = vertexStream.getIndices2();
	
	VertexAttrib* normAttrib = vertexStream.getAttrib("normal", TYPE_VEC3);
	vec3* normBuf = (vec3*)normAttrib->getBuffer();
	
	VertexAttrib* tex0Attrib = vertexStream.getAttrib("texCoord0", TYPE_VEC2);
	vec2* tex0Buf = (vec2*)tex0Attrib->getBuffer();
	
	for (theta=0, side=0; theta<=360; theta+=dtheta, ++side) {
		for (phi=0, segment=0; phi<=360; phi+=dphi, ++segment) {
			pos.x = (R + r * cos(degToRad(phi))) * cos(degToRad(theta));
			pos.y = (R + r * cos(degToRad(phi))) * sin(degToRad(theta));
			pos.z = r * sin(degToRad(phi));
			
			posOnR.x = R * cos(degToRad(theta));
			posOnR.y = R * sin(degToRad(theta));
			posOnR.z = 0;
			
			normal = normalize(pos - posOnR);
			
			coord.s = theta/360.0f;
			coord.t = phi/360.0f;
			
			*posBuf = pos;
			++posBuf;
			
			*normBuf = normal;
			++normBuf;
			
			*tex0Buf = coord;
			++tex0Buf;
			
			if (segment == nsegments) continue;
			if (side == nsides) continue;
			
			*indexBuf = ((side  )*(nsegments+1) + segment); 
			++indexBuf;
			*indexBuf = ((side+1)*(nsegments+1) + segment);			
			++indexBuf;
			*indexBuf = ((side+1)*(nsegments+1) + segment + 1);
			++indexBuf;
			
			*indexBuf = ((side  )*(nsegments+1) + segment); 
			++indexBuf;
			*indexBuf = ((side+1)*(nsegments+1) + segment + 1);
			++indexBuf;
			*indexBuf = ((side  )*(nsegments+1) + segment + 1);
			++indexBuf;		
			
			
			*indexBuf2 = ((side  )*(nsegments+1) + segment); 
			++indexBuf2;
			*indexBuf2 = ((side+1)*(nsegments+1) + segment);			
			++indexBuf2;
			
			*indexBuf2 = ((side+1)*(nsegments+1) + segment);			
			++indexBuf2;			
			*indexBuf2 = ((side+1)*(nsegments+1) + segment + 1);
			++indexBuf2;
			
			*indexBuf2 = ((side+1)*(nsegments+1) + segment + 1);
			++indexBuf2;			
			*indexBuf2 = ((side  )*(nsegments+1) + segment + 1);
			++indexBuf2;
			
			*indexBuf2 = ((side  )*(nsegments+1) + segment + 1);
			++indexBuf2;
			*indexBuf2 = ((side  )*(nsegments+1) + segment); 
			++indexBuf2;
		}
	}
	
	Log::msg(" vertexStream %d .numAttribs: %d", &vertexStream, vertexStream.getNumAttribs());
}

//------------------------------------------------------------------------------

} //namespace vrg