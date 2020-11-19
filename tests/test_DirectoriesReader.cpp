/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade : test_DirectoriesReader
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "DirectoriesReader.hpp"
#include <iostream>
#include <vector>
#include <sys/stat.h>

void redirect_all_std(void)
{
    cr_redirect_stderr();
}

Test(DirectoriesReader, setProperExtension)
{
    std::string str("hello");
    cr_expect_eq(DirectoriesReader::setProperExtension(str), ".hello");
    cr_assert_eq(str, ".hello");
    cr_expect_eq(DirectoriesReader::setProperExtension(str), ".hello");
}

Test(DirectoriesReader, isFileType)
{
    cr_expect(DirectoriesReader::isFileType("hello.de", "de"));
    cr_expect(DirectoriesReader::isFileType("hello.fe.de", "de"));
    cr_expect_not(DirectoriesReader::isFileType("hello.de.fe", "de"));
    cr_expect_not(DirectoriesReader::isFileType("hello.de1", "de"));
    cr_expect_not(DirectoriesReader::isFileType("hellode", "de"));
}

Test(DirectoriesReader, getPath)
{
    cr_assert_eq(DirectoriesReader::getPath("dir", "file"), "dir/file");
    cr_assert_eq(DirectoriesReader::getPath("dir/", "file"), "dir/file");
}

Test(DirectoriesReader, openFile)
{
    cr_expect_eq(DirectoriesReader::openFile("tests/rsrc", "test"),
                 std::vector<std::string>{"tests/rsrc/file.test"});
    cr_expect_eq(DirectoriesReader::openFile("tests/rsrc", "file", true),
                 std::vector<std::string>({"tests/rsrc/test.file",
                                           "tests/rsrc/rsrc2/test.file"}));
    cr_expect_eq(DirectoriesReader::openFile("tests/rsrc", "file"),
                 std::vector<std::string>({"tests/rsrc/test.file"}));
    try {
        DirectoriesReader::openFile("test", "file");
        cr_expect_fail("should throw error");
    } catch (const DirectoriesReaderException::EmptyFile &error) {
        cr_expect_eq(std::string(error.what()), "test is empty");
    }
}

Test(DirectoriesReader, functionnal)
{
    cr_expect_eq(DirectoriesReader("tests/rsrc", "test").getData(),
                 std::vector<std::string>{"tests/rsrc/file.test"});
    cr_expect_eq(DirectoriesReader("tests/rsrc", "file", true).getData(),
                 std::vector<std::string>({"tests/rsrc/test.file",
                                           "tests/rsrc/rsrc2/test.file"}));
    cr_expect_eq(DirectoriesReader("tests/rsrc", "file", false).getData(),
                 std::vector<std::string>({"tests/rsrc/test.file"}));
    cr_expect_eq(DirectoriesReader(std::vector<std::string>{"tests/rsrc2",
                    "tests/rsrc3"}, "file", false).getData(),
                 std::vector<std::string>({"tests/rsrc2/test.file",
                                           "tests/rsrc3/test.file"}));
    try {
        DirectoriesReader("test", "file");
        cr_expect_fail("should throw error");
    } catch (const DirectoriesReaderException::EmptyFile &error) {
        cr_expect_eq(std::string(error.what()), "\
One or several file are empty\n\
List of empty file:\n\
test");
    }
}

Test(DirectoresReader, emptySubDirectory, .init = redirect_all_std)
{
    DirectoriesReader("tests/", ".cpp", true);
}

Test(DirectoriesReader, NotThrowing)
{
    auto dr = DirectoriesReader("test", "file", false, false);
    cr_assert(dr.isError());
    cr_expect_eq(dr.getError(), "\
One or several file are empty\n\
List of empty file:\n\
test");
}

Test(DirectoriesReader, setProperFilepath)
{
    std::string filepath("hello");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "./hello");
    filepath.assign("./././././././hello");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "./hello");
    filepath.assign("./././././././dir/./");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "./dir/");
    filepath.assign("~/hello");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "~/hello");
    filepath.assign("");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "");
    filepath.assign(".");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "./");
    filepath.assign("..");
    DirectoriesReader::setProperFilepath(filepath);
    cr_expect_eq(filepath, "../");
}
