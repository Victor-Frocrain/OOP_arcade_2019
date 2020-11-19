/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: FileReader.hpp
*/

#ifndef FILE_READER_HPP_
#define FILE_READER_HPP_

#include <string>
#include <exception>
#include <vector>

class FileReader {
public:
    FileReader(const std::string &filepath);
    ~FileReader(void) noexcept;

    std::vector<std::string> find(const std::string &toFind) const;

    void reset(void) noexcept;

    /* Private Method */
private:
    static bool isSection(const std::string &line) noexcept;
    static bool isSection(const std::string &line, const std::string &sectionName) noexcept;

    /* Private Attribute */
private:
    std::string _filepath;
    std::vector<std::string> _file;
};

class FileReaderException : public std::exception {
public:
    FileReaderException(const std::string &message) noexcept;

    const char *what(void) const noexcept final;
private:
    std::string _message;
};

class SectionNotFound : public FileReaderException {
public:
    SectionNotFound(const std::string &sectionName) noexcept;
};

class EmptySection : public FileReaderException {
public:
    EmptySection(const std::string &sectionName) noexcept;
};

#endif /* FILE_READER_HPP_ */
