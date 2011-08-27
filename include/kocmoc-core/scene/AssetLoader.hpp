#ifndef KOCMOC_CORE_SCENE_ASSET_LOADER_HPP
#define KOCMOC_CORE_SCENE_ASSET_LOADER_HPP

#include <string>
#include <list>

#include <kocmoc-core/scene/Renderable.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			typedef std::list<std::string> ResourcePathList;
			
			class AssetLoader
			{
			public:
				virtual Renderable* load(std::string name) = 0;
				
				void addResourcePath(std::string path);
				
			private:
				ResourcePathList resourcePaths;
			};
		}
	}
}


#endif
