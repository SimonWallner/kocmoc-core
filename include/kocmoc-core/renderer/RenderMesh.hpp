#ifndef KOCMOC_CORE_RENDERER_RENDER_MESH_HPP
#define KOCMOC_CORE_RENDERER_RENDER_MESH_HPP

#include <vector>

#include <glm.hpp>

#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/scene/PolyMesh.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace scene
		{
			class LineGizmo;
		}

		namespace camera
		{
			class Camera;
		}

		namespace renderer
		{
			// TODO add shader attribute semantic hint/explanation/ref

			/**
			 * Wrap a polyMesh so that we can enhance it with further properties
			 * and finally render it.
			 *
			 * Practically a RenderMesh is friends with a PolyMesh in order to ease
			 * cooperation. This is indeed tight coupling, but it seems appropriate
			 * here.
			 */
			class RenderMesh
			{
			public:
				// TODO: rename to polyMesh
				const scene::PolyMesh* mesh;
				Shader* shader;

				RenderMesh(scene::PolyMesh* mesh, Shader* shader);
				~RenderMesh(void);

				void draw(glm::mat4 parentTransform, camera::Camera *camera);

				void setModelMatrix(glm::mat4 _modelMatrix);

				uint getVertexCount(void);

			private:
				
				typedef std::vector<RenderTexture > RenderTextureList;

				/** A texture wrapper */
				struct RenderTexture
				{
					const GLuint handle;
					const GLuint textureUnit;

					RenderTexture(GLuint _handle, GLuint _textureUnit)
						: handle(_handle)
						, textureUnit(_textureUnit)
					{};
				};

				RenderTextureList renderTextures;

				glm::mat4 modelMatrix;

				bool isUploaded;

				GLuint vaoHandle;
				uint triangulatedVertexIndexCount;

				scene::LineGizmo* originGizmo;
				scene::LineGizmo* boundingBox;

				glm::mat4 bbTransform;

				// uniform locations
				GLint uniformCameraPosition;
				GLint uniformProjectionMatrix;
				GLint uniformViewMatrix;
				GLint uniformModelMatrix;

				bool uniformsAreSet;

				bool debugDrawMeshGizmo;
				

				void uploadData(void);
				
				/** Set up the textures.
				 * 
				 * - read bindings from shader
				 * - fetch specified textures from poly mesh
				 * - load these textures 
				 * - store in render textures
				 */
				void setUpTextures(void);
			};
		}
	}
}


#endif