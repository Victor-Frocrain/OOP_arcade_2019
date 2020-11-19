/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: AEntity.hpp
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"

class AEntity : public IEntity {
public:
    /* Constructor */
    AEntity(const float &pos_x, const float &pos_y,
            const IEntity::entitiesType &entityType, const short &nbType = 0);

    /* Destructor */
    virtual ~AEntity(void) = default;

    /* Setter */
public:
    IEntity &setPosX(const float &pos) noexcept final;
    IEntity &setPosY(const float &pos) noexcept final;
    IEntity &setNbType(const short &pos) noexcept final;

    /* Getter */
public:
    const float &getPosX(void) const noexcept final;
    const float &getPosY(void) const noexcept final;
    const short &getNbType(void) const noexcept final;
    const entitiesType &getType(void) const noexcept final;

    /* Attributes */
protected:
    float _pos_x;
    float _pos_y;
    const entitiesType _entityType;
    short _nbType;
};

#endif /* AENTITY_HPP_ */
