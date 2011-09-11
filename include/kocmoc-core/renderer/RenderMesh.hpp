#ifndef KOCMOC_CORE_RENDERER_RENDER_MESH_HPP
#define KOCMOC_CORE_RENDERER_RENDER_MESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include <GL/glfw3.h>

#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/scene/TriangleMesh.hpp>
#include <kocmoc-core/types/types.h>

namespace kocmoc
{
	namespace core
	{

		namespace camera
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

				RenderMesh(scene::TriangleMesh* _triangleMsh)
					: triangleMesh(_triangleMsh)
					, prepared(false)
				{}
				
				virtual ~RenderMesh(void);

				void draw(glm::mat4 parentTransform, camera::Camera *camera);

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

			protected:
				
				/** A texture wrapper */
				struct RenderTexture
				{
					const GLuint handle;
					const GLuint textureUnit;
					
					RenderTexture(GLuint _handle, GLuint _textureUnit)
					: handle(_handle)
					, textureUnit(_textureUnit)
					{};
				};
				
				typedef std::vector<RenderTexture > RenderTextureList;

				/**
				 * The triangle mesh that holds the data. Once everything is 
				 * uploaded this might even be \c NULL.
				 */
				const scene::TriangleMesh* triangleMesh;
				
				/** whether the mesh is ready for rendering or not */
				bool prepared;
				
				/** 
				 * A pointer to the shader that is used. exactly one shader per
				 * mesh. Shall not be \ NULL.
				 */
				Shader* shader;

				/** List of \c RenderTexture */
				RenderTextureList renderTextures;
			};
		}
	}
}


#endif
