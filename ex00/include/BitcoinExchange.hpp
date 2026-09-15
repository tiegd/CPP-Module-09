/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:26:24 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/15 14:13:31 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BITCOIN__
#define __BITCOIN__

#include <iostream>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_dbMap;
		std::string						_input;
		std::string						_minDate;
		std::string						_maxDate;
    public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange &operator=(const BitcoinExchange &obj);
		~BitcoinExchange();
		BitcoinExchange(std::string input);
		bool	checkDate(std::string date);
		bool	checkCoef(double coef);
		void	compute();
		void	fillDbMap();
		void	displayDb();
		int		countDecimal(double nb);
};

#endif
