#include <kocmoc-core/util/util.hpp>

#include <cmath>

#define TIXML_USE_STL 
#include <tinyxml.h>

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/resources/ResourceManager.hpp>
#include <kocmoc-core/compiler.h>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core;

using std::string;
using std::vector;

using types::Symbol;
using types::symbolize;


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

void util::getNextLine(std::istream& is, std::string& line)
{
	getline(is, line);
}


string util::getFileName(string const &path)
{
	vector<string > tokens;
	tokenize(path, tokens, "/");
	return tokens[tokens.size()-1];
}

bool util::parser::parseConfigXMLFileIntoProperties(string path, Properties* props)
{
	objectifLune::Singleton::Get()->info("trying to parse: '" + path + "'");
	
	TiXmlDocument doc(path.c_str());
	if (!doc.LoadFile())
	{
		objectifLune::Singleton::Get()->error("failed to load xml file: '" + path
											  + "' - " + doc.ErrorDesc());
		std::stringstream sstr;
		sstr <<  "error row: " << doc.ErrorRow() << " col: " << doc.ErrorCol();
		objectifLune::Singleton::Get()->debug(sstr.str());
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

float util::logLuminance(float r, float g, float b)
{
	return log(r * 0.2126f + g * 0.7152f + b * 0.0722f);
}
