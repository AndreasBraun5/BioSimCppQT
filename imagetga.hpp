/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_IMAGE_HPP
#define INCLUDED_BIOSIM_IMAGE_HPP

#include <vector>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga {

public: ImageTga() = delete; // RAII pattern. No zombie image possible
public: static std::vector<unsigned char> createImageVector(const std::string &imagePath);

};


#endif // IMAGE_HPP
