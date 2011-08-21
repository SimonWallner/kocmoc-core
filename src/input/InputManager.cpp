#include <kocmoc-core/input/InputManager.hpp>
#include <GL/glfw3>

using namespace kocmoc::core::input;

InputManager& InputManager::GetInstance(void)
{
	static InputManager instance;
	return instance;
}


void InputManager::addKeyboardListener(KeyboardListener *listener)
{
	keyboardListenerList.push_back(listener);
}

void InputManager::poll(void)
{
	
}