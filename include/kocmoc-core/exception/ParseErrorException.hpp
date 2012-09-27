#ifndef KOCMOC_CORE_EXCEPTION_PARSE_ERROR_EXCEPTION_HPP_
#define KOCMOC_CORE_EXCEPTION_PARSE_ERROR_EXCEPTION_HPP_

#include <string>
#include <exception>

namespace kocmoc
{
	namespace core
	{
		namespace exception
		{
			class ParseErrorException : public virtual std::exception
			{
			public:
				ParseErrorException(std::string _error)
					: error(_error)
				{}
				
				// i.e. no-throw distructor
				~ParseErrorException() throw()
				{}
				
				virtual const char* what() const throw()
				{
					std::string msg = "Parse Error!\n" + error;
					return msg.c_str();
				}
				
			private:
				std::string error;
			};
		}
	}
}


#endif
