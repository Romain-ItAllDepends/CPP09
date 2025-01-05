/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/27 15:45:27 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static void ParseInput(int ac, char **av)
{
	if (ac == 1) // Maybe != 3
		throw std::string("Too few arguments!");
	for (int i = 1 ; av[i] != NULL ; i++)
	{
		for (int j = 0 ; av[i][j] != '\0' ; j++)
		{
			if (av[i][j] == '0' && av[i][j + 1] != '\0')
				continue ;
			if (std::isdigit(av[i][j]) == false
				|| std::string(&av[i][j]).length() > 10 || std::atol(&av[i][j]) > 2147483647)
				throw std::string("Invalid input: " + std::string(av[i]));
		}
	}
}

// Parse doublon

int main(int ac, char **av)
{
	PmergeMe merge;

	try // Manage time in micro sec
	{
		ParseInput(ac, av);
		merge.fill(av);
		merge.execute();
	} catch (const std::string &error)
	{
		std::cerr << RED << BOLD << "Error: " << error << NC << std::endl;
		return 1;
	} catch (const std::exception &error)
	{
		std::cerr << RED << BOLD << "Error: " << error.what() << NC << std::endl;
		return 2;
	}
	return 0;
}