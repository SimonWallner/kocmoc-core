#include <gitSHA1.h>
#include <Context.hpp>

#include <iostream>

int main(void)
{
	std::cout << "Oh my god, its full of stars!" << std::endl;
	std::cout << KOCMOC_CORE_GIT_SHA1 << std::endl;
	
	kocmoc::core::createContext();
}