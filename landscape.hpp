/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    landscape
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_LANDSCAPE_HPP
#define INCLUDED_BIOSIM_LANDSCAPE_HPP

#include <vector>
#include "creature.hpp"

class GameModel;

enum ClimateType {DEEP_SEA, EARTH, ROCKS, SAND, SHALLOW_WATER, SNOW};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class LandscapeTile{
public: LandscapeTile() = delete;
public: LandscapeTile(ClimateType climate);
public: ClimateType climate;
    CreatureTileType creatureTileType;
    std::vector<Creature> creaturesOnTile; // This way it is intended to memorize which creatures are on this tile
    // TODO AB5: operator = (and copy constructor) must be implemented
    // add operator= and copy-constructor are not generated implicitly because of const properties

    // TODO: All stuff to do for AB5

    // all creatures that are added here must be the same  (or only a reference/pointer) that are stored in the gamemodel.
    // deleting a creature in the gamemodel must result in deleting the creature on the tile and vice versa

    // void QGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
    // marking as active tile: catch mouspressevent, add cursor to the scene method
    // showing the cursor symbol
    // presseing place creature button -- creating creature and placing it on the active tile
    // checking creature type and tile type, if error show window with error, that explains

    // adding visible creatures to the scene using the creaturesOnTile and NOT the list from gamemodel
};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class LandscapeGrid{
public: LandscapeGrid() = delete;
public: static std::vector<std::vector<LandscapeTile>> createLandscapeGrid
    (unsigned int sizehorizontal, unsigned int sizevertical);
};

#endif // LANDSCAPE_HPP
