#include "PawnSelectWindow.h"
#include "GameWindow.h"

#include <QEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

// =======================================================

PawnSelectWindow::PawnSelectWindow(GameMode mode, Difficulty diff, QWidget *parent)
    : QWidget(parent), mode(mode), diff(diff)
{
    setWindowTitle("Choose Pawns");
    setFixedSize(460, 420);

    setStyleSheet(
        "PawnSelectWindow {"
        " background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        " stop:0 #1f1f1f, stop:1 #121212);"
        "}"
    );

    maxSelections = (mode == GameMode::PvAI) ? 1 : 2;
    player1Starts = false;   // default for all modes

    auto *mainLayout = new QVBoxLayout(this);

    // ===== Info Label =====
    infoLabel = new QLabel("Player 1: Choose pawn color");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet(
        "color:#f0f0f0;"
        "font-size:17px;"
        "font-weight:bold;"
        "letter-spacing:1px;"
    );

    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setColor(Qt::black);
    shadow->setOffset(0, 2);
    infoLabel->setGraphicsEffect(shadow);

    mainLayout->addWidget(infoLabel);

    // ===== Panel =====
    auto *panel = new QWidget();
    panel->setStyleSheet(
        "background:#2a2a2a;"
        "border-radius:16px;"
        "padding:14px;"
    );
    mainLayout->addWidget(panel);

    auto *grid = new QGridLayout(panel);
    grid->setSpacing(24);

    QList<QColor> colors = {
        Qt::red, Qt::blue, Qt::green, Qt::yellow,
        Qt::magenta, Qt::cyan,
        QColor("#FF7F50"), QColor("#8A2BE2"),
        Qt::white, Qt::gray, Qt::darkGray
    };

    if (mode != GameMode::PvAI)
        colors.append(Qt::black);

    int row = 0, col = 0;

    for (const QColor &c : colors) {
        auto *btn = new QPushButton();
        btn->setFixedSize(60, 60);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setProperty("pawnColor", c);

        btn->setStyleSheet(QString(
            "QPushButton {"
            " background:%1;"
            " border-radius:30px;"
            " border:2px solid #666;"
            "}"
            "QPushButton:hover {"
            " border:3px solid white;"
            "}"
            "QPushButton:disabled {"
            " background:#444;"
            " border:2px solid #222;"
            "}"
        ).arg(c.name()));

        grid->addWidget(btn, row, col);
        colorButtons.append(btn);

        btn->installEventFilter(this);

        connect(btn, &QPushButton::clicked, this, [=]() {
            onColorChosen(btn, c);
        });

        if (++col == 4) { col = 0; row++; }
    }

    // ===== First Turn Selector (PvAI ONLY) =====
    if (mode == GameMode::PvAI) {

        auto *turnLabel = new QLabel("Who plays first?");
        turnLabel->setAlignment(Qt::AlignCenter);
        turnLabel->setStyleSheet(
            "color:#ddd;"
            "font-size:15px;"
            "font-weight:bold;"
        );

        p1StartBtn = new QPushButton("Player");
        p2StartBtn = new QPushButton("AI");

        for (auto *b : {p1StartBtn, p2StartBtn}) {
            b->setCheckable(true);
            b->setFixedHeight(36);
            b->setCursor(Qt::PointingHandCursor);
            b->setEnabled(true);
            b->setStyleSheet(
                "QPushButton {"
                " background:#333;"
                " border-radius:10px;"
                " border:2px solid #555;"
                " color:white;"
                "}"
                "QPushButton:checked {"
                " background:#4CAF50;"
                " border:2px solid white;"
                "}"
            );
        }

        p1StartBtn->setChecked(true);

        auto *turnLayout = new QHBoxLayout();
        turnLayout->addWidget(p1StartBtn);
        turnLayout->addWidget(p2StartBtn);

        mainLayout->addWidget(turnLabel);
        mainLayout->addLayout(turnLayout);

        connect(p1StartBtn, &QPushButton::clicked, this, [=]() {
            p1StartBtn->setChecked(true);
            p2StartBtn->setChecked(false);
            player1Starts = false;
        });

        connect(p2StartBtn, &QPushButton::clicked, this, [=]() {
            p2StartBtn->setChecked(true);
            p1StartBtn->setChecked(false);
            player1Starts = true;
        });
    }

    // ===== Controls =====
    undoBtn = new QPushButton("Undo");
    undoBtn->setEnabled(false);

    startBtn = new QPushButton("Start Match");
    startBtn->setEnabled(false);

    auto *controls = new QHBoxLayout();
    controls->addWidget(undoBtn);
    controls->addStretch();
    controls->addWidget(startBtn);

    mainLayout->addStretch();
    mainLayout->addLayout(controls);

    connect(undoBtn, &QPushButton::clicked, this, &PawnSelectWindow::undoSelection);

    connect(startBtn, &QPushButton::clicked, this, [=]() {

        auto *w = new GameWindow(
            mode,
            diff,
            player1Color,
            player2Color,
            player1Starts
        );

        w->show();
        close();
    });
}

