#include <kocmoc-core/scene/TriangleMesh.hpp>

using namespace kocmoc::core::scene;

using kocmoc::core::types::symbolize;
using kocmoc::core::types::Symbol;
using kocmoc::core::types::uint;


using glm::vec3;


TriangleMesh::TriangleMesh(uint _vertexIndexCount, uint _vertexCount,
						   uint* _indices, VertexAttribute vertexPositions)
	: vertexIndexCount(_vertexIndexCount)
	, vertexCount(_vertexCount)
	, indices(_indices)
{
	vertexAttributes.insert(VertexAttributePair(symbolize("position"), vertexPositions));
}

TriangleMesh::~TriangleMesh()
{
	for (VertexAttributeMap::const_iterator ci = vertexAttributes.begin();
		ci != vertexAttributes.end();
		ci++)
	{
		if (ci->second.hasOwnership)
		{
			delete[] ci->second.attributeData;
		}
	}
}

void TriangleMesh::addVertexAttribute(Symbol name, VertexAttribute attribute)
{
	vertexAttributes.insert(VertexAttributePair(name, attribute));
}

void TriangleMesh::addTexture(Symbol name, Texture texture)
{
	textures.insert(TexturePair(name, texture));
}

TriangleMesh::BoundingBox TriangleMesh::calculateBoundingBox() const
{
	float minX, minY, minZ;
	minX = minY = minZ = std::numeric_limits<float>::max();
	float maxX, maxY, maxZ;
	maxX = maxY = maxZ = -std::numeric_limits<float>::max();

	VertexAttributeMap::const_iterator ci = vertexAttributes.find(symbolize("position"));
	const float* data = ci->second.attributeData;

	for (uint i= 0; i < vertexCount; i++)
	{
		if (data[i*3  ] < minX) minX = data[i*3  ];
		if (data[i*3+1] < minY) minY = data[i*3+1];
		if (data[i*3+2] < minZ) minZ = data[i*3+2];

		if (data[i*3  ] > maxX) maxX = data[i*3  ];
		if (data[i*3+1] > maxY) maxY = data[i*3+1];
		if (data[i*3+2] > maxZ) maxZ = data[i*3+2];
	}
	
	BoundingBox bb;
	bb.min = vec3(minX, minY, minZ);
	bb.max = vec3(maxX, maxY, maxZ);
	return bb;
}
