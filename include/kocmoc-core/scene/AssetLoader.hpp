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
		
		namespace resources
		{
			class ResourceManager;
		}
	
		
		namespace scene
		{
			class Scene;
			class ImageLoader;
			
			class AssetLoader
			{
			public:
				AssetLoader(const resources::ResourceManager* resourceManager);
				
				~AssetLoader();
				
								
//				component::Renderable* load(const std::string NodelName, const std::string shaderPath);
				
				void loadToScene(const std::string relativeScenePath, Scene* scene);
				
			private:
				
				ImageLoader* imageLoader;
				
				const resources::ResourceManager* resourceManager;
				
				Assimp::Importer importer;
			};
		}
	}
}


#endif
