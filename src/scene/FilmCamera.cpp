#include <kocmoc-core/scene/FilmCamera.hpp>

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <glm/gtx/quaternion.hpp>
#pragma GCC diagnostic pop

#include <kocmoc-core/constants.hpp>
#include <kocmoc-core/math/math.hpp>

#include <kocmoc-core/compiler.h>

using namespace kocmoc::core::scene;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

using glm::translate;

FilmCamera::FilmCamera(vec3 _eyePosition, vec3 _targetPosition, vec3 _upVector)	
	: nearPlane(-0.1f)
	, farPlane(-1000.f)
	, angleOfView(constants::pi/2.0f)
	, horizontalMargin(0)
	, verticalMargin(0)
{
	setPosition(_eyePosition);
	lookAt(_targetPosition);
	setUpVector(_upVector);
}

const glm::quat FilmCamera::getOrientation() const
{
	return glm::angleAxis(-90.0f, vec3(1, 0, 0))
		* glm::angleAxis(math::rad2Deg(theta), vec3(1, 0, 0))
		* glm::angleAxis(math::rad2Deg(phi), vec3(0, 0, 1));
}

void FilmCamera::setPosition(vec3 _position)
{
	position = _position;
}


void FilmCamera::lookAt(vec3 target)
{
	UNUSED target;
}

void FilmCamera::setUpVector(vec3 up)
{
	upVector = glm::normalize(up);
}

FilmCamera::~FilmCamera()
{
	// TODO Auto-generated destructor stub
}

const mat4 FilmCamera::getProjectionMatrix() const
{
	return projectionMatrix;
}

const mat4 FilmCamera::getViewMatrix() const
{
	return viewMatrix;
}

const mat4 FilmCamera::getUntraslatedViewMatrix() const
{
	return untranslatedViewMatrix;
}


void FilmCamera::updateMatrices()
{
	// view matrix
	untranslatedViewMatrix = glm::toMat4(getOrientation());
	viewMatrix = translate(untranslatedViewMatrix, -position);
	
	
	// projection matrix
	aspectRatio = (float)getFrameWidth() / (float)getFrameHeight();
	float extendedAOV = (atan(tan(angleOfView / 2) * (((float)width + 2 * horizontalMargin) / width))) * 2;
	
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
	phi += horizontal;
	theta = math::min(constants::pi/2, math::max(-constants::pi/2, theta + vertical));
}

void FilmCamera::dolly(vec3 direction)
{
	mat3 rotation = glm::toMat3(glm::inverse(getOrientation()));
	vec3 delta = rotation * direction;
	
	position += delta;
}


void FilmCamera::setAngleOfView(float radians)
{
	angleOfView = radians;
}

float FilmCamera::getAngleOfView() const
{
	return angleOfView;
}

void FilmCamera::setFocalLength(float length)
{
	angleOfView = 2 * atan(35.0 / (2 * length));
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

int FilmCamera::getFrameWidth() const {
	return width + 2 * horizontalMargin;
}

int FilmCamera::getFrameHeight() const {
	return height + 2 * verticalMargin;
}

int FilmCamera::getGateWidth() const {
	return width;
}

int FilmCamera::getGateHeight() const {
	return height;
}
