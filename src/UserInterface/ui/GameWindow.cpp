#include "GameWindow.h"
#include "../scene/BoardScene.h"
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>

#include "ModeSelectWindow.h"


GameWindow::GameWindow(GameMode mode,
           Difficulty diff,
           QColor p1Color,
           QColor p2Color,
           bool turn,
           QWidget *parent)
: QMainWindow(parent) {


    setWindowTitle("Quoridor Match");


    auto *scene = new BoardScene(mode, diff, p1Color, p2Color, turn, this );
    auto *view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
    setCentralWidget(view);
    resize(800, 700);

    //add undo and redo
    QToolBar *bar = addToolBar("Game");
    bar->addAction("Restart", scene, &BoardScene::reset);
    bar->addAction("New Game", this, [=]{
            auto *w = new ModeSelectWindow();
            w->show();
            close();
            }
        );
    bar->addAction("Undo", this, [=] {
        scene->undo();
        if (mode == GameMode::PvAI ) scene->undo();
    });
    bar->addAction("Redo", this, [=] {
        scene->redo();
        if (mode == GameMode::PvAI ) scene->redo();
    });
}
