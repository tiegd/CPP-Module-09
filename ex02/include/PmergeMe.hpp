/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:16 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/16 17:31:21 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PEMERGEME__
#define __PEMERGEME__

#include <string>
#include <vector>
#include <deque>
#include <ctime>

class PmergeMe
{
	private:
		clock_t				_tVec;
		clock_t				_tDeq;
		bool				_hasStraggler;
		int					_straggler;

		std::vector<int>	_vecResult;
		std::vector<int>	_vecInput;
		std::vector<size_t>	_jacobVec;

		std::deque<int>		_deqResult;
		std::deque<int>		_deqInput;
		std::deque<size_t>	_jacobDeq;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);
		PmergeMe(char** av);
		~PmergeMe();
		
		void							swap(int &x, int &y);

		/*----------std::parsing----------*/
		void							parser(char** av);
		
		/*----------std::vector----------*/
		void					jacobsthalVec();
		void					printJacobVec();
		void					insertVec(std::vector<size_t>& chain, std::vector<int> vec, size_t insertIdx, size_t bound);
		// std::vector<size_t>	fordJohnsonVec(std::vector<size_t> index, std::vector<int> vec);
		void					fordJohnsonVec(std::vector<std::vector<int> > vec, int u);
		void					sortVec();
		void					printVec(std::vector<int> vec);
		void					printDoubleVec(std::vector<std::vector<int> > vec);
		// void					swapVec(std::vector<int> &v1, std::vector<int> &v2);
		/*----------std::deque----------*/
		void							jacobsthalDeq();
		void							printJacobDeq();
		void							insertDeq(std::deque<size_t>& chain, std::deque<int> deq, size_t insertIdx, size_t bound);
		std::deque<size_t>				fordJohnsonDeq(std::deque<size_t> index, std::deque<int> deq);
		void							sortDeq();
		void							printDeq(std::deque<int> deq);
};

#endif
