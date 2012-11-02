#ifndef KOCMOC_COMPONENT_GIZMO_HPP
#define KOCMOC_COMPONENT_GIZMO_HPP

#include <glm/glm.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class Transform : public core::componentSystem::Component
			{
			public:
				Transform();
				Transform(glm::mat4 matrix);
				
				float* toGLMatrix();

				glm::mat4 matrix;
			};
		}
	}
}

#endif
