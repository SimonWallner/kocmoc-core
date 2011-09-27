#include <kocmoc-core/input/InputManager.hpp>

#include <string>
#include <iostream>

#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/compiler.h>

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
		int key = ci->second;
		UNUSED key;
		
		if (glfwGetKey(windowHandle, (int)ci->second))
		{
//			std::cout << "key pressed: " << (int)ci->second << std::endl;
			
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

void InputManager::dumpBindings()
{
	std::cout << "event to key code bindings:" << std::endl;
	for (ButtonEventKeyBindings::const_iterator ci = buttonEventKeyBindings.begin();
		 ci != buttonEventKeyBindings.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << " --> " << ci->second << " '" << (char) ci->second << "'" << std::endl;
	}
}
