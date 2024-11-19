/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:22 by rgobet            #+#    #+#             */
/*   Updated: 2024/11/19 15:00:04 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <string>

class BitcoinExchange
{
	private:
		std::string	_fileName;
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &obj);
		~BitcoinExchange(void);
		BitcoinExchange	&operator=(BitcoinExchange const &obj);
};

#endif