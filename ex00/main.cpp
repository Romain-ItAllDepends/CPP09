/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:51:19 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/14 15:21:49 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool DateParser(std::string const &date, char sep)
{
	int					dateInt[3] = {atoi(date.substr(0, 4).c_str()),
		atoi(date.substr(5, 2).c_str()), atoi(date.substr(8, 2).c_str())};
	char				delim[2] = {date[4], date[7]};
	std::tm				tm = {};
	std::time_t			t;

	if ((date.length() != 10 && sep == ',') || (date.length() != 11 && sep == '|'))
		return DateErrorMessage(date);
	tm.tm_year = dateInt[0] - 1900;
	tm.tm_mon = dateInt[1] - 1;
	tm.tm_mday = dateInt[2];
	if (delim[0] != '-' || delim[1] != '-' || (sep == '|' && date[10] != ' '))
		return DateErrorMessage(date);
	t = std::mktime(&tm);
	if (tm.tm_year + 1900 != dateInt[0] || tm.tm_mon + 1 != dateInt[1] || tm.tm_mday != dateInt[2] || t == -1)
		return DateErrorMessage(date);
	return true;
}

static bool VerifyDigitAfterComma(std::string const &str, unsigned int const start)
{
	std::string const	afterComma = str.substr(start + 1);

	for (size_t i = 1 ; i < afterComma.length() ; i++)
	{
		if ((i > 6 && afterComma[i] != '0') || std::isdigit(afterComma[i]) == false)
			return false;
	}
	return true;
}

static bool ValueParser(std::string const &value, char const sep)
{
	int					dot = 0;
	std::string const	parse = SkipSpaces(value);
	float v = strtof(parse.c_str(), NULL);

	/* Un float a généralement une précision d'environ 7 chiffres décimaux significatifs.
	 * Cela signifie que si vous avez un nombre avec plus de 7 chiffres après la virgule,
	 * les chiffres supplémentaires peuvent ne pas être représentés correctement. */
	// test alpha et ......
	for (size_t i = 0 ; i < parse.length() ; i++)
	{
		if (parse[i] == '.')
			dot++;
		if (parse[i] == '.' && VerifyDigitAfterComma(parse, i) == false)
			return ValueErrorMessage(value);
		if ((std::isdigit(parse[i]) == false && parse[i] != '.' && dot > 1) || (parse[i] == '.' && dot > 1))
			return ValueErrorMessage(value);
	}
	// Fonctionne pas
	if ((static_cast<int>(v) > 1000 && sep == '|') || v < 0 || (static_cast<int>(v) > __INT_MAX__ && sep == ','))
		return ValueErrorMessage(value);
	return true;
}

static bool FileParser(std::string const &file, char const sep)
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
	while (std::getline(ifs, line)) // Date
	{
		if (line.empty())
		{
			std::cerr << RED << "Empty line" << NC << std::endl;
			return false;
		}
		if (i == 0 && ((sep == ',' && line == "date,exchange_rate") || (sep == '|' && line == "date | value")))
		{
			i++;
			continue ; // Skip the line
		}
		std::istringstream iss(line);
		std::getline(iss, date, sep); // Date
		std::getline(iss, value, sep); // Number/price of bitcoin
		if (date.empty() || value.empty())
			return EmptyErrorMessage();
		if (DateParser(date, sep) == false)
			return false;
		if (ValueParser(value, sep) == false)
			return false;
		i++;
	}
	std::cout << GREEN << "OK" << NC << std::endl << std::endl;
	return true;
}

int main(int const ac, char *av[])
{
	if (ac != 2) {
		std::cerr << RED << "Error: could not open file." << NC << std::endl;
		return (1);
	}
	BitcoinExchange	btc(av[1]);
	std::cout << std::endl << BLUE << "Input file parsing: " << NC << std::endl;
	if (FileParser(btc.getFileName(), '|') == false)
		return (1);
	std::cout << BLUE << "Data of CSV file parsing: " << NC << std::endl;
	if (FileParser(btc.getDBName(), ',') == false)
		return (1);
	std::cout << BLUE << "Execution: " << NC << std::endl << std::endl;
	// execute();
	std::cout << std::endl;
	return (0);
}
