#ifndef KOCMOC_CORE_RENDERER_FRAME_BUFFER_21_HPP
#define KOCMOC_CORE_RENDERER_FRAME_BUFFER_21_HPP

#include <kocmoc-core/renderer/Framebuffer.hpp>

#include <kocmoc-core/renderer/RenderMesh21.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace resources
		{
			class ResourceManager;
		}
		
		namespace renderer
		{
			class FrameBuffer21 : public FrameBuffer
			{
			public:
				/**
				 * Create a frame buffer with the following arguments
				 * The difference between the frame and the gate is the filter
				 * margin.
				 *
				 * @param frameWidth Width of the complete frame. i.e. with margin
				 * @param frameHeigt Height of the complete frame.
				 * @param gateWidth Width of the actualy visible area. Make the 
				 *		gate smaller for letterbox rendering.
				 * @param gateHeight Height of the actual visiible area.
				 * @param windowWidth
				 * @param windowHeight
				 * @param angleOfView
				 * @param props
				 */
				FrameBuffer21(int frameWidth, int frameHeight, int gateWidth, int gateHeight,
							  int windowWidth, int windowHeight, float angleOfView,
							  util::Properties* props, const resources::ResourceManager* resourceManager);
				
				~FrameBuffer21() {}
				
				/**
				 * setup the shader that is used for rendering the fb quad. Override this
				 * method in subclasses!
				 */
				virtual void setupShader(util::Properties* props);
				
				/**
				 * draw the FBO to the screen
				 * It will be drawn, so that the gate matches the screen.
				 */
				virtual void drawFBO();

				const int frameWidth;
				const int frameHeight;
				const int gateWidth;
				const int gateHeight;
				const int windowWidth;
				const int windowHeight;
				const float angleOfView;
				
			private:
				RenderMesh21* renderMesh;
				unsigned int maxMipLevel;
				GLint averageWidth, averageHeight;
				
				void setFBOTexture();
				void createQuad();
				void check();
				
				const resources::ResourceManager* resourceManager;
			};
		}
	}
}

#endif
