/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:16 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/27 18:08:01 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PEMERGEME__
#define __PEMERGEME__

#include <string>
#include <vector>
#include <deque>

class PmergeMe
{
	private:
		// double				_timeManagement;
		double				_timeVec;
		double				_timeDeq;
		// std::vector<int>	_vecInput;
		std::vector<int>	_vecResult;
		std::vector<size_t>	_jacobVec;

		// std::deque<int>		_deqInput;
		std::deque<int>		_deqResult;
		std::vector<size_t>	_jacobDeq;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);
		~PmergeMe();
		PmergeMe(char** av);
		
		void					printVec(std::vector<int> vec);
		void					printDeq(std::deque<int> deq);
		
		void					jacobsthalVec(std::vector<int> vec);
		void					printJacobVec();
		void					insertVec(std::vector<size_t>& chain, std::vector<int> vec, size_t insertIdx, size_t bound);
		std::vector<size_t>		fordJohnsonVec(std::vector<size_t> index, std::vector<int> vec);
		void					sortVec(std::vector<int> vec);
		// void					printResVec(std::vector<int> res);

		void					jacobsthalDeq(std::deque<int> deq);
		void					printJacobDeq();
		void					insertDeq(std::deque<size_t>& chain, std::deque<int> deq, size_t insertIdx, size_t bound);
		std::deque<size_t>		fordJohnsonDeq(std::deque<size_t> index, std::deque<int> deq);
		void					sortDeq(std::deque<int> deq);
		// void					printResDeq(std::deque<int> res);
};

#endif
