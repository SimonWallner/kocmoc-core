//
//  Renderable.h
//  kocmoc
//
//  Created by Simon Wallner on 31.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMCO_COMPONENT_RENDERABLE_HPP
#define KOCMCO_COMPONENT_RENDERABLE_HPP

#include <kocmoc-core/componentSystem/Component.hpp>

#include "ObjectBehaviour.hpp"

namespace kocmoc
{
	namespace component
	{
		class Renderable : public core::componentSystem::Component
		{
		public:
			void onRender(void);
			
			void init(void);
			
			void loadAsset(std::string name);
			
		private:
			ObjectBehaviour* objectBehaviour;
		};
	}
}

#endif