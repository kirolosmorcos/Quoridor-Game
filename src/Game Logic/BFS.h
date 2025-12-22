//
// Created by kiro3 on 12/10/2025.
//

#ifndef QUORIDOR_BFS_H
#define QUORIDOR_BFS_H

#include "../Models/GameState.h"
#include "Legal Moves.h"
#include <queue>
#include <cstring>

using namespace std;

int bfs(GameState gamestate, bool player) ;//shortest path to goal given player (player0 -> bool player=0) (return -1-> no path to goal)
#endif //QUORIDOR_BFS_H
