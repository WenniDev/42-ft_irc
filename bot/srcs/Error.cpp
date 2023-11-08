/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:10:43 by jopadova          #+#    #+#             */
/*   Updated: 2023/10/23 15:11:06 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Error::Error(std::string what) {
	m_what = "Error: " + what;
	if (errno) {
		m_what += ": ";
		m_what += ::strerror(errno);
	};
}

Bot::Error::~Error() _NOEXCEPT {}

const char *Bot::Error::what() const _NOEXCEPT {
	return m_what.c_str();
}
