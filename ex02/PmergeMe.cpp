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
	std::cout << GREEN << "Before:  ";
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
	std::vector<int> v;
	std::deque<int> d;
	std::clock_t start, end;
	double ms;

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
	this->sortPerPair(pairVector, maxVector);
	end = std::clock();
	ms = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	PRINTG "Time to process a range of " N v.size() N " elements with std::vector : " N std::fixed N std::setprecision(5) N ms N " us" END
	start = std::clock();
	this->sortPerPair(pairDeque, maxDeque);
	end = std::clock();
	ms = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	PRINTG "Time to process a range of " N d.size() N " elements with std::deque : " N std::fixed N std::setprecision(5) N ms N " us" END

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
