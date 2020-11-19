/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Parser.cpp
*/

#include "Parser.hpp"
#include "DLLoader.cpp"
#include "DirectoriesReader.hpp"
#include <iostream>

Parser::Parser(int ac, char **av)
{
    if (ac != 2)
        throw InvalidArgumentNumber("Expected 1 argument but got "
                                    + std::to_string(ac - 1));
    if (!DirectoriesReader::isFileType(av[1], "so"))
        throw InvalidArgumentType("Expected dynamic library \
as first argument but got " + std::string(av[1]));
    std::string path(av[1]);
    DirectoriesReader::setProperFilepath(path);
    _graphLibs[path] = new DLLoader<IGraph>(path);
    setInterface(_graphLibs, "./lib");
    setInterface(_gameLibs, "./games");
    _defaultGraphLib = _graphLibs[path]->getInstance();
}

std::map<std::string, DLLoader<IGraph> *> &Parser::getGraph(void) noexcept
{
    return _graphLibs;
}

std::map<std::string, DLLoader<IGame> *> &Parser::getGame(void) noexcept
{
    return _gameLibs;
}

IGraph *Parser::getDefaultGraph(void) noexcept
{
    return _defaultGraphLib;
}
