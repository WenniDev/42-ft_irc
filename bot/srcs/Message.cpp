/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageParser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:22:55 by jopadova          #+#    #+#             */
/*   Updated: 2023/10/25 17:58:36 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "sstream"
#include "iostream"

MessageParser::MessageParser(const std::string& rawMessage) {
    std::istringstream iss(rawMessage);
    std::string token;


    std::cout << "Raw: " << rawMessage << std::endl;
    full = rawMessage;

    if (rawMessage[0] == ':')
    {
        if (iss.str().find('!') != std::string::npos) {
            getline(iss, token, '!');
            author = token.substr(1);
        }
      
        getline(iss, token, ' ');
        hostname = token;   
    }
    if (getline(iss, token, ' '))
        command = token;

    if (rawMessage[0] == ':'){
        getline(iss, token, ' ');
        channel = token;
    }

    getline(iss, token);
    if (token.size() > 1 && token[0] == ':')
        content = token.substr(1);
    else
        content = token;
}

std::string
MessageParser::get_bot_command() {
    size_t end = this->content.find("\r");
    return this->content.substr(3, end - 3);
}

bool
MessageParser::is_bot_command() {
    std::string prefix = "42";
    return content.compare(0, prefix.length(), prefix) == 0;
}

void MessageParser::display() {
    std::cout << "Author: " << author << std::endl;
    std::cout << "Host Name: " << hostname << std::endl;
    std::cout << "Command: " << command << std::endl;
    std::cout << "Channel: " << channel << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Full: " << full << std::endl << std::endl;
}