#include <kocmoc-core/util/Properties.hpp>

#include <objectif-lune/Singleton.hpp>
#include <sstream>
#include <iostream>

using namespace kocmoc::core::util;
using kocmoc::core::types::Symbol;
using std::string;

void Properties::add(const Symbol name, const float value)
{
	floatCache[name] = value;
}

void Properties::add(const Symbol name, const bool value)
{
	boolCache[name] = value;
}

void Properties::add(const Symbol name, const string value)
{
	stringCache[name] = value;
}

float Properties::getFloat(const Symbol name) const
{
	PropertiesFloatCache::const_iterator ci = floatCache.find(name);
	if (ci != floatCache.end())
		return ci->second;
	else
		return 0.0f;
}

bool Properties::getBool(const Symbol name) const
{
	PropertiesBoolCache::const_iterator ci = boolCache.find(name);
	if (ci != boolCache.end())
		return ci->second;
	else
		return false;
}

const string Properties::getString(const Symbol name) const
{
	PropertiesStringCache::const_iterator ci = stringCache.find(name);
	if (ci != stringCache.end())
		return ci->second;
	else
	{
		std::stringstream sstr;
		sstr << "could not find property: '" << name << "'" << std::endl;
		objectifLune::Singleton::Get()->warn(sstr.str());
		return "UNDEFINED";
	}
}

void Properties::dumpCache() const
{
	std::stringstream sstr;
	sstr << "dumping property cache..." << std::endl;
	
	sstr << "float values:" << std::endl;
	for (PropertiesFloatCache::const_iterator ci = floatCache.begin();
		 ci != floatCache.end();
		 ci++)
	{
		sstr << "\t" << ci->first << " - " << ci->second << std::endl;
	}
	
	sstr << "bool values:" << std::endl;
	for (PropertiesBoolCache::const_iterator ci = boolCache.begin();
		 ci != boolCache.end();
		 ci++)
	{
		sstr << "\t" << ci->first << " - " << ci->second << std::endl;
	}
	
	sstr << "string values:" << std::endl;
	for (PropertiesStringCache::const_iterator ci = stringCache.begin();
		 ci != stringCache.end();
		 ci++)
	{
		sstr << "\t" << ci->first << " - " << ci->second << std::endl;
	}
	
	std::cout << sstr.str();
	objectifLune::Singleton::Get()->debug(sstr.str());
}
