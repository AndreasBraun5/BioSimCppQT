/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_GAMEMODEL_HPP
#define INCLUDED_BIOSIM_GAMEMODEL_HPP

#include <QMainWindow>
#include <qimage.h>
#include <list>

#include "exceptions.hpp"
#include "imagetga.hpp"
#include "creature.hpp"
//#include "biosim.h" // TODO Note: circular dependency

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class TextFileReader /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class GameModel {
public: QList<CreatureData> creatureList;

    //test TODO const Qscoped... -> pointer to a const imagetga sand.
    QScopedPointer<ImageTga> sand;
    // land
    QScopedPointer<ImageTga> birne;
    QScopedPointer<ImageTga> busch;
    // terrain
    QScopedPointer<ImageTga> deep_sea;
    QScopedPointer<ImageTga> earth;
    // wasser
    QScopedPointer<ImageTga> algen;
    QScopedPointer<ImageTga> delpin;

    GameModel() = delete; // RAII pattern. No zombie gamemodel possible.
    GameModel(const std::string &relativePath);

private: void setUpGamemodel(const std::string &relativePath);
    void loadImages(const std::string &relativePath);
    void loadCreatures(const std::string &relativeFilePath);

};
#endif // GAMEMODEL_HPP
