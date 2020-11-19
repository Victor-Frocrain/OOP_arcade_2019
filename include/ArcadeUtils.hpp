/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: ArcadeUtils.hpp
*/

#ifndef ARCADE_UTILS_HPP_
#define ARCADE_UTILS_HPP_

#include <string>
#include <map>
#include "DLLoader.hpp"
#include <vector>
#include <chrono>

class ArcadeUtils {
public:
    /* Utils function */
    static std::string getFileName(const std::string &filepath) noexcept;

    /*
    ** Description:
    ** Resize a string if the $string size is higher than $size
    ** by cutting the $string to $size char and adding "..."
    **
    ** Parameters:
    ** $name is the string  to resize
    ** $size is the number of char to be kept at least from the original string
    **
    ** Example:
    ** resizeString("0123456789", 10) = "0123456789"
    ** resizeString("0123456789012", 10) = "0123456789012"
    ** resizeString("01234567890123", 10) = "0123456789..."
    */
    static std::string resizeString(const std::string &name,
                                    const size_t &size = 10) noexcept;

    template<typename T, typename G>
    static const G &getConvertedEvent(const std::map<T, G> &map,
                                      const T &event, const G &defaultReturn)
        {
            typename std::map<T, G>::const_iterator it = map.find(event);

            return (it == map.end()) ? defaultReturn : it->second;
        };

    template<typename T>
    static typename T::const_iterator getIterator(const T &map, const size_t &it) noexcept
        {
            auto iterator = map.begin();
            for (size_t i = 0; i < it && iterator != map.end(); i++)
                iterator++;
            return iterator;
        };

    static std::vector<std::string> getMap(const std::string &filepath) noexcept;

    static bool isTimePassed(std::chrono::time_point<std::chrono::system_clock> &lastUpdate,
                                          const double &range) noexcept;

    template<typename T, typename S>
    static S getMemData(const T &ref, std::map<T, S> &memMap,
                                         S (*func)(const T &)) noexcept
        {
            auto it = memMap.find(ref);
            if (it == memMap.end())
                memMap[ref] = func(ref);
            return memMap[ref];
        };

    static bool compareFloat(float f1, float f2, float epsilon) noexcept;
};

#endif /* ARCADE_UTILS_HPP_ */
