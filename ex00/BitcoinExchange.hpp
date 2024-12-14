/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:22 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/14 09:33:04 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include "ErrorMessage.hpp"
# include <iostream>
# include <fstream>
# include <regex.h> // Sa degage normalement
# include <cstring>
# include <cstdlib>
# include <ctime> // mktime
# include <iomanip>
# include <sstream>
# include <string>
# include <map>

// Maybe useless
# define REGEX_CSV "(^[0-9]{4}[-][0-9]{2}[-][0-9]{2}[,][0-9]{1,})$|(^[0-9]{4}[-][0-9]{2}[-][0-9]{2}[,][0-9]{1,}[.][0-9]{1,2})$"
# define REGEX_INPUT "(^[0-9]{4}[-][0-9]{2}[-][0-9]{2}[,][0-1][0-9]{3})$"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define NC "\033[0m" // No Color

class BitcoinExchange
{
	private:
		std::string						_dbName;
		std::string						_fileName;
		std::map<std::string, float>	bitcoinRate;
		std::map<std::string, float>	bitcoinOwn;
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &obj);
		~BitcoinExchange(void);
		BitcoinExchange	&operator=(BitcoinExchange const &obj);

		BitcoinExchange(std::string const &file);

		const char *getFileName(void) const;
		const char *getDBName(void) const;
};

#endif
