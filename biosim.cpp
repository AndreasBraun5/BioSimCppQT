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

#include "gamemodel.hpp"

// Overriding the resizeEvent function so that you are able to call the updateVisibleScene function.
// TODO Note: Be careful with the inheritance hierarchy.
void biosim::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    std::cout << "Call from resizeEvent \n" << std::endl;
    this->updateVisibleScene();
}

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

    tempCreatureEditing = &gamemodel->creatureDataList.at(0);
    for(int i = 0; i < gamemodel->creatureDataList.size(); i++) {
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel->creatureDataList.at(i).creaturename));
    }
    updateCreatureEditLines(tempCreatureEditing);

    // creating scene and adding to graphicsView
    this->scene = new QGraphicsScene(this);                                                    // !delete scene auto managed, by parent
    ui->graphicsView->setScene(scene);

    // creating "empty" QGraphicsScene with specified size
    int qrectfSize = 500*32; // TODO AB4: Needs to be sizehorizontal*sizeoftile
    QRectF viewQrectf (0,0,qrectfSize,qrectfSize); // Constructs a rectangle with (x, y) as its top-left corner and the given width and height.
    ui->graphicsView->setSceneRect(viewQrectf);

    // initial call to fill the scene
    // TODO AB4: It is called before the QGraphicsView is properly initialised resulting in a only partly filled scene.
    biosim::updateVisibleScene();

    // TODO implement zooming?
    //ui->graphicsView->scale(2, 2);

    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateVisibleSceneScrollbar()));
    connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateVisibleSceneScrollbar()));
    //connect(ui->graphicsView->resizeEvent(QResizeEvent *event), SIGNAL(), this, SLOT(updateVisibleScene(int)));
}

biosim::~biosim() {
    delete ui;                                                                                  // !delete ui
    //delete gamemodel;                    // TODO                                              // !delete gamemodel automanaged
    //  but there is shown an error if i do that. Deleting an already deleted pointer. Something that qt already does
}

void biosim::updateCreatureEditLines(const CreatureData *tempCreatureEditing) {
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
    tempCreatureEditing = &gamemodel->creatureDataList.at(index);
    updateCreatureEditLines(tempCreatureEditing);
}

void biosim::dumbClick() {
    QMessageBox msg;
    msg.setText("dead end");
    msg.exec();
}
//
void biosim::updateVisibleSceneScrollbar() {
    std::cout << "\n Call from UpdateVisibleScenceScrollbar: " << std::endl;
    biosim::updateVisibleScene();
}

