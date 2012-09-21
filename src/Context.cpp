#include <kocmoc-core/renderer/Context.hpp>

#include <sstream>
#include <iostream>

#include <kocmoc-core/version.hpp>
#include <objectif-lune/Singleton.hpp>


using namespace kocmoc::core::renderer;

Context::Context(util::Properties* _props)
	: props(_props)
{
	objectifLune::Singleton::Get()->debug("creating context now...");
	
	float width = props->getFloat(types::symbolize("width"));
	float height = props->getFloat(types::symbolize("height"));
	
	int windowMode = GLFW_WINDOWED;
	
    if(!glfwInit())
    {
		objectifLune::Singleton::Get()->fatal("Failed to initialize GLFW");
        exit(EXIT_FAILURE);
    }
	
	glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_WINDOW_RESIZABLE, GL_FALSE);
	
    windowHandle = glfwCreateWindow(width, height, windowMode,
								  props->getString(types::symbolize("window-title")).c_str(), NULL);
    if (!windowHandle)
    {
        objectifLune::Singleton::Get()->fatal("Failed to open GLFW window");
		glfwTerminate();
        exit(EXIT_FAILURE);
    }
	glfwMakeContextCurrent(windowHandle);
	glfwSetWindowPos(windowHandle, 0, 0);
	
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		objectifLune::Singleton::Get()->fatal("failed to initialize GLEW");
		exit(EXIT_FAILURE);
	}
	
	if (GLEW_EXT_framebuffer_sRGB)
	{
		objectifLune::Singleton::Get()->info("sRGB framebuffer available");
	}
	
	std::stringstream sstr;
	sstr << "glew version: " << glewGetString(GLEW_VERSION);
	objectifLune::Singleton::Get()->info(sstr.str());
	
	setGLStates();
}

Context::~Context(void)
{
	objectifLune::Singleton::Get()->info("terminating context");
	glfwTerminate();
}

void Context::getInfo(void)
{
	int major = glfwGetWindowParam(windowHandle, GLFW_OPENGL_VERSION_MAJOR);
    int minor = glfwGetWindowParam(windowHandle, GLFW_OPENGL_VERSION_MINOR);
    int revision = glfwGetWindowParam(windowHandle, GLFW_OPENGL_REVISION);
		
	std::stringstream sstr;
	sstr << "------------------------ GL Info ------------------------" << std::endl;
	sstr << "GL Version reported by glfw: " << major << "." << minor << "." << revision << std::endl;
	sstr << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
	sstr << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	sstr << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	sstr << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	sstr << "------------------------/ GL Info -----------------------" << std::endl;
	objectifLune::Singleton::Get()->info(sstr.str());
}

GLFWwindow Context::getWindowHandle()
{
	return windowHandle;
}

void Context::setGLStates()
{
	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.442047, 0.387623, 0.361867, 1.0f); // tinted gray
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // pitch black
//	glClearColor(0.0000398107f, 0.2474041117391f, 0.562703f, 1.0f); // blue
	glClearColor(0.470440f, 0.404541f, 0.284452f, 1.0f); // sand
	glEnable(GL_FRAMEBUFFER_SRGB_EXT);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(2.0f);
	glLineWidth(2.0f);
	
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
	
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if (props->getBool(types::symbolize("vsync")))
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
	
	getError();
}

void Context::swapBuffers()
{
	glfwSwapBuffers(windowHandle);
	glFlush(); // only needed for gDebugger debugging.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::pollEvents()
{
	glfwPollEvents();
}

void Context::getError()
{
	GLenum err = glGetError();
	switch (err) {
		case GL_NO_ERROR:
			objectifLune::Singleton::Get()->trace("GL ERROR: no error");
			break;
		case GL_INVALID_ENUM:
			objectifLune::Singleton::Get()->error("GL ERROR: invalid enum");
			break;
		case GL_INVALID_VALUE:
			objectifLune::Singleton::Get()->error("GL ERROR: invalid value");
			break;
		case GL_INVALID_OPERATION:
			objectifLune::Singleton::Get()->error("GL ERROR: invalid operation");
			break;
		case GL_STACK_OVERFLOW:
			objectifLune::Singleton::Get()->error("GL ERROR: stack overflow");
			break;
		case GL_STACK_UNDERFLOW:
			objectifLune::Singleton::Get()->error("GL ERROR: stack underflow");
			break;
		case GL_OUT_OF_MEMORY:
			objectifLune::Singleton::Get()->error("GL ERROR: out of memory");
			break;
		case GL_TABLE_TOO_LARGE:
			objectifLune::Singleton::Get()->error("GL ERROR: table too large");
			break;
			
		default:
			break;
	}
}
