//
// Created by ramez on 12/15/2025.
//

#ifndef QUORIDOR_GAME_PAWNSELECTWINDOW_H
#define QUORIDOR_GAME_PAWNSELECTWINDOW_H


#pragma once
#include <QWidget>
#include "../util/Constants.h"


class PawnSelectWindow : public QWidget {
    Q_OBJECT
    public:
    PawnSelectWindow(GameMode mode, Difficulty diff, QWidget *parent=nullptr);
};


#endif //QUORIDOR_GAME_PAWNSELECTWINDOW_H