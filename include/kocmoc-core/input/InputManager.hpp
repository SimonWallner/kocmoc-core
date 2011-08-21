#ifndef KOCMOC_CORE_INPUT_MANAGER_HPP
#define KOCMOC_CORE_INPUT_MANAGER_HPP

#include "KeyboardListener.hpp"

#include <vector>

namespace kocmoc
{
	namespace core
	{
		namespace input
		{
			typedef std::vector<KeyboardListener*> KeyboardListenerList;
			
			class InputManager
			{
			public:
				
				void addKeyboardListener(KeyboardListener* listener);
				
				void poll(void);
				
			private:				
				KeyboardListenerList keyboardListenerList;
			};
		}
	}
}

#endif
