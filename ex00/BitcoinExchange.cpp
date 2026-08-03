/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:45:08 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/03 14:36:48 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
	fillInputMap(input);
	// std::cout << "----------Data Base----------" << std::endl;
	fillDbMap();
}

void	BitcoinExchange::fillInputMap(std::string input)
{
	std::string	line;
	std::fstream	inputFile;
	inputFile.open(input.c_str());
	while (getline(inputFile, line))
		std::cout << GREEN << line << RESET << std::endl;
	inputFile.close();
}

void	BitcoinExchange::fillDbMap()
{
	std::string		line;
	std::fstream	db;
	db.open("data.csv");
	while (getline(db, line))
		std::cout << BLUE << line << RESET << std::endl;
	db.close();
}
