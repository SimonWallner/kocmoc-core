#ifndef KOCMOC_UTIL_UTIL_HPP
#define KOCMOC_UTIL_UTIL_HPP

#include <vector>
#include <string>

#include <kocmoc-core/types/types.h>
#include <kocmoc-core/exception/ParseErrorException.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace resources
		{
			class ResourceManager;
		}
		
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
			
			/**
			 * Get the filename of a path, e.g.
			 * foo/bar/buz/file.name --> file.name
			 */
			std::string getFileName(const std::string &path);
			
			
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
				 * @param resourceManager to load the files
				 * @param includeCounter the number of the included file, used
				 *		for the #line annotation. lineNumber:includeNumber.
				 *		Base file should be 0.
				 * @return a string with resolved includes and #line annotations
				 */
				std::string parseShader(const std::string shaderName,
										const resources::ResourceManager* resourceManager,
										unsigned int includeCounter = 0)
									throw(exception::ParseErrorException);
			}
		}
	}
}

#endif
