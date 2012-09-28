#ifndef KOCMCO_CORE_SCENE_SKYBOX_CAMERA_HPP
#define KOCMCO_CORE_SCENE_SKYBOX_CAMERA_HPP

#include <kocmoc-core/scene/Camera.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class SkyboxCamera : public Camera
			{
			public:
				SkyboxCamera(Camera* _camera)
					: camera(_camera)
				{}
				
				virtual const glm::mat4 getViewMatrix() const
				{
					return camera->getUntraslatedViewMatrix();
				}
				
				virtual const glm::mat4 getProjectionMatrix() const
				{
					return camera->getProjectionMatrix();
				}
				
				virtual const glm::mat4 getUntraslatedViewMatrix() const
				{
					return camera->getUntraslatedViewMatrix();
				}
				
				virtual void updateMatrices()
				{
					camera->updateMatrices();
				}
				
			private:
				Camera* camera;
			};
		}
	}
}

#endif
