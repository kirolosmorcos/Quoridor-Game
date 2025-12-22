#ifndef PAWNSELECTWINDOW_H
#define PAWNSELECTWINDOW_H

#include <QWidget>
#include <QColor>
#include <QPushButton>
#include <QLabel>
#include "../util/Constants.h"

class PawnSelectWindow : public QWidget {
    Q_OBJECT
public:
    PawnSelectWindow(GameMode mode, Difficulty diff, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void onColorChosen(QPushButton *btn, const QColor &color);
    void undoSelection();
    void refreshUI();

    GameMode mode;
    Difficulty diff;

    QColor player1Color;
    QColor player2Color;

    int maxSelections = 0;
    int currentSelection = 0;

    QLabel *infoLabel = nullptr;
    QPushButton *startBtn = nullptr;
    QPushButton *undoBtn = nullptr;
    QPushButton *firstBtn = nullptr;

    QList<QPushButton*> colorButtons;

    bool player1Starts = false;
    QPushButton *p1StartBtn;
    QPushButton *p2StartBtn;


};

#endif
