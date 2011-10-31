#ifndef KOCMOC_CORE_SCENE_FONT_RENDERER
#define KOCMOC_CORE_SCENE_FONT_RENDERER

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <kocmoc-core/gl.h>
#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/types/types.h>
#include <kocmoc-core/scene/Image.hpp>

namespace kocmoc 
{
	namespace core
	{
		namespace scene
		{
			/*
			 * struct to hold the return value of render
			 */
			struct Tex
			{
				Tex(GLint _handle, unsigned int _width, unsigned int _height)
					: handle(_handle)
					, width(_width)
					, height(_height)
				{}
				
				const GLint handle;
				const unsigned int width;
				const unsigned int height;
			};
			
			/**
			 * Use freetype to create textures form a given string.
			 */
			class FontRenderer
			{
			public:
				FontRenderer(util::Properties* props, unsigned int size = 100);
				
				/**
				 * Update the texture with the given text.
				 * This might change the size of the texture
				 * @param text the text to render
				 * @param existinHandle and existing texture handle to which
				 *			the text should be rendered.
				 */
				Tex render(std::string text, GLint existingHandle = -1);
				
			private:
				FT_Library library;
				FT_Face face;
				bool isKerningSupported;
				
				int em, en;
				
				/**
				 * write the bitmap to the image
				 */
				void writeToImage(FT_BitmapGlyph& bitmapGlyph, Image<unsigned char >& image,
								  types::uint penX, types::uint baseline);
				
				/**
				 * convert the image to a texture
				 */
				GLint toTexture(Image<unsigned char >& image);
			};
		}
	}
}

#endif
