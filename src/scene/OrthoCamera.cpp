#include <kocmoc-core/scene/OrthoCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace kocmoc::core::scene;
using glm::vec3;
using glm::vec4;
using glm::mat4;

OrthoCamera::OrthoCamera(vec3 _focus, vec3 _direction, vec3 _upVector)
	: focus(_focus)
	, direction(_direction)
	, upVector(glm::core::function::geometric::normalize(_upVector))
	, width(1)
	, height(1)
	, depth(1)
{}

OrthoCamera::~OrthoCamera(void)
{
}

void OrthoCamera::updateMatrixes()
{
	vec3 s = glm::normalize(glm::cross(direction, upVector));
	vec3 u = glm::normalize(glm::cross(s, direction));

	mat4 untranslatedViewMatrix = mat4(vec4(s, 0), vec4(u, 0), vec4(direction, 0), vec4(0, 0, 0, 1.0f));
	untranslatedViewMatrix = glm::core::function::matrix::transpose(untranslatedViewMatrix);

	viewMatrix = glm::gtc::matrix_transform::translate(untranslatedViewMatrix, -focus);

	projectionMatrix = mat4(1/width,	0,			0,			0,
							0,			1/height,	0,			0, 
							0,			0,			1/depth,	0,
							0,			0,			0,			1);
}

void OrthoCamera::setFocus(vec3 _focus)
{
	focus = _focus;
}