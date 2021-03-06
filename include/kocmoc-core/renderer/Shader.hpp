#ifndef KOCMOC_CORE_RENDERER_SHADER_HPP
#define KOCMOC_CORE_RENDERER_SHADER_HPP

#include <kocmoc-core/gl.h>
#include <kocmoc-core/types/Symbol.hpp>

#include <string>
#include <vector>

#define LOG_BUFFER_SIZE 8096

namespace kocmoc
{
	namespace core
	{
		namespace resources
		{
			class ResourceManager;
		}
		
		namespace renderer
		{
			
			static const std::string fragmentDataLocation = "colour";
			
			/**
			 * Basic shader class, taken from/built upon the RTR OpenGL 3 sample
			 */
			class Shader
			{
			public:
				/**
				 * Load and compile the files into a shader. All shaders are assumed
				 * to reside in the same folder and use a common path prefix.
				 *
				 * @param vertexShaderFile the name of  the vertex shader file
				 * @param fragmentShaderFile the name of the fragment shader file
				 */
				Shader(const std::string &vertexShaderFileName,
					   const std::string &fragmentShaderFileName,
					   const resources::ResourceManager* resourceManager);

				~Shader();

				/**
				 * Upload the shader to the GPU.
				 *
				 * This is a prerequisite for most of the operations that use the shader.
				 * If the shader is already loaded, it is deleted and recreated.
				 *
				 * @return \c true	\b iff the shader has been compiled and linked
				 *					successfully and is ready to use.
				 */
				bool prepare();

				/**
				 * Bind the shader to OpenGL.
				 *
				 * @note The shader must be uploaded to the GPU.
				 */
				void bind() const;

				/**
				 * Unbind the shader
				 *
				 * @note The shader must be uploaded to the GPU.
				 */
				void unbind() const;

				/**
				 * Query the location of a uniform inside the shader.
				 *
				 * @param name The name of the uniform
				 * @return the uniform location.
				 *
				 * @note The shader must be uploaded to the GPU.
				 */
				GLint getUniformLocation(const std::string &name) const;


				/**
				 * Reload the shader.
				 *
				 * I.e. delete the program and create it again from source. 
				 *
				 * @note The shader must be uploaded to the GPU.
				 */
				void reload();

				bool isPrepared() const { return prepared; }
				
				bool isPrimed() const { return primed; }
				void markPrimed() { primed = true; }

			private:

				/** Whether the shader is uploaded to the GPU or not.
				 * Most operations can only performed if this property is true
				 */
				bool prepared;
				
				/**
				 * Weather someone has set various uniforms or not.
				 * this is especially usefull after an 'external' shader reload
				 */
				bool primed;

				GLint vertexShader;
				GLint fragmentShader;
				GLint programHandle;

				std::string vertexShaderName;
				std::string fragmentShaderName;
				
				const resources::ResourceManager* resourceManager;

				GLuint compile(GLenum type, const std::string &source, const std::string name);
				void link();

				void dumpShaderLog(GLuint shader) const;
				void dumpProgramLog(GLuint programHandle) const;

				void create(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);
				void destroy();
			};
		}
	}
}
#endif
