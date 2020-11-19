/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: lib/Ncurses/Ncurses.cpp
*/

#include "Ncurses.hpp"

Ncurses::Ncurses(void) :
    ANcurses(".NcursesConfig.txt")
{}

extern "C"
{
    IGraph *newInstance(void)
    {
        return new Ncurses;
    }
}
