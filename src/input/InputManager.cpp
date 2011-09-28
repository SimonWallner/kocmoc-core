#include <kocmoc-core/input/InputManager.hpp>

#include <string>
#include <iostream>

#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/input/AnalogEventListener.hpp>
#include <kocmoc-core/compiler.h>

using namespace kocmoc::core::input;
using kocmoc::core::types::Symbol;

InputManager::InputManager(GLFWwindow _windowHandle)
	: windowHandle(_windowHandle)
	, mouseX(0)
	, mouseY(0)
{
	glfwEnable(windowHandle, GLFW_STICKY_KEYS);
}


void InputManager::registerButtonEventListener(Symbol name, ButtonEventListener* listener)
{
	buttonEventListeners.insert(ButtonEventPair(name, listener));
}

void InputManager::registerAnalogEventListener(Symbol name, AnalogEventListener* listener)
{
	analogEventListeners.insert(AnalogEventPair(name, listener));
}

void InputManager::bindKeyToButtonEvent(int key, Symbol name)
{
	buttonEventKeyBindings.insert(KeyBindingPair(key, name));
}

void InputManager::bindAnalogEvent(int eventConstant, Symbol name)
{
	analogEventBindigs.insert(AnalogBindingPair(eventConstant, name));
}

void InputManager::poll(void)
{
	// for each key
	for (KeyButtonEventBindings::const_iterator ci = buttonEventKeyBindings.begin();
		 ci != buttonEventKeyBindings.end();
		 ci++)
	{
		// poll key
		if (glfwGetKey(windowHandle, (int)ci->first))
		{
			// fetch listeners
			for(ButtonEventListenerMultiMap::const_iterator listeners = buttonEventListeners.find(ci->second);
				listeners != buttonEventListeners.end();
				listeners++)
			{
				// fire listener
				ButtonEvent event;
				event.isPressed = true;
				
				(listeners->second)->buttonEventCallback(ci->second, event);
			}
		}
	}
	
	// poll mouse
	int newMouseX, newMouseY;
	glfwGetMousePos(windowHandle, &newMouseX, &newMouseY);
	double deltaX = (double)newMouseX - (double)mouseX;
	double deltaY = (double)newMouseY - (double)mouseY;
	
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_ABSOLUTE_X, AnalogEvent(newMouseX));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_ABSOLUTE_Y, AnalogEvent(newMouseY));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_DELTA_X, AnalogEvent(deltaX));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_DELTA_Y, AnalogEvent(deltaY));
	
	mouseX = newMouseX;
	mouseY = newMouseY;
}

void InputManager::notifyAnalogListeners(int analogEventSymbolicConstant, const AnalogEvent& event)
{
	for (AnalogEventBindings::const_iterator ci = analogEventBindigs.find(analogEventSymbolicConstant);
		 ci != analogEventBindigs.end();
		 ci++)
	{
		for (AnalogEventListenerMultiMap::const_iterator ci2 = analogEventListeners.find(ci->second);
			 ci2 != analogEventListeners.end();
			 ci2++)
		{
			(ci2->second)->analogEventCallback(ci->second, event);
		}
	}
}

void InputManager::dumpBindings()
{
	std::cout << "event to key code bindings:" << std::endl;
	for (KeyButtonEventBindings::const_iterator ci = buttonEventKeyBindings.begin();
		 ci != buttonEventKeyBindings.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << "(" << (char) ci->first << ") --> " << ci->second << std::endl;
	}
}
