/*
** EPITECH PROJECT, 2020
** SDL
** File description:
** SDL.cpp
*/

#include "../include/SDL.hpp"
#include "../../../include/ArcadeException.hpp"
#include "../../../include/Entity.hpp"
#include <iostream>
#include <math.h>

SDL::SDL() : _config(FileReader(".SDLConfig.txt"))
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw ArcadeException("The SDL could not be initialized.");
    }
    _isInit = true;
    if (TTF_Init() < 0) {
        throw ArcadeException("The TTF could not be initialized.");
    }
    _font = TTF_OpenFont("ressources/fonts/Arcade.ttf", 30);
    if (_font == NULL) {
        throw ArcadeException("The font can not be loaded : file not found.");
    }
    _win = nullptr;
    _blackScreen = nullptr;
    fillEntitiesMap();
    if (!_config.find("game").empty())
        _game = _config.find("game")[0];
}

SDL::~SDL()
{
    std::map<IEntity *, std::tuple<SDL_Surface *, SDL_Rect, std::string>>::iterator it = _surfaces.begin();

    for (; it != _surfaces.end(); it++) {
        SDL_FreeSurface(std::get<0>(it->second));
    }
    _surfaces.clear();
    if (_font) {
        TTF_CloseFont(_font);
        TTF_Quit();
    }

}

const std::map<std::pair<int, int>, IGraph::graphEvent> SDL::_eventMap {
    { {SDLK_q, KeyState::NOTHING}, IGraph::EXIT},
    { {SDLK_ESCAPE, KeyState::NOTHING}, IGraph::EXIT},
    { {SDLK_p, KeyState::MAJ}, IGraph::PREV_GAME},
    { {SDLK_n, KeyState::MAJ}, IGraph::NEXT_GAME},
    { {SDLK_p, KeyState::NOTHING}, IGraph::PREV_GRAPH},
    { {SDLK_n, KeyState::NOTHING}, IGraph::NEXT_GRAPH},
    { {SDLK_m, KeyState::NOTHING}, IGraph::BACK_TO_MENU},
    { {SDLK_SPACE, KeyState::NOTHING}, IGraph::SPACE},
    { {SDLK_RETURN, KeyState::NOTHING}, IGraph::ENTER},
    { {SDLK_p, KeyState::CTRL}, IGraph::PREV_GRAPH},
    { {SDLK_n, KeyState::CTRL}, IGraph::NEXT_GRAPH},
    { {SDLK_LEFT, KeyState::NOTHING}, IGraph::LEFT},
    { {SDLK_RIGHT, KeyState::NOTHING}, IGraph::RIGHT},
    { {SDLK_UP, KeyState::NOTHING}, IGraph::UP},
    { {SDLK_DOWN, KeyState::NOTHING}, IGraph::DOWN}
};

std::string SDL::fillEntityMap(const std::string &section) noexcept
{
    std::string path = "lib/SDL/sprites/pacman/player.bmp";
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

void SDL::fillEntitiesMap(void) noexcept
{
    _entitiesMap.clear();
    _entitiesMap[IEntity::PLAYER] = fillEntityMap("Player");
    _entitiesMap[IEntity::ENEMY] = fillEntityMap("Enemy");
    _entitiesMap[IEntity::ITEMS] = fillEntityMap("Items");
    _entitiesMap[IEntity::BONUS] = fillEntityMap("Bonus");
}

const std::map<short, int> SDL::_playerState {
    {0, 2},
    {1, 0},
    {2, 1},
    {3, 3},
    {4, 4}
};

const std::map<short, int> SDL::_enemyType {
    {0, 0},
    {1, 1},
    {2, 2},
    {3, 3},
    {4, 4}
};

int SDL::checkSize(const int &border) const
{
    int width = WIDTH;
    int height = HEIGHT;

    SDL_GetWindowSize(_win, &width, &height);
    switch (border) {
    case 1:
        return width;
    case 2:
        return height;
    default:
        break;
    }
    return 0;
}

int SDL::computeRealSize(const int &size, const int &border) const
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
        return 0;
    }
    return (size * scale);
}

