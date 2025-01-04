/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2025/01/04 11:41:40 by rgobet           ###   ########.fr       */
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
		if (maxVector.empty() == false && std::find(maxVector.begin(), maxVector.end(), std::atoi(av[i])) != maxVector.end())
			throw "Doublon (dois etre traduis)";
		maxVector.push_back(std::atoi(av[i]));
		maxDeque.push_back(std::atoi(av[i]));
		if (i != 1)
			std::cout << ", " << maxVector.back();
		else
			std::cout << maxVector.back();
	}
	std::cout << NC << std::endl;
}

void PmergeMe::execute()
{
	std::cout << GREEN << "Executing..." << NC << std::endl;
	this->sortPerPair(pairVector, maxVector);
	// this->sortPerPair(pairDeque, maxDeque);
}
