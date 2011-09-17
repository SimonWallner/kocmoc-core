#ifndef KOCMOC_CORE_RENDERER_RENDER_MESH_21_HPP
#define KOCMOC_CORE_RENDERER_RENDER_MESH_21_HPP

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
				RenderMesh21(scene::TriangleMesh* triangleMesh)
					: RenderMesh(triangleMesh)
				{}
				
				~RenderMesh21(void) {}
				
				void prepare(void);
				
				void draw(scene::Camera *camera);
				
			private:
				GLuint vboHandle;
				GLuint indicesHandle;
				unsigned int strideLength;
			};
		}
	}
}

#endif
