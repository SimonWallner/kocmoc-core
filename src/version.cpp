#include <kocmoc-core/version.hpp>

std::string kocmoc::core::version::getVersionString(void)
{
	std::string version = std::string("git SHA1 hash: ");
	return version + gitSHA1;
}
