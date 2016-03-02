/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/

/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "imagetga.h"
#include "creature.h"
#include <QMainWindow>
#include <qimage.h>
#include <exceptions.h>
#include "imagetga.h"
//#include "biosim.h" // circular dependency

class GameModel {
public: QList<CreatureData> creatureList;

    //test
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

public:  GameModel(std::string relativePath);
    //~GameModel();
private: void setUpGamemodel(std::string relativePath);
private: void loadImages(std::string relativePath);
    void loadCreatures(std::string relativeFilePath);

};
#endif // GAMEMODEL_H
