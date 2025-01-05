/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2025/01/04 12:19:09 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
# define PMERGE_ME_H

# include <deque>
# include <vector>
# include <ctime>
# include <cmath>
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
				pair.push_back(std::make_pair(std::max(maxi[i], maxi[i + 1]), std::min(maxi[i], maxi[i + 1])));
			if (mini.empty() == false && *std::max_element(mini.begin(), mini.end()) < maxi.back() && maxi.size() % 2 == 1)
				pair.push_back(std::make_pair(std::max(pair.back().second, maxi.back()), -1));
			else if (maxi.size() % 2 == 1) // Impair == min if size > 3 / test if sort 3 values
				pair.push_back(std::make_pair(-1, maxi.back())); // Pair with smaller min
			maxi.clear();
			for (std::size_t i = size; i < pair.size(); i++) // need to lock 88 after save once
			{
				if (pair.size() - size % 2 == 1 && i == pair.size()) // exclude the last element because it's the place of impair element
					continue ;
				if (pair[i].first != -1)
					maxi.push_back(pair[i].first);
				if (pair[i].second != -1)
					mini.push_back(pair[i].second);
			}

			// make re && valgrind ./PmergeMe 3 10 8 18 4 16 12 13 2 15 7 9 20 17 1 19 11 14 6 5 88

			// start print test
			// std::cout << std::endl << "Stack : " << std::endl;
			// for (std::size_t i = size; i < pair.size(); i++)
			// 	std::cout << GREEN << pair[i].first << " " << RED << pair[i].second << std::endl;
			// // MAX
			// std::cout << std::endl << GREEN << "MAX" << std::endl;
			// for (std::size_t i = 0; i < maxi.size(); i++)
			// 	std::cout << BLUE << maxi[i] << NC << std::endl;

			// end print test
			if (maxi.size() > 1)
				maxi = this->sortPerPair(pair, maxi);
			this->sortAndMerge(maxi, mini);
			return maxi;
		}

		// Norme
		template< typename M >
		static M suitJacobsthal(M &mini)
		{
			M jacob(2, 2);
			std::size_t tmp = 2;
			std::size_t const n = mini.size();

			for (std::size_t i = 2 ; i < n && tmp <= n ; i++)
			{
				tmp = jacob[i - 1] + 2 * jacob[i - 2];
				jacob.push_back(tmp);
			}
			return jacob;
		}

		template< typename M >
		static void setupSections(M &split, M &mini)
		{
			std::size_t count = 0;
			int j;
			M tmp;

			// print split (suite jacob)
			// std::cout << std::endl;
			// for (std::size_t i = 0; i < split.size(); i++)
			// 	std::cout << GREEN << split[i] << ", " << NC;
			// std::cout << std::endl;
			// end print

			for (std::size_t i = 0; i < mini.size() && i < 4; i += 2)
			{
				if (mini.size() > i + 1)
					tmp.push_back(mini[i + 1]);
				tmp.push_back(mini[i]);
				count += 2;
			}
			for (std::size_t n = 2 ; n < split.size() && mini.size() > 4
				&& mini.size() != tmp.size() ; n++)
			{
				if (mini.size() - 1 >= count + split[n])
					j = count + split[n] - 1;
				else
					j = mini.size() - 1;
				for (std::size_t i = j ; i >= count ; i--)
					tmp.push_back(mini[i]);
				count += split[n];
			}
			mini = tmp;
		}

		template< typename M >
		static std::size_t binarySearch(M container, int target)
		{
			int left = 0, right = container.size() - 1, mid = 0;

			while (left <= right)
			{
				mid = (left + right) / 2;
				if (container[mid] == target)
					return mid;
				if (container[mid] < target)
					left = mid + 1;
				else if (container[mid] > target)
					right = mid - 1;
			}
			return left;
		}

		template< typename M >
		M sortAndMerge(M &maxi, M &mini)
		{
			M split;

			// print min
			// std::cout << std::endl << RED << mini.size()  << " START" << std::endl;
			// std::cout << std::endl;
			// for (std::size_t i = 0; i < mini.size(); i++)
			// 	std::cout << BLUE << mini[i] << ", " << NC;
			// std::cout << std::endl;
			// end print
			if (mini.size() == 1)
			{
				maxi.insert(maxi.begin(), mini[0]);

				// print max
				// std::cout << std::endl << RED << maxi.size() << " END" << std::endl;
				// std::cout << std::endl;
				// for (std::size_t i = 0; i < maxi.size(); i++)
				// 	std::cout << BLUE << maxi[i] << ", " << NC;
				// std::cout << std::endl;
				// end print
				
				return maxi;
			}
			if (mini.empty() == true)
				throw std::string("Error: An empty container has been detected!");
			split = suitJacobsthal(mini);
			if (maxi.size() != 1)
				setupSections(split, mini);
			for (std::size_t i = 0 ; i < mini.size() ; i++)
				maxi.insert(maxi.begin() += binarySearch(maxi, mini[i]), mini[i]);
			//
			// print min
			// std::cout << std::endl << RED << mini.size() << " END" << std::endl;
			// std::cout << std::endl;
			// for (std::size_t i = 0; i < mini.size(); i++)
			// 	std::cout << BLUE << mini[i] << ", " << NC;
			// std::cout << std::endl;
			// end print


			// print max
			// std::cout << std::endl << RED << maxi.size() << " END" << std::endl;
			// std::cout << std::endl;
			// for (std::size_t i = 0; i < maxi.size(); i++)
			// 	std::cout << BLUE << maxi[i] << ", " << NC;
			// std::cout << std::endl;
			// end print

			// Need to merge

			// Coupe min en groupe (avec la suite de jacobsthal) et les inverse (les nombres de chaque groupe)
			// insert chaque nombre en utilisant binary search
			return maxi;
		}

		template< typename M >
		void display(M &c, bool e)
		{
			for (std::size_t i = 0 ; i < c.size() ; i++)
			{
				if (i == c.size() - 1 && e == false)
					PRINTG c[i] END
				else if (e == false)
					PRINTG c[i] N ", " N NC;
				if (i == c.size() - 1 && e == true)
					PRINTRB c[i] END
				else if (e == true)
					PRINTRB c[i] N ", " N NC;
			}
		}

		PmergeMe &operator=(PmergeMe const &obj);
};

#endif
