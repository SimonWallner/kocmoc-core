#ifndef KOCMOC_CORE_COMPONENT_CAMERA_CONTROLLER_HPP
#define KOCMOC_CORE_COMPONENT_CAMERA_CONTROLLER_HPP

#include <iostream>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/input/AnalogEventListener.hpp>
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

				void onUpdate(const float deltaT, const float t);
				
			private:
				class InputCallback : public core::input::ButtonEventListener, public core::input::AnalogEventListener
				{
				public:
					InputCallback(CameraController* _p)
						: p(_p)
					{}
					
					void buttonEventCallback(types::Symbol name, input::ButtonEvent event);
					void analogEventCallback(types::Symbol name, input::AnalogEvent event);
					
				private:
					CameraController* p;
				} ic;
				
				
				scene::FilmCamera* camera;

				types::Symbol left, right, up, down, mouseTumbleH, mouseTumbleV;

				float lastDeltaT;
			};
		}
	}
}



#endif
