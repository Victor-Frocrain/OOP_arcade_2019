/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Nibbler.cpp
*/

#include "../include/Nibbler.hpp"
#include "../../../include/Entity.hpp"

Nibbler::Nibbler(void) :
    ANibbler(1, "map/nibbler.txt")
{}

Nibbler::~Nibbler(void)
{}

extern "C"
{
    IGame *newInstance(void)
    {
        return new Nibbler;
    }
}
