/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/27 18:08:45 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &obj) : _timeVec(obj._timeVec), _timeDeq(obj._timeDeq){}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		// _timeManagement = obj._timeManagement;
		_timeVec = obj._timeVec;
		_timeDeq = obj._timeDeq;
		// _vecInput = obj._vecInput;
		// _deqInput = obj._deqInput;
	}
	return *this;
}

PmergeMe::PmergeMe(char** av)
{
	std::vector<int>	vecInput;
	std::deque<int>		deqInput;
	for (int i = 1; av[i]; i++)
	{
		vecInput.push_back(atoi(av[i]));
		deqInput.push_back(atoi(av[i]));
	}
	// std::cout << "\n----------Vector----------\n\n_vec = ";
	// printVec(vecInput);
	// std::cout << "\n----------Deque----------\n\n_deq = ";
	// printDeq(deqInput);
	jacobsthalVec(vecInput);
	jacobsthalDeq(deqInput);
	sortVec(vecInput);
	sortDeq(deqInput);
}

PmergeMe::~PmergeMe(){}

/*---------VECTOR----------*/

void	PmergeMe::printVec(std::vector<int> vec)
{
	// std::cout << "\n----------Vector----------\n\n_vec = ";
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

void	PmergeMe::jacobsthalVec(std::vector<int> vec)
{
	size_t	res = 0;
	int i = 2;

	_jacobVec.push_back(0);
	_jacobVec.push_back(1);
	// std::cout << "_vec.size() = " << vec.size() << std::endl;
	while (res < vec.size() / 2)
	{
		res = _jacobVec[i - 2] * 2 + _jacobVec[i - 1];
		if (res > vec.size() / 2)
			break;
		_jacobVec.push_back(res);
		i++;
	}
	// printJacobVec();
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

void	PmergeMe::sortVec(std::vector<int> vec)
{
	std::vector<size_t> index;
	for (size_t i = 0; i < vec.size(); i++)
		index.push_back(i);

	std::vector<size_t>	sortedIndex = fordJohnsonVec(index, vec);
	std::vector<int>	result;
	for (size_t i = 0; i < sortedIndex.size(); i++)
		result.push_back(vec[sortedIndex[i]]);
	std::cout << "\n----------Result std::vector----------\n" << std::endl;
	printVec(result);
}

/*---------DEQUE----------*/

void	PmergeMe::printDeq(std::deque<int> deq)
{
	for (size_t i = 0; i < deq.size(); i++)
		std::cout << deq[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::printJacobDeq()
{
	std::cout << "\n----------Jacobsthal----------\n" << std::endl;
	for (size_t i = 0; i < _jacobDeq.size(); i++)
		std::cout << _jacobDeq[i] << ' ';
	std::cout << std::endl;
}

void	PmergeMe::jacobsthalDeq(std::deque<int> deq)
{
	size_t	res = 0;
	int i = 2;

	_jacobDeq.push_back(0);
	_jacobDeq.push_back(1);
	while (res < deq.size() / 2)
	{
		res = _jacobDeq[i - 2] * 2 + _jacobDeq[i - 1];
		if (res > deq.size() / 2)
			break;
		_jacobDeq.push_back(res);
		i++;
	}
	// printJacobDeq();
}

void	PmergeMe::insertDeq(std::deque<size_t>& chain, std::deque<int> deq, size_t insertIdx, size_t bound)
{
	size_t	lo = 0;
	size_t	hi = bound;
	int		value = deq[insertIdx];
	
	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
		if (deq[chain[mid]] < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + static_cast<long>(lo), insertIdx);
}

std::deque<size_t>	PmergeMe::fordJohnsonDeq(std::deque<size_t> index, std::deque<int> deq)
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
	
	std::deque<size_t> leaders;
	std::deque<size_t> followers;
	for (size_t i = 0; i < index.size(); i += 2)
	{
		size_t a = index[i];
		size_t b = index[i + 1];
		if (deq[a] > deq[b])
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
	
	std::deque<size_t> sortedLeaders = fordJohnsonDeq(leaders, deq);
	
	std::deque<size_t> followerOf(deq.size());
	for (size_t i = 0; i < leaders.size(); i++)
		followerOf[leaders[i]] = followers[i];
	
	std::deque<size_t> chain = sortedLeaders;
	
	size_t b1 = followerOf[sortedLeaders[0]];
	chain.insert(chain.begin(), b1);

	size_t m = sortedLeaders.size();

	for (size_t k = 2; k < _jacobDeq.size(); ++k)
	{
		size_t hi = std::min(_jacobDeq[k], m);
		size_t lo = _jacobDeq[k - 1] + 1;
		if (lo > hi)
			continue;
		for (size_t t = hi; t >= lo; --t)
		{
			size_t leadrtIdx = sortedLeaders[t - 1];
			size_t followerIdx = followerOf[leadrtIdx];
			
			std::deque<size_t>::iterator it = std::find(chain.begin(), chain.end(), leadrtIdx);
			size_t bound = static_cast<size_t>(it - chain.begin());
			
			insertDeq(chain, deq, followerIdx, bound);
			if (t == lo)
				break;
		}
	}

	if (hasStraggler)
	{
		size_t	lo2 = 0;
		size_t	hi2 = chain.size();
		int		sval = deq[straggler];
		while (lo2 < hi2)
		{
			size_t mid = lo2 + (hi2 - lo2) / 2;
			if (deq[chain[mid]] < sval)
				lo2 = mid + 1;
			else
				hi2 = mid;
		}
		chain.insert(chain.begin() + static_cast<long>(lo2), straggler);
	}
	return chain;
}

void	PmergeMe::sortDeq(std::deque<int> deq)
{
	std::deque<size_t> index;
	for (size_t i = 0; i < deq.size(); i++)
		index.push_back(i);

	std::deque<size_t>	sortedIndex = fordJohnsonDeq(index, deq);
	std::deque<int>	result;
	for (size_t i = 0; i < sortedIndex.size(); i++)
		result.push_back(deq[sortedIndex[i]]);
	std::cout << "\n----------Result std::deque----------\n" << std::endl;
	printDeq(result);
}
