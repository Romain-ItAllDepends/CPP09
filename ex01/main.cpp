/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:05 by rgobet            #+#    #+#             */
/*   Updated: 2025/02/03 10:58:42 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static void ParseInput(int ac, char **str)
{
	std::string input;
	int j = 1;
	int x;

	if (ac != 2)
		throw std::string("Wrong number of arguments!");
	if (str == NULL || str[1][0] == 0)
		throw std::string("Wrong input!");
	while (str && str[j])
	{
		x = 0;
		input = str[j];
		while (str[j][x])
		{
			if (str[j][x] != 32 && str[j][x] != 43 && str[j][x] != 42
				&& str[j][x] != 45 && (str[j][x] < 47 || str[j][x] > 57))
				throw std::string("Invalid argument: ") + input;
			if ((str[j][x] == 43 || str[j][x] == 42 || str[j][x] == 47 || str[j][x] == 45)
				&& (str[j][x + 1] && str[j][x + 1] != ' ' && str[j][x + 1] != '\0'))
				throw std::string("Wrong format!");
			x++;
		}
		j++;
	}
}

int main(int ac, char *av[])
{
	RPN rpn;

	try
	{
		ParseInput(ac, av);
		rpn.execute(av);
	} catch (std::string &error)
	{
		std::cerr << RED << "Error: " << error << NC << std::endl;
		return 1;
	} catch (std::exception &error)
	{
		std::cerr << RED << "Error: " << error.what() << NC << std::endl;
		return 2;
	}
	return 0;
}
