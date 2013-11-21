#pragma once

#include <kocmoc-core/types/types.h>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			
			// vertex attribute constants
			static const char* const vertexAttributePositionName = "inPosition";
			static const types::uint vertexAttributePositionIndex = 0;
			
			static const char* const vertexAttributeNormalName = "inNormal";
			static const types::uint vertexAttributeNormalIndex = 1;
			
			static const char* const vertexAttributeUVName = "inUv";
			static const types::uint vertexAttributeUVIndex = 2;
			
			static const char* const vertexAttributeTangentName = "inTangent";
			static const types::uint vertexAttributeTangentIndex = 3;
			
			static const char* const vertexAttributeColorName = "inColor";
			static const types::uint vertexAttributeColorIndex = 4;
			
			// texture units
			static const int textureUnitDiffuse		= 0;
			static const int textureUnitSpecular	= 1;
			static const int textureUnitGloss		= 2;
			static const int textureUnitNormal		= 3;
		}
	}
}