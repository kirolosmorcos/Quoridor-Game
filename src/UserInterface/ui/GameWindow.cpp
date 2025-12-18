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
    resize(900, 700);


    QToolBar *bar = addToolBar("Game");
    bar->addAction("Restart", scene, &BoardScene::reset);
    bar->addAction("New Game", this, [=]{
            auto *w = new ModeSelectWindow();
            w->show();
            close();
            }
        );
}
