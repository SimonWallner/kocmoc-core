#ifndef KOCMOC_CORE_COMPONENT_OVERLAY_QUAD_HPP
#define KOCMOC_CORE_COMPONENT_OVERLAY_QUAD_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/gl.h>

#include <glm/glm.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class RenderMesh;
			class Shader;
		}
		
		namespace component
		{
			class OverlayQuad : public componentSystem::Component
			{
			public:
				OverlayQuad(util::Properties* _props,
							renderer::Shader* _shader = NULL,
							GLint _texture = -1)
					: props(_props)
					, shader(_shader)
					, texture(_texture)
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
				renderer::Shader* shader;
				GLint texture;
				
				glm::vec2 position;
				glm::vec2 scale;
			};
		}
	}
}

#endif
