/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: SFML.cpp
*/

#include "../include/SFML.hpp"
#include "../../../include/Entity.hpp"
#include "../../../include/ArcadeException.hpp"
#include <iostream>

Sfml::Sfml(void) : _config(FileReader(".SFMLConfig.txt"))
{
    _win = nullptr;
    _font.loadFromFile("ressources/fonts/Arcade.ttf");
    _time = sf::seconds(0.2);
    fillEntitiesMap();
    if (!_config.find("game").empty())
        _game = _config.find("game")[0];
}

Sfml::~Sfml(void)
{
}

const std::map<std::pair<int, int>, IGraph::graphEvent> Sfml::_eventMap {
    {{sf::Keyboard::Key::Q, KeyState::NOTHING}, IGraph::EXIT},
    {{sf::Keyboard::Key::Escape, KeyState::NOTHING}, IGraph::EXIT},
    {{sf::Keyboard::Key::P, KeyState::MAJ}, IGraph::PREV_GAME},
    {{sf::Keyboard::Key::N, KeyState::MAJ}, IGraph::NEXT_GAME},
    {{sf::Keyboard::Key::P, KeyState::NOTHING}, IGraph::PREV_GRAPH},
    {{sf::Keyboard::Key::N, KeyState::NOTHING}, IGraph::NEXT_GRAPH},
    {{sf::Keyboard::Key::M, KeyState::NOTHING}, IGraph::BACK_TO_MENU},
    {{sf::Keyboard::Key::Space, KeyState::NOTHING}, IGraph::SPACE},
    {{sf::Keyboard::Key::Return, KeyState::NOTHING}, IGraph::ENTER},
    {{sf::Keyboard::Key::P, KeyState::CTRL}, IGraph::PREV_GRAPH},
    {{sf::Keyboard::Key::N, KeyState::CTRL}, IGraph::NEXT_GRAPH},
    {{sf::Keyboard::Key::Left, KeyState::NOTHING}, IGraph::LEFT},
    {{sf::Keyboard::Key::Right, KeyState::NOTHING}, IGraph::RIGHT},
    {{sf::Keyboard::Key::Up, KeyState::NOTHING}, IGraph::UP},
    {{sf::Keyboard::Key::Down, KeyState::NOTHING}, IGraph::DOWN}
};

void Sfml::displayWindow(const std::vector<IEntity *> &entities)
{
    if (!_win->isOpen())
        createWindow();
    checkIfNewEntity(entities);
    _config.reset();
    if (!_config.find("game").empty() && _config.find("game")[0] != _game) {
        _game = _config.find("game")[0];
        fillEntitiesMap();
        replaceSprites(entities);
    }
    checkText(entities);
    _win->clear(sf::Color::Black);
    drawEntity(entities);
    _win->display();
    if (_clock.getElapsedTime() >= _time)
        _clock.restart();
}

void Sfml::replaceSprites(const std::vector<IEntity *> &entities)
{
    std::string path = "";

    for (auto it : entities) {
        if (it->getType() != IEntity::WALL && it->getType() != IEntity::TEXT) {
            switch (it->getType()) {
            case IEntity::entitiesType::PLAYER:
                path = _entitiesMap[IEntity::PLAYER];
                break;
            case IEntity::entitiesType::ENEMY:
                path = _entitiesMap[IEntity::ENEMY];
                break;
            case IEntity::entitiesType::BONUS:
                path = _entitiesMap[IEntity::BONUS];
                break;
            case IEntity::entitiesType::ITEMS:
                path = _entitiesMap[IEntity::ITEMS];
                break;
            default:
                break;
            }
            sf::Texture txt;
            txt.loadFromFile(path);
            std::get<0>(_sprite[it]).setTexture(txt);
        }
    }
}

void Sfml::createWindow(void)
{
    sf::VideoMode mode(WIDTH, HEIGHT);

    _win = new sf::RenderWindow(mode, "Arcade", sf::Style::Resize | sf::Style::Close);
}

void Sfml::closeWindow(void)
{
    if (_win) {
        _win->close();
    }
}

