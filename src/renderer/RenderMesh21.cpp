#include "RenderMesh21.hpp"

#include <iostream>

#include <GL/glfw3.h>

using namespace kocmoc::core::renderer;

using kocmoc::core::scene::Camera;

void RenderMesh21::prepare(void)
{
	GLuint buffer = 0;
	
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 
				 3 * triangleMesh->vertexCount * sizeof(float), 
				 triangleMesh->vertexPositions, 
				 GL_STATIC_DRAW);

	glVertexAttrib3fv(0, NULL);
}

void RenderMesh21::draw(Camera *camera)
{
	std::cout << "drawing with camera: " << camera << std::endl;
}
