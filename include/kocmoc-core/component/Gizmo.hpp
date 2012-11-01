#ifndef KOCMOC_COMPONENT_GIZMO_HPP
#define KOCMOC_COMPONENT_GIZMO_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/math/math.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class Gizmo : public core::componentSystem::Component
			{
			public:
				Gizmo();

				glm::vec3 position;
				glm::quat orientation;
				glm::vec3 scale;
			};
		}
	}
}

#endif
