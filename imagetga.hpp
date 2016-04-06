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
    // TODO AB0: which one is actually needed.
    QImage imageData;
    //QPixmap qPixmap;

    // TODO Note: imagaDatap. Pointer to the QImage data.
    // QImage *imageDatap;


public: ImageTga() = delete; // RAII pattern. No zombie image possible
        ImageTga(const ImageTga &imageTga);
private: ImageTga(const std::vector<unsigned int> &tgaHeader,
                  const QImage &imageData);
public: static ImageTga createCorrectQImage(const std::string &imagePath);
};


#endif // IMAGE_HPP
