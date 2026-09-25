/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/24 16:49:23 by gaducurt         ###   ########.fr       */
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

struct	CmpLast
{
	bool operator()(const std::vector<size_t>& a, const std::vector<size_t>& b) const
	{
		return a.back() < b.back();
	}
};

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

/*---------VECTOR----------*/

void	PmergeMe::printVec(std::vector<size_t> vec)
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

	// _jacobVec.push_back(0);
	// _jacobVec.push_back(1);
	_jacobVec.push_back(3);
	_jacobVec.push_back(5);
	while (res < _vecInput.size() >> 1)
	{
		res = (_jacobVec[i - 2] << 1) + _jacobVec[i - 1];
		if (res > _vecInput.size() >> 1)
			break;
		_jacobVec.push_back(res);
		i++;
	}
	printVec(_jacobVec);
}

void	PmergeMe::printDoubleVec(std::vector<std::vector<size_t> > vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "[ ";
		for (size_t j = 0; j < vec[i].size(); j++)
			std::cout << vec[i][j] << " ";
		std::cout << "] ";
	}
	// if (_hasStraggler)
	// 	std::cout << _straggler;
	// std::cout << "\n" << std::endl;
}

void	PmergeMe::fillTmp(std::vector<std::vector<size_t> > vec, std::vector<size_t> vecStraggler)
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
	for (size_t i = 0; i < vecStraggler.size(); i++)
	{
		_vecTmp.push_back(vecStraggler[i]);
		// std::cout << YELLOW << vecStraggler[i] << " " << RESET;
	}
	std::cout << std::endl;
}

