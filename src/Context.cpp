#include "Context.hpp"

#include <iostream>
#include <gitSHA1.h>

#include <GL/glfw.h>

void kocmoc::core::createContext(void) 
{
	std::cout << "creating context now..." << std::endl;
	std::cout << __DATE__ << std::endl;
	std::cout << KOCMOC_CORE_GIT_SHA1 << std::endl;
	
	

	float width = 720;
	float height = 432;
	
	int windowMode = GLFW_WINDOW;

	if (!glfwInit())
		//throw Exception("FATAL: Failed to initialize glfw!");
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	
	// Set flags so GLFW gives us a forward-compatible context.
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	
	glfwOpenWindow(width, height, 
					   0, 0, 0, 0, // r, g, b, a
					   24, 8, // depth, stencil
				   windowMode);
		
	glfwSetWindowPos(200, 20);
	glfwSetWindowTitle("KOCMOC");
}
