#ifndef KOCMOC_CORE_SCENE_ASSET_LOADER_HPP
#define KOCMOC_CORE_SCENE_ASSET_LOADER_HPP

#include <string>
#include <list>

#include <kocmoc-core/component/Renderable.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class AssetLoader
			{
			public:
				virtual component::Renderable* load(std::string name) = 0;
				
				void addResourcePath(std::string path);
				
				component::Renderable* loadAsset(std::string name);
				
			private:
				typedef std::list<std::string> ResourcePathList;
				
				ResourcePathList resourcePaths;
			};
		}
	}
}


#endif
