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
			class Camera;
		}
		
		namespace renderer
		{
			/**
			 * OpenGL 2.1 implementation of \c RenderMesh interface.
			 **/
			class RenderMesh21 : public RenderMesh
			{
			public:
				RenderMesh21(scene::TriangleMesh* triangleMsh)
					: RenderMesh(triangleMsh)
				{}
				
				virtual void prepare(void);
				
				void draw(camera::Camera *camera) = 0;

			};
		}
	}
}

#endif
