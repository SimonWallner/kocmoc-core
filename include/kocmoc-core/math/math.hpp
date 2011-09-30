#ifndef KOCMOC_CORE_MATH_MATH_HPP
#define KOCMOC_CORE_MATH_MATH_HPP

namespace kocmoc
{
	namespace core
	{
		namespace math
		{
			template <typename T >
			int sign(T x)
			{
				return (x > 0) - (x < 0);
				// no branching sign, found on stack overflow
			}
			
			template <typename T >
			T max(T v1, T v2)
			{
				return (v1 > v2 ? v1 : v2);
			}
			
			template <typename T >
			T min(T v1, T v2)
			{
				return (v1 < v2 ? v1 : v2);
			}
		}		
	}
}

#endif
