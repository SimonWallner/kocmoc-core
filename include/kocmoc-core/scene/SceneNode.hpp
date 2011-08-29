//
//  SceneNode.hpp
//  kocmoc
//
//  Created by Simon Wallner on 29.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_SCENE_SCENE_NODE_HPP
#define KOCMOC_CORE_SCENE_SCENE_NODE_HPP

#include <kocmoc-core/types/Symbol.hpp>

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
			 */
			class SceneNode
			{
			public:
				
				/**
				 * get the 
				 */
				SceneNode* getChild(void);
				
			private:
				/**
				 * name of the node
				 * this is merely a convenience thing, and only to support
				 * humans debugging the scene graph
				 */
				types::Symbol name;
			};
		}
	}
}

#endif
