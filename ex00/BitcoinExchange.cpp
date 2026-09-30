/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:45:08 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/30 10:40:53 by gaducurt         ###   ########.fr       */
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
	fillDbMap();
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
	if (db.fail())
		throw std::logic_error("Error: invalid data file");
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
			if (i == 1)
				_minDate = key;
			tm.tm_isdst = 0;
			std::time_t	time = mktime(&tm);
			char buffer[11];
			std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
			if (time == -1 || buffer != key)
				throw std::logic_error("Error: bad input (data) => " + key);
			getline(ss, val, ',');
			_dbMap[key] = std::atof(val.c_str());
			_maxDate = key;
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
	bool	check;
	double	coef;

	input.open(_input.c_str());
	if (input.fail())
		throw std::logic_error("Error: invalid input file");
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
					check = true;
					for (size_t i = 0; i < tmp.size(); i++)
					{
						if (tmp.find_first_not_of("0123456789.-") != std::string::npos)
						{
							std::cout << "Error: coef is empty or bad input" << std::endl;
							check = false;
							break;
						}
					}
					if (check)
					{
						coef = atof(tmp.c_str());
						if (checkCoef(coef))
						{
							int nbFloat = countDecimal(it->second);
							std::cout << it->first << " => " << coef << " = " << std::setprecision(nbFloat + 4) << coef * it->second << std::endl;
						}
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
	struct std::tm	min = {};
	struct std::tm	max = {};
	
	strptime(date.c_str(), "%Y-%m-%d", &tm);
	tm.tm_isdst = 0;
	std::time_t	time = mktime(&tm);

	strptime(_minDate.c_str(), "%Y-%m-%d", &min);
	min.tm_isdst = 0;
	std::time_t minTime = mktime(&min);
	if (time < minTime)
		return false;

	strptime(_maxDate.c_str(), "%Y-%m-%d", &max);
	max.tm_isdst = 0;
	std::time_t maxTime = mktime(&max);
	if (time > maxTime)
		return false;

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
