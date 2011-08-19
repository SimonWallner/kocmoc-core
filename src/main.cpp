#include <kocmoc-core/gitSHA1.h>
#include <kocmoc-core/Context.hpp>
#include <kocmoc-core/version.hpp>

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