/*
** EPITECH PROJECT, 2020
** 202unsold
** File description:
** 202unsold: Color.hpp
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <string>
#include <map>

class Color {
public:
    /* Enum */
    enum Colors {Blue, Red, Green, Yellow, White, Pink};
    enum Type {Normal, Bold, Underline};

    /* Methods */
    static std::string getStrColor(const std::string &str,
                            const Colors &color = White,
                            const Type &type = Normal);
    static std::string getColor(const Colors &color = White,
                            const Type &type = Normal);

    /* Variables */
    static const std::map<Colors, std::string> colorMap;
    static const std::map<Type, std::string> typeMap;
};

#endif /* COLOR_HPP_ */
