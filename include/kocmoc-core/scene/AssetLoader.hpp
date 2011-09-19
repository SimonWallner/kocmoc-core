#ifndef KOCMOC_CORE_SCENE_ASSET_LOADER_HPP
#define KOCMOC_CORE_SCENE_ASSET_LOADER_HPP

#include <string>
#include <list>

// wrap, wrap
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#pragma GCC diagnostic error "-Wunused-parameter"

#include <kocmoc-core/exception/ResourceNotFoundException.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class Renderable;
		}
		
		namespace scene
		{
			class AssetLoader
			{
			public:
				AssetLoader(void);
				
				void addResourcePath(const std::string path);
				
				component::Renderable* load(const std::string name);
				
			private:
				typedef std::list<std::string> ResourcePathList;
				
				ResourcePathList resourcePaths;
				
				Assimp::Importer importer;
				
				/**
				 * Try to find a given file in all the resource paths.
				 * @param the name of the file as a path relative to the existin
				 *		resource paths.
				 * @return the absolute path to the asset
				 * @throws 
				 */
				std::string findAbsolutePathInResources(const std::string name) const throw(exception::ResourceNotFoundException);
			};
		}
	}
}


#endif
