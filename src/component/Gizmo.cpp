#include <kocmoc-core/component/Gizmo.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <glm/gtx/quaternion.hpp>
#pragma GCC diagnostic pop

using namespace kocmoc::core::component;

using glm::angleAxis;

Gizmo::Gizmo()
	: position(glm::vec3(0, 0, 0))
	, orientation(angleAxis(0.0f, 0.0f, 0.0f, 1.0f))
	, scale(glm::vec3(1, 1, 1))
{}
