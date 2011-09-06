//
//  Renderable.cpp
//  kocmoc
//
//  Created by Simon Wallner on 31.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include <kocmoc-core/component/Renderable.hpp>

#include <iostream>

#include <GL/glfw3.h>

using namespace kocmoc::core::component;
using std::string;

Renderable::Renderable(unsigned int _vaoHandle)
	: vaoHandle(_vaoHandle)
{}

void Renderable::onRender()
{
	glDrawBuffer(GL_TRIANGLES);
	
}

void Renderable::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}
