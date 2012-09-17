#include <kocmoc-core/resources/ResourceManager.hpp>

#include <kocmoc-core/util/util.hpp>
#include <objectif-lune/Singleton.hpp>
#include <kocmoc-core/renderer/Shader.hpp>

using namespace kocmoc::core;
using namespace resources;

using std::string;

void ResourceManager::addResourcePath(const string path)
{
	resourcePaths.push_back(path);
	objectifLune::Singleton::Get()->debug("Resource Path added: '" + path + "'");
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

string ResourceManager::getAbsolutePath(const string relativePath) const
	throw(exception::ResourceNotFoundException)
{
	for (ResourcePathVector::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		string absolutePath = (*ci) + relativePath;
		if (util::file_exists(absolutePath))
			return absolutePath;
	}
	
	objectifLune::Singleton::Get()->warn("Resource with relative path could not be found: '"
										 + relativePath + "'");
	exception::ResourceNotFoundException e;
	throw e;
}

renderer::Shader* ResourceManager::getShader(const std::string vertexShaderRelativePath,
							const std::string fragmentShaderRelativePath) const
{
	string key = vertexShaderRelativePath + fragmentShaderRelativePath;
	
	// note: caching based on files is nonsensical, 'cause shaders carry a state
	// i.e. have their uniforms set over lifetime.
	
	renderer::Shader* shader = new renderer::Shader(getAbsolutePath(vertexShaderRelativePath),
													getAbsolutePath(fragmentShaderRelativePath));
	
	shaders.push_back(shader);
	return shader;
}

void ResourceManager::reloadShaders()
{
	objectifLune::Singleton::Get()->info("reloading all shaders");
	for (ShaderVector::iterator it = shaders.begin(); it != shaders.end(); it++)
	{
		(*it)->reload();
	}
}

string ResourceManager::readFile(const string relativePath) const
	throw(exception::ResourceNotFoundException)
{
	string absolutePath = getAbsolutePath(relativePath);
	return util::read_file(absolutePath);
}
