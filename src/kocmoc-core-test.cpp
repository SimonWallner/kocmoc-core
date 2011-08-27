#include <iostream>

#include <kocmoc-core/renderer/Context.hpp>
#include <kocmoc-core/version.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>

#include <GL/glfw3.h>

using namespace kocmoc::core;
using namespace kocmoc::core::input;
using namespace kocmoc::core::types;


class KeyWatcher : public ButtonEventListener
{
	void buttonEventCallback(types::Symbol name, ButtonEvent event)
	{
		if (name == types::symbolize("quit") && event.isPressed == true)
			running = false;
	}
	
public:
	KeyWatcher(void)
	: running(true)
	{}

	bool running;
};


/**
 * this is a small test program to illustrate the use of the core component
 */
int main(void) // int argc, char *argv[]
{
	std::cout << "Starting kocmoc-core-test..." << std::endl;
	std::cout << "this is version: " << std::endl;
	std::cout << version::getVersionString() << std::endl;
	
	renderer::Context context;
	context.getInfo();
	
	glfwEnable(context.getWindowHandle(), GLFW_STICKY_KEYS);
	
	InputManager inputManager(context.getWindowHandle());
	KeyWatcher kw;
	
	Symbol quit = symbolize("quit");
	
	inputManager.registerButtonEventListener(quit, &kw);
	inputManager.bindButtonEventToKey(quit, GLFW_KEY_Q);
	
	while (kw.running == true && glfwIsWindow(context.getWindowHandle()))
	{
		inputManager.poll();
		
		if (glfwGetKey(context.getWindowHandle(), GLFW_KEY_ESC))
			kw.running = false;
		
		context.swapBuffers();
		glfwPollEvents();
	}
}

