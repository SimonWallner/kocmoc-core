#include <kocmoc-core/Context.hpp>
#include <kocmoc-core/version.hpp>

#include <iostream>

using namespace kocmoc::core;

/**
 * this is a small test program to illustrate the use of the core component
 */
int main(void) // int argc, char *argv[]
{
	std::cout << "Starting kocmoc-core-test..." << std::endl;
	std::cout << "this is version: " << std::endl;
	std::cout << version::getVersionString() << std::endl;
	
	Context context;
	context.init();
	
	context.getInfo();
}