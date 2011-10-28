#ifndef KOCMOC_CORE_RENDERER_FRAME_BUFFER_HPP
#define KOCMOC_CORE_RENDERER_FRAME_BUFFER_HPP

#include <kocmoc-core/gl.h>
#include <kocmoc-core/util/Properties.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class Shader;

			/**
			 * quick and dirty frame buffer
			 */
			class FrameBuffer
			{
			public:
				virtual ~FrameBuffer() {}

				/**
				* setup the shader that is used for rendering the fb quad. Override this
				* method in subclasses!
				*/
				virtual void setupShader(util::Properties* props) = 0;


				GLuint getTextureHandle() const 
				{
					return textureHandle;
				}
				
				GLuint getFBOHandle() const
				{
					return fboHandle;
				}
				
				/**
				 * draw the FBO to the screen
				 * It will be drawn, so that the gate matches the screen.
				 */
				virtual void drawFBO() = 0;

			protected:
			
				GLuint textureHandle;
				GLuint depthbufferHandle; 

				/** shader to draw the fbo */
				Shader *shader;

				/** handle of the fbo */
				GLuint fboHandle;
			};
		}
	}
}

#endif
