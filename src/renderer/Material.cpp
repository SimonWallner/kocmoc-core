#include <kocmoc-core/renderer/Material.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <kocmoc-core/renderer/Shader.hpp>

using namespace kocmoc::core;
using namespace renderer;

Material::Material(glm::vec3 _diffuseColour)
	: diffuseColour(_diffuseColour)
{
	//
}

void Material::primeShader(Shader *shader)
{
	shader->bind();
	
	GLint location = shader->getUniformLocation("diffuseColour");
	if (location >= 0)
	{
		glUniform3fv(location, 1, glm::value_ptr(diffuseColour));
	}
	
	shader->unbind();
}