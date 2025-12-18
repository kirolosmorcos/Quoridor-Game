#include "Evaluaion Function.h"

int evaluateBoard(GameState state) {
	//    score = (opponentDistance - aiDistance) * 10
	//            + (AI walls remaining) * 2
	//                                   - (opponent walls remaining) * 1
	// + BlockingPotential(state)*weight
	//  +winBonus

	int score = heuresticDistanceToGoalDifference(state);

	int aiWalls = state.p1_walls;
	int oppWalls = state.p0_walls;
	score = +(aiWalls) * 2 - (oppWalls) * 1;
	score += (BlockingPotential(state) * 5);

	return score;

	//    Win bonus
	//    if AI_distance == 0:
	//    winBonus = +1000
	//    elif Opp_distance == 0:
	//    winBonus = -1000
	//    else:
	//    winBonus=0

	// search if there are more factors to add to the evaluation function
}

int heuresticDistanceToGoalDifference(GameState state) {
	int oppDistance = bfs(state, false);
	int aiDistance = bfs(state, true);
	int winBonus = 0;

	if (aiDistance == 0) {
		winBonus = +1000;
	}
	else if (oppDistance == 0) {
		winBonus = -1000;
	}
	else {
		winBonus = 0;
	}
	int score = (oppDistance - aiDistance) * 10 + winBonus;
	return score;
}

int BlockingPotential(GameState state) {
	int blockingBonus = 0;

	//Get all legal walls AI can place

	vector<GameState> legalWalls;
	vector<GameState> legalHorizontalWalls = horizontalWallMoves(state, true);
	vector<GameState> legalverticaleWalls = verticalWallMoves(state, true);

	legalWalls.insert(legalWalls.end(), legalHorizontalWalls.begin(), legalHorizontalWalls.end());
	legalWalls.insert(legalWalls.end(), legalverticaleWalls.begin(), legalverticaleWalls.end());

	// Measure opponent's current shortest path

	int currentOppDistance = bfs(state, false);

	//Check each legal wall

	for (auto& wall : legalWalls) {
		int newOppDistance = bfs(wall, false);
		int bonus = newOppDistance - currentOppDistance;
		if (bonus > 0) {
			int blockingBonusScore = bonus * 2;
			blockingBonus = max(blockingBonus, blockingBonusScore);
		}
		return blockingBonus;
	}

	return blockingBonus;
}
