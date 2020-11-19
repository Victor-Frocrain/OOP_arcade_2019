/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Pacman.hpp
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "APacman.hpp"
#include <map>

class Pacman : public APacman {
public:
    /* Constructor */
    Pacman(void);

    /* Heritate method */
    ~Pacman(void);

    /* Attribute */
private:
    unsigned int _top;
    unsigned int _left;
    bool _isUnderBonus;
    IEntity *_player;
    unsigned int _score;
    std::vector<IEntity *> _enemy;
    std::vector<IEntity *> _life;

    /* Static const map */
private:
    static const std::map<char, IEntity::entitiesType> _mapConverter;
};

extern "C"
{
    IGame *newInstance(void);
}

#endif /* PACMAN_HPP_ */
