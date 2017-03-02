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
