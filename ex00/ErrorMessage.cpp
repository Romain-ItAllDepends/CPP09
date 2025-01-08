/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 09:28:34 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/16 09:34:34 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorMessage.hpp"

#include <fstream>

bool DateErrorMessage(std::string const &error, std::ifstream &ifs)
{
	std::cerr << RED << "Error: Invalid date: " << error << NC << std::endl;
	ifs.close();
	return false;
}

bool ValueErrorMessage(std::string const &error, std::ifstream &ifs)
{
	std::cerr << RED << "Error: Invalid value: " << error << NC << std::endl;
	ifs.close();
	return false;
}

bool EmptyErrorMessage(std::ifstream &ifs)
{
	std::cerr << RED << "Error: An empty date or/and value has been found" << NC << std::endl;
	ifs.close();
	return false;
}
