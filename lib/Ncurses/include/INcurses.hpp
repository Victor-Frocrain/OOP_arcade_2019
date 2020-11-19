/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: INcurses.hpp
*/

#ifndef INCURSES_HPP_
#define INCURSES_HPP_

#include  "IGraph.hpp"
#include <string>
#include <map>

typedef std::pair<char, int> ncursesChar;
typedef std::map<short, ncursesChar> entityMap;


class INcurses : public IGraph {
public:
    virtual ~INcurses(void) = default;

    virtual void createWindow(void) = 0;

    virtual void displayWindow(const std::vector<IEntity *> &entities) = 0;

    virtual graphEvent getEvent(void) const noexcept = 0;

    virtual void closeWindow(void) = 0;

private:
    virtual void displayEntity(const IEntity *entity,
                               const size_t &top,  const size_t &left) = 0;

    virtual void fillEntitiesMap(void) noexcept = 0;

    virtual entityMap fillEntityMap(const std::string &section) noexcept = 0;
};

#endif /* */
