/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: Entity.hpp
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "AEntity.hpp"
#include <string>

class Entity : public AEntity {
public:
    Entity(const float &pos_x, const float &pos_y,
           const IEntity::entitiesType &type, const short &nbType = 0);
};

class Text : public AEntity {
public:
    Text(const float &pos_x, const float &pos_y,
         const std::string &text, const short &nbType = 0);

    /* Getter */
public:
    const std::string &getText(void) const noexcept;

    /* Setter */
public:
    void setText(const std::string &text) noexcept;

    /* Attribute */
private:
    std::string _text;
};

#endif /* ENTITY_HPP_ */
