//
//  AssetLoader.cpp
//  kocmoc
//
//  Created by Simon Wallner on 27.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <kocmoc-core/scene/AssetLoader.hpp>

#include <iostream>

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <assimp/aiScene.h>

#include <kocmoc-core/component/Renderable.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/types/types.h>
#include <kocmoc-core/scene/TriangleMesh.hpp>

#include <renderer/RenderMesh21.hpp>

using namespace kocmoc::core::scene;
using namespace Assimp;

using std::string;

using kocmoc::core::component::Renderable;
using kocmoc::core::types::uint;
using kocmoc::core::scene::TriangleMesh;
using kocmoc::core::renderer::RenderMesh21;

void AssetLoader::addResourcePath(const string path)
{
	resourcePaths.push_back(path);
}

Renderable* AssetLoader::load(const string name)
{
	Renderable* renderable = new Renderable();
	
	string absolutePath = findAbsolutePathInResources(name);	
	std::cout << "trying to load asset: " << absolutePath << std::endl;
	
	const aiScene* scene = importer.ReadFile(absolutePath,
											 aiProcess_Triangulate |
											 aiProcess_SortByPType |
											 aiProcess_CalcTangentSpace |
											 aiProcess_ImproveCacheLocality);
	
	if (!scene) // error
	{
		std::cout << "Assimp asset loading error" << importer.GetErrorString() << std::endl;
	}
	else
	{
		if (scene->HasMeshes())
		{
			for (uint i = 0; i < scene->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[i];
				if (mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE)
				{
					uint vertexCount = mesh->mNumVertices;
					uint vertexIndexCount = mesh->mNumFaces * 3;

					uint* indices = new uint[vertexIndexCount];
					for (uint j = 0; j < mesh->mNumFaces; j++)
					{
						indices[j*3  ] = mesh->mFaces[j].mIndices[0];
						indices[j*3+1] = mesh->mFaces[j].mIndices[1];
						indices[j*3+2] = mesh->mFaces[j].mIndices[2];
					}
					
					float* positions = new float[vertexCount * 3];
					for (uint j = 0; j < vertexCount; j++)
					{
						positions[j*3  ] = mesh->mVertices[j].x;
						positions[j*3+1] = mesh->mVertices[j].y;
						positions[j*3+2] = mesh->mVertices[j].z;
					}
					
					float* normals = new float[vertexCount * 3];
					for (uint j = 0; j < mesh->mNumFaces; j++)
					{
						normals[j*3  ] = mesh->mNormals[j].x;
						normals[j*3+1] = mesh->mNormals[j].y;
						normals[j*3+2] = mesh->mNormals[j].z;
					}
					
					TriangleMesh* triangleMesh = new TriangleMesh(vertexIndexCount,
																 indices,
																 vertexCount,
																 positions,
																 normals);
					RenderMesh21* renderMesh = new RenderMesh21(triangleMesh);
					renderable->add(renderMesh);
				}	
			}
			
			for (uint i = 0; i < scene->mNumMaterials; i++)
			{
				aiMaterial* mat = scene->mMaterials[i];
				aiString* path = new aiString();
				mat->GetTexture(aiTextureType_DIFFUSE, 0, path);
				std::cout << "diffuse texture 0: " << path->data << std::endl;
			}
		}
		std::cout << "loading successful" << std::endl;

	}
	return renderable;
}

AssetLoader::AssetLoader()
{
	
}

string AssetLoader::findAbsolutePathInResources(const string name) const throw(exception::ResourceNotFoundException)
{
	for (ResourcePathList::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		string absolutePath = (*ci) + name;
		if (util::file_exists(absolutePath))
			return absolutePath;
	}
	
	std::cout << name << " not found in resources" << std::endl;
	exception::ResourceNotFoundException e;
	throw e;
}
