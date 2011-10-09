#include <kocmoc-core/scene/FontRenderer.hpp>

#include <iostream>

#include FT_GLYPH_H

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
		std::cout << "failed to initialize freetype lib" << std::endl;
	
	string fontPath = props->getString(symbolize("core-media-path"))
		+ props->getString(symbolize("default-font-name"));
	
	error = FT_New_Face(library,
						fontPath.c_str(),
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
	
	isKerningSupported = FT_HAS_KERNING(face);
}

GLint FontRenderer::render(string text, GLint existingHandle)
{	
	// compute string AABB
	const char* cText = text.c_str();
	FT_Glyph* glyphs = new FT_Glyph[text.length()];
	FT_Vector* pos = new FT_Vector[text.length()];
	
	int penX = 0;
	int penY = 0;
	
	FT_UInt previousGlyphIndex = 0;
	for (size_t i = 0; i < text.length(); i++)
	{
		FT_UInt glyphIndex = FT_Get_Char_Index(face, cText[i]);
		
		/* retrieve kerning distance and move pen position */
		if (isKerningSupported && previousGlyphIndex && glyphIndex)
		{
			FT_Vector delta;
			
			FT_Get_Kerning(face, previousGlyphIndex, glyphIndex,
						   FT_KERNING_DEFAULT, &delta);
			
			penX += delta.x >> 6;
		}
		
		/* store current pen position */
		pos[i].x = penX;
		pos[i].y = penY;
		
		/* load glyph image into the slot without rendering */
		FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
		if (error)
			continue;  /* ignore errors, jump to next glyph */
		
		/* extract glyph image and store it in our table */
		error = FT_Get_Glyph(face->glyph, &glyphs[i]);
		if (error)
			continue;  /* ignore errors, jump to next glyph */
		
		
		previousGlyphIndex = glyphIndex;

	}
	
	
	// create blank image
	// render string into image
	// convert image to texture
	// return handle
	
	UNUSED cText;
	UNUSED glyphs;
	UNUSED existingHandle;
	
	return 0;
}

