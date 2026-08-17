/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:16 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/17 10:39:37 by gaducurt         ###   ########.fr       */
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
		int*				_intArray;
		double				_timeManagement;
		double				_time1;
		double				_time2;
		std::string			_input;
		std::vector<int>	_cont1;
		std::deque<int>		_cont2; 
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);
		~PmergeMe();
		PmergeMe(std::string include);
		void	mergeInset();
		void	sort1(); // change the name after chosing both containers.
		void	sort2(); // change the name after chosing both containers.
};

#endif
