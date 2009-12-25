/*
 *  Texture2D.h
 *  DMA
 *
 *  Created by Marcin Ignac on 12/20/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FLOW_TEXTURE_2D_H
#define FLOW_TEXTURE_2D_H

#include <string>
#include "Graphics.h"

namespace flow {

class Texture2D {
private:
	GLuint textureObject; 
	GLuint textureTarget;
	GLuint width;
	GLuint height;
	
public:
	Texture2D();
	~Texture2D();
	static Texture2D* create(int width, int height);
	static Texture2D* fromFile(const char* fileName);
	static Texture2D* generateChecker();
	void bind();
};

	
/*
public static Texture2D generateChecker() {		
	final int W = 256;
	final int H = 256;
	int[] pixels = new int[W*H];
	
	int c;
	//int r, g, b, rgb;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			c = (byte)(((x&16)^(y&16))*255);
			//r = c << 16;
			//g = c << 0;
			//b = c << 0;
			//rgb = r + g + b;
			pixels[x + y*W] = c;
		}
	}
	BufferedImage bufImage = new BufferedImage(W, H, BufferedImage.TYPE_BYTE_GRAY);
	WritableRaster raster = bufImage.getRaster();
	raster.setPixels(0, 0, W, H, pixels);
	TextureData data = new TextureData(GL.GL_LUMINANCE, GL.GL_LUMINANCE, true, bufImage);
	com.sun.opengl.util.texture.Texture texture = TextureIO.newTexture(data);
	return new Texture2D(texture);
}
 */
	
}

#endif
