//
//  Object.hpp
//  kocmoc
//
//  Created by Simon Wallner on 29.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_COMPONENT_OBJECT_HPP
#define KOCMOC_CORE_COMPONENT_OBJECT_HPP

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			/**
			 * Base game/domain object class
			 *
			 * This object can aggregate a number of components to define
			 * its behaviour
			 */
			class Object
			{
			public:
				void sendMessage(void);
				void update(void);
			};
		}
	}
}

#endif