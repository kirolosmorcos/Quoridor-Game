#include "BoardScene.h"

#include <iostream>
#include "../model/PawnItem.h"
#include "../model/WallItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QPropertyAnimation>


BoardScene::BoardScene(GameMode mode, Difficulty diff, QObject *parent)
: QGraphicsScene(parent) {
    this->mode = mode;
    this->diff = diff;
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
    undoStack.clear();
    redoStack.clear();
    setBoardEnabled(false);
    clear();
    setBoardEnabled(true);
    // turn = Turn::White;
    game.turn = false;
    game.p0_walls = 10;
    game.p1_walls = 10;

    //TODO: reset wall arrays
    memset(game.horizontal_walls, false, sizeof(game.horizontal_walls));
    memset(game.vertical_walls, false, sizeof(game.vertical_walls));

    // procedural grid (current)
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

    // ---- LEFT HUD PANEL ----
    const int HUD_WIDTH = 140;
    const int HUD_HEIGHT = BOARD_SIZE * STEP;

    auto *hudBg = addRect(
        -HUD_WIDTH, 0,
        HUD_WIDTH - 10, HUD_HEIGHT,
        QPen(Qt::NoPen),
        QBrush(Qt::darkGray) // dark panel
    );
    hudBg->setZValue(0.5);

    addItem(wallPreview);
    addItem(white);
    addItem(black);

    //TODO: get position from game state
    //DONE
    white->setPos(4*STEP + CELL_SIZE/2, 8*STEP + CELL_SIZE/2 );
    black->setPos(4*STEP + CELL_SIZE/2, 0*STEP + CELL_SIZE/2 );

    game.player0_pos = 76; // row 0, col 4
    game.player1_pos = 4;  // row 8, col 4

    // ---- Wall counters ----
    QFont hudFont("Arial", 14, QFont::Bold);

    // White
    whiteWallsText = addText("", hudFont);
    whiteWallsText->setDefaultTextColor(Qt::white);
    whiteWallsText->setTextWidth(HUD_WIDTH - 20);
    whiteWallsText->setZValue(1);
    whiteWallsText->setPos(-HUD_WIDTH + 10, STEP * 2);

    // Black
    blackWallsText = addText("", hudFont);
    blackWallsText->setDefaultTextColor(Qt::black);
    blackWallsText->setTextWidth(HUD_WIDTH - 20);
    blackWallsText->setZValue(1);
    blackWallsText->setPos(-HUD_WIDTH + 10, STEP * 6);

    updateWallCounters();
        setSceneRect(
        -HUD_WIDTH,
        0,
        BOARD_SIZE * STEP + HUD_WIDTH,
        BOARD_SIZE * STEP
    );


    hoverWall(game);
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
    if (!boardEnabled) {
        wallPreview->setVisible(false);
        event->ignore();
        return;
    }

    //TODO: check remaining walls for the current player
    //DONE
    if ((game.turn == 0 && game.p0_walls <= 0) ||
        (game.turn == 1 && game.p1_walls <= 0)) {
        wallPreview->setVisible(false);
        return;
    }
    int r, c;
    HoverType type = detectHover(event->scenePos(), r, c);

    if (type == HoverType::None) {
        wallPreview->setVisible(false);
    }
    else if (type != lastHover) {
        lastHover = type;
    }
    if (type == HoverType::VerticalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {
            if (hoverVertical[r][c]) {
                wallPreview->setOrientation(ori::Vertical);
                wallPreview->setPos(c * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2, r * STEP - (WALL_LEN - STEP - CELL_SIZE)/2 );
                wallPreview->setOpacity(0.4);
                wallPreview->setVisible(true);
            }
        }
    }
    else if (type == HoverType::HorizontalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {
            if (hoverHorizontal[r][c]) {
                wallPreview->setOrientation(ori::Horizontal);
                wallPreview->setPos(c * STEP - (WALL_LEN - STEP - CELL_SIZE)/2, r * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2);
                wallPreview->setOpacity(0.4);
                wallPreview->setVisible(true);
            }
        }
    }
    else {
        wallPreview->setVisible(false);
    }
}

void BoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!boardEnabled) {
        event->ignore();
        return;
    }
    if (event->button() != Qt::LeftButton) return;

    int r, c;
    HoverType type = detectHover(event->scenePos(), r, c);


    if (type == HoverType::Cell) {
        PawnItem *p = game.turn == 0 ? white : black;
        UndoAction a;
        a.type = ActionType::PawnMove;
        a.prevTurn = game.turn;
        a.prevP0Pos = game.player0_pos;
        a.prevP1Pos = game.player1_pos;

        if (movePawn(p, r, c)) {
            a.nextP0Pos = game.player0_pos;
            a.nextP1Pos = game.player1_pos;

            undoStack.push_back(a);
            redoStack.clear();
            game.turn = !game.turn;
            hoverWall(game);
            updateTurnHighlight();
        }
    }
    else if ((game.turn == 0 && game.p0_walls <= 0) ||
            (game.turn == 1 && game.p1_walls <= 0)) {}

    else if (type == HoverType::VerticalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {
            if (hoverVertical[r][c]){
                game.vertical_walls[r][c]= true;
                game.vertical_walls[r+1][c]= true;

                auto *wall = new WallItem(ori::Vertical);
                addItem(wall);
                wall->setPos(c * STEP + CELL_SIZE - (WALL_THICK - WALL_GAP)/2, r * STEP - (WALL_LEN - STEP - CELL_SIZE)/2);
                if (game.turn == 0) {
                    game.p0_walls--;
                } else {
                    game.p1_walls--;
                }
                UndoAction a;
                a.type = ActionType::PlaceWall;
                a.prevTurn = game.turn;
                a.wallOri = ori::Vertical;
                a.r = r;
                a.c = c;
                a.wallItem = wall;

                undoStack.push_back(a);
                redoStack.clear();

                game.turn = !game.turn;
                hoverWall(game);
                updateWallCounters();
                updateTurnHighlight();

            }
        }
    }
    else if (type == HoverType::HorizontalEdge) {
        if (!(r >= BOARD_SIZE - 1 || c >= BOARD_SIZE - 1)) {
            if (hoverHorizontal[r][c]) {

                game.horizontal_walls[r][c]= true; // TODO: mark wall in array
                game.horizontal_walls[r][c+1]= true; // TODO: mark wall in array

                auto *wall = new WallItem(ori::Horizontal);
                addItem(wall);
                wall->setPos(c * STEP - (WALL_LEN - STEP - CELL_SIZE)/2, r * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2);
                if (game.turn == 0) {
                    game.p0_walls--;
                } else {
                    game.p1_walls--;
                }
                UndoAction a;
                a.type = ActionType::PlaceWall;
                a.prevTurn = game.turn;
                a.wallOri = ori::Horizontal;
                a.r = r;
                a.c = c;
                a.wallItem = wall;

                undoStack.push_back(a);
                redoStack.clear();

                game.turn = !game.turn;

                hoverWall(game);
                updateWallCounters();
                updateTurnHighlight();
            }
        }
    }
    if (mode == GameMode::PvAI)clearMoveHighlights();
    QTimer::singleShot(150, this, &BoardScene::modeAI);
}

bool BoardScene::movePawn(PawnItem *pawn, int toRow, int toCol){
    //TODO: function to get available moves
    if (mode == GameMode::PvP || game.turn == 0) {
        auto moves = getPawnLegalMoves(game);
        if (!moves.contains(QPoint(toRow, toCol))) {
            return false;
        }
        if (game.turn == 0) {
            game.player0_pos = toRow * 9 + toCol;
        } else {
            game.player1_pos = toRow * 9 + toCol;
        }
    }
    pawn->animateMove(cellCenter(toRow, toCol));
    if (checkWin()) {
        return false;
    }
    return true;
}

void BoardScene::updateTurnHighlight(){

    white->setOpacity(game.turn == 0 ? 1.0 : 0.4);
    black->setOpacity(game.turn == 1? 1.0 : 0.2);

    whiteWallsText->setOpacity(game.turn == 0 ? 1.0 : 0.5);
    blackWallsText->setOpacity(game.turn == 1 ? 1.0 : 0.5);

    showMoveHighlights();
}

void BoardScene::clearMoveHighlights()
{
    for (auto *r : moveHighlights) {
        removeItem(r);
        delete r;
    }
    moveHighlights.clear();
}

