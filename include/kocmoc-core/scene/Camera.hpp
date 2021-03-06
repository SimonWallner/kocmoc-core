#ifndef KOCMOC_CORE_CAMERA_HPP
#define KOCMOC_CORE_CAMERA_HPP

#include <glm/glm.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class Shader;
		}
		
		namespace scene
		{
			/**
			 * Abstract camera class
			 */
			class Camera
			{
			public:
				
				/** 
				 * Get the view matrix of this camera
				 * @return the view matrix of the camera
				 */
				virtual const glm::mat4 getViewMatrix() const = 0;
				
				/**
				 * Get the projection matrix of this camera
				 */
				virtual const glm::mat4 getProjectionMatrix() const = 0;
				
				/**
				 * Get the untranslated view matrix that only reflects the viewing
				 * direction. made for the skybox.
				 * @return the untranslated view matrix
				 */
				virtual const glm::mat4 getUntraslatedViewMatrix() const = 0;
				
				/**
				 * Get the position of the camera in world space
				 */
				virtual const glm::vec3 getPosition() const { return glm::vec3(0.0f); };
				
				/**
				 * Update the view matrix of this camera with the current values. 
				 * You should call this method at the beginning of every frame. Camera
				 * parameters (eyePsition, targetPosition, etc.) my change during a 
				 * frame due to user inputs, but the viewMatrix remains constant until
				 * \c updateViewMatrix() is called.
				 *
				 * Also updates the untranslated view Matrix.
				 */
				virtual void updateMatrices() = 0;
			};
		}
	}
}
#endif
