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
#include <QPainter>
#include <QTransform>

#include "gamemodel.hpp"
#include "landscape.hpp"


GridClickablePixmapItem::GridClickablePixmapItem(const QPixmap &pixmap, int x, int y,
                                                 GridCursorCallback *cursorCallback,
                                                 QGraphicsItem *parent)
    : cursorCallback(cursorCallback), x(x), y(y), QGraphicsPixmapItem(pixmap, parent), opacity(1.0) {
}

void GridClickablePixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setOpacity(this->opacity);
    QGraphicsPixmapItem::paint(painter, option, widget);
}


void GridClickablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mousePressEvent(event);
    if(this->cursorCallback) {
        this->cursorCallback->gridClicked(this->x, this->y);
    }
}
// TODO: !!!! after this method is left the error occurs
/*/
void biosim::paintEvent(QPaintEvent *)
{
    QImage tempImage = qImageMap["Baer"];
    QPixmap tempPixmapAlpha =  QPixmap::fromImage(tempImage, Qt::AutoColor);
    QPainter painter(this);
    painter.setOpacity(0.5);
    painter.drawPixmap(0, 0, tempPixmapAlpha);

    /*/
/*/
    // create a new object scaled to widget size
    QPixmap result_avatar = m_avatar.scaled(size());

    QPainter painter(this);
    painter.setOpacity(0.5);
    // use scaled image or if needed not scaled m_avatar
    painter.drawPixmap(0, 0, result_avatar);
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
        this->gamemodel = new GameModel(qApp->arguments().at(1).toStdString());                 // !delete gamemodel
    } catch(const std::exception &e) {
        writeStartErrorToMsgboxAndExit(e.what());
        exit(EXIT_FAILURE);
    }
    try {
        if (!gamemodel->creaturesPossibleList.empty()){
            tempCreatureEditing = &gamemodel->creaturesPossibleList.at(0);
        } else {
            throw noCorrectCreaturesFoundInTextfile(); // TODO Discuss: memory leak here too? No, it should be done with the destructor of biosim being called
        }
    } catch(const std::exception &e) {
        writeStartErrorToMsgboxAndExit(e.what());
        exit(EXIT_FAILURE);
    }
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
    delete gamemodel;                    // TODO Discuss:                                       // !delete gamemodel
    //  but there is shown an error if i do that. Deleting an already deleted pointer. Something that qt already does
}

void biosim::loadQImages() {
    int imageSizeInPixel = 32;

    qImageMap["cursor"] = QImage(gamemodel->imageMap["cursor"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["dead"] = QImage(gamemodel->imageMap["dead"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["path"] = QImage(gamemodel->imageMap["path"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);

    qImageMap["deep_sea"] = QImage(gamemodel->imageMap["deep_sea"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["shallow_water"] = QImage(gamemodel->imageMap["shallow_water"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["sand"] = QImage(gamemodel->imageMap["sand"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["earth"] = QImage(gamemodel->imageMap["earth"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["rocks"] = QImage(gamemodel->imageMap["rocks"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    qImageMap["snow"] = QImage(gamemodel->imageMap["snow"].data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);

    QTransform myTransform;
    myTransform.rotate(180);
    for(int i=0; i<this->gamemodel->creaturesPossibleList.size(); i++) {
        std::string tempCreatureName = this->gamemodel->creaturesPossibleList.at(i).creaturename;
        QImage tempImage = QImage(this->gamemodel->imageMap[tempCreatureName].data(),
                                  imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
        tempImage =  tempImage.transformed(myTransform);
        qImageMap[tempCreatureName] = tempImage;
    }
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
    } else { // adding the creature to the gamemodel and also to the grid.
        gamemodel->creaturesAllOnGrid.append(tempCreature);
        tempTile->creaturesOnTile.push_back(tempCreature);
        // TODO: deleting creatures not implemented
        this->updateVisibleScene();
        std::cout << std::hex << &gamemodel->creaturesAllOnGrid.at(0) << std::endl;
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

    // Calculating the four needed values that are used in the for loops
    int scrollBarValueHorizontalLeft = scrollBarValueHorizontal;
    int scrollBarValueHorizontalRight = scrollBarValueHorizontal + viewPortWidth;
    int scrollBarValueVerticalUpper = scrollBarValueVertical;
    int scrollBarValueVerticalDown = scrollBarValueVertical + viewPortHeight;

    // Problem now is to determine the coordinate transformation between scrollBarValues and the position of the picture in the grid
    // now the scrollBarValues are in multiple of tiles
    scrollBarValueHorizontalLeft = scrollBarValueHorizontalLeft/32;
    scrollBarValueHorizontalRight = scrollBarValueHorizontalRight/32;
    scrollBarValueVerticalUpper = scrollBarValueVerticalUpper/32;
    scrollBarValueVerticalDown = scrollBarValueVerticalDown/32;

    // guaranteeing that the calculated subsripts exists. Needed because with applied method sometimes
    // little bit more than the visible area is being drawn. At the right and down boader this
    // would lead to a vector subscript access out of range.
    if(scrollBarValueHorizontalRight > 499) {
        scrollBarValueHorizontalRight = 499;
    }
    if(scrollBarValueVerticalDown > 499) {
        scrollBarValueVerticalDown = 499;
    }

    QImage tempImage;
    // TODO Note: Still need to verify. landscapegrid vector[0][0] (down, left) is being printed to the upper left corner of scene
    for (int i = scrollBarValueHorizontalLeft; i <= scrollBarValueHorizontalRight; i++) {
    for (int j = scrollBarValueVerticalUpper; j <= scrollBarValueVerticalDown; j++) {
            if(this->gamemodel->landscapeGridmap[i][j].climate == DEEP_SEA)
            {tempImage = qImageMap["deep_sea"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SHALLOW_WATER){tempImage = qImageMap["shallow_water"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SAND){tempImage = qImageMap["sand"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == EARTH){tempImage = qImageMap["earth"];}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == ROCKS){tempImage = qImageMap["rocks"];}
            else //this->gamemodel->landscapeGridmap[i][j].climate == SNOW)
            {tempImage = qImageMap["snow"];}
            //scene->addPixmap(QPixmap::fromImage(tempImage, Qt::AutoColor)); // Coordinates are default (0,0)
            // only the landscape tiles need to be clickable
            GridClickablePixmapItem *tempPixmapItem = new GridClickablePixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor), i, j, this);
            tempPixmapItem->setOffset(i*32,j*32);
            scene->addItem(tempPixmapItem);
    }
    }

    for (int i = scrollBarValueHorizontalLeft; i <= scrollBarValueHorizontalRight; i++) {
    for (int j = scrollBarValueVerticalUpper; j <= scrollBarValueVerticalDown; j++) {
        if(this->gamemodel->landscapeGridmap[i][j].creaturesOnTile.empty()) continue;
        int creaturesOnTile = this->gamemodel->landscapeGridmap[i][j].creaturesOnTile.size();
        // opacities allowed are 1.0, 0.8, 0.6 and 0.4, every creature more has opacity 0.4
        double tempOpacity = 1.2;
        for(int k = 0; k < creaturesOnTile ; k++){
            if(tempOpacity > 0.5) {
                tempOpacity = tempOpacity - 0.2;
            }
            QImage tempImage;
            std::string tempCreaturename = this->gamemodel->landscapeGridmap[i][j].creaturesOnTile[k].creaturename;
            tempImage = qImageMap[tempCreaturename];
            GridClickablePixmapItem *tempPixmapItem = new GridClickablePixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor), i, j, this);
            tempPixmapItem->setAcceptedMouseButtons(0);
            tempPixmapItem->opacity = tempOpacity;
            tempPixmapItem->setOffset(i*32,j*32);
            scene->addItem(tempPixmapItem);            
        }
    }
    }

    //DRAW CURSOR
    tempImage = qImageMap["cursor"];
    QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor));
    //tempPixmapItem->setAcceptedMouseButtons(0);
    tempPixmapItem->setOffset(this->cursorX*32,this->cursorY*32);
    scene->addItem(tempPixmapItem);
    std::cout << "x:" << (int) this->cursorX << ", y:" << (int) this->cursorY << "\n" <<std::endl;
    // TODO Note: Output follows here to the console: QGraphicsItem::ungrabMouse: not a mouse grabber
    //  doesn´t matter because the cursor position is set.

    // /*/
    // working on the created pixmap
    tempImage = qImageMap["Baer"];
    // GridClickablePixmapItem
    GridClickablePixmapItem *tempPixmapItem2 = new GridClickablePixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor), 5, 5, this);
    tempPixmapItem2->setAcceptedMouseButtons(0);
    tempPixmapItem2->opacity = 1.0;
    tempPixmapItem2->setOffset(5*32,5*32);
    scene->addItem(tempPixmapItem2);

    // /*/
    /*/
    // painter does modify the pixmap
    QPainter tempPainter;
    tempPainter.begin(&tempPixmapAlpha);
    tempPainter.setOpacity(0.25);
    tempPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tempPainter.end();
    /*/
    /*/

    // As soon as there is a GridClickablePixmapItem the programm crashes. Nothing to do with painter.
    // Qgraphicspixmapitem is constructed from the modified pixmap
    QPixmap tempPixmap2 =  QPixmap::fromImage(tempImage, Qt::AutoColor);
    QGraphicsPixmapItem *tempPixmapitem2 = new GridClickablePixmapItem(tempPixmap2, 3, 3, this);
    tempPixmapitem2->setAcceptedMouseButtons(0);
    tempPixmapitem2->setOffset(3*32,3*32);
    scene->addItem(tempPixmapitem2);

    // Qgraphicspixmapitem is constructed from the modified pixmap
    QPixmap tempPixmap3 =  QPixmap::fromImage(tempImage, Qt::AutoColor);
    GridClickablePixmapItem *tempPixmapitem3 = new GridClickablePixmapItem(tempPixmap3, 4, 4, this);
    tempPixmapitem3->setAcceptedMouseButtons(0);
    tempPixmapitem3->setOffset(4*32,4*32);
    scene->addItem(tempPixmapitem3);
    /*/
}

void biosim::gridClicked(int xCoord, int yCoord) {
    this->cursorX = xCoord;
    this->cursorY = yCoord;
    this->updateVisibleScene();
}

void biosim::writeStartErrorToMsgboxAndExit(const std::string &error) {
    QMessageBox msg;
    QString qerror = QString::fromStdString(error);
    msg.setText(qerror);
    msg.exec();
    QApplication::exit();
}