void SDL::computeRectSprite(IEntity *entity, const bool &animate)
{
    static bool way = true;

    if (animate) {
        if (std::get<1>(_surfaces[entity]).x + std::get<0>(_surfaces[entity])->w / 3 < std::get<0>(_surfaces[entity])->w && way) {
            std::get<1>(_surfaces[entity]).x += std::get<0>(_surfaces[entity])->w / 3;
        }
        else if (std::get<1>(_surfaces[entity]).x - std::get<0>(_surfaces[entity])->w / 3 >= 0) {
            std::get<1>(_surfaces[entity]).x -= std::get<0>(_surfaces[entity])->w / 3;
        }
        if (std::get<1>(_surfaces[entity]).x == 0) {
            way = true;
        }
        else if (std::get<1>(_surfaces[entity]).x + std::get<0>(_surfaces[entity])->w / 3 >= std::get<0>(_surfaces[entity])->w) {
            way = false;
        }
    }
    if (entity->getType() == IEntity::entitiesType::PLAYER) {
        std::get<1>(_surfaces[entity]).y = (std::get<0>(_surfaces[entity])->h / 5) * _playerState.find(entity->getNbType())->second;
    }
    else if (entity->getType() == IEntity::entitiesType::ENEMY)
        std::get<1>(_surfaces[entity]).y = (std::get<0>(_surfaces[entity])->h / 5) * _enemyType.find(entity->getNbType())->second;
    std::get<1>(_surfaces[entity]).h = std::get<0>(_surfaces[entity])->h / 5 - 1;
    std::get<1>(_surfaces[entity]).w = std::get<0>(_surfaces[entity])->w / 3;
}

int SDL::takeAfterDot(const double &nb) const
{
    int result = 0;
    std::string str = std::to_string(nb);
    std::string res = "";
    size_t i = 0;

    for (; i < str.length() && str[i] != '.'; i++);
    i++;
    if (i < str.length()) {
        res += str[i];
    }
    result = std::stoi(res);
    return (result);
}

void SDL::drawEntities(const std::vector<IEntity *> &entities)
{
    static Uint32 lastTime = 0;
    static Uint32 time = 0;
    SDL_Rect destRect = {0, 0, 0, 0};
    bool animate = false;

    time = SDL_GetTicks();
    if (time >= lastTime + 300) {
        animate = true;
        lastTime = time;
    }
    for (size_t i = 0; i < entities.size(); i++) {
        destRect.x = computeRealSize((entities[i]->getPosX()), 1) + (std::round(takeAfterDot(entities[i]->getPosX()) * 2.4));
        destRect.y = computeRealSize((entities[i]->getPosY()), 2) + (std::round(takeAfterDot(entities[i]->getPosY()) * 2.4));
        destRect.w = SCALE;
        destRect.h = SCALE;
        if (entities[i]->getType() == IEntity::entitiesType::TEXT) {
            destRect.x -= std::get<1>(_surfaces[entities[i]]).w / 2;
        }
        if (entities[i]->getType() == IEntity::entitiesType::PLAYER || entities[i]->getType() == IEntity::entitiesType::ENEMY) {
            computeRectSprite(entities[i], animate);
        }
        if (entities[i]->getType() == IEntity::entitiesType::ITEMS || entities[i]->getType() == IEntity::entitiesType::BONUS) {
            std::get<1>(_surfaces[entities[i]]).h = SCALE;
            std::get<1>(_surfaces[entities[i]]).w = SCALE;
        }
        SDL_BlitSurface(std::get<0>(_surfaces[entities[i]]), &(std::get<1>(_surfaces[entities[i]])), SDL_GetWindowSurface(_win), &destRect);
    }
    SDL_RenderSetScale(SDL_GetRenderer(_win), checkSize(1), checkSize(2));
}

void SDL::checkTexts(const std::vector<IEntity *> &entities)
{
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i]->getType() == IEntity::entitiesType::TEXT) {
            Text text = *(static_cast<Text *>(entities[i]));
            std::string reader = text.getText();
            if (reader != std::get<2>(_surfaces[entities[i]]) && reader != "") {
                std::get<2>(_surfaces[entities[i]]) = reader;
                SDL_FreeSurface(std::get<0>(_surfaces[entities[i]]));
                std::get<0>(_surfaces[entities[i]]) = TTF_RenderText_Solid(_font, reader.c_str(), {255, 255, 255, 255});
                std::get<1>(_surfaces[entities[i]]).w = std::get<0>(_surfaces[entities[i]])->w;
                std::get<1>(_surfaces[entities[i]]).h = std::get<0>(_surfaces[entities[i]])->h;
            }
        }
    }
}

