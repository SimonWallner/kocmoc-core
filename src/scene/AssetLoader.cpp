//
//  AssetLoader.cpp
//  kocmoc
//
//  Created by Simon Wallner on 27.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <kocmoc-core/scene/AssetLoader.hpp>

#include <iostream>

#include <kocmoc-core/component/Renderable.hpp>
#include <kocmoc-core/util/util.hpp>

using namespace kocmoc::core::scene;
using namespace Assimp;

using std::string;

using kocmoc::core::component::Renderable;

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

	return new Renderable();
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