void	PmergeMe::fordJohnsonVec()
{
	std::vector<size_t>	vecStraggler;

	if ((std::size_t)pow(2, _u) >= _vecInput.size())
		return ;
	size_t	index = 0;
	size_t add = 0;
	std::vector<size_t>	tmp;
	std::cout << BLUE << "u = " << _u << RESET << std::endl;
	if (_u == 0)
	{
		if (_vecInput.size() % 2 != 0)
			vecStraggler.push_back(_vecInput[_vecInput.size() - 1]);
		for (size_t i = 0; i < _vecInput.size(); i++)
		{
			tmp.clear();
			tmp.push_back(_vecInput[i]);
			_main.push_back(tmp);
		}
		if (_main.size() % 2 != 0)
			add = 1;
		for (size_t i = 0; i < _main.size() - add; i+=2)
		{
			if (_main[i][_main[i].size() - 1] > _main[i+1][_main[i].size() - 1])
				_main[i].swap(_main[i+1]);
		}
	}
	else
	{
		_main.clear();
		for (size_t i = 0; i < _vecTmp.size(); i++)
		{
			tmp.clear();
			if (i + pow(2, _u) < _vecTmp.size())
			{
				for (int j = 0; j < pow(2, _u); j++)
				{
					tmp.push_back(_vecTmp[i]);
					index = i;
					if (j < pow(2, _u) - 1)
						i++;
				}
				_main.push_back(tmp);
			}
		}
		index++;
		std::cout << RED << "_vecTmp = " << std::endl;
		printVec(_vecTmp);
		for (; index < _vecTmp.size(); index++)
			vecStraggler.push_back(_vecTmp[index]);
		std::cout << "_vecTmp = " << std::endl;
		printVec(_vecTmp);
		std::cout << RESET;
		if (_main.size() % 2 != 0)
			add = 1;
		for (size_t i = 0; i < _main.size() - add; i+=2)
		{
			if (_main[i][_main[i].size() - 1] > _main[i+1][_main[i].size() - 1])
				_main[i].swap(_main[i+1]);
		}
	}
	_u++;
	std::cout << "_main = ";
	fillTmp(_main, vecStraggler);
	// vecStraggler.clear();
	std::cout << "_vecTmp = ";
	printVec(_vecTmp);
	std::cout << "vecStraggler = ";
	printVec(vecStraggler);
	std::cout << std::endl;
	fordJohnsonVec();
	
	/*----------Unrolling----------*/
	
	_u--;
	std::cout << BLUE << "u = " << _u << RESET << std::endl;

	std::vector<std::vector<size_t> >	pend;
	std::vector<std::vector<size_t> >::iterator it;
	std::cout << RED << "main.size() = " << _main.size() << RESET << std::endl;
	std::cout << "main before insert = ";
	printDoubleVec(_main);

	if (pow(2, _u) < _vecInput.size())
	{
		std::cout << RED << "\ntest" << RESET << std::endl;
		_vecTmp.clear();
		std::cout << "\n_main.size() = " << _main.size() << std::endl;
		for (size_t i = 0; i < _main.size(); i++)
			for (size_t j = 0; j < _main[i].size(); j++)
				_vecTmp.push_back(_main[i][j]);
		for (size_t i = 0; i < vecStraggler.size(); i++)
			_vecTmp.push_back(vecStraggler[i]);
		std::cout << "_vecTmp = ";
		printVec(_vecTmp);
		_main.clear();
	// }
		for (size_t i = 0; i < _vecTmp.size(); i++)
		{
			tmp.clear();
			if (i + pow(2, _u) < _vecTmp.size())
			{
				for (int j = 0; j < pow(2, _u); j++)
				{
					tmp.push_back(_vecTmp[i]);
					index = i;
					if (j < pow(2, _u) - 1)
						i++;
				}
				_main.push_back(tmp);
			}
		}
		std::cout << "\nmain = ";
		printDoubleVec(_main);
		for (; index < _vecTmp.size(); index++)
			vecStraggler.push_back(_vecTmp[index]);
		for (it = _main.begin() + 2; it < _main.end(); it++)
		{
			pend.push_back(*it);
			_main.erase(it);
			std::cout << YELLOW << "\npend = ";
			printDoubleVec(pend);
			std::cout << "\nmain = ";
			printDoubleVec(_main);
			std::cout << RESET;
		}
		std::cout << "\n--------------------" << std::endl;
		std::cout << "pend = ";
		printDoubleVec(pend);
		std::cout << "\nmain = ";
		printDoubleVec(_main);
		size_t	pos = 0;
		std::cout << "\npend.size() = " << pend.size() << std::endl;
		for (size_t i = 0; i < pend.size(); i++)
		{
			if (pos == 0)
			{
				for (int jac = (int)_jacobVec[pos] - 2; jac >= 0; jac-- && i++)
				{
					std::cout << GREEN << "jac = " << jac << std::endl;// << "\ni = " << i << RESET << std::endl;
					if (jac >= (int)pend.size())
						while (jac >= (int)pend.size())
							jac--;
					std::vector<std::vector<size_t> >::iterator it = std::lower_bound(_main.begin(), _main.end(), pend[jac], CmpLast());
					_main.insert(it, pend[jac]);
					std::cout << BLUE << "\npend = ";
					std::cout << "\nmain = ";
					printDoubleVec(_main);
					std::cout << RESET << std::endl;
					// vecStraggler = fillTmp2(_main);
				}
				pos++;
			}
			else
			{
				for (int jac = (int)_jacobVec[pos] - 2; jac >= (int)_jacobVec[pos - 1]; jac-- && i++)
				{
					if (jac >= (int)pend.size())
						while (jac >= (int)pend.size())
							jac--;
					std::vector<std::vector<size_t> >::iterator it = std::lower_bound(_main.begin(), _main.end(), pend[jac], CmpLast());
					_main.insert(it, pend[jac]);
				}
			}
			pos++;
		}
	}
	std::cout << "main after insert = ";
	printDoubleVec(_main);
	std::cout << std::endl;
}

void	PmergeMe::sortVec()
{
	_tVec = clock();
	_u = 0;

	fordJohnsonVec();
	_tVec = clock() - _tVec;
	// std::cout << "\n----------Result std::vector----------\n" << std::endl;
}

/*---------DEQUE----------*/
