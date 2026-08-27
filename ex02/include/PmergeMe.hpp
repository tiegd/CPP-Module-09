/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:16 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/27 16:16:47 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PEMERGEME__
#define __PEMERGEME__

#include <string>
#include <vector>
#include <deque>

// typedef struct	Nb
// {
// 	int		nb;
// 	int		index;
// 	bool	largest;
// }				Nb;

typedef struct	Pair
{
	size_t		_small;
	size_t		_large;
	size_t		_index;
	bool		_isAlone;
}				Pair;

class PmergeMe
{
	private:
		// int*				_intArray;
		double				_timeManagement;
		double				_time1;
		double				_time2;
		std::vector<int>	_vecInput;
		std::vector<int>	_vecResult;
		std::vector<size_t>	_jacobVec;
		// std::vector<Nb>	_vec;
		std::deque<int>		_deqInput;
		std::deque<int>		_deqResult;
		std::vector<size_t>	_jacobDeq;
		// std::vector<Pair>		_vec;
		// std::deque<Pair>		_deq; 
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);
		~PmergeMe();
		PmergeMe(char** av);
		
		void	printVec();
		void	printDeq();
		void	printJacob();
		
		void					jacobsthalVec();
		void					insertVec(std::vector<size_t>& chain, std::vector<int> vec, size_t insertIdx, size_t bound);
		std::vector<size_t>		fordJohnsonVec(std::vector<size_t> index, std::vector<int> vec);
		// std::vector<int>		sortVec();
		void					sortVec();
		void					printResVec(std::vector<int> res);

		void	jacobsthalDeq();
		void	insertDeq();
		void	fordJohnsonDeq();
		void	sortDeq();
		void					printResDeq(std::deque<int> res);
};

#endif
