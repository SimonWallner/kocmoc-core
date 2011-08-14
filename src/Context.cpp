#include "Context.hpp"

#include <iostream.h>
#include <gitSHA1.h>

void kocmoc::core::createContext(void) 
{
	std::cout << "creating context now..." << std::endl;
	std::cout << __DATE__ << std::endl;
	std::cout << KOCMOC_CORE_GIT_SHA1 << std::endl;
}
