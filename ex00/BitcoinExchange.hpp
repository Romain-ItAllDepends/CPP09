/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:22 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/16 14:53:55 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include "ErrorMessage.hpp"
# include <iostream>
#include <algorithm>
# include <fstream>
# include <cstring>
# include <cstdlib>
# include <iomanip>
# include <sstream>
# include <limits>
# include <string>
# include <ctime>
# include <map>

# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define NC "\033[0m" // No Color

class BitcoinExchange
{
	private:
		std::string const				_dbName;
		std::string const				_fileName;
		std::map<std::string, float>	_bitcoinRate;
	public:
		BitcoinExchange(std::string const &bdd, std::string const &file);
		~BitcoinExchange();

		void setBitcoinRate();

		const char *getFileName() const;
		const char *getDBName() const;

		void execute();
		private:
			BitcoinExchange();
			BitcoinExchange(BitcoinExchange const &obj);
			BitcoinExchange	&operator=(BitcoinExchange const &obj);
};

bool ValueParser(std::string const &value, char const sep, std::ifstream &ifs);
bool VerifyDigitAfterComma(std::string const &str, unsigned int const start);
bool DateParser(std::string const &date, char sep, std::ifstream &ifs);

#endif
