/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:51:19 by rgobet            #+#    #+#             */
/*   Updated: 2024/11/22 11:24:55 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// parsing .csv et file
// format -> date -> range
// "date | valeur"
// "Année-Mois-Jour" (YYYY-MM-DD)

// Une valeur valide doit être soit un nombre à virgule flottante (float), ou un entier
// positif, compris entre 0 et 1000

static int	parse_line_input(std::string str, regex_t* regex) {
	int result = regexec(regex, str.c_str(), 0, NULL, 0);
	if (str == "date,exchange_rate") {
		return (-1);
	}
	else if (result == REG_NOMATCH) {
		std::cerr << "Bad pattern => " << str << "." << std::endl;
		//    	std::cout << result << std::endl;
		return (1);
	} else if (result != 0) {
		std::cerr << "Regex execution error: " << result << std::endl;
	}
	// price range verif
	// date verif
	std::cout << str << std::endl;
	return (0);
}

static int	parse_line_csv(std::string str, regex_t* regex) {
    int result = regexec(regex, str.c_str(), 0, NULL, 0);
	if (str == "date,exchange_rate") {
		return (-1);
	}
	else if (result == REG_NOMATCH) {
		std::cerr << "Bad pattern => " << str << "." << std::endl;
		//    	std::cout << result << std::endl;
		return (1);
	} else if (result != 0) {
		std::cerr << "Regex execution error: " << result << std::endl;
	}
    // price range verif
    // date verif
	std::cout << str << std::endl;
    return (0);
}

static bool	parse_file(char *file, bool is_csv) {
	regex_t 		reg;
	std::string		line;
	std::string		regex[2] = {REGEX_INPUT, REGEX_CSV};
	std::ifstream	ifs;
	int				count;

	count = 0;
	if (regcomp(&reg, regex[is_csv], REG_EXTENDED)) {
    	std::cerr << "Regex compilation failed: " << std::endl;
    	return (false);
   	}
	ifs.open(file);
	if (!ifs.is_open()) {
		std::cerr << "Error opening infile" << std::endl;
        return (false);
    }
	while (std::getline(ifs, line)) {
        if (line.empty()) {
        	break ;
        }
		if (count == 0) { // First line ("date | valeur")
			if (parse_line_csv(line, &reg) <= 0) {
				count++;
				continue ;
			}
			else {
				regfree(&reg);
				return (false);
            }
		}
		else if (parse_line_csv(line, &reg) != 0) {
			std::cout << line << std::endl;
			regfree(&reg);
            return (false);
		}
		count++;
	}
	regfree(&reg);
	ifs.close();
	return (true);
}

int main(int ac, char *av[]) {
	if (ac != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
    (void)av[1];
	BitcoinExchange	btc;
	if (parse_file(btc.getDBName(), true) == false) {
		return (1);
	}
	// if (parse_file(btc.getFileName(), false) == false) {
		// return (1);
	// }
	// execute();
	return (0);
}