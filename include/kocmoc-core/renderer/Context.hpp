#ifndef KOCMOC_CORE_CONTEXT_HPP
#define KOCMOC_CORE_CONTEXT_HPP

#include <kocmoc-core/gl.h>
#include <kocmoc-core/util/Properties.hpp>

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
				Context(util::Properties* props);

				~Context();

				/**
				 * Print a bunch of usefull informations
				 */
				void getInfo();
				
				GLFWwindow getWindowHandle();
				
				void swapBuffers();
				
				void pollEvents();
				
				bool isAlive();
			
			private:
				
				void setGLStates();
				
				void getError();
				
				GLFWwindow windowHandle;
				util::Properties* props;
			};
		}
	}
}

#endif
