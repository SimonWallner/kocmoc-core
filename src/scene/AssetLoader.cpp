//
//  AssetLoader.cpp
//  kocmoc
//
//  Created by Simon Wallner on 27.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <kocmoc-core/scene/AssetLoader.hpp>

#include <iostream>

#include <kocmoc-core/gl.h>

#include <assimp/aiScene.h>
#include <assimp/DefaultLogger.h>
#include <assimp/LogStream.h>

#include <kocmoc-core/component/Renderable.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/types/types.h>
#include <kocmoc-core/scene/TriangleMesh.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/util/util.hpp>

#include <kocmoc-core/renderer/RenderMesh21.hpp>

using namespace kocmoc::core::scene;
using namespace Assimp;

using std::string;

using kocmoc::core::component::Renderable;
using kocmoc::core::types::uint;
using kocmoc::core::scene::TriangleMesh;
using kocmoc::core::renderer::RenderMesh21;
using kocmoc::core::renderer::Shader;

void AssetLoader::addResourcePath(const string path)
{
	resourcePaths.push_back(path);
}

Renderable* AssetLoader::load(const string modelName, const string shaderPath)
{
	Renderable* renderable = new Renderable();
	Shader* shader;
	RenderMesh21* renderMesh;
	
	string absolutePath = findAbsolutePathInResources(modelName);	
	std::cout << "trying to load asset: " << absolutePath << std::endl;
	
	const aiScene* scene = importer.ReadFile(absolutePath,
											 aiProcess_Triangulate
											 | aiProcess_SortByPType
//											 | aiProcess_CalcTangentSpace
											 | aiProcess_ImproveCacheLocality
//											 | aiProcess_FlipWindingOrder
//											 | aiProcess_GenUVCoords
											 );

	
	if (!scene) // error
	{
		std::cout << "Assimp asset loading error" << importer.GetErrorString() << std::endl;
	}
	else
	{
		if (scene->HasMeshes())
		{
			for (uint i = 0; i < scene->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[i];
				if (mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE)
				{
					uint vertexCount = mesh->mNumVertices;
					uint vertexIndexCount = mesh->mNumFaces * 3;

					uint* indices = new uint[vertexIndexCount];
					for (uint j = 0; j < mesh->mNumFaces; j++)
					{
						indices[j*3  ] = mesh->mFaces[j].mIndices[0];
						indices[j*3+1] = mesh->mFaces[j].mIndices[1];
						indices[j*3+2] = mesh->mFaces[j].mIndices[2];
					}
					
					float* positions = new float[vertexCount * 3];
					for (uint j = 0; j < vertexCount; j++)
					{
						positions[j*3  ] = mesh->mVertices[j].x;
						positions[j*3+1] = mesh->mVertices[j].y;
						positions[j*3+2] = mesh->mVertices[j].z;
					}
					
					float* normals = NULL;
					if (mesh->HasNormals())
					{
						normals = new float[vertexCount * 3];
						for (uint j = 0; j < vertexCount; j++)
						{
							normals[j*3  ] = mesh->mNormals[j].x;
							normals[j*3+1] = mesh->mNormals[j].y;
							normals[j*3+2] = mesh->mNormals[j].z;
						}
					}
					
					float* uvs = NULL;
					if (mesh->HasTextureCoords(0))
					{
						uvs = new float[vertexCount * 2];
						for (uint j = 0; j < vertexCount; j++)
						{
							uvs[j*2  ] = mesh->mTextureCoords[0][j].x;
							uvs[j*2+1] = mesh->mTextureCoords[0][j].y;
						}
					}
					
					TriangleMesh* triangleMesh = new TriangleMesh(vertexIndexCount,
																 indices,
																 vertexCount,
																 positions,
																 normals,
																 uvs);
					
					shader = new Shader(shaderPath + ".vert", shaderPath + ".frag");
					
					renderMesh = new RenderMesh21(triangleMesh, shader);
					renderable->add(renderMesh);
				}	
			}
			
			// use only first material for now!
			std::cout << "material count: " << scene->mNumMaterials << std::endl;
			if (scene->mNumMaterials > 0)
			{
				aiMaterial* material = scene->mMaterials[0];
				aiString* path = new aiString();
				
				// FIXME: refactor!
				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					material->GetTexture(aiTextureType_DIFFUSE, 0, path);
					std::string imageName = util::getFileName(string(path->data));
					std::cout << "diffuse texture 0: " << imageName << std::endl;
					GLuint handle = imageLoader->loadImage(findAbsolutePathInResources("/textures/" + imageName));
					renderMesh->addTexture(handle, renderer::textureUnitDiffuse);
				}
				
				if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
				{
					material->GetTexture(aiTextureType_SPECULAR, 0, path);
					std::string imageName = util::getFileName(string(path->data));
					std::cout << "diffuse texture 0: " << imageName << std::endl;
					GLuint handle = imageLoader->loadImage(findAbsolutePathInResources("/textures/" + imageName));
					renderMesh->addTexture(handle, renderer::textureUnitSpecular);
				}
				
				if (material->GetTextureCount(aiTextureType_SHININESS) > 0)
				{
					material->GetTexture(aiTextureType_SHININESS, 0, path);
					std::string imageName = util::getFileName(string(path->data));
					std::cout << "diffuse texture 0: " << imageName << std::endl;
					GLuint handle = imageLoader->loadImage(findAbsolutePathInResources("/textures/" + imageName));
					renderMesh->addTexture(handle, renderer::textureUnitGloss);
				}
				
				if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
				{
					material->GetTexture(aiTextureType_NORMALS, 0, path);
					std::string imageName = util::getFileName(string(path->data));
					std::cout << "diffuse texture 0: " << imageName << std::endl;
					GLuint handle = imageLoader->loadImage(findAbsolutePathInResources("/textures/" + imageName));
					renderMesh->addTexture(handle, renderer::textureUnitNormal);
				}
			}
		}
		std::cout << "loading successful" << std::endl;
		
	}
	return renderable;
}

AssetLoader::AssetLoader()
	:imageLoader(new ImageLoader)
{
	// Create a logger instance 
	DefaultLogger::create("", Logger::VERBOSE);
	DefaultLogger::get()->attachStream(LogStream::createDefaultStream(aiDefaultLogStream_STDOUT));
	
	// Now I am ready for logging my stuff
	DefaultLogger::get()->info("logging starts here...");	
	
}

AssetLoader::~AssetLoader()
{
	// Kill it after the work is done
	DefaultLogger::kill();
	
	delete imageLoader;
}

string AssetLoader::findAbsolutePathInResources(const string name) const throw(exception::ResourceNotFoundException)
{
	for (ResourcePathList::const_iterator ci = resourcePaths.begin();
		 ci != resourcePaths.end();
		 ci++)
	{
		string absolutePath = (*ci) + name;
		if (util::file_exists(absolutePath))
			return absolutePath;
	}
	
	std::cout << name << " not found in resources" << std::endl;
	exception::ResourceNotFoundException e;
	throw e;
}
