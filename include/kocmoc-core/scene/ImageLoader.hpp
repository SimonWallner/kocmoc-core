#ifndef KOCMOC_CORE_SCENE_IMAGE_LOADER_HPP
#define KOCMOC_CORE_SCENE_IMAGE_LOADER_HPP

#include <map>
#include <IL/il.h>
#include <kocmoc-core/gl.h>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{

			struct ImageData{
				GLuint width;
				GLuint height;
				GLubyte* data;
			};

			/**
			 * A basic devIL image Loader.
			 */
			class ImageLoader
			{
			public:
				
				ImageLoader(void);

				/**
				 * Load the image from the given filename.
				 * This method loads the given texture into the graphic card's memory
				 * and returns a texture handle. The images are remove from the system
				 * memory after they have been pushed to the GPU.
				 * 
				 * Only files are supported that are supported by the underlying devIl lib.
				 *
				 * @param path full file path
				 * @return The texture handle. If an error occurs, \c0 is
				 *		returned instead
				 */
				GLuint loadImage(std::string path);


				/**
				 * Take a screenshot and save it to disk
				 * @param sequence if it is true, the screenshots are numbered in 
				 *		a sequence.
				 */
				void screenShot(void);
			};
		}
	}
}

#endif
