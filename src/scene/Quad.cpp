#include <kocmoc-core/scene/Quad.hpp>

#include <string>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace kocmoc::core::renderer;
using namespace kocmoc::core::scene;

using glm::gtx::quaternion::toMat4;

void Quad::draw(Camera *camera)
{	
	glm::mat4 transform = glm::gtx::transform::translate(position.x, position.y, position.z)
		* toMat4(rotation)
		* glm::gtx::transform::translate(0.0f, 3.0f, 0.0f)
		* glm::gtx::transform::scale(size.x, size.y, 1.0f);

	
	// FIXME: ugly hack, should put texture into mesh or 'ting...
	if (textureHandle)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		renderMesh->draw(camera, transform);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

Quad::Quad(Shader* shader, GLint _textureHandle)
	: textureHandle(_textureHandle)
	, position(glm::vec3(0))
	, size(glm::vec2(1))
	, rotation(glm::quat(0, glm::vec3(1, 0, 0)))
{
	float* vertices = new float[12];
	/*
	 3 ---- 2
	 |     /|
	 |   /  |
	 | /    |
	 0----- 1
	 */
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0;
	
	vertices[3] = 1;
	vertices[4] = 0;
	vertices[5] = 0;
	
	vertices[6] = 1;
	vertices[7] = 1;
	vertices[8] = 0;
	
	vertices[9] = 0;
	vertices[10] = 1;
	vertices[11] = 0;
	
	float* uv = new float[8];
	uv[0] = 0;
	uv[1] = 0;
	
	uv[2] = 1;
	uv[3] = 0;
	
	uv[4] = 1;
	uv[5] = 1;
	
	uv[6] = 0;
	uv[7] = 1;
	
	unsigned int* indices = new unsigned int[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
	
	TriangleMesh* triMesh = new TriangleMesh(6, indices, 4, vertices, NULL, uv);
	
	renderMesh = new RenderMesh21(triMesh, shader);
}
