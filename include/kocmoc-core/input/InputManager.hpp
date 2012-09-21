#ifndef KOCMOC_CORE_INPUT_MANAGER_HPP
#define KOCMOC_CORE_INPUT_MANAGER_HPP

// symbolic input event constants
#define ANALOG_EVENT_MOUSE_DELTA_X		0
#define ANALOG_EVENT_MOUSE_DELTA_Y		1
#define ANALOG_EVENT_MOUSE_ABSOLUTE_X	2
#define ANALOG_EVENT_MOUSE_ABSOLUTE_Y	3

#define ANALOG_EVENT_LEFT_STICK_X		4
#define ANALOG_EVENT_LEFT_STICK_Y		5
#define ANALOG_EVENT_RIGHT_STICK_X		6
#define ANALOG_EVENT_RIGHT_STICK_Y		7

#define BUTTON_EVENT_XBOX_A				8
#define BUTTON_EVENT_XBOX_B				9
#define BUTTON_EVENT_XBOX_X				9
#define BUTTON_EVENT_XBOX_Y				9
#define BUTTON_EVENT_XBOX_START			10
#define BUTTON_EVENT_XBOX_BACK			11

#define ANALOG_EVENT_LEFT_TRIGGER		12
#define ANALOG_EVENT_RIGHT_TRIGGER		13



#include <map>

#include <kocmoc-core/gl.h>

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/types/types.h>

namespace kocmoc
{
	namespace core
	{
		namespace input
		{
			class ButtonEventListener;
			class AnalogEventListener;
			struct AnalogEvent;
			struct ButtonEvent;
			
			/**
			 * The Input Manager handles input from all devices.
			 *
			 * An event listener can be registered under a certain name. This 
			 * name is then later bound to an actual event.
			 * 
			 * For example:
			 * A button listener is registered under the name "shoot". The name
			 * "shoot" is then bound to the event "left mouse button"
			 * Now whenever the event "left mouse button" occurs all listeners
			 * bound to it are fired.
			 */
			class InputManager
			{
			public:
				
				InputManager(GLFWwindow);
				
				/**
				 * register a button event listener for the given event name
				 */
				void registerButtonEventListener(types::Symbol name, ButtonEventListener* listener);
				
				/**
				 * register an analog event listener for the given even name
				 */
				void registerAnalogEventListener(types::Symbol name, AnalogEventListener* listener);
				
				/**
				 * bind a key to an event. A key kan be bound to multiple events.
				 * @note using glfw3 key kodes for now.
				 */
				void bindKeyToButtonEvent(int key, types::Symbol name);
				
				/**
				 * Bind a gamepad key to a button event
				 * use constants defined above.
				 */
				void bindButtonToButtonEvent(int key, types::Symbol name);
				
				/**
				 * Bind an analog event. An event can be bound to multiple names.
				 */
				void bindAnalogEvent(int analogEventSymbolicConstant, types::Symbol name);
				
				/**
				 * Poll input devices.
				 */
				void poll(void);
				
				/**
				 * dump the bindings over objectif-lune
				 */
				virtual void dumpBindings(void);
				
			protected:
				typedef std::multimap<types::Symbol, ButtonEventListener* > ButtonEventListenerMultiMap;
				typedef std::pair<types::Symbol, ButtonEventListener* > ButtonEventPair;
				typedef std::multimap<int, types::Symbol> KeyButtonEventBindings;
				typedef std::pair<int, types::Symbol > KeyBindingPair;
				
				typedef std::multimap<int, types::Symbol> ButtonButtonEventBindings;
				typedef std::pair<int, types::Symbol > ButtonBindingPair;
				
				typedef std::multimap<types::Symbol, AnalogEventListener* > AnalogEventListenerMultiMap;
				typedef std::pair<types::Symbol, AnalogEventListener* > AnalogEventPair;
				typedef std::multimap<int, types::Symbol> AnalogEventBindings;
				typedef std::pair<int, types::Symbol> AnalogBindingPair;								
				
				ButtonEventListenerMultiMap buttonEventListeners;
				AnalogEventListenerMultiMap analogEventListeners;
				
			private:				
				GLFWwindow windowHandle;
				
				KeyButtonEventBindings buttonEventKeyBindings;
				ButtonButtonEventBindings buttonEventButtonBindings;
				AnalogEventBindings analogEventBindigs;
				
				int mouseX, mouseY;
				
				float gamepadDeadZone;
				
				void notifyAnalogListeners(int analogEventSymbolicConstant, const AnalogEvent& event);
				void notifyButtonListeners(int buttonEventSymbolicConstant, const ButtonEvent& event) const;
			};
		}
	}
}

#endif
