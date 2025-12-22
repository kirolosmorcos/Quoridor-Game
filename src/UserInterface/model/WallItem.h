//
// Created by ramez on 12/15/2025.
//

#ifndef QUORIDOR_GAME_WALLITEM_H
#define QUORIDOR_GAME_WALLITEM_H
#pragma once
#include <QGraphicsRectItem>


enum class ori;

class WallItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    explicit WallItem(ori o);
    void setOrientation(ori o);

private:
    ori orientation;
};

#endif //QUORIDOR_GAME_WALLITEM_H