/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_GAMEMODEL_HPP
#define INCLUDED_BIOSIM_GAMEMODEL_HPP

#include <list>

#include <QList> // // QT stuff allowed here in gamemodel
#include <QGraphicsScene>

#include "exceptions.hpp"
#include "imagetga.hpp"
#include "creature.hpp"
#include "textfilereader.hpp"
#include "landscape.hpp"
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class GameModel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class GameModel {
public:
    // possible creature types
    QList<Creature> creaturesPossibleList;
    QList<Creature> creaturesAllOnGrid; //  TODO: position
    // all creatures that exist must be stored here and deleted if dead.

    // images
    std::vector<unsigned char> cursor;
    std::vector<unsigned char> dead;
    std::vector<unsigned char> path;
    // terrain
    std::vector<unsigned char> deep_sea;
    std::vector<unsigned char> shallow_water;
    std::vector<unsigned char> sand;
    std::vector<unsigned char> earth;
    std::vector<unsigned char> rocks;
    std::vector<unsigned char> snow;
    // land
    std::vector<unsigned char> birne;
    std::vector<unsigned char> busch;
    std::vector<unsigned char> eiche;
    std::vector<unsigned char> emu;
    std::vector<unsigned char> gras;
    std::vector<unsigned char> hund;
    std::vector<unsigned char> kaktus;
    std::vector<unsigned char> kuh;
    std::vector<unsigned char> pferd;
    std::vector<unsigned char> schaf;
    std::vector<unsigned char> sonnenblume;
    std::vector<unsigned char> tanne;
    std::vector<unsigned char> tiger;
    std::vector<unsigned char> ursus;
    //wasser
    std::vector<unsigned char> algen;
    std::vector<unsigned char> delphin;
    std::vector<unsigned char> forelle;
    std::vector<unsigned char> hai;
    std::vector<unsigned char> krabbe;
    std::vector<unsigned char> plankton;
    std::vector<unsigned char> seetang;
    std::vector<unsigned char> wels;

    // landscape
    std::vector<std::vector<LandscapeTile>> landscapeGridmap;// landscapeGridmap [down][left] = landscapeGridmap [0][0];

    // storing of all creatures objects here too

    GameModel() = delete; // RAII pattern. No zombie gamemodel possible.
    GameModel(const std::string &relativePath);

private:
    void setUpGamemodel(const std::string &relativePath);
    void loadImages(const std::string &imageDataFilepath);
    void loadCreatures(const std::string &creatureDataFilepath);
public: void loadLandscapeGrid(unsigned int sizehorizontal, unsigned int sizevertical);
};
#endif // GAMEMODEL_HPP
