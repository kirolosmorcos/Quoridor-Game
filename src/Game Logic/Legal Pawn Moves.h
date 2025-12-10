//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_LEGAL_PAWN_MOVES_H
#define QUORIDOR_LEGAL_PAWN_MOVES_H

#include "../Models/GameState.h"
#include <bits/stdc++.h>

using namespace std;

vector<GameState>  normalPawnMoves(GameState gamestate);
vector<GameState> jumpMoves(GameState gamestate);

#endif //QUORIDOR_LEGAL_PAWN_MOVES_H
