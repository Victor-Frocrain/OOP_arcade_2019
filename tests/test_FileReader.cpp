/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: test_FileReader.cpp
*/

#include "FileReader.hpp"
#include <criterion/criterion.h>

Test(FileReader, emptySection)
{
    FileReader fr("tests/fileReader");

    try {
        fr.find("empty");
        cr_expect_fail("Should throw error");
    } catch (const EmptySection &error) {
        cr_expect_eq(std::string(error.what()), "The section empty is empty");
    } catch (const FileReaderException &error) {
        cr_expect_fail();
    }
}

Test(FileReader, notFoundSection)
{
    FileReader fr("tests/fileReader");

    try {
        fr.find("notExisting");
        cr_expect_fail("Should throw error");
    } catch (const SectionNotFound &error) {
        cr_expect_eq(std::string(error.what()), "The section notExisting cannot be found");
    } catch (const FileReaderException &error) {
        cr_expect_fail();
    }
}

Test(FileReader, findSectionEndFile)
{
    FileReader fr("tests/fileReader");

    std::vector<std::string> v = fr.find("player");
    cr_expect_eq(v[0], "path.txt");
}

Test(FileReader, findSectionEndNextSection)
{
    FileReader fr("tests/fileReader");

    std::vector<std::string> v = fr.find("player2");
    cr_expect_eq(v[0], "path.txt");
    cr_expect_eq(v[1], "path2.txt");
    fr.reset();
    v = fr.find("player2");
    cr_expect_eq(v[0], "path.txt");
    cr_expect_eq(v[1], "path2.txt");
}
