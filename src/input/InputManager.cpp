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
	glfwSetCursorMode(windowHandle, GLFW_CURSOR_HIDDEN);
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
	bool found = false;

	// fetch bindings
	std::pair<KeyButtonEventBindings::const_iterator, KeyButtonEventBindings::const_iterator> bounds =
	buttonEventKeyBindings.equal_range(key);
	
	for (KeyButtonEventBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		if (ci->second == name)
			found = true;
	}
	
	if (found != true)
		buttonEventKeyBindings.insert(KeyBindingPair(key, name));
}

void InputManager::bindAnalogEvent(int eventConstant, Symbol name)
{
	bool found = false;
	
	// fetch bindings
	std::pair<AnalogEventBindings::const_iterator, AnalogEventBindings::const_iterator> bounds =
	buttonEventKeyBindings.equal_range(eventConstant);
	
	for (AnalogEventBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		if (ci->second == name)
			found = true;
	}
	
	if (found != true)
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
			std::pair<ButtonEventListenerMultiMap::const_iterator, ButtonEventListenerMultiMap::const_iterator> bounds =
				buttonEventListeners.equal_range(ci->second);
			
			for (ButtonEventListenerMultiMap::const_iterator listeners = bounds.first;
				listeners != bounds.second;
				listeners++)
			{
				// fire listener
				(listeners->second)->buttonEventCallback(ci->second, ButtonEvent(ButtonEvent::HELD));
			}
		}
	}
	
	// poll mouse
	int newMouseX;
	int newMouseY;
	glfwGetMousePos(windowHandle, &newMouseX, &newMouseY);
	
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_ABSOLUTE_X, AnalogEvent(newMouseX));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_ABSOLUTE_Y, AnalogEvent(newMouseY));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_DELTA_X, AnalogEvent(newMouseX - mouseX));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_DELTA_Y, AnalogEvent(newMouseY - mouseY));
	
	mouseX = newMouseX;
	mouseY = newMouseY;
}

void InputManager::notifyAnalogListeners(int analogEventSymbolicConstant, const AnalogEvent& event)
{
	// constant --> symbol
	std::pair<AnalogEventBindings::const_iterator, AnalogEventBindings::const_iterator> bounds = 
		analogEventBindigs.equal_range(analogEventSymbolicConstant);
	
	for (AnalogEventBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		// symbol --> listener
		std::pair<AnalogEventListenerMultiMap::const_iterator, AnalogEventListenerMultiMap::const_iterator> bounds2 = 
			analogEventListeners.equal_range(ci->second);
		
		for (AnalogEventListenerMultiMap::const_iterator listeners = bounds2.first;
			 listeners != bounds2.second;
			 listeners++)
		{
			(listeners->second)->analogEventCallback(ci->second, event);
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
	
	std::cout << "analog bindings: " << std::endl;
	for (AnalogEventBindings::const_iterator ci = analogEventBindigs.begin();
		 ci != analogEventBindigs.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << " --> " << ci->second << std::endl;
	}	
	
	std::cout << "analog callbacks:" << std::endl;
	for (AnalogEventListenerMultiMap::const_iterator ci = analogEventListeners.begin();
		 ci != analogEventListeners.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << " --> " << ci->second << std::endl;
	}	
}
