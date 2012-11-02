#ifndef KOCMOC_CORE_RENDERER_RENDER_MESH_21_HPP
#define KOCMOC_CORE_RENDERER_RENDER_MESH_21_HPP

#include <map>

#include <kocmoc-core/renderer/RenderMesh.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class TriangleMesh;
		}
		
		namespace renderer
		{
			class Material;
			
			/**
			 * OpenGL 2.1 implementation of \c RenderMesh interface.
			 **/
			class RenderMesh21 : public RenderMesh
			{
			public:
				RenderMesh21(scene::TriangleMesh* triangleMesh, Shader* _shader,
							 Material* _material = NULL)
					: RenderMesh(triangleMesh, _shader)
					, material(_material)
				{}
				
				~RenderMesh21() {}
				
				void addTexture(GLint handle, int textureUnit)
				{
					textureMap[textureUnit] = handle;
				}
				
				void prepare();
				
				void draw(scene::Camera *camera, glm::mat4 modelMatrix) const;
				
				void setShaderParam(std::string name, glm::vec3 value);
				void setShaderParam(std::string name, int value);
			private:
				typedef std::map<int, GLint> TextureMap;
				
				GLuint vboHandle;
				GLuint indicesHandle;
				
				struct interleave
				{
					float x, y, z;		// position
					float nx, ny, nz;	// normals
					float u, v;			// uv
				};
				
				TextureMap textureMap;
				
				GLint modelMatrixLocation;
				GLint viewMatrixLocation;
				GLint projectionMatrixLocation;
				GLint normalMatrixLocation;
				GLint instanceLocation;
				GLint cameraPositionLocation;
				
				Material* material;
			};
		}
	}
}

#endif
