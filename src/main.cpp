#include <gitSHA1.h>
#include <Context.hpp>
#include <version.hpp>

#include <iostream>

using kocmoc::core::Context;

/**
 * this is a small test program to illustrate the use of the core component
 */
int main(void) // int argc, char *argv[]
{
	std::cout << "Starting kocmoc-core-test..." << std::endl;
	std::cout << "this is version: " << std::endl;
	std::cout << kocmoc::core::version::getVersionString();
	
	Context context;
	context.init();
}