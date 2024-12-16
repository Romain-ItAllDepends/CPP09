/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:51:19 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/16 11:44:10 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <string>

#include "BitcoinExchange.hpp"

// parsing .csv et file
// format -> date -> range
// "date | valeur"
// "Année-Mois-Jour" (YYYY-MM-DD)

// Une valeur valide doit être soit un nombre à virgule flottante (float), ou un entier
// positif, compris entre 0 et 1000 pour input et MAX_INT pour CSV

static std::string SkipSpaces(const std::string& s)
{
	int i = 0;

	while (s[i] == ' ')
		i++;
	return s.substr(i, s.size() - i);
}

bool DateParser(std::string const &date, char sep, std::ifstream &ifs)
{
	int					dateInt[3] = {atoi(date.substr(0, 4).c_str()),
		atoi(date.substr(5, 2).c_str()), atoi(date.substr(8, 2).c_str())};
	char				delim[2] = {date[4], date[7]};
	std::tm				tm = {};
	std::time_t			t;

	if ((date.length() != 10 && sep == ',') || (date.length() != 11 && sep == '|'))
		return DateErrorMessage(date, ifs);
	tm.tm_year = dateInt[0] - 1900;
	tm.tm_mon = dateInt[1] - 1;
	tm.tm_mday = dateInt[2];
	if (delim[0] != '-' || delim[1] != '-' || (sep == '|' && date[10] != ' '))
		return DateErrorMessage(date, ifs);
	t = std::mktime(&tm);
	if (tm.tm_year + 1900 != dateInt[0] || tm.tm_mon + 1 != dateInt[1] || tm.tm_mday != dateInt[2] || t == -1)
		return DateErrorMessage(date, ifs);
	return true;
}

bool VerifyDigitAfterComma(std::string const &str, unsigned int const start)
{
	std::string const	afterComma = str.substr(start + 1);

	if (afterComma.empty())
		return false;
	for (size_t i = 1 ; i < afterComma.length() ; i++)
	{
		if ((i > 6 && afterComma[i] != '0') || std::isdigit(afterComma[i]) == false)
			return false;
	}
	return true;
}

bool ValueParser(std::string const &value, char const sep, std::ifstream &ifs)
{
	int					dot = 0;
	std::string const	parse = SkipSpaces(value);
	double v = strtod(parse.c_str(), NULL);

	/* A float can be precise up to seven decimal places */
	if (parse.empty())
		return EmptyErrorMessage(ifs);
	for (size_t i = 0 ; i < parse.length() ; i++)
	{
		if (parse[i] == '.')
			dot++;
		if ((i == 0 && parse[i] == '.') || (parse[i] == '.' && VerifyDigitAfterComma(parse, i) == false))
			return ValueErrorMessage(value, ifs);
		if ((std::isdigit(parse[i]) == false && parse[i] != '.') || (parse[i] == '.' && dot > 1))
			return ValueErrorMessage(value, ifs);
	}
	if ((v > 1000.0 && sep == '|') || (v > static_cast<double>(std::numeric_limits<int>::max()) && sep == ','))
		return ValueErrorMessage(value, ifs);
	return true;
}

static bool FileParser(std::string const &file)
{
	int				i = 0;
	std::string		line, date, value;
	std::ifstream	ifs;

	ifs.open(file.c_str());
	if (!ifs.is_open())
	{
		std::cerr << RED << "Error opening infile" << NC << std::endl;
		return false;
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
		std::getline(iss, value, '\n');
		if (date.empty() || value.empty())
			return EmptyErrorMessage(ifs);
		if (DateParser(date, ',', ifs) == false)
			return false;
		if (ValueParser(value, ',', ifs) == false)
			return false;
		i++;
	}
	ifs.close();
	std::cout << GREEN << "OK" << NC << std::endl << std::endl;
	return true;
}

int main(int const ac, char *av[])
{
	if (ac != 2) {
		std::cerr << RED << "Error: could not open file." << NC << std::endl;
		return (1);
	}
	std::cout << BLUE << "Data of CSV file parsing: " << NC << std::endl;
	if (FileParser("data.csv", ',') == false)
		return (1);
	BitcoinExchange	btc(av[1]);
	std::cout << BLUE << "Execution: " << NC << std::endl << std::endl;
	btc.execute();
	std::cout << std::endl;
	return (0);
}
