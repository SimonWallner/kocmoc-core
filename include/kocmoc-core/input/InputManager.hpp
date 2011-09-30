#ifndef KOCMOC_CORE_INPUT_MANAGER_HPP
#define KOCMOC_CORE_INPUT_MANAGER_HPP

// symbolic input event constants
#define ANALOG_EVENT_MOUSE_DELTA_X		0
#define ANALOG_EVENT_MOUSE_DELTA_Y		1
#define ANALOG_EVENT_MOUSE_ABSOLUTE_X	2
#define ANALOG_EVENT_MOUSE_ABSOLUTE_Y	3


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
				 * Bind an analog event. An event can be bound to multiple names.
				 */
				void bindAnalogEvent(int analogEventSymbolicConstant, types::Symbol name);
				
				/**
				 * Poll input devices.
				 */
				void poll(void);
				
				/**
				 * dump the bindings to std::out
				 */
				void dumpBindings(void);
				
			private:
				
				typedef std::multimap<types::Symbol, ButtonEventListener* > ButtonEventListenerMultiMap;
				typedef std::pair<types::Symbol, ButtonEventListener* > ButtonEventPair;
				typedef std::multimap<int, types::Symbol> KeyButtonEventBindings;
				typedef std::pair<int, types::Symbol > KeyBindingPair;
				
				typedef std::multimap<types::Symbol, AnalogEventListener* > AnalogEventListenerMultiMap;
				typedef std::pair<types::Symbol, AnalogEventListener* > AnalogEventPair;
				typedef std::multimap<int, types::Symbol> AnalogEventBindings;
				typedef std::pair<int, types::Symbol> AnalogBindingPair;
				
				
				GLFWwindow windowHandle;
				
				ButtonEventListenerMultiMap buttonEventListeners;
				KeyButtonEventBindings buttonEventKeyBindings;
				
				AnalogEventListenerMultiMap analogEventListeners;
				AnalogEventBindings analogEventBindigs;
				
				int mouseX, mouseY;
				
				void notifyAnalogListeners(int AnalogEventSymbolicConstant, const AnalogEvent& event);
			};
		}
	}
}

#endif
