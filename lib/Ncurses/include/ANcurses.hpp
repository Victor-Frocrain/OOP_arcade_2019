/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: lib/Ncurse/ANcurses.hpp
*/

#ifndef ANCURSES_HPP_
#define ANCURSES_HPP_

#include "INcurses.hpp"
#include <curses.h>
#include "FileReader.hpp"

#ifndef CTRL
#define CTRL(c) (c & 037)
#endif /* CTRL */

class ANcurses : public INcurses {
public:
    ANcurses(const std::string &configPath, const std::map<int, IGraph::graphEvent>
             &eventMap = ANcurses::_defaultEventMap, const ncursesChar &defaultChar =
             ANcurses::_defaultDefaultChar);

    /* Herited method */
    virtual ~ANcurses(void);

    virtual void createWindow(void) final;

    virtual void displayWindow(const std::vector<IEntity *> &entities) final;

    virtual graphEvent getEvent(void) const noexcept final;

    virtual void closeWindow(void) final;

    /* Private method */
private:
    virtual void displayEntity(const IEntity *entity,
                               const size_t &top, const size_t &left) final;

    virtual void fillEntitiesMap(void) noexcept final;

    virtual entityMap fillEntityMap(const std::string &section) noexcept final;

    /* Attribute */
private:
    FileReader _config;
    std::string _game;
    WINDOW *_win;
    std::map<IEntity::entitiesType, entityMap> _entitiesMap;
    const ncursesChar &_defaultChar;
    const std::map<int, IGraph::graphEvent> &_eventMap;

protected:
    static const size_t _maxCols;
    static const size_t _maxLines;

    /* Default Attribute */
private:
    static const std::map<int, IGraph::graphEvent> _defaultEventMap;
    static const ncursesChar _defaultDefaultChar;
};

#endif /* ANCURSES_HPP_ */
