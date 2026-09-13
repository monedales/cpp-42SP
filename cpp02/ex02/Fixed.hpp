/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 13:25:00 by mona              #+#    #+#             */
/*   Updated: 2026/09/13 16:42:13 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>
#include <ostream>


class Fixed
{
    private:
        int				    value;
        static const int    fractBits;
    public:
        Fixed(void);
		Fixed(const Fixed &src);
		Fixed &operator=(const Fixed &src);
		~Fixed(void);
        Fixed(const int i_num);
        Fixed(const float f_num);
        
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
        float   toFloat(void) const;
        int     toInt(void) const;

        bool operator>(const Fixed &other) const;
        bool operator<(const Fixed &other) const;
        bool operator>=(const Fixed &other) const;
        bool operator<=(const Fixed &other) const;
        bool operator==(const Fixed &other) const;
        bool operator!=(const Fixed &other) const;
        
        Fixed operator+(const Fixed &other) const;
        Fixed operator-(const Fixed &other) const;
        Fixed operator*(const Fixed &other) const;
        Fixed operator/(const Fixed &other) const;
        
        Fixed &operator++(void);
        Fixed  operator++(int);
        Fixed &operator--(void);
        Fixed  operator--(int);
        
        static Fixed &min(Fixed &a, Fixed &b);
        static const Fixed &min(const Fixed &a, const Fixed &b);
        static Fixed &max(Fixed &a, Fixed &b);
        static const Fixed &max(const Fixed &a, const Fixed &b);
    };
std::ostream &operator<<(std::ostream &obj, const Fixed &f_num);

#endif
