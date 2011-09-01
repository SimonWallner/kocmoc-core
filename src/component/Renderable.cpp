//
//  Renderable.cpp
//  kocmoc
//
//  Created by Simon Wallner on 31.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Renderable.hpp"

#include <iostream>

using namespace kocmoc::component;

void Renderable::onRender()
{
	std::cout << "position: " << objectBehaviour->position.x << std::endl;
}

void Renderable::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}

void Renderable::loadAsset(string name)
{
	
}