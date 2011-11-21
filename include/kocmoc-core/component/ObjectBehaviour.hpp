//
//  ObjectBehaviour.h
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_COMPONENT_OBJECT_BEHAVIOUR_HPP
#define KOCMOC_COMPONENT_OBJECT_BEHAVIOUR_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/math/math.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class ObjectBehaviour : public core::componentSystem::Component
			{
			public:
				
				ObjectBehaviour();

				void onUpdate(float deltaT, float t);

				glm::vec3 position;
				glm::quat rotation;
				glm::vec3 scale;
				glm::vec3 speed;
				float lambda;
				float mass;
				glm::vec3 drag;
			};
		}
	}
}

#endif
