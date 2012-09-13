#ifndef KOCMOC_CORE_RESOURCES_RESOURCE_MANAGER_HPP
#define KOCMOC_CORE_RESOURCES_RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>

#include <kocmoc-core/exception/ResourceNotFoundException.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class Shader;
		}
		
		namespace resources
		{
			/**
			 * Resource Manager to handle all things resources.
			 * It abstracts the file system and makes accessing easier so you
			 * don't have to worry about file paths etc...
			 *
			 */
			class ResourceManager
			{
			
			public:
				
				/**
				 * Add a resource path.
				 * Resource paths are absolute paths that are searched for a
				 * given filename or resource.
				 * Search order is not guaranteed.
				 * @param path should be path with trailing /, like "foo/bar/"
				 */
				void addResourcePath(const std::string path);
				
				/**
				 * Check if a resource exists.
				 * i.e. if it can be found in one of the resource paths.
				 * @param relativeResourceName relative resource name like /textures/foo.jpg
				 *
				 */
				bool resourceExists(const std::string relativeResourceName) const;
				
				/**
				 * Try to find a given file in all the resource paths.
				 * @param the relativePath of the file as a path relative to the existin
				 *		resource paths.
				 * @return the absolute path to the asset
				 * @throws ResourceNotFoundException if the resource can not be
				 *		known paths.
				 */
				std::string getAbsolutePath(const std::string relativePath) const
					throw(exception::ResourceNotFoundException);
				
				
				/**
				 * read the given file into the string
				 */
				std::string readFile(const std::string relativePath) const
					throw(exception::ResourceNotFoundException);
				
				/**
				 * Get the shader constructed from the given shader files
				 */
				renderer::Shader* getShader(const std::string vertexShaderRelativePath,
											const std::string fragmentShaderRelativePath) const;
				
				void reloadShaders();

				
			private:
				typedef std::vector<std::string > ResourcePathVector;
				typedef std::vector<renderer::Shader* > ShaderVector;
				
				ResourcePathVector resourcePaths;
				mutable ShaderVector shaders;
			};
		}
	}
}


#endif
