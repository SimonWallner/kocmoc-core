#ifndef KOCMOC_CORE_RENDERER_RENDER_MESH_HPP
#define KOCMOC_CORE_RENDERER_RENDER_MESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include <kocmoc-core/gl.h>

#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/scene/TriangleMesh.hpp>
#include <kocmoc-core/types/types.h>
#include <kocmoc-core/compiler.h>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class Camera;
		}

		namespace renderer
		{
			class Shader;

			/**
			 * This is the hardware dependent (2.1, 3.2, ES2.0, etc.) wrapper
			 * that takes a version independent triangle mesh and makes it 
			 * displayable for the target platform.
			 *
			 * Well, to be more precise, this is the HW independent interface
			 * that is implemented by the hardware specific implementations.
			 */
			class RenderMesh
			{
			public:

				RenderMesh(scene::TriangleMesh* _triangleMsh, Shader* _shader)
					: triangleMesh(_triangleMsh)
					, shader(_shader)
					, prepared(false)
				{}
				
				virtual void addTexture(GLint handle, int textureUnit) = 0;
				virtual ~RenderMesh(void) {}

				/**
				 * Draw the render mesh
				 * @param camera the camera that is used for drawing
				 * @param parentTransform
				 */
				virtual void draw(scene::Camera *camera, glm::mat4 modelMatrix) const = 0;
				
				types::uint getVertexCount(void) const
				{
					return triangleMesh->vertexCount;
				}
				
				/**
				 * Prepare the mesh for rendering.
				 *
				 * This covers all the chores that have to be done before the 
				 * actual rendering. Like, setting up textures, loading shaders
				 * uploading vertex data, etc.
				 */
				virtual void prepare(void) = 0;
				
				/**
				 * Find out if this \c RenderMesh is ready for rendering.
				 */
				bool isPrepared(void) const
				{
					return prepared;
				}
				
				virtual void setShaderParam(std::string name, glm::vec3 value) = 0;
				virtual void setShaderParam(std::string name, int value) = 0;

			protected:
				
				/** A texture wrapper */
				struct RenderTexture
				{
					const GLuint handle;
					const GLuint textureUnit;
					
					RenderTexture(GLuint _handle, GLuint _textureUnit)
					: handle(_handle)
					, textureUnit(_textureUnit)
					{}
				};
				typedef std::vector<RenderTexture > RenderTextureList;

				/**
				 * The triangle mesh that holds the data. Once everything is 
				 * uploaded this might even be \c NULL.
				 */
				const scene::TriangleMesh* triangleMesh;
				
				/** 
				 * A pointer to the shader that is used. exactly one shader per
				 * mesh. Shall not be \ NULL.
				 */
				Shader* shader;
				
				/** whether the mesh is ready for rendering or not */
				bool prepared;
				
				/** List of \c RenderTexture */
				RenderTextureList renderTextures;
			};
		}
	}
}


#endif
