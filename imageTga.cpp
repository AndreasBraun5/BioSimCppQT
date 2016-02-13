/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    TODO loading of a correct TGA-image into the RAM
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "imageTga.h"
#include <fstream>
#include "exceptions.h"
#include <vector>


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helperMethods /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
unsigned int readByteFromStream(std::ifstream &imageStream, unsigned int numberOfByte);
Pixel readPixel(unsigned int byteToReadPerPixel, std::ifstream &imageStream);

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ constructor /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
ImageTga::ImageTga(std::vector<unsigned int> tgaHeader,
                   std::vector< std::vector <unsigned long int> > imageData  ){
    this->tgaHeader=tgaHeader;
    this->imageData=imageData;
}



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ createCorrectImage /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// return Image
// TODO error checking
ImageTga ImageTga::createCorrectImage(const std::string imagePath){

    std::vector<unsigned int> tempTgaHeader(12);
    std::vector< std::vector <unsigned long int> > tempImageData;

    unsigned int numberOfPixels;
    unsigned int byteToReadPerPixel;

    std::ifstream imageStream(imagePath, std::ifstream::binary);
    while(imageStream.good()){

        tempTgaHeader[0] = readByteFromStream(imageStream, 1); // imageIDLength
        tempTgaHeader[1] = readByteFromStream(imageStream, 1); // colourPalletType
        tempTgaHeader[2] = readByteFromStream(imageStream, 1); // imageType
        tempTgaHeader[3] = readByteFromStream(imageStream, 2); // palletStart
        tempTgaHeader[4] = readByteFromStream(imageStream, 2); // palletLength
        tempTgaHeader[5] = readByteFromStream(imageStream, 1); // sizePerBitsOfEachPalletEntry
        tempTgaHeader[6] = readByteFromStream(imageStream, 2); // zeroPointX
        tempTgaHeader[7] = readByteFromStream(imageStream, 2); // zeroPointY
        tempTgaHeader[8] = readByteFromStream(imageStream, 2); // imageWidth
        tempTgaHeader[9] = readByteFromStream(imageStream, 2); // imageHeigth
        tempTgaHeader[10] = readByteFromStream(imageStream, 1); // bitsPerPixel
        tempTgaHeader[11] = readByteFromStream(imageStream, 1); // imageAttributeType
        // imageID is nonexistent
        // colourPallet is nonexistent


        if(tempTgaHeader[0] != 0) throw invalidHeader(); // imageIDLength = 0 --> imageID is nonexistent
        if(tempTgaHeader[1] != 0) throw invalidHeader();// colourPalletType = 0 --> colourPallet is nonexistent
        if(tempTgaHeader[2] != 2) throw invalidHeader();// imageType = 2
        if(tempTgaHeader[3] != 0) throw invalidHeader();// palletStart = 0
        if(tempTgaHeader[4] != 0) throw invalidHeader();// palletLength = 0
        // if(tempTgaHeader[5] != ??) // sizePerBitsOfEachPalletEntry: nothing explicitly specified
        if(tempTgaHeader[6] != 0) throw invalidHeader();// zeroPointX = 0
        if(tempTgaHeader[7] != 0) throw invalidHeader();// zeroPointY = 0
        if(tempTgaHeader[8] != tempTgaHeader[9]) throw onlySqareImages();  // imageWidth=imageHeigth

        if(tempTgaHeader[10] = 24){ // bitsPerPixel = 24 = RGB
            byteToReadPerPixel = 3;}
        else if(tempTgaHeader[10] = 32){ // bitsPerPixel = 32 = RGB(A)
            byteToReadPerPixel = 4;}
        else{throw falseBitsPerPixel();}
        // if(tempTgaHeader[11] != ??) // imageAttributeType: nothing explicitly specified

        // Reading imageData
        numberOfPixels = tempTgaHeader[8]*tempTgaHeader[9]; // only square images. So it is imageWidth*imageHeigth

        tempImageData;

    }

    imageStream.close();
    return ImageTga(tempTgaHeader,tempImageData);
}

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helperMethods /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
unsigned int readByteFromStream(std::ifstream &imageStream, unsigned int numberOfBytes){
    char * buffer = new char[numberOfBytes]; // is getting saved into vector <unsigned long int>
    imageStream.read(buffer, numberOfBytes);
    // oder mit .read(whatKindOfVariableToRead, sizeToReadFromBuffer);
    unsigned int temp = static_cast<unsigned int> (*buffer);
    return temp;
};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class Pixel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
Pixel::Pixel(unsigned int Rvalue, unsigned int Gvalue, unsigned int Bvalue){
    pixelValues[0] = Rvalue;
    pixelValues[1] = Gvalue;
    pixelValues[2] = Bvalue;
    pixelValues[3] = 255; // maximum A by default 255
}

Pixel::Pixel(unsigned int Rvalue, unsigned int Gvalue, unsigned int Bvalue, unsigned int Avalue){
    pixelValues[0] = Rvalue;
    pixelValues[1] = Gvalue;
    pixelValues[2] = Bvalue;
    pixelValues[3] = Avalue;
}

Pixel readPixel(unsigned int byteToReadPerPixel, std::ifstream &imageStream){
    unsigned int tempRvalue;

    Pixel pixel = Pixel::Pixel(1,1,1);

    for(int i = 0; i <= byteToReadPerPixel; i++){
        readByteFromStream(imageStream, 1);

    }
    return pixel;
}

std::vector <unsigned int> Pixel::getPixelValues() const
{
    return pixelValues;
}









