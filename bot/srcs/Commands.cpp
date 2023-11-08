/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:17:03 by jopadova          #+#    #+#             */
/*   Updated: 2023/10/27 14:57:46 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Bot.hpp"

ACommand::ACommand() : name("") {};
ACommand::~ACommand() {};

ACommand::ACommand(std::string const &cmd) : name(cmd) {};

HelloCommand::HelloCommand() : ACommand("hello") {};
HelloCommand::~HelloCommand() {};

std::string
HelloCommand::execute(std::string dest) const {
	return "PRIVMSG " + dest + " :Hey!";
}

PingCommand::PingCommand() : ACommand("ping") {};
PingCommand::~PingCommand() {};

std::string
PingCommand::execute(std::string dest) const {
	return "PRIVMSG " + dest + " :Pong!";
}

StopCommand::StopCommand() : ACommand("stop") {};
StopCommand::~StopCommand() {};

std::string
StopCommand::execute(std::string dest) const {
	return "PRIVMSG " + dest + " :Bye!";
}


CommandFactory::CommandFactory() {
	for (int i = 0; i < 4; i++)
		this->commands[i] = NULL;
};

CommandFactory::~CommandFactory() {
	for (int i = 0; i < 4; i++)
		if (this->commands[i] != NULL)
			 delete this->commands[i];
};

void
CommandFactory::learnCommand(ACommand *cmd) {
	for (int i = 0; i < 4; i++) {
		if (this->commands[i] == NULL) {
			this->commands[i] = cmd;
			return;
		}
	}
}

ACommand *
CommandFactory::add(std::string const &name) {
	for (int i = 0; i < 4; i++) {
		if (this->commands[i] && this->commands[i]->getName() == name)
			return this->commands[i];		
	}
	return NULL;
}