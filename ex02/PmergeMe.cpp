/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/23 12:33:51 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &obj)
{
	*this = obj;
}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(PmergeMe const &obj)
{
	if (this != &obj)
	{
		vector = obj.vector;
		deque = obj.deque;
	}
	return *this;
}

void PmergeMe::fill(char **av)
{
	std::cout << "Begin: ";
	for (int i = 1; av[i]; i++)
	{
		vector.push_back(atoi(av[i]));
		deque.push_back(atoi(av[i]));
		if (i != 1)
			std::cout << ", " << av[i];
		else
			std::cout << av[i];
	}
	std::cout << std::endl;
}
