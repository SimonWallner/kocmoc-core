//
//  ButtonEventListener.hpp
//  kocmoc
//
//  Created by Simon Wallner on 25.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_CORE_INPUT_BUTTON_EVENT_LISTENER_HPP
#define KOCMOC_CORE_INPUT_BUTTON_EVENT_LISTENER_HPP

#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace input
		{
			struct ButtonEvent
			{
				bool isPressed;
			};
			
			class ButtonEventListener
			{
			public:
				virtual void buttonEventCallback(types::Symbol name, ButtonEvent event) = 0;
			};
		}
	}
}

#endif
