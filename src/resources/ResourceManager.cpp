#include <kocmoc-core/resources/ResourceManager.hpp>

#include <kocmoc-core/util/util.hpp>
#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::resources;

using std::string;

void ResourceManager::addResourcePath(const string path)
{
	resourcePaths.push_back(path);
	objectifLune::Singleton::Get()->info("Resource Path '" + path + "' was added.");
}

bool ResourceManager::resourceExists(const string relativeResourceName) const
{
	for (ResourcePathVector::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		std::string absolutePath = (*ci) + relativeResourceName;
		if (util::file_exists(absolutePath))
			return true;
	}
	return false;
}

string ResourceManager::getAbsolutePath(const string relativePath) const throw(exception::ResourceNotFoundException)
{
	for (ResourcePathVector::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		string absolutePath = (*ci) + relativePath;
		if (util::file_exists(absolutePath))
			return absolutePath;
	}
	
	objectifLune::Singleton::Get()->warn("Resource with relative path: '" + relativePath + "' could not be found!");
	exception::ResourceNotFoundException e;
	throw e;
}