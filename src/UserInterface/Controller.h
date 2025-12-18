//
// Created by ramez on 12/18/2025.
//

#ifndef QUORIDOR_GAME_CONTROLLER_H
#define QUORIDOR_GAME_CONTROLLER_H
//3iz vector of integers for positions of the pawn u take game state ys7bi
//3iz vbox wa hbox
//3iz gamestate mn AI

#include "../Models/GameState.h"
#include "../Game Logic/Legal Moves.h"
#include <bits/stdc++.h>

using namespace std;

bool hoverHorizontal[8][9];
bool hoverVertical[9][8];


vector<int> getPawnLegalMoves(GameState state);
void hoverWall(GameState state);

GameState AIMove(GameState state);

#endif //QUORIDOR_GAME_CONTROLLER_H