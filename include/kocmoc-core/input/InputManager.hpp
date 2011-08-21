#ifndef KOCMOC_CORE_INPUT_MANAGER_HPP
#define KOCMOC_CORE_INPUT_MANAGER_HPP

#include <vector>

#include <GL/glfw3.h>

namespace kocmoc
{
	namespace core
	{
		namespace input
		{
			class KeyboardListener;
			
			typedef std::vector<KeyboardListener*> KeyboardListenerList;
			
			class InputManager
			{
			public:
				
				InputManager(GLFWwindow);
				
				void addKeyboardListener(KeyboardListener* listener);
				
				void poll(void);
				
			private:				
				GLFWwindow windowHandle;
				KeyboardListenerList keyboardListenerList;
			};
		}
	}
}

#endif
