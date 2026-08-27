/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/27 16:18:15 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &obj) : _timeManagement(obj._timeManagement), _time1(obj._time1), _time2(obj._time2), _vecInput(obj._vecInput), _deqInput(obj._deqInput){}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		_timeManagement = obj._timeManagement;
		_time1 = obj._time1;
		_time2 = obj._time2;
		_vecInput = obj._vecInput;
		_deqInput = obj._deqInput;
	}
	return *this;
}

PmergeMe::PmergeMe(char** av)
{
	for (int i = 1; av[i]; i++)
	{
		_vecInput.push_back(atoi(av[i]));
		_deqInput.push_back(atoi(av[i]));
	}
	printVec();
	jacobsthalVec();
	// printDeq();
	// jacobsthalDeq();
}

PmergeMe::~PmergeMe(){}

void	PmergeMe::printVec()
{
	std::cout << "\n----------Vector----------\n\n_vec = ";
	for (size_t i = 0; i < _vecInput.size(); i++)
		std::cout << _vecInput[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::printResVec(std::vector<int> res)
{
	std::cout << "\n----------Result Vector----------\n" << std::endl;
	for (size_t i = 0; i < res.size(); i++)
		std::cout << res[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::printDeq()
{
	std::cout << "\n----------Deque----------\n\n_deq = " << std::endl;
	for (size_t i = 0; i < _deqInput.size(); i++)
		std::cout << _deqInput[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::printResDeq(std::deque<int> res)
{
	std::cout << "\n----------Result Deque----------\n" << std::endl;
	for (size_t i = 0; i < res.size(); i++)
		std::cout << res[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::printJacob()
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
	std::cout << "_vec.size() = " << _vecInput.size() << std::endl;
	while (res < _vecInput.size() / 2)
	{
		res = _jacobVec[i - 2] * 2 + _jacobVec[i - 1];
		if (res > _vecInput.size() / 2)
			break;
		_jacobVec.push_back(res);
		i++;
	}
	printJacob();
}

void	PmergeMe::insertVec(std::vector<size_t>& chain, std::vector<int> vec, size_t insertIdx, size_t bound)
{
	size_t	lo = 0;
	size_t	hi = bound;
	int		value = vec[insertIdx];
	
	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
		if (vec[chain[mid]] < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + static_cast<long>(lo), insertIdx);
}

std::vector<size_t>	PmergeMe::fordJohnsonVec(std::vector<size_t> index, std::vector<int> vec)
{
	size_t	n = index.size();
	if (n <= 1)
		return index;
	
	bool	hasStraggler = (n % 2 != 0);
	size_t	straggler = 0;
	if (hasStraggler)
	{
		straggler = index.back();
		index.pop_back();
	}
	
	std::vector<size_t> leaders;
	std::vector<size_t> followers;
	for (size_t i = 0; i < index.size(); i += 2)
	{
		size_t a = index[i];
		size_t b = index[i + 1];
		if (vec[a] > vec[b])
		{
			leaders.push_back(a);
			followers.push_back(b);
		}
		else
		{
			leaders.push_back(b);
			followers.push_back(a);
		}
	}
	
	std::vector<size_t> sortedLeaders = fordJohnsonVec(leaders, vec);
	
	std::vector<size_t> followerOf(vec.size());
	for (size_t i = 0; i < leaders.size(); i++)
		followerOf[leaders[i]] = followers[i];
	
	std::vector<size_t> chain = sortedLeaders;
	
	size_t b1 = followerOf[sortedLeaders[0]];
	chain.insert(chain.begin(), b1);

	size_t m = sortedLeaders.size();

	for (size_t k = 2; k < _jacobVec.size(); ++k)
	{
		size_t hi = std::min(_jacobVec[k], m);
		size_t lo = _jacobVec[k - 1] + 1;
		if (lo > hi)
			continue;
		for (size_t t = hi; t >= lo; --t)
		{
			size_t leadrtIdx = sortedLeaders[t - 1];
			size_t followerIdx = followerOf[leadrtIdx];
			
			std::vector<size_t>::iterator it = std::find(chain.begin(), chain.end(), leadrtIdx);
			size_t bound = static_cast<size_t>(it - chain.begin());
			
			insertVec(chain, vec, followerIdx, bound);
			if (t == lo)
				break;
		}
	}

	if (hasStraggler)
	{
		size_t	lo2 = 0;
		size_t	hi2 = chain.size();
		int		sval = vec[straggler];
		while (lo2 < hi2)
		{
			size_t mid = lo2 + (hi2 - lo2) / 2;
			if (vec[chain[mid]] < sval)
				lo2 = mid + 1;
			else
				hi2 = mid;
		}
		chain.insert(chain.begin() + static_cast<long>(lo2), straggler);
	}
	return chain;
}

void	PmergeMe::sortVec()
{
	std::vector<size_t> index;
	for (size_t i = 0; i < _vecInput.size(); i++)
		index.push_back(i);

	std::vector<size_t>	sortedIndex = fordJohnsonVec(index, _vecInput);
	std::vector<int>	result;
	for (size_t i = 0; i < sortedIndex.size(); i++)
		result.push_back(_vecInput[sortedIndex[i]]);
	printResVec(result);
}
