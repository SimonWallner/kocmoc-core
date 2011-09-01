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

#include <kocmoc-core/componentSystem/Component.hpp>

namespace kocmoc
{
	namespace component
	{
		class ObjectBehaviour : public core::componentSystem::Component
		{
		public:
			
			ObjectBehaviour();

			void onUpdate(void) {};

			glm::vec3 position;
			
		};
	}
}

#endif