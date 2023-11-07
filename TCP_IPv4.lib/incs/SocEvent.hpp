#ifndef SOCEVENT_HPP
#define SOCEVENT_HPP

#include "defines.hpp"
#include "Socket.hpp"
#include "Error.hpp"
#include <sys/epoll.h>
#include <map>

namespace TCP_IPv4 {

	class Socket;

	/**
	 * @brief class to monitor and handle events on sockets 
	 * using epoll system call
	*/
	class SocEvent {
		public :
			typedef std::map<int, Socket *> socketMap;

			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/
			
			SocEvent();
			~SocEvent();

			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			//add a socket to the poll
			void add(Socket *, int);

			void del(Socket *);

			//wait for event to occur an modify the corresponding sockets
			void wait();

		private :
			int m_fd;

			//a map of every sockets currently in the poll
			socketMap m_sockets;

			//array of struct representing events that occured after a call to wait
			struct epoll_event *m_events;

			int m_eventNb;
			static const int m_maxEvents = 1;
	};
}

#endif //SOCEVENT_HPP