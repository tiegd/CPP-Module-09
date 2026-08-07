/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:11:11 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/07 10:37:10 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

Rpn::Rpn()
{
}

Rpn::Rpn(const Rpn &obj) : _stack(obj._stack)
{
}

Rpn& Rpn::operator=(const Rpn &obj)
{
	if (this != &obj)
		_stack = obj._stack;
	return *this;
}

Rpn::~Rpn()
{
}

Rpn::Rpn(std::string input) : _input(input)
{
	parser();
}

void	Rpn::parser()
{
	int	nbDigit = 0;
	int	nbOp = 0;

	for (size_t i = 0; i < _input.size(); i++)
	{
		if (!std::isdigit(_input[2]))
			throw std::logic_error("Error: bad input: " + _input);
		if (std::isdigit(_input[i]))
			nbDigit++;
		if (!std::isdigit(_input[i]))
		{
			if (_input[i] != ' ')
			{
				if (_input[i] != '+' && _input[i] != '-' && _input[i] != '/' && _input[i] != '*')
					throw std::logic_error("Error: not a digit or wrong operator: " + _input[i]);
				nbOp++;
			}
		}
	}
	if (nbDigit - 1 > nbOp)
		throw std::logic_error("Error: too many numbers: " + _input);
	else if (nbDigit - 1 < nbOp)
		throw std::logic_error("Error: too many operators: " + _input);
	std::string	tmp;
	std::stringstream	ss(_input);
	while (getline(ss, tmp, ' '))
	{
		if (tmp.size() > 1)
			throw std::logic_error("Error: number biger than 9: " + tmp);
	}
}

void	Rpn::compute()
{
	std::string			tmp;
	std::stringstream	ss(_input);
	void	(Rpn::*f[4])() = {
		&Rpn::add,
		&Rpn::sub,
		&Rpn::mult,
		&Rpn::div,
	};
	while (getline(ss, tmp, ' '))
	{
		if (std::isdigit(tmp[0]))
			_stack.push(std::atoi(tmp.c_str()));
		else
		{
			switch(tmp[0])
			{
				case '+':
					(this->*f[0])();
					break;
				case '-':
					(this->*f[1])();
					break;
				case '*':
					(this->*f[2])();
					break;
				case '/':
					(this->*f[3])();
					break;
			}
		}
	}
	std::cout << _stack.top() << std::endl;
}

void	Rpn::add()
{
	int	tmp;
	int	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() + tmp;
	_stack.pop();
	_stack.push(res);
}

void	Rpn::sub()
{
	int	tmp;
	int	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() - tmp;
	_stack.pop();
	_stack.push(res);
}

void	Rpn::mult()
{
	int	tmp;
	int	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() * tmp;
	_stack.pop();
	_stack.push(res);
}

void	Rpn::div()
{
	int	tmp;
	int	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() / tmp;
	_stack.pop();
	_stack.push(res);
}
