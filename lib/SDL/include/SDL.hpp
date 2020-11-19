/*
** EPITECH PROJECT, 2020
** SDL
** File description:
** SDL.hpp
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include "ASDL.hpp"

class SDL : public ASDL {
public:
    SDL();
    ~SDL() final;
    void createWindow();
    void displayWindow(const std::vector<IEntity *> &entities);
    graphEvent getEvent(void) const noexcept;
    void closeWindow(void);

private:
    enum KeyState {NOTHING, MAJ, CTRL};

    void drawEntities(const std::vector<IEntity *> &entities);
    void compareEntities(const std::vector<IEntity *> &entities);
    void addEntity(IEntity *entity);
    int checkSize(const int &border) const;
    int checkKeyState(const SDL_Event &event) const;
    int computeRealSize(const int &size, const int &border) const;
    void checkTexts(const std::vector<IEntity *> &entities);
    void computeRectSprite(IEntity *entity, const bool &animate);
    int takeAfterDot(const double &nb) const;
    void replaceSprites(const std::vector<IEntity *> &entities);

    void fillEntitiesMap(void) noexcept;
    std::string fillEntityMap(const std::string &section) noexcept;

    static const std::map<std::pair<int, int>, IGraph::graphEvent> _eventMap;
    static const std::map<short, int> _playerState;
    static const std::map<short, int> _enemyType;

    FileReader _config;
    std::string _game;
    std::map<IEntity::entitiesType, std::string> _entitiesMap;
    bool _isInit;
};

extern "C"
{
    IGraph *newInstance(void);
}

#endif /* SDL_HPP_ */
