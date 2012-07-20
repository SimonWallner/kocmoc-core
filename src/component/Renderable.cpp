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
#include <glm/gtx/quaternion.hpp>

#include <kocmoc-core/gl.h>
#include <kocmoc-core/renderer/RenderMesh.hpp>

using namespace kocmoc::core::component;

using std::string;

using kocmoc::core::scene::Camera;

using glm::mat4;
using glm::toMat4;
using glm::translate;
using glm::scale;

Renderable::Renderable()
{}

void Renderable::onRender(renderer::RenderPass pass, Camera* camera)
{
	if (pass == kocmoc::core::renderer::RP_NORMAL)
	{
		mat4 modelMatrix = translate(objectBehaviour->position)
			* toMat4(objectBehaviour->rotation)
			* scale(objectBehaviour->scale);
		
		for (RenderMeshList::const_iterator ci = renderMeshList.begin();
			 ci != renderMeshList.end();
			 ci++)
		{
			(*ci)->draw(camera, modelMatrix);
		}
	}
}

void Renderable::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}
