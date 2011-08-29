//
//  SceneNode.hpp
//  kocmoc
//
//  Created by Simon Wallner on 29.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_SCENE_SCENE_NODE_HPP
#define KOCMOC_CORE_SCENE_SCENE_NODE_HPP

#include <list>
#include <string>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			/**
			 * Base node class of the application level scene graph
			 *
			 * This SG is on the application level. It resides in the domain
			 * of the application and therefore does not know anything about
			 * rendering, displaying or other fancy stuff.
			 *
			 * In order to render it or use it in any other domain, it a view
			 * has to be derived from the SG. A SG can have an arbitrary number 
			 * of views
			 *
			 * This SG is a directed acyclic graph (DAG)
			 */
			class SceneNode
			{
			public:
				
				/**
				 * Update the node and all its subnodes.
				 *
				 * Update this node and propagate the update through all
				 * subnodes.
				 */
				void update(void)
				
				/**
				 * Render this node and all its subnodes.
				 *
				 * Render this node and propagate the render call to all its
				 * subnodes.
				 */
				void render(void)
				
				/**
				 * Add a child node to this node.
				 *
				 * The child is directly attached to this node.
				 */
				void addChild(SceneNode* child)

				
			private:
				
				typedef std::list<SceneNode* node> NodeList;
				
				/**
				 * name of the node
				 * this is merely a convenience thing, and only to support
				 * humans debugging the scene graph
				 */
				std::string name;
				
				/** 
				 * a list of all child nodes
				 */
				NodeList children;
				
			};
		}
	}
}

#endif
