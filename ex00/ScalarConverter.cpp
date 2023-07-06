/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:23:54 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/06 11:31:49 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

enum
{
    CHAR,
    INT,
    DOUBLE,
    FLOAT,
    INF_TYPE,
    NAN_TYPE,
    TYPES_TOTAL
};


int strtoint(const std::string & str)
{
    errno = 0;
    long val = std::strtol(str.c_str(), 0, 10);
    if (val > std::numeric_limits<int>::max()
        || val < std::numeric_limits<int>::min()
        || errno == ERANGE)
        throw std::exception();
    return static_cast<int>(val);
}

double strtodouble(const std::string & str)
{
    errno = 0;
    double val = std::strtod(str.c_str(), 0);
    if (errno == ERANGE)
        throw std::exception();
    return val;
}

float strtofloat(const std::string & str)
{
    errno = 0;
    float val = std::strtod(str.c_str(), 0);
    if (errno == ERANGE)
        throw std::exception();
    return val;
}


ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(ScalarConverter const &copy)
{
    *this = copy;
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &copy)
{
    (void)copy;
    return *this;
}

bool isInf(const std::string &str)
{
    return str == "-inf" || str == "+inf";
}

bool isNan(const std::string &str)
{
    return str == "nan";
}

bool isInt(const std::string &str)
{
    size_t i = 0;

    if (str[0] == '+' || str[0] == '-')
        i++;
    while (str[i])
    {
        if (std::isdigit(str[i]) == false)
            return false;
        i++;
    }
    return true;
}

bool isDouble(const std::string &str, bool isType[TYPES_TOTAL])
{
    size_t i = 0;
    int dot = 0;
    bool sign = false;

    if (isNan(str) || isInf(str))
        return (isType[NAN_TYPE] = isType[NAN_TYPE] || isNan(str),
                isType[INF_TYPE] = isType[INF_TYPE] || isInf(str),
                true);
    if (str[0] == '+' || str[0] == '-')
        i++, sign = true;
    while (i < str.length())
    {
        if (str[i] == '.' && dot == 0 && i < str.length() - 1
            && ((sign == false && i > 0) || (sign == true && i > 1)))
            dot++;
        else if (std::isdigit(str[i]) == false)
            return false;
        i++;
    }
    if (dot == 1)
        return true;
    return false;
}

bool isFloat(const std::string &str, bool isType[TYPES_TOTAL])
{
    bool Double = isDouble(str.substr(0, str.length() - 1), isType);
    if (str[str.length() - 1] == 'f' && Double)
        return true;
    return false;
}

bool isChar(const std::string &str)
{
    return str.length() == 1 && !std::isdigit(str[0]);
}

std::string toChar(const std::string &str, bool isType[TYPES_TOTAL])
{
    int c = -1;

    if (isType[NAN_TYPE])
        return IMPOSSIBLE;
    else if (isType[INF_TYPE])
        return NON_DISPLAYABLE;
    if (isType[INT])
        try {c = strtoint(str);} catch (...) {return IMPOSSIBLE;}
    else if (isType[FLOAT])
        try {c = static_cast<int>(strtofloat(str));} catch (...) {return IMPOSSIBLE;}
    else if (isType[DOUBLE])
        try {c = static_cast<int>(strtodouble(str));} catch (...) {return IMPOSSIBLE;}
    else if (isType[CHAR])
        c = static_cast<int>(str[0]);
    if (c > std::numeric_limits<char>::max()
        || c < std::numeric_limits<char>::min())
        return IMPOSSIBLE;
    return std::isprint(c) ? '\'' + std::string() + static_cast<char>(c) + '\'' : NON_DISPLAYABLE;
}

std::string toInt(const std::string &str, bool isType[TYPES_TOTAL])
{
    int c = -1;
    std::stringstream ss;

    if (isType[NAN_TYPE])
        return IMPOSSIBLE;
    else if (isType[INF_TYPE])
        return IMPOSSIBLE;
    if (isType[INT])
        try {c = strtoint(str);} catch (...) {return IMPOSSIBLE;}
    else if (isType[FLOAT])
        try {c = static_cast<int>(strtofloat(str));} catch (...) {return IMPOSSIBLE;}
    else if (isType[DOUBLE])
        try {c = static_cast<int>(strtodouble(str));} catch (...) {return IMPOSSIBLE;}
    else if (isType[CHAR])
        c = static_cast<int>(str[0]);
    else
        return IMPOSSIBLE;
    ss << c;
    return ss.str();
}

std::string toFloat(const std::string &str, bool isType[TYPES_TOTAL])
{
    float c = -1;
    std::stringstream ss;

    if (isType[NAN_TYPE])
        c = NAN;
    else if (isType[INF_TYPE])
        c = str[0] == '-' ? -INFINITY : INFINITY;
    else if (isType[INT] || isType[FLOAT] || isType[DOUBLE])
        try {c = static_cast<float>(strtodouble(str));} catch (...) {return IMPOSSIBLE;}
    else if (isType[CHAR])
        c = static_cast<float>(str[0]);
    else
        return IMPOSSIBLE;
    ss << c;
    if (!std::isinf(c) && !std::isnan(c))
    {
        if (ss.str().find('.') == std::string::npos)
            ss << ".0";
        if (ss.str().find('f') == std::string::npos)
            ss << "f";
    }
    else
        ss << "f";
    return ss.str();
}

std::string toDouble(const std::string &str, bool isType[TYPES_TOTAL])
{
    double c = -1;
    std::stringstream ss;

    if (isType[NAN_TYPE])
        c = NAN;
    else if (isType[INF_TYPE])
        c = str[0] == '-' ? -INFINITY : INFINITY;
    else if (isType[INT] || isType[FLOAT] || isType[DOUBLE])
        try {c = strtodouble(str);} catch (...) {return IMPOSSIBLE;}
    else if (isType[CHAR])
        c = static_cast<double>(str[0]);
    else
        return IMPOSSIBLE;
    ss << c;
    if (!std::isinf(c) && !std::isnan(c))
    {
        if (ss.str().find('.') == std::string::npos)
            ss << ".0";
    }
    return ss.str();
}


void ScalarConverter::convert(const std::string &str)
{
    bool isType[TYPES_TOTAL];
    bool identified = false;

    isType[CHAR] = isChar(str);
    isType[INT] = isInt(str);
    isType[DOUBLE] = isDouble(str, isType);
    isType[FLOAT] = isFloat(str, isType);
    isType[NAN_TYPE] = false;
    isType[INF_TYPE] = false;

    for (int i = 0; i < TYPES_TOTAL; i++)
        if (isType[i])
            identified = true;
    
    if (identified)
    {
        std::cout << "char: " << toChar(str, isType) << std::endl;
        std::cout << "int: " << toInt(str, isType) << std::endl;
        std::cout << "float: " << toFloat(str, isType) << std::endl;
        std::cout << "double: " << toDouble(str, isType) << std::endl;
    }
    else
        std::cout << "have you tried?" << std::endl;
}