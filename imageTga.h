/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    TODO loading of a correct TGA-image into the RAM
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
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ImageTga{

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


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ variables /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private:    static int imageCount;   // further use for checking total number of read images

    // represents TGA
    // 16 bits and positive --> unsigned int
private:    std::vector<unsigned int> tgaHeader;

    // imageData, idea mutlilevel or multidimensional storage, break if imageWitdth*imageHeigth*...
    // saved as RGB(A) with 1 Byte per channel
    // 32 bits and positive --> unsigned long int
    // Alpha-channel maybe not given
private:    std::vector< std::vector <unsigned long int> > imageData; // [1]


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ constructor: after checking CreateCorrectImage /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     ImageTga() = delete;
private:    ImageTga(std::vector<unsigned int> tgaHeader,
                     std::vector< std::vector <unsigned long int> > imageData  );

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ createCorrectImage: ... /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public:     static ImageTga createCorrectImage(const std::string imagePath);


};

class Pixel{
private:    std::vector <unsigned int> pixelValues;

public:     Pixel(unsigned int Rvalue, unsigned int Gvalue, unsigned int Bvalue);
    Pixel(unsigned int Rvalue, unsigned int Gvalue, unsigned int Bvalue, unsigned int Avalue);

    //pixelValues[0] = Rvalue;
    //pixelValues[1] = Gvalue;
    //pixelValues[2] = Bvalue;
    //pixelValues[3] = Avalue; // by default 255
    std::vector <unsigned int> getPixelValues() const;

};


#endif // IMAGE_H
