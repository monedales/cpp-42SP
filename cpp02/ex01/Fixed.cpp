/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:26:34 by mona              #+#    #+#             */
/*   Updated: 2026/09/13 15:23:16 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cmath>
#include "Fixed.hpp"


const int Fixed::fractBits = 8;

Fixed::Fixed(void)
{
	std::cout << "Default constructor called" << std::endl;
	this->value = 0;
}

Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src)
		this->value = src.value;
	return (*this);
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const int i_num)
{
	std::cout << "Int constructor called" << std::endl;
	this->value = i_num * (1 << fractBits);
}

Fixed::Fixed(const float f_num)
{
	std::cout << "Float constructor called" << std::endl;
	this->value = static_cast<int>(roundf(f_num * (1 << this->fractBits)));
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->value);
}

void Fixed::setRawBits(int const raw)
{
	this->value = raw;
}

float   Fixed::toFloat(void) const
{
	return (static_cast<float>(this->value) / (1 << this->fractBits));
}

int     Fixed::toInt(void) const
{
	return (this->value >> this->fractBits);
}

std::ostream &operator<<(std::ostream &obj, const Fixed &f_num)
{
	obj << f_num.toFloat();
	return (obj);
}
