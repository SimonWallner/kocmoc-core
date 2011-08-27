#ifndef KOCMOC_CORE_UTIL_PROPERTIES_FILE_PARSER_HPP
#define KOCMOC_CORE_UTIL_PROPERTIES_FILE_PARSER_HPP

#include <map>

#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace util
		{
			typedef std::map<types::Symbol, std::string> PropertiesStringCache;
			typedef std::map<types::Symbol, float> PropertiesFloatCache;
			typedef std::map<types::Symbol, bool> PropertiesBoolCache;

			class Properties
			{
			public:

				/**
				 * Get a property with the given name.
				 */
				float getFloat(types::Symbol name);
				bool getbool(types::Symbol name);
				std::string getString(types::Symbol name);

				/**
				 * Dump the cache to stdout for debugging
				 */
				void dumpCache(void);
				
			private:								
				PropertiesStringCache stringCache;
				PropertiesFloatCache floatCache;
				PropertiesBoolCache boolCache;
			};
		}
	}
}
#endif
