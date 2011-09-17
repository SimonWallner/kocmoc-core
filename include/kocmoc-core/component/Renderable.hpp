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
#include <list>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/types/Symbol.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class RenderMesh;
		}
		
		namespace scene
		{
			class Camera;
		}
		
		namespace component
		{
		
			class Renderable : public core::componentSystem::Component
			{
			public:
				Renderable();
				
				/**
				 * Render callback function.
				 * 
				 * @param camera The camera that should be used for rendering.
				 */
				void onRender(scene::Camera* camera);
				
				void init(void);
				
				/**
				 * A a renderMesh to the list, so that it is rendered during
				 * \onRender(...)
				 */
				void add(renderer::RenderMesh* renderMesh)
				{
					renderMeshList.push_back(renderMesh);
				}
				
			private:
				typedef std::list<renderer::RenderMesh* > RenderMeshList;
				
				ObjectBehaviour* objectBehaviour;
				
				RenderMeshList renderMeshList;
			};
		}
	}
}

#endif
