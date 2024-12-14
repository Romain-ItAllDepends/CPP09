/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:04 by rgobet            #+#    #+#             */
/*   Updated: 2024/11/21 10:04:14 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void):_dbName("data.csv"), _fileName(NULL)
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &obj)
{
	*this = obj;
}

BitcoinExchange::BitcoinExchange(std::string const &file):_dbName("data.csv"), _fileName(file)
{
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &obj)
{
	if (this != &obj) {
		_dbName = obj._dbName;
		_fileName = obj._fileName;
		// copy map
	}
	return (*this);
}

const char *BitcoinExchange::getFileName(void) const
{
	return (_fileName.c_str());
}

const char *BitcoinExchange::getDBName(void) const
{
	return (_dbName.c_str());
}

// Si date inexistante
// Soyez attentifs à utilser la date précédente la plus proche
