#include <kocmoc-core/input/InputManager.hpp>

#include <string>
#include <iostream>

#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/input/AnalogEventListener.hpp>
#include <kocmoc-core/compiler.h>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::input;
using kocmoc::core::types::Symbol;

InputManager::InputManager(GLFWwindow _windowHandle)
	: windowHandle(_windowHandle)
	, mouseX(0)
	, mouseY(0)
	, gamepadDeadZone(0.2f)
{
	glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(windowHandle, GLFW_CURSOR_MODE, GLFW_CURSOR_HIDDEN);
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

void InputManager::bindButtonToButtonEvent(int button, Symbol name)
{
	bool found = false;
	
	// fetch bindings
	std::pair<ButtonButtonEventBindings::const_iterator, ButtonButtonEventBindings::const_iterator>
		bounds = buttonEventButtonBindings.equal_range(button);
	
	for (ButtonButtonEventBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		if (ci->second == name)
			found = true;
	}
	
	if (found != true)
		buttonEventButtonBindings.insert(KeyBindingPair(button, name));
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
	glfwGetCursorPos(windowHandle, &newMouseX, &newMouseY);
	
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_ABSOLUTE_X, AnalogEvent(newMouseX));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_ABSOLUTE_Y, AnalogEvent(newMouseY));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_DELTA_X, AnalogEvent(newMouseX - mouseX));
	notifyAnalogListeners(ANALOG_EVENT_MOUSE_DELTA_Y, AnalogEvent(newMouseY - mouseY));
	
	mouseX = newMouseX;
	mouseY = newMouseY;
	
	
	// poll all gamepads
	for (int i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwGetJoystickParam(i, GLFW_PRESENT) == GL_TRUE)
		{
			unsigned int numButtons = glfwGetJoystickParam(i, GLFW_BUTTONS);
			unsigned int numAxes = glfwGetJoystickParam(i, GLFW_AXES);
			
			/*
			 * 360 gamepad assignment: (direction given for positive values) / OSX Mountain Lion, glfw3 pre
			 * - [0]: left stick right
			 * - [1]: left stick up
			 * - [2]: right stick up
			 * - [3]: right stick right
			 * - [4]: left trigger [-1, 1]
			 * - [5]: right trigger [1, -1]
			 */

			GLfloat *pos = new GLfloat[numAxes];
			glfwGetJoystickAxes(i, pos, numAxes);
			
			if (abs(pos[0]) > gamepadDeadZone) // left stick right
				notifyAnalogListeners(ANALOG_EVENT_LEFT_STICK_X, AnalogEvent(pos[0]));
			
			if (abs(pos[1]) > gamepadDeadZone) // left stick up
				notifyAnalogListeners(ANALOG_EVENT_LEFT_STICK_Y, AnalogEvent(pos[1]));
			
			if (abs(pos[2]) > gamepadDeadZone) // right stick up
				notifyAnalogListeners(ANALOG_EVENT_RIGHT_STICK_X, AnalogEvent(pos[3]));
			
			if (abs(pos[3]) > gamepadDeadZone) // right stick right
				notifyAnalogListeners(ANALOG_EVENT_RIGHT_STICK_Y, AnalogEvent(pos[4]));
			
			if (abs(pos[4]) > gamepadDeadZone) // left trigger
				notifyAnalogListeners(ANALOG_EVENT_RIGHT_STICK_Y, AnalogEvent((pos[4] / 2.0) + 0.5f));
			
			if (abs(pos[5]) > gamepadDeadZone) // right stick right
				notifyAnalogListeners(ANALOG_EVENT_RIGHT_STICK_Y, AnalogEvent((pos[4] / -2.0f) + 0.5f));
			
//			for (unsigned int i = 0; i < numAxes; i++)
//			{
//				std::cout << "axis " << i << ": " << (pos[i]) << std::endl;
//			}
//			std::cout << "===================" << std::endl;
			
			delete [] pos;
			
			
			/*
			 * Button assignment 360 gamepad / OSX Mountain Lion, glfw3 pre
			 * [0]: d-up
			 * [1]: d-down
			 * [2]: d-left
			 * [3]: d-right
			 * [4]: start
			 * [5]: back
			 * [6]: left stick
			 * [7]: right stick
			 * [8]: bumper left
			 * [9]: bumper right
			 * [10]: XBox 
			 * [11]: A
			 * [12]: B
			 * [13]: X
			 * [14]: Y
			 */

			unsigned char *buttons = new unsigned char[numButtons];
			glfwGetJoystickButtons(i, buttons, numButtons);
			
			if (buttons[11] == GLFW_PRESS)
				notifyButtonListeners(BUTTON_EVENT_XBOX_A, ButtonEvent(ButtonEvent::HELD));
			
			if (buttons[12] == GLFW_PRESS)
				notifyButtonListeners(BUTTON_EVENT_XBOX_B, ButtonEvent(ButtonEvent::HELD));
			
			if (buttons[13] == GLFW_PRESS)
				notifyButtonListeners(BUTTON_EVENT_XBOX_X, ButtonEvent(ButtonEvent::HELD));
			
			if (buttons[14] == GLFW_PRESS)
				notifyButtonListeners(BUTTON_EVENT_XBOX_Y, ButtonEvent(ButtonEvent::HELD));
			
			if (buttons[6] == GLFW_PRESS)
				notifyButtonListeners(BUTTON_EVENT_XBOX_START, ButtonEvent(ButtonEvent::HELD));
			
			if (buttons[5] == GLFW_PRESS)
				notifyButtonListeners(BUTTON_EVENT_XBOX_BACK, ButtonEvent(ButtonEvent::HELD));
			
//			for (unsigned int i = 0; i < numButtons; i++)
//			{
//				std::cout << "button " << i << ": " << (buttons[i] == GLFW_PRESS) << std::endl;
//			}
//			std::cout << "===================" << std::endl;
			
			delete [] buttons;
		}
	}
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

void InputManager::notifyButtonListeners(int buttonEventSymbolicConstant, const ButtonEvent& event) const
{
	// constant --> symbol
	std::pair<ButtonButtonEventBindings::const_iterator, ButtonButtonEventBindings::const_iterator>
		bounds = buttonEventButtonBindings.equal_range(buttonEventSymbolicConstant);
	
	for (ButtonButtonEventBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		// symbol --> listener
		std::pair<ButtonEventListenerMultiMap::const_iterator, ButtonEventListenerMultiMap::const_iterator>
			bounds2 = buttonEventListeners.equal_range(ci->second);
		
		for (ButtonEventListenerMultiMap::const_iterator listeners = bounds2.first;
			 listeners != bounds2.second;
			 listeners++)
		{
			(listeners->second)->buttonEventCallback(ci->second, event);
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

