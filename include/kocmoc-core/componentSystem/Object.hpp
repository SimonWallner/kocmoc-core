//
//  Object.hpp
//  kocmoc
//
//  Created by Simon Wallner on 29.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_COMPONENT_OBJECT_HPP
#define KOCMOC_CORE_COMPONENT_OBJECT_HPP

#include <list>
#include <map>
#include <string>
#include <typeinfo>

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/renderer/RenderPassEnum.hpp>

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
			class Component;
			
			/**
			 * Base game/domain object class
			 *
			 * This object can aggregate a number of components to define
			 * its behaviour
			 */
			class Object
			{
			public:
				
				/**
				 * Create a new object
				 * @param name	The human readable name of the object.
				 * @param props	A general set of properties to be used by the 
				 *		Object.
				 */
				Object(std::string name, util::Properties* props);
				
				/**
				 * get a component by name and dynamic cast to it.
				 * If there are more components with this name, the first one
				 *	is returned.
				 * @return first component that matches, or NULL if none match.
				 */
				template <class T>
				T* getComponent()
				{
					ComponentMultimap::iterator it = components.find(types::symbolize(typeid(T).name()));
					if (it != components.end())
					{
						Component* c = it->second;
						return dynamic_cast<T*>(c);
					}
					else
						return NULL;
				}
				
				/**
				 * Add a component to the object
				 */
				void addComponent(Component* component);
				
				/**
				 * Register a component to receive update calls.
				 *
				 * @param receiver The component to receive the update call.
				 */
				void registerUpdateReceiver(Component* receiver);
				
				/**
				 * Call update on all components.
				 * 
				 * @param deltaT the time since the last update in seconds.
				 * @param current time in seconds. This might even be negative.
				 */
				void update(float deltaT, float t);
				
				
				/**
				 * Register a component to receive render calls.
				 *
				 * @param receiver The component to receive the render call.
				 */
				void registerRenderReceiver(Component* receiver);
				
				/**
				 * call render on all components with the given camera.
				 */
				void render(renderer::RenderPass pass, scene::Camera* camera);
				
				/**
				 * call \c init on all registered components
				 */
				void initComponents();
				
			protected:
				util::Properties* props;
				
			private:
				std::string name;
				
				typedef std::list<Component* > ComponentList;
				typedef std::multimap<types::Symbol, Component* > ComponentMultimap;
				typedef std::pair<types::Symbol, Component* > NameComponentPair;
				
				ComponentMultimap components;
				ComponentList messageReceivers;
				ComponentList updateReceivers;
				ComponentList renderReceivers;
			};
		}
	}
}

#endif
