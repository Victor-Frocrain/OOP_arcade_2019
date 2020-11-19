/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Core.cpp
*/

#include "Core.hpp"
#include <iostream>
#include "DLLoader.cpp"
#include "Menu.hpp"
#include "ArcadeUtils.hpp"

const std::map<IGraph::graphEvent, IGame::gameEvent> Core::_eventConverter {
    {IGraph::NOTHING, IGame::NOTHING},
    {IGraph::RIGHT, IGame::RIGHT},
    {IGraph::LEFT, IGame::LEFT},
    {IGraph::UP, IGame::UP},
    {IGraph::DOWN, IGame::DOWN},
    {IGraph::SPACE, IGame::SPACE}
};

Core::Core(Parser &parser) noexcept :
    _graphs(parser.getGraph()), _games(parser.getGame()),
    _graphIt(0), _gameIt(0), _error(""),
    _usedGraph(parser.getDefaultGraph()),
    _menu(new Menu(_graphs, _games, _graphIt, _gameIt, _error)),
    _usedGame(_menu), _lastError(0)
{}

Core::Core(std::map<std::string, DLLoader<IGraph> *> &graphs,
           std::map<std::string, DLLoader<IGame> *> &games,
           IGraph *defaultGraph) noexcept :
    _graphs(graphs), _games(games), _usedGraph(defaultGraph)
{}

Core::~Core(void) noexcept
{
    for (auto it : _graphs)
        delete it.second;
    for (auto it : _games)
        delete it.second;
}

void Core::coreEvent(const IGraph::graphEvent &event)
{
    switch (static_cast<int>(event)) {
    case IGraph::ENTER:
        if (_graphs.size() && _games.size()) {
            try {
                ArcadeUtils::getIterator(_games, _gameIt)->second->getInstance();
                if (_usedGraph != ArcadeUtils::getIterator(_graphs, _graphIt)->second->getInstance()) {
                    _usedGraph->closeWindow();
                    _usedGraph = ArcadeUtils::getIterator(_graphs, _graphIt)->second->getInstance();
                    _usedGraph->createWindow();
                }
                _usedGame = ArcadeUtils::getIterator(_games, _gameIt)->second->getInstance();
            } catch (const ArcadeException &error) {
                _error.assign(error.what());
                _lastError = 0;
            }
        }
        break;
    case IGraph::BACK_TO_MENU:
        _usedGame = _menu;
        break;
    case IGraph::NEXT_GAME:
        _gameIt++;
        _gameIt %= _games.size();
        break;
    case IGraph::PREV_GAME:
        _gameIt = ((_gameIt) ? _gameIt : _games.size()) - 1;
        break;
    case IGraph::NEXT_GRAPH:
        _graphIt++;
        _graphIt %= _graphs.size();
        break;
    case IGraph::PREV_GRAPH:
        _graphIt = ((_graphIt) ? _graphIt : _graphs.size()) - 1;
        break;
    }
}

void Core::loop(void)
{
    IGraph::graphEvent event = IGraph::NOTHING;
    double framerate = 30;
    double timeBetweenFrame = (1000 / framerate) / 1000;
    auto lastFrame = std::chrono::system_clock::now();
    double lastLibUpdate = 0;

    _usedGraph->createWindow();
    while (event != IGraph::EXIT) {
        if (ArcadeUtils::isTimePassed(lastFrame, timeBetweenFrame)) {
            event = _usedGraph->getEvent();
            _usedGame->nextCycle(ArcadeUtils::getConvertedEvent(_eventConverter, event, IGame::NOTHING));
            _usedGraph->displayWindow(_usedGame->getData());
            _lastError += timeBetweenFrame;
            lastLibUpdate += timeBetweenFrame;
            if (_lastError >= 5) {
                _error.assign("");
                _lastError = 0;
            }
            if (lastLibUpdate >= 2) {
                lastLibUpdate = 0;
                try {
                    Parser::setInterface(_graphs, "./lib/");
                } catch (const DirectoriesReaderException::DirectoriesReaderException &error) {
                    _graphs.clear();
                }
                try {
                    Parser::setInterface(_games, "./games/");
                } catch (const DirectoriesReaderException::DirectoriesReaderException &error) {
                    _games.clear();
                }
            }
            coreEvent(event);
        }
    }
    _usedGraph->closeWindow();
}
