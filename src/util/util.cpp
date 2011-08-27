#include <kocmoc-core/util/util.h>

using namespace kocmoc::core;

using std::string;
using std::vector;


bool util::file_exists(const string &filename)
{
	std::ifstream ifile(filename.c_str());
	return ifile;
}

string util::read_file(const string &filename)
{
	std::ifstream ifile(filename.c_str());
	
	return std::string(std::istreambuf_iterator<char>(ifile),
					   std::istreambuf_iterator<char>());
}


// code taken from http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
void util::tokenize(const string& str, vector<string >& tokens, const string& delimiter)
{
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiter, 0);
	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiter, lastPos);
	
	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiter, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiter, lastPos);
	}
}

