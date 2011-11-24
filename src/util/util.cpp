#include <kocmoc-core/util/util.hpp>

#include <fstream>
#include <iostream>
#include <cstdlib>

#define TIXML_USE_STL 
#include <tinyxml.h>

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/util/Properties.hpp>

using namespace kocmoc::core;

using std::string;
using std::vector;

using types::Symbol;
using types::symbolize;


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

string util::getFileName(string const &path)
{
	vector<string > tokens;
	tokenize(path, tokens, "/");
	return tokens[tokens.size()-1];
}

bool util::parser::parseConfigXMLFileIntoProperties(string path, Properties* props)
{
	std::cout << "trying to parse: '" << path << "'" << std::endl;
	
	TiXmlDocument doc(path.c_str());
	if (!doc.LoadFile())
	{
		std::cout << "failed to load xml file: " << path << " - " << doc.ErrorDesc() << std::endl;
		std::cout << "error row: " << doc.ErrorRow() << " col: " << doc.ErrorCol() << std::endl;
		return false;
	}
	else
	{
		TiXmlElement* properties = doc.FirstChildElement("properties");
		
		if (properties != NULL)
		{

			for (TiXmlElement* element = properties->FirstChildElement("string");
				 element != NULL;
				 element = element->NextSiblingElement("string"))
			{
				props->add(symbolize(element->Attribute("name")), string(element->Attribute("value")));
			}
			
			for (TiXmlElement* element = properties->FirstChildElement("float");
				 element != NULL;
				 element = element->NextSiblingElement("float"))
			{
				float value = 0;
				value = atof(element->Attribute("value"));
				props->add(symbolize(element->Attribute("name")), value);
			}
			
			for (TiXmlElement* element = properties->FirstChildElement("bool");
				 element != NULL;
				 element = element->NextSiblingElement("bool"))
			{
				float value = false;
				value = atof(element->Attribute("value"));
				props->add(symbolize(element->Attribute("name")), (bool)value);
			}
		}
		else
			return false;
	}
	return true;
}
