#ifndef tranquility_Scene_cpp
#define tranquility_Scene_cpp

#include <kocmoc-core/scene/Scene.hpp>
#include <kocmoc-core/scene/FilmCamera.hpp>
#include <kocmoc-core/renderer/RenderMesh.hpp>

using namespace kocmoc::core::scene;

using kocmoc::core::renderer::RenderMesh;
using glm::vec3;

Scene::Scene()
	: camera(new FilmCamera(vec3(0, -10, 0), vec3(0, 0, 0), vec3(0, 0, 1)))
{
	//
}

void Scene::render() const
{
	// setup shader and load camera matrix
	
	// render meshes
	for (MeshVector::const_iterator ci = meshes.begin();
		 ci != meshes.end();
		 ci++)
	{
		(*ci)->draw(camera, glm::mat4(1));
	}
}

void Scene::addMesh(RenderMesh *mesh)
{
	meshes.push_back(mesh);
}

Camera* Scene::getCamera() const
{
	return camera;
}

#endif
