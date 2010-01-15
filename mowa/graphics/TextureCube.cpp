/*
 *  TextureCube.cpp
 *  DirectMemoryAccess
 *
 *  Created by Marcin Ignac on 12/27/09.
 *  Copyright 2009 marcinignac.com. All rights reserved.
 *
 */

#include "TextureCube.h"
#include "Utils.h"
#include "Os.h"

namespace flow {
	
//------------------------------------------------------------------------------

TextureCube::TextureCube() {
	//Log::msg("TextureCube+");	
}

//------------------------------------------------------------------------------

TextureCube::~TextureCube() {
	//Log::msg("TextureCube-");	
}
	
//------------------------------------------------------------------------------
	
TextureCube* TextureCube::fromFile(const char* fileName) {
	TextureCube* texture = new TextureCube();
	texture->textureTarget = GL_TEXTURE_CUBE_MAP;
	glGenTextures(1, &texture->textureObject);	
	
	texture->bind();	
	glTexParameteri(texture->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texture->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(texture->textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf(texture->textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameterf(texture->textureTarget, 0x8072, GL_CLAMP_TO_EDGE);	//GL_TEXTURE_WRAP_R
	
	int targets[] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};
	const char* suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
	char sideFileName[255];	
	for(int i=0; i<6; i++) {		
		sprintf(sideFileName, "numsky_%s.png", suffixes[i]);
		//sprintf(sideFileName, "sky_%s.png", suffixes[i]);
		//sprintf(sideFileName, "browar_%s.jpg", suffixes[i]);
		unsigned int bpp;
		unsigned char* imageData = osLoadImageFile(sideFileName, &texture->width, &texture->height, &bpp);
		
		if (bpp == 32) {
			glTexImage2D(targets[i], 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		}
		else if (bpp == 24) {
			glTexImage2D(targets[i], 0, GL_RGBA, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		}
		else {
			Log::error("Texture2D::fromFile unsupported numbe of bpp (%d) in \"%s\"", bpp, fileName);
			return NULL;
		}
	}
	
	return texture;
}
	
//------------------------------------------------------------------------------
	
/*
 
 package pl.vorg.mowa.graphics;
 
 
 import java.io.File;
 import java.io.IOException;
 import java.util.logging.Logger;
 
 import javax.media.opengl.GL;
 
 import com.sun.opengl.util.texture.Texture;
 import com.sun.opengl.util.texture.TextureData;
 import com.sun.opengl.util.texture.TextureIO;
 
 import pl.vorg.mowa.core.*;
 import pl.vorg.mowa.graphics.gl.Texture2D;
 
 public class CubemapFile extends Operator {
 public @In(String.class) Param<String> fileName;
 public @In(Boolean.class) Param<Boolean> mipmap;
 public @Out(Texture2D.class) Param<Texture2D> texture;
 
 private static Logger log = Logger.getLogger(CubemapFile.class.getName());
 
 private static final String[] suffixes = { "posx", "negx", "posy", "negy", "posz", "negz" };
 private static final int[] targets = { 
 GL.GL_TEXTURE_CUBE_MAP_POSITIVE_X,
 GL.GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
 GL.GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
 GL.GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
 GL.GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
 GL.GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
 };
 
 //	  public static Texture loadFromStreams(ClassLoader scope,
 //	                                        String basename,
 //	                                        String suffix,
 //	                                        boolean mipmapped) throws IOException, GLException {
 //	    
 //
 //	    for (int i = 0; i < suffixes.length; i++) {
 //	      String resourceName = basename + suffixes[i] + "." + suffix;
 //	      TextureData data = TextureIO.newTextureData(scope.getResourceAsStream(resourceName),
 //	                                                  mipmapped,
 //	                                                  FileUtil.getFileSuffix(resourceName));
 //	      if (data == null) {
 //	        throw new IOException("Unable to load texture " + resourceName);
 //	      }
 //	      cubemap.updateImage(data, targets[i]);
 //	    }
 //
 //	    return cubemap;
 //	  }
 
 public CubemapFile() {
 mipmap.set(false);
 }
 
 @Override
 public void update(Context context) {
 if (!valid && (fileName.get() != null)) {
 texture.set(null);
 
 int posOfAstertix = fileName.get().indexOf("*");
 if (posOfAstertix == -1) {
 log.severe("Invalid cubemap file name \""+ fileName.get()+"\"");
 return;
 }
 
 String basename = fileName.get().substring(0, posOfAstertix);
 String ext = fileName.get().substring(posOfAstertix+1);
 Texture cubemap = TextureIO.newTexture(GL.GL_TEXTURE_CUBE_MAP);
 
 for (int i = 0; i<suffixes.length; i++) {
 String textureFileName = basename + suffixes[i] + ext;
 TextureData data = null;
 try {
 data = TextureIO.newTextureData(new File(textureFileName), mipmap.get(), null);
 } catch (IOException e) {
 log.severe(e.getMessage());
 }
 if (data != null) {
 cubemap.updateImage(data, targets[i]);
 }
 else {
 log.severe("Failed to load cubemap texture from \"" + textureFileName + "\"");
 }
 }
 
 texture.set(new Texture2D(cubemap));
 valid = true;
 }
 }
 
 @Override
 public void paramChange(ParamChangeEvent evt) {
 if (evt.getParam() == fileName) {
 invalidate();
 }
 }
 
 @Override
 public void dispose() {
 texture.set(null);
 }
 }
*/ 

}

	

