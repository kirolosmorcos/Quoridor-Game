#include "Legal Moves.h"

vector<GameState> normalPawnMoves(GameState gameState, bool player) {
	vector<GameState> legalNormalPawnMoves = vector<GameState>();

	int currentPawnRow, currentPawnCol;
	int opponentPawnRow, opponentPawnCol;
	if (player) {
		currentPawnRow = gameState.getrow(gameState.player1_pos);
		currentPawnCol = gameState.getcol(gameState.player1_pos);
		opponentPawnRow = gameState.getrow(gameState.player0_pos);
		opponentPawnCol = gameState.getcol(gameState.player0_pos);
	}
	else {
		currentPawnRow = gameState.getrow(gameState.player0_pos);
		currentPawnCol = gameState.getcol(gameState.player0_pos);
		opponentPawnRow = gameState.getrow(gameState.player1_pos);
		opponentPawnCol = gameState.getcol(gameState.player1_pos);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check moving up
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (currentPawnRow != 0) { // inside board
		if (!gameState.horizontal_walls[currentPawnRow - 1][currentPawnCol] && // No wall upwards
			((currentPawnCol != opponentPawnCol) || ((currentPawnRow - 1) != opponentPawnRow)) // Opponent pawn isn't upwards
		   ) {
			int nextPawnPosition = (currentPawnRow - 1) * 9 + currentPawnCol;
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalNormalPawnMoves.push_back(gameState);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check moving down
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (currentPawnRow != 8) { // inside board
		if (!gameState.horizontal_walls[currentPawnRow][currentPawnCol] && // No wall downwards
			((currentPawnCol != opponentPawnCol) || ((currentPawnRow + 1) != opponentPawnRow)) // Opponent pawn isn't downwards
		   ){
			int nextPawnPosition = (currentPawnRow + 1) * 9 + currentPawnCol;
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalNormalPawnMoves.push_back(gameState);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check moving left
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (currentPawnCol != 0) { // inside board
		if (!gameState.vertical_walls[currentPawnRow][currentPawnCol - 1] && // No wall leftwards
			((currentPawnRow != opponentPawnRow) || ((currentPawnCol - 1) != opponentPawnCol)) // Opponent pawn isn't leftwards
		   ) {
			int nextPawnPosition = currentPawnRow * 9 + (currentPawnCol - 1);
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalNormalPawnMoves.push_back(gameState);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check moving right
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (currentPawnCol != 8) { // inside board
		if (!gameState.vertical_walls[currentPawnRow][currentPawnCol] && // No wall rightwards
			((currentPawnRow != opponentPawnRow) || ((currentPawnCol + 1) != opponentPawnCol)) // Opponent pawn isn't rightwards
		   ) {
			int nextPawnPosition = currentPawnRow * 9 + (currentPawnCol + 1);
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalNormalPawnMoves.push_back(gameState);
		}
	}

	return legalNormalPawnMoves;
}

vector<GameState> jumpMoves(GameState gameState, bool player) {
	vector<GameState> legalJumpMoves = vector<GameState>();

	int currentPawnRow, currentPawnCol;
	int opponentPawnRow, opponentPawnCol;
	if (player) {
		currentPawnRow = gameState.getrow(gameState.player1_pos);
		currentPawnCol = gameState.getcol(gameState.player1_pos);
		opponentPawnRow = gameState.getrow(gameState.player0_pos);
		opponentPawnCol = gameState.getcol(gameState.player0_pos);
	}
	else {
		currentPawnRow = gameState.getrow(gameState.player0_pos);
		currentPawnCol = gameState.getcol(gameState.player0_pos);
		opponentPawnRow = gameState.getrow(gameState.player1_pos);
		opponentPawnCol = gameState.getcol(gameState.player1_pos);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check adjacent up
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if ((currentPawnCol == opponentPawnCol) && ((currentPawnRow - 1) == opponentPawnRow)	// adjacent upwards
		&& !gameState.horizontal_walls[currentPawnRow - 1][currentPawnCol]) {	// & no walls between them
		// check if there is no wall above opponent pawn & inside board
		if ((opponentPawnRow != 0) // can jump up over inside board
			&& !gameState.horizontal_walls[opponentPawnRow - 1][opponentPawnCol] // No wall upwards
			) {
			int nextPawnPosition = (opponentPawnRow - 1) * 9 + opponentPawnCol;
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalJumpMoves.push_back(gameState);
		}
		else {	// check jump diagonal up
			// check jumping up left diagonal
			if((opponentPawnCol != 0)	// can jump left over the opponent
				&& !gameState.vertical_walls[opponentPawnRow][opponentPawnCol - 1]	// No wall leftward the opponent
				) {
				int nextPawnPosition = opponentPawnRow * 9 + (opponentPawnCol - 1);
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
			// check jumping up right diagonal
			if((opponentPawnCol != 8)	// can jump right over the opponent
				&& !gameState.vertical_walls[opponentPawnRow][opponentPawnCol]	// No wall rightwards the opponent
				) {
				int nextPawnPosition = opponentPawnRow * 9 + (opponentPawnCol + 1);
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check adjacent down
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ((currentPawnCol == opponentPawnCol) && ((currentPawnRow + 1) == opponentPawnRow)	// adjacent downwards
			 && !gameState.horizontal_walls[currentPawnRow][currentPawnCol]) {	// & no walls between them
		// check if there is no wall below opponent pawn & inside board
		if ((opponentPawnRow != 8) // can jump down over inside board
			&& !gameState.horizontal_walls[opponentPawnRow][opponentPawnCol] // No wall downwards the opponent
			) {
			int nextPawnPosition = (opponentPawnRow + 1) * 9 + opponentPawnCol;
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalJumpMoves.push_back(gameState);
		}
		else {	// check jump diagonal down
			// check jumping down left diagonal
			if((opponentPawnCol != 0)	// can jump left over the opponent
				&& !gameState.vertical_walls[opponentPawnRow][opponentPawnCol - 1]	// No wall leftward the opponent
				) {
				int nextPawnPosition = opponentPawnRow * 9 + (opponentPawnCol - 1);
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
			// check jumping down right diagonal
			if((opponentPawnCol != 8)	// can jump right over the opponent
				&& !gameState.vertical_walls[opponentPawnRow][opponentPawnCol]	// No wall rightwards the opponent
				) {
				int nextPawnPosition = opponentPawnRow * 9 + (opponentPawnCol + 1);
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check adjacent left
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ((currentPawnRow == opponentPawnRow) && ((currentPawnCol - 1) == opponentPawnCol)	// adjacent leftwards
			 && !gameState.vertical_walls[currentPawnRow][currentPawnCol - 1]) {	// & no walls between them
		// check if there is no wall left opponent pawn & inside board
		if ((opponentPawnCol != 0) // can jump left over inside board
			&& !gameState.vertical_walls[opponentPawnRow][opponentPawnCol - 1] // No wall leftwards the opponent
			) {
			int nextPawnPosition = opponentPawnRow * 9 + (opponentPawnCol - 1);
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalJumpMoves.push_back(gameState);
		}
		else {	// check jump diagonal left
			// check jumping left up diagonal
			if((opponentPawnRow != 0)	// can jump up over the opponent
				&& !gameState.horizontal_walls[opponentPawnRow - 1][opponentPawnCol]	// No wall upward the opponent
				) {
				int nextPawnPosition = (opponentPawnRow - 1) * 9 + opponentPawnCol;
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
			// check jumping left down diagonal
			if((opponentPawnRow != 8)	// can jump down over the opponent
				&& !gameState.horizontal_walls[opponentPawnRow][opponentPawnCol]	// No wall downwards the opponent
				) {
				int nextPawnPosition = (opponentPawnRow + 1) * 9 + opponentPawnCol;
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// check adjacent right
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ((currentPawnRow == opponentPawnRow) && ((currentPawnCol + 1) == opponentPawnCol)	// adjacent rightwards
			 && !gameState.vertical_walls[currentPawnRow][currentPawnCol]) {	// & no walls between them
		// check if there is no wall right opponent pawn & inside board
		if ((opponentPawnCol != 8) // can jump right over inside board
			&& !gameState.vertical_walls[opponentPawnRow][opponentPawnCol] // No wall rightwards the opponent
			) {
			int nextPawnPosition = opponentPawnRow * 9 + (opponentPawnCol + 1);
			if (player) {
				gameState.player1_pos = nextPawnPosition;
			}
			else {
				gameState.player0_pos = nextPawnPosition;
			}
			legalJumpMoves.push_back(gameState);
		}
		else {	// check jump diagonal right
			// check jumping right up diagonal
			if((opponentPawnRow != 0)	// can jump up over the opponent
				&& !gameState.horizontal_walls[opponentPawnRow - 1][opponentPawnCol]	// No wall upward the opponent
				) {
				int nextPawnPosition = (opponentPawnRow - 1) * 9 + opponentPawnCol;
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
			// check jumping right down diagonal
			if((opponentPawnRow != 8)	// can jump down over the opponent
				&& !gameState.horizontal_walls[opponentPawnRow][opponentPawnCol]	// No wall downwards the opponent
				) {
				int nextPawnPosition = (opponentPawnRow + 1) * 9 + opponentPawnCol;
				if (player) {
					gameState.player1_pos = nextPawnPosition;
				}
				else {
					gameState.player0_pos = nextPawnPosition;
				}
				legalJumpMoves.push_back(gameState);
			}
		}
	}

	return legalJumpMoves;
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
			if (gameState.horizontal_walls[i][j] || // cell is occupied
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
			if (shortest_path_player_0 != -1 && shortest_path_player_1 != -1) {
				// valid wall
				legalWallMoves.push_back(gameState);
				// Add to UI legal hover horizontal wall array
				hoverHorizontal[i][j] = true;
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
			if (gameState.vertical_walls[i][j] || // cell is occupied
				gameState.vertical_walls[i + 1][j] || // adjacent cell is occupied
				(gameState.horizontal_walls[i][j] && gameState.horizontal_walls[i][j + 1]) // slot crosses horizontal wall
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
			if ((shortest_path_player_0 != -1) && (shortest_path_player_1 != -1)) {
				// valid wall
				legalWallMoves.push_back(gameState);
				// Add to UI legal hover vertical wall array
				hoverVertical[i][j] = true;
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

vector<GameState> getAllLegalMoves(GameState gameState, bool player) {
	vector<GameState> legalHorizontalWallMoves = horizontalWallMoves(gameState, player);
	vector<GameState> legalVerticalWallMoves = verticalWallMoves(gameState, player);
	vector<GameState> legalNormalPawnMoves = normalPawnMoves(gameState, player);
	vector<GameState> legalJumpMoves = jumpMoves(gameState, player);

	vector<GameState> allLegalMoves;
	allLegalMoves.reserve(legalHorizontalWallMoves.size() + legalVerticalWallMoves.size() +
		legalNormalPawnMoves.size() + legalJumpMoves.size());
	allLegalMoves.insert(allLegalMoves.end(), legalHorizontalWallMoves.begin(), legalHorizontalWallMoves.end());
	allLegalMoves.insert(allLegalMoves.end(), legalVerticalWallMoves.begin(), legalVerticalWallMoves.end());
	allLegalMoves.insert(allLegalMoves.end(), legalNormalPawnMoves.begin(), legalNormalPawnMoves.end());
	allLegalMoves.insert(allLegalMoves.end(), legalJumpMoves.begin(), legalJumpMoves.end());
	return allLegalMoves;
}

vector<GameState> getAscendingHeuristicMoves(GameState gameState, bool player, int numberOfMoves) {
	vector<GameState> allLegalMoves = getAllLegalMoves(gameState, player);
	sort(allLegalMoves.begin(), allLegalMoves.end(),
	     [](const GameState& a, const GameState& b) {
		     return heuresticDistanceToGoalDifference(a) < heuresticDistanceToGoalDifference(b);
	     }
	);
	if(allLegalMoves.size() > numberOfMoves) {
		allLegalMoves.resize(numberOfMoves);
	}
	return allLegalMoves;
}

vector<GameState> getDescendingHeuristicMoves(GameState gameState, bool player, int numberOfMoves) {
	vector<GameState> allLegalMoves = getAllLegalMoves(gameState, player);
	sort(allLegalMoves.begin(), allLegalMoves.end(),
	     [](const GameState& a, const GameState& b) {
		     return heuresticDistanceToGoalDifference(a) > heuresticDistanceToGoalDifference(b);
	     }
	);
	if(allLegalMoves.size() > numberOfMoves) {
		allLegalMoves.resize(numberOfMoves);
	}
	return allLegalMoves;
}
