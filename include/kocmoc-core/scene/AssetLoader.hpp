#ifndef KOCMOC_CORE_SCENE_ASSET_LOADER_HPP
#define KOCMOC_CORE_SCENE_ASSET_LOADER_HPP

#include <string>
#include <list>

// wrap, wrap
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <assimp/assimp.hpp>
#pragma GCC diagnostic error "-Wunused-parameter"

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
				
				void addResourcePath(std::string path);
				
				component::Renderable* load(std::string name);
				
			private:
				typedef std::list<std::string> ResourcePathList;
				
				ResourcePathList resourcePaths;
				
				Assimp::Importer importer;
			};
		}
	}
}


#endif
