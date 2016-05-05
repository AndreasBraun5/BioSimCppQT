/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Explanation & collection of all self defined exceptions used in BioSim.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_EXCEPTIONS_HPP
#define INCLUDED_BIOSIM_EXCEPTIONS_HPP

#include <exception>

// TODO Note: make more specific exceptions possible?

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ exceptions used by TextFileReader.hpp /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class badTextFilePath : public std::exception{
public:    virtual const char* what() const throw() {
        return "BadTextFilePath: The given file path is incorrect.";
    }
};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ exceptions used by ImageTga.hpp /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/

class invalidHeader : public std::exception{
    virtual const char* what() const throw(){
        return "InvalidHeader: Not supported TGA properties. "
               "See imageTGA.cpp for more information.";
    }
};

class onlySqareImages : public std::exception{
    virtual const char* what() const throw(){
        return "OnlySqareImages: Only square images are allowed.";
    }
};

class falseBitsPerPixel : public std::exception{
    virtual const char* what() const throw(){
        return "FalseBitsPerPixel: Allowed bitsPerPixel are 24(RGB) and 32(RGB(A)).";
    }
};

class imageTooBig : public std::exception{
    virtual const char* what() const throw(){
        return "ImageTooBig: Maximum image size exceeded.";
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

class wrongNumberOfBytesRead : public std::exception{
    virtual const char* what() const throw() {
        return "WrongNumberOfBytesRead: The read number of bytes is incorrect.";
    }
};

#endif // EXCEPTIONS_HPP
