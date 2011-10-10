#ifndef KOCMOC_CORE_SCENE_ORTHO_CAMERA_HPP
#define KOCMOC_CORE_SCENE_ORTHO_CAMERA_HPP

#include <kocmoc-core/scene/Camera.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			
			class OrthoCamera : public Camera
			{
			public:
				/**
				 * Construct a orthographic camera with a focus point
				 * and a direction. The focus point is the center of the
				 * viewing cube, and the direction is the direction of the
				 * view vector from eye towards focus.
				 */
				OrthoCamera(glm::vec3 focus, glm::vec3 direction, glm::vec3 upVector);
				~OrthoCamera(void);
				
				/**
				 * set the size of the viewing cube in world space
				 */
				void setWidthHeightDepth(float _width, float _height, float _depth)
				{
					width = _width;
					height = _height;
					depth = _depth;
				}
				
				// override fuctions from camera
				const glm::mat4 getViewMatrix() {return viewMatrix;}
				const glm::mat4 getProjectionMatrix() {return projectionMatrix;}
				const glm::mat4 getUntraslatedViewMatrix(){return glm::mat4(1);}
				void updateMatrixes();
				
				void setFocus(glm::vec3 focus);
				
			private:
				glm::vec3 focus;
				glm::vec3 direction;
				glm::vec3 upVector;
				float width;
				float height;
				float depth;
				
				glm::mat4 viewMatrix;
				glm::mat4 projectionMatrix;
			};
		}
	}
}

#endif
