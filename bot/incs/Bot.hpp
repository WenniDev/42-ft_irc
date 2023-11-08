/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:49:02 by jopadova          #+#    #+#             */
/*   Updated: 2023/11/02 15:08:37 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../TCP_IPv4.lib/TCP_IPv4"
#include "deque"

enum e_status {
	OFFLINE,
	CONNECTED,
	LOGGED
};

class ACommand;
class MessageParser;
class CommandFactory;

class Bot {
	public:
		Bot();
		Bot(int, std::string);
		~Bot();
		
		void		init();
		void		start(std::string);
		void		set_status(e_status);
		
		void		login(std::string, std::string);
		bool		is_logged();

		void		init_commands();
		void		exec_command(std::string, std::string);

		void		send_cmd(std::string);		
		std::string	get_msg();
		
		void		add_in_queue();
		MessageParser *get_message(std::string &);

		class Error : public std::exception {
			public :
				Error(std::string);
				~Error() _NOEXCEPT;
				const char *what() const _NOEXCEPT;
				
			private :
				std::string m_what;
		};

	private:
		TCP_IPv4::PSocket	psock;
		TCP_IPv4::ASocket	*asock;
		TCP_IPv4::SocEvent	event;
		

		struct sockaddr_in	serv_addr;
		e_status			status;

		std::deque<MessageParser *> queue;			
		std::string			ret_msg;
		
		int					listening_port;
		std::string			serv_address;

		CommandFactory *cmd_han;
		ACommand *commands[4];
};