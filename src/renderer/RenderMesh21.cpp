#include "RenderMesh21.hpp"

#include <iostream>

#include <GL/glfw3.h>

using namespace kocmoc::core::renderer;

using kocmoc::core::scene::Camera;

void RenderMesh21::prepare(void)
{
	strideLength = (3 + 3); // position + normal + uv + tangent
	if (triangleMesh->vertexUVs != NULL)
		strideLength += 2;
	if (triangleMesh->vertexTangents != NULL)
		strideLength += 3;
	
	
	float* interleaved = new float[triangleMesh->vertexCount * strideLength];
	
	//interleave
	for (unsigned int i = 0; i < triangleMesh->vertexCount; i++)
	{
		unsigned j = 0;
		interleaved[i*strideLength + j++] = triangleMesh->vertexPositions[i + 0];
		interleaved[i*strideLength + j++] = triangleMesh->vertexPositions[i + 1];
		interleaved[i*strideLength + j++] = triangleMesh->vertexPositions[i + 2];
		
		interleaved[i*strideLength + j++] = triangleMesh->vertexNormals[i + 0];
		interleaved[i*strideLength + j++] = triangleMesh->vertexNormals[i + 1];
		interleaved[i*strideLength + j++] = triangleMesh->vertexNormals[i + 2];
		
		if (triangleMesh->vertexUVs != NULL)
		{
			interleaved[i*strideLength + j++] = triangleMesh->vertexUVs[i + 0];
			interleaved[i*strideLength + j++] = triangleMesh->vertexUVs[i + 1];
		}
		
		if (triangleMesh->vertexTangents != NULL)
		{
			interleaved[i*strideLength + j++] = triangleMesh->vertexTangents[i + 0];
			interleaved[i*strideLength + j++] = triangleMesh->vertexTangents[i + 1];
			interleaved[i*strideLength + j++] = triangleMesh->vertexTangents[i + 2];
		}
	}
	
	vboHandle = 0;

	glGenBuffers(1, &vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, 
				 triangleMesh->vertexCount * strideLength * sizeof(float), 
				 interleaved, 
				 GL_STATIC_DRAW);
	
	delete [] interleaved;	
	
	glGenBuffers(1, &indicesHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 triangleMesh->vertexIndexCount,
				 triangleMesh->indices,
				 GL_STATIC_DRAW);

	prepared = true;
}

void RenderMesh21::draw(Camera *camera)
{
	if (!prepared)
		prepare();
	
	if (!shader->isPrepared())
		shader->prepare();
	
	UNUSED camera;
	
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
	
	// for each vertex attribute do...
	// positions
	glEnableVertexAttribArray(vertexAttributePositionIndex);
	glVertexAttribPointer(vertexAttributePositionIndex, 3, GL_FLOAT, false,
						  strideLength, 0);
	
	

	// draw
	shader->bind();
	{
		glDrawElements(GL_TRIANGLES,
					   triangleMesh->vertexIndexCount / 3,
					   GL_UNSIGNED_INT,
					   NULL);
	}
	shader->unbind();
	
	// cleanup
	glDisableVertexAttribArray(vertexAttributePositionIndex);
}
