//
//  version.h
//  kocmoc-core
//
//  Created by Simon Wallner on 19.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <string>

#include <gitSHA1.h>

namespace kocmoc
{
	namespace core
	{
		namespace version
		{
			std::string getVersionString(void)
			{
				std::string version = std::string("git SHA1 hash: ");
				return version + std::string(KOCMOC_CORE_GIT_SHA1);
			}
		}
	}
}