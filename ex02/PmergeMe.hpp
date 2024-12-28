/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/28 11:27:28 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
# define PMERGE_ME_H

# include <deque>
# include <vector>
# include <time.h>
# include <cstdlib>
# include <iostream>
# include <algorithm>

# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define NC "\033[0m" // No Color
# define BOLD "\033[1m"

# define PRINT "std::cout << "
# define PRINTG "std::cout << GREEN << "
# define PRINTB "std::cout << BLUE << "
# define PRINTR "std::cout << RED << "
# define PRINTGB "std::cout << GREEN << BOLD << "
# define PRINTBB "std::cout << BLUE << BOLD << "
# define PRINTRB "std::cout << RED << BOLD << "
# define N " << "
# define F " << NC << std::endl;"

class PmergeMe
{
	private:
		std::vector<int> vector;
		std::vector<int> maxVector;
		std::vector<int> minVector;
		std::vector< std::pair<int, int> > pairVector;
		std::deque<int> deque;
		std::deque<int> maxDeque;
		std::deque<int> minDeque;
		std::deque< std::pair<int, int> > pairDeque;
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &obj);
		~PmergeMe();

		void fill(char **av);
		void execute();
		template< typename C, typename M >
		M sortPerPair(C &pair, M &max) // vector modif pour deque aussi
		{
			int size = pair.size(), tmp = 0;

			if (pair.size() == 0)
			{
				for (std::size_t i = 0; i < vector.size() - 1; i += 2)
				{
					pair.push_back(std::make_pair(vector[i] > vector[i + 1] ? vector[i] : vector[i + 1],
						vector[i] < vector[i + 1] ? vector[i] : vector[i + 1]));
					max.push_back(vector[i] > vector[i + 1] ? vector[i] : vector[i + 1]);
					tmp = pair.back().second;
				}
				if (vector.size() % 2 == 1)
				{
					pair.push_back(std::make_pair(tmp > vector.back() ? tmp : vector.back(), tmp < vector.back() ? tmp : vector.back()));
					max.push_back(pair.back().first);
				}
			}
			else
			{
				for (std::size_t i = 0; i < max.size() - 1; i += 2)
				{
					pair.push_back(std::make_pair(max[i] > max[i + 1] ? max[i] : max[i + 1],
						max[i] < max[i + 1] ? max[i] : max[i + 1]));
					tmp = pair.back().second;
				}
				if (max.size() % 2 == 1) // Impair == min if size > 3 / test if sort 3 values
					pair.push_back(std::make_pair(tmp > max.back() ? tmp : max.back(), tmp < max.back() ? tmp : max.back())); // Pair with smaller min
				max.clear();
				for (std::size_t i = size; i < pair.size(); i++) // need to lock 88 after save once
				{
					if (pair.size() - size % 2 == 1 && i == pair.size()) // exclude the last element because it's the place of impair element
						continue ;
					max.push_back(pair[i].first);
				}
			}


			// start print test
			std::cout << std::endl << "Stack : " << std::endl;
			for (std::size_t i = 0; i < pair.size(); i++)
				std::cout << GREEN << pair[i].first << " " << RED << pair[i].second << std::endl;
			// MAX
			std::cout << std::endl << GREEN << "MAX" << std::endl;
			for (std::size_t i = 0; i < max.size(); i++)
				std::cout << BLUE << max[i] << NC << std::endl;

			// end print test
			if (max.size() > 1)
				max = this->sortPerPair(pair, max);
			return max;
		}

		PmergeMe &operator=(PmergeMe const &obj);
};

#endif