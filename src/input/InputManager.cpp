#include <kocmoc-core/input/InputManager.hpp>

#include <string>

#include <kocmoc-core/input/ButtonEventListener.hpp>

using namespace kocmoc::core::input;
using kocmoc::core::types::Symbol;

InputManager::InputManager(GLFWwindow _windowHandle)
	: windowHandle(_windowHandle)
{
	glfwEnable(windowHandle, GLFW_STICKY_KEYS);
}


void InputManager::registerButtonEventListener(Symbol name, ButtonEventListener *listener)
{
	buttonEventListenerMultiMap.insert(EventPair(name, listener));
}

void InputManager::bindButtonEventToKey(Symbol name, int key)
{
	buttonEventKeyBindings.insert(keyBindingPair(name, key));
}

void InputManager::poll(void)
{
	// for each key
	for (ButtonEventKeyBindings::const_iterator ci = buttonEventKeyBindings.begin();
		 ci != buttonEventKeyBindings.end();
		 ci++)
	{
		// poll key
		if (glfwGetKey(windowHandle, ci->second))
		{
			// fetch listeners
			for(ButtonEventListenerMultiMap::const_iterator listeners = buttonEventListenerMultiMap.find(ci->first);
				listeners != buttonEventListenerMultiMap.end();
				listeners++)
			{
				// fire listener
				ButtonEvent event;
				event.isPressed = true;
				
				(listeners->second)->buttonEventCallback(ci->first, event);
			}
		}
	}
}
