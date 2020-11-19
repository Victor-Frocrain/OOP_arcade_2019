/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Nibbler.cpp
*/

#include "../include/ANibbler.hpp"
#include "../../../include/Entity.hpp"
#include "../../../include/ArcadeUtils.hpp"
#include <math.h>

const std::map<char, IEntity::entitiesType> ANibbler::_defaultMapConverter {
    {'#', IEntity::WALL},
    {'P', IEntity::PLAYER}
};

const std::map<IGame::gameEvent, INibbler::Direction> ANibbler::_mapDirection {
    {IGame::DOWN, INibbler::Direction::DOWN},
    {IGame::UP, INibbler::Direction::UP},
    {IGame::LEFT, INibbler::Direction::LEFT},
    {IGame::RIGHT, INibbler::Direction::RIGHT}
};

const std::map<INibbler::Direction, std::pair<int , int>> ANibbler::_mapMove {
    {INibbler::Direction::DOWN, {0, 1}},
    {INibbler::Direction::UP, {0, -1}},
    {INibbler::Direction::LEFT, {-1, 0}},
    {INibbler::Direction::RIGHT, {1, 0}}
};

ANibbler::ANibbler(const size_t &nbLife, const std::string &mapPath,
    const std::map<char, IEntity::entitiesType> &mapConverter) :
    _mapPath(mapPath), _map(ArcadeUtils::getMap(mapPath)),
    _top((40 - _map.size()) / 2), _left((80 - _map[0].size()) / 2), _nbLife(nbLife),
    _playerDirection(INibbler::Direction::RIGHT),
    _score(0), _scoreEntity(new Text(_left + _map[0].size() / 2, _top - 1, "Score: 0")),
    _mapConverter(mapConverter), haveFood(false), _clock(std::chrono::system_clock::now()), _newScore(false),
    _newName("")
{
    std::srand(std::time(nullptr));
    for (auto it : _mapConverter)
        _mapConverterRev[it.second] = it.first;
    if (_mapConverterRev.find(IEntity::WALL) == _mapConverterRev.end() ||
        _mapConverterRev.find(IEntity::PLAYER) == _mapConverterRev.end())
        throw ArcadeException("Map converter is missing some converting entity type");
    _life = new Text(_left + _map[0].size() / 2, _top + _map.size(), "Life: " + std::to_string(_nbLife));
    _entities.push_back(_life);
    _state = IGame::gameState::RUNNING;
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = _map[y].size() - 1; x < _map[y].size(); x--) {
            auto it = mapConverter.find(_map[y][x]);
            if (it != mapConverter.end()) {
                auto entity = new Entity(_left + x, _top + y, it->second);
                switch (static_cast<int>(entity->getType())) {
                case IEntity::PLAYER:
                    entity->setNbType(_playerDirection);
                    if (_player.empty()) {
                        entity->setPosX(entity->getPosX() - 0.9);
                        _player.push_back(entity);
                    }
                    else {
                        for (size_t i = 0; i < 10; i++) {
                            auto ent = new Entity(_left + x, _top + y, it->second, 4);
                            ent->setPosX(ent->getPosX() - 0.1 * i);
                            _player.push_back(ent);
                        }
                    }
                    break;
                default:
                    _entities.push_back(entity);
                    break;
                }
            }
        }
    }
    if (_player.empty())
        throw ArcadeException("Nibbler: map have no player");
    for (size_t i = 0; i < _player.size(); i++) {
        _entities.push_back(_player[i]);
    }
    _entities.push_back(_scoreEntity);
}

void ANibbler::generateItem()
{
    float posX = 0;
    float posY = 0;

    if (!haveFood) {
        posX = std::rand() % (_map[0].size() - 2);
        posY = std::rand() % (_map.size() - 2);
        auto food = new Entity(_left + posX + 1, _top + posY + 1, IEntity::BONUS);
        _entities.push_back(food);
        haveFood = true;
    }
}

void ANibbler::addCorpse()
{
    float posX = 0;
    float posY = 0;
    float diffX = 0;
    float diffY = 0;

    for (size_t i = 0; i < 10; i++) {
        posX = _player[_player.size() - 1]->getPosX();
        posY = _player[_player.size() - 1]->getPosY();
        diffX = _player[_player.size() - 1]->getPosX() - _player[_player.size() - 2]->getPosX();
        diffY = _player[_player.size() - 1]->getPosY() - _player[_player.size() - 2]->getPosY();
        auto entity = new Entity(posX + diffX, posY + diffY, Entity::PLAYER, 4);
        _player.push_back(entity);
        _entities.push_back(entity);
    }
}

void ANibbler::nextCycle(const gameEvent &event) noexcept
{
    if (_state == IGame::gameState::RUNNING) {
        generateItem();
        _playerDirection = ArcadeUtils::getConvertedEvent(_mapDirection, event, _playerDirection);
        playerMovement(_player[0], _playerDirection);
        for (size_t i = 0; i < _entities.size();) {
            switch (_entities[i]->getType()) {
            /*case IEntity::ITEMS:
                if (std::round(_entities[i]->getPosX()) == _player[0]->getPosX() &&
                    std::round(_entities[i]->getPosY()) == _player[0]->getPosY()) {
                    _score += 10;
                    _scoreEntity->setText("Score: " + std::to_string(_score));
                    _entities.erase(_entities.begin() + i);
                } else
                    i++;
                break;*/
            case IEntity::BONUS:
                if (std::round(_entities[i]->getPosX()) == _player[0]->getPosX() &&
                    std::round(_entities[i]->getPosY()) == _player[0]->getPosY()) {
                    _entities.erase(_entities.begin() + i);
                    _score += 10;
                    _scoreEntity->setText("Score: " + std::to_string(_score));
                addCorpse();
                    haveFood = false;
                } else
                    i++;
                break;
            /*case IEntity::WALL:
                if ((_entities[i]->getPosX()) == _player[0]->getPosX() &&
                    (_entities[i]->getPosY() + 0.9) == _player[0]->getPosY()) {
                    _nbLife--;
                    _life->setText("Life: " + std::to_string(_nbLife));
                }
                i++;
                break;*/
            default:
                i++;
                break;
            }
        }
    }
    if (_nbLife == 0 && _state != IGame::gameState::END) {
        _state = IGame::gameState::END;
        if (!_entities.empty()) {
            _entities.erase(_entities.begin(), _entities.end());
        }
        readBestScores();
    }
    if (_state == IGame::gameState::END) {
        if (_newScore) {
            _playerDirection = STAND;
            _playerDirection = ArcadeUtils::getConvertedEvent(_mapDirection, event, _playerDirection);
            enterName();
        }
        else {
            addScoresList();
        }
    }
}

