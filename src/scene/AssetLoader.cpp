//
//  AssetLoader.cpp
//  kocmoc
//
//  Created by Simon Wallner on 27.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <kocmoc-core/scene/AssetLoader.hpp>

#include <kocmoc-core/component/Renderable.hpp>

using namespace kocmoc::core::scene;

using std::string;

using kocmoc::core::component::Renderable;

void AssetLoader::addResourcePath(string path)
{
	resourcePaths.push_back(path);
}

Renderable* AssetLoader::load(string name)
{
	
}

AssetLoader::AssetLoader()
{
	
}
