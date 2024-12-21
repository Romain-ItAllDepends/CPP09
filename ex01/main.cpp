/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:05 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/21 14:13:19 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static bool ParseInput(char **str)
{
	std::string input;
	int j = 1;

	while (str[j])
	{
		input = str[j];
		for (int i = 0; i < 255 - 14; i++)
		{
			if (i != 32 && i != 43 && i != 42 && (i < 47 || i > 57) && !input.find(static_cast<char>(i)))
				return false;
		}
		std::cout << input << std::endl;
		j++;
	}
	return true;
}

int main(int ac, char *av[])
{
	if (ac < 2 || ParseInput(av) == false)
	{
		std::cerr << RED << "Error!" << NC << std::endl;
		return 1;
	}
	return 0;
}