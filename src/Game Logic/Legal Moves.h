#ifndef QUORIDOR_LEGAL_MOVES_H
#define QUORIDOR_LEGAL_MOVES_H

#include "../Models/GameState.h"
#include "../AI/Evaluaion Function.h"
#include "BFS.h"
#include "../UserInterface/Controller.h"
#include <vector>
#include <algorithm>


using namespace std;

vector<GameState> normalPawnMoves(GameState gameState, bool player);
vector<GameState> jumpMoves(GameState gameState, bool player);

vector<GameState> horizontalWallMoves(GameState gameState, bool player);
vector<GameState> verticalWallMoves(GameState gameState, bool player);

vector<GameState> getAllLegalMoves(GameState gameState, bool player);

vector<GameState> getAscendingHeuristicMoves(GameState gameState, bool player, int numberOfMoves);
vector<GameState> getDescendingHeuristicMoves(GameState gameState, bool player, int numberOfMoves);

#endif //QUORIDOR_LEGAL_MOVES_H
