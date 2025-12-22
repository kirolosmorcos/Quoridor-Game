//
// Created by ramez on 12/15/2025.
//

#ifndef QUORIDOR_GAME_BOARDSCENE_H
#define QUORIDOR_GAME_BOARDSCENE_H

#pragma once
#include <QGraphicsScene>

#include "../../Models/GameState.h"
#include "../util/Constants.h"
#include "../Controller.h"


class WallItem;
class PawnItem;


class BoardScene : public QGraphicsScene {
    Q_OBJECT
    public:

    BoardScene(GameMode mode, Difficulty diff, QColor p1Color,
           QColor p2Color,bool turn, QObject *parent=nullptr);

    QPointF cellCenter(int row, int col) const;
    HoverType detectHover(const QPointF &p, int &row, int &col) const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    bool movePawn(PawnItem *pawn, int toRow, int toCol);

    void updateWallCounters();
    void updateTurnHighlight();
    void showMoveHighlights();
    void clearMoveHighlights();
    bool checkWin();
    void handleWin(QString w);

    void modeAI();
    void undo();
    void redo();


    QVector<QGraphicsRectItem*> moveHighlights;
    WallItem *wallPreview = nullptr;
    HoverType lastHover = HoverType::None;
    QGraphicsRectItem *whiteGoalRect = nullptr;
    QGraphicsRectItem *blackGoalRect = nullptr;
    GameState game;

    void setBoardEnabled(bool enabled) {
        boardEnabled = enabled;
        clearMoveHighlights();
    }

public slots:
void reset();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private:
    PawnItem *white;
    PawnItem *black;
    // Turn turn;
    bool hWall[BOARD_SIZE - 1][BOARD_SIZE]; // horizontal walls
    bool vWall[BOARD_SIZE][BOARD_SIZE - 1]; // vertical walls
    bool boardEnabled = true;

    QGraphicsTextItem *whiteWallsText = nullptr;
    QGraphicsTextItem *blackWallsText = nullptr;

    GameMode mode;
    Difficulty diff;

    QVector<UndoAction> undoStack;
    QVector<UndoAction> redoStack;

    QColor p1Color;
    QColor p2Color;
    bool turn;
};


#endif //QUORIDOR_GAME_BOARDSCENE_H