#ifndef KOCMOC_CORE_COMPONENT_POINT_SPRITE
#define KOCMOC_CORE_COMPONENT_POINT_SPRITE

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/renderer/RenderMesh21.hpp>
#include <kocmoc-core/gl.h>

#include <glm/glm.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class PointSprite : public componentSystem::Component
			{
			public:
				PointSprite(renderer::Shader* _shader, GLint _textureHandle)
					: shader(_shader)
					, textureHandle(_textureHandle)
					, position(glm::vec3(0))
					, size(glm::vec2(1))
				{}
				
				void setPosition(glm::vec3 newPos)
				{
					position = newPos;
				}
				
				void setSize(glm::vec2 newSize)
				{
					size = newSize;
				}
				
				void init();
				void onRender(renderer::RenderPass pass, scene::Camera* camera);
				
			private:
				renderer::Shader* shader;
				GLint textureHandle;
				glm::vec3 position;
				glm::vec2 size;
				
				renderer::RenderMesh* renderMesh;
			};
		}
	}
}


#endif
