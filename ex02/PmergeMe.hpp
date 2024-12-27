/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/27 15:51:41 by rgobet           ###   ########.fr       */
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
				if (max.size() == 3)
					pair.push_back(std::make_pair(max[1] > max[2] ? max[1] : max[2], max[1] < max[2] ? max[1] : max[2]));
				max.clear();
				for (std::size_t i = size; i < pair.size(); i++) // need to lock 88 after save once
				{
					if (pair[i].first == -1 || pair[i].first == tmp) // problem can't take any value
						continue ; // make re && ./PmergeMe 3 10 8 18 4 16 12 13 2 15 7 9 20 17 1 19 11 14 6 5 88
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