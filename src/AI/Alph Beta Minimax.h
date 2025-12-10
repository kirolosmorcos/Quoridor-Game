//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_ALPH_BETA_MINIMAX_H
#define QUORIDOR_ALPH_BETA_MINIMAX_H

#include "../Models/GameState.h"

int alphaBeta(GameState gameState, int depth, int alpha, int beta, bool maximizingPlayer);
#endif //QUORIDOR_ALPH_BETA_MINIMAX_H
