#ifndef KOCMOC_CORE_RENDERER_MATERIAL_HPP_
#define KOCMOC_CORE_RENDERER_MATERIAL_HPP_

#include <glm/glm.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class Shader;
			
			class Material
			{
			public:
				Material(glm::vec3 diffuseColour);
				
				/**
				 * Set up the given shader with all that is needed for the
				 * Material
				 */
				void primeShader(Shader* shader);
			
			private:
				glm::vec3 diffuseColour;
			};
		}
	}
}

#endif
