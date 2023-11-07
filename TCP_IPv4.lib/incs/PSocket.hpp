#ifndef PSOCKET_HPP
#define PSOCKET_HPP

#include "defines.hpp"
#include "Socket.hpp"
#include "ASocket.hpp"
#include <netdb.h>

namespace TCP_IPv4 {

	/**
	 * @brief  * Class for passive sockets using TCP on IPv4
 	 * passive sockets are bind to an address and
 	 * will wait for an incoming connection that
 	 * will create a new active socket
	*/
	class PSocket : public Socket {
		public :
			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			PSocket();
			PSocket(const PSocket &);
			~PSocket() _NOEXCEPT;
	
			/*------------------------------------*/
			/*             Operators              */
			/*------------------------------------*/

			PSocket &operator=(const PSocket &);

			/*------------------------------------*/
			/*              Methods               */
			/*------------------------------------*/

			//bind the socket to the given address
			void bind(const sockaddr *);

			//set the soket in listening mode awaiting incoming connections
			void listen();

			/**accept a new connection and returns a pointer to 
			 * a new active socket representing the connection
			*/
			ASocket *accept();
	
		private :
			//Max length for the connexion queue
			static const int m_backlog = 5;
	};
}

#endif