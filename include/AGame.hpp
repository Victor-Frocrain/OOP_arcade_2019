/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: AGame.hpp
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"

class AGame : public IGame {
public:
    /* Heritated method */
    virtual ~AGame(void);

    virtual void nextCycle(const gameEvent &event) noexcept = 0;

    virtual const std::vector<IEntity *> &getData(void) const noexcept final;

    virtual const gameState &getState(void) const noexcept final;

    /* Attribute */
protected:
    std::vector<IEntity *> _entities;
    gameState _state;
};

#endif /* AGAME_HPP_ */
