/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:05 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/23 09:37:16 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
#include <sstream>
# include <stack>

# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define NC "\033[0m" // No Color

class RPN
{
	private:
		std::stack<int> stack;
	public:
		RPN(void);
		RPN(const RPN& obj);
		~RPN(void);

		RPN& operator=(const RPN& obj);

		void execute(char **av);
};

#endif
