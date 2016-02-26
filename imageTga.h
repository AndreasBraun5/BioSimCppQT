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



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class Pixel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class Pixel{
private:    std::vector <unsigned char> pixelValues;
public:     Pixel(unsigned char Rvalue, unsigned char Gvalue, unsigned char Bvalue, unsigned char Avalue);
    std::vector <unsigned char> getPixelValues() const;
};



// TODO auto_pointer/unique_ptr: limited garbage collection facility ??
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga{
private:    std::vector<unsigned int> tgaHeader;    // 18 Byte size
private:    std::vector<Pixel> imageData;           // saved as following with 1 byte of each RGB(A). 4 byte = 1 pixel.


public:     ImageTga() = delete;
private:    ImageTga(std::vector<unsigned int> tgaHeader,
                     std::vector<Pixel> imageData  );

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/  createCorrectImage: static method for creating a image. The created image is always
     *  a valid one. Different types of errors are excluded before creating. Therefore no
     *  corrupt image can be constructed /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     static ImageTga createCorrectImage(const std::string imagePath);

};


#endif // IMAGE_H
