/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:19 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/29 14:07:02 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

void printVec(const std::string &label, const std::vector<int> &c)
{
	std::cout << label;
	for (std::vector<int>::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void printDeq(const std::string &label, const std::deque<int> &c)
{
	std::cout << label;
	for (std::deque<int>::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void fordJohnsonVec(std::vector<int> &c)
{
	if (c.size() <= 1)
		return;

	std::vector<std::pair<int, int> > pairs;
	std::vector<int> winners;
	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		int a = c[i];
		int b = c[i + 1];
		if (a < b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
		winners.push_back(a);
	}

	bool hasStraggler = (c.size() % 2 == 1);
	int straggler = 0;
	if (hasStraggler)
		straggler = c.back();

	fordJohnsonVec(winners);

	std::vector<int> pend;
	std::vector<bool> used(pairs.size(), false);
	for (size_t i = 0; i < winners.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == winners[i])
			{
				pend.push_back(pairs[j].second);
				used[j] = true;
				break;
			}
		}
	}

	std::vector<int> main = winners;
	main.insert(main.begin(), pend[0]);

	size_t m = pend.size();
	size_t jPrev = 1;
	size_t jCurr = 3;
	while (jPrev < m)
	{
		size_t top = jCurr;
		if (top > m)
			top = m;
		for (size_t j = top; j > jPrev; j--)
		{
			int value = pend[j - 1];
			std::vector<int>::iterator end =
				std::find(main.begin(), main.end(), winners[j - 1]);
			std::vector<int>::iterator pos =
				std::lower_bound(main.begin(), end, value);
			main.insert(pos, value);
		}
		size_t next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}

	if (hasStraggler)
	{
		std::vector<int>::iterator pos =
			std::lower_bound(main.begin(), main.end(), straggler);
		main.insert(pos, straggler);
	}

	c = main;
}

void fordJohnsonDeq(std::deque<int> &c)
{
	if (c.size() <= 1)
		return;

	std::deque<std::pair<int, int> > pairs;
	std::deque<int> winners;
	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		int a = c[i];
		int b = c[i + 1];
		if (a < b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
		winners.push_back(a);
	}

	bool hasStraggler = (c.size() % 2 == 1);
	int straggler = 0;
	if (hasStraggler)
		straggler = c.back();

	fordJohnsonDeq(winners);

	std::deque<int> pend;
	std::deque<bool> used(pairs.size(), false);
	for (size_t i = 0; i < winners.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == winners[i])
			{
				pend.push_back(pairs[j].second);
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> main = winners;
	main.insert(main.begin(), pend[0]);

	size_t m = pend.size();
	size_t jPrev = 1;
	size_t jCurr = 3;
	while (jPrev < m)
	{
		size_t top = jCurr;
		if (top > m)
			top = m;
		for (size_t j = top; j > jPrev; j--)
		{
			int value = pend[j - 1];
			std::deque<int>::iterator end =
				std::find(main.begin(), main.end(), winners[j - 1]);
			std::deque<int>::iterator pos =
				std::lower_bound(main.begin(), end, value);
			main.insert(pos, value);
		}
		size_t next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator pos =
			std::lower_bound(main.begin(), main.end(), straggler);
		main.insert(pos, straggler);
	}

	c = main;
}
