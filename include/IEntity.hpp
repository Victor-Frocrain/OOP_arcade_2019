/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

class IEntity {
public:
    /* Enum */
    enum entitiesType {TEXT, WALL, PLAYER, ENEMY, BONUS, ITEMS};

public:
    virtual ~IEntity(void) = default;

    /* Setter */
public:
    virtual IEntity &setPosX(const float &pos) noexcept = 0;
    virtual IEntity &setPosY(const float &pos) noexcept = 0;
    virtual IEntity &setNbType(const short &pos) noexcept = 0;

    /* Getter */
public:
    virtual const float &getPosX(void) const noexcept = 0;
    virtual const float &getPosY(void) const noexcept = 0;
    virtual const short &getNbType(void) const noexcept = 0;
    virtual const entitiesType &getType(void) const noexcept = 0;
};

#endif /* IENTITY_HPP_ */
