/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:04 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/16 15:06:30 by rgobet           ###   ########.fr       */
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

BitcoinExchange::BitcoinExchange(std::string const &bdd, std::string const &file):_dbName(bdd), _fileName(file)
{
	this->setBitcoinRate();
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &obj)
{
	if (this != &obj) {
		this->_bitcoinRate = obj._bitcoinRate;
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

void BitcoinExchange::execute()
{
	int				i = 0;
	std::string		line, date, value;
	std::ifstream	ifs, tmp;

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
		{
			EmptyErrorMessage(tmp);
			continue ;
		}
		if (DateParser(date, '|', tmp) == false || ValueParser(value, '|', tmp) == false)
			continue ;
		std::map<std::string, float>::const_iterator itRate = _bitcoinRate.find(date);
		if (itRate == _bitcoinRate.end())
			itRate = _bitcoinRate.lower_bound(date);
		std::cout << GREEN << date << "=> " << value << " = " << strtof(value.c_str(), NULL) * itRate->second;
		std::cout << NC << std::endl;
		i++;
	}
	ifs.close();
}
