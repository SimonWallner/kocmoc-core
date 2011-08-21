#include <kocmoc-core/input/InputManager.hpp>

#include <GL/glfw3.h>

using namespace kocmoc::core::input;


void InputManager::addKeyboardListener(KeyboardListener *listener)
{
	keyboardListenerList.push_back(listener);
}

void InputManager::poll(void)
{
	
}