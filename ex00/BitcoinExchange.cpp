/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:45:08 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/05 17:02:07 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <bits/stdc++.h>
#include <utility>
#include <iomanip>
#include <ctime>
#include <algorithm>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj) : _dbMap(obj._dbMap), _input(obj._input)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if (this != &obj)
	{
		_dbMap = obj._dbMap;
		_input = obj._input;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string input)
{
	std::ifstream db;
	// (void)input;
	_input = input;
	try
	{
		fillDbMap();
		calcul();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	// displayDb();
}

void	BitcoinExchange::displayDb()
{
	for (std::map<std::string, float>::iterator it = _dbMap.begin(); it != _dbMap.end(); it++)
		std::cout << it->first << "\n" << it->second << "\n" << std::endl;
}

void	BitcoinExchange::fillDbMap()
{
	std::string			line;
	std::fstream		db;
	int					i = 0;

	db.open("data.csv");
	while (getline(db, line))
	{
		if (i > 0)
		{
			struct std::tm	tm = {};
			std::string	key;
			std::string	val;
			std::stringstream	ss(line);
			getline(ss, key, ',');
			strptime(key.c_str(), "%Y-%m-%d", &tm);
			tm.tm_isdst = 0;
			std::time_t	time = mktime(&tm);
			char buffer[11];
			std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
			if (time == -1 || buffer != key)
				throw std::logic_error("Error: bad input (data) => " + key);
			getline(ss, val, ',');
			_dbMap[key] = std::atof(val.c_str());
		}
		i++;
	}
	db.close();
}

void	BitcoinExchange::calcul()
{
	std::string			line;
	std::fstream		input;
	std::string			tmp;
	int		i = 0;
	float	coef;

	input.open(_input.c_str());
	while (getline(input, line))
	{
		std::stringstream	ss(line);
		if (i > 0)
		{
			getline(ss, tmp, ' ');
			// std::string	date;
			// std::cout << tmp << std::endl;
			if (checkDate(tmp))
			{
				// std::map<std::string, float>::iterator it = _dbMap.find(tmp);
				std::map<std::string, float>::iterator it = _dbMap.lower_bound(tmp);
				// std::map<std::string, float>::iterator it = std::lower_bound(_dbMap.begin(), _dbMap.end(), tmp);
				if (it != _dbMap.end())
				{
					// std::cout << "date = " << it->first << " prix = " << it->second << std::endl;
					getline(ss, tmp, ' ');
					getline(ss, tmp, ' ');
					// std::cout << tmp << std::endl;
					coef = atof(tmp.c_str());
					// std::cout << "coef = " << coef << "\nresult = " << it->second * coef << std::endl;
					std::cout << it->first << " => " << it->second << " = " << coef * it->second << std::endl;
				}
			}
			else if (!checkDate(tmp))
				std::cout << "Error: bad input (data) => " << tmp << std::endl;
		}
		i++;
	}
}

bool	BitcoinExchange::checkDate(std::string date)
{
	struct std::tm	tm = {};
	strptime(date.c_str(), "%Y-%m-%d", &tm);
	tm.tm_isdst = 0;
	std::time_t	time = mktime(&tm);
	char	buff[11];
	std::strftime(buff, sizeof(buff), "%Y-%m-%d", &tm);
	// std::cout << BLUE << date << RESET << std::endl;
	// std::cout << RED << buff << RESET << std::endl;
	if (time == -1 || buff != date)
		return false;
	return true;
}
