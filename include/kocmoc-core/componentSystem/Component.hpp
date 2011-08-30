//
//  Component.hpp
//  kocmoc
//
//  Created by Simon Wallner on 29.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_COMPONENT_COMPONENT_HPP
#define KOCMOC_CORE_COMPONENT_COMPONENT_HPP

#include <kocmoc-core/componentSystem/Object.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace componentSystem
		{
			/**
			 * core component class
			 *
			 * This is the core component class for the "component base" design
			 * approach. Derive from it to create your own components.
			 */
			class Component
			{
				/**
				 * The Object is allowed to set itself as parent when it adds
				 * a component
				 */
				friend void Object::addComponent(Component*);

			public:
				virtual void onUpdate(void) {}
				virtual void onMessage(void) {}
				virtual void onRender(void) {}
				
			private:
				void setParent(Object* parent);
				
				/**
				 * A component can only have a single parent
				 */
				Object* parent;
			
			};
		}
	}
}

#endif