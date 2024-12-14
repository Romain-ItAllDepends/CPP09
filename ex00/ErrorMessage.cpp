/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 09:28:34 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/14 09:46:14 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorMessage.hpp"

bool DateErrorMessage(std::string const &error)
{
	std::cerr << RED << "Invalid date: " << error << NC << std::endl;
	return false;
}

bool ValueErrorMessage(std::string const &error)
{
	std::cerr << RED << "Invalid value: " << error << NC << std::endl;
	return false;
}

bool EmptyErrorMessage()
{
	std::cerr << RED << "An empty date or/and value has been found" << NC << std::endl;
	return false;
}
