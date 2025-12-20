#include "PawnSelectWindow.h"
#include "GameWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


PawnSelectWindow::PawnSelectWindow(GameMode mode, Difficulty diff, QWidget *parent)
: QWidget(parent) {


    setWindowTitle("Choose Pawns");
    setFixedSize(400,300);


    auto *layout = new QVBoxLayout(this);


    QLabel *info = new QLabel(
    mode == GameMode::PvAI ?
    "Choose your pawn" :
    "Player 1 & Player 2 choose pawns"
    );
    info->setAlignment(Qt::AlignCenter);


    QPushButton *start = new QPushButton("Start Match");


    layout->addWidget(info);
    layout->addWidget(start);
    // Add pawn previews here (images or 3D later)


    connect(start, &QPushButton::clicked, this, [=]{
    auto *w = new GameWindow(mode, diff);
    w->show(); close();
    });
}