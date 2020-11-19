/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: AGame.hpp
*/

#include "AGame.hpp"
#include <iostream>

AGame::~AGame(void)
{
    for (auto it : _entities)
        delete it;
}

const std::vector<IEntity *> &AGame::getData(void) const noexcept
{
    return _entities;
}

const IGame::gameState &AGame::getState(void) const noexcept
{
    return _state;
}
