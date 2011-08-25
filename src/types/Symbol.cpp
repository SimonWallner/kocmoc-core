#include <kocmoc-core/types/Symbol.hpp>

#include <set>

using namespace kocmoc::core::types;
using kocmoc::core::types::Symbol;

typedef std::set<const char*, charComparator> SymbolSet;

static SymbolSet symbols;

Symbol symbolize(const char* string)
{
	if (string == NULL || *string == 0)
		return NULL;

	//search for symbol in symbols map
	SymbolSet::iterator symbolLowerBound = symbols.lower_bound(string);
	if (symbolLowerBound != symbols.end() && !(symbols.key_comp()(string, (*symbolLowerBound))) ) 
	{
		//symbol already exits in symbols map
		return (*symbolLowerBound);
	}
	else
	{
		//if not, copy string and insert it into symbols map at symbolLowerBound
		char* copy = new char[strlen(string)];
		strcpy(copy, string);
		return *symbols.insert(symbolLowerBound, copy);
	}
}
