#include <iostream>

#include <GL/glfw3.h>

#include <kocmoc-core/renderer/Context.hpp>
#include <kocmoc-core/version.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>

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

void keyCallback(GLFWwindow win, int key, int mode)
{
	std::cout << "key: " << key << std::endl;
	std::cout << win << mode;
}


/**
 * this is a small test program to illustrate the use of the core component
 */
int main(void) // int argc, char *argv[]
{
	std::cout << "Starting kocmoc-core-test..." << std::endl;
	std::cout << "this is version: " << std::endl;
	std::cout << version::getVersionString() << std::endl;
	
	renderer::Context context;
	glfwEnable(context.getWindowHandle(), GLFW_STICKY_KEYS);
	glfwSetKeyCallback(keyCallback);
	
	InputManager inputManager(context.getWindowHandle());
	KeyWatcher kw;
	
	Symbol quit = symbolize("quit");
	
	inputManager.registerButtonEventListener(quit, &kw);
	inputManager.bindButtonEventToKey(quit, 'q');
	
	while (kw.running == true && glfwIsWindow(context.getWindowHandle()))
	{
		inputManager.poll();
		
		if (glfwGetKey(context.getWindowHandle(), GLFW_KEY_ESC))
			kw.running = false;
		
		glfwSwapBuffers();
	}

	context.getInfo();
}

