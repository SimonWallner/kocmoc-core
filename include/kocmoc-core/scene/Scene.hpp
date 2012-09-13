#ifndef KOCMOC_CORE_SCENE_SCENE_HPP_
#define KOCMOC_CORE_SCENE_SCENE_HPP_

#include <string>
#include <vector>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class RenderMesh;
		}
		
		namespace scene
		{
			class FilmCamera;
			class ResourceManager;
			
			class Scene
			{
			public:
				Scene();
				
				void update();

				void render();
				
				void addMesh(renderer::RenderMesh* mesh);
				
			private:
				
				typedef std::vector<renderer::RenderMesh* > MeshVector;
				
//				list of meshes
//				cameras
//				resource manager
//				trigger/zones
//				materials
//				physics world
				
				FilmCamera* camera;
				MeshVector meshes;
			};
		}
	}
}

#endif
