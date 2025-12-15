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
