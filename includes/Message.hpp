/**
 * Class for messages.
 * Messages have a specific syntax in order 
 * to be detected by the IRC client.
*/

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "params.hpp"
# include "../TCP_IPv4.lib/TCP_IPv4"

using namespace TCP_IPv4;

class Message 
{
public:
	friend class IRCServer;

	// CONSTRUCTORS AND DESTRUCTOR
	Message();
	Message(std::string msg);
	Message(std::string pfx, std::string cmd, std::string args);
	Message(Message & src);
	Message & operator=(Message & src);
	~Message();

	// GETTERS
	std::string getArgs() const;

	// EXCEPTION
	class MsgError : public Error {
		public:
			MsgError(std::string what);
	};

private:
	// MEMBERS
	std::string	m_msg;
	std::string m_prefix;
	std::string m_cmd;
	vecStr 		m_args;

	// PARSING
	void	parseMsg(std::string msg);
	void	parseArgs(std::string args);
	void	checkCmdFormat(std::string str);

};

#endif