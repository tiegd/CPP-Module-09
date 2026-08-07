/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:45:08 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/07 10:33:24 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <bits/stdc++.h>

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
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string input)
{
	std::ifstream db;
	_input = input;
	try
	{
		fillDbMap();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	BitcoinExchange::displayDb()
{
	for (std::map<std::string, double>::iterator it = _dbMap.begin(); it != _dbMap.end(); it++)
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

void	BitcoinExchange::compute()
{
	std::string			line;
	std::fstream		input;
	std::string			tmp;
	int		i = 0;
	double	coef;

	input.open(_input.c_str());
	while (getline(input, line))
	{
		std::stringstream	ss(line);
		if (i > 0)
		{
			getline(ss, tmp, ' ');
			if (checkDate(tmp))
			{
				std::map<std::string, double>::iterator it = _dbMap.lower_bound(tmp);
				if (it != _dbMap.end())
				{
					if (it->first != tmp)
						it--;
					getline(ss, tmp, ' ');
					getline(ss, tmp, ' ');
					coef = atof(tmp.c_str());
					if (checkCoef(coef))
					{
						int nbFloat = countDecimal(it->second);
						std::cout << it->first << " => " << coef << " = " << std::setprecision(nbFloat + 4) << coef * it->second << std::endl;
					}
				}
			}
			else if (!checkDate(tmp))
				std::cout << "Error: bad input => " << tmp << std::endl;
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
	if (time == -1 || buff != date)
		return false;
	return true;
}

bool	BitcoinExchange::checkCoef(double coef)
{
	if (coef < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (coef > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

int	BitcoinExchange::countDecimal(double nb)
{
	int	i = 0;
	while (nb > 1)
	{
		nb /= 10;
		i++;
	}
	return i;
}
