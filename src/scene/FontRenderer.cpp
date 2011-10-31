#include <kocmoc-core/scene/FontRenderer.hpp>

#include <iostream>

#include <kocmoc-core/compiler.h>
#include <kocmoc-core/math/math.hpp>
#include <kocmoc-core/scene/Image.hpp>

using namespace kocmoc::core::scene;
using std::string;
using kocmoc::core::types::symbolize;
using kocmoc::core::math::min;
using kocmoc::core::math::max;
using kocmoc::core::scene::Image;
using kocmoc::core::types::uint;

/**
 * code mostly derived from the tutorial found at
 * http://www.freetype.org/freetype2/docs/tutorial/step1.html
 */

FontRenderer::FontRenderer(util::Properties* props, unsigned int size)
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
	
	error = FT_Set_Pixel_Sizes(
							   face,   /* handle to face object */
							   0,      /* pixel_width           */
							   size );   /* pixel_height          */
	if (error)
		std::cout << "setting the pixel size failed!" << std::endl;
	
	isKerningSupported = FT_HAS_KERNING(face);
	
	// computing em and en
	FT_UInt emIndex = FT_Get_Char_Index(face, 'M');
	FT_UInt enIndex = FT_Get_Char_Index(face, 'N');
	
	FT_Load_Glyph(face, emIndex, FT_LOAD_DEFAULT);
	em = face->glyph->metrics.width >> 6;

	FT_Load_Glyph(face, enIndex, FT_LOAD_DEFAULT);
	en = face->glyph->metrics.width >> 6;
}

Tex FontRenderer::render(string text, GLint existingHandle)
{	
	// compute string AABB
	const char* cText = text.c_str();
	FT_Glyph* glyphs = new FT_Glyph[text.length()];
	int* pos = new int[text.length()];
	
	int penX = 0;
	int maxDescender = 0;
	int maxBearingY = 0;
	
	FT_UInt previousGlyphIndex = 0;
	for (size_t i = 0; i < text.length(); i++)
	{
		if (cText[i] == ' ')
		{
			penX += en/2;
			continue;
		}
		
		
		FT_UInt glyphIndex = FT_Get_Char_Index(face, cText[i]);
		
		/* retrieve kerning distance and move pen position */
		if (isKerningSupported && previousGlyphIndex && glyphIndex)
		{
			FT_Vector delta;
			
			FT_Get_Kerning(face, previousGlyphIndex, glyphIndex,
						   FT_KERNING_DEFAULT, &delta);
			
			penX += delta.x >> 6;
		}
		
		/* load glyph image into the slot without rendering */
		FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
		if (error)
			continue;  /* ignore errors, jump to next glyph */
		
		/* extract glyph image and store it in our table */
		error = FT_Get_Glyph(face->glyph, &glyphs[i]);
		if (error)
			continue;  /* ignore errors, jump to next glyph */

		FT_Glyph_Metrics metrics = face->glyph->metrics;
		
		/* store current pen position */
		pos[i] = penX + (metrics.horiBearingX >> 6);
		
		penX += metrics.horiAdvance >> 6;
		
		int descender = metrics.height - metrics.horiBearingY;
		maxDescender = max(maxDescender, descender >> 6);
		maxBearingY = max<int>(maxBearingY, metrics.horiBearingY >> 6);

		previousGlyphIndex = glyphIndex;
	}
	
	
	// create blank image
	Image<unsigned char > image(penX, maxDescender + maxBearingY + 2);
	image.clear(0);
	
	
	// render string into image
	FT_Vector origin;
	origin.x = 0;
	origin.y = 0;
	
	for (size_t i = 0; i < text.length(); i++)
	{
		FT_Error error = FT_Glyph_To_Bitmap(&glyphs[i],
											FT_RENDER_MODE_NORMAL,
											&origin,
											true); // destroy original glyph
		if (error) // ignore errors for now.
			continue;
		
		FT_BitmapGlyph glyphBitmap = (FT_BitmapGlyph)glyphs[i];
		
		writeToImage(glyphBitmap, image, pos[i], maxDescender + 1);
		
		FT_Done_Glyph(glyphs[i]);
	}
	
	// convert image to texture
	// return handle
	
	UNUSED existingHandle;	
	
	return Tex(toTexture(image), image.width, image.height);

}

void FontRenderer::writeToImage(FT_BitmapGlyph& bitmapGlyph, Image<unsigned char>& image,
						   const uint penX, const uint baseline)
{
	const FT_Bitmap& bitmap = bitmapGlyph->bitmap;
	int top = bitmapGlyph->top;
	
	// copy line by line
	for (int l = 0; l < bitmap.rows; l++)
	{
		unsigned int targetIndex = image.getIndex(penX, ((bitmap.rows - l) - 1) + (baseline - (bitmap.rows - top)));
		unsigned int sourceIndex = bitmap.width * l;
		
		for (int i = 0; i < bitmap.width; i++)
		{
			image.data[targetIndex + i] = image.data[targetIndex + i] + bitmap.buffer[sourceIndex + i];
		}
	}
}

GLint FontRenderer::toTexture(Image<unsigned char >& image)
{
	GLuint handle;
	glGenTextures(1, &handle);
			
	glBindTexture(GL_TEXTURE_2D, handle);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, // target
				 0,				// level
				 GL_LUMINANCE,		// internal format
				 image.width,	// width
				 image.height,	// height
				 0,				// border
				 GL_LUMINANCE,		// format
				 GL_UNSIGNED_BYTE, // type
				 image.data);	// data
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glGenerateMipmap(GL_TEXTURE_2D);		
	
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return handle;
}
