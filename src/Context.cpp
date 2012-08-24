#include <sstream>

#include <kocmoc-core/gl.h>
/**
 * this is bullshit!
 * can't include the header to this file as the first include since glew does
 * not allow any other gl includes to happen before it.
 * *sigh* #fail
 */
#include <kocmoc-core/renderer/Context.hpp>

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
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwOpenWindowHint(GLFW_DEPTH_BITS, 32);
	glfwOpenWindowHint(GLFW_WINDOW_RESIZABLE, GL_FALSE);
	
    windowHandle = glfwOpenWindow(width, height, windowMode,
								  props->getString(types::symbolize("window-title")).c_str(), NULL);
    if (!windowHandle)
    {
        objectifLune::Singleton::Get()->fatal("Failed to open GLFW window");
		glfwTerminate();
        exit(EXIT_FAILURE);
    }
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
	std::stringstream sstr;
	sstr << "------------------------ GL Info ------------------------" << std::endl;
	sstr << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // pitch black
//	glClearColor(0.0000398107f, 0.2474041117391f, 0.562703f, 1.0f); // blue
	glEnable(GL_FRAMEBUFFER_SRGB_EXT);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(2.0f);
	glLineWidth(2.0f);
	
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	getError();
}

void Context::swapBuffers()
{
	glfwSwapBuffers();
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
			objectifLune::Singleton::Get()->info("no error");
			break;
		case GL_INVALID_ENUM:
			objectifLune::Singleton::Get()->error("invalid enum");
			break;
		case GL_INVALID_VALUE:
			objectifLune::Singleton::Get()->error("invalid value");
			break;
		case GL_INVALID_OPERATION:
			objectifLune::Singleton::Get()->error("invalid operation");
			break;
		case GL_STACK_OVERFLOW:
			objectifLune::Singleton::Get()->error("stack overflow");
			break;
		case GL_STACK_UNDERFLOW:
			objectifLune::Singleton::Get()->error("stack underflow");
			break;
		case GL_OUT_OF_MEMORY:
			objectifLune::Singleton::Get()->error("out of memory");
			break;
		case GL_TABLE_TOO_LARGE:
			objectifLune::Singleton::Get()->error("table too large");
			break;
			
		default:
			break;
	}
}
