#include <kocmoc-core/input/InputManager.hpp>

#include <kocmoc-core/input/KeyboardListener.hpp>

#include <string>

using namespace kocmoc::core::input;

InputManager::InputManager(GLFWwindow _windowHandle)
	: windowHandle(_windowHandle)
{
}


void InputManager::addKeyboardListener(KeyboardListener *listener)
{
	keyboardListenerList.push_back(listener);
}

void InputManager::poll(void)
{
	;
}


