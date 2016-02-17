/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef IMAGE_H
#define IMAGE_H


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <vector>



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class Pixel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class Pixel{


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ variables /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private:    std::vector <unsigned char> pixelValues;


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ constructor: after checking CreateCorrectImage /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     Pixel(unsigned char Rvalue, unsigned char Gvalue, unsigned char Bvalue, unsigned char Avalue);


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ getPixelValues: returns pixelValues ascending as following: RGB(A) /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    std::vector <unsigned char> getPixelValues() const;
};



    //auto_pointer/unique_ptr: limited garbage collection facility ??
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga{


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ variables /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private:    std::vector<unsigned int> tgaHeader;    // 18 Byte size
private:    std::vector<Pixel> imageData;           // saved as following with 1 byte of each RGB(A). 4 byte = 1 pixel.


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ constructor: after checking CreateCorrectImage /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     ImageTga() = delete;
private:    ImageTga(std::vector<unsigned int> tgaHeader,
                     std::vector<Pixel> imageData  );


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ createCorrectImage: static method for creating a image. The created image is always
     *  a valid one. Different types of errors are excluded before creating. Therefore no
     *  corrupt image can be constructed /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     static ImageTga createCorrectImage(const std::string imagePath);

};


#endif // IMAGE_H
