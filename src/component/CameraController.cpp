#include <kocmoc-core/component/CameraController.hpp>

using namespace kocmoc::core::component;
using kocmoc::core::scene::FilmCamera;
using kocmoc::core::input::InputManager;

CameraController::CameraController(FilmCamera* _camera, InputManager* inputManager)
	: kw(this)
	, camera(_camera)
{
	inputManager->registerButtonEventListener(cameraControllerConstants::left, &kw);
	inputManager->bindButtonEventToKey(cameraControllerConstants::left, 65); // A
}

void CameraController::onUpdate(float deltaT)
{
	UNUSED deltaT;
}
