/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(const float &pos_x, const float &pos_y,
               const IEntity::entitiesType &type, const short &nbType) :
    AEntity(pos_x, pos_y, type, nbType)
{}

Text::Text(const float &pos_x, const float &pos_y,
           const std::string &text, const short &nbType) :
    AEntity(pos_x, pos_y, IEntity::TEXT, nbType), _text(text)
{}

const std::string &Text::getText(void) const noexcept
{
    return _text;
}

void Text::setText(const std::string &text) noexcept
{
    _text = text;
}
