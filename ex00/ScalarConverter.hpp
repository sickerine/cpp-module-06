/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:21:45 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/17 09:14:46 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <cerrno>
#include <sstream>
#include <cmath>

#define IMPOSSIBLE "impossible"
#define NON_DISPLAYABLE "Non displayable"

class ScalarConverter {
    private:
        ScalarConverter();
        ScalarConverter(ScalarConverter const & copy);
        ScalarConverter & operator=(ScalarConverter const & copy);
    public:
        ~ScalarConverter();

        static void convert(const std::string & str);
};