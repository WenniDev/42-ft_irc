#ifndef SERVER_HPP
#define SERVER_HPP

#include "defines.hpp"
#include "PSocket.hpp"
#include "ASocket.hpp"
#include "SocEvent.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

void ft_sig_handler(int signum);

namespace TCP_IPv4 {

	class Server {
		public :
			friend void ::ft_sig_handler(int);
			typedef std::map<int, ASocket *> map_ASocket;

			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Server(std::string);
			Server(const Server &);
			virtual ~Server();
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			Server &operator=(const Server &);
	
			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			/**
			 * @brief bind the server's passive socket to the given 
			 * corresponding port (using TCP protocol and IPv4 familly) 
			 * then calls listen and adds it to socEvent handler
			 * 
			 * @param port the port on wich the socket should bind and 
			 * so the port on wich the clients should connect
			 * @exception throws TCP_IPv4::Error exception if any 
			 * system call fails
			*/
			void start(const char *);

			//accept a new connection and add it to socEvent handler
			ASocket *newConnection();

			void closeConnection(ASocket *);

			//return true if the server can accept a new connection
			bool pendingConnection() const _NOEXCEPT;

			//return true if the server is running
			bool isrunning() const _NOEXCEPT;

			//return true if the server is up
			bool isup() const _NOEXCEPT;
			
			//return true if the server is down
			bool isdown() const _NOEXCEPT;

			std::ofstream &log() _NOEXCEPT;

			//TESTING
			void runTest();

		protected :
			std::string m_name;
			std::string m_port;
			int m_state;
			PSocket m_pSocket;
			map_ASocket m_aSockets;
			SocEvent m_socEvent;
			std::ofstream m_logFile;
			std::string m_creationTime;

			void setState(int) _NOEXCEPT;

	};
}

void signal_handler(TCP_IPv4::Server *server);

#endif