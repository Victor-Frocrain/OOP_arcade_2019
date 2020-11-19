/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Arcade: ArcadeException.hpp
*/

#ifndef ARCADE_EXCEPTION_HPP_
#define ARCADE_EXCEPTION_HPP_

#include <exception>
#include <string>

class ArcadeException : public std::exception {
public:
    ArcadeException(const std::string &what);

    /* Override of std::exception::what() */
    const char *what(void) const noexcept override;

private:
    const std::string _what;
};

class DLLoaderException : public ArcadeException {
public:
    DLLoaderException(const std::string &what);
};

class InvalidArgumentNumber : public ArcadeException {
public:
    InvalidArgumentNumber(const std::string &what);
};

class InvalidArgumentType : public ArcadeException {
public:
    InvalidArgumentType(const std::string &what);
};

#endif /* ARCADE_EXCEPTION_HPP_ */
