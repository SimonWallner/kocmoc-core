#ifndef KOCMOC_CORE_CONTEXT_HPP
#define KOCMOC_CORE_CONTEXT_HPP

#include <GL/glfw3.h>

namespace kocmoc {
	namespace core {
		namespace renderer
		{	
			/**
			 * main GL context
			 */
			class Context
			{
			public:
				/**
				 * Create a new context, RAII
				 */
				Context(void);

				~Context(void);

				/**
				 * Print a bunch of usefull informations
				 */
				void getInfo(void);
				
				GLFWwindow getWindowHandle(void);
			
			private:
				GLFWwindow windowHandle;
			};
		}
	}
}


#endif