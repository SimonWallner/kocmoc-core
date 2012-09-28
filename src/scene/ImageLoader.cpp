#include <kocmoc-core/scene/ImageLoader.hpp>

#define ILUT_USE_OPENGL
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <sstream>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::scene;

ImageLoader::ImageLoader(void)
{
	ilInit();
	iluInit();

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
}


GLuint ImageLoader::loadImage(const std::string& filename)
{
	types::Symbol fileNameSymbol = types::symbolize(filename.c_str());
	ImageCache::const_iterator ci = cache.find(fileNameSymbol);
	if (ci != cache.end())
	{
		return ci->second;
	}
	
	GLuint handle;
	glGenTextures(1, &handle); /* Texture name generation */
	std::string fullPath = filename;
	
	// this code is based on the code found at http://gpwiki.org/index.php/DevIL:Tutorials:Basics
	ILuint texid;
	
	ilGenImages(1, &texid);
	ilBindImage(texid);
	
	ilLoadImage(fullPath.c_str());
	ILenum error = ilGetError();
	
	if (error == IL_NO_ERROR) /* If no error occured: */
	{
		/* Convert every colour component into unsigned byte. If your textureHandle contains
		 alpha channel you can replace IL_RGB with IL_RGBA */
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		
		glBindTexture(GL_TEXTURE_2D, handle); /* Binding of texture name */
		
		GLint internalFormat = GL_RGBA;// ilGetInteger(IL_IMAGE_FORMAT);
		
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, ilGetInteger(IL_IMAGE_WIDTH),
					 ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
					 ilGetData()); /* Texture specification */
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glGenerateMipmap(GL_TEXTURE_2D);		
		
		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// remove loaded image from memory
		ilDeleteImages(1, &texid);
		
		objectifLune::Singleton::Get()->debug("texture: '" + filename + "' loaded successfully");
		cache[fileNameSymbol] = handle;
		return handle;
	} else
	{
		std::stringstream sstr;
		sstr << "failed ot load image: " << filename << " '" << iluErrorString(error) << "'";
		objectifLune::Singleton::Get()->warn(sstr.str());
		return -1;
	}
}

GLuint ImageLoader::loadImage3D(const std::string& filename, bool degamma)
{
	GLuint handle;
	glGenTextures(1, &handle);
	
	// this code is based on the code found at http://gpwiki.org/index.php/DevIL:Tutorials:Basics
	ILuint texid;
	ilGenImages(1, &texid);
	ilBindImage(texid);
	
	ilLoadImage(filename.c_str());
	ILenum error = ilGetError();
	
	if (error == IL_NO_ERROR) /* If no error occured: */
	{
		/* Convert every colour component into unsigned byte. If your textureHandle contains
		 alpha channel you can replace IL_RGB with IL_RGBA */
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		
		glBindTexture(GL_TEXTURE_3D, handle);
		
		GLint internalFormat;
		if (degamma)
			internalFormat = GL_SRGB8_ALPHA8;
		else
			internalFormat = GL_RGBA;// ilGetInteger(IL_IMAGE_FORMAT);
		
		// we only consider square 3d textures this time
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int width = height;
		int depth = height;
		
		glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width,
					 height, depth, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
					 ilGetData()); /* Texture specification */
		
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		
		
		// unbind texture
		glBindTexture(GL_TEXTURE_3D, 0);
		// remove loaded image from memory
		ilDeleteImages(1, &texid);
		
		return handle;
	} else
	{
		objectifLune::Singleton::Get()->warn("failed to load 3D image: '" + filename + "'\ncause: " +
											 iluErrorString(error));
		return 0;
	}
}
