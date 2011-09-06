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

using namespace kocmoc::core::scene;
using namespace Assimp;

using std::string;

using kocmoc::core::component::Renderable;
using kocmoc::core::types::uint;

void AssetLoader::addResourcePath(string path)
{
	resourcePaths.push_back(path);
}

Renderable* AssetLoader::load(string name)
{
	string absolutePath = findAbsolutePathInResources(name);	
	std::cout << "trying to load asset: " << absolutePath << std::endl;
	
	const aiScene* scene = importer.ReadFile(absolutePath, aiProcess_Triangulate);
	
	if (!scene) // error
	{
		std::cout << "Assimp asset loading error" << importer.GetErrorString() << std::endl;
	}
	else
		std::cout << "loading successful" << std::endl;
	
	if (scene->HasMeshes())
	{
		aiMesh* mesh = scene->mMeshes[0];
		
		if (mesh->HasPositions())
		{
			
			GLuint vaoHandle = 0;
			
			glGenVertexArraysAPPLE(1, &vaoHandle);
			glBindVertexArrayAPPLE(vaoHandle);
			
			GLuint handle = 0;
			glGenBuffers(1, &handle);
			glBindBuffer(GL_ARRAY_BUFFER, handle);
			glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(float), mesh->mVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
			
			return new Renderable(vaoHandle);
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
