/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    landscape
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "landscape.hpp"
#include <libnoise/noise.h>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
LandscapeTile::LandscapeTile(ClimateType climate)
    : climate(climate){
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
std::vector<std::vector<LandscapeTile> > LandscapeGrid::createLandscapeGrid
(unsigned int sizehorizontal, unsigned int sizevertical) {

    std::vector<std::vector<LandscapeTile>> a;

    LandscapeTile shallowWaterTile(SHALLOW_WATER);
    LandscapeTile deepSeaTile(DEEP_SEA);
    LandscapeTile sandTile(SAND);
    LandscapeTile rocksTile(ROCKS);

    std::vector<LandscapeTile> row1 = {shallowWaterTile, deepSeaTile};
    std::vector<LandscapeTile> row2 = {sandTile, rocksTile};

    return a;
}
