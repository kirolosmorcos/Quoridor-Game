//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_BEST_MOVE_H
#define QUORIDOR_BEST_MOVE_H

#include "../Models/GameState.h"
#include "../Models/GameState.h"
#include "../Game Logic/Legal Moves.h"
#include "Alpha Beta Minimax.h"

GameState  chooseBestMove(GameState state, int depth, int numberOfMoves);



#endif //QUORIDOR_BEST_MOVE_H
