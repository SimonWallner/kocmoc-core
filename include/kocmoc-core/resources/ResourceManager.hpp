#ifndef KOCMOC_CORE_RESOURCES_RESOURCE_MANAGER_HPP
#define KOCMOC_CORE_RESOURCES_RESOURCE_MANAGER_HPP

#include <string>

namespace kocmoc
{
	namespace core
	{
		namespace resources
		{
			/**
			 * Resource Manager to handle all things resources.
			 * It abstracts the file system and makes accessing easier so you
			 * don't have to worry about file paths etc...
			 *
			 * requirements
			 *	- hide physical location (file sys, bundle, zip, ...)
			 *	- reload resources
			 *	- watch resources and reload on change
			 */
			class ResourceManager
			{
			
			public:
				bool resourceExists(std::string resourceName);
				
				/**
				 * reload all resources!
				 * @this can take a while. You might want to grab a snickers!
				 */
				void forceReloadAll(void);
				
				void getTexture(void* textureID)
				
				void getScene(void* sceneID)
				
				void getSound(void* soundID)
				
				void getScript(void)
				
				/**
				 something like Resource<Type> smart pointer...???
				 */
				
			};
		}
	}
}


#endif
