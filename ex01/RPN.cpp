/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:05 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/21 13:34:56 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// RPN::RPN(void)
// {
// 	// Fill the stack
// }

RPN::RPN(const RPN& obj)
{
	*this = obj;
}

RPN::~RPN(void) {}

RPN& RPN::operator=(const RPN& obj)
{
	if (this != &obj)
		stack = obj.stack;
	return *this;
}