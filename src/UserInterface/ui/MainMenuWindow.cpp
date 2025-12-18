#include "MainMenuWindow.h"
#include "ModeSelectWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


MainMenuWindow::MainMenuWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("Quoridor");
    setFixedSize(420,420);


    auto *layout = new QVBoxLayout(this);


    // 🔹 Game icon
    QLabel *icon = new QLabel;
    icon->setPixmap(QPixmap(":/assets/Icon1.png")
                        .scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    icon->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("<h1>Quoridor</h1>");
    title->setAlignment(Qt::AlignCenter);

    QPushButton *start = new QPushButton("Start Game");

    layout->addWidget(title);
    layout->addStretch();
    layout->addWidget(icon, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(start);


    connect(start, &QPushButton::clicked, this, [=]{
    auto *w = new ModeSelectWindow();
    w->show();
    close();
    });
}