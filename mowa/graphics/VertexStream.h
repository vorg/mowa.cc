/*
 *  VertexStream.h
 *  DMA
 *
 *  Created by vorg on 2009-10-15.
 *  Copyright 2009 Vorg. All rights reserved.
 *
 */

#ifndef FLOW_VERTEX_STREAM_H
#define FLOW_VERTEX_STREAM_H

#include <vector>
#include "DataType.h"
#include "Utils.h"

namespace flow {
	
//-----------------------------------------------------------------------------
		
typedef std::string VertexAttribType;
	
//-----------------------------------------------------------------------------
	
class VertexAttribDeclaration {
public:
	VertexAttribType name;
	DataType dataType;
	VertexAttribDeclaration(VertexAttribType name, DataType dataType) {
		this->name = name;
		this->dataType = dataType;
		//Log::msg("VertexAttribDeclaration+");
	}
	~VertexAttribDeclaration() {
		//Log::msg("VertexAttribDeclaration-");
	}
};
	
//-----------------------------------------------------------------------------


class VertexAttrib {
friend class VertexStream;
public:
	VertexAttrib(VertexAttribType vertexAttribType, DataType dataType);
	
	void*				getBuffer();
	unsigned int		getNumVertices();
	VertexAttribType	getVertexAttribType();
	DataType			getDataType();
	unsigned char		getStride();
	unsigned char		getSize();
	
private:
	std::vector<unsigned int>	buffer;
	VertexAttribType	vertexAttribType;
	DataType			dataType;
	unsigned int		numVertices;
	unsigned char		stride;
	unsigned char		size; //number of components per attribute value
	
	void				setNumVertices(unsigned int numVertices);
};

//-----------------------------------------------------------------------------

class VertexStream {	
public:
	VertexStream();
	~VertexStream();
	
	unsigned int	getNumAttribs();
	VertexAttrib*	addAttrib(VertexAttribType type, DataType dataType);
	VertexAttrib*	getAttrib(VertexAttribType type, DataType dataType);
	VertexAttrib*	getAttrib(unsigned int index);		
	
	unsigned int	getNumVertices();
	void			setNumVertices(unsigned int numVertices);
	
	unsigned int	getNumIndices();
	void			setNumIndices(unsigned int numIndices);	
	unsigned short*	getIndices();

	//quads?
	unsigned int	getNumIndices2();
	void			setNumIndices2(unsigned int numIndices);	
	unsigned short*	getIndices2();
	
	typedef std::vector<unsigned short> IndicesList;
	typedef std::vector<VertexAttrib*> AttribList;
	
private:
	IndicesList		indices;
	IndicesList		indices2;
	AttribList		attribs;
	unsigned int	numVertices;		
};
	
//-----------------------------------------------------------------------------
	
} //namespace flow

#endif //FLOW_VERTEX_STREAM_H

