#ifndef KOCMOC_CORE_RENDERER_RENDER_PASS_ENUM_HPP
#define KOCMOC_CORE_RENDERER_RENDER_PASS_ENUM_HPP

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			/**
			 * render pass enum. This enum gives name to the render pass
			 */
			enum RenderPass {
				RP_NORMAL,
				RP_TRANSPARENT,
				RP_OVERLAY
			};	
		}
	}
}

#endif
