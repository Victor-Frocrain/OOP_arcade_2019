/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: FileReader.cpp
*/

#include "FileReader.hpp"
#include <fstream>
#include "ArcadeUtils.hpp"

FileReader::FileReader(const std::string &filepath) :
    _filepath(filepath), _file(ArcadeUtils::getMap(filepath))
{}

FileReader::~FileReader(void) noexcept
{}

std::vector<std::string> FileReader::find(const std::string &toFind) const
{
    std::vector<std::string> v;
    bool section = false;

    if (!_file.empty()) {
        for (auto line : _file) {
            if (line != ""){
                if (!section)
                    section = isSection(line, toFind);
                else if (isSection(line))
                    break;
                else
                    v.push_back(line);
            }
        }
        if (!section)
            throw SectionNotFound(toFind);
        if (!v.size())
            throw EmptySection(toFind);
    }
    return v;
}

void FileReader::reset(void) noexcept
{
    _file = ArcadeUtils::getMap(_filepath);
}

bool FileReader::isSection(const std::string &line) noexcept
{
    return line[line.size() - 1] == ':';
}

bool FileReader::isSection(const std::string &line, const std::string &sectionName) noexcept
{
    if (!isSection(line))
        return false;
    return sectionName == line.substr(0, line.size() - 1);
}

FileReaderException::FileReaderException(const std::string &message) noexcept :
    _message(message)
{}

const char *FileReaderException::what(void) const noexcept
{
    return _message.c_str();
}

SectionNotFound::SectionNotFound(const std::string &sectionName) noexcept :
    FileReaderException("The section " + sectionName + " cannot be found")
{}

EmptySection::EmptySection(const std::string &sectionName) noexcept :
    FileReaderException("The section " + sectionName + " is empty")
{}
