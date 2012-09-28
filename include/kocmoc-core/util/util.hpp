#ifndef KOCMOC_UTIL_UTIL_HPP
#define KOCMOC_UTIL_UTIL_HPP

#include <vector>
#include <string>
#include <istream>

#include <kocmoc-core/types/types.h>

namespace kocmoc
{
	namespace core
	{
		namespace util
		{
			class Properties;
			
			void tokenize(const std::string& str, std::vector<std::string >& tokens, const std::string& delimiter);
			
			/**
			 * Get the next line in the stream and store it in the string
			 */
			void getNextLine(std::istream& is, std::string& line);

			
			/**
			 * Get the filename of a path, e.g.
			 * foo/bar/buz/file.name --> file.name
			 */
			std::string getFileName(const std::string &path);
			
			/**
			 * Compute the perceived luminance from the given tristumulus.
			 */
			float logLuminance(float r, float g, float b);
			
			
			namespace parser
			{
				/**
				 * Parse a xml config file into the given properties.
				 * New props are added to existing properties. The properties
				 * must not be \c NULL
				 *
				 * @param path The path of the xml file to parse (absolute???)
				 * @param props The properties where the new properties are added to
				 * @return \c true iff parsing the file was successful
				 */
				bool parseConfigXMLFileIntoProperties(std::string path, Properties* props);
			}
		}
	}
}

#endif
