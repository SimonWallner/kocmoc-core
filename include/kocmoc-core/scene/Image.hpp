#ifndef KOCMOC_CORE_SCENE_IMAGE_HPP
#define KOCMOC_CORE_SCENE_IMAGE_HPP

#include <kocmoc-core/types/types.h>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			/**
			 * Simple generic image class
			 */
			template <typename T>
			class Image
			{
			public:
				/**
				 * Create a new Image with the given dimensions
				 * Creation allocates memory.
				 */
				Image(types::uint _width, types::uint _height)
					: width(_width)
					, height(_height)
				{
					data = new T[width * height];
				}


				/**
				 * Destruct the image, free memory.
				 */
				~Image()
				{
					delete [] data;
				}
				
				/**
				 * set a value of the image
				 */
				void set(types::uint x, types::uint y, T value)
				{
					data[getIndex(x, y)] = value;
				}
				
				/**
				 * Get the value at the specified position
				 * Make sure it is in bound!
				 */
				T get(types::uint x, types::uint y)
				{
					return data[getIndex(x, y)];
				}
				
				types::uint getWidth(void) {return width;}
				types::uint getHeight(void) {return height;}
				
				/**
				 * get the raw data pointer
				 */
				T* raw(void) {return data;}
				
			private:
				T* data;
				types::uint width, height;
				
				inline types::uint getIndex(types::uint x, types::uint y)
				{
					return width * y + x;
				}
			};
		}
	}
}

#endif
