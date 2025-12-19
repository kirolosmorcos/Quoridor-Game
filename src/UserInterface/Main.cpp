#include <QApplication>
#include "ui/MainMenuWindow.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainMenuWindow w;
    w.show();
    return app.exec();
}