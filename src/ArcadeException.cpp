/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: ArcadeException.cpp
*/

#include "ArcadeException.hpp"

ArcadeException::ArcadeException(const std::string &what):
    _what(what)
{};

const char *ArcadeException::what(void) const noexcept
{
    return _what.c_str();
}

DLLoaderException::DLLoaderException(const std::string &what):
    ArcadeException(what)
{};

InvalidArgumentNumber::InvalidArgumentNumber(const std::string &what) :
    ArcadeException(what)
{};

InvalidArgumentType::InvalidArgumentType(const std::string &what) :
    ArcadeException(what)
{};
