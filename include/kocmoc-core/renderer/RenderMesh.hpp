#ifndef KOCMOC_CORE_RENDERER_RENDER_MESH_HPP
#define KOCMOC_CORE_RENDERER_RENDER_MESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include <GL/glfw3.h>

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
			
			// vertex attribute constants
			static const char* const vertexAttributePositionName = "inPosition";
			static const types::uint vertexAttributePositionIndex = 0;
			
			static const char* const vertexAttributeNormalName = "inNormal";
			static const types::uint vertexAttributeNormalIndex = 1;
			
			static const char* const vertexAttributeUVName = "inUv";
			static const types::uint vertexAttributeUVIndex = 2;
			
			static const char* const vertexAttributeTangentName = "inTangent";
			static const types::uint vertexAttributeTangentIndex = 3;
			
			// texture units
			static const int textureUnitDiffuse		= 0;
			static const int textureUnitSpecular	= 1;
			static const int textureUnitGloss		= 2;
			static const int textureUnitNormal		= 3;
			
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
				
				void addTexture(GLint handle, int textureUnit);
				virtual ~RenderMesh(void) {}

				virtual void draw(scene::Camera *camera) = 0;

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
