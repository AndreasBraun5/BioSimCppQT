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


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helperMethods /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
unsigned int readByteFromStream(std::ifstream imageStream, unsigned int numberOfByte);

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

    std::vector<unsigned int> tempTgaHeader;
    std::vector< std::vector <unsigned long int> > tempImageData;

    std::ifstream imageStream(imagePath, std::ifstream::binary);
    while(imageStream.good()){
        //tempTgaHeader[0] = readByteFromStream(&imageStream, 1);
        // do for all 12 header entries, TODO not working...

        // works fine
        //char * buffer = new char[2];
        //imageStream.get(buffer,1);
        //unsigned int temp = static_cast<unsigned int> (*buffer);

        // check if, throws notSupportedTgaProperties
        if(tempTgaHeader[0] != 0) // imageIDLength = 0
        if(tempTgaHeader[1] != 0) // colourPalletType = 0
        if(tempTgaHeader[2] != 2) // imageType = 2
        if(tempTgaHeader[3] != 0) // palletStart = 0
        if(tempTgaHeader[4] != 0) // palletLength = 0
        // if(tempTgaHeader[5] != 0) // sizePerBitsOfEachPalletEntry
        if(tempTgaHeader[6] != 0) // zeroPointX = 0
        if(tempTgaHeader[7] != 0) // zeroPointY = 0

        // throws onlySquareImagesAllowed
        // if(tempTgaHeader[8] != 0) // imageWidth
        // if(tempTgaHeader[9] != 0) // imageHeigth

        int numberOfPixels = tempTgaHeader[8]*tempTgaHeader[9]; // imageWidth*imageHeigth
        //int imageDataToReadInByte = numberOfPixels*4;
        if(tempTgaHeader[10] = 24); // RGB
        else if(tempTgaHeader[10] = 32); // RGB(A)
        else ; // throws corruptImage

     }

    imageStream.close();
    return ImageTga(tempTgaHeader,tempImageData);
}

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helperMethods /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
unsigned int readByteFromStream(std::ifstream &imageStream, unsigned int numberOfBytes){
    char * buffer = new char[2]; // is getting saved into vector <unsigned long int>
    imageStream.get(buffer, numberOfBytes);
    // oder mit .read(whatKindOfVariableToRead, sizeToReadFromBuffer);
    unsigned int temp = static_cast<unsigned int> (*buffer);
    return temp;
};
