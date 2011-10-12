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
			class Properties
			{
			public:
				Properties() {}
				
				/**
				 * Add values to the map
				 */
				void add(const types::Symbol name, const float value);
				void add(const types::Symbol name, const bool value);
				void add(const types::Symbol name, const std::string);

				/**
				 * Get a property with the given name.
				 */
				float getFloat(const types::Symbol name) const ;
				bool getBool(const types::Symbol name) const;
				const std::string getString(const types::Symbol name) const;

				/**
				 * Dump the cache to stdout for debugging
				 */
				void dumpCache(void) const;
				
			private:		
				Properties(const Properties& noCopy);
				Properties& operator=(const Properties* noAssign);
				
				typedef std::map<types::Symbol, std::string> PropertiesStringCache;
				typedef std::map<types::Symbol, float> PropertiesFloatCache;
				typedef std::map<types::Symbol, bool> PropertiesBoolCache;
				
				PropertiesStringCache stringCache;
				PropertiesFloatCache floatCache;
				PropertiesBoolCache boolCache;
			};
		}
	}
}
#endif
