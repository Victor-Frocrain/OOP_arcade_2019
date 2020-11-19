/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: Nibbler.hpp
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "ANibbler.hpp"

class Nibbler : public ANibbler {
public:
    /* Constructor */
    Nibbler(void);

    /* Heritate method */
    ~Nibbler(void);

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

#endif /* NIBBLER_HPP_ */
