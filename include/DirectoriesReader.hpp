/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: directoriesReader.hpp
*/

#ifndef DIRECTORIES_READER_HPP
#define DIRECTORIES_READER_HPP

#include <string>
#include <vector>
#include <exception>

/*
** Can throw during Construction when one or more provided file are empty
** Will also write in error output if empty file is find during recusivity
*/

class DirectoriesReader {
public:
    /* Constructor */
    DirectoriesReader(const std::string &name, const std::string &ext,
                      bool openRec = false, bool throwIfEmpty = true);
    DirectoriesReader(std::vector<std::string> names,
                      const std::string &ext, bool openRec = false,
                      bool throwIfEmpty = true);

    /* Destructor */
    ~DirectoriesReader(void);

    /* Setter */
    void readDirectories(std::vector<std::string> names, const std::string &ext,
                         bool openRec, bool throwIfEmpty);

    /* Getter */
    const std::vector<std::string> &getData(void) const noexcept;
    std::string getError(void) noexcept;
    bool isError(void) const noexcept;

    /* Static function */
    static std::vector<std::string> openFile(const std::string &name,
                                             const std::string &ext,
                                             bool openRec = false);
    static bool isFileType(const std::string &name, const std::string &ext);
    static std::string getPath(const std::string &dir,
                               const std::string &file);
    static std::string &setProperExtension(std::string &ext) noexcept;
    static std::string &setProperFilepath(std::string &filepath) noexcept;

private:
    std::vector<std::string> _data;
    std::string _error;
};

namespace DirectoriesReaderException {
    class DirectoriesReaderException : public std::exception {
    public:
        DirectoriesReaderException(const std::string &message);
        const char *what(void) const noexcept;
    private:
        const std::string _message;
    };

    class EmptyFile : public DirectoriesReaderException {
    public:
        EmptyFile(const std::string &message);
    };
}

#endif /* DIRECTORIES_READER_HPP */
