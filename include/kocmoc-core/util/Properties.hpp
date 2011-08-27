#ifndef KOCMOC_CORE_UTIL_PROPERTIES_FILE_PARSER_HPP
#define KOCMOC_CORE_UTIL_PROPERTIES_FILE_PARSER_HPP

#include <map>
#include <string>

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
				 * Add values to the map
				 */
				void add(types::Symbol name, float value);
				void add(types::Symbol name, bool value);
				void add(types::Symbol name, std::string);

				/**
				 * Get a property with the given name.
				 */
				float getFloat(types::Symbol name);
				bool getBool(types::Symbol name);
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
