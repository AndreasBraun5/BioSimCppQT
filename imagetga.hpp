/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_IMAGE_HPP
#define INCLUDED_BIOSIM_IMAGE_HPP

#include <vector>

#include <qimage.h>


// TODO Discuss: smart pointer, auto_pointer = boost::scoped_ptr or std::unique_ptr, boost::shared_ptr, std::shared_ptr
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga {
public: const std::vector<unsigned int> tgaHeader;    // 18 Byte size
    //QScopedPointer<std::vector<unsigned char>> imageDataVector;
    QImage qImage;

public: ImageTga() = delete; // RAII pattern. No zombie image possible
private: ImageTga(const std::vector<unsigned int> &tgaHeader,
                  const QImage &qImage);
public: static ImageTga createCorrectQImage(const std::string &imagePath);
};


#endif // IMAGE_HPP
