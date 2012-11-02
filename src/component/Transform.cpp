#include <kocmoc-core/component/Transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace kocmoc::core::component;

Transform::Transform()
	: matrix(glm::mat4())
{}

Transform::Transform(glm::mat4 _matrix)
	: matrix(_matrix)
{}

float* Transform::toGLMatrix()
{
	return glm::value_ptr(matrix);
}