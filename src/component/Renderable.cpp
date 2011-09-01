//
//  Renderable.cpp
//  kocmoc
//
//  Created by Simon Wallner on 31.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include <kocmoc-core/component/Renderable.hpp>

#include <iostream>

using namespace kocmoc::core::component;
using std::string;

void Renderable::onRender()
{
	std::cout << "position: " << objectBehaviour->position.x << std::endl;
}

void Renderable::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}
