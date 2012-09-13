#ifndef tranquility_Scene_cpp
#define tranquility_Scene_cpp

#include <kocmoc-core/scene/Scene.hpp>

using namespace kocmoc::core::scene;

using kocmoc::core::renderer::RenderMesh;

Scene::Scene()
{
	//
}

void Scene::render()
{
	// setup shader and load camera matrix
	
	// render meshes
	for (MeshVector::const_iterator ci = meshes.begin();
		 ci != meshes.end();
		 ci++)
	{
		//
	}
}

void Scene::addMesh(RenderMesh *mesh)
{
	meshes.push_back(mesh);
}

#endif
