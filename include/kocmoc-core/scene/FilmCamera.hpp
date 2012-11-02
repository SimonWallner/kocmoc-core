/*
 * A basic camera modelled after a real 35mm camera.
 */

#ifndef KOCMOC_CORE_SCENE_FILM_CAMERA_HPP
#define KOCMOC_CORE_SCENE_FILM_CAMERA_HPP

#include <kocmoc-core/scene/Camera.hpp>

#include <glm/gtc/quaternion.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{

			/**
			 * Implementation of a basic film camera
			 * @note a right-handed coordinate system is used throughout the whole 
			 * application. This is in sync with both opengl.
			 */
			class FilmCamera : public Camera
			{
			public:
				/**
				 * Construct a new camera from the given params
				 * @param eyePosition The point from where the camera looks into the
				 * scene
				 * @param targetPosition The point the camera looks at
				 * @param upVector the up-vector of the camera
				 */
				FilmCamera(glm::vec3 eyePosition, glm::vec3 targetPosition, glm::vec3 upVector);
				virtual ~FilmCamera();

				void setPosition(glm::vec3 position);
				void setUpVector(glm::vec3 up);
				void lookAt(glm::vec3 target);


				/**
				 * Set the film gate in pixel
				 * Set the film gate to specific size in pixels. This will most likely be the
				 * final output resolution, or the visual area in a letterboxed output.
				 * @param width The width of the gate
				 * @param height The height of the gate
				 */
				void setGateInPixel(int width, int height);

				/**
				 * The filter margin of the camera.
				 * A field wider than the final gate is rendered to provide some
				 * margin for post processing filters.
				 */
				void setFilterMarginInPixel(int horizontalMargin, int verticalMargin);

				int getFrameWidth() const;
				int getFrameHeight() const;
				int getGateWidth() const;
				int getGateHeight() const;

				/**
				 * Set the 35mm equivalent focal length of the lens. This should be
				 * calculated for the visible area i.e. the gate.
				 * @param The focal length as it would be in a standard 35mm film camera.
				 */
				void setFocalLength(float mm);

				/**
				 * The counterpart to setFocalLength. Directly set the horizontal AOV
				 * @param radians The horizontal AOV in radians.
				 */
				void setAngleOfView(float radians);
				float getAngleOfView() const;

				// override fuctions from camera
				const glm::mat4 getViewMatrix() const;
				const glm::mat4 getProjectionMatrix() const;
				const glm::mat4 getUntraslatedViewMatrix() const;
				
				/** Update all matrices from the current camera parameters.
				 * Effects of tumble(), dolly(), ... are only visible after
				 * this call.
				 */
				void updateMatrices();

				const glm::vec3 getPosition() const { return position; }
				const glm::quat getOrientation() const;


				/**
				 * Tumble the camera around the eye position. unit = radians
				 * @param vertical The vertical rotation
				 * @param horizontal The horizontal rotation
				 */
				void tumble(float horizontal, float vertical);

				/**
				 * translate the camera. i.e. the postion and the target
				 * The camera uses the standard OpenGL right handed coordinate
				 * system. 
				 *
				 * |+Y
				 * |
				 * |
				 * |  /-Z
				 * | /
				 * |/______________ +X
				 */
				void dolly(glm::vec3 direction);
				
				glm::mat4 getTransformation() const;

			private:
				/** The position of the camera/eye */
				glm::vec3 position;
				glm::vec3 upVector;
				
				/** horizontal rotation in radians */
				float phi;
				
				/** vertical rotation in radians */
				float theta;
				
				
				glm::mat4 viewMatrix;

				/** this is for the skybox and things alike */
				glm::mat4 untranslatedViewMatrix;
				glm::mat4 projectionMatrix;


				/** Near plane and far plane as seen from the camera, i.e. negative
				 * values, as we have a right-handed coordinate system and look down
				 * the negative z-axis. */
				float nearPlane;
				float farPlane;

				/** The aspect ration of the camera */
				float aspectRatio;

				/** The horizontal angle of view in radians */
				float angleOfView;
				
				/** the width and height of the gate. */
				int width;
				int height;

				/** horizontal and vertical filter margin */
				int horizontalMargin;
				int verticalMargin;
			};
		}
	}
}

#endif
