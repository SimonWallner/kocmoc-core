#ifndef KOCMOC_CORE_RENDERER_SHADER_HPP
#define KOCMOC_CORE_RENDERER_SHADER_HPP

#include <GL/glfw3.h>
#include <kocmoc-core/types/Symbol.hpp>

#include <string>
#include <vector>

#define LOG_BUFFER_SIZE 8096

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			
			const std::string fragmentDataLocation = "colour";
			
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
					const std::string &fragmentShaderFileName);

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

				bool isPrepared(void) const {return prepared;}

			private:

				/** Whether the shader is uploaded to the GPU or not.
				 * Most operations can only performed if this property is true
				 */
				bool prepared;

				GLuint vertexShader;
				GLuint fragmentShader;
				GLuint programHandle;

				std::string vertexShaderName;
				std::string fragmentShaderName;

				GLuint compile(GLenum type, const std::string &source);
				void link (void);

				void dumpShaderLog(GLuint shader);
				void dumpProgramLog(GLuint programHandle);

				void create(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);
				void destroy(void);
			};
		}
	}
}
#endif
