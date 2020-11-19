/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: directoriesReader.cpp
*/

#include "DirectoriesReader.hpp"
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <regex>

DirectoriesReader::
DirectoriesReader(const std::string &name, const std::string &ext, bool openRec,
                  bool throwIfEmpty)
{
    readDirectories({name}, ext, openRec, throwIfEmpty);
}

DirectoriesReader::DirectoriesReader(
    std::vector<std::string> names, const std::string &ext, bool openRec,
    bool throwIfEmpty)
{
    readDirectories(names, ext, openRec, throwIfEmpty);
}

void DirectoriesReader::readDirectories(
    std::vector<std::string> names, const std::string &ext, bool openRec,
    bool throwIfEmpty)
{
    std::vector<std::string> emptyFile;

    for (auto it : names) {
        try {
            std::vector<std::string> data = openFile(it, ext, openRec);
            _data.insert(_data.end(), data.begin(), data.end());
        } catch (const DirectoriesReaderException::EmptyFile &error) {
            emptyFile.push_back(it);
        }
    }
    if (emptyFile.size() > 0) {
        std::stringstream ss;
        ss << "One or several file are empty" << std::endl;
        ss << "List of empty file:";
        for (auto it : emptyFile)
            ss << std::endl << it;
        if (!throwIfEmpty)
            _error = ss.str();
        else
            throw DirectoriesReaderException::EmptyFile(ss.str());
    }
}

std::string &DirectoriesReader::setProperExtension(std::string &ext) noexcept
{
    if (ext.size() > 0 && ext[0] != '.')
        ext.insert(ext.begin(), '.');
    return ext;
}

std::string &DirectoriesReader::setProperFilepath(std::string &filepath) noexcept
{
    if (filepath == ".") {
        filepath.assign("./");
        return filepath;
    } else if (filepath == "..") {
        filepath.assign("../");
        return filepath;
    } else if (filepath == "")
        return filepath;
    filepath.assign(std::regex_replace(filepath, std::regex("\\./"), ""));
    std::string begin(filepath.substr(0, 2));
    if (begin != "./" && begin != "~/" && filepath.substr(1) != "/")
        filepath.assign("./" + filepath);
    return filepath;
}

std::string DirectoriesReader::
getPath(const std::string &dir, const std::string &file)
{
    if (dir[dir.size() - 1] != '/')
        return dir + "/" + file;
    return dir + file;
}

std::vector<std::string> DirectoriesReader::
openFile(const std::string &name, const std::string &ext, bool openRec)
{
    std::vector<std::string> result;
    DIR *dir = opendir(name.c_str());
    struct dirent *ent;
    struct stat s;

    if (dir) {
        while ((ent = readdir(dir))) {
            if (std::string(ent->d_name) == "." || std::string(ent->d_name) == "..")
                continue;
            std::string path = getPath(name, ent->d_name);
            stat(path.c_str(), &s);
            if (openRec && s.st_mode & S_IFDIR) {
                try {
                    std::vector<std::string> res = openFile(path, ext, openRec);
                    result.insert(result.end(), res.begin(), res.end());
                } catch (const DirectoriesReaderException::EmptyFile &error) {
                    std::cerr << error.what() << std::endl;
                }
            } else if (isFileType(ent->d_name, ext))
                result.push_back(path);
        }
    }
    closedir(dir);
    if (!result.size())
        throw DirectoriesReaderException::EmptyFile(name + " is empty");
    return result;
}

bool DirectoriesReader::
isFileType(const std::string &name, const std::string &ext)
{
    auto it = name.find_last_of('.');
    std::string realExt(ext[0] == '.' ? ext.substr(1, ext.size()) : ext);

    if (it >= name.size())
        return false;
    return name.substr(it + 1, name.size()) == realExt;
}

const std::vector<std::string> &DirectoriesReader::getData(void)
    const noexcept
{
    return _data;
}

std::string DirectoriesReader::getError(void) noexcept
{
    std::string error(_error);

    _error.assign("");
    return error;
}

bool DirectoriesReader::isError(void) const noexcept
{
    return _error != "";
}

DirectoriesReaderException::DirectoriesReaderException::
DirectoriesReaderException(const std::string &message):
    _message(message)
{}

const char *DirectoriesReaderException::DirectoriesReaderException::
what(void) const noexcept
{
    return _message.c_str();
}

DirectoriesReader::~DirectoriesReader(void)
{};

DirectoriesReaderException::
EmptyFile::EmptyFile(const std::string &message) :
    DirectoriesReaderException(message)
{}
