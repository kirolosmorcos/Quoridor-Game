//
// Created by ramez on 12/15/2025.
//

#ifndef QUORIDOR_GAME_GAMEWINDOW_H
#define QUORIDOR_GAME_GAMEWINDOW_H


#pragma once
#include <QMainWindow>
#include "../util/Constants.h"


class BoardScene;


class GameWindow : public QMainWindow {
    Q_OBJECT
    public:
    GameWindow(GameMode mode, Difficulty diff, QWidget *parent=nullptr);
};


#endif //QUORIDOR_GAME_GAMEWINDOW_H