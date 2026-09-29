#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <climits>
#include <ctime>

// template <typename Container>
// void fordJohnson(Container &c)
void fordJohnsonVec(std::vector<int> &c)
{
	// 1. Cas de base : rien a trier
	if (c.size() <= 1)
		return;

	// 2. Former des paires (grand, petit)
	std::vector<std::pair<int, int> > pairs;
	// Container winners;
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

	// 3. Element seul si le nombre d'elements est impair
	bool hasStraggler = (c.size() % 2 == 1);
	int straggler = 0;
	if (hasStraggler)
		straggler = c.back();

	// 4. RECURSION : trier les grands
	fordJohnsonVec(winners);

	// 5. Retrouver le petit associe a chaque grand (dans l'ordre trie)
	// Container pend;
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

	// 6. Chaine principale = grands tries ; le 1er petit va tout au debut
	// Container chain = winners;
	std::vector<int> chain = winners;
	chain.insert(chain.begin(), pend[0]);

	// 7. Inserer les autres petits dans l'ordre de Jacobsthal
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
			// typename Container::iterator end =
			std::vector<int>::iterator end =
				std::find(chain.begin(), chain.end(), winners[j - 1]);
			// typename Container::iterator pos =
			std::vector<int>::iterator pos =
				std::lower_bound(chain.begin(), end, value);
			chain.insert(pos, value);
		}
		size_t next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}

	// 8. Inserer l'element seul (s'il existe) dans toute la chaine
	if (hasStraggler)
	{
		// typename Container::iterator pos =
		std::vector<int>::iterator pos =
			std::lower_bound(chain.begin(), chain.end(), straggler);
		chain.insert(pos, straggler);
	}

	c = chain;
}

void fordJohnsonDeq(std::deque<int> &c)
{
	// 1. Cas de base : rien a trier
	if (c.size() <= 1)
		return;

	// 2. Former des paires (grand, petit)
	std::deque<std::pair<int, int> > pairs;
	// Container winners;
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

	// 3. Element seul si le nombre d'elements est impair
	bool hasStraggler = (c.size() % 2 == 1);
	int straggler = 0;
	if (hasStraggler)
		straggler = c.back();

	// 4. RECURSION : trier les grands
	fordJohnsonDeq(winners);

	// 5. Retrouver le petit associe a chaque grand (dans l'ordre trie)
	// Container pend;
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

	// 6. Chaine principale = grands tries ; le 1er petit va tout au debut
	// Container chain = winners;
	std::deque<int> chain = winners;
	chain.insert(chain.begin(), pend[0]);

	// 7. Inserer les autres petits dans l'ordre de Jacobsthal
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
			// typename Container::iterator end =
			std::deque<int>::iterator end =
				std::find(chain.begin(), chain.end(), winners[j - 1]);
			// typename Container::iterator pos =
			std::deque<int>::iterator pos =
				std::lower_bound(chain.begin(), end, value);
			chain.insert(pos, value);
		}
		size_t next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}

	// 8. Inserer l'element seul (s'il existe) dans toute la chaine
	if (hasStraggler)
	{
		// typename Container::iterator pos =
		std::deque<int>::iterator pos =
			std::lower_bound(chain.begin(), chain.end(), straggler);
		chain.insert(pos, straggler);
	}

	c = chain;
}

/* ------------------------------------------------------------------ */
template <typename Container>
void printContainer(const std::string &label, const Container &c)
{
	std::cout << label;
	for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

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

	printContainer("Before:", vec);

	clock_t start = clock();
	fordJohnsonVec(vec);
	double timeVec = static_cast<double>(clock() - start) * 1000000.0 / CLOCKS_PER_SEC;

	start = clock();
	fordJohnsonDeq(deq);
	double timeDeq = static_cast<double>(clock() - start) * 1000000.0 / CLOCKS_PER_SEC;

	printContainer("After: ", vec);
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque  : " << timeDeq << " us" << std::endl;
	return 0;
}