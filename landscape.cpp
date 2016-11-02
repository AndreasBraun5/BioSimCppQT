/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    landscape
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "landscape.hpp"
#include <libnoise/noise.h>
#include <iostream>
#include <libnoise/noiseutils.h>
#include <stdlib.h>
#include <random>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
LandscapeTile::LandscapeTile(ClimateType climate)
    : climate(climate), creatureTileType(NONE){
    if( climate == DEEP_SEA || climate == SHALLOW_WATER) {
        creatureTileType = WATER;
    } else if (climate == EARTH || climate == ROCKS || climate == SAND || climate == SNOW){
        creatureTileType = TERESTIAL;
    } else { // ROCKS
        creatureTileType = NONE;
    }
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid, using Perlin Noise /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// helper function only needed for qsort here
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

std::vector<std::vector<LandscapeTile> > LandscapeGrid::createLandscapeGrid
(unsigned int sizehorizontal, unsigned int sizevertical) {

    noise::module::Perlin myModule;
    myModule.SetOctaveCount(6); // default value is 6, ranges from 1 to 6.
    myModule.SetFrequency(1.0); // default value is 1.0, ranges from 1.0 to 16.0.
    myModule.SetPersistence(0.5); // default value is 0.5, ranges from 0.0 to 1.0.
    //double value = myModule.GetValue(1.25, 0.75, 0.5);
    //std::cout << "\n" << value << std::endl;
    utils::NoiseMap heightMap;
    //TODO Note: Setting border Value?
    //heightMap.m_borderValue;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(myModule);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(sizehorizontal, sizevertical);
    /*/
     * Not fully understood for what exactly SetBounds is for. As far as I know this kinda
     * sets the bounding rectangle which is rendered out of the infinite perl noise.
     * The documentation says:
     * "You'll also need to specify the (x, z) coordinates of the bounding rectangle.
     * The builder generates the coherent-noise values from the input values contained
     * within this bounding rectangle. These input values are evenly spaced within the rectangle.
     * Because you've set the size of the noise map to 256 x 256, the builder generates
     * 65,536 (256 x 256) coherent-noise values." http://libnoise.sourceforge.net/tutorials/tutorial3.html
     * So it seems, that the rectangle influences withing the GetValue(x,y,z)-method the z value.
     * This in combination with the variable size, are responsible witch type of terrain will be generated
    /*/

    //TODO Discuss: Maybe using random number of a square to setbounds. Now it does sometimes generate deformed/distorted maps.

    // Powered by Start: http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range from user "Walter"
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    int randomnumbers[4];
    for(int i = 0; i < 4; i++){
        std::uniform_int_distribution<int> uni(1,10); // guaranteed unbiased
        int random_integer = uni(rng);
        randomnumbers[i] = random_integer;
    }
    std::qsort(randomnumbers, 4, sizeof(int), compare);
    // Powered by END

    //heightMapBuilder.SetBounds (2.0, 6.0, 1.0, 5.0);
    heightMapBuilder.SetBounds (randomnumbers[0], randomnumbers[2], randomnumbers[1], randomnumbers[3]);
    heightMapBuilder.Build ();

    // TODO Note: If a value outside of the heightMap is called, then the default m_borderValue value is given back.
    std::vector<std::vector<LandscapeTile>> landscapeGridmap(sizehorizontal, std::vector<LandscapeTile> (sizehorizontal, DEEP_SEA));
    for (unsigned int i = 0; i < sizehorizontal; i++) {
        for (unsigned int j = 0; j < sizevertical; j++) {
            double landscapeGridmapvalue = heightMap.GetValue(i,j);
            if(landscapeGridmapvalue < -0.2500){
                landscapeGridmap[i][j] = LandscapeTile(DEEP_SEA);}
            else if(landscapeGridmapvalue >= -0.2500 && landscapeGridmapvalue < 0.0000){landscapeGridmap[i][j] = LandscapeTile(SHALLOW_WATER);}
            else if(landscapeGridmapvalue >= 0.0000 && landscapeGridmapvalue < 0.0625){landscapeGridmap[i][j] = LandscapeTile(SAND);}
            else if(landscapeGridmapvalue >= 0.0625 && landscapeGridmapvalue < 0.7500){landscapeGridmap[i][j] = LandscapeTile(EARTH);}
            else if(landscapeGridmapvalue >= 0.7500 && landscapeGridmapvalue < 0.9000){landscapeGridmap[i][j] = LandscapeTile(ROCKS);}
            else //(landscapeGridmapvalue >= 0.9000)
                {landscapeGridmap[i][j] = LandscapeTile(SNOW);}
         }
     }
    return landscapeGridmap;
}
