/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_GAMEMODEL_HPP
#define INCLUDED_BIOSIM_GAMEMODEL_HPP

#include <list>
#include <map>

#include <QList> // // minimal QT stuff allowed here in gamemodel, for convenience

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
    QList<Creature> creaturesPossibleList;
    QList<Creature> creaturesAllOnGrid;
    // somthing better than QList needed. As example one must be able to access nearby creatures
    // later. --> Quadtree
    // TODO: deleting creatures not implemented
    // all creatures that exist must be stored here and deleted if dead. Deleting is more or less implementation dependent. So still pending.

    std::map<std::string, std::vector<unsigned char>> imageMap;
    std::vector<std::vector<LandscapeTile>> landscapeGridmap;// landscapeGridmap [down][left] = landscapeGridmap [0][0];

    GameModel() = delete; // RAII pattern. No zombie gamemodel possible.
    GameModel(const std::string &relativePath);

private:
    void setUpGamemodel(const std::string &relativePath);
    void loadImages(const std::string &imageDataFilepath);
    void loadCreatures(const std::string &creatureDataFilepath);
public: void loadLandscapeGrid(unsigned int sizehorizontal, unsigned int sizevertical);
};
#endif // GAMEMODEL_HPP
