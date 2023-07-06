/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharrad <mcharrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:50:17 by mcharrad          #+#    #+#             */
/*   Updated: 2023/07/06 12:10:16 by mcharrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

Base * generate(void)
{
    std::srand(std::time(0));
    int roll = std::rand() % 3;

    if (roll == 0)
        return new A();
    else if (roll == 1)
        return new B();
    else
        return new C();  
}

void identify(Base *p)
{
    A *a = dynamic_cast<A *>(p);
    B *b = dynamic_cast<B *>(p);
    C *c = dynamic_cast<C *>(p);
    
    std::cout << (a ? "A" : b ? "B" : c ? "C" : "???") << std::endl;
}

void identify(Base &p)
{
    std::string ret[3] = {"A", "B", "C"};

    for (int i = 0; i < 3; i++)
    {
        try
        {
            switch (i) {
            case 0: dynamic_cast<A &>(p); break;
            case 1: dynamic_cast<B &>(p); break;
            case 2: dynamic_cast<C &>(p); break;
            }
            std::cout << ret[i] << std::endl;
            return ;
        }
        catch (...)
        {
            
        }
    }
}

int main()
{
    Base *a = new A();
    Base *b = new B();
    Base *c = new C();

    Base *random = generate();

    std::cout << "Pointers:" << std::endl;
    identify(c);
    identify(b);
    identify(a);
    identify(random);
    std::cout << std::endl << "References:" << std::endl;
    identify(*c);
    identify(*b);
    identify(*a);
    identify(*random);

    delete a;
    delete b;
    delete c;
    delete random;
}

