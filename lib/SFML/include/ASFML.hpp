/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: lib/SFML/ASFML.hpp
*/

#ifndef ASFML_HPP_
#define ASFML_HPP_

#include "../../../include/IGraph.hpp"
#include "../../../include/FileReader.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#define WIDTH 1920
#define HEIGHT 1080
#define WSIZE 24
#define HSIZE 24
#define SCALE 24

class ASFML : public IGraph {
public:
    virtual ~ASFML() = default;
    virtual void createWindow() = 0;
    virtual void displayWindow(const std::vector<IEntity *> &entities) = 0;
    virtual graphEvent getEvent(void) const noexcept = 0;
    virtual void closeWindow(void) = 0;

protected:
    sf::RenderWindow *_win;
    sf::Font _font;
    sf::Clock _clock;
    sf::Time _time;
    std::map<IEntity *, std::tuple<sf::Sprite, sf::Rect<int>, sf::Text, sf::RectangleShape, sf::Texture>> _sprite;
};

#endif /* ASFML_HPP_ */
