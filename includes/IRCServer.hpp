#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "Channel.hpp"
#include "User.hpp"
#include "Message.hpp"
#include "../TCP_IPv4.lib/TCP_IPv4"
#include "params.hpp"

using namespace TCP_IPv4;

class IRCServer : public TCP_IPv4::Server
{
public:
	// CONSTRUCTORS AND DESTRUCTORS
	IRCServer(std::string name);
	IRCServer(std::string name, std::string pwd);
	IRCServer(const IRCServer &src);
	IRCServer &operator=(const IRCServer &src);
	virtual ~IRCServer();

	// EXECUTION
	void checkEvents();

private:
	// PASSWORD
	std::string m_pwd;

	// VECTOR FOR STORAGE (users, channels)
	vecUser		m_users;
	vecChan		m_channels;

	// MAPS FOR EASY FIND (users, channels)
	mapChannel	m_mapChan;
	mapUser		m_mapUser;

	// EXECUTION
	int executeCommand(User *user, std::string cmd);

	// BASIC USER COMMANDS
	void	passCmd(User *user, Message &msg);
	void	nickCmd(User *user, Message &msg);
	void	userCmd(User *user, Message &msg);
	void	joinCmd(User *user, Message &msg);
	void	namesCmd(User *user, Message &msg);
	void	partCmd(User *user, Message &msg);
	void	quitCmd(User *user, Message &msg);
	void	privmsgCmd(User *user, Message &msg);
	void	noticeCmd(User *user, Message &msg);
	void	topicCmd(User *user, Message &msg);

	// OPERATOR COMMANDS
	void	operCmd(User *user, Message &msg);
	void	kickCmd(User *user, Message &msg);
	void	inviteCmd(User *user, Message &msg);
	void	modeCmd(User *user, Message &msg);

	// CLIENT COMMANDS
	void	pingCmd(User *user, Message &msg);
	void	whoisCmd(User *user, Message &msg);
	void	whoCmd(User *user, Message& msg);

	// SERVER SETTERS (users, channels, memory)
	void	addUser(ASocket *socket);
	void	addChannel(std::string name, User *user);
	void	addChannel(std::string name, std::string pwd, User *user);
	void	removeUser(User *user);
	void	removeChannel(std::string name);
	void	freeMemory(void);

	// PARSING
	void	checkNickDup(std::string nick, User *user);
	void	checkNickFormat(std::string type, User *user);
	void	checkChanFormat(std::string name, User *user);

	// MESSAGE MANAGEMENT
	static std::string buildReply(User *user, std::string what);
	static std::string buildReply(User *user, std::string what, std::string arg);
	static std::string buildReply(User *user, std::string what, std::string arg1, std::string arg2);
	vecStr	parseMsgArgs(std::string arg);
	void	writeWelcome(User *user, std::string nick);
	void	writeToClient(User *user, std::string prefix, std::string reply);
	void	writeToChannel(User *sender, Channel *channel, bool inclSender, std::string fullMsg);
	void	writeToOps(Channel *channel, std::string fullMsg);
	void	writeToRelations(User *user, std::string fullMsg);

	// EXCEPTIONS
	class CmdError : public std::exception
	{
	public:
		CmdError(std::string what, User *user);
		CmdError(std::string what, User *user, std::string arg);
		~CmdError() _NOEXCEPT;

		virtual const char *what() const _NOEXCEPT;

	private:
		std::string m_what;
	};

	class UserRemoved : public std::exception
	{
	public:
		virtual const char *what() const _NOEXCEPT;
	};
};

#endif