/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/23 12:29:29 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static void ParseInput(int ac, char **av)
{
	if (ac == 1)
		throw std::string("Too few arguments!");
	for (int i = 1 ; av[i] != NULL ; i++)
	{
		for (int j = 0 ; av[i][j] != '\0' ; j++)
		{
			if (std::isdigit(av[i][j]) == false)
				throw std::string("Invalid input: " + std::string(av[i]));
		}
	}
}

int main(int ac, char **av)
{
	PmergeMe merge;

	try
	{
		ParseInput(ac, av);
		merge.fill(av);
	} catch (const std::string &error)
	{
		std::cerr << RED << "Error: " << error << NC << std::endl;
		return 1;
	} catch (const std::exception &error)
	{
		std::cerr << RED << "Error: " << error.what() << NC << std::endl;
		return 2;
	}
	return 0;
}