/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 11:15:27 by mona              #+#    #+#             */
/*   Updated: 2026/09/13 12:47:53 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"


int	main(void)
{
	Harl	level;

	level.complain("DEBUG");
	level.complain("INFO");
	level.complain("WARNING");
	level.complain("ERROR");
	level.complain("OOPS");
	return (0);
}
