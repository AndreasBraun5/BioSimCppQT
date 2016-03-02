/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Explanation & collection of all self defined exceptions used in BioSim.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// #include <iostream>
#include <exception>

class invalidHeader : public std::exception{
    virtual const char* what() const throw(){
        return "InvalidHeader: Not supported TGA properties. "
               "See imageTGA.cpp for more information./n";
    }
};

class onlySqareImages : public std::exception{
    virtual const char* what() const throw(){
        return "OnlySqareImages: Only square images are allowed./n";
    }
};

class falseBitsPerPixel : public std::exception{
    virtual const char* what() const throw(){
        return "FalseBitsPerPixel: Allowed bitsPerPixel are 24(RGB) and 32(RGB(A))./n";
    }
};

class imageTooBig : public std::exception{
    virtual const char* what() const throw(){
        return "ImageTooBig: Maximum image size exceeded./n";
    }
};

class corruptImageData : public std::exception{
    virtual const char* what() const throw(){
        return "CorruptImageData: Expected imageDataSize does not match read Bytes from stream.";
    }
};

class badImageFilePath : public std::exception{
    virtual const char* what() const throw() {
        return "BadImageFilePath: The given file path is incorrect.";
    }
};


class badTextFilePath : public std::exception{
    virtual const char* what() const throw() {
        return "BadTextFilePath: The given file path is incorrect.";
    }
};

#endif // EXCEPTIONS_H
