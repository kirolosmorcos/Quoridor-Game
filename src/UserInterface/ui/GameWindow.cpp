#include "GameWindow.h"
#include "../scene/BoardScene.h"
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>

#include "ModeSelectWindow.h"


GameWindow::GameWindow(GameMode mode, Difficulty diff, QWidget *parent)
: QMainWindow(parent) {


    setWindowTitle("Quoridor Match");


    auto *scene = new BoardScene(mode, diff, this);
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
        //l7d ma rbna yrid b2a
    });
    bar->addAction("Redo", this, [=] {
        //l7d ma rbna yrid
    });
}
