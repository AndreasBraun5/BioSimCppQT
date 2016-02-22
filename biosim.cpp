#include "biosim.h"
#include "ui_biosim.h"

biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim)
{
    ui->setupUi(this);
}

biosim::~biosim()
{
    delete ui;
}
