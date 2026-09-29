/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:19:12 by gaducurt          #+#    #+#             */
/*   Updated: 2026/09/29 14:06:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
