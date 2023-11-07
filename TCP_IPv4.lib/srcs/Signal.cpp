#include "Server.hpp"
#include <signal.h>

TCP_IPv4::Server *g_server;

void signal_handler(TCP_IPv4::Server *server) {
	g_server = server;
	struct sigaction act, oldact;
	::memset(&act, 0, sizeof(act));
	::memset(&oldact, 0, sizeof(oldact));
	act.sa_handler = ft_sig_handler;
	oldact.sa_handler = SIG_DFL;
	::sigaction(SIGINT, &act, &oldact);
}

void ft_sig_handler(int signum) {
	std::cout << std::endl;
	if (signum == SIGINT)
		g_server->setState(DOWN);
}