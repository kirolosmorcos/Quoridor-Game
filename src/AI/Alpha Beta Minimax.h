//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_ALPHA_BETA_MINIMAX_H
#define QUORIDOR_ALPHA_BETA_MINIMAX_H

#include "../Models/GameState.h"

int AlphaBetaMinimax(const GameState & gameState, int depth, int alpha, int beta, bool maximizingPlayer);
#endif //QUORIDOR_ALPHA_BETA_MINIMAX_H
