//
//  ObjectBehaviour.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <glm/gtx/quaternion.hpp>

using namespace kocmoc::core::component;

using glm::gtx::quaternion::angleAxis;

ObjectBehaviour::ObjectBehaviour()
	: position(glm::vec3(0, 0, 0))
	, rotation(angleAxis(0.0f, 0.0f, 0.0f, 1.0f))
	, scale(glm::vec3(1, 1, 1))
	, speed(glm::vec3(0))
	, lambda(math::decayConst(2.0f))
	, mass(1.0f)
	, drag(glm::vec3(0))
{}

void ObjectBehaviour::onUpdate(float deltaT, float t)
{
	// apply drag
	speed += math::applyForce(drag, mass) * deltaT;
	
	// damping, exp decay
	speed *= math::decay(lambda, deltaT);
	
	// update position
	position += speed * deltaT;
	
	// reset draging force
	drag = glm::vec3(0);
	
	UNUSED t;
}
