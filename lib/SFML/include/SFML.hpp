/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: lib/SFML/SFML.hpp
*/

#ifndef SFML
#define SFML

#include "ASFML.hpp"

class Sfml : public ASFML {
public:
    /* Constructor */
    Sfml(void);

    /* Herited method */
    ~Sfml(void) final;
    void createWindow(void) final;
    void displayWindow(const std::vector<IEntity *> &entities) final;
    graphEvent getEvent(void) const noexcept final;
    void closeWindow(void) final;

private:
    enum KeyState {NOTHING, MAJ, CTRL};

    void checkText(const std::vector<IEntity *> &entities);
    void checkIfNewEntity(const std::vector<IEntity *> &entities);
    void addEntity(IEntity *entity);
    void replaceSprites(const std::vector<IEntity *> &entities);
    void drawEntity(const std::vector<IEntity *> &entity);
    void computeAnimSprite(IEntity *entity);
    float getRealPosition(const float &size, const int &border) const;
    int checkControl(void) const;

    void fillEntitiesMap(void) noexcept;
    std::string fillEntityMap(const std::string &section) noexcept;

private:
    static const std::map<std::pair<int, int>, IGraph::graphEvent> _eventMap;

    FileReader _config;
    std::string _game;
    std::map<IEntity::entitiesType, std::string> _entitiesMap;
};

extern "C"
{
    IGraph *newInstance(void);
}

#endif /* SFML */