// static method
// always updating everything
// computing visible area: graphicsViewSize, maximum value, scrollbarValue (value) --> position,
// filling a bit more tiles than needed
void biosim::updateVisibleScene() {

    // Quiet some debug output following
    int viewPortWidth = ui->graphicsView->viewport()->width();
    std::cout << "viewPortWidth: " << viewPortWidth << std::endl;
    int viewPortHeight = ui->graphicsView->viewport()->height();
    std::cout << "viewPortHeight: " << viewPortHeight << std::endl;

    int viewQRectfSizeHeight = ui->graphicsView->sceneRect().size().rheight();
    std::cout << "viewQRectfSizeHeight: " << viewQRectfSizeHeight << std::endl;
    int viewQRectfSizeWidth = ui->graphicsView->sceneRect().size().rwidth();
    std::cout << "viewQRectfSizeWidth: " << viewQRectfSizeWidth << std::endl;

    int scrollBarValueHorizontal = ui->graphicsView->horizontalScrollBar()->value();
    std::cout << "scrollBarValueHorizontal: " << scrollBarValueHorizontal << std::endl;
    int scrollBarValueHorizontalMaximum = ui->graphicsView->horizontalScrollBar()->maximum();
    std::cout << "scrollBarValueHorizontalMaximum: " << scrollBarValueHorizontalMaximum << std::endl;

    int scrollBarValueVertical = ui->graphicsView->verticalScrollBar()->value();
    std::cout << "scrollBarValueVertical: " << scrollBarValueVertical << std::endl;
    int scrollBarValueVerticalMaximum = ui->graphicsView->verticalScrollBar()->maximum();
    std::cout << "scrollBarValueVerticalMaximum: " << scrollBarValueVerticalMaximum << std::endl;

    // scrollBarValue + scrollBarValueMaximum --> position within entire scence
    // position + viewPortWidth + viewPortHeight --> area to update/show
    // area shown will be somewhat bigger as needed to prevent mistakes due to inaccurate and not exact enough postion values

    // Assuring its size is at least one
    scrollBarValueHorizontalMaximum = std::max(scrollBarValueHorizontalMaximum,1);
    std::cout << "\nscrollBarValueHorizontalMaximum: " << scrollBarValueHorizontalMaximum << std::endl;
    scrollBarValueVerticalMaximum = std::max(scrollBarValueVerticalMaximum,1);
    std::cout << "scrollBarValueVerticalMaximum: " << scrollBarValueVerticalMaximum << std::endl;

    // Calculating the four needed values
    int scrollBarValueHorizontalLeft = scrollBarValueHorizontal;
    std::cout << "scrollBarValueHorizontalLeft: " << scrollBarValueHorizontalLeft << std::endl;
    int scrollBarValueHorizontalRight = scrollBarValueHorizontal + viewPortWidth;
    std::cout << "scrollBarValueHorizontalRight: " << scrollBarValueHorizontalRight << std::endl;
    int scrollBarValueVerticalUpper = scrollBarValueVertical;
    std::cout << "scrollBarValueVerticalUpper: " << scrollBarValueVerticalUpper << std::endl;
    int scrollBarValueVerticalDown = scrollBarValueVertical + viewPortHeight;
    std::cout << "scrollBarValueVerticalDown: " << scrollBarValueVerticalDown << std::endl;


    int imageSizeInPixel = sqrt((int) gamemodel->sand.size())/2; // Image size in pixel

    QImage deep_sea = QImage(gamemodel->deep_sea.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    QImage shallow_water = QImage(gamemodel->shallow_water.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    QImage sand = QImage(gamemodel->sand.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    QImage earth = QImage(gamemodel->earth.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    QImage rocks = QImage(gamemodel->rocks.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);
    QImage snow = QImage(gamemodel->snow.data(), imageSizeInPixel, imageSizeInPixel, QImage::Format_ARGB32);

    scene->clear();

    // Problem now is to determine the coordinate transformation between scrollBarValues and the position of the picture in the grid
    // now the scrollBarValues are in multiple of tiles
    scrollBarValueHorizontalLeft = scrollBarValueHorizontalLeft/32;
    std::cout << "scrollBarValueHorizontalLeft: " << scrollBarValueHorizontalLeft << std::endl;
    scrollBarValueHorizontalRight = scrollBarValueHorizontalRight/32;
    std::cout << "scrollBarValueHorizontalRight: " << scrollBarValueHorizontalRight << std::endl;
    scrollBarValueVerticalUpper = scrollBarValueVerticalUpper/32;
    std::cout << "scrollBarValueVerticalUpper: " << scrollBarValueVerticalUpper << std::endl;
    scrollBarValueVerticalDown = scrollBarValueVerticalDown/32;
    std::cout << "scrollBarValueVerticalDown: " << scrollBarValueVerticalDown << std::endl;

    // guaranteeing that the calculated subsripts exist. Needed because with applied method sometimes
    // little bit more than the visible area is expected to be drawn. At the right and down boarder this
    // would lead to a vector subscript access out of range.
    if(scrollBarValueHorizontalRight > 499) {
        scrollBarValueHorizontalRight = 499;
        std::cout << "scrollBarValueHorizontalRightGuaranteed: " << scrollBarValueHorizontalRight << std::endl;
    }
    if(scrollBarValueVerticalDown > 499) {
        scrollBarValueVerticalDown = 499;
        std::cout << "scrollBarValueVerticalDownGuaranteed: " << scrollBarValueVerticalDown << std::endl;
    }
    int vectorSize1 = (int) this->gamemodel->landscapeGridmap.size();
    std::cout << "vectorSize1: " << vectorSize1 << std::endl;
    int vectorSize2 = (int) this->gamemodel->landscapeGridmap[1].size();
    std::cout << "vectorSize2: " << vectorSize2 << std::endl;

    // TODO Note: Still need to verify. landscapegrid vector[0][0] (down, left) is being printed to the upper left corner of scene
    for (int i = scrollBarValueHorizontalLeft; i <= scrollBarValueHorizontalRight; i++) {
        for (int j = scrollBarValueVerticalUpper; j <= scrollBarValueVerticalDown; j++) {
            QImage tempImage;
            if(this->gamemodel->landscapeGridmap[i][j].climate == DEEP_SEA)
                {tempImage = deep_sea;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SHALLOW_WATER){tempImage = shallow_water;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SAND){tempImage = sand;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == EARTH){tempImage = earth;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == ROCKS){tempImage = rocks;}
            else //this->gamemodel->landscapeGridmap[i][j].climate == SNOW)
                {tempImage = snow;}
            //scene->addPixmap(QPixmap::fromImage(tempImage, Qt::AutoColor)); // Coordinates are default (0,0)
            QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor));
            tempPixmapItem->setOffset(i*32,j*32);
            scene->addItem(tempPixmapItem);
            //std::cout << i << std::endl;
            //std::cout << j << std::endl;
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
