/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 09:30:19 by rgobet            #+#    #+#             */
/*   Updated: 2024/12/16 09:35:54 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

# include <iostream>

# define RED "\033[0;31m"
# define NC "\033[0m" // No Color

bool DateErrorMessage(std::string const &error, std::ifstream &ifs);
bool ValueErrorMessage(std::string const &error, std::ifstream &ifs);
bool EmptyErrorMessage(std::ifstream &ifs);

#endif
