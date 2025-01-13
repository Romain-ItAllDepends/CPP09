/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2025/01/13 20:26:42 by rgobet           ###   ########.fr       */
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
	PRINTG "Before:  ";
	for (int i = 1; av[i]; i++)
	{
		maxVector.push_back(std::atoi(av[i]));
		maxDeque.push_back(std::atoi(av[i]));
		if (i != 1)
			PRINT ", " N maxVector.back();
		else
			PRINT maxVector.back();
	}
	PRINT NC << std::endl;
}

void PmergeMe::execute()
{
	std::vector<int> v;
	std::deque<int> d;
	double start, duration;

	for (std::size_t i = 0; i < maxVector.size(); i++)
	{
		v.push_back(maxVector[i]);
		d.push_back(maxDeque[i]);
	}
	sort(v.begin(), v.end());
	sort(d.begin(), d.end());
	PRINTG "After:   ";
	display(v, false);
	PRINT NC END
	start = std::clock();
	if (start == -1)
		throw std::string("Clock error!");
	this->sortPerPair(pairVector, maxVector);
	duration = 1000000.0 * (std::clock() - start) / CLOCKS_PER_SEC;
	PRINTG "Time to process a range of " N v.size() N " elements with std::vector : " N duration N " us" END
	start = std::clock();
	if (start == -1)
		throw std::string("Clock error!");
	this->sortPerPair(pairDeque, maxDeque);
	duration = 1000000.0 * (std::clock() - start) / CLOCKS_PER_SEC;
	PRINTG "Time to process a range of " N d.size() N " elements with std::deque : " N duration N " us" END

	for (std::size_t i = 0; i < v.size(); i++)
	{
		if (v[i] != maxVector[i])
		{
			display(maxVector, true);
			throw std::string("vector not sort!");
		}
		if (d[i] != maxDeque[i])
		{
			display(maxDeque, true);
			throw std::string("deque not sort!");
		}
	}
	PRINTGB "IT'S SORT!" END
}
