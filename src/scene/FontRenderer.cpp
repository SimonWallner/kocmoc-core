#include <kocmoc-core/scene/FontRenderer.hpp>

#include <iostream>

#include <kocmoc-core/compiler.h>

using namespace kocmoc::core::scene;
using std::string;
using kocmoc::core::types::symbolize;

/**
 * code mostly derived from the tutorial found at
 * http://www.freetype.org/freetype2/docs/tutorial/step1.html
 */

FontRenderer::FontRenderer(util::Properties* props)
{
	FT_Error error;
	
	error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "failed to initialize freetype lib" << std::endl;
	}
	
	string fontPath = props->getString(symbolize("core-media-path"))
		+ props->getString(symbolize("default-font-name"));
	
	error = FT_New_Face(library,
						fontPath,
						0,
						&face );
	
	if (error == FT_Err_Unknown_File_Format)
		std::cout << "font format not supported: " << fontPath << std::endl;
	else if (error)
		std::cout << "failed to open font: " << fontPath << std::endl;
	
	error = FT_Set_Char_Size(
							 face,    /* handle to face object           */
							 0,       /* char_width in 1/64th of points  */
							 16*64,   /* char_height in 1/64th of points */
							 300,     /* horizontal device resolution    */
							 300 );   /* vertical device resolution      */
	if (error)
		std::cout << "setting the char size failed!" << std::endl;
	
	error = FT_Set_Pixel_Sizes(
							   face,   /* handle to face object */
							   0,      /* pixel_width           */
							   16 );   /* pixel_height          */
	if (error)
		std::cout << "setting the pixel size failed!" << std::endl;
}

GLint FontRenderer::render(string text, GLint existingHandle)
{	
	int pen_x = 300;
	int pen_y = 200;

	FT_GlyphSlot slot = face->glyph;    
	
	const char* cText = text.c_str();
	for (size_t n = 0; n < text.length(); n++)
	{
		FT_UInt  glyph_index;
		
		/* retrieve glyph index from character code */
		glyph_index = FT_Get_Char_Index(face, cText[n]);
		
		/* load glyph image into the slot (erase previous one) */
		FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		if (error)
			continue;  /* ignore errors */
		
		/* convert to an anti-aliased bitmap */
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if (error)
			continue;
		
		/* now, draw to our target surface */
		drawToTexture(&slot->bitmap,
					   pen_x + slot->bitmap_left,
					   pen_y - slot->bitmap_top);
		
		/* increment pen position */
		pen_x += slot->advance.x >> 6;
		pen_y += slot->advance.y >> 6; /* not useful for now */
	}
	
	UNUSED text;
	UNUSED existingHandle;
	
	return 0;
}