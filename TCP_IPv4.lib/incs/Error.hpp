#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>
#include <iostream>
#include <errno.h>
#include <cstring>
#include "defines.hpp"

namespace TCP_IPv4 {

	class Error : public std::exception {
		public :
			Error(std::string);
			~Error() _NOEXCEPT;
			const char *what() const _NOEXCEPT;
			
		private :
			std::string m_what;
	};
}

#endif