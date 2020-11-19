/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: test_ArcadeUtils.cpp
*/

#include "ArcadeUtils.hpp"
#include <criterion/criterion.h>
#include <iostream>
#include <thread>

Test(ArcadeUtils, getFileName, .timeout = 1)
{
    cr_expect_eq(ArcadeUtils::getFileName("hello"), "hello");
    cr_expect_eq(ArcadeUtils::getFileName("./hello"), "hello");
    cr_expect_eq(ArcadeUtils::getFileName("./dir/hello"), "hello");
}

Test(ArcadeUtils, resizeStrong, .timeout = 1)
{
    cr_expect_eq(ArcadeUtils::resizeString("0123456789", 10), "0123456789");
    cr_expect_eq(ArcadeUtils::resizeString("0123456789012", 10), "0123456789012");
    cr_expect_eq(ArcadeUtils::resizeString("01234567890123", 10), "0123456789...");
}

Test(ArcadeUtils, getMap)
{
    std::vector<std::string> v = ArcadeUtils::getMap("map/pacman.txt");
    cr_expect_eq(v.size(), 31);
    cr_expect_eq(v[0], "###########################");
    cr_expect_eq(v[30], "###########################");
}

Test(ArcadeUtils, getIterator)
{
    std::map<int, short> map {
        {10, 20},
        {20, 10}
    };
    cr_expect_eq(ArcadeUtils::getIterator(map, 0), map.begin());
    cr_expect_eq(ArcadeUtils::getIterator(map, 1), ++map.begin());
    cr_expect_eq(ArcadeUtils::getIterator(map, 2), map.end());
}

Test(ArcadeUtils, getConvertedEvent)
{
    std::map<int, std::string> map {
        {2, "hello"},
        {3, "hey"}
    };
    std::string defaultChar("h");

    cr_expect_eq(ArcadeUtils::getConvertedEvent(map, 2, defaultChar), "hello");
    cr_expect_eq(ArcadeUtils::getConvertedEvent(map, 3, defaultChar), "hey");
    cr_expect_eq(ArcadeUtils::getConvertedEvent(map, 1, defaultChar), "h");
}

Test(ArcadeUtils, isTimePassed)
{
    std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> start = time;
    cr_expect_not(ArcadeUtils::isTimePassed(time, 1));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cr_expect(ArcadeUtils::isTimePassed(time, 1));
    cr_expect_neq(time, start);
}
