/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:45:08 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/04 15:25:53 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <bits/stdc++.h>
#include <utility>
#include <iomanip>
#include <ctime>
// #include <ctime>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj) : _dbMap(obj._dbMap), _inputMap(obj._inputMap)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if (this != &obj)
	{
		_dbMap = obj._dbMap;
		_inputMap = obj._inputMap;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string input)
{
	std::ifstream db;
	(void)input;
	fillDbMap();
	displayDb();
}

// void	BitcoinExchange::fillInputMap(std::string input)
// {
// 	std::string	line;
// 	std::fstream	inputFile;
// 	inputFile.open(input.c_str());
// 	while (getline(inputFile, line))
// 	{
// 		// std::string	key;
// 		// std::string	value;
// 		// int			i = 0;
// 		// int			j = 0;
// 		// for (i; line[i] != '|'; i++)
// 		// 	key[i] = line[i];
// 		// i++;
// 		// for (i; line[i]; i++)
// 		// {
// 		// 	value[j] = line[i];
// 		// 	j++;
// 		// }
// 		// std::cout << "key = " << key << "\nvalue = " << value << std::endl;
// 		std::cout << GREEN << line << RESET << std::endl;
// 	}
// 	inputFile.close();
// }

void	BitcoinExchange::displayDb()
{
	for (std::map<std::time_t, float>::iterator it = _dbMap.begin(); it != _dbMap.end(); it++)
		std::cout << it->first << "\n" << it->second << "\n" << std::endl;
}

void	BitcoinExchange::fillDbMap()
{
	std::string			line;
	std::fstream		db;
	std::stringstream	ss(line);
	int					i = 0;

	try
	{
		db.open("data.csv");
		while (getline(db, line))
		{
			if (i > 0)
			{
				struct std::tm	tm;
				std::string	key;
				std::string	val;
				std::stringstream	ss(line);
				getline(ss, key, ',');
				strptime(key.c_str(), "%Y-%m-%d", &tm);
				std::time_t	time = mktime(&tm);
				getline(ss, val, ',');
				_dbMap[time] = atof(val.c_str());
			}
			i++;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	db.close();
}
