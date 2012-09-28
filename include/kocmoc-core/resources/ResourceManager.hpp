#ifndef KOCMOC_CORE_RESOURCES_RESOURCE_MANAGER_HPP
#define KOCMOC_CORE_RESOURCES_RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>

#include <kocmoc-core/exception/ResourceNotFoundException.hpp>
#include <kocmoc-core/exception/ParseErrorException.hpp>

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
				bool resourceExists(const std::string& relativeResourceName) const;
				
				/**
				 * Try to find a given file in all the resource paths.
				 * @param the relativePath of the file as a path relative to the existin
				 *		resource paths.
				 * @return the absolute path to the asset
				 * @throws ResourceNotFoundException if the resource can not be
				 *		known paths.
				 */
				std::string getAbsolutePath(const std::string& relativePath) const
					throw(exception::ResourceNotFoundException);
				
				
				/**
				 * read the given resource into the string
				 */
				std::string readResource(const std::string& resourceName) const
					throw(exception::ResourceNotFoundException);
				
				void getResourceStream(const std::string& resourceName,
									   std::ifstream& stream) const
					throw(exception::ResourceNotFoundException);
				
				/**
				 * Get the shader constructed from the given shader files
				 */
				renderer::Shader* getShader(const std::string vertexShaderRelativePath,
											const std::string fragmentShaderRelativePath,
											bool cache = true) const;
				
				void reloadShaders();
				
				/**
				 * parse the shader and resolve #pragma includes
				 * useage:
				 * #pragma include <filename.extension>
				 *
				 * @param shaderName the file name of the shader
				 * @param resourceManager to load the files
				 * @param includeCounter the number of the included file, used
				 *		for the #line annotation. lineNumber:includeNumber.
				 *		Base file should be 0.
				 * @return a string with resolved includes and #line annotations
				 */
				std::string preprocessShader(const std::string& shaderName,
											 unsigned int includeCounter = 0) const
					throw(exception::ParseErrorException,
						  exception::ResourceNotFoundException);

				
			private:
				
				/**
				 * Check if the given file exists on the file system.
				 */
				bool fileExists(const std::string &path) const;
				
				/**
				 * Read the given file into a String
				 */
				std::string readFile(const std::string &path) const;
				
				
				typedef std::vector<std::string > ResourcePathVector;
				typedef std::vector<renderer::Shader* > ShaderVector;
				typedef std::map<std::string, renderer::Shader* > ShaderCache;
				
				ResourcePathVector resourcePaths;
				mutable ShaderVector shaders;
				mutable ShaderCache shaderCache;
			};
		}
	}
}


#endif
