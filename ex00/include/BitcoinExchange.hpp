/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:26:24 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/05 16:19:29 by gaducurt         ###   ########.fr       */
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
		std::string						_input;
		// std::map<std::time_t, float>	_dbMap;
    public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange &operator=(const BitcoinExchange &obj);
		~BitcoinExchange();
		BitcoinExchange(std::string input);
		bool	checkDate(std::string date);
		void	calcul();
		void	fillDbMap();
		void	displayDb();
};

#endif

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
