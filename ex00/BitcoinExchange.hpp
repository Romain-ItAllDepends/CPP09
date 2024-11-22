/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:22 by rgobet            #+#    #+#             */
/*   Updated: 2024/11/22 09:03:57 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <fstream>
# include <regex.h>
# include <cstring>
# include <map>

# define REGEX_CSV "(^[0-9]{4}[-][0-9]{2}[-][0-9]{2}[,][0-9]{1,})$|(^[0-9]{4}[-][0-9]{2}[-][0-9]{2}[,][0-9]{1,}[.][0-9]{1,2})$"
# define REGEX_INPUT "(^[0-9]{4}[-][0-9]{2}[-][0-9]{2}[,][0-1][0-9]{3})$"

class BitcoinExchange
{
	private:
		char							_dbName[9];
		char							*_fileName;
		std::map<std::string, float>	bitcoinRate;
		std::map<std::string, float>	bitcoinOwn;
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &obj);
		~BitcoinExchange(void);
		BitcoinExchange	&operator=(BitcoinExchange const &obj);

		char *getFileName(void) const;
		char *getDBName(void) const;
};

#endif