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

namespace kocmoc
{
	namespace core
	{
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
				 * get a component by name and dynamic cast to it.
				 */
				template <class T>
				T* getComponent()
				{
					ComponentMap::iterator it = components.find(types::symbolize(typeid(T).name()));
					if (it != components.end())
					{
						Component* c = it->second;
						return dynamic_cast<T*>(c);
					}
					else
						return NULL;
				}
				
				/**
				 * Create a new object
				 * @param name	The human readable name of the object.
				 * @param props	A general set of properties to be used by the 
				 *		Object.
				 */
				explicit Object(std::string name, util::Properties* props);
				
				virtual void init(void) {};
				
				/**
				 * Add a component to the object
				 */
				void addComponent(Component* component);
				
				/**
				 * Register a component to receive messages.
				 *
				 * @param receiver The component to receive the messages.
				 */
				void registerMessageReceiver(Component* receiver);
				
				/**
				 * Send a message to all registered message recievers
				 */
				void sendMessage(void);
				
				
				/**
				 * Register a component to receive update calls.
				 *
				 * @param receiver The component to receive the update call.
				 */
				void registerUpdateReceiver(Component* receiver);
				
				/**
				 * Call update on all components
				 */
				void update(void);
				
				
				/**
				 * Register a component to receive render calls.
				 *
				 * @param receiver The component to receive the render call.
				 */
				void registerRenderReceiver(Component* receiver);
				
				/**
				 * call render on all components
				 */
				void render(void);
				
			protected:
				util::Properties* props;
				
			private:
				std::string name;
				
				typedef std::list<Component* > ComponentList;
				typedef std::map<types::Symbol, Component* > ComponentMap;
				
				ComponentMap components;
				ComponentList messageReceivers;
				ComponentList updateReceivers;
				ComponentList renderReceivers;
			};
		}
	}
}

#endif