void ANibbler::playerMovement(IEntity *entity, const INibbler::Direction &direction) noexcept
{
    static int lastTime = 0;
    int newTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _clock).count();
    int x = static_cast<int>(entity->getPosX()) - _left;
    int y = static_cast<int>(entity->getPosY()) - _top;
    float speed = 0.1;

    if (static_cast<int>(entity->getPosX()) == entity->getPosX() &&
        static_cast<int>(entity->getPosY()) == entity->getPosY() &&
        _playerDirection != _player[0]->getNbType()) {
        auto p = _mapMove.find(direction);
        if (moveTo(x + p->second.first, y + p->second.second))
            entity->setNbType(direction);
    }
    auto p = _mapMove.find(static_cast<Direction>(_player[0]->getNbType()));
    switch (_player[0]->getNbType()) {
    case Direction::LEFT:
        if (static_cast<int>(_player[0]->getPosX()) == _player[0]->getPosX())
            x += p->second.first;
        break;
    case Direction::RIGHT:
        x += p->second.first;
        break;
    case Direction::UP:
        if (static_cast<int>(_player[0]->getPosY()) == _player[0]->getPosY())
            y += p->second.second;
        break;
    case Direction::DOWN:
        y += p->second.second;
        break;
    }
    float beforeMoveX = _player[0]->getPosX();
    float beforeMoveY = _player[0]->getPosY();
    if (moveTo(x, y)) {
        switch (isOutOfBounds(x, y)) {
        case 1:
            _player[0]->setPosX(_map[y].size() - 1 + _left);
            break;
        case 2:
            _player[0]->setPosY(_top - (_map.size() - 1));
            break;
        case 3:
            _player[0]->setPosY(_top);
            break;
        case 4:
            _player[0]->setPosX(_left);
            break;
        default:
            _player[0]->setPosX(_player[0]->getPosX() + (p->second.first * speed));
            _player[0]->setPosY(_player[0]->getPosY() + (p->second.second * speed));
            break;
        }
        if (ArcadeUtils::compareFloat(_player[0]->getPosX(), std::round(_player[0]->getPosX()), 0.09))
            _player[0]->setPosX(std::round(_player[0]->getPosX()));
        if (ArcadeUtils::compareFloat(_player[0]->getPosY(), std::round(_player[0]->getPosY()), 0.09))
            _player[0]->setPosY(std::round(_player[0]->getPosY()));
    }
    else if (_nbLife > 0 && newTime >= lastTime + 1000) {
        _nbLife--;
        _life->setText("Life: " + std::to_string(_nbLife));
        lastTime = newTime;
    }
    if (_nbLife > 0 && eatQueue() && newTime >= lastTime + 1000) {
        _nbLife--;
        _life->setText("Life: " + std::to_string(_nbLife));
        lastTime = newTime;
    }
    moveQueue(beforeMoveX, beforeMoveY);
}

void ANibbler::moveQueue(float speedX, float speedY)
{
    float beforeMoveX = 0;
    float beforeMoveY = 0;

    for (size_t i = 1; i < _player.size(); i++) {
        beforeMoveX = _player[i]->getPosX();
        beforeMoveY = _player[i]->getPosY();
        _player[i]->setPosX(speedX);
        _player[i]->setPosY(speedY);
        speedX = beforeMoveX;
        speedY = beforeMoveY;
    }
}

bool ANibbler::eatQueue() const
{
    for (size_t i = 1; i < _player.size(); i++) {
        if (_player[0]->getPosX() == _player[i]->getPosX() &&
            _player[0]->getPosY() == _player[i]->getPosY()) {
                return true;
            }
    }
    return false;
}

bool ANibbler::isWall(int x, int y) const noexcept
{
    if (isOutOfBounds(x, y)) {
        return false;
    }
    auto val = ArcadeUtils::getConvertedEvent(_mapConverter,
                                              _map[y][x], IEntity::entitiesType::BONUS);
    return val == IEntity::entitiesType::WALL;// || IEntity::entitiesType::PLAYER;
}

bool ANibbler::moveTo(int x, int y) const noexcept
{
    if (isWall(x, y))
        return false;
    switch (isOutOfBounds(x, y)) {
    case 1:
        return !isWall(_map[y].size() - 1, y);
        break;
    case 2:
        return !isWall(x, _map.size() - 1);
        break;
    case 3:
        return !isWall(0, y);
        break;
    case 4:
        return !isWall(x, 0);
        break;
    }
    return true;
}


int ANibbler::isOutOfBounds(int x, int y) const noexcept
{
    if (x < 0)
        return 1;
    else if (y < 0)
        return 2;
    else if (static_cast<size_t>(y) >= _map.size())
        return 3;
    else if (static_cast<size_t>(x) >= _map[y].size())
        return 4;
    return 0;
}
