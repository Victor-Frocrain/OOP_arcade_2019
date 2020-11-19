/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: Menu.cpp
*/

#include "Menu.hpp"
#include "Entity.hpp"
#include "ArcadeUtils.hpp"
#include "Parser.hpp"
#include "DLLoader.cpp"

Menu::Menu(std::map<std::string, DLLoader<IGraph> *> &graphs,
           std::map<std::string, DLLoader<IGame> *> &games,
           size_t &graphIt, size_t &gameIt,
           const std::string &lastError) :
    _graphs(graphs), _games(games),
    _graphIt(graphIt), _gameIt(gameIt), _onGraph(true),
    _lastColorChange(std::chrono::system_clock::now()), _color(0),
    _lastError(lastError)
{
    _texts.push_back(new Text(40, 20, "Graph: " +
ArcadeUtils::getIterator(_graphs, _graphIt)->first));
    _texts.push_back(new Text(40, 22, "Game: " +
ArcadeUtils::getIterator(_games, _gameIt)->first));
    _texts.push_back(new Text(40, 30, lastError));
    _entities.push_back(new Text(40, 18, "Arcade"));
    _entities.push_back(_texts[0]);
    _entities.push_back(_texts[1]);
    _entities.push_back(_texts[2]);
}

Menu::~Menu(void)
{}

void Menu::manageEvent(const gameEvent &event) noexcept
{
    if (_graphIt >= _graphs.size())
        _graphIt = _graphs.size() - 1;
    if (_gameIt >= _games.size())
        _gameIt = _games.size() - 1;
    switch (static_cast<int>(event)) {
    case RIGHT:
        if (_onGraph) {
            _graphIt++;
            _graphIt %= _graphs.size();
        } else {
            _gameIt++;
            _gameIt %= _games.size();
        }
        break;
    case LEFT:
        if (_onGraph)
            _graphIt = ((_graphIt) ? _graphIt : _graphs.size()) - 1;
        else
            _gameIt = ((_gameIt) ? _gameIt : _games.size()) - 1;
        break;
    case UP:
        _onGraph ^= 1;
        break;
    case DOWN:
        _onGraph ^= 1;
        break;
    }
}

void Menu::nextCycle(const gameEvent &event) noexcept
{
    if (ArcadeUtils::isTimePassed(_lastColorChange, 0.1)) {
        _color++;
        _color %= 7;
        for (auto it : _entities)
            it->setNbType(_color + 1);
    }
    manageEvent(event);
    if (_graphs.size()) {
        std::string str(ArcadeUtils::getIterator(_graphs, _graphIt)->first);
        auto graphIt = _graphDisplay.find(str);
        if (graphIt == _graphDisplay.end()) {
            _graphDisplay[str] = "Graph: " +
                ArcadeUtils::resizeString(ArcadeUtils::getFileName(str), 20);
            graphIt = _graphDisplay.find(str);
        }
        _texts[0]->setText(graphIt->second);
    } else
        _texts[0]->setText("No graphical library available");
    if (_games.size()) {
        std::string str(ArcadeUtils::getIterator(_games, _gameIt)->first);
        auto gameIt = _gameDisplay.find(str);
        if (gameIt == _gameDisplay.end()) {
            _gameDisplay[str] = "Game: " +
                ArcadeUtils::resizeString(ArcadeUtils::getFileName(str), 20);
            gameIt = _gameDisplay.find(str);
        }
        _texts[1]->setText(gameIt->second);
    } else
        _texts[1]->setText("No games library available");
    _texts[2]->setText(_lastError);
    // TODO
}
