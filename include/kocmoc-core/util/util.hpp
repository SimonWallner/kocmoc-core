#ifndef KOCMOC_UTIL_UTIL_HPP
#define KOCMOC_UTIL_UTIL_HPP

#include <vector>
#include <string>

#include <kocmoc-core/types/types.h>

namespace kocmoc
{
	namespace core
	{
		namespace util
		{
			class Properties;
			
			/**
			 * Check if the given file exists on the file system.
			 */
			bool file_exists(const std::string &filename);
			
			/**
			 * Read the given file into a String
			 */
			std::string read_file(const std::string &filename);
			
			void tokenize(const std::string& str, std::vector<std::string >& tokens, const std::string& delimiter);
			
			
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
				
				
				/**
				 * parse the shader and resolve #pragma includes
				 * useage:
				 * #pragma include <filename.extension>
				 * 
				 * @param shaderName the file name of the shader
				 * @param pathPrefix the local path to the include directory
				 * @param includeCounter the number of the included file, used
				 *		for the #line annotation. lineNumber:includeNumber.
				 *		Base file should be 0.
				 * @return a string with resolved includes and #line annotations
				 */
//				std::string parseShader(std::string shaderName, std::string pathPrefix, types::uint includeCounter = 0) throw(kocmoc::Exception);
			}
		}
	}
}

#endif
