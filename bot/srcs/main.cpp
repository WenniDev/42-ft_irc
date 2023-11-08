/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:01:38 by jopadova          #+#    #+#             */
/*   Updated: 2023/11/07 18:47:09 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "cstdlib"

int main(int argc, char **argv) {
	try {
		if (argc != 4)
			throw Bot::Error("Usage: ./bot <port> <address> <password>");
	
		std::string port(argv[1]);
		std::string address(argv[2]);
		std::string password(argv[3]);
		
		if (port.find_first_not_of("0123456789") != std::string::npos)
			throw Bot::Error("Invalid port");

		Bot bot(std::atol(argv[1]), argv[2]);
		bot.init();
		bot.init_commands();
		
		bot.start(argv[3]);
		
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}	
	return 0;
}