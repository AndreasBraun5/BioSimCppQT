/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "imagetga.hpp"

#include <fstream>
#include <vector>

#include <QImage>

#include "exceptions.hpp"


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
ImageTga::ImageTga(std::vector<unsigned int> tgaHeader,
                   QImage imageData  ): tgaHeader(tgaHeader), imageData(imageData){
    //this->imageDatap=&imageData;
}


ImageTga ImageTga::createCorrectQImage(const std::string imagePath){

    std::vector<unsigned int> tempTgaHeader(12);
    char bufferTgaHeaderUnformatted[18];
    std::vector<unsigned char> tempImageData; //TODO with temporary length of one (1)...

    //QImage tempQImage;

    unsigned int numberOfPixels;
    unsigned int byteToReadPerPixel;
    unsigned int charsToReadFromStreamForImageData;

    std::ifstream imageStream(imagePath, std::ifstream::binary);
    bool goodStream = imageStream.good();
    if(goodStream == false) throw badImageFilePath();
    while(goodStream){
        // reading header //
        imageStream.read(bufferTgaHeaderUnformatted, 18);
        // imageIDLength
        tempTgaHeader[0] = bufferTgaHeaderUnformatted[0];
        // colourPalletType
        tempTgaHeader[1] = bufferTgaHeaderUnformatted[1];
        // imageType
        tempTgaHeader[2] = bufferTgaHeaderUnformatted[2];
        // palletStart
        tempTgaHeader[3] = bufferTgaHeaderUnformatted[3] + bufferTgaHeaderUnformatted[4];
        // palletLength
        tempTgaHeader[4] = bufferTgaHeaderUnformatted[5] + bufferTgaHeaderUnformatted[6];
        // sizePerBitsOfEachPalletEntry
        tempTgaHeader[5] = bufferTgaHeaderUnformatted[7];
        // zeroPointX
        tempTgaHeader[6] = bufferTgaHeaderUnformatted[8] + bufferTgaHeaderUnformatted[9];
        // zeroPointY
        tempTgaHeader[7] = bufferTgaHeaderUnformatted[10] + bufferTgaHeaderUnformatted[11];
        // imageWidth
        tempTgaHeader[8] = bufferTgaHeaderUnformatted[12] + bufferTgaHeaderUnformatted[13];
        // imageHeigth
        tempTgaHeader[9] = bufferTgaHeaderUnformatted[14] + bufferTgaHeaderUnformatted[15];
        // bitsPerPixel
        tempTgaHeader[10] = bufferTgaHeaderUnformatted[16];
        // imageAttributeType
        tempTgaHeader[11] = bufferTgaHeaderUnformatted[17];
        // imageID is nonexistent
        // colourPallet is nonexistent

        // checking header //
        // imageIDLength = 0 --> imageID is nonexistent
        if(tempTgaHeader[0] != 0) throw invalidHeader();
        // colourPalletType = 0 --> colourPallet is nonexistent
        if(tempTgaHeader[1] != 0) throw invalidHeader();
        // imageType = 2
        if(tempTgaHeader[2] != 2) throw invalidHeader();
        // palletStart = 0
        if(tempTgaHeader[3] != 0) throw invalidHeader();
        // palletLength = 0
        if(tempTgaHeader[4] != 0) throw invalidHeader();
        // sizePerBitsOfEachPalletEntry: nothing explicitly specified
        // if(tempTgaHeader[5] != ??)
        // zeroPointX = 0
        if(tempTgaHeader[6] != 0) throw invalidHeader();
        // zeroPointY = 0
        if(tempTgaHeader[7] != 0) throw invalidHeader();
        // imageWidth=imageHeigth
        if(tempTgaHeader[8] != tempTgaHeader[9]) throw onlySqareImages();
        // bitsPerPixel
        if(tempTgaHeader[10] = 24) {
            // 24 = RGB
            byteToReadPerPixel = 3;
        } else if(tempTgaHeader[10] = 32) {
            // 32 = RGB(A)
            byteToReadPerPixel = 4;
        }
        else{
            throw falseBitsPerPixel();
        }
        // imageAttributeType: nothing explicitly specified
        // if(tempTgaHeader[11] != ??)

        // limitation of image size. Symbolic value of 10kBytes (maximum value needed to load all used images)
        if( byteToReadPerPixel > 10000) throw invalidHeader();


        // reading imageData
        numberOfPixels = tempTgaHeader[8]*tempTgaHeader[9]; // only square images supported
        charsToReadFromStreamForImageData = numberOfPixels*byteToReadPerPixel;
        char *bufferImageDataUnformatted =  new char[numberOfPixels*4]; // always 4 byte per pixel              // !delete bufferImageDataUnformatted
        imageStream.read(bufferImageDataUnformatted, charsToReadFromStreamForImageData);


        // Bytes are ordered as BGR(A) in usigned char bufferImageDataUnformatted[i]
        // --> reorganizing aplpha-RGB in Pixel whereas each value is safed in Pixel tempImageData
        if(byteToReadPerPixel == 3){
            for(unsigned int i=0; i<charsToReadFromStreamForImageData ; i=i+3){
                tempImageData.push_back(255);
                tempImageData.push_back(bufferImageDataUnformatted[i+2]); // TODO here
                tempImageData.push_back(bufferImageDataUnformatted[i+1]);
                tempImageData.push_back(bufferImageDataUnformatted[i+0]);
            }
        } else { // byteToReadPerPixel == 4
            for(unsigned int i=0; i<charsToReadFromStreamForImageData ; i=i+4){
                tempImageData.push_back(bufferImageDataUnformatted[i+3]);
                tempImageData.push_back(bufferImageDataUnformatted[i+2]);
                tempImageData.push_back(bufferImageDataUnformatted[i+1]);
                tempImageData.push_back(bufferImageDataUnformatted[i+0]);
            }
        }

        if(numberOfPixels*4 != tempImageData.size()) throw corruptImageData();

        delete[] bufferImageDataUnformatted;                                                                    // !delete bufferImageDataUnformatted
        imageStream.close();
        goodStream = false;
    }
    uchar *imageData = &tempImageData.front(); // TODO !!!!
    return ImageTga(tempTgaHeader, QImage(imageData, tempTgaHeader[8], tempTgaHeader[9], QImage::Format_ARGB32));
}

/*      // this is how u cast correctly... -_-
for(int i=0; i<=1000; i++){
    char charTemp = bufferImageDataUnformatted[i];
    unsigned char unsignedCharTemp = bufferImageDataUnformatted[i];
    int intTemp = 0xFF & (int) bufferImageDataUnformatted[i]; //leading 1er abschneiden (per Bitmaske auf das letzte Byte)
    unsigned int unsignedIntTemp = (unsigned int) (unsigned char) bufferImageDataUnformatted[i];
}
*/











