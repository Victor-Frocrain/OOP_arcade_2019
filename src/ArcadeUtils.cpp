/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: ArcadeUtils.cpp
*/

#include "ArcadeUtils.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <math.h>

std::string ArcadeUtils::getFileName(const std::string &filepath) noexcept
{
    std::string name(filepath);
    size_t pos;

    while ((pos = name.find('/')) < name.size())
        name.assign(name.substr(pos + 1, name.size()));
    return name;
}

std::string ArcadeUtils::resizeString(const std::string &name,
                                      const size_t &size) noexcept
{
    if (name.size() > size + 3)
        return name.substr(0, size) + "...";
    return name;
}

std::vector<std::string> ArcadeUtils::getMap(const std::string &filepath) noexcept
{
    std::vector<std::string> result;
    std::fstream fs(filepath);
    std::string line;

    while (std::getline(fs, line))
        result.push_back(line);
    fs.close();
    return result;
}

bool ArcadeUtils::isTimePassed(std::chrono::time_point<std::chrono::system_clock> &lastUpdate,
                        const double &range) noexcept
{
    using namespace std::chrono;
    auto now = system_clock::now();

    if (duration<double>(now - lastUpdate).count() >= range) {
        lastUpdate = now;
        return true;
    }
    return false;
}

bool ArcadeUtils::compareFloat(float f1, float f2, float epsilon) noexcept
{
    return (fabs(f1 - f2) < epsilon);
}
