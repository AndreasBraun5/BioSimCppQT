/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef IMAGE_H
#define IMAGE_H


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <vector>
#include <qimage.h>


// TODO auto_pointer/unique_ptr: limited garbage collection facility ??
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga{
private:    std::vector<unsigned int> tgaHeader;    // 18 Byte size
private:    QImage imageData;
            //QImage *imageDatap;


public:     ImageTga() = delete;
private:    ImageTga(std::vector<unsigned int> tgaHeader,
                     QImage imageData);

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/  createCorrectImage: static method for creating a image. The created image is always
     *  a valid one. Different types of errors are excluded before creating. Therefore no
     *  corrupt image can be constructed /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     static ImageTga createCorrectQImage(const std::string imagePath);
};


#endif // IMAGE_H
