/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:45:08 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/04 14:21:04 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <bits/stdc++.h>
#include <utility>

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
	// db.open("data.csv");
	// std::cout << "----------Input----------" << std::endl;
	// fillInputMap(input);
	// std::cout << "----------Data Base----------" << std::endl;
	(void)input;
	fillDbMap();
	displayDb();
}

void	BitcoinExchange::fillInputMap(std::string input)
{
	std::string	line;
	std::fstream	inputFile;
	inputFile.open(input.c_str());
	while (getline(inputFile, line))
	{
		// std::string	key;
		// std::string	value;
		// int			i = 0;
		// int			j = 0;
		// for (i; line[i] != '|'; i++)
		// 	key[i] = line[i];
		// i++;
		// for (i; line[i]; i++)
		// {
		// 	value[j] = line[i];
		// 	j++;
		// }
		// std::cout << "key = " << key << "\nvalue = " << value << std::endl;
		std::cout << GREEN << line << RESET << std::endl;
	}
	inputFile.close();
}

void	BitcoinExchange::displayDb()
{
	for (std::map<std::string, std::string>::iterator it = _dbMap.begin(); it != _dbMap.end(); it++)
	{
		std::cout << it->first << "\n" << it->second << "\n" << std::endl;
	}
}

void	BitcoinExchange::fillDbMap()
{
	std::string			line;
	std::fstream		db;
	std::stringstream	ss(line);

	db.open("data.csv");
	// std::map<std::string, std::string>::iterator it = _dbMap.begin();
	while (getline(db, line))
	{
		std::string	key;
		std::string	val;
		std::stringstream	ss(line);
		getline(ss, key, ',');
		getline(ss, val, ',');
		// _dbMap.insert(std::pair<std::string, std::string>{key, val});
		_dbMap[key] = val;
		// it->first = token;
		// while (getline(ss, token, ','))
		// {
			
		// }
		// int			i = 0;
		// int			j = 0;
		// for (; line[i] != ','; i++)
		// 	key[i] = line[i];
		// i++;
		// for (; line[i]; i++)
		// {
		// 	// value[j] = atof(line[i]);
		// 	j++;
		// }
		// std::cout << BLUE << line << RESET << std::endl;
	}
	db.close();
}
