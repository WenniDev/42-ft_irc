#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <exception>

# ifndef _NOEXCEPT
# define _NOEXCEPT _GLIBCXX_NOTHROW
# endif //_NOEXCEPT

enum serverState {
	UP,
	RUNNING,
	DOWN
};

enum socketType {
	ACTIVE,
	PASSIVE
};

enum logMode {
	CREATE,
	STATE,
	CONNECTION,
	COMMAND
};

#define ERR_NOTWRITEABLE	"socket is not writeable"
#define ERR_NOTREADABLE		"socket is not readable"

#define CRLF "\r\n"

#endif //DEFINES_HPP