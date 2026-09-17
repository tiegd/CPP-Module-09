/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/17 18:23:06 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <climits>
#include <complex>

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &obj) : _tVec(obj._tVec), _tDeq(obj._tDeq){}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		_tVec = obj._tVec;
		_tDeq = obj._tDeq;
	}
	return *this;
}

PmergeMe::PmergeMe(char** av)
{
	// std::vector<int>	vecInput;
	// std::deque<int>		deqInput;
	
	parser(av);
	for (int i = 1; av[i]; i++)
	{
		long	nb = atol(av[i]);
		if (nb > INT_MAX)
			throw std::logic_error("Error: number too large");
		else if (nb < INT_MIN)
			throw std::logic_error("Error: number too small");
		_vecInput.push_back(atoi(av[i]));
		_deqInput.push_back(atoi(av[i]));
	}
	jacobsthalVec();
	// jacobsthalDeq();
	sortVec();
	// sortDeq();
	
	_tVec = static_cast<double>(_tVec) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << "\nTime to process a range of 5 elements with std::vector : " << _tVec << " us" << std::endl;
	// _tDeq = static_cast<double>(_tDeq) / CLOCKS_PER_SEC * 1000000.0;
	// std::cout << "Time to process a range of 5 elements with std::deque : " << _tDeq << " us" << std::endl;
}

PmergeMe::~PmergeMe(){}

void	PmergeMe::parser(char** av)
{
	for (int i = 1; av[i]; i++)
	{
		for (int j = 0; av[i][j]; j++)
		{
			if (!std::isdigit(av[i][j]))
				throw std::logic_error("Error: bad input");
		}
	}
}

void	PmergeMe::swap(int &x, int &y)
{
	x ^= y;
	y ^= x;
	x ^= y;
}

/*---------VECTOR----------*/

void	PmergeMe::printVec(std::vector<int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::printJacobVec()
{
	std::cout << "\n----------Jacobsthal----------\n" << std::endl;
	for (size_t i = 0; i < _jacobVec.size(); i++)
		std::cout << _jacobVec[i] << ' ';
	std::cout << std::endl;
}

void	PmergeMe::jacobsthalVec()
{
	size_t	res = 0;
	int i = 2;

	_jacobVec.push_back(0);
	_jacobVec.push_back(1);
	while (res < _vecInput.size()  >> 1)
	{
		res = (_jacobVec[i - 2] << 1) + _jacobVec[i - 1];
		if (res > _vecInput.size() >> 1)
			break;
		_jacobVec.push_back(res);
		i++;
	}
}

void	PmergeMe::printDoubleVec(std::vector<std::vector<int> > vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "[ ";
		for (size_t j = 0; j < vec[i].size(); j++)
			std::cout << vec[i][j] << " ";
		std::cout << "] ";
	}
	if (_hasStraggler)
		std::cout << _straggler;
	std::cout << "\n" << std::endl;
}

void	PmergeMe::fillTmp1(std::vector<std::vector<int> > vec)
{
	_vecTmp.clear();
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "[ ";
		for (size_t j = 0; j < vec[i].size(); j++)
		{
			_vecTmp.push_back(vec[i][j]);
			std::cout << GREEN << vec[i][j] << " " << RESET;
		}
		std::cout << "] ";
	}
	_vecTmp.push_back(_straggler);
	std::cout << RED << _straggler << RESET << std::endl;
}

void	PmergeMe::fillTmp2(std::vector<std::vector<int> > vec)
{
	_vecTmp.clear();
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "[ ";
		for (size_t j = 0; j < vec[i].size(); j++)
		{
			_vecTmp.push_back(vec[i][j]);
			std::cout << GREEN << vec[i][j] << " " << RESET;
		}
		std::cout << "] ";
	}
	for (size_t i = 0; i < _vecStraggler.size(); i++)
	{
		_vecTmp.push_back(_vecStraggler[i]);
		std::cout << YELLOW << _vecStraggler[i] << " " << RESET;
	}
	std::cout << std::endl;
}

void	PmergeMe::fordJohnsonVec(int u)
{
	std::vector<std::vector<int> >	vec;

	if ((std::size_t)pow(2, u) >= _vecInput.size())
		return ;
	size_t	index = 0;
	size_t add = 0;
	std::cout << "u = " << u << std::endl;

	std::vector<int>	tmp;
	for (size_t i = 0; i < _vecTmp.size(); i++)
	{
		tmp.clear();
		if (i + pow(2, u) < _vecTmp.size())
		{
			for (int j = 0; j < pow(2, u); j++)
			{
				tmp.push_back(_vecTmp[i]);
				index = i;
				i++;
			}
			vec.push_back(tmp);
		}
	}
	std::cout << "index = " << index << std::endl;
	for (; index < _vecTmp.size(); index++)
		_vecStraggler.push_back(_vecTmp[index]);
	if (vec.size() % 2 != 0)
		add = 1;
	for (size_t i = 0; i < vec.size() - add; i+=2)
	{
		if (vec[i][vec[i].size() - 1] > vec[i+1][vec[i].size() - 1])
			vec[i].swap(vec[i+1]);
	}
	u++;
	fillTmp2(vec);
	_vecStraggler.clear();
	printVec(_vecTmp);
	std::cout << std::endl;
	fordJohnsonVec(u);
}

void	PmergeMe::sortVec()
{
	_tVec = clock();
	std::vector<std::vector<int> > vec;
	int	u = 1;

	_hasStraggler = _vecInput.size() % 2 != 0;
	_straggler = _vecInput[_vecInput.size() - 1];
	for (size_t i = 0; i < _vecInput.size(); )
	{
		if (i == _vecInput.size() - 1 && _hasStraggler)
			break;
		std::vector<int>	tmp;
		for (int j = 0; j < pow(2, u); j++)
		{
			tmp.push_back(_vecInput[i]);
			i++;
		}
		// printVec(tmp);
		if (tmp[0] > tmp[1])
			swap(tmp[0], tmp[1]);
		// printVec(tmp);
		vec.push_back(tmp);
	}
	// printDoubleVec(vec);
	size_t add = 0;
	if (vec.size() % 2 != 0)
		add = 1;
	for (size_t i = 0; i < vec.size() - add; i+=2)
	{
		if (vec[i][vec[i].size() - 1] > vec[i+1][vec[i].size() - 1])
			vec[i].swap(vec[i+1]);
	}
	// printDoubleVec(vec);
	std::cout << "u = " << u << std::endl;
	u++;
	fillTmp1(vec);
	printVec(_vecTmp);
	// fordJohnsonVec(_vecTmp, u);
	fordJohnsonVec(u);
	_tVec = clock() - _tVec;
	// std::cout << "\n----------Result std::vector----------\n" << std::endl;
}

/*---------DEQUE----------*/
