#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <climits>
#include <ctime>

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

/* ------------------------------------------------------------------ */


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::deque<int> deq;
	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];
		if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		long n = std::strtol(argv[i], NULL, 10);
		if (n > INT_MAX)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		vec.push_back(static_cast<int>(n));
		deq.push_back(static_cast<int>(n));
	}

	printVec("Before:", vec);

	clock_t start = clock();
	fordJohnsonVec(vec);
	double timeVec = static_cast<double>(clock() - start) * 1000000.0 / CLOCKS_PER_SEC;

	start = clock();
	fordJohnsonDeq(deq);
	double timeDeq = static_cast<double>(clock() - start) * 1000000.0 / CLOCKS_PER_SEC;

	printVec("After: ", vec);
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque  : " << timeDeq << " us" << std::endl;
	return 0;
}