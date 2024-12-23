/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:05 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/23 10:58:03 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN& obj)
{
	*this = obj;
}

RPN::~RPN(void) {}

RPN& RPN::operator=(const RPN& obj)
{
	if (this != &obj)
		stack = obj.stack;
	return *this;
}

void RPN::execute(char **av)
{
	int i = 1, j = 0, value;
	std::stringstream str;

	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
				j++;
			if (av[i][j] == '+' || av[i][j] == '-' || av[i][j] == '*' || av[i][j] == '/')
			{
				value = stack.top();
				stack.pop();
				if (av[i][j] == '/' && (value == 0 || stack.top() == 0))
					throw std::string("Divisions by zero are impossible!");
				if (av[i][j] == '+')
					value += stack.top();
				else if (av[i][j] == '-')
					value = stack.top() - value;
				else if (av[i][j] == '*')
					value *= stack.top();
				else if (av[i][j] == '/')
					value /= stack.top();
				stack.pop();
				stack.push(value);
				// std::cout << value << std::endl;
			}
			else if (av[i][j] != ' ')
			{
				value = atoi(&av[i][j]);
				if (av[i][j + 1] != '\0' && av[i][j + 1] != ' ')
				{
					str << value;
					throw std::string("Invalid number: " + str.str());
				}
				stack.push(value);
			}
			j++;
		}
		i++;
	}
	if (stack.size() > 1)
		throw std::string("Too few sign!");
	std::cout << stack.top() << std::endl;
}