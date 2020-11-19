/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: APacman.cpp
*/

#include "APacman.hpp"
#include "ArcadeUtils.hpp"
#include "Entity.hpp"
#include <math.h>
#include <algorithm>

const std::map<char, IEntity::entitiesType> APacman::_defaultMapConverter {
    {'#', IEntity::WALL},
    {'o', IEntity::BONUS},
    {'.', IEntity::ITEMS},
    {'P', IEntity::PLAYER},
    {'E', IEntity::ENEMY}
};

const std::map<IGame::gameEvent, IPacman::Direction> APacman::_mapDirection {
    {IGame::DOWN, IPacman::Direction::DOWN},
    {IGame::UP, IPacman::Direction::UP},
    {IGame::LEFT, IPacman::Direction::LEFT},
    {IGame::RIGHT, IPacman::Direction::RIGHT}
};

const std::map<IPacman::Direction, std::pair<int , int>> APacman::_mapMove {
    {IPacman::Direction::DOWN, {0, 1}},
    {IPacman::Direction::UP, {0, -1}},
    {IPacman::Direction::LEFT, {-1, 0}},
    {IPacman::Direction::RIGHT, {1, 0}}
};

const std::map<IPacman::Direction, IPacman::Direction> APacman::_reversedDirection {
    {LEFT, RIGHT},
    {RIGHT, LEFT},
    {UP, DOWN},
    {DOWN, UP}
};

APacman::APacman(const size_t &nbLife, const std::string &mapPath,
    const std::map<char, IEntity::entitiesType> &mapConverter) :
    _mapPath(mapPath), _map(ArcadeUtils::getMap(mapPath)),
    _top((40 - _map.size()) / 2), _left((80 - _map[0].size()) / 2),
    _nbLife(nbLife), _clock(0), _spawnEnemy({-1, 5, 10, 15}), _lastBonus(0),
    _player(nullptr), _playerDirection(IPacman::Direction::RIGHT),
    _score(0), _scoreEntity(new Text(_left + _map[0].size() / 2, _top - 1, "Score: 0")),
    _mapConverter(mapConverter), _nbItems(0)
{
    for (auto it : _mapConverter)
        _mapConverterRev[it.second] = it.first;
    if (_mapConverterRev.find(IEntity::WALL) == _mapConverterRev.end() ||
        _mapConverterRev.find(IEntity::PLAYER) == _mapConverterRev.end() ||
        _mapConverterRev.find(IEntity::ITEMS) == _mapConverterRev.end() ||
        _mapConverterRev.find(IEntity::BONUS) == _mapConverterRev.end() ||
        _mapConverterRev.find(IEntity::ENEMY) == _mapConverterRev.end())
        throw ArcadeException("Map converter is missing some converting entity type");
    _life = new Text(_left + _map[0].size() / 2, _top + _map.size(), "Life: " + std::to_string(_nbLife));
    _entities.push_back(_life);
    _state = IGame::gameState::RUNNING;
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            auto it = mapConverter.find(_map[y][x]);
            if (it != mapConverter.end()) {
                auto entity = new Entity(_left + x, _top + y, it->second);
                switch (static_cast<int>(entity->getType())) {
                case IEntity::PLAYER:
                    if (_player)
                        throw ArcadeException("Invalid game map");
                    _player = entity;
                    _player->setNbType(_playerDirection);
                    _playerSpawn = {entity->getPosX(), entity->getPosY()};
                    break;
                case IEntity::ENEMY:
                    _enemy.push_back(entity);
                    entity->setNbType(_enemy.size() - 1);
                    _enemySpawns.push_back({entity->getPosX(), entity->getPosY()});
                    _enemyDirections.push_back(UP);
                    break;
                case IEntity::ITEMS:
                    _entities.push_back(entity);
                    _nbItems++;
                    break;
                case IEntity::BONUS:
                    _entities.push_back(entity);
                    _nbItems++;
                    break;
                default:
                    _entities.push_back(entity);
                    break;
                }
            }
        }
    }
    for (IEntity *it : _enemy)
        _entities.push_back(it);
    if (!_player)
        throw ArcadeException("Pacman: map have no player");
    if (_enemy.size() != 4)
        throw ArcadeException("Pacman: map haven't exactly 4 enemies");
    _entities.push_back(_player);
    _entities.push_back(_scoreEntity);
}

