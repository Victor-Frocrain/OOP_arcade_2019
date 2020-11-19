/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: main.cpp
*/

#include "Core.hpp"
#include <iostream>
#include "DLLoader.hpp"

int main(int ac, char **av)
{
    try {
        Parser parser(ac, av);
        Core(parser).loop();
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
    return 0;
}
