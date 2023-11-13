/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:49:07 by jopadova          #+#    #+#             */
/*   Updated: 2023/11/13 11:34:42 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "Commands.hpp"
#include "Message.hpp"
#include "sstream"

Bot::Bot() {};

Bot::~Bot() {
	std::cout << "Bot disconnected !" << std::endl;
	delete asock;
	delete cmd_han;
};

Bot::Bot(int port, std::string addr) {
	this->status = OFFLINE;
	this->listening_port = port;
	this->serv_address = addr;
}

void
Bot::init() {
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->listening_port);

	struct addrinfo hint, *servinfo;
	
	::memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;	
	hint.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(this->serv_address.c_str(), 0, &hint, &servinfo) == -1)
		throw TCP_IPv4::Error("getaddrinfo");
	serv_addr.sin_addr = ((struct sockaddr_in *) servinfo->ai_addr)->sin_addr;

	freeaddrinfo(servinfo);
	std::cout << "Trying to connect to " << this->serv_address << ":" << this->listening_port << std::endl;
}

void
Bot::init_commands() {
	cmd_han = new CommandFactory();

	cmd_han->learnCommand(new PingCommand());
	cmd_han->learnCommand(new HelloCommand());
	cmd_han->learnCommand(new StopCommand());

	Bot::commands[0] = cmd_han->add("ping");
	Bot::commands[1] = cmd_han->add("hello");
	Bot::commands[2] = cmd_han->add("stop");
}

void
Bot::exec_command(std::string cmd, std::string arg) {
	for (int i = 0; i < 4; i++) {
		if (Bot::commands[i] && Bot::commands[i]->getName() == cmd){
			if (cmd == "stop") {
				this->set_status(OFFLINE);
				this->send_cmd("QUIT :leaving");
				return;
			}
			return Bot::send_cmd(Bot::commands[i]->execute(arg));
		}
	}
}

void
Bot::start(std::string password) {
	while (connect(psock.fd(), (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << ::strerror(errno) << std::endl;
		std::cerr << "Connection failed, retry in 5 secondes..." << std::endl;
		sleep(5);
	}

	asock = new TCP_IPv4::ASocket(dup(psock.fd()), psock.addr());

	asock->setNonBlock();
	this->event.add(this->asock, EPOLLIN | EPOLLHUP);
	std::cout << "start() connection established" << std::endl;
	this->status = CONNECTED;
	
		
	this->login("miniBot", password);
	this->send_cmd("JOIN #bot");

	while (this->is_logged())
	{		
		std::string res;
		this->event.wait();
		this->get_msg();
		add_in_queue();

		while (!queue.empty())
		{
			MessageParser *msg = queue.front();
			
			if (msg->command == "PING")
				Bot::send_cmd("PONG " + msg->content);
			
			if (msg->command == "PRIVMSG" && msg->is_bot_command()) {
				std::string cmd_str = msg->get_bot_command();
				if (msg->channel.find('#') == std::string::npos)
					this->exec_command(cmd_str, msg->author);
				else
					this->exec_command(cmd_str, msg->channel);
			}
			delete msg;
			queue.pop_front();
		}				
	}
}

void
Bot::add_in_queue()
{
	if (this->ret_msg.empty())
		return;
	std::stringstream ss(this->ret_msg);
    std::string line;
    std::string result;

    while (std::getline(ss, line)){
		MessageParser *msg = get_message(line);
		if (!msg)
			continue;
		this->queue.push_back(msg);
		std::cout << "Add message from " << msg->author << std::endl;
	}
}

void
Bot::set_status(e_status status) {
	this->status = status;
}

MessageParser *
Bot::get_message(std::string &input) {
	if (input.empty())
		return NULL;
 	std::stringstream ss(input);
    std::string line;
    std::string result;

    std::getline(ss, line);
	MessageParser *msg = new MessageParser(line);

	if (msg->command == "PRIVMSG")
		return msg;
	if (msg->command == "PING")
		return msg;

	delete msg;
    return NULL;
}

void
Bot::send_cmd(std::string cmd) {
	
	std::string msg = cmd + "\r\n";

	if (send(psock.fd(), msg.c_str(), msg.size(), 0) < 0)
		throw Bot::Error("Cannot send commands");
	
	std::cout << "send_cmd() cmd: '" << cmd << "' sent" << std::endl;
}

std::string
Bot::get_msg() {
	std::string res;
	char buff[1025];
	int nb;

	while ((nb = recv(psock.fd(), &buff, 1024, 0)) > 0) {
		buff[nb] = '\0';
		res += buff;
	}
	ret_msg = res;
	return ret_msg;
}

void
Bot::login(std::string name, std::string pass) {
	if (!pass.empty())
		send_cmd("PASS " + pass);
	std::cout << "login() logging" << std::endl;

	send_cmd("NICK " + name);
	send_cmd("USER Testing 0 * :BOT TEST");
	
	this->status = LOGGED;
	std::cout << "login() logged" << std::endl;
}

bool
Bot::is_logged() {
	return this->status == LOGGED ? true : false;
}
