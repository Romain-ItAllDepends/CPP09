/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/27 11:44:30 by rgobet           ###   ########.fr       */
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
		M sortPerPair(C &pair, M &max)
		{
			int size = pair.size();

			if (pair.size() == 0)
			{
				for (std::size_t i = 0; i < vector.size() - 1; i += 2)
				{
					pair.push_back(std::make_pair(vector[i] > vector[i + 1] ? vector[i] : vector[i + 1],
						vector[i] < vector[i + 1] ? vector[i] : vector[i + 1]));
					max.push_back(vector[i] > vector[i + 1] ? vector[i] : vector[i + 1]);
				}
			}
			else
			{
				for (std::size_t i = 0; i < max.size() - 1; i += 2)
				{
					pair.push_back(std::make_pair(max[i] > max[i + 1] ? max[i] : max[i + 1],
						max[i] < max[i + 1] ? max[i] : max[i + 1]));
				}
				max.clear();
				for (std::size_t i = size; i < pair.size(); i++)
					max.push_back(pair[i].first);
			}
			if (vector.size() % 2 == 1)
				pair.push_back(std::make_pair(-1, vector.back()));
			if (pair.size() == 2 && pair[1].second == -1)
				pair[0].first = pair[0].second > pair[1].second ? pair[0].second : pair[1].second;
			std::cout << std::endl << "Stack : " << std::endl;
			for (std::size_t i = 0; i < pair.size(); i++)
				std::cout << GREEN << pair[i].first << " " << RED << pair[i].second << std::endl;
			std::cout << GREEN << pair.size() << RED << " ,impair int: " << pair[pair.size() - 1].second << NC << std::endl;
			if (max.size() > 1)
				max = this->sortPerPair(pair, max);
			std::cout << std::endl << pair[0].first << " ," << pair[0].second << std::endl;
			return max;
		}

		PmergeMe &operator=(PmergeMe const &obj);
};

#endif