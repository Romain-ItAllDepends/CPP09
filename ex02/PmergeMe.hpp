/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/30 12:37:51 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
# define PMERGE_ME_H

# include <deque>
# include <vector>
# include <time.h>
# include <cmath>
# include <cstdlib>
# include <iostream>
# include <algorithm>


# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define NC "\033[0m" // No Color
# define BOLD "\033[1m"

class PmergeMe
{
	private:
		std::vector<int> vector;
		std::vector<int> maxVector;
		std::vector< std::pair<int, int> > pairVector;
		std::deque<int> deque;
		std::deque<int> maxDeque;
		std::deque< std::pair<int, int> > pairDeque;
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &obj);
		~PmergeMe();

		void fill(char **av);
		void execute();
		template< typename C, typename M >
		M sortPerPair(C &pair, M &maxi)
		{
			int size = pair.size();
			M mini;

			for (std::size_t i = 0; i < maxi.size() - 1; i += 2)
			{
				pair.push_back(std::make_pair(std::max(maxi[i], maxi[i + 1]), std::min(maxi[i], maxi[i + 1])));
				mini.push_back(pair.back().second);
			}
			if (maxi.size() == 3 || (mini.empty() == false && *std::max_element(mini.begin(), mini.end()) < maxi.back() && maxi.size() % 2 == 1))
				pair.push_back(std::make_pair(std::max(pair.back().second, maxi.back()), -1));
			else if (maxi.size() % 2 == 1) // Impair == min if size > 3 / test if sort 3 values
				pair.push_back(std::make_pair(-1, maxi.back())); // Pair with smaller min
			maxi.clear();
			for (std::size_t i = size; i < pair.size(); i++) // need to lock 88 after save once
			{
				if (pair.size() - size % 2 == 1 && i == pair.size()) // exclude the last element because it's the place of impair element
					continue ;
				maxi.push_back(pair[i].first);
			}

			// make re && ./PmergeMe 3 10 8 18 4 16 12 13 2 15 7 9 20 17 1 19 11 14 6 5 88

			// start print test
			std::cout << std::endl << "Stack : " << std::endl;
			for (std::size_t i = size; i < pair.size(); i++)
				std::cout << GREEN << pair[i].first << " " << RED << pair[i].second << std::endl;
			// MAX
			std::cout << std::endl << GREEN << "MAX" << std::endl;
			for (std::size_t i = 0; i < maxi.size(); i++)
				std::cout << BLUE << maxi[i] << NC << std::endl;

			// end print test
			if (maxi.size() > 1)
				maxi = this->sortPerPair(pair, maxi);
			this->sortAndMerge(maxi, mini);
			return maxi;
		}

		template< typename M >
		M sortAndMerge(M &maxi, M &mini)
		{
			static int n = 0;
			int tmp;
			tmp = n - 1 + 2 * (n - 2);
			n++;
			std::cout << BLUE << "TEST N: " << tmp << NC << std::endl;

			// print min
			std::cout << BLUE << std::endl << mini.size() << NC << std::endl;
			for (std::size_t i = 0; i < mini.size(); i++)
				std::cout << BLUE << mini[i] << NC << std::endl;
			// end print
			if (maxi.size() == 1)
			{
				maxi.push_back(mini.back());
				return maxi;
			}
			// for (std::vector<int>::iterator it = mini.begin() ; it != mini.end(); ++it)
			// {
			//
			// }
			// Coupe min en groupe (avec la suite de jacobsthal) et les inverse (les nombres de chaque groupe)
			// insert chaque nombre en utilisant binary search
			return maxi;
		}

		PmergeMe &operator=(PmergeMe const &obj);
};

#endif