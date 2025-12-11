//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_EVALUAION_FUNCTION_H
#define QUORIDOR_EVALUAION_FUNCTION_H

#include "../Models/GameState.h"

int evaluateBoard(GameState state);
int heuresticDistanceToGoalDifference(GameState state);
int BlockingPotential(GameState state);

#endif //QUORIDOR_EVALUAION_FUNCTION_H
