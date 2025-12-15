#include <iostream>
#include <vector>
#include "GameState.h"
#include "Legal Moves.h"

using namespace std;

int main() {
	GameState gameState;

	gameState.turn = true;

	gameState.player0_pos = 0 * 9 + 4; // (row 0, col 4)
	gameState.player1_pos = 8 * 9 + 4; // (row 8, col 4)

	// Initialize all horizontal walls to false
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 9; j++) {
			gameState.horizontal_walls[i][j] = false;
		}
	}

	// Initialize all vertical walls to false
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			gameState.vertical_walls[i][j] = false;
		}
	}

	// Initial wall counts
	gameState.p0_walls = 10;
	gameState.p1_walls = 10;




	gameState.horizontal_walls[0][0] = true;
	gameState.horizontal_walls[0][1] = true;
	gameState.horizontal_walls[0][4] = true;
	gameState.horizontal_walls[0][5] = true;


	vector<GameState> legalWallMoves = horizontalWallMoves(gameState, false);
	for (int i = 0; i < legalWallMoves.size(); i++) {
		GameState newGameState = legalWallMoves[i];
		for(int j = 0; j < 8; j++) {
			for(int k = 0; k < 9; k++) {
				cout << newGameState.horizontal_walls[j][k] << " ";
			}
			cout << endl;
		}
		cout << "////////////////\n";
	}


	return 0;
}
