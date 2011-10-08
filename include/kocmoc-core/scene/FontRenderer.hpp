#ifndef KOCMOC_CORE_SCENE_FONT_RENDERER
#define KOCMOC_CORE_SCENE_FONT_RENDERER

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <kocmoc-core/gl.h>
#include <kocmoc-core/util/Properties.hpp>

namespace kocmoc 
{
	namespace core
	{
		namespace scene
		{
			/**
			 * Use freetype to create textures form a given string.
			 */
			class FontRenderer
			{
			public:
				FontRenderer(util::Properties* props);
				
				/**
				 * Update the texture with the given text.
				 * This might change the size of the texture
				 * @param text the text to render
				 * @param existinHandle and existing texture handle to which
				 *			the text should be rendered.
				 */
				GLint render(std::string text, GLint existingHandle = -1);
				
			private:
				FT_Library library;
				FT_Face face;      
			};
		}
	}
}

#endif
