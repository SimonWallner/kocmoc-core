//
//  AnalogEventListener.hpp
//  kocmoc
//
//  Created by Simon Wallner on 25.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace input
		{
			struct AnalogEvent
			{
				double value;
			}
			
			class AnalogEventListener
			{
				void AnalogEventCallback(Symbol name, ButtonEvent event) = 0;
			}
		}
	}
}