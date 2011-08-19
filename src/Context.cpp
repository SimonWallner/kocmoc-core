#include <kocmoc-core/Context.hpp>

#include <iostream>
#include <kocmoc-core/gitSHA1.h>

#include <GL/glfw3.h>

void kocmoc::core::Context::init(void) 
{
	
	std::cout << "creating context now..." << std::endl;
	std::cout << __DATE__ << std::endl;
	std::cout << KOCMOC_CORE_GIT_SHA1 << std::endl;
	
	
	GLFWwindow window;

	float width = 720;
	float height = 432;
	
	int windowMode = GLFW_WINDOWED;

    if(!glfwInit())
    {
		std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    window = glfwOpenWindow(width, height, windowMode, "kocmoc", NULL);
    if (!window)
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        exit(EXIT_FAILURE);
    }
}

kocmoc::core::Context::Context(void)
{
	std::cout << "Context dfault ctor" << std::endl;
}

kocmoc::core::Context::~Context(void)
{
	std::cout << "terminating context" << std::endl;
	glfwTerminate();
}
