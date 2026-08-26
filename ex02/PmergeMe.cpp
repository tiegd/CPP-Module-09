/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/26 15:24:40 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &obj) : _timeManagement(obj._timeManagement), _time1(obj._time1), _time2(obj._time2), _vec(obj._vec), _deq(obj._deq){}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		_timeManagement = obj._timeManagement;
		_time1 = obj._time1;
		_time2 = obj._time2;
		_vec = obj._vec;
		_deq = obj._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe(){}

void	PmergeMe::printVec()
{
	// std::cout << "\n----------Vector----------\n" << std::endl;
	// for (size_t i = 0; i < _vec.size(); i++)
	// 	std::cout << "_vec[" << i << "] =\n_small = " << _vec[i]._small << "\n_large = " << _vec[i]._large << "\n_index = " << _vec[i]._index << "\n_isAlone = " << _vec[i]._isAlone << '\n' << std::endl;
	std::cout << "\n----------Vector----------\n\n_vec = ";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << i << "[" << _vec[i]._small << " " << _vec[i]._large << "] ";
	std::cout << std::endl;
}

void	PmergeMe::printDeq()
{
	std::cout << "\n----------Deque----------\n" << std::endl;
	for (size_t i = 0; i < _deq.size(); i++)
		std::cout << "_deq[" << i << "] =\n_small = " << _deq[i]._small << "\n_large = " << _deq[i]._large << "\n_index = " << _deq[i]._index << "\n_isAlone = " << _deq[i]._isAlone << '\n' << std::endl;
}

void	PmergeMe::printJacob()
{
	std::cout << "\n----------Jacobsthal----------\n" << std::endl;
	for (size_t i = 0; i < _jacob.size(); i++)
		std::cout << _jacob[i] << ' ';
	std::cout << std::endl;
}

void	PmergeMe::swap(size_t *a, size_t *b)
{
	int p;
	p = *a;
	*a = *b;
	*b = p;
}

void	PmergeMe::genJacobsthal()
{
	size_t	res = 0;
	int i = 2;

	_jacob.push_back(0);
	_jacob.push_back(1);
	std::cout << "_vec.size() = " << _vec.size() << std::endl;
	while (res < _vec.size())
	{
		res = _jacob[i - 2] * 2 + _jacob[i - 1];
		if (res > _vec.size())
			break;
		_jacob.push_back(res);
		i++;
	}
	printJacob();
}

PmergeMe::PmergeMe(int ac, char** av)
{
	int	j = 0;

	if (ac % 2 == 1)
	{
		for (int i = 1; av[i]; i += 2)
		{
			Pair	pair;
			pair._index = j;
			pair._small = atoi(av[i]);
			pair._large = atoi(av[i + 1]);
			pair._isAlone = false;
			if (pair._small > pair._large)
				swap(&pair._small, &pair._large);
			_vec.push_back(pair);
			_deq.push_back(pair);
			j++;
		}
	}
	else if (ac % 2 == 0)
	{
		for (int i = 1; av[i + 1]; i += 2)
		{
			Pair	pair;
			pair._index = j;
			pair._small = atoi(av[i]);
			pair._large = atoi(av[i + 1]);
			pair._isAlone = false;
			if (pair._small > pair._large)
				swap(&pair._small, &pair._large);
			_vec.push_back(pair);
			_deq.push_back(pair);
			j++;
		}
		Pair	alone;
		alone._index = j;
		alone._large = atoi(av[ac - 1]);
		alone._small = atoi(av[ac - 1]);
		alone._isAlone = true;
		_vec.push_back(alone);
		_deq.push_back(alone);
	}
	printVec();
	// printDeq();
	genJacobsthal();
}

void	PmergeMe::mergeInset()
{
	
}
