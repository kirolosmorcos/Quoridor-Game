#include "BoardScene.h"

#include <iostream>

#include "../model/PawnItem.h"
#include "../model/WallItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>


BoardScene::BoardScene(GameMode, Difficulty, QObject *parent)
: QGraphicsScene(parent) {

    reset();
    setStickyFocus(true);
}


QPointF BoardScene::cellCenter(int row, int col) const {
    return QPointF(
        col * STEP + CELL_SIZE / 2,
        row * STEP + CELL_SIZE / 2
    );
}


void BoardScene::reset() {
    clear();
    turn = Turn::White;

    //TODO: reset wall arrays
    memset(hWall, false, sizeof(hWall));
    memset(vWall, false, sizeof(vWall));

    // 🔹 BOARD DRAWING
    // Option A: procedural grid (current)
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            QPen pen(Qt::lightGray);
            pen.setWidth(2);
            addRect(
                c * STEP,
                r * STEP,
                CELL_SIZE,
                CELL_SIZE,
                pen
            );
        }
    }
    // Option B: image board
    // QGraphicsPixmapItem *board = addPixmap(QPixmap(":/assets/board.png"));
    // board->setZValue(0);


    white = new PawnItem(Qt::white);
    black = new PawnItem(Qt::black);

    wallPreview = new WallItem(ori::Vertical);
    wallPreview->setOpacity(0.5);
    wallPreview->setVisible(false);

    addItem(wallPreview);
    addItem(white);
    addItem(black);

    //TODO: get position from game state
    white->setPos(4*STEP + CELL_SIZE/2, 8*STEP + CELL_SIZE/2 );
    black->setPos(4*STEP + CELL_SIZE/2, 0*STEP + CELL_SIZE/2 );
    white->setBoardPos(8, 4);
    black->setBoardPos(0, 4);
    updateTurnHighlight();

}

HoverType BoardScene::detectHover(const QPointF &p, int &row, int &col) const
{
    if (p.x() < 0 || p.y() < 0)
        return HoverType::None;

    col = int(p.x()) / STEP;
    row = int(p.y()) / STEP;

    if (row < 0 || row >= BOARD_SIZE ||
        col < 0 || col >= BOARD_SIZE)
        return HoverType::None;

    int localX = int(p.x()) - col * STEP;
    int localY = int(p.y()) - row * STEP;

    if (localX < CELL_SIZE && localY < CELL_SIZE)
        return HoverType::Cell;

    if (localX >= CELL_SIZE && localY < CELL_SIZE)
        return HoverType::VerticalEdge;

    if (localY >= CELL_SIZE && localX < CELL_SIZE)
        return HoverType::HorizontalEdge;

    return HoverType::None;
}

void BoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //TODO: check remaining walls for the current player

    int r, c;
    HoverType type = detectHover(event->scenePos(), r, c);

    if (type == HoverType::None) {
        wallPreview->setVisible(false);
        return;
    }

    if (type != lastHover) {
        lastHover = type;
    }

    if (type == HoverType::VerticalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {
            wallPreview->setOrientation(ori::Vertical);
            wallPreview->setPos(c * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2, r * STEP - (WALL_LEN - STEP - CELL_SIZE)/2 );
            wallPreview->setOpacity(0.4);
            wallPreview->setVisible(true);
        }
    }
    else if (type == HoverType::HorizontalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {
            wallPreview->setOrientation(ori::Horizontal);
            wallPreview->setPos(c * STEP - (WALL_LEN - STEP - CELL_SIZE)/2, r * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2);
            wallPreview->setOpacity(0.4);
            wallPreview->setVisible(true);
        }
    }
    else {
        wallPreview->setVisible(false);
    }
}


void BoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton) return;

    int r, c;
    HoverType type = detectHover(event->scenePos(), r, c);

    if (type == HoverType::Cell) {
        PawnItem *p = (turn == Turn::White) ? white : black;

        if (movePawn(p, r, c)) {
            turn = (turn == Turn::White ? Turn::Black : Turn::White);
            updateTurnHighlight();
        }
    }
    else if (type == HoverType::VerticalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {

            vWall[r][c]= true; // TODO: mark wall in array
            vWall[r+1][c]= true; // TODO: mark wall in array

            auto *wall = new WallItem(ori::Vertical);
            addItem(wall);
            wall->setPos(c * STEP + CELL_SIZE - (WALL_THICK - WALL_GAP)/2, r * STEP - (WALL_LEN - STEP - CELL_SIZE)/2);
            turn = (turn == Turn::White ? Turn::Black : Turn::White);
            updateTurnHighlight();
        }
    }
    else if (type == HoverType::HorizontalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {

            auto *wall = new WallItem(ori::Horizontal);
            addItem(wall);
            wall->setPos(c * STEP - (WALL_LEN - STEP - CELL_SIZE)/2, r * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2);
            turn = (turn == Turn::White ? Turn::Black : Turn::White);
            updateTurnHighlight();
        }
    }
}

QVector<QPoint> BoardScene::getAvailableMoves(int r, int c) const
{
    QVector<QPoint> moves;

    // UP
    if (r > 0 && !hWall[r - 1][c]) {
        moves.append({r - 1, c});
    }

    // DOWN
    if (r < BOARD_SIZE - 1 && !hWall[r][c]) {
        moves.append({r + 1, c});
    }

    // LEFT
    if (c > 0 && !vWall[r][c - 1]) {
        moves.append({r, c - 1});
    }

    // RIGHT
    if (c < BOARD_SIZE - 1 && !vWall[r][c]) {
        moves.append({r, c + 1});
    }

    return moves;
}

bool BoardScene::movePawn(PawnItem *pawn, int toRow, int toCol)
{
    QPoint from = pawn->boardPos(); // YOU NEED THIS (see below)

    auto moves = getAvailableMoves(from.x(), from.y());

    if (!moves.contains(QPoint(toRow, toCol)))
        return false;

    pawn->setBoardPos(toRow, toCol);
    pawn->animateMove(cellCenter(toRow, toCol));
    return true;
}

void BoardScene::updateTurnHighlight()
{
    white->setOpacity(turn == Turn::White ? 1.0 : 0.4);
    black->setOpacity(turn == Turn::Black ? 1.0 : 0.4);
    showMoveHighlights(turn == Turn::White ? white : black);
}

void BoardScene::clearMoveHighlights()
{
    for (auto *r : moveHighlights) {
        removeItem(r);
        delete r;
    }
    moveHighlights.clear();
}

void BoardScene::showMoveHighlights(PawnItem *pawn)
{
    clearMoveHighlights();

    QPoint from = pawn->boardPos();
    auto moves = getAvailableMoves(from.x(), from.y());

    for (const QPoint &m : moves) {
        auto *rect = new QGraphicsRectItem(
            0, 0, CELL_SIZE, CELL_SIZE
        );

        rect->setPos(m.y() * STEP, m.x() * STEP);

        QColor gold(255, 215, 0);
        gold.setAlpha(120);

        rect->setBrush(gold);
        rect->setPen(QPen(QColor(255, 215, 0), 2));

        rect->setZValue(1.5); // above board, below pawn
        rect->setOpacity(0.6);

        addItem(rect);
        moveHighlights.append(rect);
    }
}
