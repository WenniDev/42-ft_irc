#include "Socket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constrcutors and destructor     */
/*------------------------------------*/

TCP_IPv4::Socket::Socket() : m_fd(-1), m_evFlags(0), m_type(ACTIVE) {}

TCP_IPv4::Socket::Socket(const Socket &other) {
	*this = other;
}

TCP_IPv4::Socket::~Socket() _NOEXCEPT {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::Socket &TCP_IPv4::Socket::operator=(const Socket &other) {
	m_fd = other.m_fd;
	m_type = other.m_type;
	m_addr = other.m_addr;
	m_evFlags = other.m_evFlags;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void TCP_IPv4::Socket::close() {
	if (::close(m_fd) != 0)
		throw TCP_IPv4::Error("close");
}

int TCP_IPv4::Socket::fd() const _NOEXCEPT {
	return (m_fd);
}

void TCP_IPv4::Socket::setNonBlock() {
	if (fcntl(m_fd, F_SETFL, O_NONBLOCK) == -1)
		throw TCP_IPv4::Error("fcntl");
}

void TCP_IPv4::Socket::setNoLinger() {
	struct linger linger;
	linger.l_onoff = true;
	linger.l_linger = 0;
	if (::setsockopt(m_fd, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger)) == -1)
		throw TCP_IPv4::Error("setsockopt");
}

bool TCP_IPv4::Socket::isReadable() const _NOEXCEPT {
	return (m_evFlags & EPOLLIN);
}

bool TCP_IPv4::Socket::isWriteable() const _NOEXCEPT {
	return (m_evFlags & EPOLLOUT);
}

/*------------------------------------*/
/*             Exceptions             */
/*------------------------------------*/

TCP_IPv4::Socket::Failure::Failure(std::string what) : TCP_IPv4::Error(what) {}