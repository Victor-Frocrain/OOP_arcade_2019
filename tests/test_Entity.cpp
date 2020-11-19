/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: test_Entity.cpp
*/

#include <criterion/criterion.h>
#include "Entity.hpp"

Test(Entity, entityType)
{
    cr_expect_eq(Entity(0, 0, IEntity::WALL).getType(), IEntity::WALL);
    cr_expect_eq(Entity(0, 0, IEntity::PLAYER).getType(), IEntity::PLAYER);
    cr_expect_eq(Entity(0, 0, IEntity::ENEMY).getType(), IEntity::ENEMY);
    cr_expect_eq(Text(0, 0, "hey").getType(), IEntity::TEXT);
}

Test(Entity, text)
{
    IEntity *entity = new Text(0, 0, "Score: " + std::to_string(10));
    cr_assert(dynamic_cast<Text *>(entity));
    cr_expect_eq(dynamic_cast<Text *>(entity)->getText(), "Score: 10");
    cr_expect_not(dynamic_cast<Text *>(new Entity(0, 0, IEntity::TEXT)));
    dynamic_cast<Text *>(entity)->setText("Score: " + std::to_string(20));
    cr_expect_eq(dynamic_cast<Text *>(entity)->getText(), "Score: 20");
}

Test(Entity, AEntity)
{
    cr_expect_eq(Text(-1, 0, "").getPosX(), -1);
    cr_expect_eq(Text(0, -1, "").getPosY(), -1);
    cr_expect_eq(Text(0, 0, "", -1).getNbType(), -1);
    cr_expect_eq(Text(-1, 0, "").setPosX(2).getPosX(), 2);
    cr_expect_eq(Text(0, -1, "").setPosY(2).getPosY(), 2);
    cr_expect_eq(Text(0, 0, "", -1).setNbType(2).getNbType(), 2);
}
