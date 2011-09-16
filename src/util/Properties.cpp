#include <kocmoc-core/util/Properties.hpp>

#include <iostream>

using namespace kocmoc::core::util;
using kocmoc::core::types::Symbol;
using std::string;

void Properties::add(Symbol name, float value)
{
	floatCache[name] = value;
}

void Properties::add(Symbol name, bool value)
{
	boolCache[name] = value;
}

void Properties::add(Symbol name, string value)
{
	stringCache[name] = value;
}

float Properties::getFloat(Symbol name)
{
	PropertiesFloatCache::const_iterator ci = floatCache.find(name);
	if (ci != floatCache.end())
		return ci->second;
	else
		return 0.0f;
}

bool Properties::getBool(Symbol name)
{
	PropertiesBoolCache::const_iterator ci = boolCache.find(name);
	if (ci != boolCache.end())
		return ci->second;
	else
		return false;
}

string Properties::getString(Symbol name)
{
	PropertiesStringCache::const_iterator ci = stringCache.find(name);
	if (ci != stringCache.end())
		return ci->second;
	else
	{
		std::cout << "could not find property: '" << name << "'" << std::endl;
		return "UNDEFINED";
	}
}

void Properties::dumpCache()
{
	std::cout << "dumping cache..." << std::endl;
	
	std::cout << "float values:" << std::endl;
	for (PropertiesFloatCache::const_iterator ci = floatCache.begin();
		 ci != floatCache.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << " - " << ci->second << std::endl;
	}
	
	std::cout << "bool values:" << std::endl;
	for (PropertiesBoolCache::const_iterator ci = boolCache.begin();
		 ci != boolCache.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << " - " << ci->second << std::endl;
	}
	
	std::cout << "string values:" << std::endl;
	for (PropertiesStringCache::const_iterator ci = stringCache.begin();
		 ci != stringCache.end();
		 ci++)
	{
		std::cout << "\t" << ci->first << " - " << ci->second << std::endl;
	}
}
