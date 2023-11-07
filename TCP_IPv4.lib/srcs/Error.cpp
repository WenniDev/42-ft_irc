#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

TCP_IPv4::Error::Error(std::string what) {
	m_what = "Error: " + what;
	if (errno) {
		m_what += ": ";
		m_what += ::strerror(errno);
	};
}

TCP_IPv4::Error::~Error() _NOEXCEPT {}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

const char *TCP_IPv4::Error::what() const _NOEXCEPT {
	return m_what.c_str();
}