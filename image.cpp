/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*/
    TODO loading of a correct TGA-image into the RAM
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "image.h"
#include <fstream>


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
Image::Image(const std::string imagePath){
    Image::openImage(imagePath);
    readImageHeader();
    loadImage();
}

Image::~Image(){

}

static void Image::openImage(const std::string imagePath){
    std::ifstream ifs(imagePath, std::ifstream::binary);
    while(ifs.good()){

    }
}

static bool Image::readImageHeader(){

}

static void Image::loadImage(){

}
