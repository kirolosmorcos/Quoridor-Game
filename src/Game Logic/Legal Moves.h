//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_LEGAL_MOVES_H
#define QUORIDOR_LEGAL_MOVES_H

#include "../Models/GameState.h"
#include <bits/stdc++.h>

using namespace std;

vector<GameState> getAllLegalMoves(GameState gamestate);

vector <GameState> getAscendingHeuristicMoves(GameState gamestate ,int numberOfMoves);
vector<GameState> getDescendingHeuristicMoves(GameState gamestate ,int numberOfMoves);

vector<GameState>  normalPawnMoves(GameState gamestate);
vector<GameState> jumpMoves(GameState gamestate);
vector<GameState> horizontalWallMoves(GameState gameState, bool player);
vector<GameState> verticalWallMoves(GameState gameState, bool player);

#endif //QUORIDOR_LEGAL_MOVES_H
