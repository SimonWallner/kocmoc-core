#ifndef KOCMOC_CORE_SCENE_ASSET_LOADER_HPP
#define KOCMOC_CORE_SCENE_ASSET_LOADER_HPP

#include <string>
#include <list>

// wrap, wrap
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <assimp/Importer.hpp>
#pragma GCC diagnostic pop


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
			class Scene;
			class ImageLoader;
			
			class AssetLoader
			{
			public:
				AssetLoader(void);
				~AssetLoader(void);
				
								
//				component::Renderable* load(const std::string NodelName, const std::string shaderPath);
				
				void loadToScene(const std::string relativeScenePath, Scene* scene);
				
			private:
				
				ImageLoader* imageLoader;
				
				Assimp::Importer importer;
			};
		}
	}
}


#endif
