/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*/
    TODO loading of a correct TGA-image into the RAM
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class Image{

/*/ TGA fileheader = 12 informations (see wikipedia TGA)
 *  followed by imageID and imagePalletType (don´t exist here)
 *  followed by the image data
/*/

/*/ b) Das Resultat des Einlesevorgangs soll eine Instanz einer ebenfalls zu entwickelnden
    Bild-Klasse sein. In dieser Klasse sollen RGB(A)-Daten mit einem Byte pro
    Farbkanal und Pixel vorgehalten werden. Der Ladevorgang soll durch statische
    Methoden innerhalb der Bild-Klasse umgesetzt werden.
        RGB (A) 1B for each colour Red, Green, Blue and 1B for Alpha-chanel == 4B == 32bits per pixel


    c) Beim Schreiben der Bild-Klasse ist ein C++-übliches Vorgehen zu nutzen,
    insbesondere das RAII-Pattern (Resource acquisition is initialization) zum Vermeiden
    ungültiger Klassenzustände. In anderen Worten, eine Konstruktion eines Bildes soll
    bereits vollständige Parameter erfordern. Fehlerzustände müssen im Konstruktor
    erkannt und ungültige Klasseninstanzen durch Ausnahmebehandlung vermieden
    werden. Die Bildklasse soll Speicher intern automatisch verwalten und bei
    Zerstörung eines Bildobjekts automatisch freigeben.


    d) Korrupte oder nicht unterstützte Bilddaten sind zu erkennen und über geeignete
    Mechanismen (Exceptions) zu propagieren. Speicherlecks sind zu vermeiden,
    ebenfalls sind offene Dateien korrekt zu schliessen.


    e) Redundanzen im Code sind durch geschickte Funktionsaufteilung zu vermeiden. Alle
    Variablen, Methoden, und Klassen sind entsprechend dem Anwendungs-Kontext
    sinnvoll zu benennen. Dokumentation und Formatierung analog zur ersten Aufgabe.

    // Nach dem Einlesen des Bilddaten-Blocks mit Pixelfarben kann der Einlesevorgang
    // abgebrochen werden. Weitere Metainformationen sind nicht zu lesen.

    Google-Stichwörter
    ifstream binary:
    auto_pointer/unique_ptr: limited garbage collection facility
    vector: sequence containers representing arrays that can change in size
    RAII: Dabei wird die Belegung von Betriebsmitteln an den Konstruktoraufruf einer Variablen
        eines benutzerdefinierten Typs und die Freigabe der Betriebsmittel an dessen
        Destruktoraufruf gebunden. Die automatische Freigabe wird beispielsweise durch das
        Verlassen des Gültigkeitsbereichs ausgelöst.
    tga tutorial:
/*/

private:    static int imageCount;   // further use for checking total number of read images

// represents TGA
// 16 bits and positive --> unsigned int
private: std::vector<unsigned int> tgaHeader[12];
            // 01 int imageIDLength;       // 1 Byte, is zero --> no imageID
            // 02 int colourPalletType;    // 1 Byte, is zero --> no colourPalletType
            // 03 int imageType;           // 1 Byte, is two --> RGB 24 bit uncompressed
            // 04 int palletStart;         // 16 bits, is zero
            // 05 int palletLength;        // 16 bits, is zero
            // 06 int sizePerBitsOfEachPalletEntry;    // 1 Byte
            // 07 int zeroPointX;          // 16 bits, is zero
            // 08 int zeroPointY;          // 16 bits, is zero
            // 09 int imageWidth;          // 16 bits
            // 10 int imageHeigth;         // 16 bits
            // 11 int bitsPerPixel;        // 1 Byte, is 24 or 32, maybe there is no Alpha-channel
            // 12 int imageAttributeType;  // 1 Byte
            //    int imageID;             // nonexistent --> not in tgaHeader
            //    int colourPallet;        // nonexistent --> not in tgaHeader

// imageData, idea mutlilevel or multidimensional storage, break if imageWitdth*imageHeigth*...
// saved as RGB(A) with 1 Byte per channel
// 32 bits and positive --> unsigned long int
// Alpha-channel maybe not given
private: std::vector< std::vector <unsigned long int> > imageData; // [1]

// RAII: call readImageHeader()
public: Image(const std::string imagePath);
// RAII: auto free images from RAM
public: ~Image();

// try to access image, exceptions
private: static void openImage(const std::string imagePath);

// throws exceptions if there is a not supported property in the file
private: static void readImageHeader();

// loading image to RAM
private: static void loadImage();

};
#endif // IMAGE_H
