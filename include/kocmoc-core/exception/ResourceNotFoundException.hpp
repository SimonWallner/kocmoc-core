#ifndef KOCMOC_CORE_EXCEPTION_EXCEPTION_HPP
#define KOCMOC_CORE_EXCEPTION_EXCEPTION_HPP

#include <exception>

namespace kocmoc
{
	namespace core
	{
		namespace exception
		{
			class ResourceNotFoundException : public virtual std::exception
			{
				virtual const char* what() const throw()
				{
					return "Resource not found!";
				}
			};
		}
	}
}

#endif
