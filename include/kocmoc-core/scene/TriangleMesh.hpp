#ifndef KOCMOC_CORE_SCENE_TRIANGLE_MESH_HPP
#define KOCMOC_CORE_SCENE_TRIANGLE_MESH_HPP

#include <map>
#include <string>

#include <glm/glm.hpp>

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

			/**
			 * The \c TriangleMesh acts as the canonical basis for triangle meshes.
			 *
			 * This representation is very close to the hardware, and also influenced
			 * by the way the assimp loader provides the data.
			 *
			 * Vertex attributes are handled by a unique \c Symbol
			 *
			 * @note	only primitives with at least 3 vertices are supported so far.
			 *			That means no line or point primitives. Primitives with more than
			 *			3 vertices are triangulated before they are sent to the GPU.
			 * @note	All data is in standard float precision unless applications
			 *			demand higher precision.
			 */

			// TODO textures

			class TriangleMesh
			{
				friend class renderer::RenderMesh;

			public:
				
				/** The vertex attribute struct.
				 * It holds together all the data needed for such an attribute.
				 *
				 * @note	All fields in this structure are const. This should be nice
				 *			when it comes to data encapsulation and such, however
				 *			it prevents the compiler from creating a default \c operator=()
				 *			This means that it can not be used like map[symbol] = bar, instead
				 *			the explicit way over pair<> and insert() has to be taken.
				 */
				struct VertexAttribute
				{
					/** the stride of the attribute. E.g stride=3 for a 3d position
					 * and stride=2 for UV coordinates */
					const types::uint stride;

					/** The attribute data array */
					const float* attributeData;

					/** whether or whether not we own the data, i.e. are allowed to delete it */
					const bool hasOwnership;

					/**
					 * construct a new vertexAttribute instance from the given data.
					 * Parameter semantics are as the fields described above
					 */
					VertexAttribute(types::uint _stride, float* _attributeData,
									bool handOverOwnership)
						: stride(_stride)
						, attributeData(_attributeData)
						, hasOwnership(handOverOwnership)
					{}

				};

				/**
				 * this struct holds all relevant texture information.
				 */
				struct Texture
				{
					/** The file name of the texture */
					const std::string fileName;

					explicit Texture(std::string _fileName)
						: fileName(_fileName)
					{}
				};

				/**
				 * Simple structure to define a bounding box.
				 * The 3d min and max coordinates define a axis aligned cube in space
				 */
				struct BoundingBox
				{
					glm::vec3 min;
					glm::vec3 max;
				};
					
				typedef std::map<types::Symbol, VertexAttribute> VertexAttributeMap;
				typedef std::map<types::Symbol, Texture> TextureMap;

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
				 * The number of unique vertices in this mesh.
				 *
				 * This since we are only allowed to have a single indices
				 * array the number of vertices in all vertex attributes is
				 * the same.
				 */
				const types::uint vertexCount;
				
				/**
				 * The index array.
				 *
				 * There is only one index array per mesh. All vertex attributes
				 * are indexed with the same indices, since hardware does not
				 * allow multiple indices per vertex.
				 */
				const types::uint* indices;

				/**
				 * Create a new \c TriangleMesh.
				 * 
				 * @param	vertexIndexCount	The number of vertex indices.
				 * @param	vertexCount			The number of unique vertices.
				 * @param	indices				The vertex indices for the mesh.
				 * @param	vertexAttributes	The vertex positions.
				 */
				TriangleMesh(types::uint vertexIndexCount, types::uint vertexCount,
							 types::uint* indices, VertexAttribute vertexPositions);

				/**
				 * deconstruct the mesh and delete the data fields it owns.
				 */
				virtual ~TriangleMesh();

				/**
				 * Add a vertex Attribute.
				 *
				 * An arbitrary number of vertex attributes can be added to a mesh
				 *
				 * @param name the name of the attribute under which it will be filed
				 * @param attribute the vertex attribute itself
				 *
				 * @note	the given vertex attribute must conform to the mesh structure
				 *			i.e. the vertex index count must match.
				 */
				void addVertexAttribute(types::Symbol name, VertexAttribute attribute);

				/**
				 * Add a texture to this mesh.
				 *
				 * @param name The name under which the texture will be filed.
				 * @param texture The texture object itself.
				 */
				void addTexture(types::Symbol name, Texture texture);

				/**
				 * Calculate the bounding box of this mesh
				 */
				BoundingBox calculateBoundingBox(void) const;

			private:

				typedef std::pair<types::Symbol, VertexAttribute > VertexAttributePair;
				typedef std::pair<types::Symbol, Texture > TexturePair;

				/** The map of vertex attributes */
				VertexAttributeMap vertexAttributes;

				/** Map of textures in this mesh */
				TextureMap textures;
			};
		}
	}
}
#endif
