//
//  Renderable.cpp
//  kocmoc
//
//  Created by Simon Wallner on 31.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include <kocmoc-core/component/Renderable.hpp>

#include <iostream>
#include <glm/gtx/transform.hpp>

#include <kocmoc-core/gl.h>
#include <kocmoc-core/renderer/RenderMesh.hpp>

using namespace kocmoc::core::component;
using std::string;
using kocmoc::core::scene::Camera;
using glm::mat4;

Renderable::Renderable()
{}

void Renderable::onRender(Camera* camera)
{
	for (RenderMeshList::const_iterator ci = renderMeshList.begin();
		 ci != renderMeshList.end();
		 ci++)
	{
		mat4 modelMatrix = glm::gtx::transform::translate(objectBehaviour->position);
		(*ci)->draw(camera, modelMatrix);
	}
}

void Renderable::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}
