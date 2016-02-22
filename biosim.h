#ifndef BIOSIM_H
#define BIOSIM_H

#include <QMainWindow>

namespace Ui {
class biosim;
}

class biosim : public QMainWindow // main window biosim is subclass of qmainwindow
{
    Q_OBJECT

public:
    explicit biosim(QWidget *parent = 0); // biosim has no parent --> own window
    ~biosim();

private:
    Ui::biosim *ui;
};

#endif // BIOSIM_H
