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

BitcoinExchange::BitcoinExchange(void):_dbName("data.csv"), _fileName(NULL) {
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &obj):_dbName("data.csv"), _fileName(NULL) {
	*this = obj;
}

BitcoinExchange::~BitcoinExchange(void) {
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &obj) {
	char* str = new char[std::strlen(obj._fileName) + 1];
    std::strcpy(str, obj._fileName);
	char* strDB = new char[std::strlen(obj._dbName) + 1];
    std::strcpy(strDB, obj._dbName);

	if (this != &obj) {
//		_dbName = "data.csv";
		_fileName = str;
		// copy map
	}
	return (*this);
}

char *BitcoinExchange::getFileName(void) const {
	return (_fileName);
}


char *BitcoinExchange::getDBName(void) const {
	return ((char *)"data.csv"); // Essaye de le link a _dbName
}

// Si date inexistante
// Soyez attentifs à utilser la date précédente la plus proche