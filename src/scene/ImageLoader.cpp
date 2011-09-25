#include <kocmoc-core/scene/ImageLoader.hpp>

#define ILUT_USE_OPENGL
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <sstream>
#include <iostream>

using namespace kocmoc::core::scene;
using std::cout;
using std::endl;

ImageLoader::ImageLoader(void)
{
	ilInit();
	iluInit();

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
}


GLuint ImageLoader::loadImage(std::string filename)
{
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
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//if (useAF)
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy);
		
//		glGenerateMipmap(GL_TEXTURE_2D);		
		
		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// remove loaded image from memory
		ilDeleteImages(1, &texid);
		
		cout << "texture: '" << filename << "' loaded successfully" << std::endl;
		return true;
	} else
	{
		cout << "failed ot load image: " << filename << " '" << iluErrorString(error) << "'" << endl;
		return false;
	}
}


void ImageLoader::screenShot()
{
	// init
	ilutRenderer(ILUT_OPENGL);

	ILuint image;

	ilGenImages(1, &image);
	ilBindImage(image);

	ilutGLScreen();

//	ILenum error = ilGetError();

	time_t t = time(0);
	struct tm * now = localtime(&t);

	char buffer[50];
	
	sprintf(buffer, "screenshot_%d_%d_%d-%d-%d-%d.png",
	now->tm_year + 1900,
	now->tm_mon + 1,
	now->tm_mday,
	now->tm_hour,
	now->tm_min,
	now->tm_sec);


	if(ilSave(IL_PNG, buffer))
		cout << "screenshot taken! (" << buffer << ")" << std::endl;
	else 
	{
		std::cout << "failed to take screenshot: ";
		if (ilGetError() == IL_COULD_NOT_OPEN_FILE)
			std::cout << "could not open file '" << buffer << "' for writing";

		std::cout << std::endl;
	}

	ilDeleteImage(image);
}
