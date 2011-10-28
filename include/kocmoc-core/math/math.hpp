#ifndef KOCMOC_CORE_MATH_MATH_HPP
#define KOCMOC_CORE_MATH_MATH_HPP

#include <glm/glm.hpp>
#include <kocmoc-core/compiler.h>

namespace kocmoc
{
	namespace core
	{
		namespace math
		{
			static const float pi = 3.1415926535897932384f;
			
			template <typename T >
			inline int sign(T x)
			{
				return (x > 0) - (x < 0);
				// no branching sign, found on stack overflow
			}
			
			template <typename T >
			inline T max(T v1, T v2)
			{
				return (v1 > v2 ? v1 : v2);
			}
			
			template <typename T >
			inline T min(T v1, T v2)
			{
				return (v1 < v2 ? v1 : v2);
			}
			

			/**
			 * constrained point to ray distance.
			 * @return the smallest distance from a point to a ray. If the point
			 *		lies behing the origin (t0 <= 0), -1 is returned. 
			 */
			inline float pointToRayDistance(glm::vec3 position,
									 glm::vec3 origin, glm::vec3 direction)
			{
				float t0 = glm::dot(direction, position - origin) / 
							glm::dot(direction, direction);
				
				if (t0 > 0)
					return glm::length(position - (origin + t0 * direction));
				else
					return -1;
			}
			
			/**
			 * convert degrees into radians
			 */
			inline float deg2Rad(float deg)
			{
				return deg * (pi / 180);
			}
			
			/**
			 * convert a polar coordinate into a cartesian coordinate
			 * @param rad angle in radians
			 * @param r radius
			 */
			inline glm::vec2 pol2Cart(float rad, float r)
			{
				glm::vec2 res;
				res.x = cos(rad) * r;
				res.y = sin(rad) * r;
				return res;
			}
		}		
	}
}

#endif
