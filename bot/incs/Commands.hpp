/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:11:51 by jopadova          #+#    #+#             */
/*   Updated: 2023/10/27 14:57:40 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string"
#include "iostream"

class ACommand {
	public:
		ACommand();
		ACommand(std::string const &cmd);

		std::string const & getName() const { return this->name; };
		virtual ~ACommand();
		virtual std::string execute(std::string) const = 0;
	protected:
		std::string name;
};

class HelloCommand : public ACommand {
	public:
		HelloCommand();
		~HelloCommand();
		
		std::string execute(std::string) const;
};

class PingCommand : public ACommand {
	public:
		PingCommand();
		~PingCommand();

		std::string execute(std::string) const;
};

class StopCommand : public ACommand {
	public:
		StopCommand();
		~StopCommand();
		
		std::string execute(std::string) const;
};

class CommandFactory {
	public:
		CommandFactory();
		~CommandFactory();

		void learnCommand(ACommand *);
		ACommand *add(std::string const &);

	private:
		ACommand *commands[4];
};