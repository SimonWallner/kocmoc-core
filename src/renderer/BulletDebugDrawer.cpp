#include <kocmoc-core/renderer/BulletDebugDrawer.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <kocmoc-core/scene/Camera.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/renderer/constants.hpp>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::renderer;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

BulletDebugDrawer::BulletDebugDrawer(Shader* _shader)
	: vboAllocatedSize(0)
	, shader(_shader)
	, cnt(0)
{
	glGenBuffers(1, &vboHandle);
	
	shader->prepare();
	shader->bind();
	viewMatrixLocation = shader->getUniformLocation("viewMatrix");
	projectionMatrixLocation = shader->getUniformLocation("projectionMatrix");
	shader->unbind();
}

void BulletDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to,
								 const btVector3 &color)
{
	drawLine(from, to, color, color);
}

void BulletDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to,
							 const btVector3 &fromColor, const btVector3 &toColor)
{
	cnt++;

	interleavedLineData.push_back(from.getX());
	interleavedLineData.push_back(from.getY());
	interleavedLineData.push_back(from.getZ());
	interleavedLineData.push_back(fromColor.getX());
	interleavedLineData.push_back(fromColor.getY());
	interleavedLineData.push_back(fromColor.getZ());
	interleavedLineData.push_back(to.getX());
	interleavedLineData.push_back(to.getY());
	interleavedLineData.push_back(to.getZ());
	interleavedLineData.push_back(toColor.getX());
	interleavedLineData.push_back(toColor.getY());
	interleavedLineData.push_back(toColor.getZ());
}

void BulletDebugDrawer::draw(scene::Camera* camera)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	
	// reallocate GPU buffer if we need to draw more lines than last frame
	if (interleavedLineData.size() > vboAllocatedSize)
	{
		unsigned int newVboAllocatedSize = interleavedLineData.size() * 1.5; // *1.5 is for extra padding to avoid ongoing reallocation
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(float) * newVboAllocatedSize,
					 NULL,
					 GL_DYNAMIC_DRAW);
		vboAllocatedSize = newVboAllocatedSize;
	}
	
	// copy data
	glBufferSubData(GL_ARRAY_BUFFER,
					0, // offset
					sizeof(float) * interleavedLineData.size(),
					interleavedLineData.data());
	
	
	// drawing
	if (!shader->isPrepared())
	{
		shader->prepare();
	}
	
	shader->bind();
	if (viewMatrixLocation >= 0)
	{
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	}
	
	if (projectionMatrixLocation >= 0)
	{
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
	}
	
	
	glEnableVertexAttribArray(vertexAttributePositionIndex);
	glVertexAttribPointer(vertexAttributePositionIndex, 3, GL_FLOAT, false,
						  sizeof(float) * 3, 0);
	
	glEnableVertexAttribArray(vertexAttributeColorIndex);
	glVertexAttribPointer(vertexAttributeColorIndex, 3, GL_FLOAT, false,
						  sizeof(float) * 3, BUFFER_OFFSET(sizeof(float) * 3));
	
	
	glDrawArrays(GL_LINES, 0, interleavedLineData.size() / 12);
	
	// cleanup
	glDisableVertexAttribArray(vertexAttributePositionIndex);
	glDisableVertexAttribArray(vertexAttributeColorIndex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BulletDebugDrawer::clear()
{
	interleavedLineData.clear();
	cnt = 0;
}

void BulletDebugDrawer::reportErrorWarning (const char* warningString)
{
	objectifLune::Singleton::Get()->warn(warningString);
}


int BulletDebugDrawer::getDebugMode() const
{
	return DBG_DrawWireframe;
}

