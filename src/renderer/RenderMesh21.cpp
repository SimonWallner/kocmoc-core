#include <kocmoc-core/renderer/RenderMesh21.hpp>

#include <iostream>

#include <kocmoc-core/gl.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <kocmoc-core/scene/Camera.hpp>
#include <kocmoc-core/renderer/Material.hpp>

#include <objectif-lune/Singleton.hpp>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace kocmoc::core::renderer;

using kocmoc::core::scene::Camera;

void RenderMesh21::prepare(void)
{
	// interleave vertex attribute for great good.
	interleave* interleaved = new interleave[triangleMesh->vertexCount];
	for (unsigned int i = 0; i < triangleMesh->vertexCount; i++)
	{
		interleaved[i].x = triangleMesh->vertexPositions[i*3 + 0];
		interleaved[i].y = triangleMesh->vertexPositions[i*3 + 1];
		interleaved[i].z = triangleMesh->vertexPositions[i*3 + 2];
		
		if (triangleMesh->vertexNormals != NULL)
		{
			interleaved[i].nx = triangleMesh->vertexNormals[i*3 + 0];
			interleaved[i].ny = triangleMesh->vertexNormals[i*3 + 1];
			interleaved[i].nz = triangleMesh->vertexNormals[i*3 + 2];
		}
		
		if (triangleMesh->vertexUVs != NULL)
		{
			interleaved[i].u = triangleMesh->vertexUVs[i*2 + 0];
			interleaved[i].v = triangleMesh->vertexUVs[i*2 + 1];
		}		
	}
	
	vboHandle = 0;

	glGenBuffers(1, &vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, 
				 triangleMesh->vertexCount * sizeof(interleave), 
				 interleaved, 
				 GL_STATIC_DRAW);
	
	delete [] interleaved;	
	
	glGenBuffers(1, &indicesHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 triangleMesh->vertexIndexCount * sizeof(unsigned int),
				 triangleMesh->indices,
				 GL_STATIC_DRAW);

	// shader stuff
	if (!shader->isPrepared())
		shader->prepare();
	
	shader->bind();
	{
		modelMatrixLocation = shader->getUniformLocation("modelMatrix");
		viewMatrixLocation = shader->getUniformLocation("viewMatrix");
		projectionMatrixLocation = shader->getUniformLocation("projectionMatrix");
		normalMatrixLocation = shader->getUniformLocation("normalMatrix");
		instanceLocation = shader->getUniformLocation("instance");
		cameraPositionLocation = shader->getUniformLocation("cameraPosition");
	}
	shader->unbind();
	
	prepared = true;
}

void RenderMesh21::draw(Camera *camera, glm::mat4 modelMatrix) const
{
	if (!prepared)
	{
		objectifLune::Singleton::Get()->warn("The mesh you try to render is not ready yet! Prepare it first.");
		return;
	}
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		
	// for each vertex attribute do...
	// positions
	glEnableVertexAttribArray(vertexAttributePositionIndex);
	glVertexAttribPointer(vertexAttributePositionIndex, 3, GL_FLOAT, false,
						  sizeof(interleave), 0);
	
	// normal
	glEnableVertexAttribArray(vertexAttributeNormalIndex);
	glVertexAttribPointer(vertexAttributeNormalIndex, 3, GL_FLOAT, false,
						  sizeof(interleave), BUFFER_OFFSET(sizeof(GLfloat) * 3));
	
	// uv
	glEnableVertexAttribArray(vertexAttributeUVIndex);
	glVertexAttribPointer(vertexAttributeUVIndex, 2, GL_FLOAT, false,
						  sizeof(interleave), BUFFER_OFFSET(sizeof(GLfloat) * 6));
	
	// textures
	for (TextureMap::const_iterator ci = textureMap.begin();
		 ci != textureMap.end();
		 ci++)
	{
		glActiveTexture(GL_TEXTURE0 + ci->first);
		glBindTexture(GL_TEXTURE_2D, ci->second);
	}


	if (material)
		material->primeShader(shader);
	
	shader->bind();
	{
		// update shader
		
		if (modelMatrixLocation >= 0)
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		
		if (normalMatrixLocation >= 0)
			glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE,
							   glm::value_ptr(glm::inverseTranspose(modelMatrix)));
		
		if (camera != NULL)
		{
			if (viewMatrixLocation >= 0)
				glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
			
			if (projectionMatrixLocation >= 0)
				glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

			if (cameraPositionLocation >= 0)
				glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(camera->getPosition()));
		}
			
		glDrawElements(GL_TRIANGLES,
					   triangleMesh->vertexIndexCount,
					   GL_UNSIGNED_INT,
					   NULL);

	}
	shader->unbind();
	
	// cleanup
	glDisableVertexAttribArray(vertexAttributePositionIndex);
	glDisableVertexAttribArray(vertexAttributeNormalIndex);
	glDisableVertexAttribArray(vertexAttributeUVIndex);
}

void RenderMesh21::setShaderParam(std::string name, glm::vec3 value)
{
	if (!prepared)
		prepare();
	
	shader->bind();
	{
		GLint location = shader->getUniformLocation(name);
		if(location >= 0)
			glUniform3fv(location, 1, glm::value_ptr(value));
	}
}

void RenderMesh21::setShaderParam(std::string name, int value)
{
	if (!prepared)
		prepare();
	
	shader->bind();
	{
		GLint location = shader->getUniformLocation(name);
		if(location >= 0)
			glUniform1i(location, value);
	}
}
