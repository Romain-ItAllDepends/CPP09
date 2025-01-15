/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2025/01/11 14:46:03 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
# define PMERGE_ME_H

# include <deque>
# include <ctime>
# include <cmath>
# include <vector>
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <algorithm>

# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define NC "\033[0m" // No Color
# define BOLD "\033[1m"

# define PRINT std::cout <<
# define PRINTR std::cout << RED <<
# define PRINTG std::cout << GREEN <<
# define PRINTB std::cout << BLUE <<
# define PRINTRB std::cout << RED << BOLD <<
# define PRINTGB std::cout << GREEN << BOLD <<
# define PRINTBB std::cout << BLUE << BOLD <<
# define N <<
# define END << NC << std::endl;

class PmergeMe
{
	private:
		std::vector<int> vector;
		std::vector<int> maxVector;
		std::vector< std::pair<int, int> > pairVector;
		std::deque<int> deque;
		std::deque<int> maxDeque;
		std::deque< std::pair<int, int> > pairDeque;
	private:
		PmergeMe(PmergeMe const &obj);
		PmergeMe &operator=(PmergeMe const &obj);
	public:
		PmergeMe();
		~PmergeMe();

		void fill(char **av);
		void execute();
		
	template< typename C, typename M >
	M sortPerPair(C &pair, M &maxi);
	
	template< typename M >
	M suitJacobsthal(M &mini);
	
	template< typename M >
	void setupSections(M &split, M &mini);
	
	template< typename M >
	std::size_t binarySearch(M container, int target);
	
	template< typename M >
	M sortAndMerge(M &maxi, M &mini);
	
	template< typename M >
	void display(M &c, bool e);
};

# include "PmergeMe.tpp"

#endif
