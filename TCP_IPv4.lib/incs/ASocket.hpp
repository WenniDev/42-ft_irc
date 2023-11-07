#ifndef ASOCKET_HPP
#define ASOCKET_HPP

#include "defines.hpp"
#include "Socket.hpp"
#include "SocEvent.hpp"
#include <errno.h>
#include <netdb.h>

namespace TCP_IPv4 {

	/**
	 * @brief Class for active sockets using TCP on IPv4.
 	 * Active sockets are used by clients who initiate 
 	 * the connexion for exchanging data.
	*/
	class ASocket : public Socket {
		public :
			friend class SocEvent;

			/*------------------------------------*/
			/*     Constructors and destructor    */
			/*------------------------------------*/

			ASocket();
			ASocket(struct sockaddr);
			ASocket(int, sockaddr);
			ASocket(const ASocket &);
			~ASocket() _NOEXCEPT;
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			ASocket &operator=(const ASocket &);

			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			/**
			 * @brief send the content of m_wtbuf to m_fd consuming the 
			 * readable event and clearing the m_wtbuf.
			 * 
			 * @return the number of bytes send
			 * @exception throws a TCP_IPv4::Socket::Failure exception if socket 
			 * is not writeable or if the connexion on the socket is down.
			 * @exception throws a TCP_IPv4::Error exception if send fails.
			*/
			int send();

			/**
			 * @brief read m_rdsize bytes from m_fd to m_rdbuf as long as
			 * there is something to read and EAGAIN is not returned. (on a 
			 * non blocking socket EAGAIN is returned if the operation would 
			 * nomally block). If no error occured the readable event is consumed.
			 * 
			 * @param flags the flags to pass to recv (if not set defaults to 0)
			 * @return the total number of bytes read
			 * @exception throws a TCP_IPv4::Socket::Failure exception if socket 
			 * is not readable or if the connexion on the socket is down.
			 * @exception throws a TCP_IPv4::Error exception if recv fails.
			*/
			int receive(int = 0);

			//write the msg to m_wrbuf
			void write(std::string) _NOEXCEPT;

			bool dataToSend() const _NOEXCEPT;

			bool pendingData() const _NOEXCEPT;

			bool extractData(std::string &, std::string = "\0") _NOEXCEPT;

			const std::string &host() const _NOEXCEPT;

			const std::string &serv() const _NOEXCEPT;

		private :
			//reading buffer
			std::string m_rdbuf;

			//writing buffer
			std::string m_wrbuf;

			//max reading size
			static const size_t m_rdsize = 1024;

			//host name
			std::string m_host;

			//service number
			std::string m_serv;
	};
}

#endif