void Sfml::checkText(const std::vector<IEntity *> &entities)
{
    for (auto it : entities) {
        if (it->getType() == IEntity::entitiesType::TEXT) {
            Text *objText = static_cast<Text *>(it);
            sf::Text text(objText->getText(), _font);
            text.setCharacterSize(25);
            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color::White);
            std::get<2>(_sprite[it]) = text;
        }
    }
}

void Sfml::checkIfNewEntity(const std::vector<IEntity *> &entities)
{
    if (_sprite.find(entities[entities.size() - 1]) == _sprite.end()) {
        for (size_t i = 0; i < entities.size(); i++) {
            try {
                addEntity(entities[i]);
            }
            catch (ArcadeException &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void Sfml::addEntity(IEntity *entity)
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Rect<int> rect = {0, 0, 0, 0};
    static int i = 0;

    switch (entity->getType()) {
        case IEntity::entitiesType::TEXT: {
            Text objText = *(static_cast<Text *>(entity));
            sf::Text text(objText.getText(), _font);
            text.setCharacterSize(25);
            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color::White);
            std::get<2>(_sprite[entity]) = text;
            break;
        }
        case IEntity::entitiesType::WALL: {
            sf::RectangleShape rectangle(sf::Vector2f(25.f, 25.f));
            rectangle.setFillColor(sf::Color::Blue);
            std::get<3>(_sprite[entity]) = rectangle;
            break;
        }
        case IEntity::entitiesType::PLAYER: {
            texture.loadFromFile(_entitiesMap[IEntity::PLAYER]);
            std::get<4>(_sprite[entity]) = texture;
            sprite.setTexture(texture);
            rect.width = 25;
            rect.height = 25;
            sprite.setTextureRect(rect);
            break;
        }
        case IEntity::entitiesType::ENEMY: {
            texture.loadFromFile(_entitiesMap[IEntity::ENEMY]);
            std::get<4>(_sprite[entity]) = texture;
            sprite.setTexture(texture);
            rect.top = i * 25;
            if (i < 3)
                i++;
            rect.width = 25;
            rect.height = 25;
            sprite.setTextureRect(rect);
            break;
        }
        case IEntity::entitiesType::BONUS: {
            texture.loadFromFile(_entitiesMap[IEntity::BONUS]);
            std::get<4>(_sprite[entity]) = texture;
            sprite.setTexture(texture);
            rect.width = 25;
            rect.height = 25;
            sprite.setTextureRect(rect);
            break;
        }
        case IEntity::entitiesType::ITEMS: {
            texture.loadFromFile(_entitiesMap[IEntity::ITEMS]);
            std::get<4>(_sprite[entity]) = texture;
            sprite.setTexture(texture);
            rect.width = 25;
            rect.height = 25;
            sprite.setTextureRect(rect);
            break;
        }
        default: {
            sf::RectangleShape rectangle(sf::Vector2f(25.f, 25.f));
            rectangle.setFillColor(sf::Color::White);
            std::get<3>(_sprite[entity]) = rectangle;
            break;
        }
    }
    std::get<0>(_sprite[entity]) = sprite;
    std::get<1>(_sprite[entity]) = rect;
}

float Sfml::getRealPosition(const float &size, const int &border) const
{
    int scale = 1;

    switch (border) {
    case 1:
        scale = WSIZE;
        break;
    case 2:
        scale = HSIZE;
        break;
    default:
        break;
    }
    return (size * scale);
}

void Sfml::drawEntity(const std::vector<IEntity *> &entity)
{
    for (auto it : entity) {
        if (it->getType() == IEntity::entitiesType::TEXT) {
            std::get<2>(_sprite[it]).setPosition(WIDTH / 2 - std::get<2>(_sprite[it]).getLocalBounds().width / 2, getRealPosition(it->getPosY(), 2));
            _win->draw(std::get<2>(_sprite[it]));
        } else if (it->getType() == IEntity::entitiesType::WALL){
            std::get<3>(_sprite[it]).setPosition(getRealPosition(it->getPosX(), 1), getRealPosition(it->getPosY(), 2));
            _win->draw(std::get<3>(_sprite[it]));
        } else {
            std::get<0>(_sprite[it]).setPosition(getRealPosition(it->getPosX(), 1), getRealPosition(it->getPosY(), 2));
            std::get<0>(_sprite[it]).setTexture(std::get<4>(_sprite[it]));
            if ((it->getType() == IEntity::entitiesType::PLAYER || it->getType() == IEntity::entitiesType::ENEMY) && _clock.getElapsedTime() >= _time)
                computeAnimSprite(it);
            _win->draw(std::get<0>(_sprite[it]));
        }
    }
}

void Sfml::computeAnimSprite(IEntity *entity)
{
    unsigned int newTick = std::get<1>(_sprite[entity]).left + std::get<1>(_sprite[entity]).width;
    if (newTick < std::get<0>(_sprite[entity]).getTexture()->getSize().x)
        std::get<1>(_sprite[entity]).left += std::get<1>(_sprite[entity]).width;
    else
        std::get<1>(_sprite[entity]).left = 0;
    if (entity->getType() == IEntity::entitiesType::PLAYER) {
        switch (entity->getNbType()) {
        case 0:
            std::get<1>(_sprite[entity]).top = 2 * std::get<1>(_sprite[entity]).height;
            break;
        case 1:
            std::get<1>(_sprite[entity]).top = 0 * std::get<1>(_sprite[entity]).height;
            break;
        case 2:
            std::get<1>(_sprite[entity]).top = 1 * std::get<1>(_sprite[entity]).height;
            break;
        case 3:
            std::get<1>(_sprite[entity]).top = 3 * std::get<1>(_sprite[entity]).height;
            break;
        case 4:
            std::get<1>(_sprite[entity]).top = 4 * std::get<1>(_sprite[entity]).height;
            break;
        }
    }
    if (entity->getType() == IEntity::entitiesType::ENEMY) {
        switch (entity->getNbType()) {
        case 0:
            std::get<1>(_sprite[entity]).top = 2 * std::get<1>(_sprite[entity]).height;
            break;
        case 1:
            std::get<1>(_sprite[entity]).top = 0 * std::get<1>(_sprite[entity]).height;
            break;
        case 2:
            std::get<1>(_sprite[entity]).top = 1 * std::get<1>(_sprite[entity]).height;
            break;
        case 3:
            std::get<1>(_sprite[entity]).top = 3 * std::get<1>(_sprite[entity]).height;
            break;
        case 4:
            std::get<1>(_sprite[entity]).top = 4 * std::get<1>(_sprite[entity]).height;
            break;
        }
    }
    std::get<0>(_sprite[entity]).setTextureRect(std::get<1>(_sprite[entity]));
}

int Sfml::checkControl(void) const
{
    int state = KeyState::NOTHING;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        state = KeyState::CTRL;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        state = KeyState::MAJ;
    return state;
}

IGraph::graphEvent Sfml::getEvent(void) const noexcept
{
    graphEvent result = graphEvent::NOTHING;
    sf::Event event;
    static bool begin = true;

    while (_win->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            result = graphEvent::EXIT;
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && begin) {
            begin = false;
            return result;
        }
        if (event.type == sf::Event::KeyPressed && !begin) {
            std::pair<int, int> control = {event.key.code, checkControl()};
            result = _eventMap.find(control)->second;
        }
    }
    return result;
}

std::string Sfml::fillEntityMap(const std::string &section) noexcept
{
    std::string path = "lib/SFML/sprites/pacman/player.bmp";
    std::vector<std::string> v;

    try {
        v = _config.find(section);
        try {
            if (!v.empty())
                path = v[0];
        } catch (...) {}
    } catch (const FileReaderException &error) {
        std::cerr << error.what() << std::endl;
    }
    return path;
}

void Sfml::fillEntitiesMap(void) noexcept
{
    _entitiesMap.clear();
    _entitiesMap[IEntity::PLAYER] = fillEntityMap("Player");
    _entitiesMap[IEntity::ENEMY] = fillEntityMap("Enemy");
    _entitiesMap[IEntity::ITEMS] = fillEntityMap("Items");
    _entitiesMap[IEntity::BONUS] = fillEntityMap("Bonus");
}


extern "C"
{
    IGraph *newInstance(void)
    {
        return new Sfml;
    }
}
