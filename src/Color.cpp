/*
** EPITECH PROJECT, 2020
** 202unsold
** File description:
** 202unsold: Color.cpp
*/

#include "Color.hpp"
#include <iostream>

const std::map<Color::Colors, std::string> Color::colorMap = {
    {Color::Blue, "012"},
    {Color::Red, "009"},
    {Color::Green, "010"},
    {Color::Yellow, "011"},
    {Color::White, "015"},
    {Color::Pink, "35"}
};

const std::map<Color::Type, std::string> Color::typeMap = {
    {Color::Bold, "01"},
    {Color::Normal, "00"},
    {Color::Underline, "04"}
};

std::string Color::getColor(const Colors &color, const Type &type)
{
    return std::string("\033[") + typeMap.find(type)->second + ";" +
        colorMap.find(color)->second + "m";
}

std::string Color::getStrColor(const std::string &str,
                               const Colors &color,
                               const Type &type)
{
    return getColor(color, type) + str + getColor();
}
