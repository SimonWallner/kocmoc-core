#include <kocmoc-core/scene/TriangleMesh.hpp>

using namespace kocmoc::core::scene;

using kocmoc::core::types::symbolize;
using kocmoc::core::types::Symbol;


TriangleMesh::TriangleMesh(unsigned int _vertexIndexCount,
						   unsigned int* _indices,
						   unsigned int _vertexCount,
						   float* _vertexPositions,
						   float* _vertexNormals,
						   float* _vertexUVs,
						   float* _vertexTangents)
	: vertexIndexCount(_vertexIndexCount)
	, indices(_indices)
	, vertexCount(_vertexCount)
	, vertexPositions(_vertexPositions)
	, vertexNormals(_vertexNormals)
	, vertexUVs(_vertexUVs)
	, vertexTangents(_vertexTangents)
	, shader("undefined")
{}

TriangleMesh::~TriangleMesh()
{
	// TODO cleanup!
}

void TriangleMesh::addTexture(Symbol name, std::string path)
{
	textures[name] = path;
}
