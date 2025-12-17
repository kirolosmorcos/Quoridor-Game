#include "ModeSelectWindow.h"
#include "PawnSelectWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>


ModeSelectWindow::ModeSelectWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("Choose Mode");
    setFixedSize(400,300);


    auto *layout = new QVBoxLayout(this);


    auto *pvp = new QPushButton("Player vs Player");
    auto *pvai = new QPushButton("Player vs AI");


    auto *diff = new QComboBox;
    diff->addItems({"Easy","Medium","Hard"});


    layout->addWidget(pvp);
    layout->addWidget(pvai);
    layout->addWidget(diff);


    connect(pvp, &QPushButton::clicked, this, [=]{
    auto *w = new PawnSelectWindow(GameMode::PvP, Difficulty::Easy);
    w->show(); close();
    });


    connect(pvai, &QPushButton::clicked, this, [=]{
    auto *w = new PawnSelectWindow(GameMode::PvAI, (Difficulty)diff->currentIndex());
    w->show(); close();
    });
}