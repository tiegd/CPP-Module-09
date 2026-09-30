/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:11:11 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/30 11:13:53 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>
#include <climits>

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
					throw std::logic_error("Error: not a digit or wrong operator: " + _input);
				nbOp++;
			}
		}
	}
	if (_input.size() == 0)
		throw std::logic_error("Error: string is empty");
	else if (nbDigit - 1 > nbOp)
		throw std::logic_error("Error: too many numbers or number biger than 9: " + _input);
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
		{
			size_t	nb = std::strtol(tmp.c_str(), NULL, 10);
			if (nb > INT_MAX)
			{
				throw std::logic_error("Error: overflow");
			}
			// _stack.push(std::atoi(tmp.c_str()));
			_stack.push(nb);
		}
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
	size_t	tmp;
	size_t	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() + tmp;
	if (res > INT_MAX)
		throw std::logic_error("Error: overflow");
	_stack.pop();
	_stack.push(res);
}

void	Rpn::sub()
{
	size_t	tmp;
	size_t	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() - tmp;
	if (res > INT_MAX)
		throw std::logic_error("Error: overflow");
	_stack.pop();
	_stack.push(res);
}

void	Rpn::mult()
{
	size_t	tmp;
	size_t	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() * tmp;
	if (res > INT_MAX)
		throw std::logic_error("Error: overflow");
	_stack.pop();
	_stack.push(res);
}

void	Rpn::div()
{
	size_t	tmp;
	size_t	res;

	if (_stack.size() < 1)
		throw std::logic_error("Error");
	if (_stack.top() == 0)
		throw std::logic_error("Error: div by 0");
	tmp = _stack.top();
	_stack.pop();
	res = _stack.top() / tmp;
	if (res > INT_MAX)
		throw std::logic_error("Error: overflow");
	_stack.pop();
	_stack.push(res);
}
