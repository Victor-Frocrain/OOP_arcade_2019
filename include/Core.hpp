/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Core.hpp
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Parser.hpp"
#include "Menu.hpp"
#include <chrono>

class Core {
public:
    /* Constructor */
    Core(Parser &parser) noexcept;
    Core(std::map<std::string, DLLoader<IGraph> *> &graphs,
         std::map<std::string, DLLoader<IGame> *> &games,
         IGraph *defaultGraph) noexcept;

    /* Destructor */
    ~Core(void) noexcept;

    /* Game method */
    void loop(void);

    void coreEvent(const IGraph::graphEvent &event);

    /* Private attribute */
private:
    std::map<std::string, DLLoader<IGraph> *> &_graphs;
    std::map<std::string, DLLoader<IGame> *> &_games;
    size_t _graphIt;
    size_t _gameIt;
    std::string _error;
    IGraph *_usedGraph;
    Menu *_menu;
    IGame *_usedGame;
    double _lastError;

    /* Event converter */
private:
    static const std::map<IGraph::graphEvent, IGame::gameEvent> _eventConverter;
};

#endif /* CORE_HPP_ */
