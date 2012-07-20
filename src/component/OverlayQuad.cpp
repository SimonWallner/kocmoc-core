#include <kocmoc-core/component/OverlayQuad.hpp>

#include <glm/gtx/transform.hpp>

#include <kocmoc-core/renderer/RenderMesh21.hpp>


using namespace kocmoc::core::component;
using kocmoc::core::renderer::RenderPass;
using kocmoc::core::renderer::Shader;
using kocmoc::core::scene::Camera;
using kocmoc::core::scene::TriangleMesh;
using kocmoc::core::renderer::RenderMesh21;

using std::string;

void OverlayQuad::onRender(RenderPass pass, Camera* camera)
{
	if (pass == renderer::RP_OVERLAY)
	{
		glm::mat4 transform = glm::translate(position.x, position.y, 0.0f)
			* glm::scale(scale.x, scale.y, 1.0f);
		
		// FIXME: ugly hack, should put texture into mesh or 'ting...
		if (texture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			renderMesh->draw(camera, transform);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void OverlayQuad::init()
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
	
	string mediaPath = props->getString(types::symbolize("core-media-path"));
	
	if (shader == NULL)
		shader = new Shader(mediaPath + "shaders/overlay.vert", mediaPath + "shaders/overlay.frag");
	
	renderMesh = new RenderMesh21(triMesh, shader);
}
