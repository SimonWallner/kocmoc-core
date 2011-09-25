#include <kocmoc-core/component/CameraController.hpp>

using namespace kocmoc::core::component;
using kocmoc::core::scene::FilmCamera;
using kocmoc::core::input::InputManager;

CameraController::CameraController(FilmCamera* _camera, InputManager* inputManager)
	: kw(this)
	, camera(_camera)
	, left(types::symbolize("left"))
	, right(types::symbolize("right"))
	, up(types::symbolize("up"))
	, down(types::symbolize("down"))
{
	inputManager->registerButtonEventListener(left, &kw);
	inputManager->bindButtonEventToKey(left, 'A'); // A
	inputManager->bindButtonEventToKey(left, 263); // left

	inputManager->registerButtonEventListener(right, &kw);
	inputManager->bindButtonEventToKey(right, 'D'); // D
	inputManager->bindButtonEventToKey(right, 262); // right
	
	inputManager->registerButtonEventListener(up, &kw);
	inputManager->bindButtonEventToKey(up, 'W'); // W
	inputManager->bindButtonEventToKey(up, 265); // up
	
	inputManager->registerButtonEventListener(down, &kw);
	inputManager->bindButtonEventToKey(down, 'S'); // S
	inputManager->bindButtonEventToKey(down, 264); // down
}

void CameraController::onUpdate(float deltaT)
{
	UNUSED deltaT;
}

void CameraController::KeyWatcher::buttonEventCallback(types::Symbol name, input::ButtonEvent event)
{
	if (name == p->left && event.isPressed == true)
		p->camera->dolly(glm::vec3(-0.01, 0, 0));
	else if (name == p->right && event.isPressed == true)
		p->camera->dolly(glm::vec3(+0.01, 0, 0));
	else if (name == p->up && event.isPressed == true)
		p->camera->dolly(glm::vec3(0, 0, -0.01));
	else if (name == p->down && event.isPressed == true)
		p->camera->dolly(glm::vec3(0, 0, +0.01));
}