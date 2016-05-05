/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_IMAGE_HPP
#define INCLUDED_BIOSIM_IMAGE_HPP

#include <vector>

#include <QImage>
#include <QPixmap>


// TODO Note: smart pointer, auto_pointer = boost::scoped_ptr or std::unique_ptr, boost::shared_ptr, std::shared_ptr
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga {
public: std::vector<unsigned char> imageDataVector;

public: ImageTga() = delete; // RAII pattern. No zombie image possible
private: ImageTga(const std::vector<unsigned char> imageDataVector);
public: static ImageTga createImageTga(const std::string &imagePath);
};


#endif // IMAGE_HPP
