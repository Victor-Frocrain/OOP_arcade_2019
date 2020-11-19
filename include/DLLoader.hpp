/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: DLLoader.hpp
*/

#ifndef DLLoader_HPP_
#define DLLoader_HPP_

#include <string>
#include <dlfcn.h>
#include "ArcadeException.hpp"
#include <iostream>

template<typename T>
class DLLoader {
public:
    DLLoader(const std::string &path);
    ~DLLoader(void) noexcept(false);

    /* Generate new Instance */
    T *getInstance(void);

    /* Typedef */
    typedef T *(*Constructor)(void);

    /* Private method */
private:
    void getConstructor(void);

    /* Attribute */
private:
    const std::string _path;
    Constructor _constructor;
    T *_instance;
    void *_handle;
};
#endif /* DLLoader_HPP_ */
