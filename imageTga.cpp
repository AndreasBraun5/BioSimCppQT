/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    Loading of a correct TGA-image into the RAM.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "imagetga.h"
#include <fstream>
#include "exceptions.h"
#include <vector>
#include <QImage>



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class Pixel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
Pixel::Pixel(unsigned char Rvalue, unsigned char Gvalue, unsigned char Bvalue, unsigned char Avalue){
    pixelValues.push_back(Rvalue);
    pixelValues.push_back(Gvalue);
    pixelValues.push_back(Bvalue);
    pixelValues.push_back(Avalue);
}

std::vector<unsigned char> Pixel::getPixelValues() const { return this->pixelValues;}



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ImageTga /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
ImageTga::ImageTga(std::vector<unsigned int> tgaHeader,
                   std::vector<Pixel> imageData  ){
    this->tgaHeader=tgaHeader;
    this->imageData=imageData;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ createCorrectImage /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
ImageTga ImageTga::createCorrectImage(const std::string imagePath){

    std::vector<unsigned int> tempTgaHeader(12);
    char bufferTgaHeaderUnformatted[18];
    std::vector<Pixel> tempImageData;

    unsigned int numberOfPixels;
    unsigned int byteToReadPerPixel;
    unsigned int charsToReadFromStreamForImageData;

    std::ifstream imageStream(imagePath, std::ifstream::binary);
    bool goodStream = imageStream.good();
    if(goodStream == false) throw badImageFilePath();
    while(goodStream){


        // reading header
        imageStream.read(bufferTgaHeaderUnformatted, 18);
        tempTgaHeader[0] = bufferTgaHeaderUnformatted[0];                                       // imageIDLength
        tempTgaHeader[1] = bufferTgaHeaderUnformatted[1];                                       // colourPalletType
        tempTgaHeader[2] = bufferTgaHeaderUnformatted[2];                                       // imageType
        tempTgaHeader[3] = bufferTgaHeaderUnformatted[3] + bufferTgaHeaderUnformatted[4];       // palletStart
        tempTgaHeader[4] = bufferTgaHeaderUnformatted[5] + bufferTgaHeaderUnformatted[6];       // palletLength
        tempTgaHeader[5] = bufferTgaHeaderUnformatted[7];                                       // sizePerBitsOfEachPalletEntry
        tempTgaHeader[6] = bufferTgaHeaderUnformatted[8] + bufferTgaHeaderUnformatted[9];       // zeroPointX
        tempTgaHeader[7] = bufferTgaHeaderUnformatted[10] + bufferTgaHeaderUnformatted[11];     // zeroPointY
        tempTgaHeader[8] = bufferTgaHeaderUnformatted[12] + bufferTgaHeaderUnformatted[13];     // imageWidth
        tempTgaHeader[9] = bufferTgaHeaderUnformatted[14] + bufferTgaHeaderUnformatted[15];     // imageHeigth
        tempTgaHeader[10] = bufferTgaHeaderUnformatted[16];                                     // bitsPerPixel
        tempTgaHeader[11] = bufferTgaHeaderUnformatted[17];                                     // imageAttributeType
        // imageID is nonexistent
        // colourPallet is nonexistent

        // checking header
        if(tempTgaHeader[0] != 0) throw invalidHeader();                    // imageIDLength = 0 --> imageID is nonexistent
        if(tempTgaHeader[1] != 0) throw invalidHeader();                    // colourPalletType = 0 --> colourPallet is nonexistent
        if(tempTgaHeader[2] != 2) throw invalidHeader();                    // imageType = 2
        if(tempTgaHeader[3] != 0) throw invalidHeader();                    // palletStart = 0
        if(tempTgaHeader[4] != 0) throw invalidHeader();                    // palletLength = 0
        // if(tempTgaHeader[5] != ??)                                       // sizePerBitsOfEachPalletEntry: nothing explicitly specified
        if(tempTgaHeader[6] != 0) throw invalidHeader();                    // zeroPointX = 0
        if(tempTgaHeader[7] != 0) throw invalidHeader();                    // zeroPointY = 0
        if(tempTgaHeader[8] != tempTgaHeader[9]) throw onlySqareImages();   // imageWidth=imageHeigth
        if(tempTgaHeader[10] = 24){                                         // bitsPerPixel = 24 = RGB
            byteToReadPerPixel = 3;}
        else if(tempTgaHeader[10] = 32){                                    // bitsPerPixel = 32 = RGB(A)
            byteToReadPerPixel = 4;}
        else{throw falseBitsPerPixel();}
        // if(tempTgaHeader[11] != ??)                                      // imageAttributeType: nothing explicitly specified

        // limitation of image size. Symbolic value of 10kBytes (maximum value needed for all used images)
        if( byteToReadPerPixel > 10000) throw invalidHeader();


        // reading imageData
        numberOfPixels = tempTgaHeader[8]*tempTgaHeader[9]; // only square images supported
        charsToReadFromStreamForImageData = numberOfPixels*byteToReadPerPixel;
        char *bufferImageDataUnformatted =  new char[numberOfPixels*4]; // always 4 byte per pixel              // !delete bufferImageDataUnformatted
        imageStream.read(bufferImageDataUnformatted, charsToReadFromStreamForImageData);


        // Bytes are ordered as BGR(A) in usigned char bufferImageDataUnformatted[i]
        // --> RGB(A) in Pixel whereas each is safed in Pixel tempImageData[i]
        if(byteToReadPerPixel == 3){
            for(unsigned int i=0; i<charsToReadFromStreamForImageData ; i=i+3){
                Pixel pixel = Pixel(bufferImageDataUnformatted[i+2],
                        bufferImageDataUnformatted[i+1],
                        bufferImageDataUnformatted[i+0],
                        255);                                       // [Pixel(R,G,B,A)]
                tempImageData.push_back(pixel) ;
             }
        } else { // byteToReadPerPixel == 4
            for(unsigned int i=0; i<charsToReadFromStreamForImageData ; i=i+4){
                Pixel pixel = Pixel(bufferImageDataUnformatted[i+3],
                        bufferImageDataUnformatted[i+2],
                        bufferImageDataUnformatted[i+1],
                        bufferImageDataUnformatted[i+0]);           // [Pixel(R,G,B,A)]
                tempImageData.push_back(pixel) ;
            }
        }

        if(numberOfPixels != tempImageData.size()) throw corruptImageData();

        delete[] bufferImageDataUnformatted;                                                                    // !delete bufferImageDataUnformatted
        imageStream.close();
        goodStream = false;
    }
    return ImageTga(tempTgaHeader, tempImageData);
}


QImage* ImageTga::createCorrectQImage(const std::string imagePath){

    std::vector<unsigned int> tempTgaHeader(12);
    char bufferTgaHeaderUnformatted[18];
    std::vector<unsigned char> tempImageData(1);
    uchar *imageData = &tempImageData.front(); // TODO !!!!
    QImage *tempQImage;

    unsigned int numberOfPixels;
    unsigned int byteToReadPerPixel;
    unsigned int charsToReadFromStreamForImageData;

    std::ifstream imageStream(imagePath, std::ifstream::binary);
    bool goodStream = imageStream.good();
    if(goodStream = false) throw badImageFilePath();
    while(goodStream){


        // reading header
        imageStream.read(bufferTgaHeaderUnformatted, 18);
        tempTgaHeader[0] = bufferTgaHeaderUnformatted[0];                                       // imageIDLength
        tempTgaHeader[1] = bufferTgaHeaderUnformatted[1];                                       // colourPalletType
        tempTgaHeader[2] = bufferTgaHeaderUnformatted[2];                                       // imageType
        tempTgaHeader[3] = bufferTgaHeaderUnformatted[3] + bufferTgaHeaderUnformatted[4];       // palletStart
        tempTgaHeader[4] = bufferTgaHeaderUnformatted[5] + bufferTgaHeaderUnformatted[6];       // palletLength
        tempTgaHeader[5] = bufferTgaHeaderUnformatted[7];                                       // sizePerBitsOfEachPalletEntry
        tempTgaHeader[6] = bufferTgaHeaderUnformatted[8] + bufferTgaHeaderUnformatted[9];       // zeroPointX
        tempTgaHeader[7] = bufferTgaHeaderUnformatted[10] + bufferTgaHeaderUnformatted[11];     // zeroPointY
        tempTgaHeader[8] = bufferTgaHeaderUnformatted[12] + bufferTgaHeaderUnformatted[13];     // imageWidth
        tempTgaHeader[9] = bufferTgaHeaderUnformatted[14] + bufferTgaHeaderUnformatted[15];     // imageHeigth
        tempTgaHeader[10] = bufferTgaHeaderUnformatted[16];                                     // bitsPerPixel
        tempTgaHeader[11] = bufferTgaHeaderUnformatted[17];                                     // imageAttributeType
        // imageID is nonexistent
        // colourPallet is nonexistent

        // checking header
        if(tempTgaHeader[0] != 0) throw invalidHeader();                    // imageIDLength = 0 --> imageID is nonexistent
        if(tempTgaHeader[1] != 0) throw invalidHeader();                    // colourPalletType = 0 --> colourPallet is nonexistent
        if(tempTgaHeader[2] != 2) throw invalidHeader();                    // imageType = 2
        if(tempTgaHeader[3] != 0) throw invalidHeader();                    // palletStart = 0
        if(tempTgaHeader[4] != 0) throw invalidHeader();                    // palletLength = 0
        // if(tempTgaHeader[5] != ??)                                       // sizePerBitsOfEachPalletEntry: nothing explicitly specified
        if(tempTgaHeader[6] != 0) throw invalidHeader();                    // zeroPointX = 0
        if(tempTgaHeader[7] != 0) throw invalidHeader();                    // zeroPointY = 0
        if(tempTgaHeader[8] != tempTgaHeader[9]) throw onlySqareImages();   // imageWidth=imageHeigth
        if(tempTgaHeader[10] = 24){                                         // bitsPerPixel = 24 = RGB
            byteToReadPerPixel = 3;}
        else if(tempTgaHeader[10] = 32){                                    // bitsPerPixel = 32 = RGB(A)
            byteToReadPerPixel = 4;}
        else{throw falseBitsPerPixel();}
        // if(tempTgaHeader[11] != ??)                                      // imageAttributeType: nothing explicitly specified

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
                tempImageData.push_back(tempImageData[i+2]);
                tempImageData.push_back(tempImageData[i+1]);
                tempImageData.push_back(tempImageData[i+0]);
                /*Pixel pixel = Pixel(bufferImageDataUnformatted[i+2],
                        bufferImageDataUnformatted[i+1],
                        bufferImageDataUnformatted[i+0],255);                                       // [Pixel(R,G,B,A)]
                tempImageData.push_back(pixel) ;*/
             }
        } else { // byteToReadPerPixel == 4
            for(unsigned int i=0; i<charsToReadFromStreamForImageData ; i=i+4){
                tempImageData.push_back(tempImageData[i+3]);
                tempImageData.push_back(tempImageData[i+2]);
                tempImageData.push_back(tempImageData[i+1]);
                tempImageData.push_back(tempImageData[i+0]);
                /*Pixel pixel = Pixel(bufferImageDataUnformatted[i+3],
                        bufferImageDataUnformatted[i+2],
                        bufferImageDataUnformatted[i+1],
                        bufferImageDataUnformatted[i+0]);           // [Pixel(R,G,B,A)]
                tempImageData.push_back(pixel) ;*/
            }
        }

        if(numberOfPixels != tempImageData.size()) throw corruptImageData();

        delete[] bufferImageDataUnformatted;                                                                    // !delete bufferImageDataUnformatted
        imageStream.close();
        goodStream = false;
        tempQImage = new QImage(imageData, tempTgaHeader[8], tempTgaHeader[9], QImage::Format_ARGB32);
    }
    return tempQImage;
}

/*      // this is how u cast correctly... -_-
for(int i=0; i<=1000; i++){
    char charTemp = bufferImageDataUnformatted[i];
    unsigned char unsignedCharTemp = bufferImageDataUnformatted[i];
    int intTemp = 0xFF & (int) bufferImageDataUnformatted[i]; //leading 1er abschneiden (per Bitmaske auf das letzte Byte)
    unsigned int unsignedIntTemp = (unsigned int) (unsigned char) bufferImageDataUnformatted[i];
}
*/











