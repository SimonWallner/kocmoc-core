#include <kocmoc-core/renderer/ShaderManager.hpp>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::renderer;

using std::string;

ShaderManager* ShaderManager::instance = NULL;

ShaderManager& ShaderManager::getInstance()
{
	if(!instance)
		instance = new ShaderManager();
	return *instance;
}

void ShaderManager::Destroy()
{
	delete instance;
	instance = NULL;
}

ShaderManager::ShaderManager(void)
{
}

ShaderManager::~ShaderManager(void)
{
}


Shader* ShaderManager::load(const string &vertexShaderFile, const string &fragmentShaderFile)
{

	// disable caching for now!
	// TODO: reenable caching, use unique signature of files and semantics
	//	string key = vertexShaderFile + fragmentShaderFile;
	//	ShaderCache::const_iterator ci = cache.find(key);
	//	if (ci != cache.end()) // cache hit!
	//	{
	//		return ci->second;
	//	}

	Shader *shader = new Shader(vertexShaderFile, fragmentShaderFile);

//	cache[key] = shader;
	return shader;
}

void ShaderManager::reloadAll()
{
	objectifLune::Singleton::Get()->debug("Reloading all shaders...");
	
	for (ShaderCache::iterator it = cache.begin(); it != cache.end(); it++)
	{
		(*it).second->reload();
	}
}
