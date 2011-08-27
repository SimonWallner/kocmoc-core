#ifndef KOCMOC_UTIL_UTIL_HPP
#define KOCMOC_UTIL_UTIL_HPP

#include <vector>

namespace kocmoc
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
		
		bool parseConfigFileIntoProperties(std::string path, Properties* props);

	}
}


#endif