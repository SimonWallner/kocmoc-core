#include "RenderMesh21.hpp"

#include <iostream>

#include <GL/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <kocmoc-core/scene/Camera.hpp>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace kocmoc::core::renderer;

using kocmoc::core::scene::Camera;

void RenderMesh21::prepare(void)
{
	interleave* interleaved = new interleave[triangleMesh->vertexCount];

	for (unsigned int i = 0; i < triangleMesh->vertexCount; i++)
	{
		interleaved[i].x = triangleMesh->vertexPositions[i*3 + 0];
		interleaved[i].y = triangleMesh->vertexPositions[i*3 + 1];
		interleaved[i].z = triangleMesh->vertexPositions[i*3 + 2];
		
		interleaved[i].nx = triangleMesh->vertexNormals[i*3 + 0];
		interleaved[i].ny = triangleMesh->vertexNormals[i*3 + 1];
		interleaved[i].nz = triangleMesh->vertexNormals[i*3 + 2];
		
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

	prepared = true;
}

void RenderMesh21::draw(Camera *camera)
{
	if (!prepared)
		prepare();
	
	if (!shader->isPrepared())
	{
		shader->prepare();
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
	

	shader->bind();
	{
		// update shader
		GLint location;
		location = shader->getUniformLocation("modelMatrix");
		if (location >= 0)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
		
		location = shader->getUniformLocation("viewMatrix");
		if (location >= 0)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		
		location = shader->getUniformLocation("projectionMatrix");
		if (location >= 0)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
		
		
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
