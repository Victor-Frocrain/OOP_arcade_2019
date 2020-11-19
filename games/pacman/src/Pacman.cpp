/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman(void) :
    APacman(3, "map/pacman.txt")
{}

Pacman::~Pacman(void)
{}

extern "C"
{
    IGame *newInstance(void)
    {
        return new Pacman;
    }
}
