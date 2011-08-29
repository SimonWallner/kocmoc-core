#ifndef KOCMOC_CORE_INPUT_MANAGER_HPP
#define KOCMOC_CORE_INPUT_MANAGER_HPP

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
				
//				void bindAnalogEventToMouse(Symbol name, int event);
				
				void poll(void);
				
			private:
				
				typedef std::pair<types::Symbol, ButtonEventListener*> EventPair;
				typedef std::pair<types::Symbol, char> keyBindingPair;
				typedef std::multimap<types::Symbol, ButtonEventListener*> ButtonEventListenerMultiMap;
				typedef std::multimap<types::Symbol, char> ButtonEventKeyBindings;
				
	//			typedef std::vector<AnalogEventListener*> AnalogEventListenerList;
				
				GLFWwindow windowHandle;
				
				ButtonEventListenerMultiMap buttonEventListenerMultiMap;
				ButtonEventKeyBindings buttonEventKeyBindings;
			};
		}
	}
}

#endif
