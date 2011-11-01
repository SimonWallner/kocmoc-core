#ifndef KOCMOC_CORE_SCENE_QUAD_HPP
#define KOCMOC_CORE_SCENE_QUAD_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/renderer/RenderMesh21.hpp>
#include <kocmoc-core/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			/**
			 * a single textured quad
			 */
			class Quad : public componentSystem::Component
			{
			public:
				Quad(renderer::Shader* shader, GLint textureHandle);
				
				void setPosition(glm::vec3 newPos)
				{
					position = newPos;
				}
				
				void setSize(glm::vec2 newSize)
				{
					size = newSize;
				}
				
				void setRotation(glm::quat newRot)
				{
					rotation = newRot;
				}
				
				void draw(scene::Camera* camera);
				
			private:
				GLint textureHandle;
				
				glm::vec3 position;
				glm::vec2 size;
				glm::quat rotation;
				
				renderer::RenderMesh* renderMesh;
			};
		}
	}
}


#endif