void SDL::addEntity(IEntity *entity)
{
    std::string path = "";
    SDL_Surface *s = nullptr;
    SDL_Rect rect = {0, 0, 0, 0};
    static int i = 0;

    switch (entity->getType()) {
        case IEntity::entitiesType::PLAYER: {
            path = _entitiesMap[IEntity::PLAYER];
            s = SDL_LoadBMP(path.c_str());
            break;
        }
        case IEntity::entitiesType::ENEMY: {
            path = _entitiesMap[IEntity::ENEMY];
            s = SDL_LoadBMP(path.c_str());
            break;
        }
        case IEntity::entitiesType::WALL: {
            s = SDL_CreateRGBSurface(0, computeRealSize(1, 1), computeRealSize(1, 2), 32, 0, 0, 0, 0);
            SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0, 0, 150));
            break;
        }
        case IEntity::entitiesType::ITEMS: {
            path = _entitiesMap[IEntity::ITEMS];
            s = SDL_LoadBMP(path.c_str());
            break;
        }
        case IEntity::entitiesType::BONUS: {
            path = _entitiesMap[IEntity::BONUS];
            s = SDL_LoadBMP(path.c_str());
            break;
        }
        case IEntity::entitiesType::TEXT: {
            Text text = *(static_cast<Text *>(entity));
            std::string reader = text.getText();
            std::get<2>(_surfaces[entity]) = reader;
            if (reader == "") {
                reader = " ";
            }
            s = TTF_RenderText_Solid(_font, reader.c_str(), {255, 255, 255, 255});
            break;
        }
        default: {
            s = SDL_CreateRGBSurface(0, computeRealSize(1, 1), computeRealSize(1, 2), 32, 0, 0, 0, 0);
            SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0, 0, 0));
            break;
        }
    }
    if (!s) {
        i++;
        throw ArcadeException("The surface can not be created: " + std::string(SDL_GetError()) + std::to_string(i));
    }
    std::get<0>(_surfaces[entity]) = s;
    rect.w = s->w;
    rect.h = s->h;
    std::get<1>(_surfaces[entity]) = rect;
}

void SDL::compareEntities(const std::vector<IEntity *> &entities)
{
    if (!std::get<0>(_surfaces[entities[entities.size() - 1]])) {
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

void SDL::displayWindow(const std::vector<IEntity *> &entities)
{
    if (!_isInit) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw ArcadeException("The SDL could not be initialized.");
        _isInit = true;
        if (!_win) {
            _win = SDL_CreateWindow("Arcade SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
            if (!_win) {
                throw ArcadeException("The SDL window could not be initialized.");
            }
        }
    }
    compareEntities(entities);
    _config.reset();
    if ((!_config.find("game").empty()) && _config.find("game")[0] != _game) {
        _game = _config.find("game")[0];
        fillEntitiesMap();
        replaceSprites(entities);
    }
    checkTexts(entities);
    drawEntities(entities);
    SDL_UpdateWindowSurface(_win);
    SDL_BlitSurface(_blackScreen, nullptr, SDL_GetWindowSurface(_win), nullptr);
    SDL_Delay(20);
}

void SDL::replaceSprites(const std::vector<IEntity *> &entities)
{
    std::string path = "";

    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i]->getType() != IEntity::WALL && entities[i]->getType() != IEntity::TEXT) {
            switch (entities[i]->getType())
            {
            case IEntity::entitiesType::PLAYER:
                path = _entitiesMap[IEntity::PLAYER];
                break;
            case IEntity::entitiesType::ENEMY:
                path = _entitiesMap[IEntity::ENEMY];
                break;
            case IEntity::entitiesType::ITEMS:
                path = _entitiesMap[IEntity::ITEMS];
                break;
            case IEntity::entitiesType::BONUS:
                path = _entitiesMap[IEntity::BONUS];
                break;
            default:
                break;
            }
            std::get<0>(_surfaces[entities[i]]) = SDL_LoadBMP(path.c_str());
        }
    }
}

void SDL::createWindow()
{
    if (!_win) {
        _win = SDL_CreateWindow("Arcade SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
        if (!_win) {
            throw ArcadeException("The SDL window could not be initialized.");
        }
    }
    if (!_blackScreen) {
        _blackScreen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 255);
        if (!_blackScreen) {
            throw ArcadeException("The SDL surface black screen could not be initialized.");
        }
    }
}

void SDL::closeWindow(void)
{
    SDL_VideoQuit();
    _isInit = false;
    if (_win) {
        SDL_DestroyWindow(_win);
        _win = nullptr;
    }
}

int SDL::checkKeyState(const SDL_Event &event) const
{
    int state = KeyState::NOTHING;

    if ((((event.key.keysym.mod == KMOD_RSHIFT) || (event.key.keysym.mod == KMOD_LSHIFT)) && event.key.keysym.mod != KMOD_CAPS) ||
        event.key.keysym.mod == KMOD_CAPS) {
        state = KeyState::MAJ;
    }
    if (event.key.keysym.mod == KMOD_LCTRL || event.key.keysym.mod == KMOD_RCTRL) {
        state = KeyState::CTRL;
    }
    return state;
}

IGraph::graphEvent SDL::getEvent(void) const noexcept
{
    SDL_Event event;
    graphEvent result = graphEvent::NOTHING;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                result = graphEvent::EXIT;
                break;
            }
            case SDL_KEYDOWN: {
                std::pair<int, int> pair = {event.key.keysym.sym, checkKeyState(event)};
                result = _eventMap.find(pair)->second;
                break;
            }
            default:
                break;
        }
    }
    return result;
}

extern "C"
{
    IGraph *newInstance(void)
    {
        return new SDL;
    }
}