void APacman::resetGame(void) noexcept
{
    _spawnEnemy = {-1, 5, 10, 15};
    for (size_t i = 0; i < _enemy.size(); i++) {
        _enemy[i]->setPosX(_enemySpawns[i].first);
        _enemy[i]->setPosY(_enemySpawns[i].second);
    }
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            auto it = _mapConverter.find(_map[y][x]);
            if (it != _mapConverter.end() &&
                (it->second == IEntity::BONUS || it->second == IEntity::ITEMS)) {
                _entities.push_back(new Entity(_left + x, _top + y, it->second));
                _nbItems++;
            }
        }
    }
    _player->setPosX(_playerSpawn.first);
    _player->setPosY(_playerSpawn.second);
    _clock = 0;
}

void APacman::nextCycle(const gameEvent &event) noexcept
{
    if (_nbItems == 0)
        resetGame();
    if (_state == IGame::gameState::RUNNING) {
        playerMovement(_player, event);
        for (size_t i = 0; i < _enemy.size(); i++)
            enemyMovement(_enemy[i], _enemyDirections[i]);
        for (size_t i = 0; i < _spawnEnemy.size(); i++) {
            if (_spawnEnemy[i] != -1 && _clock > _spawnEnemy[i]) {
                _spawnEnemy[i] = -1;
                _enemy[i]->setPosX(_enemySpawns[0].first);
                _enemy[i]->setPosY(_enemySpawns[0].second);
            }
        }
        for (size_t i = 0; i < _entities.size();) {
            if (_entities[i]->getType() != IEntity::WALL &&
                std::round(_entities[i]->getPosX()) == _player->getPosX() &&
                std::round(_entities[i]->getPosY()) == _player->getPosY())
                manageCollision(_entities[i], i);
            else
                i++;
        }
        if (_clock >= _lastBonus)
            for (size_t i = 0; i < _enemy.size(); i++)
                _enemy[i]->setNbType(i);
        _clock += 1/30.0;
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

void APacman::manageCollision(IEntity *entity, size_t &index) noexcept
{
    switch (entity->getType()) {
    case IEntity::ITEMS:
        _score += 10;
        _scoreEntity->setText("Score: " + std::to_string(_score));
        _entities.erase(_entities.begin() + index);
        _nbItems--;
        break;
    case IEntity::BONUS:
        _entities.erase(_entities.begin() + index);
        _lastBonus = _clock + 5;
        for (auto it : _enemy)
            it->setNbType(4);
        _nbItems--;
        break;
    case IEntity::ENEMY:
        if (_clock < _lastBonus) {
            int pos = std::find(_enemy.begin(), _enemy.end(), entity) - _enemy.begin();
            entity->setPosX(_enemySpawns[pos ? pos : 1].first);
            entity->setPosY(_enemySpawns[pos ? pos : 1].second);
            _spawnEnemy[pos] = _clock + 3;
            _score += 100;
            _scoreEntity->setText("Score: " + std::to_string(_score));
        } else {
            _nbLife--;
            _clock = 0;
            _spawnEnemy = {-1, 5, 10, 15};
            _life->setText("Life: " + std::to_string(_nbLife));
            for (size_t i = 0; i < _enemy.size(); i++) {
                _enemy[i]->setPosX(_enemySpawns[i].first);
                _enemy[i]->setPosY(_enemySpawns[i].second);
            }
            _player->setPosX(_playerSpawn.first);
            _player->setPosY(_playerSpawn.second);
        }
        index++;
        break;
    default:
        index++;
        break;
    }
}

void APacman::playerMovement(IEntity *entity, const gameEvent &event) noexcept
{
    int x = static_cast<int>(entity->getPosX()) - _left;
    int y = static_cast<int>(entity->getPosY()) - _top;

    _playerDirection = ArcadeUtils::getConvertedEvent(_mapDirection, event, _playerDirection);
    if (static_cast<int>(entity->getPosX()) == entity->getPosX() &&
        static_cast<int>(entity->getPosY()) == entity->getPosY() &&
        _playerDirection != _player->getNbType()) {
        auto p = _mapMove.find(_playerDirection);
        if (moveTo(x + p->second.first, y + p->second.second))
            entity->setNbType(_playerDirection);
    }
    entityMovement(entity, static_cast<Direction>(_player->getNbType()));
}

void APacman::enemyMovement(IEntity *entity, Direction &direction) noexcept
{
    if (static_cast<int>(entity->getPosX()) == entity->getPosX() &&
        static_cast<int>(entity->getPosY()) == entity->getPosY()) {
        int x = static_cast<int>(entity->getPosX()) - _left;
        int y = static_cast<int>(entity->getPosY()) - _top;
        std::vector<Direction> possible;
        for (auto it : _mapMove)
            if (moveTo(x + it.second.first, y + it.second.second))
                possible.push_back(it.first);
        if (possible.size() == 1)
            direction = possible[0];
        else if (possible.size() > 1) {
            auto it = std::find(possible.begin(), possible.end(), _reversedDirection.find(direction)->second);
            if (it != possible.end())
                possible.erase(it);
            direction = possible[std::rand() % possible.size()];
        }
    }
    entityMovement(entity, direction);
}

void APacman::entityMovement(IEntity *entity, const Direction &direction) const noexcept
{
    int x = static_cast<int>(entity->getPosX()) - _left;
    int y = static_cast<int>(entity->getPosY()) - _top;
    float speed = 0.1;

    auto p = _mapMove.find(direction);
    switch (static_cast<int>(direction)) {
    case Direction::LEFT:
        if (static_cast<int>(entity->getPosX()) == entity->getPosX())
            x += p->second.first;
        break;
    case Direction::RIGHT:
        x += p->second.first;
        break;
    case Direction::UP:
        if (static_cast<int>(entity->getPosY()) == entity->getPosY())
            y += p->second.second;
        break;
    case Direction::DOWN:
        y += p->second.second;
        break;
    }
    if (moveTo(x, y)) {
        switch (isOutOfBounds(x, y)) {
        case 1:
            entity->setPosX(_map[y].size() - 1 + _left);
            break;
        case 2:
            entity->setPosY(_top - (_map.size() - 1));
            break;
        case 3:
            entity->setPosY(_top);
            break;
        case 4:
            entity->setPosX(_left);
            break;
        default:
            entity->setPosX(entity->getPosX() + (p->second.first * speed));
            entity->setPosY(entity->getPosY() + (p->second.second * speed));
            break;
        }
        if (ArcadeUtils::compareFloat(entity->getPosX(), std::round(entity->getPosX()), 0.009))
            entity->setPosX(std::round(entity->getPosX()));
        if (ArcadeUtils::compareFloat(entity->getPosY(), std::round(entity->getPosY()), 0.009))
            entity->setPosY(std::round(entity->getPosY()));
    }
}

bool APacman::isWall(int x, int y) const noexcept
{
    if (isOutOfBounds(x, y))
        return false;
    auto val = ArcadeUtils::getConvertedEvent(_mapConverter,
                                              _map[y][x], IEntity::entitiesType::BONUS);
    return val == IEntity::entitiesType::WALL;
}

bool APacman::moveTo(int x, int y) const noexcept
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


int APacman::isOutOfBounds(int x, int y) const noexcept
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
