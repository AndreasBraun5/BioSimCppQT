/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim = PRESENTER. class biosim is subclass of QMainWindow and Ui_biosim. Equals the PRESENTER,
    which in this case holds an pointer to the VIEW which is generated out of the
    biosim.ui file.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_BIOSIM_HPP
#define INCLUDED_BIOSIM_BIOSIM_HPP

#include <QMainWindow>

#include "gamemodel.hpp" // had circular dependency
#include "creature.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
namespace Ui {
class biosim;
}

class biosim : public QMainWindow {
    Q_OBJECT

public:
    explicit biosim(QWidget *parent = 0);
    ~biosim();
    void updateCreatureEditLines(const CreatureData *tempCreatureEditing);
    CreatureData getTempCreatureEditing() const;
    void writeStartErrorToMsgboxAndExit(const std::string &error);

private:
    CreatureData const *tempCreatureEditing;
    Ui::biosim *ui;
    // TODO Note: access violation scoped pointer, if main window is closed. Solved?: the pointer gamemodel was
    // deleted in the constructor, analog to the ui pointer. But I blieve some kind of garbage collection tried
    // again to delete the already deleted pointer gamemodel. How to check if the gamemodel pointer is really already deleted?
    // or better use smart pointer?
    GameModel *gamemodel;
    // TODO Discuss: Improvement, name it gamecontroller
    // Model(gamemodel)-View(Ui_biosim.h)-Presenter(biosim-.hpp/.cpp) intended. Gamemodel doesn´t know of
    // Ui_biosim.h (generated from biosim.ui) and biosim-.hpp/.cpp. Gamemodel will contain all data and logic. biosim will
    // handle the communication and Ui_biosim will only contain the view.

private slots:
    void updateCreatureComboBox(int index);
    void dumbClick();

};

#endif // BIOSIM_HPP
