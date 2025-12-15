#include "../Models/GameState.h"
#include "../Game Logic/Legal  Moves.h"
#include "../Game Logic/BFS.h"
#include <bits/stdc++.h>

using namespace std;

int evaluateBoard(GameState state){
//    score = (opponentDistance - aiDistance) * 10
//            + (AI walls remaining) * 2
//                                   - (opponent walls remaining) * 1
// + BlockingPotential(state)*weight
//  +winBonus


//    Win bonus
//    if AI_distance == 0:
//    winBonus = +1000
//    elif Opp_distance == 0:
//    winBonus = -1000
//    else:
//    winBonus=0

// search if there are more factors to add to the evaluation function
}

int BlockingPotential(GameState state, bool aiPlayer, bool opponentPlayer ) {

    int blockingBonus = 0;
    
    //Get all legal walls AI can place

    vector <GameState> legalWalls;
    vector <GameState> legalHorizontalWalls = horizontalWallMoves(state, aiPlayer);
    vector <GameState> legalverticaleWalls = verticalWallMoves(state, aiPlayer);

    legalWalls.insert(legalWalls.end(), legalHorizontalWalls.begin(), legalHorizontalWalls.end());
    legalWalls.insert(legalWalls.end(), legalverticaleWalls.begin(), legalverticaleWalls.end());

    // Measure opponent's current shortest path

    int currentOppDistance = bfs(state, opponentPlayer);

    //Check each legal wall

    for (auto &wall : legalWalls) {
    int newOppDistance = bfs(wall, opponentPlayer);
    int bonus = newOppDistance - currentOppDistance;
    if (bonus > 0) {
        int blockingBonusScore = bonus * 2;
        blockingBonus = max(blockingBonus, blockingBonusScore);
    }
    return blockingBonus;
}




}