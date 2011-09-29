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
			/**
			 * OpenGL 2.1 implementation of \c RenderMesh interface.
			 **/
			class RenderMesh21 : public RenderMesh
			{
			public:
				RenderMesh21(scene::TriangleMesh* triangleMesh, Shader* _shader)
					: RenderMesh(triangleMesh, _shader)
				{}
				
				~RenderMesh21(void) {}
				
				void addTexture(GLint handle, int textureUnit)
				{
					textureMap[textureUnit] = handle;
				}
				
				void prepare(void);
				
				void draw(scene::Camera *camera);
				
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
			};
		}
	}
}

#endif
