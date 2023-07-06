/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:33:08 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/06 11:46:17 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stdint.h>

struct Data;

class Serializer {
    public:
        ~Serializer();
        Serializer();
        Serializer(Serializer const & copy);
        Serializer & operator=(Serializer const & copy);

        uintptr_t serialize(Data * ptr);
        Data * deserialize(uintptr_t raw);
};

struct Data {
    Serializer * serializer;
    std::string idfk;
};