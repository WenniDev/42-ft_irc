/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageParser.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:23:57 by jopadova          #+#    #+#             */
/*   Updated: 2023/10/25 17:50:18 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <string>

class MessageParser {
	public:
		MessageParser(const std::string& rawMessage);
		
		bool is_bot_command();
		void display();

		std::string get_bot_command();
		
		std::string author;
		std::string hostname;
		std::string command;
		std::string channel;
		std::string content;
		std::string full;
};

#endif

