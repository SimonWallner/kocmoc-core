#include <iostream>

#include <GL/glew.h>
#include <GL/glfw3.h>
/**
 * this is bullshit!
 * can't include the header to this file as the first include since glew does
 * not allow any other gl includes to happen before it.
 * *sigh* #fail
 */
#include <kocmoc-core/renderer/Context.hpp>

#include <kocmoc-core/version.hpp>


using namespace kocmoc::core::renderer;

Context::Context(void)
{
	std::cout << "creating context now..." << std::endl;
	
	float width = 720;
	float height = 432;
	
	int windowMode = GLFW_WINDOWED;
	
    if(!glfwInit())
    {
		std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwOpenWindowHint(GLFW_DEPTH_BITS, 32);
    windowHandle = glfwOpenWindow(width, height, windowMode, "kocmoc", NULL);
    if (!windowHandle)
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        exit(EXIT_FAILURE);
    }
	glfwSetWindowPos(windowHandle, 0, 0);
	
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "failed ton initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if (GLEW_EXT_framebuffer_sRGB)
	{
		std::cout << "sRGB framebuffer available" << std::endl;
	}
	
	std::cout << "glew version: " << glewGetString(GLEW_VERSION) << std::endl;
	
	setGLStates();
}

Context::~Context(void)
{
	std::cout << "terminating context" << std::endl;
	glfwTerminate();
}

void Context::getInfo(void)
{
	std::cout << "------------------------ GL Info ------------------------" << std::endl;
	std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "------------------------/ GL Info -----------------------" << std::endl;
}

GLFWwindow Context::getWindowHandle()
{
	return windowHandle;
}

void Context::setGLStates()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.442047, 0.387623, 0.361867, 1.0f); // tinted gray
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // pitch black
	glEnable(GL_FRAMEBUFFER_SRGB_EXT);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(2.0f);
	glLineWidth(2.0f);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	getError();
}

void Context::swapBuffers()
{
	glfwSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glfwPollEvents();
}

bool Context::isAlive()
{
	return glfwIsWindow(windowHandle);
}

void Context::getError()
{
	GLenum err = glGetError();
	switch (err) {
		case GL_NO_ERROR:
			std::cout << "no error" << std::endl;
			break;
		case GL_INVALID_ENUM:
			std::cout << "invalid enum" << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "invalid value" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "invalid operation" << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "stack overflow" << std::endl;
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "stack underflow" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "out of memory" << std::endl;
			break;
		case GL_TABLE_TOO_LARGE:
			std::cout << "table too large" << std::endl;
			break;
			
		default:
			break;
	}
}
