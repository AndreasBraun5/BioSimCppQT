/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Explanation & collection of all self defined exceptions used in BioSim.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <iostream>
#include <exception>

class invalidHeader : public std::exception{
    virtual const char* what() const throw(){
        return "InvalidHeader: Not supported TGA properties. "
               "See imageTGA.cpp for more information";
    }
};

class onlySqareImages : public std::exception{
    virtual const char* what() const throw(){
        return "OnlySqareImages: Only square images are allowed.";
    }
};

class falseBitsPerPixel : public std::exception{
    virtual const char* what() const throw(){
        return "FalseBitsPerPixel: Allowed bitsPerPixel are 24(RGB) and 32(RGB(A))";
    }
};

class imageTooBig : public std::exception{
    virtual const char* what() const throw(){
        return "ImageTooBig: Maximum image size exceeded";
    }
};

class corruptImageData : public std::exception{
    virtual const char* what() const throw(){
        return "CorruptImageData: Expected imageDataSize doesn´t match read Bytes from steam.";
    }
};


#endif // EXCEPTIONS_H
