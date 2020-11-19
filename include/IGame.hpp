/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <string>
#include <vector>
#include "IEntity.hpp"

class IGame {
public:
    /*
    ** Enum
    */
    enum gameState {RUNNING, END};
    enum gameEvent {NOTHING, RIGHT, LEFT, UP, DOWN, SPACE};

public:
    /* Destructor */
    virtual ~IGame(void) = default;

    /*
    ** Send graphical event to compute
    ** next game status
    */
    virtual void nextCycle(const gameEvent &event) noexcept = 0;

    /*
    ** Get Game data needed by Graphical library
    */
    virtual const std::vector<IEntity *> &getData(void) const noexcept = 0;

    /*
    ** Get game state
    */
    virtual const gameState &getState(void) const noexcept = 0;
};

#endif /* IGAME_HPP_ */
