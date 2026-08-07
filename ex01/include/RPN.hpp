/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:11:25 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/07 10:37:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RPN__
#define __RPN__

#include <stack>
#include <iostream>

class   Rpn
{
	private:
		std::stack<int>	_stack;
		std::string		_input;
		Rpn();
		void	parser();
		void	add();
		void	sub();
		void	mult();
		void	div();
	public:
		Rpn(const Rpn &obj);
		Rpn &operator=(const Rpn &obj);
		~Rpn();
		Rpn(std::string input);
		void	compute();
};

#endif

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
