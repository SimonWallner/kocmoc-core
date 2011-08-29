//
//  Component.hpp
//  kocmoc
//
//  Created by Simon Wallner on 29.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_COMPONENT_COMPONENT_HPP
#define KOCMOC_CORE_COMPONENT_COMPONENT_HPP

#include <kocmoc-core/component/Object.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			/**
			 * core component class
			 *
			 * This is the core component class for the "component base" design
			 * approach. Derive from it to create your own components.
			 */
			class Component
			{
				friend void Object::addComponent(Component*);

			public:
				virtual void update(void) {}
				virtual void sendMessage(void) {}
				virtual void render(void) {}
				
			private:
				void setParent(Object* parent);
			
			};
		}
	}
}

#endif