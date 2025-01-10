/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:05 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/23 11:10:35 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static void ParseInput(int ac, char **str)
{
	std::string input;
	int j = 1;

	if (ac != 2)
		throw std::string("Wrong number of arguments!");
	if (str == NULL || str[1][0] == 0)
		throw std::string("Wrong input!");
	while (str && str[j])
	{
		input = str[j];
		for (int i = 0; i < 255; i++)
		{
			if (i != 32 && i != 43 && i != 42 && (i < 47 || i > 57) && !input.find(static_cast<char>(i)))
				throw std::string("Invalid argument: ") + input;
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
