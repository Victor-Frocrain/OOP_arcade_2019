/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: IGraph.hpp
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

#include "IEntity.hpp"
#include <vector>

class IGraph {
public:
    /*
    ** Enum
    */
    enum graphEvent {NOTHING, RIGHT, LEFT, UP, DOWN, SPACE, EXIT, ENTER,
                     NEXT_GRAPH, PREV_GRAPH,
                     NEXT_GAME, PREV_GAME, BACK_TO_MENU};

public:
    /* Destructor */
    virtual ~IGraph(void) = default;

    virtual void createWindow(void) = 0;

    virtual void displayWindow(const std::vector<IEntity *> &entities) = 0;

    virtual void closeWindow(void) = 0;

    virtual graphEvent getEvent(void) const noexcept = 0;
};

#endif /* IGRAPH_HPP_ */
