#include <iostream>

#include <kocmoc-core/renderer/Context.hpp>
#include <kocmoc-core/version.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>

using namespace kocmoc::core;
using namespace kocmoc::core::input;


class KeyWatcher : public ButtonEventListener
{
	void buttonEventCallback(types::Symbol name, ButtonEvent event)
	{
		if (name == types::symbolize("quit") && event.isPressed == true)
			running = false;
	}
	
public:
	KeyWatcher(void)
	: running(false)
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
	
	InputManager inputManager(context.getWindowHandle());
	KeyWatcher kw;
	
	inputManager.registerButtonEventListener(types::symbolize("quit"), &kw);
	inputManager.bindButtonEventToKey(types::symbolize("quit"), 'q');
	
	
	while (kw.running == true)
	{
		inputManager.poll();
	}

	context.getInfo();
}

