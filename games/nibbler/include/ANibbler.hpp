/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: ANibbler.hpp
*/

#ifndef ANIBBLER_HPP_
#define ANIBBLER_HPP_

#include "INibbler.hpp"
#include <map>
#include "../../../include/Entity.hpp"
#include <ctime>
#include <chrono>

class ANibbler : public INibbler {
public:
    ANibbler(const size_t &nbLife, const std::string &mapPath,
            const std::map<char, IEntity::entitiesType> &mapConverter =
            ANibbler::_defaultMapConverter);

public:
    /*
    ** Public method
    */
    virtual ~ANibbler(void) = default;

    virtual void nextCycle(const gameEvent &event) noexcept final;

private:
    /*
    ** Private method
    */
    virtual void playerMovement(IEntity *entity, const Direction &direction) noexcept;

    virtual bool moveTo(int x, int y) const noexcept;

    virtual bool isWall(int x, int y) const noexcept;

    virtual int isOutOfBounds(int x, int y) const noexcept;

    virtual void moveQueue(float speedX, float speedY);

    virtual void generateItem();

    virtual void addCorpse();

    virtual bool eatQueue() const;

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
    Text *_life;
    std::vector<IEntity *> _player;
    Direction _playerDirection;
    int _score;
    Text *_scoreEntity;
    const std::map<char, IEntity::entitiesType> _mapConverter;
    std::map<IEntity::entitiesType, char> _mapConverterRev;
    bool haveFood;
    std::chrono::time_point<std::chrono::system_clock> _clock;
    std::vector<Text *> _characters;
    bool _newScore;
    std::string _newName;
    size_t _scorePosition;

    /* Attribute */
private:
    static const std::map<Direction, std::pair<int , int>> _mapMove;
    static const std::map<gameEvent, Direction> _mapDirection;
    static const std::map<char, IEntity::entitiesType> _defaultMapConverter;
};

extern "C"
{
    IGame *newInstance(void);
}

#endif /* ANIBBLER_HPP_ */
