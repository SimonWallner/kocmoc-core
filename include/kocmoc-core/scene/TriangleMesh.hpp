#ifndef KOCMOC_CORE_SCENE_TRIANGLE_MESH_HPP
#define KOCMOC_CORE_SCENE_TRIANGLE_MESH_HPP

#include <map>
#include <string>

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/types/types.h>


namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class RenderMesh;
		}

		namespace scene
		{
//			const types::Symbol textureDiffuseColour = types::symbolize("diffuseColour");
//			const types::Symbol textureSpecularColour = types::symbolize("specularColour");
//			const types::Symbol textureNormalMap = types::symbolize("normalMap");
//			const types::Symbol textureEmmisiveColour = types::symbolize("emmisiveColour");

			/**
			 * The \c TriangleMesh acts as the canonical basis for triangle meshes.
			 *
			 * This representation is very close to the hardware, and also influenced
			 * by the way the assimp loader provides the data.
			 *
			 * Generality is given up here for the sake of simplicity of implementation.
			 * A true general solution is not needed. Requirements are clearly 
			 * defined and are enforced by the asset pipeline. 
			 *
			 * It would be nice to be able to load ANY model, but this is a feature
			 * that would not be used often (we have full control over the asset
			 * pipeline).
			 *
			 * \section a Structure/Requirements
			 * 
			 *	\b Attributes
			 *		- position, \c vec3 (mandatory)
			 *		- normals, \c vec3 (mandatory)
			 *		- uv, \c vec2
			 *		- tangents, 
			 *
			 *	\b Textures
			 *		- diffuse colour, \c RGB
			 *		- specular colour + shinyness, \c RGBA
			 *		- normal map, \c RGB
			 *		- emmissive colour, \c RGB (TODO: change to HDR format)
			 *
			 *	\b Primitives
			 *		- indexed trianlges, no tri-strips at this time!
			 *
			 *	\b Shader
			 *		- a shader to render with (mandatory)
			 *
			 * Only position and shader are mandatory, all other parts are optional.
			 *		
			 * @note	All data is in standard float precision unless applications
			 *			demand higher precision.
			 */


			class TriangleMesh
			{
				friend class renderer::RenderMesh;

			public:
					
				/**
				 * The number of non-unique vertices in this mesh.
				 * 
				 * A cube for instance has a \c vertexIndecCount of 24 (4 sides * 4
				 * vertices per plane). However This cube would only have 8 unique
				 * vertex positions.
				 *
				 * It's the number of primitives of a certain kind times their vertex
				 * count. cube: 6 quads = 12 triangles = 12 * 3 = 36
				 *
				 * @note	the \c vertexIndexCount defines the length of the vertex index
				 *			arrays and it is constant.
				 */
				const types::uint vertexIndexCount;
				
				/**
				 * The index array.
				 *
				 * There is only one index array per mesh. All vertex attributes
				 * are indexed with the same indices, since hardware does not
				 * allow multiple indices per vertex.
				 */
				const types::uint* indices;
				
				/**
				 * The number of unique vertices in this mesh.
				 *
				 * This since we are only allowed to have a single indices
				 * array the number of vertices in all vertex attributes is
				 * the same.
				 */
				const types::uint vertexCount;
				
				/**
				 * The vertex positions. Stride = 3
				 *
				 * This array must not be \c NULL. If it were, It would not make
				 * much sense either.
				 */
				const float* vertexPositions;
				
				/**
				 * The vertex normals. Stride = 3
				 */
				const float* vertexNormals;
				
				/**
				 * The texture coordinates. Stride = 2
				 */
				const float* vertexUVs;
				
				/**
				 * The tangents used for normal mapping. Stride = ?
				 */
				const float* vertexTangents;


				/**
				 * Create a new \c TriangleMesh.
				 * 
				 * @param	vertexIndexCount	The number of vertex indices.
				 * @param	indices				The vertex indices for the mesh.
				 * @param	vertexCount			The number of unique vertices.
				 * @param	vertexPositions		mandatory, must not be \c NULL
				 * @param	vertexNormals		mandatory, must not be \c NULL
				 * @param	vertexUVs			optional, can be \c NULL
				 * @param	vertexTangents		optional, can be \c NULL
				 */
				TriangleMesh(types::uint vertexIndexCount,
							 types::uint* indices,
							 types::uint vertexCount,
							 float* vertexPositions,
							 float* vertexNormals,
							 float* vertexUVs = NULL,
							 float* vertexTangents = NULL);

				/**
				 * deconstruct the mesh and delete the data fields it owns.
				 */
				virtual ~TriangleMesh();

				/**
				 * Add a texture to this mesh.
				 *
				 * @param name The name under which the texture will be filed. 
				 *		Use on of the texture name constants defined in this 
				 *		very name space. Orther texture names might not be 
				 *		recognised.
				 * @param texture The texture object itself.
				 */
				void addTexture(types::Symbol name, std::string path);
				
				void setShader(std::string _shader)
				{
					shader = _shader;
				}

			private:
				
				typedef std::map<types::Symbol,	std::string > TextureMap;

				/** Map of textures in this mesh */
				TextureMap textures;

				/**
				 * The name of the shader to use.
				 */
				std::string shader;
			};
		}
	}
}
#endif
