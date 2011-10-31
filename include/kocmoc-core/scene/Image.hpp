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
				 * The flattened image data array
				 */
				T* data;
				
				/**
				 * image width and height
				 */
				const unsigned int width;
				const unsigned int height;
				
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
				 * set a value of a certain pixel with the given index.
				 */

				
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
				
				/**
				 * get the index of a certain pixel
				 */
				inline types::uint getIndex(types::uint x, types::uint y)
				{
					return width * y + x;
				}
				
				/**
				 * clear the image with the given value
				 */
				void clear(T clearValue)
				{
					for (unsigned int i = 0; i < (width * height); i++)
					{
						data[i] = clearValue;
					}
				}
				
				void fillRect(unsigned int x, unsigned int y,
							  unsigned int width, unsigned int height,
							  unsigned char value)
				{
					// for each line
					for (unsigned int l = 0; l < height; l++)
					{
						unsigned int index = getIndex(x, y + l);
						for (unsigned int j = 0; j < width; j++)
						{
							data[index + j] = value;
						}
					}
				}
			};
		}
	}
}

#endif
