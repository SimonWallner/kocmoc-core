#include <kocmoc-core/component/CameraController.hpp>

using namespace kocmoc::core::component;
using kocmoc::core::scene::FilmCamera;
using kocmoc::core::input::InputManager;

CameraController::CameraController(FilmCamera* _camera, InputManager* inputManager)
	: ic(this)
	, camera(_camera)
	, left(types::symbolize("left"))
	, right(types::symbolize("right"))
	, up(types::symbolize("up"))
	, down(types::symbolize("down"))
	, mouseTumbleH(types::symbolize("mouseTumbleH"))
	, mouseTumbleV(types::symbolize("mouseTumbleV"))
	, lastDeltaT(0.0f)
{
	inputManager->registerButtonEventListener(left, &ic);
	inputManager->bindKeyToButtonEvent('A', left); // A
	inputManager->bindKeyToButtonEvent(263, left); // left

	inputManager->registerButtonEventListener(right, &ic);
	inputManager->bindKeyToButtonEvent('D', right); // D
	inputManager->bindKeyToButtonEvent(262, right); // right
	
	inputManager->registerButtonEventListener(up, &ic);
	inputManager->bindKeyToButtonEvent('W', up); // W
	inputManager->bindKeyToButtonEvent(265, up); // up
	
	inputManager->registerButtonEventListener(down, &ic);
	inputManager->bindKeyToButtonEvent('S', down); // S
	inputManager->bindKeyToButtonEvent(264, down); // down
	
	// mouse controls
	inputManager->registerAnalogEventListener(mouseTumbleH, &ic);
	inputManager->bindAnalogEvent(ANALOG_EVENT_MOUSE_DELTA_X, mouseTumbleH);
	inputManager->registerAnalogEventListener(mouseTumbleV, &ic);
	inputManager->bindAnalogEvent(ANALOG_EVENT_MOUSE_DELTA_Y, mouseTumbleV);
}

void CameraController::onUpdate(const float deltaT)
{
	lastDeltaT = deltaT;
}

void CameraController::InputCallback::buttonEventCallback(types::Symbol name, input::ButtonEvent event)
{
	if (name == p->left && event.isPressed == true)
		p->camera->dolly(glm::vec3(-1.0f * p->lastDeltaT, 0, 0));
	else if (name == p->right && event.isPressed == true)
		p->camera->dolly(glm::vec3(+1.0f * p->lastDeltaT, 0, 0));
	else if (name == p->up && event.isPressed == true)
		p->camera->dolly(glm::vec3(0, 0, +1.0f * p->lastDeltaT));
	else if (name == p->down && event.isPressed == true)
		p->camera->dolly(glm::vec3(0, 0, -1.0f * p->lastDeltaT));
}

void CameraController::InputCallback::analogEventCallback(types::Symbol name, input::AnalogEvent event)
{
	if (name == p->mouseTumbleH)
		p->camera->tumble(event.value*0.001f, 0.0f);
	else if (name == p->mouseTumbleV)
		p->camera->tumble(0.0f, event.value*-0.001f);
}
