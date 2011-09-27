//
//  AnalogEventListener.hpp
//  kocmoc
//
//  Created by Simon Wallner on 25.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_INPUT_ANALOG_EVENT_LISTENER_HPP
#define KOCMOC_CORE_INPUT_ANALOG_EVENT_LISTENER_HPP

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
				void AnalogEventCallback(Symbol name, AnalogEvent event) = 0;
			}
		}
	}
}

#endif
