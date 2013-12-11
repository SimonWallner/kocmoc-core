#include <kocmoc-core/input/InputManager.hpp>

#include <string>
#include <iostream>

#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/input/AnalogEventListener.hpp>
#include <kocmoc-core/compiler.h>
#include <kocmoc-core/util/util.hpp>

#include <kocmoc-core/math/math.hpp>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core;
using namespace input;
using kocmoc::core::types::Symbol;


InputManager::InputManager(GLFWwindow _windowHandle)
	: windowHandle(_windowHandle)
	, mouseX(0)
	, mouseY(0)
	, gamepadDeadZone(0.2f)
{
	glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(windowHandle, GLFW_CURSOR_MODE, GLFW_CURSOR_HIDDEN);
	
	for (unsigned int i = 0; i < 16; i++) {
		buttonWasPressed[i] = false;
	}
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
			 * with extra gamepad driver
			 * - [0]: left stick right
			 * - [1]: left stick up
			 * - [2]: right stick up
			 * - [3]: right stick right
			 * - [4]: left trigger [-1, 1]
			 * - [5]: right trigger [1, -1]
			 */

			GLfloat *pos = new GLfloat[numAxes];
			glfwGetJoystickAxes(i, pos, numAxes);
			
			// left stick right
			notifyAnalogListeners(ANALOG_EVENT_LEFT_STICK_X,
								  AnalogEvent(math::deadZone(gamepadDeadZone, pos[0])));
			
			// left stick up
			notifyAnalogListeners(ANALOG_EVENT_LEFT_STICK_Y,
								  AnalogEvent(math::deadZone(gamepadDeadZone, pos[1])));
			
			// right stick up
			notifyAnalogListeners(ANALOG_EVENT_RIGHT_STICK_X,
								  AnalogEvent(math::deadZone(gamepadDeadZone, pos[2])));
			
			// right stick right
			notifyAnalogListeners(ANALOG_EVENT_RIGHT_STICK_Y,
								  AnalogEvent(math::deadZone(gamepadDeadZone, pos[3])));
			
			// left trigger
			notifyAnalogListeners(ANALOG_EVENT_LEFT_TRIGGER,
								  AnalogEvent(math::deadZone(gamepadDeadZone, (pos[4] / 2.0f) + 0.5f)));
			
			// right stick right
			notifyAnalogListeners(ANALOG_EVENT_RIGHT_TRIGGER,
								  AnalogEvent(math::deadZone(gamepadDeadZone, (pos[5] / -2.0f) + 0.5f)));
			
//			for (unsigned int i = 0; i < numAxes; i++)
//			{
//				objectifLune::Singleton::Get()->scalar("gamepad axis: " + i, pos[i]);
//			}
			
			delete [] pos;
			
			
			/*
			 * Button assignment 360 gamepad / OSX Mountain Lion, glfw3 pre
			 * with extra gamepad driver
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
			
			
			handleButtonState(buttons[11], buttonWasPressed[11], BUTTON_EVENT_XBOX_A);
			handleButtonState(buttons[12], buttonWasPressed[12], BUTTON_EVENT_XBOX_B);
			handleButtonState(buttons[13], buttonWasPressed[13], BUTTON_EVENT_XBOX_X);
			handleButtonState(buttons[14], buttonWasPressed[14], BUTTON_EVENT_XBOX_Y);
			handleButtonState(buttons[4], buttonWasPressed[4], BUTTON_EVENT_XBOX_START);
			handleButtonState(buttons[5], buttonWasPressed[5], BUTTON_EVENT_XBOX_BACK);

			handleButtonState(buttons[0], buttonWasPressed[0], BUTTON_EVENT_XBOX_DPAD_UP);
			handleButtonState(buttons[1], buttonWasPressed[1], BUTTON_EVENT_XBOX_DPAD_DOWN);
			handleButtonState(buttons[2], buttonWasPressed[2], BUTTON_EVENT_XBOX_DPAD_LEFT);
			handleButtonState(buttons[3], buttonWasPressed[3], BUTTON_EVENT_XBOX_DPAD_RIGHT);

		
//			for (unsigned int i = 0; i < numButtons; i++)
//			{
//				if (buttons[i] == GLFW_PRESS)
//					objectifLune::Singleton::Get()->scalar("button ", i);
//			}
			
			delete [] buttons;
		}
	}
}

void InputManager::handleButtonState(unsigned char buttonState, bool& wasPressed, int buttonSymbolicConstant)
{
	if (buttonState == GLFW_PRESS && !wasPressed) // button pressed
	{
		notifyButtonListeners(buttonSymbolicConstant, ButtonEvent(ButtonEvent::PRESSED));
		wasPressed = true;
	}
	else if (buttonState == GLFW_RELEASE && wasPressed) // button released
	{
		notifyButtonListeners(buttonSymbolicConstant, ButtonEvent(ButtonEvent::RELEASED));
		wasPressed = false;
	}
	
	if (buttonState == GLFW_PRESS) // button held
	{
		notifyButtonListeners(buttonSymbolicConstant, ButtonEvent(ButtonEvent::HELD));
	}
}

void InputManager::notifyAnalogListeners(int analogEventSymbolicConstant, const AnalogEvent& event)
{
//	static unsigned int cnt = 0;
//	objectifLune::Singleton::Get()->data(cnt++, util::toString(analogEventSymbolicConstant),
//										   event.value);
	
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

void InputManager::captureMouse()
{
	glfwSetInputMode(windowHandle, GLFW_CURSOR_MODE, GLFW_CURSOR_CAPTURED);
}

