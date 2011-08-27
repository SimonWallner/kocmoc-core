#ifndef KOCMOC_CORE_SCENE_RENDERABLE_HPP
#define KOCMOC_CORE_SCENE_RENDERABLE_HPP

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class Renderable
			{
			public:
				virtual void render(void) const = 0;
			};
		}
	}
}


#endif
