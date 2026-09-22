/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:16 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/22 12:49:34 by gaducurt         ###   ########.fr       */
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
		int					_u;
		bool				_hasStraggler;
		int					_straggler;
		std::vector<int>	_vecStraggler;

		std::vector<int>	_vecResult;
		std::vector<int>	_vecInput;
		std::vector<int>	_vecTmp;
		std::vector<int>	_rest;
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
		void							jacobsthalVec();
		void							printJacobVec();
		void							insertVec(std::vector<size_t>& chain, std::vector<int> vec, size_t insertIdx, size_t bound);
		void							fordJohnsonVec();
		void							sortVec();
		void							printVec(std::vector<int> vec);
		void							printDoubleVec(std::vector<std::vector<int> > vec);
		void							cpVec(std::vector<std::vector<int> > vec);
		void							fillTmp1(std::vector<std::vector<int> > vec);
		void							fillTmp2(std::vector<std::vector<int> > vec);
		void							binInsert();

		/*----------std::deque----------*/
		void							jacobsthalDeq();
		void							printJacobDeq();
		void							insertDeq(std::deque<size_t>& chain, std::deque<int> deq, size_t insertIdx, size_t bound);
		std::deque<size_t>				fordJohnsonDeq(std::deque<size_t> index, std::deque<int> deq);
		void							sortDeq();
		void							printDeq(std::deque<int> deq);
};

#endif


#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"