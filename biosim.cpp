/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim = PRESENTER
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "biosim.hpp"
#include "ui_biosim.h" // generated from biosim.ui form

#include "list"
#include "iostream"

#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QScrollBar>
#include <QResizeEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#include "gamemodel.hpp"
#include "landscape.hpp"

class GridClickablePixmapItem : public QGraphicsPixmapItem {
public :
    GridClickablePixmapItem(const QPixmap &pixmap, int x, int y, GridCursorCallback *cursorCallback = NULL, QGraphicsItem *parent = Q_NULLPTR)
    // calling parent constructor
        : QGraphicsPixmapItem(pixmap, parent) {
        this->cursorCallback = cursorCallback;
        this->x = x;
        this->y = y;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        QGraphicsPixmapItem::mousePressEvent(event);
        if(this->cursorCallback) {
            this->cursorCallback->gridClicked(this->x, this->y);
        }
    }

private:
    GridCursorCallback *cursorCallback;
    int x;
    int y;
};

/*/
void biosim::mousePressEvent(QMouseEvent *event){
    std::cout << "mouse press event biosim" << std::endl;

    //int viewPortWidth = ui->graphicsView->viewport()->width();
    //int viewPortHeight = ui->graphicsView->viewport()->height();

    int scrollBarValueHorizontal = ui->graphicsView->horizontalScrollBar()->value();
    int scrollBarValueVertical = ui->graphicsView->verticalScrollBar()->value();

    int scrollBarValueHorizontalLeft = scrollBarValueHorizontal;
    //int scrollBarValueHorizontalRight = scrollBarValueHorizontal + viewPortWidth;
    int scrollBarValueVerticalUpper = scrollBarValueVertical;
    //int scrollBarValueVerticalDown = scrollBarValueVertical + viewPortHeight;

    scrollBarValueHorizontalLeft = scrollBarValueHorizontalLeft/32;
    //scrollBarValueHorizontalRight = scrollBarValueHorizontalRight/32;
    scrollBarValueVerticalUpper = scrollBarValueVerticalUpper/32;
    //scrollBarValueVerticalDown = scrollBarValueVerticalDown/32;

    // Problem this are not scene coordinates, only coordinates relative to the biosim widget
    QPoint point1  = event->pos();
    std::cout << "Event->pos().x(): " << point1.x() << std::endl;
    std::cout << "Event->pos().y(): " << point1.y() << std::endl;

    // the difference is more to the upper left corner
    // x difference: 26
    // y difference: 38

    int xPos = point1.x() - 26;
    int yPos = point1.y() - 38;
    std::cout << "xPos: " << xPos << std::endl;
    std::cout << "yPos: " << yPos << std::endl;

    QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(*this->cursor, Qt::AutoColor));

    scrollBarValueHorizontalLeft = scrollBarValueHorizontalLeft/32;
    //scrollBarValueHorizontalRight = scrollBarValueHorizontalRight/32;
    scrollBarValueVerticalUpper = scrollBarValueVerticalUpper/32;
    //scrollBarValueVerticalDown = scrollBarValueVerticalDown/32;

    //tempPixmapItem->setOffset(i*32,j*32); // TODO still to calculate
    //scene->addItem(tempPixmapItem);

    this->updateVisibleScene();
}
/*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim) { // initialisation of the private pointer ui of type biosim             // !delete ui
    ui->setupUi(this);
    try {
        this->gamemodel = new GameModel(qApp->arguments().at(1).toStdString());                 // !delete gamemodel auto managed
    } catch(const std::exception &e) {
        writeStartErrorToMsgboxAndExit(e.what());
        exit(EXIT_FAILURE);
    }

    tempCreatureEditing = &gamemodel->creaturesPossibleList.at(0);
    for(int i = 0; i < gamemodel->creaturesPossibleList.size(); i++) {
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel->creaturesPossibleList.at(i).creaturename));
    }
    updateCreatureEditLines(tempCreatureEditing);
    loadQImages();

    // creating scene and adding to graphicsView
    this->scene = new QGraphicsScene(this);                                                    // !delete scene auto managed, by parent
    ui->graphicsView->setScene(scene);

    // creating "empty" QGraphicsScene with specified size
    int qrectfSize = (int) this->gamemodel->landscapeGridmap.size()*32; // always square maps, so this length is ok
    QRectF viewQrectf (0,0,qrectfSize,qrectfSize); // Constructs a rectangle with (x, y) as its top-left corner and the given width and height --> scrollbars have the right size
    ui->graphicsView->setSceneRect(viewQrectf);

    // TODO Note: implement zooming? I guess not :D
    //ui->graphicsView->scale(2, 2);

    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(placeCreature()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateVisibleSceneScrollbar()));
    connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateVisibleSceneScrollbar()));
}

biosim::~biosim() {
    delete ui;                                                                                  // !delete ui
    //delete gamemodel;                    // TODO                                              // !delete gamemodel automanaged
    //  but there is shown an error if i do that. Deleting an already deleted pointer. Something that qt already does
}

void biosim::loadQImages() {
    int imageSizeInPixel = 32;

    //TODO: rotate images...
    imageMap["cursor"] = QImage(gamemodel->cursor.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["dead"] = QImage(gamemodel->dead.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["path"] = QImage(gamemodel->path.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);

    imageMap["deep_sea"] = QImage(gamemodel->deep_sea.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["shallow_water"] = QImage(gamemodel->shallow_water.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["sand"] = QImage(gamemodel->sand.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["earth"] = QImage(gamemodel->earth.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["rocks"] = QImage(gamemodel->rocks.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["snow"] = QImage(gamemodel->snow.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);

    imageMap["birne"] = QImage(gamemodel->birne.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["busch"] = QImage(gamemodel->busch.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["eiche"] = QImage(gamemodel->eiche.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["emu"] = QImage(gamemodel->emu.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["gras"] = QImage(gamemodel->gras.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["hund"] = QImage(gamemodel->hund.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["kaktus"] = QImage(gamemodel->kaktus.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["kuh"] = QImage(gamemodel->kuh.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["pferd"] = QImage(gamemodel->pferd.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["schaf"] = QImage(gamemodel->schaf.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["sonnenblume"] = QImage(gamemodel->sonnenblume.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["tanne"] = QImage(gamemodel->tanne.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["tiger"] = QImage(gamemodel->tiger.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["ursus"] = QImage(gamemodel->ursus.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);

    imageMap["algen"] = QImage(gamemodel->algen.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["delphin"] = QImage(gamemodel->delphin.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["forelle"] = QImage(gamemodel->forelle.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["hai"] = QImage(gamemodel->hai.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["krabbe"] = QImage(gamemodel->krabbe.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["plankton"] = QImage(gamemodel->plankton.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["seetang"] = QImage(gamemodel->seetang.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    imageMap["wels"] = QImage(gamemodel->wels.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
}

void biosim::updateCreatureEditLines(const Creature *tempCreatureEditing) {
    ui->creatureEditingStrengthLineEdit->setText(QString::number(tempCreatureEditing->strength));
    ui->creatureEditingSpeedLineEdit->setText(QString::number(tempCreatureEditing->speed));
    ui->creatureEditingHealthLineEdit->setText(QString::number(tempCreatureEditing->lifetime));
    QString tempProperties;
    for(int i = 0; i < tempCreatureEditing->properties.size();i++) {
        tempProperties.append(QString::fromStdString(tempCreatureEditing->properties[i]));
        tempProperties.append(" ");
    }
    // TODO Note: Too much text in the LineEdit possible.
    ui->creatureEditingPropertiesLineEdit->setText(tempProperties);
}

void biosim::updateCreatureComboBox(int index) {
    tempCreatureEditing = &gamemodel->creaturesPossibleList.at(index);
    updateCreatureEditLines(tempCreatureEditing);
}

void biosim::dumbClick() {
    QMessageBox msg;
    msg.setText("dead end");
    msg.exec();
}

void biosim::placeCreature() {
    // getting the selected creature either due to letting Creature inherit from Qvariant and currentData Property
    // or via the index like here
    int index = ui->creatureEditingComboBox->currentIndex();
    //copying the creature at the index in the list
    Creature tempCreature = this->gamemodel->creaturesPossibleList.at(index);
    tempCreature.positionX = this->cursorX;
    tempCreature.positionY = this->cursorY;

    LandscapeTile *tempTile = &gamemodel->landscapeGridmap[this->cursorX][this->cursorY];

    if(tempCreature.creatureTileType != tempTile->creatureTileType) {
        QMessageBox msg;
        msg.setText("Creature can´t be placed on this Tile!");
        msg.exec();
    } else {
        // adding the creature to the gamemodel and also to the grid.
        gamemodel->creaturesAllOnGrid.append(tempCreature);
        tempTile->creaturesOnTile.push_back(tempCreature);
        // TODO: deleting creatures not implemented
        this->updateVisibleScene();
    }
}

// TODO Note: Be careful with the inheritance hierarchy
void biosim::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    // std::cout << "resize event triggered \n" << std::endl;
    this->updateVisibleScene();
}

void biosim::updateVisibleSceneScrollbar() {
    // std::cout << "\n Call from UpdateVisibleScenceScrollbar: " << std::endl;
    biosim::updateVisibleScene();
}

void biosim::updateVisibleScene() {

    // always the entire scene will be redrawn
    scene->clear();

    // starting values for calculating
    int viewPortWidth = ui->graphicsView->viewport()->width();
    int viewPortHeight = ui->graphicsView->viewport()->height();
    int scrollBarValueHorizontal = ui->graphicsView->horizontalScrollBar()->value();
    int scrollBarValueVertical = ui->graphicsView->verticalScrollBar()->value();
    /*/ debug output for testing
    std::cout << "viewPortWidth: " << viewPortWidth << std::endl;
    std::cout << "viewPortHeight: " << viewPortHeight << std::endl;
    std::cout << "scrollBarValueHorizontal: " << scrollBarValueHorizontal << std::endl;
    std::cout << "scrollBarValueVertical: " << scrollBarValueVertical << std::endl;
    /*/

    // Calculating the four needed values that are used in the for loops
    int scrollBarValueHorizontalLeft = scrollBarValueHorizontal;
    int scrollBarValueHorizontalRight = scrollBarValueHorizontal + viewPortWidth;
    int scrollBarValueVerticalUpper = scrollBarValueVertical;
    int scrollBarValueVerticalDown = scrollBarValueVertical + viewPortHeight;
    /*/ debug output for testing
    std::cout << "scrollBarValueHorizontalLeft: " << scrollBarValueHorizontalLeft << std::endl;
    std::cout << "scrollBarValueHorizontalRight: " << scrollBarValueHorizontalRight << std::endl;
    std::cout << "scrollBarValueVerticalUpper: " << scrollBarValueVerticalUpper << std::endl;
    std::cout << "scrollBarValueVerticalDown: " << scrollBarValueVerticalDown << std::endl;
    /*/

    // Problem now is to determine the coordinate transformation between scrollBarValues and the position of the picture in the grid
    // now the scrollBarValues are in multiple of tiles
    scrollBarValueHorizontalLeft = scrollBarValueHorizontalLeft/32;
    scrollBarValueHorizontalRight = scrollBarValueHorizontalRight/32;
    scrollBarValueVerticalUpper = scrollBarValueVerticalUpper/32;
    scrollBarValueVerticalDown = scrollBarValueVerticalDown/32;
    /*/ debug output for testing
    std::cout << "scrollBarValueHorizontalLeft: " << scrollBarValueHorizontalLeft << std::endl;
    std::cout << "scrollBarValueHorizontalRight: " << scrollBarValueHorizontalRight << std::endl;
    std::cout << "scrollBarValueVerticalUpper: " << scrollBarValueVerticalUpper << std::endl;
    std::cout << "scrollBarValueVerticalDown: " << scrollBarValueVerticalDown << std::endl;
    /*/

    // guaranteeing that the calculated subsripts exists. Needed because with applied method sometimes
    // little bit more than the visible area is being drawn. At the right and down boader this
    // would lead to a vector subscript access out of range.
    if(scrollBarValueHorizontalRight > 499) {
        scrollBarValueHorizontalRight = 499;
        //std::cout << "scrollBarValueHorizontalRightGuaranteed: " << scrollBarValueHorizontalRight << std::endl;
    }
    if(scrollBarValueVerticalDown > 499) {
        scrollBarValueVerticalDown = 499;
        //std::cout << "scrollBarValueVerticalDownGuaranteed: " << scrollBarValueVerticalDown << std::endl;
    }

    // TODO Note: Still need to verify. landscapegrid vector[0][0] (down, left) is being printed to the upper left corner of scene
    for (int i = scrollBarValueHorizontalLeft; i <= scrollBarValueHorizontalRight; i++) {
        for (int j = scrollBarValueVerticalUpper; j <= scrollBarValueVerticalDown; j++) {
            QImage tempImage;
            if(this->gamemodel->landscapeGridmap[i][j].climate == DEEP_SEA)
            {tempImage = imageMap["deep_sea"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SHALLOW_WATER){tempImage = imageMap["shallow_water"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SAND){tempImage = imageMap["sand"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == EARTH){tempImage = imageMap["earth"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == ROCKS){tempImage = imageMap["rocks"];}
            else //this->gamemodel->landscapeGridmap[i][j].climate == SNOW)
            {tempImage = imageMap["snow"];}
            //scene->addPixmap(QPixmap::fromImage(tempImage, Qt::AutoColor)); // Coordinates are default (0,0)
            // only the landscape tiles need to be clickable
            QGraphicsPixmapItem *tempPixmapItem = new GridClickablePixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor), i, j, this);
            tempPixmapItem->setOffset(i*32,j*32);
            scene->addItem(tempPixmapItem);
        }
    }

    //DRAW CURSOR
    QImage tempImage = imageMap["cursor"];
    QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor));
    tempPixmapItem->setOffset(this->cursorX*32,this->cursorY*32);
    scene->addItem(tempPixmapItem);
    std::cout << "x:" << (int) this->cursorX << ", y:" << (int) this->cursorY << "\n" <<std::endl;
    // TODO Note: Output follows here to the console: QGraphicsItem::ungrabMouse: not a mouse grabber
    //  doesn´t matter because the cursor position is set.

    //TODO: using alpha channel
    for (int i = scrollBarValueHorizontalLeft; i <= scrollBarValueHorizontalRight; i++) {
        for (int j = scrollBarValueVerticalUpper; j <= scrollBarValueVerticalDown; j++) {
            if(!this->gamemodel->landscapeGridmap[i][j].creaturesOnTile.empty()){
                for(int k = 0; k < this->gamemodel->landscapeGridmap[i][j].creaturesOnTile.size(); k++){
                    QImage tempImage;
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == BIRNE){tempImage = imageMap["birne"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == BUSCH){tempImage = imageMap["busch"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == EICHE){tempImage = imageMap["eiche"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == EMU){tempImage = imageMap["emu"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == GRAS){tempImage = imageMap["gras"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == HUND){tempImage = imageMap["hund"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == KAKTUS){tempImage = imageMap["kaktus"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == KUH){tempImage = imageMap["kuh"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == PFERD){tempImage = imageMap["pferd"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == SCHAF){tempImage = imageMap["schaf"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == SONNENBLUME){tempImage = imageMap["sonnenblume"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == TANNE){tempImage = imageMap["tanne"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == TIGER){tempImage = imageMap["tiger"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == URSUS){tempImage = imageMap["ursus"];}

                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == ALGEN){tempImage = imageMap["algen"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == DELPHIN){tempImage = imageMap["delphin"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == FORELLE){tempImage = imageMap["forelle"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == HAI){tempImage = imageMap["hai"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == KRABBE){tempImage = imageMap["krabbe"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == PLANKTON){tempImage = imageMap["plankton"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == SEETANG){tempImage = imageMap["seetang"];}
                    if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].type == WELS){tempImage = imageMap["wels"];}
                    QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor));
                    tempPixmapItem->setOffset(i*32,j*32);
                    scene->addItem(tempPixmapItem);
                }
            }
        }
    }
}

void biosim::writeStartErrorToMsgboxAndExit(const std::string &error) {
    QMessageBox msg;
    QString qerror = QString::fromStdString(error);
    msg.setText(qerror);
    msg.exec();
    QApplication::exit();
}
