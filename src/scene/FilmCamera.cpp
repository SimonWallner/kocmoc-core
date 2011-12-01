#include <kocmoc-core/scene/FilmCamera.hpp>

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <kocmoc-core/constants.hpp>

using namespace kocmoc::core::scene;

using glm::vec3;
using glm::vec4;
using glm::mat4;

using glm::gtc::matrix_transform::translate;

FilmCamera::FilmCamera(vec3 _eyePosition, vec3 _targetPosition, vec3 _upVector)	
	: nearPlane(-0.1f)
	, farPlane(-1000.f)
	, angleOfView(constants::pi/2.0f)
	, horizontalMargin(0)
	, verticalMargin(0)
{
	setPosition(_eyePosition);
	setTargetPosition(_targetPosition);
	setUpVector(_upVector);
}

void FilmCamera::setPosition(vec3 position)
{
	eyePosition = position;
}

void FilmCamera::setTargetPosition(vec3 target)
{
	targetVector = glm::normalize(target - eyePosition);
}

void FilmCamera::setUpVector(vec3 up)
{
	upVector = glm::normalize(up);
}

FilmCamera::~FilmCamera()
{
	// TODO Auto-generated destructor stub
}

const mat4 FilmCamera::getProjectionMatrix()
{
	return projectionMatrix;
}

const mat4 FilmCamera::getViewMatrix()
{
	return viewMatrix;
}

const mat4 FilmCamera::getUntraslatedViewMatrix()
{
	return untranslatedViewMatrix;
}


void FilmCamera::updateMatrixes() 
{
	aspectRatio = (float)getFrameWidth()/(float)getFrameHeight();
	float extendedAOV = (atan(tan(angleOfView/2) * (((float)width + 2*horizontalMargin) / width))) * 2;

	// FIXME: dirty hack, make new camera model with phi, theta orientation
	upVector = vec3(0, 1, 0);

	vec3 s = glm::normalize(glm::cross(targetVector, upVector));
	vec3 u = glm::normalize(glm::cross(s, targetVector));

	untranslatedViewMatrix = mat4(vec4(s, 0), vec4(u, 0), vec4(-targetVector, 0), vec4(0, 0, 0, 1.0f));
	untranslatedViewMatrix = glm::core::function::matrix::transpose(untranslatedViewMatrix);
	viewMatrix = translate(untranslatedViewMatrix, -eyePosition);
		
	// as found in hearn & baker
	float x0 = 1.0f/(tan(extendedAOV/2.0f));
	float y1 = (1.0f/(tan(extendedAOV/2.0f))) * aspectRatio;
	float z2 = (nearPlane + farPlane)/(nearPlane - farPlane);
	float w2 = -1.0f;
	float z3 = (-2.0f * nearPlane * farPlane)/(nearPlane - farPlane);


	projectionMatrix = mat4(x0, 0, 0, 0,
							0, y1, 0, 0, 
							0, 0, z2, w2,
							0, 0, z3, 0);
}

void FilmCamera::tumble(float horizontal, float vertical)
{
	// first horizontally
	vec3 s = glm::normalize(glm::cross(targetVector, upVector));
	targetVector = glm::normalize(targetVector + horizontal * s);

		
	// then vertically
	float eps = 0.9;
	if ((vertical > 0 && targetVector.y < eps) || (vertical < 0 && targetVector.y > -eps))
	{
		targetVector = glm::normalize(targetVector + vertical * upVector);
		upVector = glm::normalize(glm::cross(s, targetVector));
	}
}

void FilmCamera::dolly(vec3 direction)
{
	vec3 s = glm::normalize(glm::cross(targetVector, upVector));
	
	eyePosition += (direction.x * s);
	eyePosition += (direction.y * upVector);
	eyePosition += (direction.z * targetVector);

	//std::cout << "eye position: " << eyePosition.x << "|"<< eyePosition.y << "|"<< eyePosition.z << std::endl;
}


void FilmCamera::setAngleOfView(float radians)
{
	angleOfView = radians;
}

void FilmCamera::setFocalLength(float length)
{
	angleOfView = 2 * atan(35.0 / (2 * length));
}

void FilmCamera::rotate(float radians)
{
	// rotate up vector
	mat4 rotation = glm::gtx::transform::rotate(radians, targetVector);
	vec4 res = rotation * vec4(upVector, 1.0f);
	upVector = vec3(res);
	// std::cout << "up vector: " << upVector.x << " | "<< upVector.y << " | "<< upVector.z << std::endl;
} 

void FilmCamera::setGateInPixel(int _width, int _height)
{
	width = _width;
	height = _height;
}

void FilmCamera::setFilterMarginInPixel(int _horizontalMargin, int _verticalMargin)
{
	horizontalMargin = _horizontalMargin;
	verticalMargin = _verticalMargin;
}

int FilmCamera::getFrameWidth() {
	return width + 2 * horizontalMargin;
}

int FilmCamera::getFrameHeight() {
	return height + 2 * verticalMargin;
}

int FilmCamera::getGateWidth() {
	return width;
}

int FilmCamera::getGateHeight() {
	return height;
}

