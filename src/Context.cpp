#include <kocmoc-core/Context.hpp>
#include <kocmoc-core/version.hpp>

#include <iostream>

#include <GL/glfw3.h>

void kocmoc::core::Context::init(void) 
{	
	std::cout << "creating context now..." << std::endl;
	
	GLFWwindow window;

	float width = 720;
	float height = 432;
	
	int windowMode = GLFW_WINDOWED;

    if(!glfwInit())
    {
		std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
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

void kocmoc::core::Context::getInfo(void)
{
	std::cout << "------------------------ GL Info ------------------------" << std::endl;
	std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "------------------------/ GL Info -----------------------" << std::endl;
}
