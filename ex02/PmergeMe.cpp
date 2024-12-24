/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/24 13:39:31 by rgobet           ###   ########.fr       */
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

std::vector<int> PmergeMe::sortPerPair(std::vector<int> vectore)
{
	std::vector<int> max, min;

	for (std::size_t i = 0; i < vectore.size() - 1; i += 2)
	{
		min.push_back(vectore[i] < vectore[i + 1] ? vectore[i] : vectore[i + 1]);
		max.push_back(vectore[i] > vectore[i + 1] ? vectore[i] : vectore[i + 1]);
	}
	if (vectore.size() == 3)
	{
		max.push_back(vectore[0] > vectore[1] ? vectore[0] : vectore[1]);
		max.push_back(vectore[0] > vectore[1] ? vectore[0] : vectore[1]);
	}
	else if (vectore.size() % 2 == 1)
		min.push_back(vectore.back());
	std::cout << std::endl << "Stack : " << std::endl;
	for (std::size_t i = 0; i < max.size(); i++)
		std::cout << GREEN << max[i] << " " << RED << min[i] << std::endl;
	std::cout << GREEN << max.size() << " " << RED << min.size() << " ,impair int: " << min[min.size() - 1] << NC << std::endl;
	if (max.size() > 1)
		max = this->sortPerPair(max);
	std::cout << std::endl << max[0] << std::endl;
	return max;
}

void PmergeMe::execute()
{
	std::cout << GREEN << "Executing..." << NC << std::endl;
	this->sortPerPair(vector);
}
