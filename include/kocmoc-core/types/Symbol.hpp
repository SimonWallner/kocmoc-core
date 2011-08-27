#ifndef KOCMOC_CORE_TYPES_SYMBOL_HPP
#define KOCMOC_CORE_TYPES_SYMBOL_HPP

#include <cstring>


/**
 * This symbol implementation is base on the symbol implementation
 * by Broken Rules GmbH, (c) 2010
 */
namespace kocmoc
{
	namespace core
	{
		namespace types
		{
			typedef const char* Symbol;
			
			Symbol symbolize(const char* string);

			/**
			 * a struct to compare two char*s
			 */
			struct charComparator
			{
				bool operator() (const char* lhs, const char* rhs) const
				{
					return strcmp(lhs, rhs) < 0;
				}
			};
		}
	}
}

#endif
