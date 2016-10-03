/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "imagetga.hpp"

#include <fstream>
#include <vector>
#include <iostream>

#include "exceptions.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/

std::vector<unsigned char> ImageTga::createImageVector(const std::string &imagePath) {

    std::vector<unsigned int> tempTgaHeader(12);
    char bufferTgaHeaderUnformatted[18];
    std::vector<unsigned char> tempImageData; //TODO Note: with temporary length of one (1)... ??

    unsigned int numberOfPixels;
    unsigned int byteToReadPerPixel;
    unsigned int charsToReadFromStreamForImageData;

    std::ifstream imageStream(imagePath, std::ifstream::binary);
    if(!imageStream.good()) throw badImageFilePath();

    // reading and checking header //
    imageStream.read(bufferTgaHeaderUnformatted, 18);
    if(imageStream.gcount() != 18){throw wrongNumberOfBytesRead();}


    // imageIDLength = 0 --> imageID is nonexistent
    tempTgaHeader[0] = bufferTgaHeaderUnformatted[0];
    if(tempTgaHeader[0] != 0) {throw invalidHeader();}

    // colourPalletType = 0 --> colourPallet is nonexistent
    tempTgaHeader[1] = bufferTgaHeaderUnformatted[1];
    if(tempTgaHeader[1] != 0) {throw invalidHeader();}

    // imageType
    tempTgaHeader[2] = bufferTgaHeaderUnformatted[2];
    if(tempTgaHeader[2] != 2) {throw invalidHeader();}

    // palletStart
    tempTgaHeader[3] = bufferTgaHeaderUnformatted[3] + bufferTgaHeaderUnformatted[4];
    if(tempTgaHeader[3] != 0) {throw invalidHeader();}

    // palletLength
    tempTgaHeader[4] = bufferTgaHeaderUnformatted[5] + bufferTgaHeaderUnformatted[6];
    if(tempTgaHeader[4] != 0) {throw invalidHeader();}

    // sizePerBitsOfEachPalletEntry: nothing explicitly specified
    tempTgaHeader[5] = bufferTgaHeaderUnformatted[7];
    // if(tempTgaHeader[5] != ??)

    // zeroPointX
    tempTgaHeader[6] = bufferTgaHeaderUnformatted[8] + bufferTgaHeaderUnformatted[9];
    if(tempTgaHeader[6] != 0) {throw invalidHeader();}

    // zeroPointY
    tempTgaHeader[7] = bufferTgaHeaderUnformatted[10] + bufferTgaHeaderUnformatted[11];
    if(tempTgaHeader[7] != 0) {throw invalidHeader();}

    // imageWidth + imageHeigth
    tempTgaHeader[8] = bufferTgaHeaderUnformatted[12] + bufferTgaHeaderUnformatted[13];
    tempTgaHeader[9] = bufferTgaHeaderUnformatted[14] + bufferTgaHeaderUnformatted[15];
    if(tempTgaHeader[8] != tempTgaHeader[9]) {throw onlySqareImages();}

    // bitsPerPixel
    tempTgaHeader[10] = bufferTgaHeaderUnformatted[16];
    if(tempTgaHeader[10] == 24) {
        // 24 = RGB
        byteToReadPerPixel = 3;
    } else if(tempTgaHeader[10] == 32) {
        // 32 = RGB(A)
        byteToReadPerPixel = 4;
    } else {
        throw falseBitsPerPixel();
    }

    // imageAttributeType: nothing explicitly specified
    tempTgaHeader[11] = bufferTgaHeaderUnformatted[17];
    // if(tempTgaHeader[11] != ??)


    // limitation of image size. Symbolic value of 10kBytes (maximum value needed to load all used images)
    if( byteToReadPerPixel > 10000) {throw invalidHeader();}


    // reading imageData
    numberOfPixels = tempTgaHeader[8] * tempTgaHeader[9]; // only square images supported
    charsToReadFromStreamForImageData = numberOfPixels * byteToReadPerPixel;
    char *bufferImageDataUnformatted =  new char[numberOfPixels * 4]; // always 4 byte per pixel              // !delete bufferImageDataUnformatted
    imageStream.read(bufferImageDataUnformatted, charsToReadFromStreamForImageData);
    if(imageStream.gcount() != charsToReadFromStreamForImageData){throw wrongNumberOfBytesRead();}


    // Bytes are ordered as BGR(A) in bufferImageDataUnformatted
    // --> reorganizing as aplpha-RGB planned, because constructor of QImage is
    // QImage::QImage(uchar * data, int width, int height, Format format) and
    // Format is used QImage::Format_ARGB32, equals int value 5. (The image is stored using
    // a 32-bit ARGB format (0xAARRGGBB)." !!!BUT!!!: It is not taken the ordering within the vector
    // data structure but the one directly in the RAM. Therefore because of the endianess the
    // values are stored without a reorganization.
    if(byteToReadPerPixel == 3) {
        for(unsigned int i = 0; i < charsToReadFromStreamForImageData; i = i + 3) {
            tempImageData.push_back(bufferImageDataUnformatted[i + 0]);
            tempImageData.push_back(bufferImageDataUnformatted[i + 1]);
            tempImageData.push_back(bufferImageDataUnformatted[i + 2]);
            tempImageData.push_back(255);
        }
    } else { // byteToReadPerPixel == 4
        for(unsigned int i = 0; i < charsToReadFromStreamForImageData ; i = i + 4) {
            tempImageData.push_back(bufferImageDataUnformatted[i + 0]);
            tempImageData.push_back(bufferImageDataUnformatted[i + 1]);
            tempImageData.push_back(bufferImageDataUnformatted[i + 2]);
            tempImageData.push_back(bufferImageDataUnformatted[i + 3]);
        }
    }

    delete[] bufferImageDataUnformatted;                                                                    // !delete bufferImageDataUnformatted
    if(numberOfPixels * 4 != tempImageData.size()) throw corruptImageData();
    imageStream.close();
    //return ImageTga(tempImageData);
    return tempImageData;
}


