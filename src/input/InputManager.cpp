#include <kocmoc-core/input/InputManager.hpp>

#include <kocmoc-core/input/KeyboardListener.hpp>

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
	int keys[6] = {GLFW_KEY_ESCAPE, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_W};
	
	for (unsigned int i = 0; i < 6; i++)
	{
		if (glfwGetKey(windowHandle, keys[i]) == GLFW_KEY_DOWN)
		{
			for (KeyboardListenerList::iterator it = keyboardListenerList.begin(); it != keyboardListenerList.end(); it++)
			{
				(*it).keyPressed(keys[i]);
			}
		}
	}
}


