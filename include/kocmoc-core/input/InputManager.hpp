#ifndef KOCMOC_CORE_INPUT_MANAGER_HPP
#define KOCMOC_CORE_INPUT_MANAGER_HPP

#define ANALOG_EVENT_MOUSE_X 0
#define ANALOG_EVENT_MOUSE_Y 1


#include <map>

#include <GL/glfw3.h>

#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace input
		{
			class ButtonEventListener;
			class AnalogEventListener;
			
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
				
				void registerButtonEventListener(types::Symbol name, ButtonEventListener* listener);
				
				void registerAnalogEventListener(types::Symbol name, AnalogEventListener* listener);
				
				void bindButtonEventToKey(types::Symbol name, int key);
				
				void bindAnalogEventToMouse(types::Symbol name, int analogEventSymbolicConstant);
				
				void poll(void);
				
				/**
				 * dump the bindings to std::out
				 */
				void dumpBindings(void);
				
			private:
				
				typedef std::pair<types::Symbol, ButtonEventListener*> ButtonEventPair;
				typedef std::pair<types::Symbol, int> keyBindingPair;
				typedef std::multimap<types::Symbol, ButtonEventListener*> ButtonEventListenerMultiMap;
				typedef std::multimap<types::Symbol, int> ButtonEventKeyBindings;
				
				// TODO add analog events, ftw!
				
				GLFWwindow windowHandle;
				
				ButtonEventListenerMultiMap buttonEventListenerMultiMap;
				ButtonEventKeyBindings buttonEventKeyBindings;
			};
		}
	}
}

#endif
