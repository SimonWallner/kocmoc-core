#include <kocmoc-core/Component/PointSprite.hpp>

#include <string>
#include <glm/gtx/transform.hpp>

using namespace kocmoc::core::component;
using namespace kocmoc::core::renderer;
using namespace kocmoc::core::scene;

void PointSprite::onRender(RenderPass pass, Camera *camera)
{
	if (pass == RP_NORMAL)
	{		
		glm::mat4 transform = glm::gtx::transform::translate(position.x, position.y + 3.0f, position.z)
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
}

void PointSprite::init()
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
