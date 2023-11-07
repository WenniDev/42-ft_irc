#include "ASocket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::ASocket::ASocket() : TCP_IPv4::Socket() {}

TCP_IPv4::ASocket::ASocket(struct sockaddr serverAddr) : TCP_IPv4::Socket() {
	if ((m_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw TCP_IPv4::Error("socket");
	if (::connect(m_fd, &serverAddr, sizeof(serverAddr)) == -1)
		throw TCP_IPv4::Error("connect");
}

TCP_IPv4::ASocket::ASocket(int fd, sockaddr addr) : TCP_IPv4::Socket() {
	m_fd = fd;
	m_addr = addr;
	m_type = ACTIVE;
	m_evFlags |= EPOLLIN | EPOLLOUT;
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	if (::getnameinfo(&m_addr, sizeof(m_addr), host, sizeof(host), serv, sizeof(serv), NI_NAMEREQD) == -1)
		throw TCP_IPv4::Error("getnameinfo");
	m_host = host;
	m_serv = serv;
}

TCP_IPv4::ASocket::ASocket(const ASocket &other) : TCP_IPv4::Socket() {
	*this = other;
}

TCP_IPv4::ASocket::~ASocket() _NOEXCEPT {
	this->close();
}

/*------------------------------------*/
/*              Operators             */
/*------------------------------------*/

TCP_IPv4::ASocket &TCP_IPv4::ASocket::operator=(const ASocket &other) {
	Socket::operator=(other);
	m_rdbuf = other.m_rdbuf;
	m_wrbuf = other.m_wrbuf;
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

int TCP_IPv4::ASocket::send() {
	int nb;
	if (!this->isWriteable())
		throw TCP_IPv4::Socket::Failure(ERR_NOTWRITEABLE);
	do {
		nb = ::send(m_fd, m_wrbuf.c_str(), m_wrbuf.size(), 0);
		if (nb == -1) {
			if (errno != EAGAIN)
				throw TCP_IPv4::Error("send");
		}
		else
			m_wrbuf.erase(0, nb);
	} while (nb > 0);
	if (errno == EAGAIN) {
		m_evFlags &= ~EPOLLOUT;
		errno = 0;
	}
	m_wrbuf.clear();
	return nb;
}

int TCP_IPv4::ASocket::receive(int flags) {
	if (!this->isReadable())
		throw TCP_IPv4::Socket::Failure(ERR_NOTREADABLE);
	int nb;
	int ret = 0;
	char buf[m_rdsize + 1];
	do {
		nb = ::recv(m_fd, buf, m_rdsize, flags);
		if (nb == -1) {
			if (errno != EAGAIN)
				throw TCP_IPv4::Error("recv");
		}
		else {
			buf[nb] = '\0';
			m_rdbuf += buf;
			ret += nb;
		}
	} while (nb > 0);
	if (errno == EAGAIN) {
		m_evFlags &= ~EPOLLIN;
		errno = 0;
	}
	return ret;
}

void TCP_IPv4::ASocket::write(std::string msg) _NOEXCEPT {
	m_wrbuf += msg;
}

bool TCP_IPv4::ASocket::pendingData() const _NOEXCEPT {
	return !m_rdbuf.empty();
}

bool TCP_IPv4::ASocket::dataToSend() const _NOEXCEPT {
	return !m_wrbuf.empty();
}

bool TCP_IPv4::ASocket::extractData(std::string &dest, std::string sep) _NOEXCEPT {
	size_t pos;
	if (sep.empty()) {
		dest = m_rdbuf;
		m_rdbuf.clear();
		return true;
	}
	pos = m_rdbuf.find(sep);
	if (pos != std::string::npos) {
		dest = m_rdbuf.substr(0, pos);
		m_rdbuf.erase(0, pos + sep.length());
		return true;
	}
	return false;
}

const std::string &TCP_IPv4::ASocket::host() const _NOEXCEPT {
	return m_host;
}

const std::string &TCP_IPv4::ASocket::serv() const _NOEXCEPT {
	return m_serv;
}