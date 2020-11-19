/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: lib/Ncurses/Ncurses.hpp
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "ANcurses.hpp"

class Ncurses : public ANcurses {
public:
    /* Constructor */
    Ncurses(void);

    /* Method herited */
    virtual ~Ncurses(void) = default;
};

extern "C"
{
    IGraph *newInstance(void);
}

#endif /* NCURSES_HPP_ */
