/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: INibbler.hpp
*/

#ifndef INIBBLER_HPP_
#define INIBBLER_HPP_

#include "../../../include/AGame.hpp"

class INibbler : public AGame {
public:
    enum Direction {LEFT, RIGHT, UP, DOWN, STAND};
public:
    /*
    ** Public method
    */
    virtual ~INibbler(void) = default;

    virtual void nextCycle(const gameEvent &event) noexcept = 0;

private:
    /*
    ** Private method
    */
    virtual void playerMovement(IEntity *entity, const Direction &direction) noexcept = 0;

    virtual bool moveTo(int x, int y) const noexcept = 0;

    virtual bool isWall(int x, int y) const noexcept = 0;

    virtual int isOutOfBounds(int x, int y) const noexcept = 0;
};

extern "C"
{
    IGame *newInstance(void);
}

#endif /* INIBBLER_HPP_ */
