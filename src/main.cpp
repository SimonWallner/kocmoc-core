#include <gitSHA1.h>
#include <Context.hpp>

#include <iostream>

using kocmoc::core::Context;

int main(void) // int argc, char *argv[]
{
	std::cout << "Oh my god, its full of stars!" << std::endl;
	std::cout << KOCMOC_CORE_GIT_SHA1 << std::endl;
	
	Context context;
	context.init();
}