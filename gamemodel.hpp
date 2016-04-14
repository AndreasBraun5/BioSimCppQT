/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_GAMEMODEL_HPP
#define INCLUDED_BIOSIM_GAMEMODEL_HPP

#include <QMainWindow>
#include <QImage>
#include <list>

#include "exceptions.hpp"
#include "imagetga.hpp"
#include "creature.hpp"
#include "landscape.hpp"
//#include "biosim.h" // TODO Note: circular dependency
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class TextFileReader /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class GameModel {
public: QList<CreatureData> creatureList;

    //TODO Discuss: const Qscoped... -> pointer to a ?const? imagetga, because Image data
    // doesn´t need to be manipulated.

    // land
    QScopedPointer<ImageTga> birne;
    QScopedPointer<ImageTga> busch;
    // terrain
    QScopedPointer<LandscapeGrid> landscapeGrid;
    //QScopedPointer<QGraphicsPixmapItem> landscapeGridPixmap; //the generated landscape is only data here, no logic,
                                                         //each item has its pointer set to its pixmap and the offset specified
    // holding all graphical Items only one time here as QPixmaps
    QScopedPointer<ImageTga> deep_seaImageTga;
    QScopedPointer<ImageTga> earthImageTga;
    QScopedPointer<ImageTga> rocksImageTga;
    QScopedPointer<ImageTga> sandImageTga;
    QScopedPointer<ImageTga> shallow_waterImageTga;
    QScopedPointer<ImageTga> snowImageTga;

    QSharedPointer<QPixmap> deep_seaPixmap;
    QSharedPointer<QPixmap> earthPixmap;
    QSharedPointer<QPixmap> rocksPixmap;
    QSharedPointer<QPixmap> sandPixmap;
    QSharedPointer<QPixmap> shallow_waterPixmap;
    QSharedPointer<QPixmap> snowPixmap;

    // wasser
    QScopedPointer<ImageTga> algen;
    QScopedPointer<ImageTga> delpin;

    //TODO AB4: insert landscape scoped Pointer

    GameModel() = delete; // RAII pattern. No zombie gamemodel possible.
    GameModel(const std::string &relativePath);

private:
    void setUpGamemodel(const std::string &relativePath);
    void loadImages(const std::string &relativePath);
    void loadCreatures(const std::string &relativeFilePath);
public: void loadLandscapeGrid(); //TODO AB4: additional parameters at compiletime
};
#endif // GAMEMODEL_HPP
