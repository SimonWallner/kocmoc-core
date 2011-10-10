#ifndef KOCMOC_CORE_COMPONENT_OVERLAY_QUAD_HPP
#define KOCMOC_CORE_COMPONENT_OVERLAY_QUAD_HPP

#include <kocmoc-core/componentSystem/Component.hpp>

#include <glm/glm.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class RenderMesh;
		}
		
		namespace component
		{
			class OverlayQuad : public componentSystem::Component
			{
			public:
				OverlayQuad(util::Properties* _props)
					: props(_props)
					, position(glm::vec2(0.0f))
					, scale(glm::vec2(1.0f))
				{}
				
				void init();
				void onRender(renderer::RenderPass pass, scene::Camera* camera);
				
				void setPosition(glm::vec2 _position)
				{
					position = _position;
				}
				
				void setScale(glm::vec2 _scale)
				{
					scale = _scale;
				}
			
			private:
				renderer::RenderMesh* renderMesh;
				util::Properties* props;
				
				glm::vec2 position;
				glm::vec2 scale;
			};
		}
	}
}

#endif
