/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:26:24 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/03 14:30:52 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BITCOIN__
#define __BITCOIN__

#include <fstream>
#include <iostream>
#include <map>
#include <ctime>

class BitcoinExchange
{
	private:
		std::map<std::string, float>	_dbMap;
		std::map<std::string, float>	_inputMap;
		// std::fstream					_db;
		// std::fstream					_input;
    public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange &operator=(const BitcoinExchange &obj);
		~BitcoinExchange();
		BitcoinExchange(std::string input);
		void	parser();
		void	calcul();
		void	fillDbMap();
		void	fillInputMap(std::string db);
};

#endif

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
