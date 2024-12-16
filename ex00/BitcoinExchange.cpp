/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:04 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/16 11:43:43 by rgobet           ###   ########.fr       */
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
	this->setBitcoinOwn();
	this->setBitcoinRate();
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &obj)
{
	if (this != &obj) {
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

void BitcoinExchange::setBitcoinRate()
{
	int				i = 0;
	std::string		line, date, value;
	std::ifstream	ifs;

	ifs.open(_dbName.c_str());
	if (!ifs.is_open())
	{
		std::cerr << RED << "Error opening infile" << NC << std::endl;
		return ;
	}
	while (std::getline(ifs, line))
	{
		if (i == 0 && line == "date,exchange_rate")
		{
			i++;
			continue ;
		}
		std::istringstream iss(line);
		std::getline(iss, date, ',');
		std::getline(iss, value, ',');
		_bitcoinRate[date] = strtof(value.c_str(), NULL);
		i++;
	}
	ifs.close();
}

void BitcoinExchange::setBitcoinOwn()
{
	int				i = 0;
	std::string		line, date, value;
	std::ifstream	ifs;

	ifs.open(_fileName.c_str());
	if (!ifs.is_open())
	{
		std::cerr << RED << "Error opening infile" << NC << std::endl;
		return ;
	}
	while (std::getline(ifs, line))
	{
		if (i == 0 && line == "date | value")
		{
			i++;
			continue ;
		}
		std::istringstream iss(line);
		std::getline(iss, date, '|');
		std::getline(iss, value, '\n');
		if (date.empty() || value.empty())
			return EmptyErrorMessage(ifs);
		if (DateParser(date, ',', ifs) == false)
			return false;
		if (ValueParser(value, ',', ifs) == false)
			return false;
		_bitcoinOwn.insert(std::make_pair(date, strtof(value.c_str(), NULL)));
		i++;
	}
	ifs.close();
}

void BitcoinExchange::execute()
{
	// Maybe c'est upper ???
	for (std::multimap<std::string, float>::const_iterator it = _bitcoinOwn.begin(); it != _bitcoinOwn.end(); ++it)
	{
		std::map<std::string, float>::const_iterator itRate = _bitcoinRate.find(it->first);
		if (itRate == _bitcoinRate.end())
			itRate = _bitcoinRate.lower_bound(it->first);
		std::cout << it->first << "=> " << it->second << " = " << it->second * itRate->second << std::endl;
		std::cout << itRate->first << std::endl;
	}
}

// Si date inexistante
// Soyez attentifs à utilser la date précédente la plus proche
