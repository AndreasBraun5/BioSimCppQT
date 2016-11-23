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
    // TODO Note: add operator= and copy-constructor are not generated implicitly because of const properties
    // operator = (and copy constructor) must be implemented

    // TODO: All stuff to do for AB5

    // all creatures that are added here must be the same (or only a reference/pointer) that are stored in the gamemodel.

    // deleting a creature in the gamemodel must result in deleting the creature on the tile and vice versa

    // TODO Discuss: Now I have the same Creatures for the Possible Creatures and the Creature Objects being placed onto the grid.

    // TODO Discuss: make map["key"] with enum, well only practicable for the tiles via using an extra std::map<int, QImage>. But why to do so?
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
