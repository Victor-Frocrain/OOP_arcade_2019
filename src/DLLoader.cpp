/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: DLLoader.cpp
*/

#include "DLLoader.hpp"
#include "IGraph.hpp"
#include "IGame.hpp"
#include <iostream>

template<typename T>
DLLoader<T>::DLLoader(const std::string &path):
    _path(path), _constructor(nullptr), _instance(nullptr), _handle(nullptr)
{
    getConstructor();
}

template<typename T>
DLLoader<T>::~DLLoader(void) noexcept(false)
{
    if (_instance)
        delete _instance;
    if (_handle && dlclose(_handle) != 0)
        throw DLLoaderException(dlerror());
}

template<typename T>
T *DLLoader<T>::getInstance(void)
{
    if (!_instance)
        _instance = _constructor();
    return _instance;
}

template<typename T>
void DLLoader<T>::getConstructor(void)
{
    _handle = dlopen(_path.c_str(), RTLD_LOCAL | RTLD_LAZY | RTLD_NODELETE);
    if (!_handle)
        throw DLLoaderException(dlerror());
    void *ret = dlsym(_handle, "newInstance");
    if (!ret)
        throw DLLoaderException(dlerror());
    _constructor = reinterpret_cast<Constructor>(reinterpret_cast<long>(ret));
}
