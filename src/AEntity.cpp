/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: AEntity.cpp
*/

#include "AEntity.hpp"
#include <iostream>

AEntity::AEntity(const float &pos_x, const float &pos_y,
                 const IEntity::entitiesType &type, const short &nbType) :
    _pos_x(pos_x), _pos_y(pos_y), _entityType(type), _nbType(nbType)
{}

const float &AEntity::getPosX(void) const noexcept
{
    return _pos_x;
}

const float &AEntity::getPosY(void) const noexcept
{
    return _pos_y;
}

const short &AEntity::getNbType(void) const noexcept
{
    return _nbType;
}

const AEntity::entitiesType &AEntity::getType(void) const noexcept
{
    return _entityType;
}

IEntity &AEntity::setPosX(const float &pos) noexcept
{
    _pos_x = pos;
    return *this;
}

IEntity &AEntity::setPosY(const float &pos) noexcept
{
    _pos_y = pos;
    return *this;
}

IEntity &AEntity::setNbType(const short &nbType) noexcept
{
    _nbType = nbType;
    return *this;
}
