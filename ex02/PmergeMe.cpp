/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/27 09:37:56 by rgobet           ###   ########.fr       */
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
	std::cout << GREEN << "Begin: ";
	for (int i = 1; av[i]; i++)
	{
		vector.push_back(atoi(av[i]));
		deque.push_back(atoi(av[i]));
		if (i != 1)
			std::cout << ", " << vector.back();
		else
			std::cout << vector.back();
	}
	std::cout << NC << std::endl;
}

int binary_search(std::vector<int> start, int target)
{
	for (std::size_t i = 0 ; i != start.size() - 1 ; i++)
	{
		if (start[i + start.size() / 2] > target)
			i = i + start.size() / 2 - 1;
		else if (start[i + start.size() / 2] < target)
			i = i + start.size() / 2 + 1;
		else if (start[i] == target)
			return i;
	}
	return -1;
}

void PmergeMe::execute()
{
	std::cout << GREEN << "Executing..." << NC << std::endl;
	this->sortPerPair(pairVector);
	this->sortPerPair(pairDeque);
}
