#pragma once

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#include <btBulletDynamicsCommon.h>
#pragma GCC diagnostic pop

#include <kocmoc-core/gl.h>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class Camera;
		}
		
		namespace renderer
		{
			class Shader;
			
			class BulletDebugDrawer : public btIDebugDraw
			{
				
			public:
				BulletDebugDrawer(Shader* shader);
				
				void drawLine(const btVector3& from,const btVector3& to,
							  const btVector3& color);
				void drawLine(const btVector3& from, const btVector3& to,
							  const btVector3& fromColor, const btVector3& toColor);
								
				void reportErrorWarning (const char* warningString);
				
				
				int getDebugMode() const;
				
				void draw(scene::Camera* camera);
				void clear();
				
				// not implemented
				#pragma GCC diagnostic push
				#pragma GCC diagnostic ignored "-Wunused-parameter"
				void drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB,
									   btScalar distance, int lifeTime, const btVector3 &color) {}
				void draw3dText (const btVector3 &location, const char *textString) {}
				void setDebugMode (int debugMode) {}
				#pragma GCC diagnostic pop
				
			private:
				std::vector<float> interleavedLineData;
				GLuint vboHandle;
				unsigned int vboAllocatedSize;
				
				Shader* shader;
				
				GLint viewMatrixLocation;
				GLint projectionMatrixLocation;
				
				unsigned int cnt;
			};
		}
	}
}
