/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:26:17 by gaducurt          #+#    #+#             */
/*   Updated: 2026/08/03 14:24:49 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char** av)
{
	if (ac != 2)
		return (1);	
	// (void)av;
	BitcoinExchange test(av[1]);
	return (0);
}
