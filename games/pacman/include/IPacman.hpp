/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: IPacman.hpp
*/

#ifndef IPACMAN_HPP_
#define IPACMAN_HPP_

#include "AGame.hpp"

class IPacman : public AGame {
public:
    enum Direction {LEFT, RIGHT, UP, DOWN, STAND};
public:
    /*
    ** Public method
    */
    virtual ~IPacman(void) = default;

    virtual void nextCycle(const gameEvent &event) noexcept = 0;

private:
    /*
    ** Private method
    */
    virtual void resetGame(void) noexcept = 0;

    virtual void entityMovement(IEntity *entity, const Direction &direction) const noexcept = 0;

    virtual void playerMovement(IEntity *entity, const gameEvent &event) noexcept = 0;

    virtual void enemyMovement(IEntity *entity, Direction &direction) noexcept = 0;

    virtual void manageCollision(IEntity *entity, size_t &index) noexcept = 0;

    virtual bool moveTo(int x, int y) const noexcept = 0;

    virtual bool isWall(int x, int y) const noexcept = 0;

    virtual int isOutOfBounds(int x, int y) const noexcept = 0;
};

#endif /* IPACMAN_HPP_ */
