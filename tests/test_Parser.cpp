/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: test_Parser.cpp
*/

#include <criterion/criterion.h>
#include "Parser.hpp"
#include "ArcadeException.hpp"
#include <unistd.h>
#include "DirectoriesReader.hpp"

Test(Parser, invalidArgumentNumber)
{
    char *av[] = {(char *)"./parser", nullptr};
    try {
        Parser(1, av);
    } catch (const InvalidArgumentNumber &error) {
        cr_expect_eq(std::string(error.what()), "Expected 1 argument but got 0");
    }
    try {
        Parser(3, av);
    } catch (const InvalidArgumentNumber &error) {
        cr_expect_eq(std::string(error.what()), "Expected 1 argument but got 2");
    }
}

Test(Parser, invalidArgumentExtension)
{
    char *arg[] = {(char *)"./parser", (char *)"test", nullptr};
    try {
        Parser(2, arg);
    } catch (const InvalidArgumentType &error) {
        cr_expect_eq(std::string(error.what()), "Expected dynamic library as \
first argument but got test");
    }
}

Test(Parser, invalidArgumentFile)
{
    char *argv[] = {(char *)"./parser", (char *)"test.so", nullptr};
    try {
        Parser(2, argv);
    } catch (const DLLoaderException &error) {
        cr_expect_eq(std::string(error.what()), "./test.so: cannot open shared \
object file: No such file or directory");
    }
}

Test(Parser, LibWhithoutNewInstance)
{
    chdir("tests/rsrc7/");
    char *argv[] = {(char *)"./parser", (char *)"lib/test_graph.so", nullptr};
    try {
        Parser(2, argv);
    } catch (const DLLoaderException &error) {
        cr_expect_eq(std::string(error.what()), "./games/test_game.so: \
undefined symbol: newInstance");
    }
}

Test(Parser, emptyLibFile)
{
    chdir("tests/rsrc4/");
    char *argv[] = {(char *)"./parser", (char *)"test_graph.so", nullptr};
    try {
        Parser(2, argv);
    } catch (const DirectoriesReaderException::DirectoriesReaderException &error) {
        cr_expect_eq(std::string(error.what()), "One or several file are empty\n\
List of empty file:\n\
./lib");
    }
}

Test(Parser, emptyGamesFile)
{
    chdir("tests/rsrc5/");
    char *argv[] = {(char *)"./parser", (char *)"lib/test_graph.so", nullptr};
    try {
        Parser(2, argv);
    } catch (const DirectoriesReaderException::DirectoriesReaderException &error) {
        cr_expect_eq(std::string(error.what()), "One or several file are empty\n\
List of empty file:\n\
./games");
    }
}

Test(Parser, functionnal)
{
    chdir("tests/rsrc6/");
    char *argv[] = {(char *)"./parser", (char *)"./lib/test_graph.so", nullptr};
    try {
        Parser(2, argv);
    } catch (const std::exception &error) {
        cr_assert_fail("Should not throw error");
    }
    try {
        Parser parser(2, argv);
        cr_expect_not_null(parser.getDefaultGraph());
        cr_expect_eq(parser.getGame().size(), 1);
        cr_expect_eq(parser.getGraph().size(), 1);
        for (auto it : parser.getGame())
            delete it.second;
        for (auto it : parser.getGraph())
            delete it.second;
    } catch (const std::exception &error) {
        cr_assert_fail("Should not throw error");
    }
}
