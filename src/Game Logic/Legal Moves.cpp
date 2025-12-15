#include "../Models/GameState.h"
#include <bits/stdc++.h>

#include "BFS.h"

using namespace std;

vector<GameState> normalPawnMoves(GameState gamestate) {
	// Implement the logic to calculate normal pawn moves up,right ,left, down
	/*  if nextCell is outside the board:
	  continue

	  if wall exists between pawnPosition and nextCell:
	  continue

	  if nextCell == opponentPosition:
	  continue*/
}

vector<GameState> jumpMoves(GameState gamestate) {
	//moves = empty list
	//
	//if opponent is adjacent to myPawn:
	//direction = directionFrom(myPawn to opponentPawn)
	//jumpCell = cellBehind(opponentPawn, direction)
	//
	//if jumpCell exists AND no wall between opponentPawn and jumpCell:
	//add jumpCell to moves
	//else:
	//for diagonal in diagonalCellsAround(opponentPawn):
	//if diagonal exists AND no wall blocks diagonal:
	//add diagonal to moves
}

vector<GameState> horizontalWallMoves(GameState gameState, bool player) {
	vector<GameState> legalWallMoves = vector<GameState>();
	// check remaining walls
	if (player) {
		if (gameState.p1_walls == 0) {
			return legalWallMoves;
		}
	}
	else {
		if (gameState.p0_walls == 0) {
			return legalWallMoves;
		}
	}

	// check all legal moves
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameState.horizontal_walls[i][j] ||		// cell is occupied
				gameState.horizontal_walls[i][j + 1] || // adjacent cell is occupied (horizontal wall occupy 2 cells)
				(gameState.vertical_walls[i][j] && gameState.vertical_walls[i + 1][j]) // slot crosses vertical wall
			) {
				continue;
			}
			// temporary place wall and check if both players have a path
			gameState.horizontal_walls[i][j] = true;
			gameState.horizontal_walls[i][j + 1] = true;
			if (player) {
				gameState.p1_walls--;
			}
			else {
				gameState.p0_walls--;
			}
			int shortest_path_player_0 = bfs(gameState, false);
			int shortest_path_player_1 = bfs(gameState, true);
			if (shortest_path_player_0 != -1 && shortest_path_player_1 != -1) {		// valid wall
				legalWallMoves.push_back(gameState);
			}
			// remove wall
			gameState.horizontal_walls[i][j] = false;
			gameState.horizontal_walls[i][j + 1] = false;
			if (player) {
				gameState.p1_walls++;
			}
			else {
				gameState.p0_walls++;
			}
		}
	}
	return legalWallMoves;
}

vector<GameState> verticalWallMoves(GameState gameState, bool player) {
	vector<GameState> legalWallMoves = vector<GameState>();
	// check remaining walls
	if (player) {
		if (gameState.p1_walls == 0) {
			return legalWallMoves;
		}
	}
	else {
		if (gameState.p0_walls == 0) {
			return legalWallMoves;
		}
	}

	// check all legal moves
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (gameState.vertical_walls[i][j] ||		// cell is occupied
				gameState.vertical_walls[i + 1][j] ||	// adjacent cell is occupied
				(gameState.horizontal_walls[i][j] && gameState.horizontal_walls[i][j + 1])	// slot crosses horizontal wall
				) {
				continue;
			}
			// temporary place wall and check if both players have a path
			gameState.vertical_walls[i][j] = true;
			gameState.vertical_walls[i + 1][j] = true;
			if (player) {
				gameState.p1_walls--;
			}
			else {
				gameState.p0_walls--;
			}
			int shortest_path_player_0 = bfs(gameState, false);
			int shortest_path_player_1 = bfs(gameState, true);
			if ((shortest_path_player_0 != -1) && (shortest_path_player_1 != -1)) {		// valid wall
				legalWallMoves.push_back(gameState);
			}
			// remove wall
			gameState.vertical_walls[i][j] = false;
			gameState.vertical_walls[i + 1][j] = false;
			if (player) {
				gameState.p1_walls++;
			}
			else {
				gameState.p0_walls++;
			}
		}
	}
	return legalWallMoves;
}
