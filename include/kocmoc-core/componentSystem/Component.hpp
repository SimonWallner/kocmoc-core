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
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/compiler.h>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class Camera;
		}
		
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
				
				types::Symbol getName()
				{
					return types::symbolize(typeid(*this).name());
				}
				
				/**
				 * init is callen when all components are constructed.
				 * This is where you get you pointers to other components.
				 */
				virtual void init() {}
				
				
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
				
				/**
				 * update callback.
				 * @param deltaT time since the last update in seconds
				 * @param current time, this can also be negative.
				 */
				virtual void onUpdate(float deltaT, float t) {}
				
				virtual void onRender(renderer::RenderPass pass, scene::Camera* camera) {}
				
#pragma GCC diagnostic pop
				
				
			protected:
				/**
				 * Set the parent of this component.
				 * This shall be only called by Object::addComponent(...)
				 *
				 * @param parent the new parent object.
				 */
				void setParent(Object* parent)
				{
					this->parent = parent;
				}
				
				/**
				 * A component can only have a single parent
				 */
				Object* parent;
			};
		}
	}
}

#endif
