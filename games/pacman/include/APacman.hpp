/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: APacman.hpp
*/

#ifndef APACMAN_HPP
#define APACMAN_HPP

#include "IPacman.hpp"
#include <map>
#include "Entity.hpp"

class APacman : public IPacman {
public:
    APacman(const size_t &nbLife, const std::string &mapPath,
            const std::map<char, IEntity::entitiesType> &mapConverter =
            APacman::_defaultMapConverter);

public:
    /*
    ** Public method
    */
    virtual ~APacman(void) = default;

    virtual void nextCycle(const gameEvent &event) noexcept final;

private:
    /*
    ** Private method
    */
    virtual void resetGame(void) noexcept;

    virtual void entityMovement(IEntity *entity, const Direction &direction) const noexcept;

    virtual void playerMovement(IEntity *entity, const gameEvent &event) noexcept;

    virtual void enemyMovement(IEntity *entity, Direction &direction) noexcept;

    virtual void manageCollision(IEntity *entity, size_t &index) noexcept;

    virtual bool moveTo(int x, int y) const noexcept;

    virtual bool isWall(int x, int y) const noexcept;

    virtual int isOutOfBounds(int x, int y) const noexcept;

    virtual void readBestScores();

    virtual int checkScores(const std::string &line) const;

    virtual int takeScore(const std::string &line) const;

    virtual void enterName();

    virtual void addNewScore();

    virtual void writeNewScore() const;

    virtual void addScoresList();

    /* Shared attribute */
protected:
    std::string _mapPath;
    std::vector<std::string> _map;
    size_t _top;
    size_t _left;
    size_t _nbLife;
    float _clock;
    std::vector<float> _spawnEnemy;
    float _lastBonus;
    Text *_life;
    std::vector<IEntity *> _enemy;
    IEntity *_player;
    std::pair<int, int> _playerSpawn;
    Direction _playerDirection;
    int _score;
    Text *_scoreEntity;
    const std::map<char, IEntity::entitiesType> _mapConverter;
    std::map<IEntity::entitiesType, char> _mapConverterRev;
    std::vector<std::pair<int, int >> _enemySpawns;
    std::vector<Direction> _enemyDirections;
    std::vector<Text *> _characters;
    bool _newScore;
    std::string _newName;
    size_t _scorePosition;
    size_t _nbItems;

    /* Attribute */
private:
    static const std::map<Direction, Direction> _reversedDirection;
    static const std::map<Direction, std::pair<int , int>> _mapMove;
    static const std::map<gameEvent, Direction> _mapDirection;
    static const std::map<char, IEntity::entitiesType> _defaultMapConverter;
};

#endif /* APACMAN_HPP */
