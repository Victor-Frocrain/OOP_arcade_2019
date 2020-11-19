/*
** EPITECH PROJECT, 2020
** ASDL
** File description:
** ASDL.hpp
*/

#ifndef ASDL_HPP_
#define ASDL_HPP_

#define WIDTH 1920
#define HEIGHT 1080
#define WSIZE 24
#define HSIZE 24
#define SCALE 24

#include "../../../include/IGraph.hpp"
#include "../../../include/FileReader.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <tuple>

class ASDL : public IGraph {
public:
    ASDL() = default;
    virtual void createWindow() = 0;
    virtual void displayWindow(const std::vector<IEntity *> &entities) = 0;
    virtual graphEvent getEvent(void) const noexcept = 0;
    virtual void closeWindow(void) = 0;

protected:
    virtual void drawEntities(const std::vector<IEntity *> &entities) = 0;

protected:
    SDL_Window *_win;
    SDL_Surface *_blackScreen;
    
    std::map<IEntity *, std::tuple<SDL_Surface *, SDL_Rect, std::string>> _surfaces;

    TTF_Font *_font;
};

extern "C"
{
    IGraph *newInstance(void);
}

#endif /* ASDL_HPP_ */