// =======================================================

void PawnSelectWindow::onColorChosen(QPushButton *btn, const QColor &color)
{
    if (currentSelection >= maxSelections)
        return;

    if (color == player1Color || color == player2Color)
        return;

    QString ring = (color == Qt::black) ? "white" : "black";

    btn->setStyleSheet(QString(
        "background:%1;"
        "border-radius:30px;"
        "border:4px solid %2;"
    ).arg(color.name(), ring));

    btn->setEnabled(false);

    if (currentSelection == 0)
        player1Color = color;
    else
        player2Color = color;

    currentSelection++;
    refreshUI();
}

// =======================================================

void PawnSelectWindow::undoSelection()
{
    if (currentSelection == 0)
        return;

    QColor removed =
        (currentSelection == 2) ? player2Color : player1Color;

    if (currentSelection == 2)
        player2Color = QColor();
    else
        player1Color = QColor();

    for (auto *btn : colorButtons) {
        QColor c = btn->property("pawnColor").value<QColor>();
        if (c == removed) {
            btn->setEnabled(true);
            btn->setStyleSheet(QString(
                "background:%1;"
                "border-radius:30px;"
                "border:2px solid #666;"
            ).arg(c.name()));
            break;
        }
    }

    currentSelection--;
    refreshUI();
}

// =======================================================

void PawnSelectWindow::refreshUI()
{
    undoBtn->setEnabled(currentSelection > 0);
    startBtn->setEnabled(currentSelection == maxSelections);

    if (mode == GameMode::PvAI) {
        if (p1StartBtn && p2StartBtn) {
            bool ready = (currentSelection == maxSelections);
            p1StartBtn->setEnabled(ready);
            p2StartBtn->setEnabled(ready);
        }

        infoLabel->setText(
            currentSelection == 0 ?
            "Choose pawn color" :
            "Ready to start"
        );
    } else {
        player1Starts = true;

        if (currentSelection == 0)
            infoLabel->setText("Player 1: Choose pawn color");
        else if (currentSelection == 1)
            infoLabel->setText("Player 2: Choose pawn color");
        else
            infoLabel->setText("Ready to start");
    }
}

// =======================================================

bool PawnSelectWindow::eventFilter(QObject *watched, QEvent *event)
{
    auto *btn = qobject_cast<QPushButton*>(watched);
    if (!btn || !btn->isEnabled())
        return QWidget::eventFilter(watched, event);

    QRect g = btn->geometry();

    if (event->type() == QEvent::Enter) {
        auto *anim = new QPropertyAnimation(btn, "geometry");
        anim->setDuration(120);
        anim->setStartValue(g);
        anim->setEndValue(g.adjusted(-4, -4, 4, 4));
        anim->setEasingCurve(QEasingCurve::OutBack);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if (event->type() == QEvent::Leave) {
        auto *anim = new QPropertyAnimation(btn, "geometry");
        anim->setDuration(120);
        anim->setStartValue(g);
        anim->setEndValue(g.adjusted(4, 4, -4, -4));
        anim->setEasingCurve(QEasingCurve::OutBack);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }

    return QWidget::eventFilter(watched, event);
}
