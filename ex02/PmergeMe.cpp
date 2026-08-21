/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/21 16:17:21 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &obj) : _timeManagement(obj._timeManagement), _time1(obj._time1), _time2(obj._time2), _vec(obj._vec), _deq(obj._deq)
{
	
}

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

PmergeMe::~PmergeMe()
{
	
}

void	PmergeMe::printVec()
{
	for ()
}

PmergeMe::PmergeMe(char** av)
{
	for (int i = 1; av[i]; i++)
	{
		_vec.push_back(atoi(av[i]));
	}
}
