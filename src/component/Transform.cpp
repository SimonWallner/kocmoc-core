#include <kocmoc-core/component/Transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace kocmoc::core::component;

Transform::Transform()
	: matrix(glm::mat4())
{}

float* Transform::toGLMatrix()
{
	return glm::value_ptr(matrix);
}