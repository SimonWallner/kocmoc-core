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

				~Context(void);

				/**
				 * Print a bunch of usefull informations
				 */
				void getInfo(void);
				
				GLFWwindow getWindowHandle(void);
				
				void swapBuffers(void);
				
				bool isAlive(void);
			
			private:
				
				void setGLStates(void);
				
				void getError(void);
				
				GLFWwindow windowHandle;
				util::Properties* props;
			};
		}
	}
}


#endif
