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
			 * could be a branch free abs function found on stackoverflow. 
			 * not verified.
			 * http://stackoverflow.com/questions/9772348/get-absolute-value-without-using-abs-function-nor-if-statement
			 */
			template <typename T >
			inline T abs(T a)
			{
				return (a * ((a > 0) - (a < 0)));
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
			 * convert degrees to radians
			 */
			inline float deg2Rad(float deg)
			{
				return deg * (pi / 180.0f);
			}
			
			/**
			 * convert radians to degrees
			 */
			inline float rad2Deg(float radians)
			{
				return radians / (pi / 180.0f);
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
			
			/**
			 * decay constant for exponential decay
			 * @param half-life time
			 * @return lambda
			 */
			inline float decayConst(float halfLife)
			{
				return log(2.0f) / halfLife;
			}
			
			/**
			 * exponential decay with half-life lambda and time t
			 * @lambda half-life constant
			 * @t delta t
			 * @return ration of N0/N
			 */
			inline float decay(float lambda, float t)
			{
				return exp(-lambda * t);
			}
			
			/**
			 * compute the delta v vector resulting of a force applied
			 * to an object of mass m in unit time
			 *
			 * @param F force in newton
			 * @param m mass in kg
			 * @return delta v 
			 */
			inline glm::vec3 applyForce(glm::vec3 F, float m)
			{
				return F / m; 
			}
			
			/**
			 * compute the plane-ray intersection point
			 * @param x0 point on the plane
			 * @param n plane normal vector
			 * @param r0 point on the ray
			 * @param v ray direction
			 * @return intersection point
			 * 
			 * @note http://cgafaq.info/wiki/Ray_Plane_Intersection
			 */
			inline glm::vec3 planeRayIntersection(glm::vec3 x0, glm::vec3 n,
									   glm::vec3 r0, glm::vec3 v)
			{
				float t = -glm::dot(n, (r0 - x0)) / glm::dot(n, v);
				return r0 + v * t;
			}
		}		
	}
}

#endif
