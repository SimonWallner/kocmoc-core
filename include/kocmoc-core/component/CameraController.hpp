#ifndef KOCMOC_CORE_COMPONENT_CAMERA_CONTROLLER_HPP
#define KOCMOC_CORE_COMPONENT_CAMERA_CONTROLLER_HPP

#include <iostream>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/scene/FilmCamera.hpp>

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
				CameraController(scene::FilmCamera* _camera, input::InputManager* inputManager);

				
				void onUpdate(float deltaT);
				
			private:
				
				class KeyWatcher : public core::input::ButtonEventListener
				{
				public:
					KeyWatcher(CameraController* _p)
						: p(_p)
					{}
					
					void buttonEventCallback(types::Symbol name, input::ButtonEvent event);
					
				private:
					CameraController* p;
				} kw;
				
				scene::FilmCamera* camera;

				types::Symbol left, right, up, down;

				float lastDeltaT;
			};
		}
	}
}



#endif