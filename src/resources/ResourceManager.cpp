#include <kocmoc-core/resources/ResourceManager.hpp>

#include <fstream>
#include <sstream>

#include <kocmoc-core/util/util.hpp>
#include <objectif-lune/Singleton.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/scene/ImageLoader.hpp>

using namespace kocmoc::core;
using namespace resources;

using std::string;

ResourceManager::ResourceManager()
	: imageLoader(new scene::ImageLoader())
{}

void ResourceManager::addResourcePath(const string path)
{
	resourcePaths.push_back(path);
	objectifLune::Singleton::Get()->debug("Resource Path added: '" + path + "'");
}

bool ResourceManager::resourceExists(const string& relativeResourceName) const
{
	for (ResourcePathVector::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		std::string absolutePath = (*ci) + relativeResourceName;
		if (fileExists(absolutePath))
			return true;
	}
	return false;
}

string ResourceManager::getAbsolutePath(const string& relativePath) const
	throw(exception::ResourceNotFoundException)
{
	for (ResourcePathVector::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		string absolutePath = (*ci) + relativePath;
		if (fileExists(absolutePath))
			return absolutePath;
	}
	
	objectifLune::Singleton::Get()->error("Resource with relative path could not be found: '"
										 + relativePath + "'");
	exception::ResourceNotFoundException e;
	throw e;
}

renderer::Shader* ResourceManager::getShader(const std::string vertexShaderRelativePath,
											 const std::string fragmentShaderRelativePath,
											 bool cache) const
{
	string key = vertexShaderRelativePath + fragmentShaderRelativePath;
	
	if (cache)
	{
		ShaderCache::const_iterator found = shaderCache.find(key);
		if (found != shaderCache.end())
			return found->second;
	}
	
	renderer::Shader* shader = new renderer::Shader(vertexShaderRelativePath,
													fragmentShaderRelativePath,
													this);
	shaders.push_back(shader);
	if (cache)
		shaderCache[key] = shader;
	
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

string ResourceManager::readResource(const string &resourceName) const
	throw(exception::ResourceNotFoundException)
{
	string absolutePath = getAbsolutePath(resourceName);
	return readFile(absolutePath);
}

string ResourceManager::preprocessShader(const string& shaderName,
									  unsigned int includeCounter) const
	throw(exception::ParseErrorException, exception::ResourceNotFoundException)
{
	unsigned int includeDepth = includeCounter;
	
	std::ifstream stream;
	getResourceStream(shaderName, stream);
	
	std::stringstream out;
	
	unsigned int lineCounter = 1;
	unsigned int includeCnt = 0;
	
	if (includeDepth != 0)
		out << "#line " << lineCounter << " " << includeDepth << std::endl;
	
	while (!stream.eof())
	{
		string line = "";
		util::getNextLine(stream, line);
		int pos = line.find("#pragma include ");
		if (pos == 0)
		{
			string includeName = line.substr(16); // all after "#pragma include "
			out << preprocessShader(includeName, ++includeCnt);
			out << "#line " << lineCounter + 1 << " " << includeDepth << std::endl;
		}
		else
			out << line << std::endl;
		
		
		// add #line AFTER #version
		pos = line.find("#version");
		if (pos == 0)
			out << "#line " << lineCounter + 1 << " " << includeDepth << std::endl;
		
		++lineCounter;
	}
	
	return out.str();
}

bool ResourceManager::fileExists(const string &filename) const
{
	std::ifstream ifile(filename.c_str());
	return ifile;
}

std::string ResourceManager::readFile(const string &path) const
{
	std::ifstream ifile(path.c_str());
	
	return std::string(std::istreambuf_iterator<char>(ifile),
					   std::istreambuf_iterator<char>());
}

void ResourceManager::getResourceStream(const std::string& resourceName,
										std::ifstream& stream) const
	throw(exception::ResourceNotFoundException)
{
	string absolutePath = getAbsolutePath(resourceName);
	stream.open(absolutePath.c_str());
}

GLuint ResourceManager::loadImage(const std::string& resourceName, bool degamma) const
{
	ImageCache::const_iterator found = imageCache2D.find(resourceName);
	if (found != imageCache2D.end())
	{
		return found->second.handle;
	}
	
	GLuint handle = imageLoader->loadImage(getAbsolutePath(resourceName), degamma);

	imageCache2D[resourceName] = ImageCacheEntry(handle, degamma);
	return handle;
}

GLuint ResourceManager::loadImage3D(const std::string& resourceName, bool degamma) const
{
	ImageCache::const_iterator found = imageCache3D.find(resourceName);
	if (found != imageCache3D.end())
	{
		return found->second.handle;
	}
	
	GLuint handle = imageLoader->loadImage3D(getAbsolutePath(resourceName), degamma);
	
	imageCache3D[resourceName] = ImageCacheEntry(handle, degamma);
	return handle;
}

void ResourceManager::reloadImages()
{
	objectifLune::Singleton::Get()->debug("Reloading all images ...");
	
	for(ImageCache::const_iterator ci = imageCache2D.begin();
		ci != imageCache2D.end();
		ci++)
	{
		imageLoader->loadImage(getAbsolutePath(ci->first), ci->second.handle,
							   ci->second.degamma);
	}
	
	for(ImageCache::const_iterator ci = imageCache3D.begin();
		ci != imageCache3D.end();
		ci++)
	{
		imageLoader->loadImage3D(getAbsolutePath(ci->first), ci->second.handle,
								 ci->second.degamma);
	}
}
