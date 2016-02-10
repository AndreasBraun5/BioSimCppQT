/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*/
    TODO description
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#ifndef IMAGE_H
#define IMAGE_H

//#include


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class Image{

/*/ TGA fileheader = 12 informations (see wikipedia TGA)
 *  followed by imageID and imagePalletType (don´t exist)
 *  followed by the image data
/*/

/*  a) Die Bilddatei muss im TGA-Format gelesen werden können.


    b) Das Resultat des Einlesevorgangs soll eine Instanz einer ebenfalls zu entwickelnden
    Bild-Klasse sein. In dieser Klasse sollen RGB(A)-Daten mit einem Byte pro
    Farbkanal und Pixel vorgehalten werden. Der Ladevorgang soll durch statische
    Methoden innerhalb der Bild-Klasse umgesetzt werden.


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


Google-Stichwörter
ifstream binary, auto_pointer, vector, tga tutorial, RAII
*/
public: Image(){
    }

// represents TGA
public: int imageIDLength;       // 1 Byte, is zero --> no imageID
        int colourPalletType;    // 1 Byte, is zero --> no colourPalletType
        int imageType;           // 1 Byte, is two --> RGB 24 bit uncompressed
        int palletStart;         // 16 bits, is zero
        int palletLength;        // 16 bits, is zero
        int sizePerBitsOfEachPalletEntry;    // 1 Byte
        int zeroPointX;          // 16 bits, is zero
        int zeroPointY;          // 16 bits, is zero
        int imageWidth;          // 16 bits
        int imagaHeigth;         // 16 bis
        int bitsPerPixel;        // 1 Byte, is 24 or 32
        int imageAttributeType;  // 1 Byte
        //int imageID;           // nonexistent
        //int colourPallet;      // nonexistent
        //imageData, idea mutlilevel or multidimensional storage, break if imageWitdth*imageHeigth
};
// Nach dem Einlesen des Bilddaten-Blocks mit Pixelfarben kann der Einlesevorgang
// abgebrochen werden. Weitere Metainformationen sind nicht zu lesen.








#endif // IMAGE_H
