/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:16 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/26 14:12:11 by gaducurt         ###   ########.fr       */
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
	int		_small;
	int		_large;
	int		_index;
	bool	_isAlone;
}				Pair;

class PmergeMe
{
	private:
		// int*				_intArray;
		double				_timeManagement;
		double				_time1;
		double				_time2;
		// std::vector<int>	_vec;
		// std::vector<Nb>	_vec;
		// std::deque<int>		_deq; 
		std::vector<Pair>		_vec;
		std::vector<int>		_jacob;
		std::deque<Pair>		_deq; 
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);
		~PmergeMe();
		PmergeMe(int ac, char** av);
		void	printVec();
		void	printDeq();
		void	printJacob();
		void	swap(int* a, int* b);
		void	genJacobsthal();
		void	mergeInset();
		void	sort1(); // change the name after chosing both containers.
		void	sort2(); // change the name after chosing both containers.
};

#endif
