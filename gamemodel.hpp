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
/*/ class TextFileReader /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class GameModel {
public:
    // possible creature types
    QList<CreatureData> creatureDataList;

    // images
    std::vector<unsigned char> deep_sea;
    std::vector<unsigned char> shallow_water;
    std::vector<unsigned char> sand;
    std::vector<unsigned char> earth;
    std::vector<unsigned char> rocks;
    std::vector<unsigned char> snow;

    std::vector<unsigned char> birne;
    std::vector<unsigned char> delphin;

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
