/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: ANcurses.cpp
*/

#include "ANcurses.hpp"
#include "ArcadeUtils.hpp"
#include "Entity.hpp"
#include <math.h>

ANcurses::ANcurses(const std::string &configPath,
                   const std::map<int, IGraph::graphEvent> &eventMap,
                   const ncursesChar &defaultChar) :
    _config(FileReader(configPath)), _game(_config.find("game")[0]),
    _win(nullptr), _defaultChar(defaultChar), _eventMap(eventMap)
{
    fillEntitiesMap();
}

ANcurses::~ANcurses(void)
{
    if (_win)
        delwin(_win);
}
const std::map<int, IGraph::graphEvent> ANcurses::_defaultEventMap {
    {'q', IGraph::EXIT},
    {'\e', IGraph::EXIT},
    {'P', IGraph::PREV_GAME},
    {'N', IGraph::NEXT_GAME},
    {'p', IGraph::PREV_GRAPH},
    {'n', IGraph::NEXT_GRAPH},
    {'m', IGraph::BACK_TO_MENU},
    {' ', IGraph::SPACE},
    {'\n', IGraph::ENTER},
    {CTRL('p'), IGraph::PREV_GRAPH},
    {CTRL('n'), IGraph::NEXT_GRAPH},
    {KEY_LEFT, IGraph::LEFT},
    {KEY_RIGHT, IGraph::RIGHT},
    {KEY_UP, IGraph::UP},
    {KEY_DOWN, IGraph::DOWN}
};

const ncursesChar ANcurses::_defaultDefaultChar = {'*', 7};
const size_t ANcurses::_maxCols = 80;
const size_t ANcurses::_maxLines = 40;

entityMap ANcurses::fillEntityMap(const std::string &section) noexcept
{
    entityMap map;
    short i = 0;
    try {
        std::vector<std::string> v = _config.find(section);

        for (auto it : v) {
            try {
                if (it.size() == 3 && it[1] == ':')
                    map[i++] = {it[0], std::stoi(it.substr(2, 1))};
            } catch (...) {}
        }
    } catch (const FileReaderException &error) {
        std::cerr << error.what() << std::endl;
    }
    if (!map.size())
        map[i] = _defaultChar;
    return map;
}

void ANcurses::fillEntitiesMap(void) noexcept
{
    _entitiesMap.clear();
    _entitiesMap[IEntity::PLAYER] = fillEntityMap("Player");
    _entitiesMap[IEntity::ENEMY] = fillEntityMap("Enemy");
    _entitiesMap[IEntity::WALL] = fillEntityMap("Wall");
    _entitiesMap[IEntity::ITEMS] = fillEntityMap("Items");
    _entitiesMap[IEntity::BONUS] = fillEntityMap("Bonus");
}

void ANcurses::displayWindow(const std::vector<IEntity *> &entities)
{
    _config.reset();
    if (!_config.find("game").empty() &&_config.find("game")[0] != _game) {
        _game = _config.find("game")[0];
        fillEntitiesMap();
    }
    clear();
    if (static_cast<unsigned int>(COLS) < _maxCols ||
        static_cast<unsigned int>(LINES) < _maxLines) {
        std::string error("Resize screen !");
        attron(COLOR_PAIR(1));
        mvaddstr(LINES / 2, COLS / 2 - error.size() / 2, error.c_str());
        error.assign("Minimum size: COLS(80), LINES(40)");
        mvaddstr(LINES / 2 + 1, COLS / 2 - error.size() / 2, error.c_str());
        attroff(COLOR_PAIR(1));
    } else {
        int top = LINES / 2 - _maxLines / 2;
        int left = COLS / 2  - _maxCols / 2;
        for (IEntity *it : entities) {
            if (it->getType() == IEntity::TEXT) {
                auto txt = dynamic_cast<const Text *>(it);
                attron(COLOR_PAIR(it->getNbType() % 8));
                std::string text = txt ? txt->getText() : "Wrong type";
                mvaddstr(top + it->getPosY(), left + it->getPosX() - text.size() / 2, text.c_str());
                attroff(COLOR_PAIR(it->getNbType() % 8));
            } else {
                displayEntity(it, top, left);
            }
        }
    }
}

void ANcurses::displayEntity(const IEntity *entity,
                                  const size_t &top, const size_t &left)
{
    auto iterator = _entitiesMap.find(entity->getType());
    if (iterator != _entitiesMap.end()) {
        auto type = iterator->second.find(entity->getNbType());
        auto it = type != iterator->second.end() ? type->second : iterator->second.begin()->second;
        attron(COLOR_PAIR(it.second));
        mvaddch(top + std::round(entity->getPosY()),
                left + std::round(entity->getPosX()), it.first);
        attroff(COLOR_PAIR(it.second));
    }
}

IGraph::graphEvent ANcurses::getEvent(void) const noexcept
{
    return ArcadeUtils::getConvertedEvent(_eventMap, getch(), IGraph::NOTHING);
}

void ANcurses::createWindow(void)
{
    _win = initscr();
    keypad(_win, true);
    noecho();
    nodelay(_win, true);
    curs_set(0);
    refresh();
    start_color();
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void ANcurses::closeWindow(void)
{
    curs_set(1);
    endwin();
}
