#ifndef QUORIDOR_EVALUAION_FUNCTION_H
#define QUORIDOR_EVALUAION_FUNCTION_H

#include "../Models/GameState.h"
#include "../Game Logic/BFS.h"
#include "../Game Logic/Legal Moves.h"
#include <vector>
#include <algorithm>
using namespace std;

int evaluateBoard(GameState state);
int heuresticDistanceToGoalDifference(GameState state);
int BlockingPotential(GameState state);

#endif //QUORIDOR_EVALUAION_FUNCTION_H
