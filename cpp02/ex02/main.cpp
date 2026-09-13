/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:28:49 by mona              #+#    #+#             */
/*   Updated: 2026/09/13 17:05:00 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>


const std::string RESET   = "\033[0m";
const std::string BOLD    = "\033[1m";
const std::string LILAC   = "\033[38;2;200;162;200m";
const std::string PINK    = "\033[38;2;255;105;180m";
const std::string MINT    = "\033[38;2;150;255;200m";
const std::string PEACH   = "\033[38;2;255;190;150m";
const std::string CYAN    = "\033[38;2;120;220;255m";
const std::string RED     = "\033[38;2;255;80;80m";
const std::string MAGENTA = "\033[38;2;255;80;220m";


int main(void)
{
	std::cout << BOLD << LILAC << "\n----- Exemplo do subject -----" << RESET << std::endl;
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ));
	std::cout << LILAC << a << RESET << std::endl;
	std::cout << LILAC << ++a << RESET << std::endl;
	std::cout << LILAC << a << RESET << std::endl;
	std::cout << LILAC << a++ << RESET << std::endl;
	std::cout << LILAC << a << RESET << std::endl;
	std::cout << LILAC << b << RESET << std::endl;
	std::cout << LILAC << Fixed::max( a, b ) << RESET << std::endl;

	std::cout << BOLD << CYAN << "\n----- Comparadores -----" << RESET << std::endl;
	Fixed c(5);
	Fixed d(10);
	std::cout << CYAN << "c(5) < d(10): "  << (c < d)  << RESET << std::endl;
	std::cout << CYAN << "c(5) > d(10): "  << (c > d)  << RESET << std::endl;
	std::cout << CYAN << "c(5) <= c: "     << (c <= c) << RESET << std::endl;
	std::cout << CYAN << "c(5) >= d(10): " << (c >= d) << RESET << std::endl;
	std::cout << CYAN << "c(5) == c: "     << (c == c) << RESET << std::endl;
	std::cout << CYAN << "c(5) != d(10): " << (c != d) << RESET << std::endl;

	std::cout << BOLD << MINT << "\n----- operator- e operator/ -----" << RESET << std::endl;
	std::cout << MINT << "d(10) - c(5) = " << (d - c) << RESET << std::endl;
	std::cout << MINT << "d(10) / c(5) = " << (d / c) << RESET << std::endl;

	std::cout << BOLD << PEACH << "\n----- -- pre e pos -----" << RESET << std::endl;
	Fixed e(3);
	std::cout << PEACH << "e antes: "  << e   << RESET << std::endl;
	std::cout << PEACH << "--e vale: " << --e << RESET << std::endl;
	std::cout << PEACH << "e-- vale: " << e-- << RESET << std::endl;
	std::cout << PEACH << "e depois: " << e   << RESET << std::endl;

	std::cout << BOLD << MAGENTA << "\n----- min (nao-const e const) -----" << RESET << std::endl;
	Fixed f(1);
	Fixed g(2);
	std::cout << MAGENTA << "min(f=1, g=2) nao-const: " << Fixed::min(f, g) << RESET << std::endl;
	Fixed const constA(1);
	Fixed const constB(2);
	std::cout << MAGENTA << "min(constA=1, constB=2) const: " << Fixed::min(constA, constB) << RESET << std::endl;

	std::cout << BOLD << PINK << "\n----- toInt reforco -----" << RESET << std::endl;
	Fixed h(7.9f);
	std::cout << PINK << "h(7.9f).toInt() = " << h.toInt() << RESET << std::endl;

	return (0);
}