void BoardScene::showMoveHighlights()
{
    clearMoveHighlights();
    //TODO: get available moves
    auto moves =  getPawnLegalMoves(game);

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

bool BoardScene::checkWin() {
    int p0_row = game.player0_pos /9;
    int p1_row = game.player1_pos /9;

    if (p0_row == 0) {
        handleWin("White Wins!");
        return true;
    }

    if (p1_row == 8) {
        //TODO: handle palyer type
        handleWin("Black Wins!");
        return true;

    }
        return false;

}

void BoardScene::handleWin(QString w)
{
    QString text = w;

    auto *msg = addText(text, QFont("Arial", 28, QFont::Bold));
    msg->setDefaultTextColor(Qt::yellow);
    msg->setZValue(10);
    msg->setPos(sceneRect().center() - QPointF(120, 40));

    // Block further input
    setBoardEnabled(false);
    // QMessageBox::information(nullptr, "Game Over", winner + " wins!");
}

void BoardScene::updateWallCounters()
{
    whiteWallsText->setPlainText(
        QString("WHITE\nWalls: %1").arg(game.p0_walls)
    );

    blackWallsText->setPlainText(
        QString("BLACK\nWalls: %1").arg(game.p1_walls)
    );
}

void BoardScene::modeAI() {
    if (mode == GameMode::PvAI && game.turn == 1) {
        clearMoveHighlights();
        setBoardEnabled(false);

        GameState before = game;
        int s=undoStack.size()>1?undoStack[undoStack.size()-2].prevP1Pos:0;

        game = AIMove(game, diff,s);
        GameState after = game;
        bool valid = true;

        if (before.player1_pos != after.player1_pos) {
            UndoAction a;
            a.type = ActionType::PawnMove;
            a.prevP0Pos = before.player0_pos;
            a.prevP1Pos = before.player1_pos;
            a.nextP0Pos = after.player0_pos;
            a.nextP1Pos = after.player1_pos;
            a.prevTurn = 1;
            undoStack.push_back(a);

            int pos = after.player1_pos;
            int r = pos / 9;
            int c = pos % 9;

            movePawn(black, r, c);
            valid = false;
        }
        for (int r = 0; r < BOARD_SIZE - 1; r++) {
            if (!valid) break;
            for (int c = 0; c < BOARD_SIZE - 1; c++) {
                if (!before.vertical_walls[r][c] && after.vertical_walls[r][c]) {
                    auto *wall = new WallItem(ori::Vertical);
                    addItem(wall);
                    wall->setPos(c * STEP + CELL_SIZE - (WALL_THICK - WALL_GAP)/2, r * STEP - (WALL_LEN - STEP - CELL_SIZE)/2);
                    valid = false;
                    UndoAction a;
                    a.type = ActionType::PlaceWall;
                    a.prevTurn = 1;
                    a.wallOri = ori::Vertical;
                    a.r = r;
                    a.c = c;
                    a.wallItem = wall;

                    undoStack.push_back(a);
                    break;
                }
                if (!before.horizontal_walls[r][c] && after.horizontal_walls[r][c]) {
                    auto *wall = new WallItem(ori::Horizontal);
                    addItem(wall);
                    wall->setPos(c * STEP - (WALL_LEN - STEP - CELL_SIZE)/2, r * STEP + CELL_SIZE - (WALL_THICK-WALL_GAP)/2);
                    valid = false;
                    UndoAction a;
                    a.type = ActionType::PlaceWall;
                    a.prevTurn = 1;
                    a.wallOri = ori::Horizontal;
                    a.r = r;
                    a.c = c;
                    a.wallItem = wall;

                    undoStack.push_back(a);
                    break;
                }
            }
        }
        game.turn = 0;
        if (!checkWin()){
            setBoardEnabled(true);
            hoverWall(game);
            updateWallCounters();
            updateTurnHighlight();
        }
    }
}

void BoardScene::undo() {
    if (undoStack.isEmpty())
        return;
    if (!boardEnabled)
        return;

    UndoAction a = undoStack.takeLast();
    redoStack.push_back(a);
    game.turn = a.prevTurn;


    if (a.type == ActionType::PawnMove) {
        game.player0_pos = a.prevP0Pos;
        game.player1_pos = a.prevP1Pos;

        white->animateMove(cellCenter(game.player0_pos/9,game.player0_pos%9 ));
        black->animateMove(cellCenter(game.player1_pos/9,game.player1_pos%9 ));
    }

    else if (a.type == ActionType::PlaceWall) {

        if (a.wallOri == ori::Vertical) {
            game.vertical_walls[a.r][a.c] = false;
            game.vertical_walls[a.r + 1][a.c] = false;
        } else {
            game.horizontal_walls[a.r][a.c] = false;
            game.horizontal_walls[a.r][a.c + 1] = false;
        }
        removeItem(a.wallItem);

        game.turn == 0 ? game.p0_walls++ : game.p1_walls++;
    }
    hoverWall(game);
    updateWallCounters();
    updateTurnHighlight();
}

void BoardScene::redo() {
    if (redoStack.isEmpty())
        return;
    if (!boardEnabled)
        return;

    UndoAction a = redoStack.takeLast();
    undoStack.push_back(a);


    if (a.type == ActionType::PawnMove) {
        game.player0_pos = a.nextP0Pos;
        game.player1_pos = a.nextP1Pos;

        white->animateMove(cellCenter(game.player0_pos/9,game.player0_pos%9 ));
        black->animateMove(cellCenter(game.player1_pos/9,game.player1_pos%9 ));
    }

    else if (a.type == ActionType::PlaceWall) {

        if (a.wallOri == ori::Vertical) {
            game.vertical_walls[a.r][a.c] = true;
            game.vertical_walls[a.r + 1][a.c] = true;
        } else {
            game.horizontal_walls[a.r][a.c] = true;
            game.horizontal_walls[a.r][a.c + 1] = true;
        }
        addItem(a.wallItem);
        game.turn == 0 ? game.p0_walls-- : game.p1_walls--;
    }
    game.turn = !a.prevTurn;
    hoverWall(game);
    updateWallCounters();
    updateTurnHighlight();
}




