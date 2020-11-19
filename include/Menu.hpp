/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: Menu.hpp
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "AGame.hpp"
#include "IGraph.hpp"
#include "DLLoader.hpp"
#include <map>
#include <chrono>
#include "Entity.hpp"

class Menu : public AGame {
public:
    Menu(std::map<std::string, DLLoader<IGraph> *> &graphs,
         std::map<std::string, DLLoader<IGame> *> &games,
         size_t &graphIt, size_t &gameIt,
         const std::string &lastError);

    /* Herited method */
    ~Menu(void) final;

    void nextCycle(const gameEvent &event) noexcept final;

    void manageEvent(const gameEvent &event) noexcept;

    static std::string getResized(const std::string &str) noexcept;

private:
    std::map<std::string, DLLoader<IGraph> *> &_graphs;
    std::map<std::string, DLLoader<IGame> *> &_games;
    size_t &_graphIt;
    size_t &_gameIt;
    bool _onGraph;
    std::chrono::time_point<std::chrono::system_clock> _lastColorChange;
    unsigned int _color;
    const std::string &_lastError;
    std::vector<Text *> _texts;
    std::map<std::string, std::string> _graphDisplay;
    std::map<std::string, std::string> _gameDisplay;
};

#endif /* MENU_HPP_ */
