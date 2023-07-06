/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:39:12 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/06 11:44:25 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main()
{
    Serializer serializer;
    Data data;

    data.serializer = &serializer;
    data.idfk = "???";
    std::cout << "Data (before): " << &data << std::endl;
    std::cout << "  ->idfk: " << data.idfk << std::endl; 
    std::cout << "  ->serializer: " << data.serializer << std::endl; 

    uintptr_t serial = serializer.serialize(&data);

    std::cout << "Serial: " << serial << std::endl;

    Data *deserializedData = serializer.deserialize(serial);

    std::cout << "Data (after): " << deserializedData << std::endl;
    std::cout << "  ->idfk: " << deserializedData->idfk << std::endl; 
    std::cout << "  ->serializer: " << deserializedData->serializer << std::endl; 

    return 0;
}