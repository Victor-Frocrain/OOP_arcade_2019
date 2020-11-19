/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: Parser.hpp
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "ArcadeException.hpp"
#include <map>
#include "IGraph.hpp"
#include "IGame.hpp"
#include <vector>
#include "DLLoader.hpp"
#include "DirectoriesReader.hpp"

class Parser {
public:
    /* Default constructor */
    Parser(int ac, char **av);

    /* Getter */
    std::map<std::string, DLLoader<IGraph> *> &getGraph(void) noexcept;
    std::map<std::string, DLLoader<IGame> *> &getGame(void) noexcept;
    IGraph *getDefaultGraph(void) noexcept;

    template<typename T>
    static void setInterface(std::map<std::string, DLLoader<T> *> &map,
                      const std::string &path)
        {
            std::map<std::string, DLLoader<T> *> newMap;
            DirectoriesReader dr(path, "so", false);
            for (auto it : dr.getData()) {
                if (map.find(it) == map.end())
                    newMap[it] = new DLLoader<T>(it);
                else
                    newMap[it] = map[it];
            }
            map = newMap;
        };

    /* Attribute */
private:
    std::map<std::string, DLLoader<IGraph> *> _graphLibs;
    std::map<std::string, DLLoader<IGame> *> _gameLibs;
    IGraph *_defaultGraphLib;
};

#endif /* PARSER_HPP_ */
