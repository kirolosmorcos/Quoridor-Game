//
// Created by ramez on 12/15/2025.
//

#ifndef QUORIDOR_GAME_MODESELECTWINDOW_H
#define QUORIDOR_GAME_MODESELECTWINDOW_H


#pragma once
#include <QWidget>
#include "../util/Constants.h"


class ModeSelectWindow : public QWidget {
    Q_OBJECT
    public:
    explicit ModeSelectWindow(QWidget *parent=nullptr);
};

#endif //QUORIDOR_GAME_MODESELECTWINDOW_H