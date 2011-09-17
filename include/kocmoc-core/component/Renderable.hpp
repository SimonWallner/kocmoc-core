//
//  Renderable.h
//  kocmoc
//
//  Created by Simon Wallner on 31.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMCO_COMPONENT_RENDERABLE_HPP
#define KOCMCO_COMPONENT_RENDERABLE_HPP

#include <string>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class Camera;
		
			class Renderable : public core::componentSystem::Component
			{
			public:
				Renderable();
				
				/**
				 * Render callback function.
				 * 
				 * @param camera The camera that should be used for rendering.
				 */
				void onRender(Camera* camera);
				
				void init(void);
				
			private:
				ObjectBehaviour* objectBehaviour;
			};
		}
	}
}

#endif
