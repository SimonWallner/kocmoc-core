#ifndef KOCMOC_CORE_COMPONENT_CAMERA_CONTROLLER_HPP
#define KOCMOC_CORE_COMPONENT_CAMERA_CONTROLLER_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			/**
			 * Camera controller class that takes user input and moves the camera
			 * accordingly.
			 */
			class CameraController : public componentSystem::Component
			{
			public:
				CameraController(scene::Camera* _camera)
					: camera(_camera)
				{};
				
				void onUpdate(float deltaT);
				
			private:
				
				class KeyWatcher : public core::input::ButtonEventListener
				{
				public:
					KeyWatcher(CameraController* _p)
					: p(_p)
					{};
					
					void buttonEventCallback(core::types::Symbol name, core::input::ButtonEvent event)
					{
						if (name == types::symbolize("left") && event.isPressed == true)
//							p->camera
					}
				private:
					CameraController* p;
				} kw;
				
				scene::Camera* camera;
			};
		}
	}
}



#endif