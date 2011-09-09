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

using namespace kocmoc::core::scene;
using namespace Assimp;

using std::string;

using kocmoc::core::component::Renderable;
using kocmoc::core::types::uint;
using kocmoc::core::scene::TriangleMesh;

void AssetLoader::addResourcePath(string path)
{
	resourcePaths.push_back(path);
}

Renderable* AssetLoader::load(string name)
{
	string absolutePath = findAbsolutePathInResources(name);	
	std::cout << "trying to load asset: " << absolutePath << std::endl;
	
	const aiScene* scene = importer.ReadFile(absolutePath, aiProcess_Triangulate | aiProcess_SortByPType);
	
	if (!scene) // error
	{
		std::cout << "Assimp asset loading error" << importer.GetErrorString() << std::endl;
	}
	else
		std::cout << "loading successful" << std::endl;
	
	if (scene->HasMeshes())
	{
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			if (mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE)
			{
				uint vertexCount = mesh->mNumVertices;
				uint vertexIndexCount = mesh->mNumFaces * 3;
				
				float* positions = new float[vertexCount * 3];
				for (uint j = 0; j < vertexCount; j++)
				{
					positions[j*3  ] = mesh->mVertices[j].x;
					positions[j*3+1] = mesh->mVertices[j].y;
					positions[j*3+2] = mesh->mVertices[j].z;
				}
				
				uint* indices = new uint[vertexIndexCount];
				for (uint j = 0; j < mesh->mNumFaces; j++)
				{
					indices[j*3  ] = mesh->mFaces[j].mIndices[0];
					indices[j*3+1] = mesh->mFaces[j].mIndices[1];
					indices[j*3+2] = mesh->mFaces[j].mIndices[2];
				}
				
				
				TriangleMesh::VertexAttribute positionAttribute(3, positions, true);
				TriangleMesh triangleMesh(vertexIndexCount, vertexCount, indices, positionAttribute);
			}	
		}
	}
	return NULL;
}

AssetLoader::AssetLoader()
{
	
}

string AssetLoader::findAbsolutePathInResources(string name) throw(exception::ResourceNotFoundException)
{
	for (ResourcePathList::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		string absolutePath = *ci + name;
		if (util::file_exists(absolutePath))
			return absolutePath;
	}
	
	std::cout << name << " not found in resources" << std::endl;
	exception::ResourceNotFoundException e;
	throw e;
}
