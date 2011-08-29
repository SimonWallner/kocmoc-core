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
#include <string>

namespace kocmoc
{
	namespace core
	{
		namespace component
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
				 * Create a new object with the given name.
				 */
				Object(std::string name);
				
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
				
			private:
				
				std::string name;
				
				typedef std::list<Component* > ComponentList;
				
				ComponentList components;
				ComponentList messageReceivers;
				ComponentList updateReceivers;
				ComponentList renderReceivers;
				
			};
		}
	}
}

#endif